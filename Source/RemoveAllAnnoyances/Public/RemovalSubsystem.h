// Copyright 2024 - 2025 Jesse Hodgson.

#pragma once

#include "CoreMinimal.h"
#include "FGCharacterBase.h"
#include "Subsystem/ModSubsystem.h"
#include "RemoveAllAnnoyances_ConfigStruct.h"
#include "RemovalSubsystem.generated.h"

UCLASS()
class REMOVEALLANNOYANCES_API ARemovalSubsystem : public AModSubsystem
{
	GENERATED_BODY()

public:

	ARemovalSubsystem();

	FRemoveAllAnnoyances_ConfigStruct ModConfig;

	bool bShouldRemoveArtifacts;
	bool bShouldRemoveMantaRays;
	bool bShouldRemoveDeposits;
	bool bShouldRemoveStingers;
	bool bShouldRemoveGasRocks;
	bool bShouldRemoveHogs;
	bool bShouldRemoveCrabs;
	bool bShouldRemoveSpitters;
	bool bShouldRemoveDestructibleRocks;
	bool bShouldRemoveBeans;
	bool bShouldRemoveBirds;
	bool bShouldRemoveDoggos;
	bool bShouldRemoveSporePlants;

	bool bHideScriptReminder;
	float RemovalInterval;

	// Timer for removal function
	FTimerHandle MemberTimerHandle;

// Error Message Color

	UPROPERTY(EditAnywhere)
	FLinearColor ErrorMessageColor = FLinearColor::Red;

// Blueprint Classes for annoyances

	// Manta Ray
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> MantaRay;

	// Deposits
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Deposit;

	// Stinger Subclasses

		// Elite Stinger
		UPROPERTY(EditAnywhere)
		TSubclassOf<AFGCharacterBase> EliteStinger;

		// Alpha Stinger
		UPROPERTY(EditAnywhere)
		TSubclassOf<AFGCharacterBase> AlphaStinger;

		// Child Stinger
		UPROPERTY(EditAnywhere)
		TSubclassOf<AFGCharacterBase> ChildStinger;

	// Gas Pillar Subclasses

		// Gas Pillar 1
		UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> GasPillar1;

		// Gas Pillar 2
		UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> GasPillar2;

		// Gas Pillar 3
		UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> GasPillar3;

		// Gas Pillar 4
		UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> GasPillar4;

		// Gas Pillar 5
		UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> GasPillar5;

	// Hog Subclasses

		// Alpha Hog
		UPROPERTY(EditAnywhere)
		TSubclassOf<AFGCharacterBase> AlphaHog;

		// Cliff Hog
		UPROPERTY(EditAnywhere)
		TSubclassOf<AFGCharacterBase> CliffHog;

		// Nuclear Hog
		UPROPERTY(EditAnywhere)
		TSubclassOf<AFGCharacterBase> NuclearHog;

		// Hog
		UPROPERTY(EditAnywhere)
		TSubclassOf<AFGCharacterBase> Hog;

	// Crab Hatcher
	UPROPERTY(EditAnywhere)
    TSubclassOf<AActor> CrabHatcher;

    // Plasma Spitter Subclasses

		// Aquatic Alpha Spitter
		UPROPERTY(EditAnywhere)
		TSubclassOf<AFGCharacterBase> AquaticAlphaSpitter;

		// Aquatic Spitter
		UPROPERTY(EditAnywhere)
		TSubclassOf<AFGCharacterBase> AquaticSpitter;

	    // Desert Alpha Spitter
		UPROPERTY(EditAnywhere)
		TSubclassOf<AFGCharacterBase> DesertAlphaSpitter;

		// Desert Spitter
		UPROPERTY(EditAnywhere)
		TSubclassOf<AFGCharacterBase> DesertSpitter;

	    // Red Forest Alpha Spitter
		UPROPERTY(EditAnywhere)
		TSubclassOf<AFGCharacterBase> RedForestAlphaSpitter;

		// Red Forest Spitter
		UPROPERTY(EditAnywhere)
		TSubclassOf<AFGCharacterBase> RedForestSpitter;

	    // Alpha Forest Spitter
		UPROPERTY(EditAnywhere)
		TSubclassOf<AFGCharacterBase> AlphaForestSpitter;

		// Forest Spitter
		UPROPERTY(EditAnywhere)
		TSubclassOf<AFGCharacterBase> ForestSpitter;

	// Destructible Rock Subclasses

		// Destructible Rock 1
		UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> DestructibleRock1;

		// Destructible Rock 2
		UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> DestructibleRock2;

		// Destructible Rock Flat
		UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> DestructibleRockFlat;

	// Space Giraffe
	UPROPERTY(EditAnywhere)
	TSubclassOf<AFGCharacterBase> SpaceGiraffe;

	// Non-Flying Bird
	UPROPERTY(EditAnywhere)
	TSubclassOf<AFGCharacterBase> Bird;

	// Lizard Doggo
	UPROPERTY(EditAnywhere)
	TSubclassOf<AFGCharacterBase> Doggo;

	// Spore Flower
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> SporeFlower;

	// Remove the annoyances the user has selected
	UFUNCTION()
	void RunRemover(TArray<TSubclassOf<AActor>> AnnoyanceList, TArray<TSubclassOf<AFGCharacterBase>> CharacterAnnoyanceList) const;

protected:

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
