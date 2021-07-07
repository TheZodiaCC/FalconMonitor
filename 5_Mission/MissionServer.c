modded class MissionServer
{ 	
	ref PlayerMonitorBack MonitorBack;

    void MissionServer()
    {
		MonitorBack = new ref PlayerMonitorBack();
    }
}