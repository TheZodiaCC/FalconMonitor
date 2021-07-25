modded class MissionGameplay {
	ref PlayerMonitor PlayerMonit;
	ref PlayerMonitorBack MonitorBack;

	private PlayerBase player;
	
	void MissionGameplay() {
		MonitorBack = new ref PlayerMonitorBack();
	}

	override void OnKeyPress(int key)
    {
        super.OnKeyPress(key);
		if (key == KeyCode.KC_M || key == KeyCode.KC_ESCAPE) 
		{
			if (PlayerMonit) 
			{
                if (PlayerMonit.isMenuOpened()) 
				{
                    closePlayerMenu();
                } 
				
				else if (!PlayerMonit.isMenuOpened() && key == KeyCode.KC_M) 
				{
                    openPlayerMenu();
               	}
            } 
			else if (!PlayerMonit && key == KeyCode.KC_M) 
			{
                PlayerMonit = PlayerMonitor.Cast(GetUIManager().EnterScriptedMenu(2138598, null));
                PlayerMonit.setMenuOpened(true);
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