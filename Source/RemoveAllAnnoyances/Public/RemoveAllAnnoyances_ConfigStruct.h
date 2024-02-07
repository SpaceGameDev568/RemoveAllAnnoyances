#pragma once
#include "CoreMinimal.h"
#include "Configuration/ConfigManager.h"
#include "Engine/Engine.h"
#include "RemoveAllAnnoyances_ConfigStruct.generated.h"

/* Struct generated from Mod Configuration Asset '/RemoveAllAnnoyances/RemoveAllAnnoyances_Config' */
USTRUCT(BlueprintType)
struct FRemoveAllAnnoyances_ConfigStruct {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite)
    bool RemoveArtifacts{};

    UPROPERTY(BlueprintReadWrite)
    bool RemoveMantaRays{};

    UPROPERTY(BlueprintReadWrite)
    bool RemoveDeposits{};

    UPROPERTY(BlueprintReadWrite)
    bool RemoveStingers{};

    UPROPERTY(BlueprintReadWrite)
    bool RemoveGasRocks{};

    UPROPERTY(BlueprintReadWrite)
    bool RemoveHogs{};

    UPROPERTY(BlueprintReadWrite)
    bool RemoveCrabs{};

    UPROPERTY(BlueprintReadWrite)
    bool RemoveSpitters{};

    UPROPERTY(BlueprintReadWrite)
    bool RemoveDestructibleRocks{};

    UPROPERTY(BlueprintReadWrite)
    bool RemoveBeans{};

    UPROPERTY(BlueprintReadWrite)
    float DeletionInterval{};

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

