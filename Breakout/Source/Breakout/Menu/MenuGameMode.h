// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuWidget.h"
#include "MenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BREAKOUT_API AMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	// The widget class to spawn in the main menu
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMainMenuWidget> MenuWidgetClass;

	// The game level to load when pressing play
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> GameLevel;

	// The game level to load when pressing random play
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> GameLevelRandom;

protected:
	UFUNCTION()
	void StartGame();
	UFUNCTION()
	void StartGameRandom();
	UFUNCTION()
	void ExitGame();
	
	UPROPERTY(BlueprintReadWrite)
	UMainMenuWidget* MenuWidget;

	
	
};
