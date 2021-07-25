class PlayerMonitor extends UIScriptedMenu
{
	private Widget widgetRoot;
	
	private bool isInitialized;
    private bool isMenuOpen;
	
	private ButtonWidget btnHummanityPanel;
	private ButtonWidget btnSkillsPanel;
	
	private Widget JournalMain;
	private TextWidget JournalMainText;
	
	private Widget SkillsWidget;
		
	private Widget HummanityWidget;	
	private TextWidget HummanityCountText;
	private TextWidget HummanityLevelCountText;
	private TextWidget KilledPlayersCountText;
	private TextWidget KilledZombiesCountText;
	
	private Widget currentWidget;
	
	ref PlayerMonitorBack MonitorBack;
	
	//Constructor
	void PlayerMonitor() {		
		MonitorBack = new ref PlayerMonitorBack();
		
		GetRPCManager().AddRPC( "FalconMonitor", "setHummanityC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconMonitor", "setHummanityLevelC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconMonitor", "setKilledPlayersC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconMonitor", "setKilledZombiesC", this, SingeplayerExecutionType.Server );
	}
	
	//Deconstructor
	void ~PlayerMonitor() {
        PPEffects.SetBlurMenu(0);
        GetGame().GetUIManager().Back();
        g_Game.GetUIManager().ShowCursor(true);
        g_Game.GetUIManager().ShowUICursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetMission().GetHud().Show( true );
		
		delete MonitorBack;

        if ( widgetRoot )
        	widgetRoot.Unlink();
    }
	
	override Widget Init() {
		if (!isInitialized) {
			widgetRoot = GetGame().GetWorkspace().CreateWidgets("FalconMonitor/GUI/Layouts/playerMonitor.layout");
			widgetRoot.Show(false);
			
			HummanityWidget = Widget.Cast(widgetRoot.FindAnyWidget("HummanityPanel"));
			HummanityCountText = TextWidget.Cast(widgetRoot.FindAnyWidget("HummanityCountText"));
			HummanityLevelCountText = TextWidget.Cast(widgetRoot.FindAnyWidget("HummanityLevelCountText"));
			KilledPlayersCountText = TextWidget.Cast(widgetRoot.FindAnyWidget("KilledPlayersCountText"));
			KilledZombiesCountText = TextWidget.Cast(widgetRoot.FindAnyWidget("KilledZombiesCountText"));
			
			JournalMain = Widget.Cast(widgetRoot.FindAnyWidget("JournalPanel"));
			JournalMainText = TextWidget.Cast(widgetRoot.FindAnyWidget("JournalTitleTEXT"));
			
			SkillsWidget = Widget.Cast(widgetRoot.FindAnyWidget("SkillsPanel"));
		
			btnHummanityPanel = ButtonWidget.Cast(widgetRoot.FindAnyWidget("HummanityButtonWidget")); 
			btnSkillsPanel = ButtonWidget.Cast(widgetRoot.FindAnyWidget("SkillsButtonWidget"));
			
			WidgetEventHandler.GetInstance().RegisterOnClick(btnHummanityPanel, this, "openHummanityPanel");
			WidgetEventHandler.GetInstance().RegisterOnClick(btnSkillsPanel, this, "openSkillsPanel");
			
			isInitialized = true;
		}
		
		initWidgets();
		
		return widgetRoot;		
	}

	override void OnHide() {
		super.OnHide();
        PPEffects.SetBlurMenu(0);

        unlockControls();
	}
	
	override void OnShow() {
        super.OnShow();
        PPEffects.SetBlurMenu(0.5);
		
		lockControls();
    }
	
	private void initWidgets() {
		HummanityWidget.Show(false);
		SkillsWidget.Show(false);
		currentWidget = JournalMain;
		
		JournalMainText.SetText(GetGame().GetPlayer().GetIdentity().GetName());
		
		JournalMain.Show(true);
	}
	
	bool isMenuOpened() {
        return isMenuOpen;
    }
	
	void setMenuOpened(bool state) {
        isMenuOpen = state;
        if (isMenuOpen)
            PPEffects.SetBlurMenu(0.5);
        else
            PPEffects.SetBlurMenu(0);
    }
	
	void setHummanityC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		
		Param1<int> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				int hummanity = data.param1;
				HummanityCountText.SetText(hummanity.ToString());
			}
		}
	}
	
	void setHummanity() {
		MonitorBack.setPlayerHummanity();
	}
	
	void setHummanityLevelC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		
		Param1<string> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				string hummanityLevel = data.param1;
				HummanityLevelCountText.SetText(hummanityLevel);
			}
		}
	}
	
	void setHummanityLevel() {
		MonitorBack.setPlayerHummanityLevel();
	}
	
	void setKilledPlayersC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		
		Param1<string> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				string killedPlayers = data.param1;
				KilledPlayersCountText.SetText(killedPlayers);
			}
		}
	}
	
	void setKilledPlayers() {
		MonitorBack.setKilledPlayers();
	}
	
	void setKilledZombiesC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		
		Param1<string> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				string killedZombies = data.param1;
				KilledZombiesCountText.SetText(killedZombies);
			}
		}
	}
	
	void setKilledZombies() {
		MonitorBack.setKilledZombies();
	}
	
	void openHummanityPanel() {
		currentWidget.Show(false);
		
		setHummanity();
		setHummanityLevel();
		setKilledPlayers();
		setKilledZombies();
		
		HummanityWidget.Show(true);
		currentWidget = HummanityWidget;
	}
	
	void openSkillsPanel() {
		currentWidget.Show(false);
		
		SkillsWidget.Show(true);
		currentWidget = SkillsWidget;
	}
	
	private void lockControls()
    {
        GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_ALL);
        GetGame().GetUIManager().ShowUICursor( true );
        GetGame().GetMission().GetHud().Show( false );
    }

    private void unlockControls()
    {
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetUIManager().ShowUICursor( false );
        GetGame().GetMission().GetHud().Show( true );
    }
}
	
	
