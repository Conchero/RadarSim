// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RadarSim : ModuleRules
{
    public RadarSim(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "Kismet",
        //    "UnrealEd",
        //    "Slate",
        //"SlateCore",
        //"EditorFramework",
        //"MainFrame",
        //"PropertyEditor",
                "AIModule",         
            "NavigationSystem"
        });
    }
}
