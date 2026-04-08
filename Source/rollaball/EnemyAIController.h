// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "EnemyAIController.generated.h"

class UAISenseConfig_Sight;

/**
 * 
 */
UCLASS()
class ROLLABALL_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyAIController();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI") 
	TArray<AActor*> PatrolPoints;
	
	int32 CurrentPatrolIndex;
	bool bIsChasingPlayer = false;
	void MoveToNextPatrolPoint();
	

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	/** Perception component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI")
	UAIPerceptionComponent* PerceptionComp;

	/** Sight configuration */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI")
	UAISenseConfig_Sight* SightConfig;

	/** Called when perception updates */
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

private:
	APawn* ControlledPawn;
	
};
