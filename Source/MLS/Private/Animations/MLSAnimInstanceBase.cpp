// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/MLSAnimInstanceBase.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

constexpr float SPEED_THRESHOLD = 3.f;

UMLSAnimInstanceBase::UMLSAnimInstanceBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	Speed(0.f),
	SpeedZ(0.f),
	Direction(0.f),
	bIsFalling(false),
	bShouldMove(false)
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
		const UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
		const FVector Velocity = MovementComponent->Velocity;

		Speed = Velocity.Size2D();
		SpeedZ = Velocity.Z;
		Direction = CalculateDirection(Velocity, Character->GetActorRotation());
		bIsFalling = MovementComponent->IsFalling();
		bShouldMove = (!MovementComponent->GetCurrentAcceleration().IsNearlyZero()) && Speed > SPEED_THRESHOLD;
	}
}
