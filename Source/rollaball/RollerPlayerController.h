// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "rollaballCharacter.h"
#include "GameFramework/PlayerController.h"
#include "RollerPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ROLLABALL_API ARollerPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
    
public:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputMappingContext* DefaultMappingContext;
    
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* MoveAction;
    
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* LookAction;
    
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* JumpAction;
    
private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartJump();
	void StopJump();
	
};
