// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupSpawner.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"

// Sets default values
APickupSpawner::APickupSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Needed to give our player a transform so that we can them position it in the level
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

}

// Called when the game starts or when spawned
void APickupSpawner::BeginPlay()
{
	Super::BeginPlay();

    if (!PickupClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("PickupSpawner: No PickupClass assigned!"));
        return;
    }

    UWorld* World = GetWorld();
    if (!World)
        return;

    for (int32 i = 0; i < NumberToSpawn; i++)
    {
        FVector SpawnLocation = GetRandomPointInRadius();
        FRotator SpawnRotation = FRotator::ZeroRotator;

        World->SpawnActor<AActor>(PickupClass, SpawnLocation, SpawnRotation);
    }
	
}

// Called every frame
void APickupSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector APickupSpawner::GetRandomPointInRadius() const
{
	FVector Origin = GetActorLocation();
	FVector RandomOffset = UKismetMathLibrary::RandomUnitVector() * FMath::FRandRange(0.f, SpawnRadius);
	return Origin + RandomOffset;
}

