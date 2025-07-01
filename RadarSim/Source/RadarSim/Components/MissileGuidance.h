// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MissileGuidance.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RADARSIM_API UMissileGuidance : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMissileGuidance();

	class AActor* GetTarget() {return target;};
	void SetTarget(class AActor* _target) { target = _target; }
	void SetOwnerMaxSpeed(float _s) {ownerMaxSpeed = _s;}
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//PNG Homing Function
	void AimAtTarget(float _dt);

	//PNG target
	class AActor* target;
	float ownerMaxSpeed;

	//Used to get target direction
	FVector lastTargetPos;
	FVector lastMissilePos;

	FVector GetPredictedLocation(FVector currentPos, FVector lastPos, float _dt);


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
