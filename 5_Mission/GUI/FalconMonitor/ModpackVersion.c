class ModpackVersion
{
	private Widget widgetRoot;
	
	private bool isMarkOn = false;
	
	//Constructor
	void ModpackVersion() {		
		widgetRoot = GetGame().GetWorkspace().CreateWidgets("FalconMonitor/GUI/Layouts/ModpackVersion.layout");
		widgetRoot.Show(false);
	}
	
	//Deconstructor
	void ~ModpackVersion() {
        if ( widgetRoot )
        	widgetRoot.Unlink();
    }
	
	bool getIsMarkOn() {
		return isMarkOn;
	}
	
	void setIsMarkOn(bool value) {
		isMarkOn = value;
	}
	
	void showMark() {
		if (!isMarkOn)
		{
			widgetRoot.Show(true);
			setIsMarkOn(true);
		}
	}
}
	
	
