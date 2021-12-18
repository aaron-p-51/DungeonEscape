// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/DCellDoorKey.h"

// Engine Includes
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"


static const int32 ENABLE_OUTLINE_STENCILE = 2;
static const int32 DISABLE_OUTLINE_STENCILE = 0;


// Sets default values
ADCellDoorKey::ADCellDoorKey()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(MeshComp);
	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	MeshComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	InteractIndicatorSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("InteractIndicatorSphereComp"));
	InteractIndicatorSphereComp->SetupAttachment(GetRootComponent());
	InteractIndicatorSphereComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	InteractIndicatorSphereComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	InteractIndicatorSphereComp->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	InteractIndicatorSphereComp->SetGenerateOverlapEvents(true);

	InstructionsWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("InstructionsWidget"));
	InstructionsWidgetComp->SetupAttachment(GetRootComponent());

	bIsPickedUp = false;
	bDisableInstructionsWidget = true;
	bIsFirstCellDoorKey = false;
}


void ADCellDoorKey::BeginPlay()
{
	Super::BeginPlay();

	if (InteractIndicatorSphereComp)
	{
		InteractIndicatorSphereComp->OnComponentBeginOverlap.AddDynamic(this, &ADCellDoorKey::OnInteractIndicatorSphereCompBeginOverlap);
		InteractIndicatorSphereComp->OnComponentEndOverlap.AddDynamic(this, &ADCellDoorKey::OnInteractIndicatorSphereCompEndOverlap);
	}

	if (bIsFirstCellDoorKey)
	{
		EnableInstructionsWidget(true);
		bDisableInstructionsWidget = false;
	}
	else
	{
		EnableInstructionsWidget(false);
		bDisableInstructionsWidget = true;
	}
}


void ADCellDoorKey::SetIsPickedUp(bool IsPickedUp)
{
	bIsPickedUp = IsPickedUp;

	// Stop simulating physics when player is interacting with cell door key
	if (MeshComp)
	{
		MeshComp->SetSimulatePhysics(!bIsPickedUp);
	}

	// Stop outlining mesh when player is carrying, enable outline when player drops CellDoorKey
	if (bIsPickedUp)
	{
		EnableMeshOutline(false);
	}
	else
	{
		EnableMeshOutline(true);
	}

	// If this is the first CellDoorKey hide the InstructionsWidget after picking up CellDoorKey
	if (bIsFirstCellDoorKey && bIsPickedUp && !bDisableInstructionsWidget)
	{
		EnableInstructionsWidget(false);
		bDisableInstructionsWidget = true;
	}
}


void ADCellDoorKey::OnInteractIndicatorSphereCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsPickedUp)
	{
		EnableMeshOutline(true);
	}
}


void ADCellDoorKey::OnInteractIndicatorSphereCompEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	EnableMeshOutline(false);
}


void ADCellDoorKey::EnableMeshOutline(bool Enable)
{
	if (!MeshComp) return;

	MeshComp->SetRenderCustomDepth(Enable);

	int32 StencileValue = (Enable) ? ENABLE_OUTLINE_STENCILE : DISABLE_OUTLINE_STENCILE;
	MeshComp->SetCustomDepthStencilValue(StencileValue);
}


void ADCellDoorKey::EnableInstructionsWidget(bool Enable)
{
	if (!InstructionsWidgetComp) return;

	UUserWidget* Widget = InstructionsWidgetComp->GetUserWidgetObject();
	if (!Widget) return;

	ESlateVisibility Visibility = Enable ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	Widget->SetVisibility(Visibility);
}
