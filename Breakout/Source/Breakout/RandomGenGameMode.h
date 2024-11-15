// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BreakoutGameMode.h"
#include "RandomGenGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BREAKOUT_API ARandomGenGameMode : public ABreakoutGameMode
{
	GENERATED_BODY()

	ARandomGenGameMode(const FObjectInitializer& ObjectInitializer);

	// Override block setup with random generation
	virtual void SetupBlocks_Implementation() override;

protected:
	/**
	 * The available block types and their weights for random generation.
	 * Added "None" as index will result in empty spaces instead of blocks
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<TSubclassOf<ABlock>, int32> BlockWeights;

	// Number of blocks to randomly generate
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 NumBlocks;

	// World location of the top-left-most position in the grid
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Grid Setup")
	FVector GridStartingPosition;

	// Number of grid positions per row
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Grid Setup")
	int32 GridRowWidth;

	// Maximum number of grid rows to prevent overflowing game area
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Grid Setup")
	int32 GridMaxRows;
};
