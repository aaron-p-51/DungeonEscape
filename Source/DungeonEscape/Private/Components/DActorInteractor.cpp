// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DActorInteractor.h"

// Engine Includes
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


// Game Includes
#include "DIInteractableActor.h"


// Sets default values for this component's properties
UDActorInteractor::UDActorInteractor()
{
	PrimaryComponentTick.bCanEverTick = true;

	ReachTraceRadius = 10.f;
	MaxReachDistance = 150.f;
	MaxCarrySeperation = 100.f;
}


// Called when the game starts
void UDActorInteractor::BeginPlay()
{
	Super::BeginPlay();

	MaxCarrySeperationSqr = MaxCarrySeperation * MaxCarrySeperation;
}


// Called every frame
void UDActorInteractor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!ParentAttachPoint || !CurrentActor) return;
	
	FVector CurrentActorLocation = CurrentActor->GetActorLocation();
	FVector ParentAttachPointLocation = ParentAttachPoint->GetComponentLocation();
	FRotator ParentAttachPointRotation = ParentAttachPoint->GetComponentRotation();

	if (CurrentActorWithinCarryReach(CurrentActorLocation, ParentAttachPointLocation))
	{
		TranslateCurrentActor(ParentAttachPointLocation, ParentAttachPointRotation);
	}
	else
	{
		ReleaseCurrentActor();
	}
}


bool UDActorInteractor::CurrentActorWithinCarryReach(const FVector& CurrentActorLocation, const FVector& ParentCarryAttachPointLocation) const
{
	float CarryActorSeperationSqr = (CurrentActorLocation - ParentCarryAttachPointLocation).SizeSquared();
	return CarryActorSeperationSqr <= MaxCarrySeperationSqr;
}


void UDActorInteractor::TranslateCurrentActor(const FVector& ParentAttachPointLocation, const FRotator& ParentAttachPointRotation)
{
	FTransform CurrentActorUpdatedTransform;
	CurrentActorUpdatedTransform.SetLocation(ParentAttachPointLocation);
	CurrentActorUpdatedTransform.SetScale3D(CurrentActor->GetActorScale3D());

	// Maintain rotation from when actor was grabbed
	FRotator NewRotation;
	NewRotation.Pitch = PickupRotation.Pitch;
	NewRotation.Yaw = ParentAttachPointRotation.Yaw - PickupRotation.Yaw;
	NewRotation.Roll = ParentAttachPointRotation.Roll - PickupRotation.Roll;
	CurrentActorUpdatedTransform.SetRotation(NewRotation.Quaternion());

	CurrentActor->SetActorTransform(CurrentActorUpdatedTransform, true);
}


void UDActorInteractor::ReleaseCurrentActor()
{
	if (!CurrentActor) return;

	IDIInteractableActor* InteractableActor = Cast<IDIInteractableActor>(CurrentActor);
	if (InteractableActor)
	{
		InteractableActor->SetIsPickedUp(false);
	}

	CurrentActor = nullptr;
	OnCarryActorChange.Broadcast(nullptr);
}
 

bool UDActorInteractor::TryGrabInteractableActor(const FVector& StartGrabLocation, const FRotator& StartGrabRotation)
{
	if (!ParentAttachPoint) return false;

	FVector SphereTraceStart = StartGrabLocation;
	FVector SphereTraceStop = SphereTraceStart + (StartGrabRotation.Vector() * MaxReachDistance);

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(GetOwner());

	FHitResult HitResult;
	bool Hit = UKismetSystemLibrary::SphereTraceSingle(
		GetWorld(),
		StartGrabLocation,
		SphereTraceStop,
		ReachTraceRadius,
		UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Camera),
		false,
		IgnoreActors,
		EDrawDebugTrace::None,
		HitResult,
		true
	);

	if (Hit)
	{
		IDIInteractableActor* InteractableActor = Cast<IDIInteractableActor>(HitResult.GetActor());
		if (InteractableActor)
		{
			InteractableActor->SetIsPickedUp(true);
			CurrentActor = HitResult.GetActor();
			PickupRotation = CurrentActor->GetActorRotation();
			OnCarryActorChange.Broadcast(CurrentActor);
			return true;
		}
	}

	return false;
}