// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DIInteractableActor.h"
#include "GameFramework/Actor.h"
#include "DCellDoorKey.generated.h"

/** Forward declarations */
class UStaticMeshComponent;
class USphereComponent;
class UWidgetComponent;


/**
 * Base class for cell door keys
 */
UCLASS()
class DUNGEONESCAPE_API ADCellDoorKey : public AActor, public IDIInteractableActor
{
	GENERATED_BODY()
	

/**
 * Members
 */

private:

	/*******************************************************************/
	/* Components */
	/*******************************************************************/

	/** Base mesh for cell door key */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;

	/** When player in overlapping enable outline on mesh */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USphereComponent* InteractIndicatorSphereComp;

	/** Affordance for play to know how to interact with this actor */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UWidgetComponent* InstructionsWidgetComp;


	/*******************************************************************/
	/* Configuration */
	/*******************************************************************/

	/** First Cell Door key is the first key player sees. Will show InstructionsWidget */
	UPROPERTY(EditAnywhere, Category = "Config")
	bool bIsFirstCellDoorKey;


	/*******************************************************************/
	/* State */
	/*******************************************************************/

	UPROPERTY()
	bool bIsPickedUp;

	UPROPERTY()
	bool bDisableInstructionsWidget;

	
 /**
  * Methods
  */

private:

	/** Enable Outline on MeshComp, done with RenderCustomDepth, PostProcessingMaterial */
	void EnableMeshOutline(bool Enable);

	/** Only CellDoorKey with bIsFirstCellDoorKey set to true shall show affordance widget. */
	void EnableInstructionsWidget(bool Enable);

	/** Bound callbacks for InteractIndicatorSphereComp OnBegin and OnEnd overlap events */
	UFUNCTION()
	void OnInteractIndicatorSphereCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnInteractIndicatorSphereCompEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:

	/* Called when the game starts or when spawned */
	virtual void BeginPlay() override;


public:	

	// Sets default values for this actor's properties
	ADCellDoorKey();

	/** Implements IDIInteractableActor */
	virtual void SetIsPickedUp(bool IsPickedUp) override;

	bool GetIsPickedUp() const { return bIsPickedUp; }

};
