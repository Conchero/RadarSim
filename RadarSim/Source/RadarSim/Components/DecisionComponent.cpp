// Fill out your copyright notice in the Description page of Project Settings.


#include "../Components/DecisionComponent.h"
#include "../Actor/MissileLauncher.h"
#include "../Actor/Radar.h"

// Sets default values for this component's properties
UDecisionComponent::UDecisionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UDecisionComponent::BeginPlay()
{
	Super::BeginPlay();

	if (actionReceiver)
		actionReceiver->OnMissileSent.AddUniqueDynamic(this, &UDecisionComponent::RemoveSavedEntry);
}






// Called every frame
void UDecisionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UDecisionComponent::AddNoiseEntry(TArray<AActor*> _noiseArray)
{
	
	///Decision behavior with noise filtering system
	if (lastActorArray.Num() > 0)
	{
		//Actor array that were in the last detection
		TArray<AActor*> trackedNoiseArray;
		//Actor array that were lost since the last detection
		TArray<AActor*> lostNoiseArray;
		for (AActor* noise : _noiseArray)
		{
			// Compare current detection with last and assign actor to arrays
			lastActorArray.Contains(noise) ? trackedNoiseArray.Add(noise) : lostNoiseArray.Add(noise);
		}


		//If the actor was in the detected noise map increased it's value 
		//If not and it's not a target already locked add it 
		for (AActor* trackedNoise : trackedNoiseArray)
		{
			if (detectedNoiseMap.Contains(trackedNoise))
			{
				detectedNoiseMap[trackedNoise]++;
			}
			else if (!detectedNoiseMap.Contains(trackedNoise)  && !savedTargetEntries.Contains(trackedNoise))
			{
				detectedNoiseMap.Add(trackedNoise);
			}
		}


		//Decrease the number of time the actor was detected if lost
		for (AActor* lostNoise : lostNoiseArray)
		{
			if (detectedNoiseMap.Contains(lostNoise))
			{
				detectedNoiseMap[lostNoise]--;
			}
		}

		//Parasite Noise / Target Lock management
		TArray<AActor*> noiseToRemoveArray;
		TArray<AActor*> noiseToSendArray;
		for (auto& noiseElem : detectedNoiseMap)
		{
			if (noiseElem.Value <= parasiteNoiseThreshold)
			{
				noiseToRemoveArray.Add(noiseElem.Key);
			}

			if (noiseElem.Value >= lockedNoiseThreshold)
			{
				noiseToSendArray.Add(noiseElem.Key);
			}
		}

		//Parasite Noise removal
		for (AActor* noiseToRemove : noiseToRemoveArray)
		{
			detectedNoiseMap.Remove(noiseToRemove);
		}

		//Remove locked target to send it to a specific array
		//Send Actor as target to the action receiver 
		for (AActor* noiseToSend : noiseToSendArray)
		{
			savedTargetEntries.Add(noiseToSend);
			actionReceiver->ReceiveAction(noiseToSend);
			detectedNoiseMap.Remove(noiseToSend);
		}
	}

	//If no Actor were found in the radar detection should empty completly the noise map
	if (_noiseArray.Num() <= 0)
	{
		detectedNoiseMap.Empty(0);
	}

	//Used for comparison
	lastActorArray = _noiseArray;
}


void UDecisionComponent::RemoveSavedEntry(class AActor* _actor)
{
	if (!_actor)
		return;

	int indexToRemove = -1;
	for (int i = 0; i < savedTargetEntries.Num(); i++)
	{
		if (savedTargetEntries[i] && _actor->GetName() == savedTargetEntries[i]->GetName())
		{
			indexToRemove = i;
		}
	}

	if (indexToRemove >= 0)
	{
		savedTargetEntries.RemoveAt(indexToRemove);
	}


}

