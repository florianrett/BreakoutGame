// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameWidget.generated.h"

/**
 * 
 */
UCLASS()
class BREAKOUT_API UGameWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> RestartButton;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> ExitButton;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> CameraSwitchButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> ResultText;	

	void SetScore(int32 NewScore);

	void SetButtonVisibility(bool bVisible);

	void SetResultText(const FString& Result);
	
};
