// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNodeReference.h"

class UAnimationAsset;
class UBlendSpace;
class UAnimSequence;

template<class DerivedT>
class MLS_API TAnimationAsset
{
public:
	template<class DerivedT>
	inline void SetAnimationAsset(const FAnimNodeReference& Node) const
	{
		check(Asset);
		const DerivedT* DerivedThis = StaticCast<const DerivedT*>(this);

		EAnimNodeReferenceConversionResult Result;
		FAnimNodeReference ConvertedNode = DerivedThis->Convert(Node, Result);
		if (Result == EAnimNodeReferenceConversionResult::Succeeded)
		{
			DerivedThis->Set(ConvertedNode);
		}
	}

protected:
	TAnimationAsset() = default;

	template<class DerivedT>
	inline FAnimNodeReference Convert(const FAnimNodeReference& Node, EAnimNodeReferenceConversionResult& OutResult) const
	{
		return StaticCast<const DerivedT*>(this)->Convert(Node, OutResult);
	}

	template<class DerivedT>
	inline void Set(const FAnimNodeReference& Node) const
	{
		StaticCast<const DerivedT*>(this)->Set(Node);
	}

	UPROPERTY()
	UAnimationAsset* Asset;

private:
	friend DerivedT;

};

class MLS_API TBlendSpaceAsset final : public TAnimationAsset<TBlendSpaceAsset>
{
public:
	TBlendSpaceAsset(UBlendSpace* BlendSpace);

private:
	FAnimNodeReference Convert(const FAnimNodeReference& Node, EAnimNodeReferenceConversionResult& OutResult) const;

	void Set(const FAnimNodeReference& Node) const;

	friend TAnimationAsset;

};

class MLS_API TAnimSequenceAsset final : public TAnimationAsset<TAnimSequenceAsset>
{
public:
	TAnimSequenceAsset(UAnimSequence* Sequence);

private:
	FAnimNodeReference Convert(const FAnimNodeReference& Node, EAnimNodeReferenceConversionResult& OutResult) const;

	void Set(const FAnimNodeReference& Node) const;

	friend TAnimationAsset;

};
