// Fill out your copyright notice in the Description page of Project Settings.


#include "StateAnimLayersBase.h"
#include "Animation/BlendSpace.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimExecutionContext.h"
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
	TBlendSpaceAsset Asset(StandWalkJogRun);

	Asset.SetNodeAsset(Node);
}

void UStateAnimLayersBase::OnInitialUpdateJumpAnim(const FAnimUpdateContext& Context, const FAnimNodeReference& Node)
{
	TBlendSpaceAsset Asset(Jump);

	Asset.SetNodeAsset(Node);
}

void UStateAnimLayersBase::OnInitialUpdateFallLoopAnim(const FAnimUpdateContext& Context, const FAnimNodeReference& Node)
{
	TAnimSequenceAsset Asset(FallLoop);

	Asset.SetNodeAsset(Node);
}

void UStateAnimLayersBase::OnInitialUpdateLandAnim(const FAnimUpdateContext& Context, const FAnimNodeReference& Node)
{
	TAnimSequenceAsset Asset(Land);

	Asset.SetNodeAsset(Node);
}

UStateAnimLayersBase::TBlendSpaceAsset::TBlendSpaceAsset(UBlendSpace* BlendSpace)
{
	Asset = BlendSpace;
}

bool UStateAnimLayersBase::TBlendSpaceAsset::SetNodeAsset(const FAnimNodeReference& Node) const
{
	EAnimNodeReferenceConversionResult ConversionResult;
	FBlendSpacePlayerReference BlendSpacePlayer = UBlendSpacePlayerLibrary::ConvertToBlendSpacePlayer(Node, ConversionResult);

	if (ConversionResult == EAnimNodeReferenceConversionResult::Succeeded)
	{
		UBlendSpacePlayerLibrary::SetBlendSpace(BlendSpacePlayer, StaticCast<UBlendSpace*>(Asset));
		return true;
	}

	return false;
}

UStateAnimLayersBase::TAnimSequenceAsset::TAnimSequenceAsset(UAnimSequence* AnimSequence)
{
	Asset = AnimSequence;
}

bool UStateAnimLayersBase::TAnimSequenceAsset::SetNodeAsset(const FAnimNodeReference& Node) const
{
	EAnimNodeReferenceConversionResult ConversionResult;
	FSequencePlayerReference SequencePlayer = USequencePlayerLibrary::ConvertToSequencePlayer(Node, ConversionResult);

	if (ConversionResult == EAnimNodeReferenceConversionResult::Succeeded)
	{
		USequencePlayerLibrary::SetSequence(SequencePlayer, StaticCast<UAnimSequence*>(Asset));
		return true;
	}

	return false;
}
