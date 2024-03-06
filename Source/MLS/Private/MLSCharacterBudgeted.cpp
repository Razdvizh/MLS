// Fill out your copyright notice in the Description page of Project Settings.


#include "MLSCharacterBudgeted.h"
#include "SkeletalMeshComponentBudgeted.h"

AMLSCharacterBudgeted::AMLSCharacterBudgeted(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USkeletalMeshComponentBudgeted>(MeshComponentName))
{
	USkeletalMeshComponentBudgeted* BudgetedMesh = StaticCast<USkeletalMeshComponentBudgeted*>(GetMesh());
	BudgetedMesh->SetAutoRegisterWithBudgetAllocator(true);
	BudgetedMesh->SetAutoCalculateSignificance(true);
}
