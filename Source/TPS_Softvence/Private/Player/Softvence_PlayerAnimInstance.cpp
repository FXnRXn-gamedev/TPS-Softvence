// CopyrightNotice=© 2025 Softvence. TPS — Development Build. All rights reserved


#include "Player/Softvence_PlayerAnimInstance.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/Softvence_PlayerCharacter.h"



// =====================================================================================================================
// ---> CONSTRUCTOR & UNREAL CALLBACK <---
// =====================================================================================================================
USoftvence_PlayerAnimInstance::USoftvence_PlayerAnimInstance()
{
	Speed = 0.0f;
	Direction = 0.0f;
	bIsMoving = false;
	bIsInAir = false;
	bIsCrouching = false;
	bIsProne = false;
	bIsAiming = false;
	bIsFiring = false;
	bIsReloading = false;
	bHasWeapon = false;
	ADSAlpha = 0.0f;
	LeanAmount = 0.0f;
	LeftHandIKAlpha = 0.0f;
	RightHandIKAlpha = 0.0f;
	LeftFootIKAlpha = 1.0f;
	RightFootIKAlpha = 1.0f;
	PelvisOffset = 0.0f;
	BreathingAlpha = 0.0f;
	HitReactionAlpha = 0.0f;
	DeathAlpha = 0.0f;
	TurnInPlaceAngle = 0.0f;
	bShouldTurnInPlace = false;
	CurrentWeaponType = EWeaponType::None;
	MovementStance = EMovementStance::Standing;
	CoverType = ECoverType::None;
}

void USoftvence_PlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	OwningCharacter = Cast<ASoftvence_PlayerCharacter>(TryGetPawnOwner());
    
	if (OwningCharacter)
	{
		LastFrameRotation = OwningCharacter->GetActorRotation();
	}
}

void USoftvence_PlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (!OwningCharacter) 
	{
		OwningCharacter = Cast<ASoftvence_PlayerCharacter>(TryGetPawnOwner());
		if (!OwningCharacter) return;
	}

	UpdateCharacterState();
	UpdateCombatState();
	UpdateAimOffset();
	UpdateLean();
	UpdateCoverState();
	UpdateIK(DeltaSeconds);
	UpdateProceduralAnimation(DeltaSeconds);
}

void USoftvence_PlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}



// =====================================================================================================================
// ---> LOGIC <---
// =====================================================================================================================

void USoftvence_PlayerAnimInstance::UpdateCharacterState()
{
	if (!OwningCharacter) return;

	UCharacterMovementComponent* MovementComp = OwningCharacter->GetCharacterMovement();
	if (!MovementComp) return;

	// Velocity and Speed
	Velocity = MovementComp->Velocity;
	Speed = Velocity.Size2D();
	bIsMoving = Speed > 3.0f;

	// Calculate movement direction relative to character rotation
	if (bIsMoving)
	{
		FRotator MovementRotation = Velocity.ToOrientationRotator();
		FRotator CharacterRotation = OwningCharacter->GetActorRotation();
		FRotator DeltaRotation = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, CharacterRotation);
		Direction = DeltaRotation.Yaw;
	}
	else
	{
		Direction = 0.0f;
	}

	// Movement state
	bIsInAir = MovementComp->IsFalling();
	bIsCrouching = MovementComp->IsCrouching();
	MovementStance = OwningCharacter->GetMovementStance();
	bIsProne = MovementStance == EMovementStance::Prone;
}

void USoftvence_PlayerAnimInstance::UpdateCombatState()
{
	if (!OwningCharacter) return;

	bIsAiming = OwningCharacter->IsAiming();
	bIsFiring = OwningCharacter->IsFiring();
	bIsReloading = OwningCharacter->IsReloading();
	//ADSAlpha = OwningCharacter->GetAimDownSightsAlpha();
	//CurrentRecoil = OwningCharacter->GetCurrentRecoil();

	//AWeaponBase* CurrentWeapon = OwningCharacter->GetCurrentWeapon();
	// bHasWeapon = CurrentWeapon != nullptr;
 //    
	// if (CurrentWeapon)
	// {
	// 	CurrentWeaponType = CurrentWeapon->GetWeaponType();
	// }
	// else
	// {
	// 	CurrentWeaponType = EWeaponType::None;
	// }
}


void USoftvence_PlayerAnimInstance::UpdateAimOffset()
{
	if (!OwningCharacter) return;

	//AimOffset = OwningCharacter->GetAimOffset();
	AimOffsetPitch = AimOffset.Pitch;
	AimOffsetYaw = AimOffset.Yaw;

	// Clamp values
	AimOffsetPitch = FMath::Clamp(AimOffsetPitch, -90.0f, 90.0f);
	AimOffsetYaw = FMath::Clamp(AimOffsetYaw, -90.0f, 90.0f);
}

void USoftvence_PlayerAnimInstance::UpdateLean()
{
	if (!OwningCharacter) return;

	LeanAmount = OwningCharacter->GetLeanAmount();
	LeanAngle = LeanAmount * 15.0f; // Max lean angle of 15 degrees
}

void USoftvence_PlayerAnimInstance::UpdateCoverState()
{
	if (!OwningCharacter) return;

	bIsInCover = OwningCharacter->IsInCover();

	// UCoverComponent* CoverComp = OwningCharacter->CoverComponent;
	// if (CoverComp && bIsInCover)
	// {
	// 	CoverType = CoverComp->GetCurrentCoverType();
	// 	bIsPeekingLeft = CoverComp->IsPeekingLeft();
	// 	bIsPeekingRight = CoverComp->IsPeekingRight();
	// 	bIsPeekingOver = CoverComp->IsPeekingOver();
	// }
	// else
	// {
	// 	CoverType = ECoverType::None;
	// 	bIsPeekingLeft = false;
	// 	bIsPeekingRight = false;
	// 	bIsPeekingOver = false;
	// }
}

void USoftvence_PlayerAnimInstance::UpdateIK(float DeltaTime)
{
	UpdateFootIK(DeltaTime);
	UpdateHandIK(DeltaTime);
}

void USoftvence_PlayerAnimInstance::UpdateFootIK(float DeltaTime)
{
	if (!OwningCharacter || bIsInAir) 
	{
		LeftFootIKAlpha = 0.0f;
		RightFootIKAlpha = 0.0f;
		PelvisOffset = 0.0f;
		return;
	}

	// Trace for left foot
	float LeftFootOffset = TraceFootIK(FName("foot_l"), TargetLeftFootOffset);
    
	// Trace for right foot
	float RightFootOffset = TraceFootIK(FName("foot_r"), TargetRightFootOffset);

	// Interpolate foot offsets
	LeftFootIKOffset = FMath::VInterpTo(LeftFootIKOffset, TargetLeftFootOffset, DeltaTime, FootIKInterpSpeed);
	RightFootIKOffset = FMath::VInterpTo(RightFootIKOffset, TargetRightFootOffset, DeltaTime, FootIKInterpSpeed);

	// Calculate pelvis offset (use the lower foot offset)
	float MinOffset = FMath::Min(LeftFootOffset, RightFootOffset);
	TargetPelvisOffset = MinOffset;
	PelvisOffset = FMath::FInterpTo(PelvisOffset, TargetPelvisOffset, DeltaTime, FootIKInterpSpeed);

	// Set IK alphas
	LeftFootIKAlpha = 1.0f;
	RightFootIKAlpha = 1.0f;
}

float USoftvence_PlayerAnimInstance::TraceFootIK(const FName& FootBoneName, FVector& OutOffset)
{
	if (!OwningCharacter) return 0.0f;

	USkeletalMeshComponent* Mesh = OwningCharacter->GetMesh();
	if (!Mesh) return 0.0f;

	FVector FootLocation = Mesh->GetSocketLocation(FootBoneName);
	FVector ActorLocation = OwningCharacter->GetActorLocation();

	// Trace from above the foot down
	FVector TraceStart = FVector(FootLocation.X, FootLocation.Y, ActorLocation.Z);
	FVector TraceEnd = TraceStart - FVector(0, 0, FootIKTraceDistance + 50.0f);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(OwningCharacter);

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		TraceStart,
		TraceEnd,
		ECC_Visibility,
		QueryParams
	);

	if (bHit)
	{
		float FloorZ = HitResult.ImpactPoint.Z;
		float FootZ = FootLocation.Z;
		float Offset = FloorZ - (ActorLocation.Z - OwningCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
        
		OutOffset = FVector(0, 0, FMath::Clamp(Offset, -FootIKTraceDistance, FootIKTraceDistance));
		return Offset;
	}

	OutOffset = FVector::ZeroVector;
	return 0.0f;
}


void USoftvence_PlayerAnimInstance::UpdateHandIK(float DeltaTime)
{
	if (!OwningCharacter || !bHasWeapon)
	{
		LeftHandIKAlpha = 0.0f;
		RightHandIKAlpha = 0.0f;
		return;
	}

	//LeftHandIKTransform = OwningCharacter->GetLeftHandIKTransform();
	//RightHandIKTransform = OwningCharacter->GetRightHandIKTransform();

	// Set IK alpha based on weapon state
	LeftHandIKAlpha = bHasWeapon ? 1.0f : 0.0f;
	RightHandIKAlpha = 0.0f; // Usually right hand follows the weapon socket directly
}


void USoftvence_PlayerAnimInstance::UpdateProceduralAnimation(float DeltaTime)
{
	UpdateWeaponSway(DeltaTime);
	UpdateBreathing(DeltaTime);
	UpdateTurnInPlace(DeltaTime);

	// Calculate spine rotation for aiming
	if (bIsAiming || bHasWeapon)
	{
		SpineRotation = FRotator(0.0f, AimOffsetYaw * 0.5f, AimOffsetPitch * 0.3f);
	}
	else
	{
		SpineRotation = FRotator::ZeroRotator;
	}

	// Decay hit reaction
	if (HitReactionAlpha > 0.0f)
	{
		HitReactionAlpha = FMath::FInterpTo(HitReactionAlpha, 0.0f, DeltaTime, 5.0f);
	}
}


void USoftvence_PlayerAnimInstance::UpdateWeaponSway(float DeltaTime)
{
	if (!OwningCharacter || !bHasWeapon)
	{
		WeaponSway = FVector::ZeroVector;
		return;
	}

	TimeAccumulator += DeltaTime;

	// Calculate sway based on movement and time
	float SwayX = FMath::Sin(TimeAccumulator * WeaponSwaySpeed) * WeaponSwayAmount;
	float SwayY = FMath::Cos(TimeAccumulator * WeaponSwaySpeed * 0.5f) * WeaponSwayAmount * 0.5f;
	float SwayZ = FMath::Sin(TimeAccumulator * WeaponSwaySpeed * 0.75f) * WeaponSwayAmount * 0.3f;

	// Reduce sway when aiming
	float SwayMultiplier = bIsAiming ? 0.2f : 1.0f;
    
	// Increase sway when moving
	if (bIsMoving)
	{
		SwayMultiplier *= 1.5f;
	}

	TargetWeaponSway = FVector(SwayX, SwayY, SwayZ) * SwayMultiplier;
	WeaponSway = FMath::VInterpTo(WeaponSway, TargetWeaponSway, DeltaTime, 10.0f);

	// Add recoil to weapon sway
	WeaponSway.X += CurrentRecoil.X;
	WeaponSway.Z += CurrentRecoil.Y;
}

void USoftvence_PlayerAnimInstance::UpdateBreathing(float DeltaTime)
{
	TimeAccumulator += DeltaTime;
	BreathingAlpha = (FMath::Sin(TimeAccumulator * BreathingSpeed) + 1.0f) * 0.5f;
}

void USoftvence_PlayerAnimInstance::UpdateTurnInPlace(float DeltaTime)
{
	if (!OwningCharacter) return;

	FRotator CurrentRotation = OwningCharacter->GetActorRotation();
	FRotator DeltaRotation = UKismetMathLibrary::NormalizedDeltaRotator(CurrentRotation, LastFrameRotation);
    
	if (!bIsMoving && !bIsInAir)
	{
		AccumulatedYawDelta += DeltaRotation.Yaw;
		TurnInPlaceAngle = AccumulatedYawDelta;

		// Check if we should trigger turn in place
		if (FMath::Abs(AccumulatedYawDelta) > TurnInPlaceThreshold)
		{
			bShouldTurnInPlace = true;
		}
	}
	else
	{
		AccumulatedYawDelta = 0.0f;
		TurnInPlaceAngle = 0.0f;
		bShouldTurnInPlace = false;
	}

	LastFrameRotation = CurrentRotation;
}

void USoftvence_PlayerAnimInstance::PlayHitReaction(FVector HitDirection, float Intensity)
{
	HitReactionDirection = HitDirection.GetSafeNormal();
	HitReactionAlpha = FMath::Clamp(Intensity, 0.0f, 1.0f);
}

void USoftvence_PlayerAnimInstance::TriggerReloadAnimation()
{
	// This would trigger the appropriate montage based on weapon type
}



void USoftvence_PlayerAnimInstance::TriggerFireAnimation()
{
	// This would trigger the fire additive animation
}

void USoftvence_PlayerAnimInstance::SetWeaponType(EWeaponType NewWeaponType)
{
	CurrentWeaponType = NewWeaponType;
}






