// CopyrightNotice=© 2025 Softvence. TPS — Development Build. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/Softvence_Types_Enums.h"
#include "Softvence_HealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TPS_SOFTVENCE_API USoftvence_HealthComponent : public UActorComponent
{
	GENERATED_BODY()
	
	//------------------------------------------------------------------------------------------------------------------
public:
	USoftvence_HealthComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	// ================== HEALTH MANAGEMENT ==================
	UFUNCTION()
	void TakeDamage(float DamageAmount, AActor* DamageCauser = nullptr, AActor* DamageInstigator = nullptr);
	
	UFUNCTION()
	void Heal(float HealAmount);
	
	UFUNCTION()
	void SetHealth(float NewHealth);
	
	UFUNCTION()
	void SetMaxHealth(float NewMaxHealth);
	
	UFUNCTION()
	void AddArmor(float ArmorAmount);
	
	UFUNCTION()
	void RemoveArmor(float ArmorAmount);
	
	// ================== GETTERS ==================
	UFUNCTION()
	float GetHealth() const { return CurrentHealth; }

	UFUNCTION()
	float GetMaxHealth() const { return MaxHealth; }

	UFUNCTION()
	float GetHealthPercent() const { return CurrentHealth / MaxHealth; }

	UFUNCTION()
	float GetArmor() const { return CurrentArmor; }

	UFUNCTION()
	float GetMaxArmor() const { return MaxArmor; }

	UFUNCTION()
	bool IsAlive() const { return CurrentHealth > 0.0f; }

	UFUNCTION()
	bool IsFullHealth() const { return CurrentHealth >= MaxHealth; }

	UFUNCTION()
	bool IsCriticalHealth() const { return CurrentHealth <= CriticalHealthThreshold; }
	
	// ================== DAMAGE INFO ==================
	
	UFUNCTION()
	AActor* GetLastDamageCauser() const { return LastDamageCauser; }

	UFUNCTION()
	float GetTimeSinceLastDamage() const { return TimeSinceLastDamage; }
	
	
	// ================== HEALTH REGEN ==================
	
	UFUNCTION()
	void SetHealthRegeneration(bool bEnabled, float RegenRate = 1.0f, float RegenDelay = 5.0f);
	
	
	
	// ================== DELEGATES ==================
	UPROPERTY()
	FOnHealthChanged OnHealthChanged;

	UPROPERTY()
	FOnDeath OnDeath;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnDamageTaken, float, Damage, AActor*, DamageCauser, AActor*, DamageInstigator);
	UPROPERTY()
	FOnDamageTaken OnDamageTaken;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnArmorChanged, float, NewArmor);
	UPROPERTY()
	FOnArmorChanged OnArmorChanged;
	
	
	//------------------------------------------------------------------------------------------------------------------
protected:
	
	
	// ================== HEALTH SETTINGS ==================
	
	UPROPERTY(EditAnywhere, Category = "---Softvence---|Health", ReplicatedUsing = OnRep_Health)
	float CurrentHealth;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Health", Replicated)
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Health", Replicated)
	float CurrentArmor = 0.0f;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Health", Replicated)
	float MaxArmor = 100.0f;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Health")
	float ArmorDamageReduction = 0.5f; // 50% damage reduction when armor is full

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Health")
	float CriticalHealthThreshold = 25.0f;
	
	// ================== HEALTH REGENERATION ==================
	
	UPROPERTY(EditAnywhere, Category = "---Softvence---|Regeneration")
	bool bCanRegenerate = false;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Regeneration")
	float HealthRegenRate = 1.0f;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Regeneration")
	float HealthRegenDelay = 5.0f;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Regeneration")
	bool bRegenToFull = false;

	UPROPERTY(EditAnywhere, Category = "---Softvence---|Regeneration")
	float MaxRegenHealth = 50.0f; // Only regen to this amount if bRegenToFull is false
	
	// Damage Tracking
	UPROPERTY()
	AActor* LastDamageCauser;

	UPROPERTY()
	float TimeSinceLastDamage = 0.0f;

	UPROPERTY()
	bool bIsDead = false;

	// Internal Functions
	UFUNCTION()
	void OnRep_Health();

	float CalculateDamageAfterArmor(float IncomingDamage);
	void UpdateHealthRegeneration(float DeltaTime);
	void HandleDeath();

	// Server RPCs
	UFUNCTION(Server, Reliable)
	void Server_TakeDamage(float DamageAmount, AActor* DamageCauser, AActor* DamageInstigator);

	UFUNCTION(Server, Reliable)
	void Server_Heal(float HealAmount);
	
	
};
	
