// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DPlayerCharacter.h"


// Engine Includes
#include "Camera/CameraComponent.h"
#include "Camera/CameraShake.h"
#include "Camera/PlayerCameraManager.h"
#include "Components/CapsuleComponent.h"
#include "Curves/CurveFloat.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"


// Game Includes
#include "Gameplay/DCellDoor.h"
#include "Gameplay/DCellDoorKey.h"
#include "Components/DActorInteractor.h"


// Sets default values
ADPlayerCharacter::ADPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(GetRootComponent());
	CameraComp->bUsePawnControlRotation = true;

	ObjectCarryLocation = CreateDefaultSubobject<USceneComponent>(TEXT("ObjectCarryLocation"));
	ObjectCarryLocation->SetupAttachment(CameraComp);

	ActorInteractor = CreateDefaultSubobject<UDActorInteractor>(TEXT("ActorInteractor"));
	
	WalkSpeed = 600.f;
	SprintSpeed = 750.f;
	bIsCarryingActor = false;
}


// Called when the game starts or when spawned
void ADPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	SetupActorInteractor();
	SetupCameraShakeForCellDoorStateChange();
}


/*******************************************************************/
/* Setup */
/*******************************************************************/

void ADPlayerCharacter::SetupActorInteractor()
{
	if (ActorInteractor)
	{
		ActorInteractor->SetParentCarryLocation(ObjectCarryLocation);
		ActorInteractor->OnCarryActorChange.AddDynamic(this, &ADPlayerCharacter::OnActorInteractorCarryActorChange);
	}
}


void ADPlayerCharacter::SetupCameraShakeForCellDoorStateChange()
{
	// Bind all World CellDoors OnCellDoorStateChange event to OnLevelCellDoorStateChange callback. Used for camera shake FX
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), CellDoorClass, FoundActors);
	for (auto Actor : FoundActors)
	{
		ADCellDoor* CellDoor = Cast<ADCellDoor>(Actor);
		if (CellDoor)
		{
			CellDoor->OnCellDoorStateChange.AddDynamic(this, &ADPlayerCharacter::OnLevelCellDoorStateChange);
		}
	}

	// Cache PlayerCameraManger
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerCameraManager = PlayerController->PlayerCameraManager;
	}
}


// Called to bind functionality to input
void ADPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookRight", this, &ADPlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ADPlayerCharacter::AddControllerPitchInput);


	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &ADPlayerCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ADPlayerCharacter::StopSprint);

	PlayerInputComponent->BindAction("Pickup", EInputEvent::IE_Pressed, this, &ADPlayerCharacter::PickupActor);
	PlayerInputComponent->BindAction("Pickup", EInputEvent::IE_Released, this, &ADPlayerCharacter::ReleaseActor);
}


/*******************************************************************/
/* Player Input */
/*******************************************************************/

void ADPlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}


void ADPlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}


void ADPlayerCharacter::PickupActor()
{
	if (CameraComp && ActorInteractor)
	{
		ActorInteractor->TryGrabInteractableActor(CameraComp->GetComponentLocation(), CameraComp->GetComponentRotation());
	}
}


void ADPlayerCharacter::ReleaseActor()
{
	if (ActorInteractor)
	{
		ActorInteractor->ReleaseCurrentActor();
	}
}


void ADPlayerCharacter::StartSprint()
{
	if (bIsCarryingActor) return;

	UCharacterMovementComponent* MovementComp = GetCharacterMovement();
	if (MovementComp)
	{
		MovementComp->MaxWalkSpeed = SprintSpeed;
	}
}


void ADPlayerCharacter::StopSprint()
{
	UCharacterMovementComponent* MovementComp = GetCharacterMovement();
	if (MovementComp)
	{
		MovementComp->MaxWalkSpeed = WalkSpeed;
	}
}


/*******************************************************************/
/* Bound Callbacks */
/*******************************************************************/

void ADPlayerCharacter::OnActorInteractorCarryActorChange(AActor* Actor)
{
	bIsCarryingActor = (Actor != nullptr) ? true : false;
}


void ADPlayerCharacter::OnLevelCellDoorStateChange(AActor* CellDoorActor, ECellDoorState CellDoorState)
{
	if (!CellDoorActor || !PlayerCameraManager) return;

	ADCellDoor* CellDoor = Cast<ADCellDoor>(CellDoorActor);
	if (CellDoor)
	{
		float DistanceToCellDoor = FVector::Distance(CellDoorActor->GetActorLocation(), GetActorLocation());

		if (CellDoorState == ECellDoorState::ECDS_Opened && CellDoorOpenCameraShakeFalloffCurve && CellDoorOpenCameraShake)
		{
			// Player CellDoorOpenCameraShake scale based on CellDoorOpenCameraShakeFalloffCurve value. Curve is based on player distance to CellDoor
			float CameraShakeScale = CellDoorOpenCameraShakeFalloffCurve->GetFloatValue(DistanceToCellDoor);
			PlayerCameraManager->StartCameraShake(CellDoorOpenCameraShake, CameraShakeScale);
		}
		else if (CellDoorState == ECellDoorState::ECDS_Closed && CellDoorCloseCameraShakeFalloffCurve && CellDoorCloseCameraShake)
		{
			// Player CellDoorCloseCameraShake scale based on CellDoorCloseCameraShakeFalloffCurve value. Curve is based on player distance to CellDoor
			float CameraShakeScale = CellDoorCloseCameraShakeFalloffCurve->GetFloatValue(DistanceToCellDoor);
			PlayerCameraManager->StartCameraShake(CellDoorCloseCameraShake, CameraShakeScale);
		}
	}
}
