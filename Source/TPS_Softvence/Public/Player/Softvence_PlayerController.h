// CopyrightNotice=© 2025 Softvence. TPS — Development Build. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "Softvence_PlayerController.generated.h"


class ASoftvence_PlayerCharacter;
class UInputMappingContext;
class UInputAction;









UCLASS()
class TPS_SOFTVENCE_API ASoftvence_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
	//==================================================================================================================
public:
	ASoftvence_PlayerController();
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	
#pragma region Mapping Context
	// Input Context
	UPROPERTY(EditAnywhere, Category = "---Softvence---|Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Input")
	UInputMappingContext* VehicleMappingContext;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Input")
	UInputMappingContext* BuildingMappingContext;
	
#pragma endregion 
	
#pragma region Input Action
	// Input Actions - Movement
	UPROPERTY(EditAnywhere, Category = "---Softvence---|InputAction|Movement")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|InputAction|Movement")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|InputAction|Movement")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|InputAction|Movement")
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere,Category = "---Softvence---|InputAction|Movement")
	UInputAction* CrouchAction;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|InputAction|Movement")
	UInputAction* ProneAction;

	// Input Actions - Combat
	UPROPERTY(EditAnywhere, Category = "---Softvence---|InputAction|Combat")
	UInputAction* FireAction;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|InputAction|Combat")
	UInputAction* AimAction;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|InputAction|Combat")
	UInputAction* ReloadAction;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|InputAction|Combat")
	UInputAction* WeaponSwitch1Action;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|InputAction|Combat")
	UInputAction* WeaponSwitch2Action;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|InputAction|Combat")
	UInputAction* WeaponScrollAction;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|InputAction|Combat")
	UInputAction* MeleeAction;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|InputAction|Combat")
	UInputAction* ThrowGrenadeAction;
	
	
#pragma endregion 
	
 
	
	
	//==================================================================================================================
protected:
	
#pragma region Settings
	// Settings
	UPROPERTY(EditAnywhere, Category = "---Softvence---|Settings")
	float CameraSensitivity = 1.0f;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Settings")
	bool bInvertY = false;
	
#pragma endregion
	
	
	// Controlled Character
	UPROPERTY()
	ASoftvence_PlayerCharacter* ControlledCharacter;
	
	// Input Handlers - Movement
	void HandleMove(const FInputActionValue& Value);
	void HandleLook(const FInputActionValue& Value);
	void HandleJump(const FInputActionValue& Value);
	void HandleJumpReleased(const FInputActionValue& Value);
	void HandleSprint(const FInputActionValue& Value);
	void HandleSprintReleased(const FInputActionValue& Value);
	void HandleCrouch(const FInputActionValue& Value);
	void HandleProne(const FInputActionValue& Value);
};
