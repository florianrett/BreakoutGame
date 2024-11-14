// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameWidget.h"
#include "BreakoutGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BREAKOUT_API ABreakoutGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABreakoutGameMode(const FObjectInitializer& FObjectInitializer);

	virtual void BeginPlay() override;

	// The widget class to create for showing score and retry button
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameWidget> GameWidgetClass;

protected:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UGameWidget> GameWidget;

	UFUNCTION()
	void RestartGame();

	UFUNCTION()
	void ExitGame();
	
	
};
