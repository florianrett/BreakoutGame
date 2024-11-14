// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWidget.h"

void UGameWidget::SetScore(int32 NewScore)
{
	ScoreText->SetText(FText::Format(FText::AsCultureInvariant(TEXT("Score: {0}")), NewScore));
}

void UGameWidget::SetButtonVisibility(bool bVisible)
{
	const ESlateVisibility NewVisibility = bVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	ExitButton->SetVisibility(NewVisibility);
	RestartButton->SetVisibility(NewVisibility);
}
