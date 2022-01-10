// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DIInteractableActor.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDIInteractableActor : public UInterface
{
	GENERATED_BODY()
};


/**
 * Interface used by actors that can be interface with player
 */
class DUNGEONESCAPE_API IDIInteractableActor
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION()
	virtual void SetIsPickedUp(bool Value) = 0;

};
