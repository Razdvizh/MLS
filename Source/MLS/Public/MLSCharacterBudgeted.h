// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SignificanceManager.h"
#include "MLSCharacterBudgeted.generated.h"

UCLASS()
class MLS_API AMLSCharacterBudgeted final : public ACharacter
{
	GENERATED_BODY()
	
public:
	AMLSCharacterBudgeted(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;

	virtual void BeginDestroy() override;

protected:
	virtual void BeginPlay() override;

private:
	float CalculateSignificance(USignificanceManager::FManagedObjectInfo* ObjectInfo, const FTransform& Viewpoint);

	void PostSignficanceFunction(USignificanceManager::FManagedObjectInfo* ObjectInfo, float OldSignificance, float Significance, bool bFinal);

};
