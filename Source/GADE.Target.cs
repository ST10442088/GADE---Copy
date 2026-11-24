// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class GADETarget : TargetRules
{
	public GADETarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
        BuildEnvironment = TargetBuildEnvironment.Shared;
        ExtraModuleNames.Add("GADE");
	}
}
