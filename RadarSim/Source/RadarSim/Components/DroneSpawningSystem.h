// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DroneSpawningSystem.generated.h"




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RADARSIM_API UDroneSpawningSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDroneSpawningSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere)
	float spawnEntityTreshold = 2.f;
	float spawnEntityTimer;

	UPROPERTY(EditAnywhere)
	int32 maxEnemyInMap = 20.f;

	//Replace Later for Root Enemy Classes
	UPROPERTY(VisibleInstanceOnly)
	TArray<class ADrones*> spawnedEntities;

	//Replace Later for Root Enemy Classes
	//This array is to pick a random entity 
	//in an array of possibilities
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class ADrones>> spawnableEntitiesArray;

	class UBoxComponent* spawnableArea;


	UFUNCTION()
	void RemoveEntityFromPool(class ADrones* _target);
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
