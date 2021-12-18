class PlayerMonitorBack
{	
	void PlayerMonitorBack()
	{
		GetRPCManager().AddRPC( "FalconMonitor", "setPlayerHumnityS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconMonitor", "setPlayerSkillsS", this, SingeplayerExecutionType.Server );
	}
	
	private void setPlayerHumnityS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {	
			string playerID = sender.GetId();
			
			int humanity = 0;
			string humanityLevel = "None";
			string killedPlayers = "None";
			string killedZombies = "None";
			
			#ifdef FALCON_HEROES
				PlayerHumanityValues playerHumanityData = FalconHeroesLogger.loadPlayerHumanityData(playerID);
				
				humanity = playerHumanityData.getHumanity();
				humanityLevel = playerHumanityData.getHumanityLevel();
				killedPlayers = playerHumanityData.getKilledPlayers().ToString();
				killedZombies = playerHumanityData.getKilledZeds().ToString();
			#endif
			
			PlayerHumanityPackage playerHumnityPackage = new PlayerHumanityPackage(humanity, humanityLevel, killedPlayers, killedZombies);
			
			GetRPCManager().SendRPC( "FalconMonitor", "setPlayerHumnityC", new Param1<PlayerHumanityPackage>(playerHumnityPackage), true, sender );
       	 }
    }
	
	void setPlayerHumanity() {		
		GetRPCManager().SendRPC( "FalconMonitor", "setPlayerHumnityS", new Param1<string>("") );
	}
	
	private void setPlayerSkillsS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
	{
		Param1<string> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {
			
			// Define in FalconSkills defines doesnt work dunno why...
			#ifndef FALCON_SKILLS
				#define FALCON_SKILLS
			#endif
				
			string playerID = sender.GetId();
			
			array<string> playerSkillsData = new array<string>();
			
			#ifdef FALCON_SKILLS
				playerSkillsData = FalconSkillsLogger.loadPlayerSkillData(playerID);
			#endif
			
			GetRPCManager().SendRPC( "FalconMonitor", "setPlayerSkillsC", new Param1<array<string>>(playerSkillsData), true, sender );
       	 }
	}
	
	void setPlayerSkills() {		
		GetRPCManager().SendRPC( "FalconMonitor", "setPlayerSkillsS", new Param1<string>("") );
	}
}