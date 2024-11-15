// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomGenGameMode.h"
#include "Block.h"

ARandomGenGameMode::ARandomGenGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	GridStartingPosition = FVector(-950, 0, 1850);
	GridRowWidth = 20;
	GridMaxRows = 15;

	NumBlocks = 10;
}

void ARandomGenGameMode::SetupBlocks_Implementation()
{
	// Create a list with multiple occurrences per block type according to specified weights 
	TArray<TSubclassOf<ABlock>> WeightedList;
	for (TTuple<TSubclassOf<ABlock>, int> Pair : BlockWeights)
	{
		for (int i = 0; i < Pair.Value; ++i)
		{
			WeightedList.Add(Pair.Key);
		}
	}
	const int SumWeights = WeightedList.Num();

	if (SumWeights == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("There are no block types specified for random generation!"));
		return;
	}
	for (int i = 0; i < NumBlocks; ++i)
	{
		int Row = i / GridRowWidth;
		int Column = i % GridRowWidth;
		if (Row >= GridMaxRows)
			break; // Stop generation when maximum row is reached

		TSubclassOf<ABlock> BlockType = WeightedList[FMath::RandRange(0, SumWeights - 1)];
		if (IsValid(BlockType))
		{
			const FVector BlockPosition = GridStartingPosition + FVector(Column * 100, 0, Row * -100);
			if (ABlock* NewBlock = Cast<ABlock>(GetWorld()->SpawnActor(BlockType, &BlockPosition)))
			{
				RegisterBlock(NewBlock);
			}			
		}		
	}
}
