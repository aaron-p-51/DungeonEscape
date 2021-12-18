// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DEscapeSuccessVolume.generated.h"

/** Forward declarations */
class UBoxComponent;

/**
 * Base class for volume to signify player successfully escaping
 */
UCLASS()
class DUNGEONESCAPE_API ADEscapeSuccessVolume : public AActor
{
	GENERATED_BODY()
	

/**
 * Members
 */
private:

	/*******************************************************************/
	/* Components */
	/*******************************************************************/

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* BoxComp;


/**
 * Methods
 */

 private:

	UFUNCTION()
	void OnBoxCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** The game ends when player overlaps BoxComp. Inform Gamemode of when overlap happens */
	void InformGameModeEscapeSuccess();


protected:

	/* Called when the game starts or when spawned */
	virtual void BeginPlay() override;


public:

	/* Sets default values for this actor's properties */
	ADEscapeSuccessVolume();

};
