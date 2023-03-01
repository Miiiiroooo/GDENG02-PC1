// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GDENG02_PC1 : ModuleRules
{
	public GDENG02_PC1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "UMG", "Slate", "SlateCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { });
	}
}
