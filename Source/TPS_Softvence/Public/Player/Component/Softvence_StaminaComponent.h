// CopyrightNotice=© 2025 Softvence. TPS — Development Build. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/Softvence_Types_Enums.h"
#include "Softvence_StaminaComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TPS_SOFTVENCE_API USoftvence_StaminaComponent : public UActorComponent
{
	GENERATED_BODY()

	//------------------------------------------------------------------------------------------------------------------
public:
	USoftvence_StaminaComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	// ================== STAMINA USAGE ==================
	UFUNCTION()
	bool UseStamina(float Amount);

	UFUNCTION()
	void StartContinuousUsage(float UsagePerSecond);

	UFUNCTION()
	void StopContinuousUsage();

	UFUNCTION()
	void AddStamina(float Amount);
	
	
	// ================== GETTERS ==================
	
	UFUNCTION()
	float GetStamina() const { return CurrentStamina; }

	UFUNCTION()
	float GetMaxStamina() const { return MaxStamina; }

	UFUNCTION()
	float GetStaminaPercent() const { return CurrentStamina / MaxStamina; }

	UFUNCTION()
	bool HasEnoughStamina(float Amount) const { return CurrentStamina >= Amount; }

	UFUNCTION()
	bool IsExhausted() const { return bIsExhausted; }

	UFUNCTION()
	bool IsRegenerating() const { return bIsRegenerating; }
	
	
	
	// ================== MODIFIERS ==================
	
	UFUNCTION()
	void SetStaminaRegenRate(float NewRate) { StaminaRegenRate = NewRate; }

	UFUNCTION()
	void SetStaminaRegenDelay(float NewDelay) { StaminaRegenDelay = NewDelay; }

	UFUNCTION()
	void ApplyRegenModifier(float Modifier, float Duration);
	
	
	// ================== DELEGATES ==================
	
	UPROPERTY()
	FOnStaminaChanged OnStaminaChanged;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExhausted);
	UPROPERTY()
	FOnExhausted OnExhausted;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRecovered);
	UPROPERTY()
	FOnRecovered OnRecovered;
	
	
	
	//------------------------------------------------------------------------------------------------------------------
protected:
	// ================== STAMINA SETTINGS ==================
	
	UPROPERTY(EditAnywhere, Category = "---Softvence---|Stamina")
	float MaxStamina = 100.0f;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Stamina")
	float CurrentStamina;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Stamina")
	float StaminaRegenRate = 15.0f;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Stamina")
	float StaminaRegenDelay = 1.5f;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Stamina")
	float ExhaustedThreshold = 0.0f;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Stamina")
	float RecoveryThreshold = 25.0f;
	
	
	// ================== USAGE COSTS ==================
	
	UPROPERTY(EditAnywhere, Category = "---Softvence---|Usage Costs")
	float SprintCostPerSecond = 10.0f;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Usage Costs")
	float JumpCost = 15.0f;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Usage Costs")
	float VaultCost = 20.0f;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Usage Costs")
	float MeleeCost = 25.0f;

	
	// ================== STATE ==================
	
	UPROPERTY()
	bool bIsExhausted = false;

	UPROPERTY()
	bool bIsRegenerating = false;

	UPROPERTY()
	bool bContinuousUsage = false;

	UPROPERTY()
	float ContinuousUsageRate = 0.0f;

	UPROPERTY()
	float TimeSinceLastUsage = 0.0f;

	UPROPERTY()
	float RegenModifier = 1.0f;

	UPROPERTY()
	float RegenModifierDuration = 0.0f;
	
	// ================== INTERNAL ==================
	
	void UpdateStaminaRegeneration(float DeltaTime);
	void UpdateContinuousUsage(float DeltaTime);
	void UpdateModifiers(float DeltaTime);
	
	
	
	
};
