// CopyrightNotice=© 2025 Softvence. TPS — Development Build. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Data/Softvence_Types_Enums.h"
#include "Softvence_PlayerCharacter.generated.h"




class USpringArmComponent;
class UCameraComponent;





UCLASS()
class TPS_SOFTVENCE_API ASoftvence_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	//==================================================================================================================
public:
	ASoftvence_PlayerCharacter(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
#pragma region Camera
	// Camera Components
	UPROPERTY(EditDefaultsOnly, Category = "---Softvence---|Camera")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, Category = "---Softvence---|Camera")
	UCameraComponent* FollowCamera;
	
#pragma endregion 
	
#pragma region Components
	
#pragma endregion 
	
	
	// ================== STATE GETTERS ==================
    
	UFUNCTION(BlueprintCallable, Category = "State")
	bool IsAiming() const { return bIsAiming; }

	UFUNCTION(BlueprintCallable, Category = "State")
	bool IsFiring() const { return bIsFiring; }

	UFUNCTION(BlueprintCallable, Category = "State")
	bool IsSprinting() const { return bIsSprinting; }

	UFUNCTION(BlueprintCallable, Category = "State")
	bool IsInCover() const { return bIsInCover; }

	UFUNCTION(BlueprintCallable, Category = "State")
	bool IsReloading() const { return bIsReloading; }

	UFUNCTION(BlueprintCallable, Category = "State")
	EMovementStance GetMovementStance() const { return CurrentStance; }

	UFUNCTION(BlueprintCallable, Category = "State")
	float GetLeanAmount() const { return CurrentLeanAmount; }

	// UFUNCTION(BlueprintCallable, Category = "State")
	// AWeaponBase* GetCurrentWeapon() const;

	// UFUNCTION(BlueprintCallable, Category = "State")
	// FVector GetAimLocation() const;
	//
	// UFUNCTION(BlueprintCallable, Category = "State")
	// bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "State")
	EFactionType GetFaction() const { return CharacterFaction; }
	
	
	// ================== INPUT HANDLERS ==================
    
	UFUNCTION()
	void HandleMoveInput(FVector2D MovementVector);

	UFUNCTION()
	void HandleLookInput(FVector2D LookVector);
	
	UFUNCTION()
	void HandleJumpInput(bool bPressed);

	UFUNCTION()
	void HandleSprintInput(bool bSprinting);

	UFUNCTION()
	void HandleCrouchInput();

	UFUNCTION()
	void HandleProneInput();

	UFUNCTION()
	void HandleFireInput(bool bFiring);

	UFUNCTION()
	void HandleAimInput(bool bAiming);
	
	
	
	//==================================================================================================================
protected:
	
#pragma region  STATE VARIABLES
    
	UPROPERTY(EditDefaultsOnly, Replicated, Category = "---Softvence---|State")
	bool bIsAiming = false;

	UPROPERTY(EditDefaultsOnly, Replicated, Category = "---Softvence---|State")
	bool bIsFiring = false;

	UPROPERTY(EditDefaultsOnly, Replicated, Category = "---Softvence---|State")
	bool bIsSprinting = false;

	UPROPERTY(EditDefaultsOnly, Replicated, Category = "---Softvence---|State")
	bool bIsInCover = false;

	UPROPERTY(EditDefaultsOnly, Replicated, Category = "---Softvence---|State")
	bool bIsReloading = false;

	UPROPERTY(EditDefaultsOnly, Replicated, Category = "---Softvence---|State")
	EMovementStance CurrentStance = EMovementStance::Standing;

	UPROPERTY(EditDefaultsOnly, Replicated, Category = "---Softvence---|State")
	float CurrentLeanAmount = 0.0f;

	UPROPERTY(EditDefaultsOnly,  Category = "---Softvence---|State")
	float ADSAlpha = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "---Softvence---|State")
	FVector2D CurrentRecoil = FVector2D::ZeroVector;

	UPROPERTY(EditDefaultsOnly, Category = "---Softvence---|Character")
	EFactionType CharacterFaction = EFactionType::Player;
	
#pragma endregion 
	
	
#pragma region Camera Settings
	UPROPERTY(EditAnywhere, Category = "---Softvence---|Camera")
	float DefaultCameraDistance = 300.0f;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Camera")
	float AimingCameraDistance = 150.0f;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Camera")
	FVector DefaultCameraOffset = FVector(0.0f, 50.0f, 70.0f);

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Camera")
	FVector AimingCameraOffset = FVector(0.0f, 70.0f, 60.0f);

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Camera")
	float CameraInterpSpeed = 10.0f;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Camera")
	float DefaultFOV = 90.0f;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Camera")
	float AimingFOV = 60.0f;
	
#pragma endregion 
	
	
#pragma region MOVEMENT SETTINGS
    
	UPROPERTY(EditAnywhere, Category = "---Softvence---|Movement")
	float WalkSpeed = 400.0f;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Movement")
	float SprintSpeed = 650.0f;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Movement")
	float CrouchSpeed = 150.0f;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Movement")
	float ProneSpeed = 75.0f;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Movement")
	float AimingSpeedMultiplier = 0.5f;
	
#pragma endregion 
	
	
	
	
	// ================== INTERNAL METHODS ==================
	
	void UpdateMovementSpeed();
	
	// Movement Input
	UPROPERTY()
	FVector2D CurrentMovementInput;

};
