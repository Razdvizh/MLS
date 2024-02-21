// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MLSAnimInstanceBase.generated.h"

class ACharacter;

/**
 * 
 */
UCLASS()
class MLS_API UMLSAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMLSAnimInstanceBase(const FObjectInitializer& ObjectInitializer);

	virtual void NativeInitializeAnimation() override;

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY()
	ACharacter* Character;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MLS", meta = (AllowPrivateAccess = true))
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MLS", meta = (AllowPrivateAccess = true))
	float Direction;

};
