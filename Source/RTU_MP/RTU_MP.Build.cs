// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RTU_MP : ModuleRules
{
	public RTU_MP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "SlateCore"});
	}
}
