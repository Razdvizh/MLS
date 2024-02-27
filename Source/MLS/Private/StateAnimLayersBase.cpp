// Fill out your copyright notice in the Description page of Project Settings.


#include "StateAnimLayersBase.h"
#include "Animation/BlendSpace.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimExecutionContext.h"
#include "Animation/AnimNodeReference.h"
#include "Animation/AnimNode_SequencePlayer.h"
#include "AnimNodes/AnimNode_BlendSpacePlayer.h"
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
	//SetBlendSpace(Node, StandWalkJogRun);
	TBlendSpaceAsset BlendSpaceAsset(StandWalkJogRun);

	SetAnimationAsset<TBlendSpaceAsset>(Node, BlendSpaceAsset);
}

void UStateAnimLayersBase::OnInitialUpdateJumpAnim(const FAnimUpdateContext& Context, const FAnimNodeReference& Node)
{
	//SetBlendSpace(Node, Jump);
	TBlendSpaceAsset BlendSpaceAsset(Jump);

	SetAnimationAsset<TBlendSpaceAsset>(Node, BlendSpaceAsset);
}

void UStateAnimLayersBase::OnInitialUpdateFallLoopAnim(const FAnimUpdateContext& Context, const FAnimNodeReference& Node)
{
	//SetAnimSequence(Node, FallLoop);
	TAnimSequenceAsset AnimSequenceAsset(FallLoop);

	SetAnimationAsset<TAnimSequenceAsset>(Node, AnimSequenceAsset);
}

void UStateAnimLayersBase::OnInitialUpdateLandAnim(const FAnimUpdateContext& Context, const FAnimNodeReference& Node)
{
	//SetAnimSequence(Node, Land);
	TAnimSequenceAsset AnimSequenceAsset(Land);

	SetAnimationAsset<TAnimSequenceAsset>(Node, AnimSequenceAsset);
}

//bool UStateAnimLayersBase::SetBlendSpace(const FAnimNodeReference& Node, UBlendSpace* BlendSpace) const
//{
//	EAnimNodeReferenceConversionResult ConversionResult;
//	FBlendSpacePlayerReference BlendSpacePlayer = UBlendSpacePlayerLibrary::ConvertToBlendSpacePlayer(Node, ConversionResult);
//
//	if (ConversionResult == EAnimNodeReferenceConversionResult::Succeeded)
//	{
//		UBlendSpacePlayerLibrary::SetBlendSpace(BlendSpacePlayer, BlendSpace);
//		return true;
//	}
//
//	return false;
//}
//
//bool UStateAnimLayersBase::SetAnimSequence(const FAnimNodeReference& Node, UAnimSequence* Sequence) const
//{
//	EAnimNodeReferenceConversionResult ConversionResult;
//	FSequencePlayerReference SequencePlayer = USequencePlayerLibrary::ConvertToSequencePlayer(Node, ConversionResult);
//	
//	if (ConversionResult == EAnimNodeReferenceConversionResult::Succeeded)
//	{
//		USequencePlayerLibrary::SetSequence(SequencePlayer, Sequence);
//		return true;
//	}
//
//	return false;
//}

UStateAnimLayersBase::TBlendSpaceAsset::TBlendSpaceAsset(UBlendSpace* BlendSpace)
{
	Asset = BlendSpace;
}

bool UStateAnimLayersBase::TBlendSpaceAsset::CallAnimNodeFunction(const FAnimNodeReference& Node) const
{
	bool bSucceeded = false;
	Node.CallAnimNodeFunction<FAnimNode_BlendSpacePlayer>(TEXT("SetBlendSpace"), [this, &bSucceeded](FAnimNode_BlendSpacePlayer& BlendSpacePlayer) 
	{
		bSucceeded = BlendSpacePlayer.SetBlendSpace(StaticCast<UBlendSpace*>(Asset));
	});

	return bSucceeded;
}

UStateAnimLayersBase::TAnimSequenceAsset::TAnimSequenceAsset(UAnimSequence* AnimSequence)
{
	Asset = AnimSequence;
}

bool UStateAnimLayersBase::TAnimSequenceAsset::CallAnimNodeFunction(const FAnimNodeReference& Node) const
{
	bool bSucceeded = false;
	Node.CallAnimNodeFunction<FAnimNode_SequencePlayer>(TEXT("SetSequence"), [this, &bSucceeded](FAnimNode_SequencePlayer& SequencePlayer)
	{
		bSucceeded = SequencePlayer.SetSequence(StaticCast<UAnimSequence*>(Asset));
	});

	return bSucceeded;
}
