// Fill out your copyright notice in the Description page of Project Settings.


#include "MLSCharacterBudgeted.h"
#include "SkeletalMeshComponentBudgeted.h"
#include "SignificanceManager.h"
#include "Engine/World.h"

constexpr float MaxDistanceSqr = 5000.f * 5000.f;

AMLSCharacterBudgeted::AMLSCharacterBudgeted(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USkeletalMeshComponentBudgeted>(MeshComponentName))
{
	USkeletalMeshComponentBudgeted* BudgetedMesh = StaticCast<USkeletalMeshComponentBudgeted*>(GetMesh());
	BudgetedMesh->SetAutoRegisterWithBudgetAllocator(true);
	BudgetedMesh->SetAutoCalculateSignificance(true);
}

void AMLSCharacterBudgeted::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UWorld* World = GetWorld();
	check(World);

	for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
	{
		if (APlayerController* PlayerController = It->Get())
		{
			FVector PlayerViewLocation;
			FRotator PlayerViewRotation;
			PlayerController->GetPlayerViewPoint(PlayerViewLocation, PlayerViewRotation);
			TArray<FTransform, TFixedAllocator<1>> Viewpoints;
			Viewpoints.Emplace(PlayerViewRotation, PlayerViewLocation, FVector::One());

			USignificanceManager* SignificanceManager = USignificanceManager::Get(World);
			if (ensure(SignificanceManager))
			{
				SignificanceManager->Update(Viewpoints);
			}
		}
	}
}

void AMLSCharacterBudgeted::BeginDestroy()
{
	if (UWorld* World = GetWorld(); ensure(World))
	{
		USignificanceManager* SignificanceManager = USignificanceManager::Get(World);
		if (ensure(SignificanceManager))
		{
			SignificanceManager->UnregisterObject(this);
		}
	}

	Super::BeginDestroy();
}

void AMLSCharacterBudgeted::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* World = GetWorld(); ensure(World))
	{
		USignificanceManager* SignificanceManager = USignificanceManager::Get(World);
		if (ensure(SignificanceManager))
		{
			auto CalculateSignificanceFunc = [this](USignificanceManager::FManagedObjectInfo* ObjectInfo, const FTransform& Viewpoint)
			{
				return CalculateSignificance(ObjectInfo, Viewpoint);
			};
			auto PostSignficanceFunc = [this](USignificanceManager::FManagedObjectInfo* ObjectInfo, float OldSignificance, float Significance, bool bFinal)
			{
				PostSignficanceFunction(ObjectInfo, OldSignificance, Significance, bFinal);
			};

			SignificanceManager->RegisterObject(
				this,
				TEXT("Character"),
				MoveTemp(CalculateSignificanceFunc),
				USignificanceManager::EPostSignificanceType::Sequential,
				MoveTemp(PostSignficanceFunc));
		}
	}
}

float AMLSCharacterBudgeted::CalculateSignificance(USignificanceManager::FManagedObjectInfo* ObjectInfo, const FTransform& Viewpoint)
{
	if (ObjectInfo && ObjectInfo->GetTag() == TEXT("Character"))
	{
		const float DistanceSqr = (GetActorLocation() - Viewpoint.GetLocation()).SizeSquared();
		const float Significance = FMath::Max(MaxDistanceSqr - DistanceSqr, 1.0f) / MaxDistanceSqr;

		return Significance;
	}

	return 0.0f;
}

void AMLSCharacterBudgeted::PostSignficanceFunction(USignificanceManager::FManagedObjectInfo* ObjectInfo, float OldSignificance, float Significance, bool bFinal)
{
	if (ObjectInfo && ObjectInfo->GetTag() == TEXT("Character"))
	{
		const float TickInterval = GetActorTickInterval();
		
		SetActorTickInterval(TickInterval * Significance);

		//Other desired optimizations here...
	}
}
