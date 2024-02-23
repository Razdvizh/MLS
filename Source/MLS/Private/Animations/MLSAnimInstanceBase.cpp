// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/MLSAnimInstanceBase.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UMLSAnimInstanceBase::UMLSAnimInstanceBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	Speed(0.f),
	Direction(0.f)
{
	bUseMultiThreadedAnimationUpdate = true;
}

void UMLSAnimInstanceBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ACharacter>(GetOwningActor());
}

void UMLSAnimInstanceBase::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (Character)
	{
		const FVector Velocity = Character->GetCharacterMovement()->Velocity;

		Speed = Velocity.Size2D();
		Direction = CalculateDirection(Velocity, Character->GetActorRotation());
	}
}
