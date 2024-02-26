// Fill out your copyright notice in the Description page of Project Settings.


#include "StateAnimLayersBase.h"
#include "Animation/BlendSpace.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimExecutionContext.h"
#include "Animation/AnimNodeReference.h"
#include "Animations/MLSAnimInstanceBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "BlendSpacePlayerLibrary.h"
#include "SequencePlayerLibrary.h"

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
	SetBlendSpace(Node, StandWalkJogRun);
}

void UStateAnimLayersBase::OnInitialUpdateJumpAnim(const FAnimUpdateContext& Context, const FAnimNodeReference& Node)
{
	SetBlendSpace(Node, Jump);
}

void UStateAnimLayersBase::OnInitialUpdateFallLoopAnim(const FAnimUpdateContext& Context, const FAnimNodeReference& Node)
{
	SetAnimSequence(Node, FallLoop);
}

void UStateAnimLayersBase::OnInitialUpdateLandAnim(const FAnimUpdateContext& Context, const FAnimNodeReference& Node)
{
	SetAnimSequence(Node, Land);
}

bool UStateAnimLayersBase::SetBlendSpace(const FAnimNodeReference& Node, UBlendSpace* BlendSpace) const
{
	EAnimNodeReferenceConversionResult ConversionResult;
	FBlendSpacePlayerReference BlendSpacePlayer = UBlendSpacePlayerLibrary::ConvertToBlendSpacePlayer(Node, ConversionResult);

	if (ConversionResult == EAnimNodeReferenceConversionResult::Succeeded)
	{
		UBlendSpacePlayerLibrary::SetBlendSpace(BlendSpacePlayer, BlendSpace);
		return true;
	}

	return false;
}

bool UStateAnimLayersBase::SetAnimSequence(const FAnimNodeReference& Node, UAnimSequence* Sequence) const
{
	EAnimNodeReferenceConversionResult ConversionResult;
	FSequencePlayerReference SequencePlayer = USequencePlayerLibrary::ConvertToSequencePlayer(Node, ConversionResult);
	
	if (ConversionResult == EAnimNodeReferenceConversionResult::Succeeded)
	{
		USequencePlayerLibrary::SetSequence(SequencePlayer, Sequence);
		return true;
	}

	return false;
}
