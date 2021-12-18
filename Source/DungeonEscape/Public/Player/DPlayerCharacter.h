// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DPlayerCharacter.generated.h"


/** Forward declarations */
class UCameraComponent;
class UDActorInteractor;
class USphereComponent;
class ADCellDoorKey;
class ADCellDoor;
class UMatineeCameraShake;


/**
 * Base class for player character
 */
UCLASS()
class DUNGEONESCAPE_API ADPlayerCharacter : public ACharacter
{
	GENERATED_BODY()


/**
 * Members
 */

private:

	/*******************************************************************/
	/* Components */
	/*******************************************************************/

	/** Location where Actor currently held by ActorInteractor will be swept to each frame */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USceneComponent* ObjectCarryLocation;

	/** Interact with Actors that implement IDIInteractableActor */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UDActorInteractor* ActorInteractor;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UCameraComponent* CameraComp;

	/*******************************************************************/
	/* Configuration */
	/*******************************************************************/

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	float WalkSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	float SprintSpeed;

	/*******************************************************************/
	/* State */
	/*******************************************************************/

	UPROPERTY()
	bool bIsCarryingActor;


	/*******************************************************************/
	/* FX */
	/*******************************************************************/

	/** Camera shake FX to play when a cell door opens */
	UPROPERTY(EditDefaultsOnly, Category = "FX|Camera")
	TSubclassOf<UMatineeCameraShake> CellDoorOpenCameraShake;

	/** Camera shake FX to play when a cell door closes */
	UPROPERTY(EditDefaultsOnly, Category = "FX|Camera")
	TSubclassOf<UMatineeCameraShake> CellDoorCloseCameraShake;

	/** Falloff strength for CellDoorOpenCameraShake. Falloff strength should be the distance
	 *  player is from the cell door that opened. The farther away the player is
	 *  the lower the Camera Shake scale will be */
	UPROPERTY(EditDefaultsOnly, Category = "FX|Camera")
	UCurveFloat* CellDoorOpenCameraShakeFalloffCurve;

	/** Falloff strength for CellDoorCloseCameraShake. Falloff strength is the distance
	 *  player is from the cell door that closed. The farther away the player is
	 *  the lower the Camera Shake scale will be */
	UPROPERTY(EditDefaultsOnly, Category = "FX|Camera")
	UCurveFloat* CellDoorCloseCameraShakeFalloffCurve;


	/*******************************************************************/
	/* Gameplay */
	/*******************************************************************/

	/** Derived ADCellDoor class placed in world. Bind events to ECellDoorState changes for camera FX */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	TSubclassOf<ADCellDoor> CellDoorClass;


	/*******************************************************************/
	/* Cached */
	/*******************************************************************/

	/** Cached PlayerCameraManager, used for CameraShake FX */
	UPROPERTY()
	APlayerCameraManager* PlayerCameraManager;


/**
 * Methods
 */

 private:

	/*******************************************************************/
	/* Setup */
	/*******************************************************************/
	
	void SetupActorInteractor();

	void SetupCameraShakeForCellDoorStateChange();

	/*******************************************************************/
	/* Player Input */
	/*******************************************************************/

	/** Player Move input */
	void MoveForward(float Value);
	void MoveRight(float Value);

	/** Player input for ActorInteractor*/
	void PickupActor();
	void ReleaseActor();

	/** Player input for sprinting */
	void StartSprint();
	void StopSprint();


	/*******************************************************************/
	/* Bound Callbacks */
	/*******************************************************************/

	/** Callback for ActorInteractor OnCarryActorChange event */
	UFUNCTION()
	void OnActorInteractorCarryActorChange(AActor* Actor);

	/** Callback for CellDoor state change event. This function is bound to all CellDoors
	 * Used for PlayerCamera shake FX */
	UFUNCTION()
	void OnLevelCellDoorStateChange(AActor* CellDoorActor, ECellDoorState CellDoorState);


protected:

	/* Called when the game starts or when spawned */
	virtual void BeginPlay() override;

	
public:

	/* Sets default values for this character's properties */
	ADPlayerCharacter();

	/* Called to bind functionality to input */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
