// CopyrightNotice=© 2025 Softvence. TPS — Development Build. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Data/Softvence_Types_Enums.h"
#include "Softvence_PlayerAnimInstance.generated.h"



class ASoftvence_PlayerCharacter;

UCLASS()
class TPS_SOFTVENCE_API USoftvence_PlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	
	//------------------------------------------------------------------------------------------------------------------
public:
	USoftvence_PlayerAnimInstance();
	
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	
	// ================== CHARACTER USAGE ==================
	
	UPROPERTY(BlueprintReadOnly, Category = "---Softvence---|Character")
	ASoftvence_PlayerCharacter* OwningCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "---Softvence---|Character")
	float Speed;

	UPROPERTY(BlueprintReadOnly, Category = "---Softvence---|Character")
	float Direction;

	UPROPERTY(BlueprintReadOnly, Category = "---Softvence---|Character")
	FVector Velocity;

	UPROPERTY(BlueprintReadOnly, Category = "---Softvence---|Character")
	bool bIsMoving;

	UPROPERTY(BlueprintReadOnly, Category = "---Softvence---|Character")
	bool bIsInAir;

	UPROPERTY(BlueprintReadOnly, Category = "---Softvence---|Character")
	bool bIsCrouching;

	UPROPERTY(BlueprintReadOnly, Category = "---Softvence---|Character")
	bool bIsProne;

	UPROPERTY(BlueprintReadOnly, Category = "---Softvence---|Character")
	EMovementStance MovementStance;

	// ================== COMBAT STATE ==================
    
	UPROPERTY(BlueprintReadOnly, Category = "---Softvence---|Combat")
	bool bIsAiming;

	UPROPERTY(BlueprintReadOnly, Category = "---Softvence---|Combat")
	bool bIsFiring;

	UPROPERTY(BlueprintReadOnly, Category = "---Softvence---|Combat")
	bool bIsReloading;

	UPROPERTY(BlueprintReadOnly, Category = "---Softvence---|Combat")
	bool bHasWeapon;

	UPROPERTY(BlueprintReadOnly, Category = "---Softvence---|Combat")
	EWeaponType CurrentWeaponType;

	UPROPERTY(BlueprintReadOnly, Category = "---Softvence---|Combat")
	float ADSAlpha;

	// ================== AIM OFFSET ==================
    
	UPROPERTY(BlueprintReadOnly, Category = "---Softvence---|AimOffset")
	FRotator AimOffset;

	UPROPERTY(BlueprintReadOnly, Category = "---Softvence---|AimOffset")
	float AimOffsetPitch;

	UPROPERTY(BlueprintReadOnly, Category = "---Softvence---|AimOffset")
	float AimOffsetYaw;

	// ================== LEAN ==================
    
	UPROPERTY(BlueprintReadOnly, Category = "---Softvence---|Lean")
	float LeanAmount;

	UPROPERTY(BlueprintReadOnly, Category = "---Softvence---|Lean")
	float LeanAngle;
	
	// ================== COVER ==================
    
	UPROPERTY(BlueprintReadOnly, Category = "Cover")
	bool bIsInCover;

	UPROPERTY(BlueprintReadOnly, Category = "Cover")
	ECoverType CoverType;

	UPROPERTY(BlueprintReadOnly, Category = "Cover")
	bool bIsPeekingLeft;

	UPROPERTY(BlueprintReadOnly, Category = "Cover")
	bool bIsPeekingRight;

	UPROPERTY(BlueprintReadOnly, Category = "Cover")
	bool bIsPeekingOver;

	// ================== IK ==================
    
	UPROPERTY(BlueprintReadOnly, Category = "IK")
	FTransform LeftHandIKTransform;

	UPROPERTY(BlueprintReadOnly, Category = "IK")
	FTransform RightHandIKTransform;

	UPROPERTY(BlueprintReadOnly, Category = "IK")
	float LeftHandIKAlpha;

	UPROPERTY(BlueprintReadOnly, Category = "IK")
	float RightHandIKAlpha;

	UPROPERTY(BlueprintReadOnly, Category = "IK")
	FVector LeftFootIKOffset;

	UPROPERTY(BlueprintReadOnly, Category = "IK")
	FVector RightFootIKOffset;

	UPROPERTY(BlueprintReadOnly, Category = "IK")
	float LeftFootIKAlpha;

	UPROPERTY(BlueprintReadOnly, Category = "IK")
	float RightFootIKAlpha;

	UPROPERTY(BlueprintReadOnly, Category = "IK")
	float PelvisOffset;
	
	// ================== PROCEDURAL ANIMATION ==================
    
	UPROPERTY(BlueprintReadOnly, Category = "Procedural")
	FVector2D CurrentRecoil;

	UPROPERTY(BlueprintReadOnly, Category = "Procedural")
	FRotator SpineRotation;

	UPROPERTY(BlueprintReadOnly, Category = "Procedural")
	float BreathingAlpha;

	UPROPERTY(BlueprintReadOnly, Category = "Procedural")
	FVector WeaponSway;

	UPROPERTY(BlueprintReadOnly, Category = "Procedural")
	float TurnInPlaceAngle;

	UPROPERTY(BlueprintReadOnly, Category = "Procedural")
	bool bShouldTurnInPlace;

	// ================== ADDITIVE LAYERS ==================
    
	UPROPERTY(BlueprintReadOnly, Category = "Additive")
	float HitReactionAlpha;

	UPROPERTY(BlueprintReadOnly, Category = "Additive")
	FVector HitReactionDirection;

	UPROPERTY(BlueprintReadOnly, Category = "Additive")
	float DeathAlpha;
	
	// ================== SETTINGS ==================
    
	UPROPERTY(EditAnywhere, Category = "---Softvence---|Settings")
	float FootIKTraceDistance = 50.0f;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Settings")
	float FootIKInterpSpeed = 15.0f;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Settings")
	float WeaponSwayAmount = 2.0f;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Settings")
	float WeaponSwaySpeed = 3.0f;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Settings")
	float TurnInPlaceThreshold = 90.0f;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Settings")
	float BreathingSpeed = 2.0f;

	// ================== FUNCTIONS ==================
    
	UFUNCTION()
	void PlayHitReaction(FVector HitDirection, float Intensity);

	UFUNCTION()
	void TriggerReloadAnimation();

	UFUNCTION()
	void TriggerFireAnimation();

	UFUNCTION()
	void SetWeaponType(EWeaponType NewWeaponType);
	
	//------------------------------------------------------------------------------------------------------------------
protected:
	// ================== UPDATE FUNCTIONS ==================
	
	void UpdateCharacterState();
	void UpdateCombatState();
	void UpdateAimOffset();
	void UpdateLean();
	void UpdateIK(float DeltaTime);
	void UpdateFootIK(float DeltaTime);
	void UpdateHandIK(float DeltaTime);
	void UpdateProceduralAnimation(float DeltaTime);
	void UpdateWeaponSway(float DeltaTime);
	void UpdateBreathing(float DeltaTime);
	void UpdateTurnInPlace(float DeltaTime);
	void UpdateCoverState();

	// IK Helper Functions
	float TraceFootIK(const FName& FootBoneName, FVector& OutOffset);
	FTransform GetBoneTransformFromSocket(const FName& SocketName);

	// State tracking
	UPROPERTY()
	FRotator LastFrameRotation;

	UPROPERTY()
	float AccumulatedYawDelta;

	UPROPERTY()
	float TimeAccumulator;

	// Interp targets
	UPROPERTY()
	FVector TargetLeftFootOffset;

	UPROPERTY()
	FVector TargetRightFootOffset;

	UPROPERTY()
	float TargetPelvisOffset;

	UPROPERTY()
	FVector TargetWeaponSway;
};
