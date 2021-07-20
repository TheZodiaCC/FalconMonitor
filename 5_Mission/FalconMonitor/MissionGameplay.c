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
                LockControls();
                PlayerMonit = PlayerMonitor.Cast(GetUIManager().EnterScriptedMenu(2138598, null));
                PlayerMonit.setMenuOpened(true);
            }
		}
	}
	
	private void openPlayerMenu()
	{
		GetGame().GetUIManager().ShowScriptedMenu(PlayerMonit, NULL);
        PlayerMonit.setMenuOpened(true);

        LockControls();
	}
	
	private void closePlayerMenu()
	{
		PlayerMonit.setMenuOpened(false);
        GetGame().GetUIManager().HideScriptedMenu(PlayerMonit);
		
        UnlockControls();
	}
	
	//To avoid strange situations when closing menu
	 private void LockControls()
    {
        GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_ALL);
        GetGame().GetUIManager().ShowUICursor( true );
        GetGame().GetMission().GetHud().Show( false );
    }

    private void UnlockControls()
    {
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetUIManager().ShowUICursor( false );
        GetGame().GetMission().GetHud().Show( true );
    }
}