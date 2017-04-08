// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

//namespace UnrealBuildTool.Rules
//{
	public class SplineMover : ModuleRules
	{
		public SplineMover(TargetInfo Target)
		{
			PublicIncludePaths.AddRange(new string[]{ "SplineMover/Public", "SplineMover/Public/Struct" });
			PrivateIncludePaths.AddRange(new string[]{ "SplineMover/Private", "SplineMover/Private/Struct" });
            //PublicDependencyModuleNames.AddRange(new string[] { "Json", "JsonUtilities" });
			PrivateDependencyModuleNames.AddRange(new string[]{ "Core", "CoreUObject",  "Engine", "Json", "JsonUtilities" });
			DynamicallyLoadedModuleNames.AddRange(new string[]{});
		}
	}
//}