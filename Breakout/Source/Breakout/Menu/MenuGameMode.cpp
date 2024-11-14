// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void AMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(MenuWidgetClass))
	{
		MenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MenuWidgetClass, FName(TEXT("MenuWidget")));
		if (MenuWidget)
		{
			MenuWidget->AddToViewport();
			MenuWidget->PlayButton->OnClicked.AddDynamic(this, &AMenuGameMode::StartGame);
			MenuWidget->ExitButton->OnClicked.AddDynamic(this, &AMenuGameMode::ExitGame);
			GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("MenuWidgetClass is not set!"));
	}
}

void AMenuGameMode::StartGame()
{
	if (GameLevel.IsNull())
	{
		UE_LOG(LogTemp, Error, TEXT("Specified GameLevel is not valid!"));

		return;
	}
	
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, GameLevel, true);
}

void AMenuGameMode::ExitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}
