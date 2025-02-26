using UnrealBuildTool;

public class CPP_Lecture_020525 : ModuleRules
{
	public CPP_Lecture_020525(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput", 
			"Slate", 
			"SlateCore", 
			"UMG" 
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

	}
}
