// Copyright 2024 - 2025 Jesse Hodgson.

#include "RemovalSubsystem.h"
#include "FGHealthComponent.h"
#include "RemoveAllAnnoyances.h"
#include "RemoveAllAnnoyances_ConfigStruct.h"
#include "Kismet/GameplayStatics.h"
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
		ModConfig = FRemoveAllAnnoyances_ConfigStruct::GetActiveConfig(GetWorld());
	}

	#if WITH_SERVER_CODE // Server-side code

		bShouldRemoveMantaRays         = ModConfig.bShouldRemoveMantaRays;
		bShouldRemoveDeposits          = ModConfig.bShouldRemoveDeposits;
		bShouldRemoveStingers          = ModConfig.bShouldRemoveStingers;
		bShouldRemoveGasRocks          = ModConfig.bShouldRemoveGasRocks;
		bShouldRemoveHogs              = ModConfig.bShouldRemoveHogs;
		bShouldRemoveCrabs             = ModConfig.bShouldRemoveCrabs;
		bShouldRemoveSpitters          = ModConfig.bShouldRemoveSpitters;
		bShouldRemoveDestructibleRocks = ModConfig.bShouldRemoveDestructibleRocks;
		bShouldRemoveBeans             = ModConfig.bShouldRemoveBeans;
		bShouldRemoveBirds             = ModConfig.bShouldRemoveBirds;
		bShouldRemoveDoggos            = ModConfig.bShouldRemoveDoggos;
		bShouldRemoveSporePlants       = ModConfig.bShouldRemoveSporePlants;

		bHideScriptReminder            = ModConfig.SubsystemSettingsSection.bHideScriptReminder;
		RemovalInterval                = ModConfig.SubsystemSettingsSection.RemovalInterval;

	#endif // Client-side code

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
	UE_LOG(LogRemoveAllAnnoyances, Display, TEXT("Build Date: %s %s"), ANSI_TO_TCHAR(__DATE__), ANSI_TO_TCHAR(__TIME__));

	#if WITH_SERVER_CODE // Server-side code

		TArray<TSubclassOf<AActor>> AnnoyanceList;
		TArray<TSubclassOf<AFGCharacterBase>> CharacterAnnoyanceList;

		// Add all annoyances to list
		if(bShouldRemoveMantaRays)
		{
			AnnoyanceList.Add(MantaRay);

			UE_LOG(LogRemoveAllAnnoyances, Verbose, TEXT("Added MantaRays to the list of annoyances to remove!"));
		}
		if (bShouldRemoveDeposits)
		{
			AnnoyanceList.Add(Deposit);

			UE_LOG(LogRemoveAllAnnoyances, Verbose, TEXT("Added Deposits to the list of annoyances to remove!"));
		}
		if (bShouldRemoveStingers)
		{
			CharacterAnnoyanceList.Add(EliteStinger);
			CharacterAnnoyanceList.Add(AlphaStinger);
			CharacterAnnoyanceList.Add(ChildStinger);

			UE_LOG(LogRemoveAllAnnoyances, Verbose, TEXT("Added Stingers to the list of annoyances to remove!"));
		}
		if (bShouldRemoveGasRocks)
		{
			AnnoyanceList.Add(GasPillar1);
			AnnoyanceList.Add(GasPillar2);
			AnnoyanceList.Add(GasPillar3);
			AnnoyanceList.Add(GasPillar4);
			AnnoyanceList.Add(GasPillar5);

			UE_LOG(LogRemoveAllAnnoyances, Verbose, TEXT("Added Gas Rocks to the list of annoyances to remove!"));
		}
		if (bShouldRemoveHogs)
		{
			CharacterAnnoyanceList.Add(AlphaHog);
			CharacterAnnoyanceList.Add(CliffHog);
			CharacterAnnoyanceList.Add(NuclearHog);
			CharacterAnnoyanceList.Add(Hog);

			UE_LOG(LogRemoveAllAnnoyances, Verbose, TEXT("Added Hogs to the list of annoyances to remove!"));
		}
		if (bShouldRemoveCrabs)
		{
			AnnoyanceList.Add(CrabHatcher);

			UE_LOG(LogRemoveAllAnnoyances, Verbose, TEXT("Added Crabs to the list of annoyances to remove!"));
		}
		if (bShouldRemoveSpitters)
		{
			CharacterAnnoyanceList.Add(AquaticAlphaSpitter);
			CharacterAnnoyanceList.Add(AquaticSpitter);
			CharacterAnnoyanceList.Add(DesertAlphaSpitter);
			CharacterAnnoyanceList.Add(DesertSpitter);
			CharacterAnnoyanceList.Add(RedForestAlphaSpitter);
			CharacterAnnoyanceList.Add(RedForestSpitter);
			CharacterAnnoyanceList.Add(AlphaForestSpitter);
			CharacterAnnoyanceList.Add(ForestSpitter);

			UE_LOG(LogRemoveAllAnnoyances, Verbose, TEXT("Added Spitters to the list of annoyances to remove!"));
		}
		if (bShouldRemoveDestructibleRocks)
		{
			AnnoyanceList.Add(DestructibleRock1);
			AnnoyanceList.Add(DestructibleRock2);
			AnnoyanceList.Add(DestructibleRockFlat);

			UE_LOG(LogRemoveAllAnnoyances, Verbose, TEXT("Added Destructible Rocks to the list of annoyances to remove!"));
		}
		if (bShouldRemoveBeans)
		{
			CharacterAnnoyanceList.Add(SpaceGiraffe);

			UE_LOG(LogRemoveAllAnnoyances, Verbose, TEXT("Added Beans to the list of annoyances to remove!"));
		}
		if (bShouldRemoveBirds)
		{
			CharacterAnnoyanceList.Add(Bird);

			UE_LOG(LogRemoveAllAnnoyances, Verbose, TEXT("Added Birds to the list of annoyances to remove!"));
		}
		if (bShouldRemoveDoggos)
		{
			CharacterAnnoyanceList.Add(Doggo);

			UE_LOG(LogRemoveAllAnnoyances, Verbose, TEXT("Added Doggos to the list of annoyances to remove!"));
		}
		if (bShouldRemoveSporePlants)
		{
			AnnoyanceList.Add(SporeFlower);

			UE_LOG(LogRemoveAllAnnoyances, Verbose, TEXT("Added Spore Plants to the list of annoyances to remove!"));
		}

		if (AnnoyanceList.Num() == 0 && CharacterAnnoyanceList.Num() == 0)
		{
			UE_LOG(LogRemoveAllAnnoyances, Verbose, TEXT("No annoyances selected!"));

			if (!bHideScriptReminder && this->GetWorld()->GetNetMode() != NM_DedicatedServer){
				Cast<AFGPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetRemoteCallObjectOfClass<USMLRemoteCallObject>()->SendChatMessage("Remove All Annoyances: No annoyances selected! Please go to the Main Menu and select \"Mods\" from the bottom of the menu and choose \"Remove All Annoyances\". Then scroll down and select some annoyances to remove! If you'd prefer to just disable this message, you can do that from the config as well.", ErrorMessageColor);
			}
		}
		else
		{
			GetWorldTimerManager().SetTimer(MemberTimerHandle, [this, AnnoyanceList, CharacterAnnoyanceList]{RunRemover(AnnoyanceList, CharacterAnnoyanceList);}, RemovalInterval, true, RemovalInterval);
		}

	#endif // Client-side code
	// Nothing needs to be done on client
}

#if WITH_SERVER_CODE // Server-side code

	void ARemovalSubsystem::EndPlay(const EEndPlayReason::Type EndPlayReason)
	{
		Super::EndPlay(EEndPlayReason::LevelTransition);

		GetWorldTimerManager().ClearTimer(MemberTimerHandle);
	}

	void ARemovalSubsystem::RunRemover(TArray<TSubclassOf<AActor>> AnnoyanceList, TArray<TSubclassOf<AFGCharacterBase>> CharacterAnnoyanceList) const
	{
		TArray<AActor*> OutActors;

		for (auto&  CurrentActorType : AnnoyanceList)
		{
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), CurrentActorType, OutActors);

			for (auto&  Actor: OutActors)
			{
				Actor->Destroy();
			}
		}
		// Kill creatures before destroying them
		for(auto& CurrentCharacterType : CharacterAnnoyanceList)
		{
			TArray<AFGCharacterBase*> OutCharacters;
			TArray<AActor*> OutActorCharacters;

			UGameplayStatics::GetAllActorsOfClass(GetWorld(), CurrentCharacterType, OutActorCharacters);

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

#endif