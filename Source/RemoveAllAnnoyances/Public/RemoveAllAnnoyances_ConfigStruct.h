#pragma once
#include "CoreMinimal.h"
#include "Configuration/ConfigManager.h"
#include "Engine/Engine.h"
#include "RemoveAllAnnoyances_ConfigStruct.generated.h"

struct FRemoveAllAnnoyances_ConfigStruct_SubsystemSettingsSection;

USTRUCT(BlueprintType)
struct FRemoveAllAnnoyances_ConfigStruct_SubsystemSettingsSection {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite)
    float RemovalInterval{};

    UPROPERTY(BlueprintReadWrite)
    bool bHideScriptReminder{};
};

/* Struct generated from Mod Configuration Asset '/RemoveAllAnnoyances/RemoveAllAnnoyances_Config' */
USTRUCT(BlueprintType)
struct FRemoveAllAnnoyances_ConfigStruct {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite)
    bool bShouldRemoveMantaRays{};

    UPROPERTY(BlueprintReadWrite)
    bool bShouldRemoveDeposits{};

    UPROPERTY(BlueprintReadWrite)
    bool bShouldRemoveStingers{};

    UPROPERTY(BlueprintReadWrite)
    bool bShouldRemoveGasRocks{};

    UPROPERTY(BlueprintReadWrite)
    bool bShouldRemoveHogs{};

    UPROPERTY(BlueprintReadWrite)
    bool bShouldRemoveCrabs{};

    UPROPERTY(BlueprintReadWrite)
    bool bShouldRemoveSpitters{};

    UPROPERTY(BlueprintReadWrite)
    bool bShouldRemoveDestructibleRocks{};

    UPROPERTY(BlueprintReadWrite)
    bool bShouldRemoveBeans{};

    UPROPERTY(BlueprintReadWrite)
    bool bShouldRemoveBirds{};

    UPROPERTY(BlueprintReadWrite)
    bool bShouldRemoveDoggos{};

    UPROPERTY(BlueprintReadWrite)
    bool bShouldRemoveSporePlants{};

    UPROPERTY(BlueprintReadWrite)
    FRemoveAllAnnoyances_ConfigStruct_SubsystemSettingsSection SubsystemSettingsSection{};

    /* Retrieves active configuration value and returns object of this struct containing it */
    static FRemoveAllAnnoyances_ConfigStruct GetActiveConfig(UObject* WorldContext) {
        FRemoveAllAnnoyances_ConfigStruct ConfigStruct{};
        FConfigId ConfigId{"RemoveAllAnnoyances", ""};
        if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull)) {
            UConfigManager* ConfigManager = World->GetGameInstance()->GetSubsystem<UConfigManager>();
            ConfigManager->FillConfigurationStruct(ConfigId, FDynamicStructInfo{FRemoveAllAnnoyances_ConfigStruct::StaticStruct(), &ConfigStruct});
        }
        return ConfigStruct;
    }
};

