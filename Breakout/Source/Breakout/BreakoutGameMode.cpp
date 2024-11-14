// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakoutGameMode.h"
#include "BreakoutPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Menu/MenuGameMode.h"

ABreakoutGameMode::ABreakoutGameMode(const FObjectInitializer& FObjectInitializer) : Super(FObjectInitializer)
{
	PlayerControllerClass = ABreakoutPlayerController::StaticClass();
}

void ABreakoutGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(GameWidgetClass))
	{
		GameWidget = CreateWidget<UGameWidget>(GetWorld(), GameWidgetClass, FName(TEXT("GameWidget")));
		if (GameWidget)
		{
			GameWidget->SetButtonVisibility(false);
			GameWidget->SetScore(0);
			GameWidget->AddToViewport();
			GameWidget->RestartButton->OnClicked.AddDynamic(this, &ABreakoutGameMode::RestartGame);
			GameWidget->ExitButton->OnClicked.AddDynamic(this, &ABreakoutGameMode::ExitGame);
			GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GameWidgetClass is not set!"));
	}
}

void ABreakoutGameMode::RestartGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(UGameplayStatics::GetCurrentLevelName(this)), false);
}

void ABreakoutGameMode::ExitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}
