// Copyright 2024 Jesse Hodgson

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FRemoveAllAnnoyancesModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

DECLARE_LOG_CATEGORY_EXTERN(LogRemoveAllAnnoyances, Verbose, All);