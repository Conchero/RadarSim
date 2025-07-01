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

	UFUNCTION()
	void RemoveSavedEntry(class AActor* _actor);

	//Used for visaul feebacks and to not consider locked enemy as a new entry
	TArray<class AActor*> savedTargetEntries;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<class AActor*> GetSavedTargetEntries() { return savedTargetEntries; };

	void SetRadar(class ARadar* _radar) { detectionOwner = _radar; };
	void SetMissileLauncher(class AMissileLauncher* _missileLauncher) { actionReceiver = _missileLauncher; };

	//Used By Radar
	void AddNoiseEntry(TArray<class AActor*> _noise);

private:

	//Actor for location and other info 
	//float for timer to filter noise
	TMap<class AActor*, int32> detectedNoiseMap;
	TArray<class AActor*> lastActorArray;


	//Amount of time before an actor is considered a parasite noise or a target
	UPROPERTY(EditAnywhere)
	int32 parasiteNoiseThreshold = -1;
	UPROPERTY(EditAnywhere)
	int32 lockedNoiseThreshold = 2;


	UPROPERTY(EditInstanceOnly)
	class ARadar* detectionOwner;
	UPROPERTY(EditInstanceOnly)
	class AMissileLauncher* actionReceiver;





};
