class PlayerHumanityPackage
{
	int humanity;
	string humanityLevel;
	string killedPlayers;
	string killedZombies;
	
	void PlayerHumanityPackage(int humanity, string humanityLevel, string killedPlayers, string killedZombies) 
	{
		this.humanity = humanity;
		this.humanityLevel = humanityLevel;
		this.killedPlayers = killedPlayers;
		this.killedZombies = killedZombies;
	}
}