// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyEntity.h"
#include "Drones.generated.h"

//Delegate to remove entity from spawn pool
//Could have used this delegate to manage Radar Saved Entries
// But I considered that the radar should not know if the entity aimed is an enemy or not 
//(See PNG Missile Delegate Declaration for more info)


UCLASS()
class RADARSIM_API ADrones : public AEnemyEntity
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADrones();


	void Explode();

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
	UPROPERTY(EditAnywhere)
	float acceptanceRadius = 200;
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
