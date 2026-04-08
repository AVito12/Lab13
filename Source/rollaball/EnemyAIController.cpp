// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AEnemyAIController::AEnemyAIController()
{
	//Setup
	CurrentPatrolIndex = 0;
	bIsChasingPlayer = false;
	ControlledPawn = nullptr;
	
	// Create perception component
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));
	SetPerceptionComponent(*PerceptionComp);


	// Create sight config
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 1500.f;
	SightConfig->LoseSightRadius = 1800.f;
	SightConfig->PeripheralVisionAngleDegrees = 70.f;
	SightConfig->SetMaxAge(2.f);

	// Detect only enemies (players)
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	// Register sight sense
	PerceptionComp->ConfigureSense(*SightConfig);
	PerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());

	// Bind perception callback
	PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(
		this, &AEnemyAIController::OnTargetPerceptionUpdated
	);
}


void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ControlledPawn = InPawn;
	
	// Start patrolling immediately
	MoveToNextPatrolPoint();
	
	UE_LOG(LogTemp, Warning, TEXT("AI Possessed Pawn: %s"), *InPawn->GetName());
}

void AEnemyAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{

	if (!Actor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Perception updated: Actor was NULL"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Perception updated: %s"), *Actor->GetName());

	if (!ControlledPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("ControlledPawn is NULL"));
		return;
	}
	
	if (!Actor || !ControlledPawn) return;
	{
		APawn* PlayerPawn = Cast<APawn>(Actor);
		if (!PlayerPawn) return;

		if (Stimulus.WasSuccessfullySensed())
		{
			bIsChasingPlayer = true;
			MoveToActor(PlayerPawn);
		}
		else
		{
			bIsChasingPlayer = false;
			MoveToNextPatrolPoint();
		}
	}
	// If we successfully sensed the player
	if (Stimulus.WasSuccessfullySensed())
	{
		MoveToActor(Actor, 5.f); // Chase player
	}
	else
	{
		StopMovement(); // Lost sight
	}
}

void AEnemyAIController::MoveToNextPatrolPoint()
{
	if (PatrolPoints.Num() == 0) return;

	AActor* NextPoint = PatrolPoints[CurrentPatrolIndex];
	MoveToActor(NextPoint);

	// Cycle to next point
	CurrentPatrolIndex = (CurrentPatrolIndex + 1) % PatrolPoints.Num();
}

void AEnemyAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	// Only continue patrolling if not chasing the player
	if (!bIsChasingPlayer)
	{
		MoveToNextPatrolPoint();
	}
}