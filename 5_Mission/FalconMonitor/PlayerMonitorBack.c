class PlayerMonitorBack
{
	const private string playersHumanityPath = "$profile:/FH/";
	const private string playersSkillsPath = "$profile:/FS/";
	const static string humanityValues = "$profile:/FValues/FHvalues.json";
	
	void PlayerMonitorBack()
	{
		GetRPCManager().AddRPC( "FalconMonitor", "setPlayerHumnityS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconMonitor", "setPlayerSkillsS", this, SingeplayerExecutionType.Server );
	}
	
	private PlayerMonitorHumanityValues loadPlayerData(string playerID)
	{
		PlayerMonitorHumanityValues playerHumanityData = new PlayerMonitorHumanityValues();
		string playerJsonPath = playersHumanityPath + playerID + ".json";
		
		if (FileExist(playerJsonPath))
		{
			JsonFileLoader<PlayerMonitorHumanityValues>.JsonLoadFile(playerJsonPath, playerHumanityData);
		}
		
		return playerHumanityData;
	}
	
	private array<string> loadPlayerSkillsData(string playerID)
	{
		array<string>  playerSkills = new array<string>();
		string playerJsonPath = playersSkillsPath + playerID + ".json";
		
		if (FileExist(playerJsonPath))
		{
			JsonFileLoader<array<string>>.JsonLoadFile(playerJsonPath, playerSkills);
		}
		
		return playerSkills;
	}
	
	private void setPlayerHumnityS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {	
			string playerID = sender.GetId();
			
			PlayerMonitorHumanityValues playerHumanityData = loadPlayerData(playerID);
			
			int humanity = playerHumanityData.getHumanity();
			string humanityLevel = playerHumanityData.getHumanityLevel();
			string killedPlayers = playerHumanityData.getKilledPlayers().ToString();
			string killedZombies = playerHumanityData.getKilledZeds().ToString();
			
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
			string playerID = sender.GetId();
			
			array<string> playerSkillsData = new array<string>();
			playerSkillsData = loadPlayerSkillsData(playerID);
			
			GetRPCManager().SendRPC( "FalconMonitor", "setPlayerSkillsC", new Param1<array<string>>(playerSkillsData), true, sender );
       	 }
	}
	
	void setPlayerSkills() {		
		GetRPCManager().SendRPC( "FalconMonitor", "setPlayerSkillsS", new Param1<string>("") );
	}
}