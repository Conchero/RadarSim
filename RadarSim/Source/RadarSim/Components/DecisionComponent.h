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


	void RemoveNoiseEntry(class AActor* _noise);
	void SendAction();
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetRadar(class ARadar* _radar) { detectionOwner = _radar; };
	void SetMissileLauncher(class AMissileLauncher* _missileLauncher) {actionReceiver = _missileLauncher;};


	void AddNoiseEntry(class AActor* _noise);
private:

TMap<class AActor*, float> detectedNoiseMap;
UPROPERTY(EditAnywhere)
float timeBeforeLock;
TArray<class AActor*> lockedTargetArray;

UPROPERTY(EditInstanceOnly)
class ARadar* detectionOwner;
UPROPERTY(EditInstanceOnly)
class AMissileLauncher* actionReceiver;

};
