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

	//Filters actor outside active area
	bool CheckPresenceInActiveZone(FVector _noiseLocation);
	float GetAngleFromMainAxisToDetectedNoise(FVector _noiseLocation);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:

	//Used in editor to avoid resizing Action area by hand
	UFUNCTION(BlueprintCallable)
	void ResizeAreaActionVizualizer();

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* radarMesh;

	//Radar Parameter
	UPROPERTY(EditAnywhere)
	float rotationSpeed = 0.08f;
		//Used a mesh to have a cylinder form
		//Saw on wikipedia that action areas of radars where this shape
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* actionArea;
	UPROPERTY(EditAnywhere)
	float activeAngle = 30;
	UPROPERTY(EditAnywhere)
	float actionAreaDiameter_Meter = 30;

	//Component to filter out parasite noise and confirm target
	UPROPERTY(EditAnywhere)
	class UDecisionComponent* decisionComponent;


	//Active and half angle getter
	FVector GetLeftRadarRotatedAxis();
	FVector GetRightRadarRotatedAxis();
	TArray<FVector> GetRadarZoneMainAxisPoints();




};
