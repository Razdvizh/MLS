// Fill out your copyright notice in the Description page of Project Settings.


#include "StateAnimLayersBase.h"
#include "Animation/BlendSpace.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimExecutionContext.h"
#include "Animation/AnimNodeReference.h"
#include "Animations/MLSAnimInstanceBase.h"
#include "Components/SkeletalMeshComponent.h"

UStateAnimLayersBase::UStateAnimLayersBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	StandWalkJogRun(nullptr),
	Jump(nullptr),
	FallLoop(nullptr),
	Land(nullptr)
{
}

UMLSAnimInstanceBase* UStateAnimLayersBase::GetMainAnimInstance() const
{
	UAnimInstance* MainAnimInstance = GetOwningComponent()->GetAnimInstance();

	return Cast<UMLSAnimInstanceBase>(MainAnimInstance);
}

void UStateAnimLayersBase::OnInitialUpdateIdleAnim(const FAnimUpdateContext& Context, const FAnimNodeReference& Node)
{
	TBlendSpaceAsset Asset(StandWalkJogRun);

	SetAnimationAsset<TBlendSpaceAsset>(Node, &Asset);
}

void UStateAnimLayersBase::OnInitialUpdateJumpAnim(const FAnimUpdateContext& Context, const FAnimNodeReference& Node)
{
	TBlendSpaceAsset Asset(Jump);

	SetAnimationAsset<TBlendSpaceAsset>(Node, &Asset);
}

void UStateAnimLayersBase::OnInitialUpdateStandJumpAnim(const FAnimUpdateContext& Context, const FAnimNodeReference& Node)
{
	UAnimSequence* FirstSequence = Jump->GetBlendSample(/*From blend space editor*/2).Animation;
	TAnimSequenceAsset Asset(FirstSequence);
	
	SetAnimationAsset<TAnimSequenceAsset>(Node, &Asset);
}

void UStateAnimLayersBase::OnInitialUpdateFallLoopAnim(const FAnimUpdateContext& Context, const FAnimNodeReference& Node)
{
	TAnimSequenceAsset Asset(FallLoop);

	SetAnimationAsset<TAnimSequenceAsset>(Node, &Asset);
}

void UStateAnimLayersBase::OnInitialUpdateLandAnim(const FAnimUpdateContext& Context, const FAnimNodeReference& Node)
{
	TAnimSequenceAsset Asset(Land);

	SetAnimationAsset<TAnimSequenceAsset>(Node, &Asset);
}
