// Fill out your copyright notice in the Description page of Project Settings.


#include "StateAnimLayersBase.h"
#include "Animation/BlendSpace.h"
#include "Animation/AnimExecutionContext.h"
#include "Animation/AnimNodeReference.h"
#include "Animations/MLSAnimInstanceBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "BlendSpacePlayerLibrary.h"

UStateAnimLayersBase::UStateAnimLayersBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	StandWalkJogRun(nullptr)
{
}

UMLSAnimInstanceBase* UStateAnimLayersBase::GetMainAnimInstance() const
{
	UAnimInstance* MainAnimInstance = GetOwningComponent()->GetAnimInstance();

	return Cast<UMLSAnimInstanceBase>(MainAnimInstance);
}

void UStateAnimLayersBase::OnInitialUpdateIdleAnim(const FAnimUpdateContext& Context, const FAnimNodeReference& Node)
{
	EAnimNodeReferenceConversionResult ConversionResult;
	FBlendSpacePlayerReference BlendSpacePlayer = UBlendSpacePlayerLibrary::ConvertToBlendSpacePlayer(Node, ConversionResult);

	if (ConversionResult == EAnimNodeReferenceConversionResult::Succeeded)
	{
		UBlendSpacePlayerLibrary::SetBlendSpace(BlendSpacePlayer, StandWalkJogRun);
	}
}
