// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "StateAnimLayersBase.generated.h"

class UBlendSpace;
class UAnimSequence;
class UMLSAnimInstanceBase;
struct FAnimUpdateContext;
struct FAnimNodeReference;

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
	void OnInitialUpdateLandAnim(const FAnimUpdateContext& Context, const FAnimNodeReference& Node);

	UFUNCTION(BlueprintCallable, Category = "Node Functions", meta = (BlueprintThreadSafe))
	void OnInitialUpdateFallLoopAnim(const FAnimUpdateContext& Context, const FAnimNodeReference& Node);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blend Spaces")
	UBlendSpace* StandWalkJogRun;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blend Spaces")
	UBlendSpace* Jump;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim Sequences")
	UAnimSequence* FallLoop;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim Sequences")
	UAnimSequence* Land;

private:
	bool SetBlendSpace(const FAnimNodeReference& Node, UBlendSpace* BlendSpace) const;

	bool SetAnimSequence(const FAnimNodeReference& Node, UAnimSequence* Sequence) const;

};
