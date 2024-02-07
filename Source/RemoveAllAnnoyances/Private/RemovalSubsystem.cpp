// Copyright 2024 Jesse Hodgson.

#include "RemovalSubsystem.h"
#include "RemoveAllAnnoyances.h"
#include "RemoveAllAnnoyances_ConfigStruct.h"
#include "Kismet/GameplayStatics.h"
#include "FGItemPickup.h"

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

	UE_LOG(LogRemoveAllAnnoyances, Verbose, TEXT("RemoveAllAnnoyances Subsystem loaded successfully!"));

	FTimerHandle MemberTimerHandle;

	TSubclassOf<AActor> ActorClass;
	bool ShouldSpawnReward = false;

	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ARemovalSubsystem::RunRemover(ActorClass, ShouldSpawnReward), DeletionInterval, true, DeletionInterval);
}

void ARemovalSubsystem::RunRemover(TSubclassOf<AActor> ActorClass, bool ShouldSpawnReward)
{

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ActorClass, OutActors);

	FString ActorName = ActorClass->GetName();

	if(OutActors.Num() == 0)
	{
		UE_LOG(LogRemoveAllAnnoyances, Verbose, TEXT("Found none of type %s"), *ActorName);
	}
	else
	{
		if(ShouldSpawnReward)
		{
			// int i = 0; i < OutActors.Num(); i++)
			for (auto&  Actor: OutActors)
			{
				TSubclassOf<class AFGItemPickup> RewardBlueprint;

				static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/FactoryGame/Resource/Environment/Crystal/BP_Crystal_mk2.BP_Crystal_mk2'"));
				if (ItemBlueprint.Object){
					RewardBlueprint = (UClass*)ItemBlueprint.Object->GeneratedClass;
				}

				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;

				GetWorld()->SpawnActor<AFGItemPickup>(RewardBlueprint, Actor->GetActorLocation(), Actor->GetActorRotation(), SpawnParams);
			}
		}
		else
		{
			// int i = 0; i < OutActors.Num(); i++)
			for (auto&  Actor: OutActors)
			{
				Actor->Destroy();
			}
		}

	}
}