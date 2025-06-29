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

	UFUNCTION(BlueprintImplementableEvent)
	void SpawnNiagaraEmitter();


	UFUNCTION(BlueprintCallable)
	void SetMovementBoundingBox(class AActor* _boundingBox) ;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//To fill in BP 
	UPROPERTY(EditInstanceOnly)
	class AActor* movementBoundingBox;


	//Drone Fly Attribute
	FVector currentTarget;
	UPROPERTY(EditAnywhere)
	float acceptanceRadius = 200;
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

};
