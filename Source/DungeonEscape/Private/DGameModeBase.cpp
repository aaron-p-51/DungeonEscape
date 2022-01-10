// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameModeBase.h"


// Game Includes
#include "Player/DPlayerController.h"


void ADGameModeBase::PlayerEscapeSuccess()
{
	ADPlayerController* PlayerController = GetWorld()->GetFirstPlayerController<ADPlayerController>();
	if (PlayerController)
	{
		PlayerController->OnLevelEscapeSuccess();
	}
}
