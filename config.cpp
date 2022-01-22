class CfgPatches
{
	class FalconMonitor
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={"JM_CF_Scripts", "DZ_Data"};
	};
};

class CfgMods
{
	class FalconMonitor
	{
	    dir = FalconMonitor
	    picture = "";
	    action = "";
	    hideName = 1;
	    hidePicture = 1;
	    name = FalconMonitor
	    credits = "";
	    author = "zNitche";
	    authorID = "0";
	    version = "1.0";
	    extra = 0;
	    type = "mod";

	    dependencies[] = { "Mission" };

		class defs
		{
			class missionScriptModule
			{
				value = "";
				files[] = {"FalconMonitor/5_Mission"};
			};
		};
	};
};
