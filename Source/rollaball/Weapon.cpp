// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"



// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AWeapon::OnWeaponBeginOverlap);
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::OnWeaponBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Log, TEXT("Weapon overlapped"));
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, TEXT("Weapon overlapped"));
	//UE_LOG(LogTemp, Log, TEXT("Weapon overlapped"));

	auto character = Cast<ArollaballCharacter>(OtherActor);

	if (character != nullptr)
	{
		if (Holder == nullptr)
		{
			auto playerAvatar = Cast<ArollaballCharacter>(character);

			if (playerAvatar != nullptr)
			{
				Holder = character;
				playerAvatar->AttachWeapon(this);
			}
		}
	}
}