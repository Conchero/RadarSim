// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Drones.generated.h"

UCLASS()
class RADARSIM_API ADrones : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADrones();



	void Explode();	



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly)
	class AActor* movementBoundingBox;

	FVector currentTarget;
	UPROPERTY(EditAnywhere)
	float acceptanceRadius = 200;
	UPROPERTY(EditAnywhere)
	float droneSpeed = 200.f;
		void RandomMovement(float _dt);
	void ChooseNewLocation();

protected:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditInstanceOnly)
	class UStaticMeshComponent* mesh;

	UPROPERTY(EditInstanceOnly)
	class UBoxComponent* boxCollision;


	UPROPERTY(EditAnywhere)
	class UFloatingPawnMovement* floatingPawnMovement;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ADroneController> droneController;
	
private: 
	int sendLocationInfiniteLoopBreaker = 0;
	int loopBreakerLimit = 100;

};
