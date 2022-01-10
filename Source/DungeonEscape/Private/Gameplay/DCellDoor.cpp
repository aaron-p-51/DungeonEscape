// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/DCellDoor.h"

// Engine Includes
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"


// Game Includes
#include "DGameModeBase.h"
#include "Gameplay/DCellDoorTrigger.h"


// Sets default values
ADCellDoor::ADCellDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootComp);

	CellDoorStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CellDoorStaticMesh"));
	CellDoorStaticMeshComp->SetupAttachment(GetRootComponent());

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BlockingBoxComp"));
	BoxComp->SetupAttachment(GetRootComponent());
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxComp->SetCollisionResponseToAllChannels(ECR_Block);

	CellDoorState = ECellDoorState::ECDS_Closed;
	bDebugForceGateOpen = false;
}


// Called when the game starts or when spawned
void ADCellDoor::BeginPlay()
{
	Super::BeginPlay();

	if (CellDoorStaticMeshComp)
	{
		InitialCellDoorHeight = CellDoorStaticMeshComp->GetComponentLocation().Z;
	}

#if WITH_EDITOR

	ADGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode<ADGameModeBase>();
	if (GameModeBase && GameModeBase->GetForceAllCellDoorsOpen())
	{
		bDebugForceGateOpen = true;
	}

#endif
}


// Called every frame
void ADCellDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ProcessDoorOpenCloseState();
}


void ADCellDoor::ProcessDoorOpenCloseState()
{
	if (CellDoorState == ECellDoorState::ECDS_Opening || CellDoorState == ECellDoorState::ECDS_Closing) return;

	float Weight = 0.f;

#if WITH_EDITOR
	
	if (bDebugForceGateOpen)
	{
		Weight = FLT_MAX;
	}
	else
	{
		Weight = CalculateTotalWeightOnTriggers();
	}

#else

	Weight = CalculateTotalWeightOnTriggers();

#endif

	if (CellDoorState == ECellDoorState::ECDS_Closed && Weight >= WeightToOpenCell)
	{
		OpenCellDoor();
	}
	else if (CellDoorState == ECellDoorState::ECDS_Opened && Weight < WeightToOpenCell)
	{
		CloseCellDoor();
	}
}


float ADCellDoor::CalculateTotalWeightOnTriggers() const
{
	float WeightOnTriggers = 0.f;

	for (const auto& Trigger : CellDoorTriggers)
	{
		WeightOnTriggers += Trigger->GetWeightOnTrigger();
	}

	return WeightOnTriggers;
}


void ADCellDoor::OnUpdateCellDoorHeight(float CellDoorHeightOffset)
{
	if (!CellDoorStaticMeshComp) return;

	// Change CellDoor height based on CellDoorHeightOffset in relation to InitialCellDoorHeight
	FVector CurrentCellDoorLocation = CellDoorStaticMeshComp->GetComponentLocation();
	float NewCellDoorHeight = CellDoorHeightOffset + InitialCellDoorHeight;
	FVector NewCellDoorLocation = FVector(CurrentCellDoorLocation.X, CurrentCellDoorLocation.Y, NewCellDoorHeight);

	CellDoorStaticMeshComp->SetWorldLocation(NewCellDoorLocation);
}


void ADCellDoor::OnFinishCellDoorOpened()
{
	CellDoorState = ECellDoorState::ECDS_Opened;
	OnCellDoorStateChange.Broadcast(this, CellDoorState);

	// Allow player and PhysicsBodies (CellDoorKeys) to pass through the cell door
	if (BoxComp)
	{
		BoxComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Ignore);
		BoxComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	}
}


void ADCellDoor::OnFinishedCellDoorClosed()
{
	CellDoorState = ECellDoorState::ECDS_Closed;
	OnCellDoorStateChange.Broadcast(this, CellDoorState);
}


void ADCellDoor::OpenCellDoor()
{
	CellDoorState = ECellDoorState::ECDS_Opening;
	OnCellDoorStateChange.Broadcast(this, CellDoorState);

	BP_OnOpenCellDoor();
}


void ADCellDoor::CloseCellDoor()
{
	CellDoorState = ECellDoorState::ECDS_Closing;
	OnCellDoorStateChange.Broadcast(this, CellDoorState);

	// Block player and PhysicsBodies (CellDoorKeys) from passing through the cell door
	if (BoxComp)
	{
		BoxComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Block);
		BoxComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	}

	BP_OnCloseCellDoor();
}
