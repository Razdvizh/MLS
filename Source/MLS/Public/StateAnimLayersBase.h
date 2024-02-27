// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimNodeReference.h"
#include "Animation/AnimationAsset.h"
#include "StateAnimLayersBase.generated.h"

class UBlendSpace;
class UAnimSequence;
class UMLSAnimInstanceBase;
struct FAnimUpdateContext;

/**
 * 
 */
UCLASS()
class MLS_API UStateAnimLayersBase : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UStateAnimLayersBase(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utility", meta = (DisplayName = "GetMainAnimBPThreadSafe", BlueprintThreadSafe))
	UMLSAnimInstanceBase* GetMainAnimInstance() const;

protected:
	UFUNCTION(BlueprintCallable, Category = "Node Functions", meta = (BlueprintThreadSafe))
	void OnInitialUpdateIdleAnim(const FAnimUpdateContext& Context, const FAnimNodeReference& Node);

	UFUNCTION(BlueprintCallable, Category = "Node Functions", meta = (BlueprintThreadSafe))
	void OnInitialUpdateJumpAnim(const FAnimUpdateContext& Context, const FAnimNodeReference& Node);

	UFUNCTION(BlueprintCallable, Category = "Node Functions", meta = (BlueprintThreadSafe))
	void OnInitialUpdateFallLoopAnim(const FAnimUpdateContext& Context, const FAnimNodeReference& Node);

	UFUNCTION(BlueprintCallable, Category = "Node Functions", meta = (BlueprintThreadSafe))
	void OnInitialUpdateLandAnim(const FAnimUpdateContext& Context, const FAnimNodeReference& Node);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blend Spaces")
	UBlendSpace* StandWalkJogRun;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blend Spaces")
	UBlendSpace* Jump;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim Sequences")
	UAnimSequence* FallLoop;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim Sequences")
	UAnimSequence* Land;

#pragma region Anim Assets Classes
private:
	template<class DerivedT>
	class TAnimationAsset
	{
	public:
		template<class DerivedT>
		inline bool SetNodeAsset(const FAnimNodeReference& Node) const
		{
			return StaticCast<DerivedT*>(this)->SetNodeAsset(Node);
		}

	protected:
		TAnimationAsset() = default;

		UPROPERTY()
		UAnimationAsset* Asset;

	private:
		friend DerivedT;

	};

	class TBlendSpaceAsset : public TAnimationAsset<TBlendSpaceAsset>
	{
	public:
		TBlendSpaceAsset(UBlendSpace* BlendSpace);

		bool SetNodeAsset(const FAnimNodeReference& Node) const;
	};

	class TAnimSequenceAsset : public TAnimationAsset<TAnimSequenceAsset>
	{
	public:
		TAnimSequenceAsset(UAnimSequence* AnimSequence);

		bool SetNodeAsset(const FAnimNodeReference& Node) const;
	};
#pragma endregion Anim Assets Classes
};
