// CopyrightNotice=© 2025 Softvence. TPS — Development Build. All rights reserved


#include "Player/Softvence_PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Player/Softvence_PlayerCharacter.h"


// =====================================================================================================================
// ---> CONSTRUCTOR & UNREAL CALLBACK <---
// =====================================================================================================================

ASoftvence_PlayerController::ASoftvence_PlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASoftvence_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (DefaultMappingContext)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ASoftvence_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Movement
		if (MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::HandleMove);
		}
		if (LookAction)
		{
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::HandleLook);
		}
		
		if (JumpAction)
		{
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::HandleJump);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ThisClass::HandleJumpReleased);
		}
		if (SprintAction)
		{
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ThisClass::HandleSprint);
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ThisClass::HandleSprintReleased);
		}
		
		if (CrouchAction)
		{
			EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ThisClass::HandleCrouch);
		}
		if (ProneAction)
		{
			EnhancedInputComponent->BindAction(ProneAction, ETriggerEvent::Started, this, &ThisClass::HandleProne);
		}
	}
}


// =====================================================================================================================
// ---> NET<---
// =====================================================================================================================

void ASoftvence_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ControlledCharacter = Cast<ASoftvence_PlayerCharacter>(InPawn);
}

void ASoftvence_PlayerController::OnUnPossess()
{
	Super::OnUnPossess();
	ControlledCharacter = nullptr;
}




// =====================================================================================================================
// ---> MOVEMENT INPUT<---
// =====================================================================================================================


void ASoftvence_PlayerController::HandleMove(const FInputActionValue& Value)
{
	if (!ControlledCharacter) return;
    
	FVector2D MovementVector = Value.Get<FVector2D>();
	ControlledCharacter->HandleMoveInput(MovementVector);
}

void ASoftvence_PlayerController::HandleLook(const FInputActionValue& Value)
{
	if (!ControlledCharacter) return;
    
	FVector2D LookVector = Value.Get<FVector2D>();
	LookVector *= CameraSensitivity;
    
	if (bInvertY)
	{
		LookVector.Y *= -1.0f;
	}
    
	ControlledCharacter->HandleLookInput(LookVector);
}

void ASoftvence_PlayerController::HandleJump(const FInputActionValue& Value)
{
	if (!ControlledCharacter) return;
    
	ControlledCharacter->HandleJumpInput(true);
}

void ASoftvence_PlayerController::HandleJumpReleased(const FInputActionValue& Value)
{
	if (!ControlledCharacter) return;
    
	ControlledCharacter->HandleJumpInput(false);
}

void ASoftvence_PlayerController::HandleSprint(const FInputActionValue& Value)
{
	if (!ControlledCharacter) return;
    
	ControlledCharacter->HandleSprintInput(true);
}

void ASoftvence_PlayerController::HandleSprintReleased(const FInputActionValue& Value)
{
	if (!ControlledCharacter) return;
    
	ControlledCharacter->HandleSprintInput(false);
}

void ASoftvence_PlayerController::HandleCrouch(const FInputActionValue& Value)
{
	if (!ControlledCharacter) return;
    
	ControlledCharacter->HandleCrouchInput();
}

void ASoftvence_PlayerController::HandleProne(const FInputActionValue& Value)
{
	if (!ControlledCharacter) return;
    
	ControlledCharacter->HandleProneInput();
}


// =====================================================================================================================
// ---> COMBAT INPUT <---
// =====================================================================================================================