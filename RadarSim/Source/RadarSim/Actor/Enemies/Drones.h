// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyEntity.h"
#include "Drones.generated.h"


UCLASS()
class RADARSIM_API ADrones : public AEnemyEntity
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADrones();


	//Call Niagara Emitter
	void Explode();

	//Set The Box this pawn can move in
	UFUNCTION(BlueprintCallable)
	void SetMovementBoundingBox(class UBoxComponent* _boundingBox) ;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//To fill in BP 
	UPROPERTY(EditInstanceOnly)
	class UBoxComponent* movementBoundingBox;


	//Drone Fly Attribute
	FVector currentTarget;
	//Radius around the target point before moving on to the next target
	UPROPERTY(EditAnywhere)
	float acceptanceRadius = 200;

	//Movement Management
	void RandomMovement(float _dt);
	void ChooseNewLocation();

	virtual void Destroyed() override;

protected:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditInstanceOnly)
	class UStaticMeshComponent* mesh;
	UPROPERTY(EditInstanceOnly)
	class UBoxComponent* boxCollision;

	UPROPERTY(EditAnywhere)
	class UFloatingPawnMovement* floatingPawnMovement;

};
