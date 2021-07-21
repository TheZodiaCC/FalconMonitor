class PlayerMonitorBack
{
	const private string playersHummanityPath = "$profile:/FH/";
	const static string hummanityValues = "$profile:/FValues/FHvalues.json";
	
	void PlayerMonitorBack()
	{
		GetRPCManager().AddRPC( "FalconMonitor", "setHummanityS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconMonitor", "setHummanityLevelS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconMonitor", "setKilledPlayersS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconMonitor", "setKilledZombiesS", this, SingeplayerExecutionType.Server );
	}
	
	private PlayerMonitorHummanityValues loadPlayerData(string playerID)
	{
		PlayerMonitorHummanityValues playerHummanityData = new PlayerMonitorHummanityValues();
		string playerJsonPath = playersHummanityPath + playerID + ".json";
		
		if (FileExist(playerJsonPath))
		{
			JsonFileLoader<PlayerMonitorHummanityValues>.JsonLoadFile(playerJsonPath, playerHummanityData);
		}
		
		return playerHummanityData;
	}
	
	private void setHummanityS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {	
			string playerID = sender.GetId();
			
			PlayerMonitorHummanityValues playerHummanityData = loadPlayerData(playerID);
			
			int hummanity = playerHummanityData.getHummanity();
			
			GetRPCManager().SendRPC( "FalconMonitor", "setHummanityC", new Param1<int>(hummanity) );
       	 }
    }
	
	void setPlayerHummanity() {		
		GetRPCManager().SendRPC( "FalconMonitor", "setHummanityS", new Param1<string>("") );
	}
	
	private void setHummanityLevelS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {	
			string playerID = sender.GetId();
			
			PlayerMonitorHummanityValues playerHummanityData = loadPlayerData(playerID);
			
			string hummanityLevel = playerHummanityData.getHummanityLevel();
			
			GetRPCManager().SendRPC( "FalconMonitor", "setHummanityLevelC", new Param1<string>(hummanityLevel) );
       	 }
    }
	
	void setPlayerHummanityLevel() {		
		GetRPCManager().SendRPC( "FalconMonitor", "setHummanityLevelS", new Param1<string>("") );
	}
	
	private void setKilledPlayersS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {	
			string playerID = sender.GetId();
			
			PlayerMonitorHummanityValues playerHummanityData = loadPlayerData(playerID);
			
			string killedPlayers = playerHummanityData.getKilledPlayers().ToString();
			
			GetRPCManager().SendRPC( "FalconMonitor", "setKilledPlayersC", new Param1<string>(killedPlayers) );
       	 }
    }
	
	void setKilledPlayers() {		
		GetRPCManager().SendRPC( "FalconMonitor", "setKilledPlayersS", new Param1<string>("") );
	}
	
	private void setKilledZombiesS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {	
			string playerID = sender.GetId();
			
			PlayerMonitorHummanityValues playerHummanityData = loadPlayerData(playerID);
			
			string killedZombies = playerHummanityData.getKilledZeds().ToString();
			
			GetRPCManager().SendRPC( "FalconMonitor", "setKilledZombiesC", new Param1<string>(killedZombies) );
       	 }
    }
	
	void setKilledZombies() {		
		GetRPCManager().SendRPC( "FalconMonitor", "setKilledZombiesS", new Param1<string>("") );
	}
}