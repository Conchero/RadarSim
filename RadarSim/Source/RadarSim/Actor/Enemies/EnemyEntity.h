// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnemyEntity.generated.h"


//Delegate to remove entity from spawn pool
//Could have used this delegate to manage Radar Saved Entries
// But I considered that the radar should not know if the entity aimed is an enemy or not 
//(See PNG Missile Delegate Declaration for more info)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDestroyed, class AEnemyEntity*, _e);

UCLASS()
class RADARSIM_API AEnemyEntity : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyEntity();
	FOnEnemyDestroyed OnEnemyDestroyed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
