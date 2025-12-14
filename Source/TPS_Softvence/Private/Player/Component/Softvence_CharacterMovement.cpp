// CopyrightNotice=© 2025 Softvence. TPS — Development Build. All rights reserved


#include "TPS_Softvence/Public/Player/Component/Softvence_CharacterMovement.h"


// Sets default values for this component's properties
USoftvence_CharacterMovement::USoftvence_CharacterMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USoftvence_CharacterMovement::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USoftvence_CharacterMovement::TickComponent(float DeltaTime, ELevelTick TickType,
                                                 FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

