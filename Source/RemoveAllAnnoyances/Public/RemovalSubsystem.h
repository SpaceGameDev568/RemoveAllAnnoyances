// Copyright 2024 Jesse Hodgson.

#pragma once

#include "CoreMinimal.h"
#include "Subsystem/ModSubsystem.h"
#include "RemoveAllAnnoyances_ConfigStruct.h"
#include "RemovalSubsystem.generated.h"

UCLASS()
class REMOVEALLANNOYANCES_API ARemovalSubsystem : public AModSubsystem
{
	GENERATED_BODY()

public:

	ARemovalSubsystem();

	FRemoveAllAnnoyances_ConfigStruct myConfig;

	bool RemoveArtifacts;
	bool RemoveMantaRays;
	bool RemoveDeposits;
	bool RemoveStingers;
	bool RemoveGasRocks;
	bool RemoveHogs;
	bool RemoveCrabs;
	bool RemoveSpitters;
	bool RemoveDestructibleRocks;
	bool RemoveBeans;

	float DeletionInterval;

	UFUNCTION()
	void RunRemover(TSubclassOf<AActor> ActorClass, bool ShouldSpawnReward);

protected:

	virtual void BeginPlay() override;
	
};
