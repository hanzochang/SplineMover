// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SplineMoverPrivatePCH.h"

#define LOCTEXT_NAMESPACE "FSplineMover"

void FSplineMover::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
}


void FSplineMover::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE( FSplineMover, SplineMover )