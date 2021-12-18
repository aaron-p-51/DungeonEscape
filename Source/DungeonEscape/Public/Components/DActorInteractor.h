// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DActorInteractor.generated.h"

/** Declare delegate for when actor interacting with changes  */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorChange, AActor*, Actor);

/**
 * Actor component used to interact with Actors that implement IDIInteractableActor 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UDActorInteractor : public UActorComponent
{
	GENERATED_BODY()


/**
 * Members
 */

private:
	
	/*******************************************************************/
	/* Configuration */
	/*******************************************************************/

	/** Parent actor attach point, CurrentActor will sweep to ParentAttachPoint during Tick() */
	UPROPERTY(EditDefaultsOnly, Category = "Config")
	USceneComponent* ParentAttachPoint;

	/** Max distance CurrentActor can get from ParentAttachPoint, when value is exceeded CurrentActor will be released */
	UPROPERTY(EditDefaultsOnly, Category = "Config")
	float MaxCarrySeperation;

	/** Trace radius when attempting interact with actors */
	UPROPERTY(EditDefaultsOnly, Category = "Config")
	float ReachTraceRadius;

	/** Max reach distance for ActorInteractor to look for actors */
	UPROPERTY(EditDefaultsOnly, Category = "Config")
	float MaxReachDistance;

	/** Cached max allowable distance between CurrentActor and ParentAttachPoint */
	UPROPERTY()
	float MaxCarrySeperationSqr;


	/*******************************************************************/
	/* State */
	/*******************************************************************/

	/** Current Actor owner is interacting with */
	UPROPERTY(VisibleAnywhere, Category = "State")
	AActor* CurrentActor;

	/** Rotation of CurrentActor when assigned */
	UPROPERTY(VisibleAnywhere)
	FRotator PickupRotation;


public:
	
	/** Delegate for CurrentActor changes  */
	FOnActorChange OnCarryActorChange;


 /**
  * Methods
  */

private:

	/** Check if CurrentActor is within distance from ParentAttachPoint */
	bool CurrentActorWithinCarryReach(const FVector& CurrentActorLocation, const FVector& ParentCarryAttachPointLocation) const;

	/** Sweep CurrentActor to ParentAttachPoint, maintain actors rotation when actor was grabbed  */
	void TranslateCurrentActor(const FVector& ParentAttachPointLocation, const FRotator& ParentAttachPointRotation);


protected:

	// Called when the game starts
	virtual void BeginPlay() override;


public:	

	/* Sets default values for this component's properties */
	UDActorInteractor();

	/** Release CurrentActor */
	void ReleaseCurrentActor();

	/**
	 * Attempt to interact with actor. To interact with an actor, the actor must implement IDIInteractableActor.
	 * 
	 * @param StartGrabLocation			Location to start searching for actor to grab
	 * @param StopGrabLocation			Location to stop searching for actor to grab
	 * 
	 * @return Successfully grabbed new actor
	 */
	bool TryGrabInteractableActor(const FVector& StartGrabLocation, const FRotator& StartGrabRotation);

	/** Get CurrentActor */
	AActor* GetCurrentInteractableActor() const { return CurrentActor; }

	/** Set the ParentAttachPoint, must be called and set before attempting to interface with actors*/
	void SetParentCarryLocation(USceneComponent* AttachPoint) { ParentAttachPoint = AttachPoint; }

	/* Check CurrentActor is within reach limits set by MaxCarrySeperation. Sweep CurrentActor to updated ParentAttachPoint transform  */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};
