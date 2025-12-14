// CopyrightNotice=© 2025 Softvence. TPS — Development Build. All rights reserved


#include "TPS_Softvence/Public/Player/Softvence_PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"
#include "Player/Component/Softvence_CharacterMovement.h"


// =====================================================================================================================
// ---> CONSTRUCTOR & UNREAL CALLBACK <---
// =====================================================================================================================
ASoftvence_PlayerCharacter::ASoftvence_PlayerCharacter(const FObjectInitializer& ObjectInitializer) : 
Super(ObjectInitializer.SetDefaultSubobjectClass<USoftvence_CharacterMovement>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	
	// Config Capsule
	GetCapsuleComponent()->InitCapsuleSize(36.f, 92.f);
	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 420.0f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
	
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->SetCrouchedHalfHeight(60.0f);
	
	
	// Create Camera Boom
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = DefaultCameraDistance;
	SpringArmComponent->SocketOffset = DefaultCameraOffset;
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->CameraLagSpeed = 10.0f;
	SpringArmComponent->bEnableCameraRotationLag = true;
	SpringArmComponent->CameraRotationLagSpeed = 15.0f;

	// Create Follow Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	FollowCamera->FieldOfView = DefaultFOV;

}

void ASoftvence_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	
	UpdateMovementSpeed();
}


// =====================================================================================================================
// ---> NET <---
// =====================================================================================================================

void ASoftvence_PlayerCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ASoftvence_PlayerCharacter, bIsAiming);
	DOREPLIFETIME(ASoftvence_PlayerCharacter, bIsFiring);
	DOREPLIFETIME(ASoftvence_PlayerCharacter, bIsSprinting);
	DOREPLIFETIME(ASoftvence_PlayerCharacter, bIsInCover);
	DOREPLIFETIME(ASoftvence_PlayerCharacter, bIsReloading);
	DOREPLIFETIME(ASoftvence_PlayerCharacter, CurrentStance);
	DOREPLIFETIME(ASoftvence_PlayerCharacter, CurrentLeanAmount);
}


// =====================================================================================================================
// ---> INPUT HANDLERS <---
// =====================================================================================================================

void ASoftvence_PlayerCharacter::HandleMoveInput(FVector2D MovementVector)
{
	CurrentMovementInput = MovementVector;

	if (Controller != nullptr)
	{
		// Get forward and right vectors
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Add movement
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ASoftvence_PlayerCharacter::HandleLookInput(FVector2D LookVector)
{
	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}

void ASoftvence_PlayerCharacter::HandleJumpInput(bool bPressed)
{
	if (bPressed)
	{
		if (CurrentStance == EMovementStance::Crouching)
		{
			UnCrouch();
			CurrentStance = EMovementStance::Standing;
		}
		else if (CurrentStance == EMovementStance::Prone)
		{
			// Exit Prone
			CurrentStance = EMovementStance::Crouching;
			Crouch();
		}
		else
		{
			Jump();
		}
	}
	else
	{
		StopJumping();
	}
}

void ASoftvence_PlayerCharacter::HandleSprintInput(bool bSprinting)
{
	if (bSprinting && CurrentStance == EMovementStance::Standing && !bIsAiming)
	{
		bIsSprinting = true;
		//StopAiming();
	}
	else
	{
		bIsSprinting = false;
	}
	
	UpdateMovementSpeed();
}

void ASoftvence_PlayerCharacter::HandleCrouchInput()
{
	if (CurrentStance == EMovementStance::Standing)
	{
		Crouch();
		CurrentStance = EMovementStance::Crouching;
		bIsSprinting = false;
	}
	else if (CurrentStance == EMovementStance::Crouching)
	{
		UnCrouch();
		CurrentStance = EMovementStance::Standing;
	}
	else if (CurrentStance == EMovementStance::Prone)
	{
		// Go to crouch from prone
		CurrentStance = EMovementStance::Crouching;
		Crouch();
	}
	
	UpdateMovementSpeed();
}

void ASoftvence_PlayerCharacter::HandleProneInput()
{
	if (CurrentStance == EMovementStance::Prone)
	{
		CurrentStance = EMovementStance::Crouching;
		Crouch();
	}
	else
	{
		CurrentStance = EMovementStance::Prone;
		bIsSprinting = false;
		// Additional prone logic would go here (capsule resize, etc.)
	}
	UpdateMovementSpeed();
}




// =====================================================================================================================
// ---> WEAPON <---
// =====================================================================================================================


void ASoftvence_PlayerCharacter::HandleFireInput(bool bFiring)
{
}

void ASoftvence_PlayerCharacter::HandleAimInput(bool bAiming)
{
}


// =====================================================================================================================
// ---> INTERNAL METHODS <---
// =====================================================================================================================


void ASoftvence_PlayerCharacter::UpdateMovementSpeed()
{
	float TargetSpeed = WalkSpeed;
    
	if (bIsSprinting)
	{
		TargetSpeed = SprintSpeed;
	}
	else if (CurrentStance == EMovementStance::Crouching)
	{
		TargetSpeed = CrouchSpeed;
	}
	else if (CurrentStance == EMovementStance::Prone)
	{
		TargetSpeed = ProneSpeed;
	}
    
	if (bIsAiming)
	{
		TargetSpeed *= AimingSpeedMultiplier;
	}
    
	GetCharacterMovement()->MaxWalkSpeed = TargetSpeed;
}


