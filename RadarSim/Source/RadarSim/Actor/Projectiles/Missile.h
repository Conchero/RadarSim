// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Missile.generated.h"




UCLASS()
class RADARSIM_API AMissile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMissile();

	void OnTargetSent();

	void SetTarget(class AActor* _target);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:

	class AActor* target;


	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* projectileMovementComponent;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* missileMesh;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxCollision;

	UPROPERTY(EditAnywhere)
	float initialImpulseForce_Meter = 2;

	UPROPERTY(EditAnywhere)
	float onGoingImpulseForce_Meter = 2;


	UPROPERTY(EditAnywhere)
	float fuel = 10.f;


	UFUNCTION()
	 void OnComponentBeginOverlap_Action(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor ,class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	 



};
