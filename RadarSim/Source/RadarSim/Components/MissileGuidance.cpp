// Fill out your copyright notice in the Description page of Project Settings.


#include "../Components/MissileGuidance.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UMissileGuidance::UMissileGuidance()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//Tick Optimisation
	PrimaryComponentTick.TickGroup = TG_PostPhysics;
}


// Called when the game starts
void UMissileGuidance::BeginPlay()
{
	Super::BeginPlay();
}


void UMissileGuidance::AimAtTarget(float _dt)
{
	if (!GetOwner())
	return;

	if (target)
	{
		//Target predicted location in the next frame
		FVector targetDirection = GetPredictedLocation(target->GetActorLocation(), lastTargetPos, _dt);
		//Actor/Owner predicted location in the next frame
		FVector missileDirection = GetPredictedLocation(GetOwner()->GetActorLocation(), lastMissilePos, _dt);

		//Vector between target and missile location
		FVector pushForce = (targetDirection - missileDirection);
		//Slow the rocket down 
		float maxSpeed = (1 / ownerMaxSpeed) * 100;
		//As the rocket approach target it slows down to get more precise
		float absoluteDistWithTarget = FMath::Abs(FVector::Dist(GetOwner()->GetActorLocation(), target->GetActorLocation())) / maxSpeed;
	
		//Get the direction not location 
		pushForce.Normalize();

		// Rocket Movement
		GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + (pushForce * absoluteDistWithTarget));

		// For Visual purpose making the rocket "look" at the target
		FRotator lookAtTarget = UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(), target->GetActorLocation());
		GetOwner()->SetActorRotation(lookAtTarget);

		//Used in trajectory calculation
		lastTargetPos = target->GetActorLocation();
		lastMissilePos = GetOwner()->GetActorLocation();
	}
}

// Called every frame
void UMissileGuidance::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AimAtTarget(DeltaTime);
}


FVector UMissileGuidance::GetPredictedLocation(FVector currentPos, FVector lastPos, float _dt)
{

	//PNG System
	FVector dir = (currentPos - lastPos);
	//v=d/t
	float speed = FVector::Dist(currentPos, lastPos) / _dt;
	FVector predictedLocation = currentPos + (dir * speed);

	return  predictedLocation;

}