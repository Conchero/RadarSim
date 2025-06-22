// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MissileLauncher.generated.h"

UCLASS()
class RADARSIM_API AMissileLauncher : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMissileLauncher();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ReceiveAction(class AActor* _targetLocation);

private:

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* missileLauncherMesh;

	UPROPERTY(EditAnywhere, Category = MapsAndSets)
	TArray<class AActor*> targetArray;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AMissile> missileType;
	UPROPERTY(EditAnywhere)
	float fireRate = 5.f;

	bool canShoot = true;

	void FireMissile(class AMissile* _missile);
	void SpawnMissile();

};
