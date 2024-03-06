// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MLS : ModuleRules
{
	public MLS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", 
			"AnimGraphRuntime", "AnimationBudgetAllocator" });
	}
}
