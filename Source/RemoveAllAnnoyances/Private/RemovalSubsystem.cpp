// Copyright 2024 Jesse Hodgson.

#include "RemovalSubsystem.h"

#include "FGHealthComponent.h"
#include "RemoveAllAnnoyances.h"
#include "RemoveAllAnnoyances_ConfigStruct.h"
#include "Kismet/GameplayStatics.h"
#include "FGItemPickup.h"
#include "ModLoading/ModLoadingLibrary.h"
#include "SessionSettings/SessionSettingsSubsystem.h"
#include "SML/Public/Player/SMLRemoteCallObject.h"
#include "FGPlayerController.h"

ARemovalSubsystem::ARemovalSubsystem()
{
	if(WITH_EDITOR)
	{
		UE_LOG(LogRemoveAllAnnoyances, Verbose, TEXT("Shipping env not detected, avoiding crash"));
	}
	else
	{
		myConfig = FRemoveAllAnnoyances_ConfigStruct::GetActiveConfig(GetWorld());
	}

	RemoveArtifacts = myConfig.RemoveArtifacts;
	RemoveMantaRays = myConfig.RemoveMantaRays;
	RemoveDeposits = myConfig.RemoveMantaRays;
	RemoveStingers = myConfig.RemoveStingers;
	RemoveGasRocks = myConfig.RemoveGasRocks;
	RemoveHogs = myConfig.RemoveHogs;
	RemoveCrabs = myConfig.RemoveCrabs;
	RemoveSpitters = myConfig.RemoveSpitters;
	RemoveDestructibleRocks = myConfig.RemoveDestructibleRocks;
	RemoveBeans = myConfig.RemoveBeans;

	DeletionInterval = myConfig.DeletionInterval;
}

void ARemovalSubsystem::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogRemoveAllAnnoyances, Verbose, TEXT("Loaded RemoveAllAnnoyances subsystem successfully!"));

	FModInfo ModInfo;

	const UGameInstance* GameInstance = GetGameInstance();

	UModLoadingLibrary *ModLoadingLibrary = GameInstance->GetSubsystem<UModLoadingLibrary>();

	ModLoadingLibrary->GetLoadedModInfo("RemoveAllAnnoyances", ModInfo);

	// Log the name and version of the mod
	UE_LOG(LogRemoveAllAnnoyances, Verbose, TEXT("%s"), *ModInfo.FriendlyName.Append(", " + ModInfo.Version.ToString()));

	TArray<TSubclassOf<AActor>> AnnoyanceList;
	TArray<TSubclassOf<AFGCharacterBase>> CharacterAnnoyanceList;

	// Add all annoyances to list
	if (RemoveArtifacts)
	{
		AnnoyanceList.Add(Wat1);

		UE_LOG(LogRemoveAllAnnoyances, Warning, TEXT("Added Artifacts to the list of annoyances to remove!"));
	}
	if(RemoveMantaRays)
	{
		AnnoyanceList.Add(MantaRay);

		UE_LOG(LogRemoveAllAnnoyances, Warning, TEXT("Added MantaRays to the list of annoyances to remove!"));
	}
	if (RemoveDeposits)
	{
		AnnoyanceList.Add(Deposit);

		UE_LOG(LogRemoveAllAnnoyances, Warning, TEXT("Added Deposits to the list of annoyances to remove!"));
	}
	if (RemoveStingers)
	{
		CharacterAnnoyanceList.Add(EliteStinger);
		CharacterAnnoyanceList.Add(AlphaStinger);
		CharacterAnnoyanceList.Add(ChildStinger);

		UE_LOG(LogRemoveAllAnnoyances, Warning, TEXT("Added Stingers to the list of annoyances to remove!"));
	}
	if (RemoveGasRocks)
	{
		AnnoyanceList.Add(SporeFlower);
		AnnoyanceList.Add(GasPillar1);
		AnnoyanceList.Add(GasPillar2);
		AnnoyanceList.Add(GasPillar3);
		AnnoyanceList.Add(GasPillar4);
		AnnoyanceList.Add(GasPillar5);

		UE_LOG(LogRemoveAllAnnoyances, Warning, TEXT("Added Gas Rocks to the list of annoyances to remove!"));
	}
	if (RemoveHogs)
	{
		CharacterAnnoyanceList.Add(AlphaHog);
		CharacterAnnoyanceList.Add(CliffHog);
		CharacterAnnoyanceList.Add(NuclearHog);
		CharacterAnnoyanceList.Add(Hog);

		UE_LOG(LogRemoveAllAnnoyances, Warning, TEXT("Added Hogs to the list of annoyances to remove!"));
	}
	if (RemoveCrabs)
	{
		AnnoyanceList.Add(CrabHatcher);

		UE_LOG(LogRemoveAllAnnoyances, Warning, TEXT("Added Crabs to the list of annoyances to remove!"));
	}
	if (RemoveSpitters)
	{
		CharacterAnnoyanceList.Add(AquaticAlphaSpitter);
		CharacterAnnoyanceList.Add(AquaticSpitter);
		CharacterAnnoyanceList.Add(DesertAlphaSpitter);
		CharacterAnnoyanceList.Add(DesertSpitter);
		CharacterAnnoyanceList.Add(RedForestAlphaSpitter);
		CharacterAnnoyanceList.Add(RedForestSpitter);
		CharacterAnnoyanceList.Add(AlphaForestSpitter);
		CharacterAnnoyanceList.Add(ForestSpitter);

		UE_LOG(LogRemoveAllAnnoyances, Warning, TEXT("Added Spitters to the list of annoyances to remove!"));
	}
	if (RemoveDestructibleRocks)
	{
		AnnoyanceList.Add(DestructibleRock1);
		AnnoyanceList.Add(DestructibleRock2);
		AnnoyanceList.Add(DestructibleRockFlat);

		UE_LOG(LogRemoveAllAnnoyances, Warning, TEXT("Added Destructible Rocks to the list of annoyances to remove!"));
	}
	if (RemoveBeans)
	{
		CharacterAnnoyanceList.Add(SpaceGiraffe);

		UE_LOG(LogRemoveAllAnnoyances, Warning, TEXT("Added Beans to the list of annoyances to remove!"));
	}

	if (AnnoyanceList.Num() == 0 && CharacterAnnoyanceList.Num() == 0)
	{
		UE_LOG(LogRemoveAllAnnoyances, Verbose, TEXT("No annoyances selected!"));

		APlayerController* PlayerControllerRef = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		AFGPlayerController* VarPlayerController = Cast<AFGPlayerController>(PlayerControllerRef);

		USMLRemoteCallObject *SMLRemoteCallObject = VarPlayerController->GetRemoteCallObjectOfClass<USMLRemoteCallObject>();

		SMLRemoteCallObject->SendChatMessage("Remove All Annoyances: No annoyances selected! Please go to the Main Menu and select \"Mods\" from the bottom of the menu and choose \"Remove All Annoyances\". Then scroll down and select some annoyances to remove!", ErrorMessageColor);
	}
	else
	{
		FTimerHandle MemberTimerHandle;

		GetWorldTimerManager().SetTimer(MemberTimerHandle, [this, AnnoyanceList, CharacterAnnoyanceList](){RunRemover(AnnoyanceList, CharacterAnnoyanceList);}, DeletionInterval, true, DeletionInterval);
	}
}

void ARemovalSubsystem::RunRemover(TArray<TSubclassOf<AActor>> AnnoyanceList, TArray<TSubclassOf<AFGCharacterBase>> CharacterAnnoyanceList)
{
	TArray<AActor*> OutActors;

	for (auto&  CurrentActorType : AnnoyanceList)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), CurrentActorType, OutActors);

		if(OutActors.Num() == 0)
		{
			UE_LOG(LogRemoveAllAnnoyances, Verbose, TEXT("Found none of type %s"), *CurrentActorType->GetName());
		}
		else
		{
			UE_LOG(LogRemoveAllAnnoyances, Verbose, TEXT("Found %d of type %s"), OutActors.Num(), *CurrentActorType->GetName());

			for (auto&  Actor: OutActors)
			{
				// Spawn reward for alien artifacts
				if(CurrentActorType == Wat1)
				{
					FActorSpawnParameters SpawnParams;
					SpawnParams.Owner = this;

					GetWorld()->SpawnActor<AFGItemPickup>(Reward, Actor->GetActorLocation(), Actor->GetActorRotation(), SpawnParams);
				}
				Actor->Destroy();
			}
		}
	}
	// Kill creatures before destroying them
	for(auto& CurrentCharacterType : CharacterAnnoyanceList)
	{

		TArray<AFGCharacterBase*> OutCharacters;
		TArray<AActor*> OutActorCharacters;

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), CurrentCharacterType, OutActorCharacters);

		if(OutActorCharacters.Num() == 0)
		{
			UE_LOG(LogRemoveAllAnnoyances, Verbose, TEXT("Found none of type %s"), *CurrentCharacterType->GetName());
		}
		else
		{
			UE_LOG(LogRemoveAllAnnoyances, Verbose, TEXT("Found %d of type %s"), OutCharacters.Num(), *CurrentCharacterType->GetName());

			for (auto& Character : OutActorCharacters)
			{
				AFGCharacterBase* CastedCharacter = Cast<AFGCharacterBase>(Character);

				CastedCharacter->GetHealthComponent()->Kill();

				if (IsValid(Character))
				{
					Character->Destroy();
				}
			}
		}
	}
}