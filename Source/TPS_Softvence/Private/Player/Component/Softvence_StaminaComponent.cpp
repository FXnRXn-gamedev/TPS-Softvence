// CopyrightNotice=© 2025 Softvence. TPS — Development Build. All rights reserved


#include "Player/Component/Softvence_StaminaComponent.h"


// =====================================================================================================================
// ---> CONSTRUCTOR & UNREAL CALLBACK <---
// =====================================================================================================================

USoftvence_StaminaComponent::USoftvence_StaminaComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USoftvence_StaminaComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentStamina = MaxStamina;
}

void USoftvence_StaminaComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TimeSinceLastUsage += DeltaTime;
    
	UpdateContinuousUsage(DeltaTime);
	UpdateStaminaRegeneration(DeltaTime);
	UpdateModifiers(DeltaTime);
}




// =====================================================================================================================
// ---> NET <---
// =====================================================================================================================





// =====================================================================================================================
// ---> STAMINA MANAGEMENT <---
// =====================================================================================================================

bool USoftvence_StaminaComponent::UseStamina(float Amount)
{
	if (bIsExhausted || Amount <= 0.0f) return false;
	if (CurrentStamina < Amount) return false;

	CurrentStamina = FMath::Max(CurrentStamina - Amount, 0.0f);
	TimeSinceLastUsage = 0.0f;
	bIsRegenerating = false;

	OnStaminaChanged.Broadcast(CurrentStamina);

	if (CurrentStamina <= ExhaustedThreshold)
	{
		bIsExhausted = true;
		OnExhausted.Broadcast();
	}

	return true;
}

void USoftvence_StaminaComponent::StartContinuousUsage(float UsagePerSecond)
{
	if (bIsExhausted) return;

	bContinuousUsage = true;
	ContinuousUsageRate = UsagePerSecond;
}

void USoftvence_StaminaComponent::StopContinuousUsage()
{
	bContinuousUsage = false;
	ContinuousUsageRate = 0.0f;
}

void USoftvence_StaminaComponent::AddStamina(float Amount)
{
	if (Amount <= 0.0f) return;

	CurrentStamina = FMath::Min(CurrentStamina + Amount, MaxStamina);
	OnStaminaChanged.Broadcast(CurrentStamina);

	if (bIsExhausted && CurrentStamina >= RecoveryThreshold)
	{
		bIsExhausted = false;
		OnRecovered.Broadcast();
	}
}

void USoftvence_StaminaComponent::ApplyRegenModifier(float Modifier, float Duration)
{
	RegenModifier = Modifier;
	RegenModifierDuration = Duration;
}



// =====================================================================================================================
// ---> INTERNAL <---
// =====================================================================================================================

void USoftvence_StaminaComponent::UpdateContinuousUsage(float DeltaTime)
{
	if (!bContinuousUsage || bIsExhausted) return;

	float UsageAmount = ContinuousUsageRate * DeltaTime;
    
	CurrentStamina = FMath::Max(CurrentStamina - UsageAmount, 0.0f);
	TimeSinceLastUsage = 0.0f;

	OnStaminaChanged.Broadcast(CurrentStamina);

	if (CurrentStamina <= ExhaustedThreshold)
	{
		bIsExhausted = true;
		bContinuousUsage = false;
		OnExhausted.Broadcast();
	}
}

void USoftvence_StaminaComponent::UpdateStaminaRegeneration(float DeltaTime)
{
	if (bContinuousUsage) return;
	if (CurrentStamina >= MaxStamina) return;
	if (TimeSinceLastUsage < StaminaRegenDelay) return;

	bIsRegenerating = true;

	float RegenAmount = StaminaRegenRate * RegenModifier * DeltaTime;
	CurrentStamina = FMath::Min(CurrentStamina + RegenAmount, MaxStamina);

	OnStaminaChanged.Broadcast(CurrentStamina);

	if (bIsExhausted && CurrentStamina >= RecoveryThreshold)
	{
		bIsExhausted = false;
		OnRecovered.Broadcast();
	}

	if (CurrentStamina >= MaxStamina)
	{
		bIsRegenerating = false;
	}
}

void USoftvence_StaminaComponent::UpdateModifiers(float DeltaTime)
{
	if (RegenModifierDuration > 0.0f)
	{
		RegenModifierDuration -= DeltaTime;
        
		if (RegenModifierDuration <= 0.0f)
		{
			RegenModifier = 1.0f;
			RegenModifierDuration = 0.0f;
		}
	}
}