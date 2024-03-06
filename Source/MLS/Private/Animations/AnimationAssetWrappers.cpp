// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/AnimationAssetWrappers.h"
#include "BlendSpacePlayerLibrary.h"
#include "SequencePlayerLibrary.h"

TBlendSpaceAsset::TBlendSpaceAsset(UBlendSpace* BlendSpace)
{
	Asset = BlendSpace;
}

FAnimNodeReference TBlendSpaceAsset::Convert(const FAnimNodeReference& Node, EAnimNodeReferenceConversionResult& OutResult) const
{
	return UBlendSpacePlayerLibrary::ConvertToBlendSpacePlayer(Node, OutResult);
}

void TBlendSpaceAsset::Set(const FAnimNodeReference& Node) const
{
	UBlendSpacePlayerLibrary::SetBlendSpace(StaticCast<const FBlendSpacePlayerReference&>(Node), StaticCast<UBlendSpace*>(Asset));
}

TAnimSequenceAsset::TAnimSequenceAsset(UAnimSequence* Sequence)
{
	Asset = Sequence;
}

FAnimNodeReference TAnimSequenceAsset::Convert(const FAnimNodeReference& Node, EAnimNodeReferenceConversionResult& OutResult) const
{
	return USequencePlayerLibrary::ConvertToSequencePlayer(Node, OutResult);
}

void TAnimSequenceAsset::Set(const FAnimNodeReference& Node) const
{
	USequencePlayerLibrary::SetSequence(StaticCast<const FSequencePlayerReference&>(Node), StaticCast<UAnimSequence*>(Asset));
}
