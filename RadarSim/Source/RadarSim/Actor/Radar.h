// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Radar.generated.h"

UCLASS()
class RADARSIM_API ARadar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARadar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	bool CheckPresenceInActiveZone(FVector _noiseLocation);

	float GetAngleFromMainAxisToDetectedNoise(FVector _noiseLocation);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	


private:

UFUNCTION(BlueprintCallable)
void ResizeAreaActionVizualizer();

UPROPERTY(EditAnywhere)
class UStaticMeshComponent* radarMesh;


UPROPERTY(EditAnywhere)
float rotationSpeed = 0.08f;
UPROPERTY(EditAnywhere)
class UStaticMeshComponent* actionArea;
UPROPERTY(EditAnywhere)
float activeAngle = 30;
UPROPERTY(EditAnywhere)
float actionAreaDiameter_Meter = 30;


UPROPERTY(EditAnywhere)
class UDecisionComponent* decisionComponent;


FVector GetLeftRadarRotatedAxis();
FVector GetRightRadarRotatedAxis();
TArray<FVector> GetRadarZoneMainAxisPoints();




};
