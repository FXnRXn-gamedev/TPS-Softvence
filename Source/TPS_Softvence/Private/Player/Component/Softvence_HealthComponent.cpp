// CopyrightNotice=© 2025 Softvence. TPS — Development Build. All rights reserved


#include "Player/Component/Softvence_HealthComponent.h"

#include "Net/UnrealNetwork.h"


// =====================================================================================================================
// ---> CONSTRUCTOR & UNREAL CALLBACK <---
// =====================================================================================================================

USoftvence_HealthComponent::USoftvence_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}

void USoftvence_HealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

void USoftvence_HealthComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bIsDead) return;
	
	TimeSinceLastDamage += DeltaTime;
	UpdateHealthRegeneration(DeltaTime);
}




// =====================================================================================================================
// ---> NET <---
// =====================================================================================================================

void USoftvence_HealthComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(USoftvence_HealthComponent, CurrentHealth);
	DOREPLIFETIME(USoftvence_HealthComponent, MaxHealth);
	DOREPLIFETIME(USoftvence_HealthComponent, CurrentArmor);
	DOREPLIFETIME(USoftvence_HealthComponent, MaxArmor);
}


// =====================================================================================================================
// ---> HEALTH MANAGEMENT <---
// =====================================================================================================================


void USoftvence_HealthComponent::TakeDamage(float DamageAmount, AActor* DamageCauser, AActor* DamageInstigator)
{
	if (bIsDead || DamageAmount <= 0.0f) return;

	if (GetOwner()->HasAuthority())
	{
		float ActualDamage = CalculateDamageAfterArmor(DamageAmount);
		CurrentHealth = FMath::Clamp(CurrentHealth - ActualDamage, 0.0f, MaxHealth);
		LastDamageCauser = DamageCauser;
		TimeSinceLastDamage = 0.0f;

		OnHealthChanged.Broadcast(CurrentHealth);
		OnDamageTaken.Broadcast(ActualDamage, DamageCauser, DamageInstigator);

		if (CurrentHealth <= 0.0f)
		{
			HandleDeath();
		}
	}
	else
	{
		Server_TakeDamage(DamageAmount, DamageCauser, DamageInstigator);
	}
}

void USoftvence_HealthComponent::Server_TakeDamage_Implementation(float DamageAmount, AActor* DamageCauser, AActor* DamageInstigator)
{
	TakeDamage(DamageAmount, DamageCauser, DamageInstigator);
}



void USoftvence_HealthComponent::Heal(float HealAmount)
{
	if (bIsDead || HealAmount <= 0.0f) return;

	if (GetOwner()->HasAuthority())
	{
		CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.0f, MaxHealth);
		OnHealthChanged.Broadcast(CurrentHealth);
	}
	else
	{
		Server_Heal(HealAmount);
	}
}

void USoftvence_HealthComponent::Server_Heal_Implementation(float HealAmount)
{
	Heal(HealAmount);
}

void USoftvence_HealthComponent::SetHealth(float NewHealth)
{
	CurrentHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth);

	if (CurrentHealth <= 0.0f && !bIsDead)
	{
		HandleDeath();
	}
}

void USoftvence_HealthComponent::SetMaxHealth(float NewMaxHealth)
{
	MaxHealth = FMath::Max(NewMaxHealth, 1.0f);
	CurrentHealth = FMath::Min(CurrentHealth, MaxHealth);
}

void USoftvence_HealthComponent::AddArmor(float ArmorAmount)
{
	CurrentArmor = FMath::Clamp(CurrentArmor + ArmorAmount, 0.0f, MaxArmor);
	OnArmorChanged.Broadcast(CurrentArmor);
}

void USoftvence_HealthComponent::RemoveArmor(float ArmorAmount)
{
	CurrentArmor = FMath::Clamp(CurrentArmor - ArmorAmount, 0.0f, MaxArmor);
	OnArmorChanged.Broadcast(CurrentArmor);
}

float USoftvence_HealthComponent::CalculateDamageAfterArmor(float IncomingDamage)
{
	if (CurrentArmor <= 0.0f)
	{
		return IncomingDamage;
	}

	// Calculate armor effectiveness
	float ArmorEffectiveness = (CurrentArmor / MaxArmor) * ArmorDamageReduction;
	float DamageAfterArmor = IncomingDamage * (1.0f - ArmorEffectiveness);

	// Armor takes damage too
	float ArmorDamage = IncomingDamage * 0.5f;
	CurrentArmor = FMath::Max(CurrentArmor - ArmorDamage, 0.0f);
	OnArmorChanged.Broadcast(CurrentArmor);

	return DamageAfterArmor;
}

void USoftvence_HealthComponent::UpdateHealthRegeneration(float DeltaTime)
{
	if (!bCanRegenerate) return;
	if (TimeSinceLastDamage < HealthRegenDelay) return;
	if (IsFullHealth()) return;

	float MaxRegen = bRegenToFull ? MaxHealth : MaxRegenHealth;
	if (CurrentHealth >= MaxRegen) return;

	float RegenAmount = HealthRegenRate * DeltaTime;
	CurrentHealth = FMath::Min(CurrentHealth + RegenAmount, MaxRegen);
	OnHealthChanged.Broadcast(CurrentHealth);
}

void USoftvence_HealthComponent::SetHealthRegeneration(bool bEnabled, float RegenRate, float RegenDelay)
{
	bCanRegenerate = bEnabled;
	HealthRegenRate = RegenRate;
	HealthRegenDelay = RegenDelay;
}

void USoftvence_HealthComponent::HandleDeath()
{
	if (bIsDead) return;
    
	bIsDead = true;
	OnDeath.Broadcast();
}

void USoftvence_HealthComponent::OnRep_Health()
{
	OnHealthChanged.Broadcast(CurrentHealth);

	if (CurrentHealth <= 0.0f && !bIsDead)
	{
		HandleDeath();
	}
}

