// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DecisionComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RADARSIM_API UDecisionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDecisionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//Method used to filter out parasite noise after a certain time
	void NoiseFilter(float _dt);

	UFUNCTION()
	void RemoveSavedEntry(class AActor* _actor);

	//Used for visual feebacks
	TArray<class AActor*> savedTargetEntries;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(BlueprintCallable,BlueprintPure)
	TArray<class AActor*> GetSavedTargetEntries() {return savedTargetEntries;};

	void SetRadar(class ARadar* _radar) { detectionOwner = _radar; };
	void SetMissileLauncher(class AMissileLauncher* _missileLauncher) {actionReceiver = _missileLauncher;};

	//Used By Radar
	void AddNoiseEntry(class AActor* _noise, float _dt);
private:

//Actor for location and other info 
//float for timer to filter noise
TMap<class AActor*, float> detectedNoiseMap;

//Lock Parameters
UPROPERTY(EditAnywhere)
float timeBeforeLock = 3.f;
TArray<class AActor*> lockedTargetArray;
//TArray<class AActor*> aimedTargetArray;

UPROPERTY(EditInstanceOnly)
class ARadar* detectionOwner;
UPROPERTY(EditInstanceOnly)
class AMissileLauncher* actionReceiver;

//Tag detected enemies to later find them
FString detectionTag = "detectedEntity";
int32 currentDetectedIndex = 1;


//Noise Filter Parameter
UPROPERTY(EditAnywhere)
float noiseFilterTimerValue = 1.f;
float noiseFilterTimer = 0.f;
float noiseThreshold = noiseFilterTimerValue;




};
