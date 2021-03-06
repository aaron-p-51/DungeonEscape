// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/DCellDoorTrigger.h"


// Engine Includes
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"


// Game Includes
#include "Gameplay/DCellDoorKey.h"


// Sets default values
ADCellDoorTrigger::ADCellDoorTrigger()
{
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(GetRootComponent());

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerArea"));
	BoxComp->SetupAttachment(GetRootComponent());
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}


// Called when the game starts or when spawned
void ADCellDoorTrigger::BeginPlay()
{
	Super::BeginPlay();

	if (BoxComp)
	{
		BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ADCellDoorTrigger::OnBoxCompBeginOverlap);
		BoxComp->OnComponentEndOverlap.AddDynamic(this, &ADCellDoorTrigger::OnBoxCompEndOverlap);
	}
}


float ADCellDoorTrigger::GetWeightOnTrigger() const
{
	float TotalWeight = 0.f;

	// Add together weight of all CellDoorKeys
	for (const auto& Key : CellDoorKeys)
	{
		if (!Key->GetIsPickedUp())
		{
			UPrimitiveComponent* PrimativeComp = Key->FindComponentByClass<UPrimitiveComponent>();
			if (PrimativeComp)
			{
				TotalWeight += PrimativeComp->GetMass();
			}
		}
	}

	return TotalWeight;
}


void ADCellDoorTrigger::OnBoxCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;

	ADCellDoorKey* CellDoorKey = Cast<ADCellDoorKey>(OtherActor);
	if (CellDoorKey && !CellDoorKeys.Contains(CellDoorKey))
	{
		CellDoorKeys.Add(CellDoorKey);
	}
}


void ADCellDoorTrigger::OnBoxCompEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor) return;

	ADCellDoorKey* CellDoorKey = Cast<ADCellDoorKey>(OtherActor);
	if (CellDoorKey && CellDoorKeys.Contains(CellDoorKey))
	{
		CellDoorKeys.Remove(CellDoorKey);
	}
}

