// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Missile.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMissileDestroyed, class AActor*, _target);


UCLASS()
class RADARSIM_API AMissile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMissile();

	void OnTargetSent();

	void SetTarget(class AActor* _target);

	
	void SetInitialImpulseForce(float _v) { initialImpulseForce_Meter = _v; };

	FOnMissileDestroyed OnMissileDestroyed;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:

	class AActor* target;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UProjectileMovementComponent* projectileMovementComponent;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* missileMesh;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxCollision;

	UPROPERTY(EditAnywhere)
	float initialImpulseForce_Meter = 2;

	//Used to get target direction
	FVector lastTargetPos;
	FVector lastMissilePos;

	FVector GetPredictedLocation(FVector currentPos, FVector lastPos, float _dt);

	UFUNCTION()
	 void OnComponentBeginOverlap_Action(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor ,class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	 



};
