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
		if (key == KeyCode.KC_M) 
		{
			if ( PlayerMonit ) 
			{
                if (PlayerMonit.isMenuOpened()) 
				{
                    PlayerMonit.setMenuOpened(false);
                    GetGame().GetUIManager().HideScriptedMenu(PlayerMonit);
                    UnlockControls();
                } 
				
				else if (GetGame().GetUIManager().GetMenu() == NULL) 
				{
                    GetGame().GetUIManager().ShowScriptedMenu(PlayerMonit, NULL);
                    PlayerMonit.setMenuOpened(true);
					
                    LockControls();
               	 }
            } 
			else if (GetGame().GetUIManager().GetMenu() == NULL && PlayerMonit == null) 
			{
                LockControls();
                PlayerMonit = PlayerMonitor.Cast(GetUIManager().EnterScriptedMenu(2138598, null));
                PlayerMonit.setMenuOpened(true);
            }
		}
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