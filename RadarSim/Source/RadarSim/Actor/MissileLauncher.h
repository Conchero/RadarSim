// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MissileLauncher.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMissileSent, class AActor*, target);


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

	//Used in BP for editor spawn button 
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TSubclassOf<class AMissile> GetMissileType() { return missileType; }

	//TODO: Make it a component ---- Missile management - Tick function
	bool MissileManagement(float _dt);
	void FireRateManagement(float _dt);
	void ReloadManagement(float _dt);

	//TODO: Make it a component ---- Missile management - functions
	void CanSendMissile();
	void LaunchMissile(class AActor* _target);
	void Reload();


	//Get Missiles spawned in editor and linked them to missile array
	UFUNCTION(BlueprintCallable)
	void GetMissileAttachedToMissileLauncherFromStart(TArray<class AMissile*> missiles);

	UFUNCTION()
	void RemovedEntryOnDestroy(class AActor* _target);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool ReceiveAction(class AActor* _targetLocation);

	FOnMissileSent OnMissileSent;
protected:
	/// Missile Launcher Attribute
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* missileLauncherMesh;

	UPROPERTY(VisibleAnywhere, Category = MapsAndSets)
	TArray<class AActor*> targetArray;

	UPROPERTY(EditAnywhere, Category = "Missile")
	TSubclassOf<class AMissile> missileType;

	float fireRate = 0.f;
	UPROPERTY(EditAnywhere)
	float fireRateValue = 1.5f;


	float reloadTime = 0.f;
	UPROPERTY(EditAnywhere)
	float reloadTimeValue = 5.f;
	bool is_reloading =false;

	bool canShoot = true;


	UPROPERTY(VisibleInstanceOnly, Category="Missile")
	TArray<class AMissile*> missileActorArray;
	UPROPERTY(VisibleInstanceOnly, Category="Missile")
	TArray<FTransform> missileRelativeTransform;


};
