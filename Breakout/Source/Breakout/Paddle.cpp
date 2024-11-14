// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle.h"

// Sets default values
APaddle::APaddle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PaddleSize = FVector2D(100.0f, 50.0f);

	Collider = CreateDefaultSubobject<UBoxComponent>("Collider");
	Collider->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	RootComponent = Collider;
}

void APaddle::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	Collider->SetBoxExtent(FVector(PaddleSize.X, 50.f, PaddleSize.Y));
}

// Called every frame
void APaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

