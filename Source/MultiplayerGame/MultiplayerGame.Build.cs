// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MultiplayerGame : ModuleRules
{
	public MultiplayerGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"OnlineSubsystem",
			"OnlineSubsystemSteam"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"MultiplayerGame",
			"MultiplayerGame/Variant_Platforming",
			"MultiplayerGame/Variant_Platforming/Animation",
			"MultiplayerGame/Variant_Combat",
			"MultiplayerGame/Variant_Combat/AI",
			"MultiplayerGame/Variant_Combat/Animation",
			"MultiplayerGame/Variant_Combat/Gameplay",
			"MultiplayerGame/Variant_Combat/Interfaces",
			"MultiplayerGame/Variant_Combat/UI",
			"MultiplayerGame/Variant_SideScrolling",
			"MultiplayerGame/Variant_SideScrolling/AI",
			"MultiplayerGame/Variant_SideScrolling/Gameplay",
			"MultiplayerGame/Variant_SideScrolling/Interfaces",
			"MultiplayerGame/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
