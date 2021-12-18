// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DCellDoor.generated.h"


/** Forward declarations */
class ADCellDoorTrigger;
class UStaticMeshComponent;
class UBoxComponent;
class UParticleSystem;


/**
 * States for Cell Door
 */
UENUM(BlueprintType)
enum class ECellDoorState : uint8
{
	ECDS_Closed		UMETA(DisplayName = "Closed"),
	ECDS_Opening	UMETA(DisplayName = "Opening"),
	ECDS_Opened		UMETA(DisplayName = "Opened"),
	ECDS_Closing	UMETA(DisplayName = "Closing")
};

/** Decalre delegate for CellDoorState change */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCellDoorStateChange, AActor*, CellDoor, ECellDoorState, NewState);


/**
 * Base class for Cell Doors. See derived BP event graph for cell door height change via timelines.
 */
UCLASS()
class DUNGEONESCAPE_API ADCellDoor : public AActor
{
	GENERATED_BODY()


/**
 * Members
 */

private:

	/*******************************************************************/
	/* Components */
	/*******************************************************************/

	/** CellDoorStaticMeshComp will move around RootComp */
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USceneComponent* RootComp;

	/** Cell door Mesh */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* CellDoorStaticMeshComp;

	/** Blocking collisions when cell door is not open */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UBoxComponent* BoxComp;


	/*******************************************************************/
	/* Configuration */
	/*******************************************************************/

	/** Triggers to open cell door */
	UPROPERTY(EditAnywhere, Category = "Config")
	TArray<ADCellDoorTrigger*> CellDoorTriggers;

	/** Total weight that must be applied to CellDoorTriggers in any combination to open CellDoor  */
	UPROPERTY(EditAnywhere, Category = "Config")
	float WeightToOpenCell;

	/** Height of cell door set on BeginPlay. Used as cell door closed height */
	UPROPERTY()
	float InitialCellDoorHeight;


	/*******************************************************************/
	/* State */
	/*******************************************************************/

	/** Current state of this cell door */
	UPROPERTY()
	ECellDoorState CellDoorState;


	/*******************************************************************/
	/* Debud */
	/*******************************************************************/

	/** Force this cell door open regardless of weight applied to triggers */
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool bDebugForceGateOpen;


public:

	/** Delegate for Cell door state change */
	FOnCellDoorStateChange OnCellDoorStateChange;


/**
 * Methods
 */

private:

	/** Check the current weight on all triggers and current CellDoorState. Calls functions to Open/Close cell door if conditions are met */
	void ProcessDoorOpenCloseState();

	float CalculateTotalWeightOnTriggers() const;

	void OpenCellDoor();
	void CloseCellDoor();


public:

	/* Sets default values for this actor's properties */
	ADCellDoor();

	/* Called every frame */
	virtual void Tick(float DeltaTime) override;


protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Blueprint event for controlling cell door height triggering event based on cell door changing through states. */
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnOpenCellDoor"))
	void BP_OnOpenCellDoor();

	/** Blueprint event for controlling cell door height triggering event based on cell door changing through states */
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnCloseCellDoor"))
	void BP_OnCloseCellDoor();

	/** Update the current of the cell door. */
	UFUNCTION(BlueprintCallable)
	void OnUpdateCellDoorHeight(float CellDoorHeightOffset);

	/** Must be called when cell door reaches the fully open position */
	UFUNCTION(BlueprintCallable)
	void OnFinishCellDoorOpened();

	/** Must be called when cell door reaches the fully closed position */
	UFUNCTION(BlueprintCallable)
	void OnFinishedCellDoorClosed();

};
