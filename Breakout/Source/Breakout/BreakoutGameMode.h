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

	/**
	 * Add a ball to the game
	 */
	UFUNCTION(BlueprintCallable)
	void AddBall(ABall* Ball);

	// The widget class to create for showing score and retry button
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameWidget> GameWidgetClass;

protected:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UGameWidget> GameWidget;

	/**
	 * Create the level layout of differently positioned blocks.
	 * All blocks need to be registered by calling RegisterBlock.
	 * Default behavior is to scan level for all pre-spawned blocks
	 */
	UFUNCTION(BlueprintNativeEvent)
	void SetupBlocks();

	/**
	 * Setup initial Balls during level start.
	 * All balls need to be added by calling AddBall.
	 * Default behavior is to scan level for any pre-spawned balls
	 */
	UFUNCTION(BlueprintNativeEvent)
	void SetupBalls();

	UFUNCTION(BlueprintCallable)
	void RemoveBall(const ABall* Ball);

	// Add a Block to be tracked as part of the current level
	UFUNCTION(BlueprintCallable)
	void RegisterBlock(ABlock* Block);

	// Destroy a block
	UFUNCTION(BlueprintCallable)
	void DestroyBlock(const ABlock* Block);

	/**
	 * Setup Paddle and input routing.
	 * Default behavior is to scan level for a pre-spawned paddle
	 */
	UFUNCTION(BlueprintNativeEvent)
	void SetupPaddle();

	UFUNCTION()
	void RestartGame();

	UFUNCTION()
	void ExitGame();

	UFUNCTION()
	void CycleCamera();

	void CheckWinLoseConditions();

	// CameraActors that can server as potential view targets
	UPROPERTY()
	TArray<ACameraActor*> Cameras;

	int32 CurrentCameraIndex = -1;

	UPROPERTY(BlueprintReadOnly)
	int32 TotalScore = 0;

	// All Balls that are currently in the game
	UPROPERTY(BlueprintReadOnly)
	TSet<ABall*> Balls;
	// Remaining blocks in the game
	UPROPERTY(BlueprintReadOnly)
	TSet<ABlock*> Blocks;
};
