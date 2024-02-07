// Copyright 2024 Jesse Hodgson

#include "RemoveAllAnnoyances.h"

#define LOCTEXT_NAMESPACE "FRemoveAllAnnoyancesModule"

void FRemoveAllAnnoyancesModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FRemoveAllAnnoyancesModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

DEFINE_LOG_CATEGORY(LogRemoveAllAnnoyances);

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FRemoveAllAnnoyancesModule, RemoveAllAnnoyances)