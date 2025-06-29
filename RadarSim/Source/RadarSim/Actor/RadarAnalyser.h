// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RadarAnalyser.generated.h"

UCLASS()
class RADARSIM_API ARadarAnalyser : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARadarAnalyser();


	void SetRadarAnaylserMaterialParameter(float rotationSpeed,float _dt);

	void SetSavedTargetNameArray(TArray<FName> _newArray) {savedTargetNameArray = _newArray;};

	// Used in saved target UI to display target names
	UFUNCTION(BlueprintPure,BlueprintCallable)
	TArray<FName> GetSavedTargetNameArray() {return savedTargetNameArray;};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* consoleMesh;

	//Radar Saved Entries
	TArray<FName> savedTargetNameArray;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* savedTargetVisualizerMesh;
	UPROPERTY(EditInstanceOnly,BlueprintReadOnly)
	class UWidgetComponent* savedTarget_UI;

	//Radar Vizualizer Material Management
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* radarVisualizerMesh;
	class UMaterialInstanceDynamic* radarVizualizer_MT;
	float radarAngleDegrees = 0;
	UPROPERTY(EditAnywhere)
	float  radarVisualizerSpeedFactor = 0.17;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
