class PlayerMonitor extends UIScriptedMenu
{
	private Widget widgetRoot;
	
	private bool isInitialized;
    private bool isMenuOpen;
	
	private ButtonWidget btnHumanityPanel;
	private ButtonWidget btnSkillsPanel;
	
	private Widget JournalMain;
	private TextWidget JournalMainText;
	
	private Widget SkillsWidget;
	private TextWidget MechanicSkillTitleText;
	private TextWidget MechanicSkillText;
	private TextWidget MedicalSkillTitleText;
	private TextWidget MedicalSkillText;
	private TextWidget BuildingSkillTitleText;
	private TextWidget BuildingSkillText;
	
	private Widget HumanityWidget;	
	private TextWidget HumanityCountText;
	private TextWidget HumanityLevelCountText;
	private TextWidget KilledPlayersCountText;
	private TextWidget KilledZombiesCountText;
	
	private Widget currentWidget;
	
	private ref Timer buttonsTimer = new Timer( CALL_CATEGORY_SYSTEM );
	
	ref PlayerMonitorBack MonitorBack;
	
	//Constructor
	void PlayerMonitor() {		
		MonitorBack = new ref PlayerMonitorBack();
		
		//Humanity
		GetRPCManager().AddRPC( "FalconMonitor", "setPlayerHumnityC", this, SingeplayerExecutionType.Server );
		
		//Skills
		GetRPCManager().AddRPC( "FalconMonitor", "setPlayerSkillsC", this, SingeplayerExecutionType.Server );
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
			
			HumanityWidget = Widget.Cast(widgetRoot.FindAnyWidget("HumanityPanel"));
			HumanityCountText = TextWidget.Cast(widgetRoot.FindAnyWidget("HumanityCountText"));
			HumanityLevelCountText = TextWidget.Cast(widgetRoot.FindAnyWidget("HumanityLevelCountText"));
			KilledPlayersCountText = TextWidget.Cast(widgetRoot.FindAnyWidget("KilledPlayersCountText"));
			KilledZombiesCountText = TextWidget.Cast(widgetRoot.FindAnyWidget("KilledZombiesCountText"));
			
			JournalMain = Widget.Cast(widgetRoot.FindAnyWidget("JournalPanel"));
			JournalMainText = TextWidget.Cast(widgetRoot.FindAnyWidget("JournalTitleTEXT"));
			
			SkillsWidget = Widget.Cast(widgetRoot.FindAnyWidget("SkillsPanel"));
			MechanicSkillText = TextWidget.Cast(widgetRoot.FindAnyWidget("MechanicSkillText"));
			MedicalSkillText = TextWidget.Cast(widgetRoot.FindAnyWidget("MedicalSkillText"));
			BuildingSkillText = TextWidget.Cast(widgetRoot.FindAnyWidget("BuildingSkillText"));
			
			btnHumanityPanel = ButtonWidget.Cast(widgetRoot.FindAnyWidget("HumanityButtonWidget")); 
			btnSkillsPanel = ButtonWidget.Cast(widgetRoot.FindAnyWidget("SkillsButtonWidget"));
			
			WidgetEventHandler.GetInstance().RegisterOnClick(btnHumanityPanel, this, "openHumanityPanel");
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
		HumanityWidget.Show(false);
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
	
	void setPlayerHumnityC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		
		Param1<PlayerHumanityPackage> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				PlayerHumanityPackage playerHumnityPackage = data.param1;
				
				HumanityCountText.SetText(playerHumnityPackage.humanity.ToString());
				HumanityLevelCountText.SetText(playerHumnityPackage.humanityLevel);
				KilledPlayersCountText.SetText(playerHumnityPackage.killedPlayers);
				KilledZombiesCountText.SetText(playerHumnityPackage.killedZombies);
			}
		}
	}
	
	void setHumanity() {
		MonitorBack.setPlayerHumanity();
	}
	
	void setPlayerSkillsC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		
		Param1<array<string>> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				array<string> skills = new array<string>();
				skills = data.param1;
				
				int length = skills.Count();
				
				array<string> mechanicSkills = new array<string>();
				array<string> medicalSkills = new array<string>();
				array<string> buildingSkills = new array<string>();
				
				for (int i = 0; i < length; i++){
					if (skills.Get(i).IndexOf("Mechanic") != -1)
					{
						mechanicSkills.Insert(skills.Get(i));
					}
					
					if (skills.Get(i).IndexOf("Medical") != -1)
					{
						medicalSkills.Insert(skills.Get(i));
					}
					
					if (skills.Get(i).IndexOf("Building") != -1)
					{
						buildingSkills.Insert(skills.Get(i));
					}
				}
				
				switch(mechanicSkills.Count())
				{
					case 0:
						MechanicSkillText.SetText("Untaught");
						break;
					case 1:
						MechanicSkillText.SetText("Beginner");
						break;
					case 2:
						MechanicSkillText.SetText("Intermediate");
						break;
					case 3:
						MechanicSkillText.SetText("Advanced");
						break;
					default:
						break;
				
				}
				
				switch(medicalSkills.Count())
				{
					case 0:
						MedicalSkillText.SetText("Untaught");
						break;
					case 1:
						MedicalSkillText.SetText("Beginner");
						break;
					case 2:
						MedicalSkillText.SetText("Intermediate");
						break;
					case 3:
						MedicalSkillText.SetText("Advanced");
						break;
					default:
						break;
				
				}
				
				switch(buildingSkills.Count())
				{
					case 0:
						BuildingSkillText.SetText("Untaught");
						break;
					case 1:
						BuildingSkillText.SetText("Beginner");
						break;
					case 2:
						BuildingSkillText.SetText("Intermediate");
						break;
					case 3:
						BuildingSkillText.SetText("Advanced");
						break;
					default:
						break;
				
				}
			
			}
		}
	}
	
	void setPlayerSkills() {
		MonitorBack.setPlayerSkills();
	}
	
	void openHumanityPanel() 
	{
		if (!buttonsTimer.IsRunning())
		{
			currentWidget.Show(false);
		
			setHumanity();
			
			HumanityWidget.Show(true);
			currentWidget = HumanityWidget;
			
			startButtonsTimer();
		}
	}
	
	void openSkillsPanel() {
		if (!buttonsTimer.IsRunning())
		{
			currentWidget.Show(false);
		
			setPlayerSkills();
			
			SkillsWidget.Show(true);
			currentWidget = SkillsWidget;
			
			startButtonsTimer();
		}
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
	
	void startButtonsTimer()
	{
		buttonsTimer.Run(1, null, "");
	}
}
	
	
