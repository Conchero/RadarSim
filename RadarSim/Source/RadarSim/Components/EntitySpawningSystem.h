// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EntitySpawningSystem.generated.h"




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RADARSIM_API UEntitySpawningSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEntitySpawningSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere)
	float spawnEntityTreshold = 2.f;
	float spawnEntityTimer;

	//max Pool size
	UPROPERTY(EditAnywhere)
	int32 maxEnemyInMap = 20.f;

	UPROPERTY(VisibleInstanceOnly)
	TArray<class AEnemyEntity*> spawnedEntities;

	//This array is to pick a random entity 
	//in an array of possibilities
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class AEnemyEntity>> spawnableEntitiesArray;

	class UBoxComponent* spawnableArea;


	UFUNCTION()
	void RemoveEntityFromPool(class AEnemyEntity* _target);
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
