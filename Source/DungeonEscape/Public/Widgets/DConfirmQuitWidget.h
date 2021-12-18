// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DConfirmQuitWidget.generated.h"

/** Forward declarations */
class UButton;

/**
 * Widget for the player to comfirm they wish to quit the game
 */
UCLASS()
class DUNGEONESCAPE_API UDConfirmQuitWidget : public UUserWidget
{
	GENERATED_BODY()
	
/**
 * Members
 */

private:

	/** Parent widget that spawns this widget. Parent will have IsEnabled set to false when this widget is on Viewport */
	UPROPERTY()
	UWidget* SpawningParentWidget;


protected:

	/**************************************************************************/
	/* Widgets */
	/**************************************************************************/
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* CancelQuitButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* ConfirmQuitButton;

/**
 * Methods
 */
private:

	bool BindWidgetEvents();

	/**************************************************************************/
	/* Widget event bindings */
	/**************************************************************************/
	UFUNCTION()
	void OnCancelQuitButtonClick();

	UFUNCTION()
	void OnConfirmQuitButtonClick();


protected:

	/** Bind widget events */
	virtual bool Initialize() override;


public:
	
	/** Set SpawningParentWidget. Set SpawningParentWidget IsEnabled to false. Add this widget to Viewport */
	void SetUp(UWidget* ParentWidget);
	
};
