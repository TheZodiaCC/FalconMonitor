modded class MissionGameplay {
	ref PlayerMonitor PlayerMonit;
	ref PlayerMonitorBack MonitorBack;
	private ref ModpackVersion packVersionMark = new ModpackVersion();

	private PlayerBase player;
	
	void MissionGameplay() {
		MonitorBack = new ref PlayerMonitorBack();
	}
	
	override void OnMissionLoaded()
	{
		super.OnMissionLoaded();
		
		packVersionMark.showMark();
	}

	override void OnKeyPress(int key)
    {
        super.OnKeyPress(key);
		if (key == KeyCode.KC_J || key == KeyCode.KC_ESCAPE) 
		{
			if (GetGame().GetUIManager().GetMenu() == null || GetGame().GetUIManager().GetMenu().Type().ToString() == "PlayerMonitor")
			{
				if (PlayerMonit) 
				{
	                if (PlayerMonit.isMenuOpened()) 
					{
	                    closePlayerMenu();
	                } 
					
					else if (!PlayerMonit.isMenuOpened() && key == KeyCode.KC_J) 
					{
	                    openPlayerMenu();
	               	}
	            } 
				else if (!PlayerMonit && key == KeyCode.KC_J) 
				{
	                PlayerMonit = PlayerMonitor.Cast(GetUIManager().EnterScriptedMenu(2138598, null));
	                PlayerMonit.setMenuOpened(true);
	            }
			}
		}
	}
	
	private void openPlayerMenu()
	{
		GetGame().GetUIManager().ShowScriptedMenu(PlayerMonit, NULL);
        PlayerMonit.setMenuOpened(true);
	}
	
	private void closePlayerMenu()
	{
		PlayerMonit.setMenuOpened(false);
        GetGame().GetUIManager().HideScriptedMenu(PlayerMonit);
	}
}