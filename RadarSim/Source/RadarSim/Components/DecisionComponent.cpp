// Fill out your copyright notice in the Description page of Project Settings.


#include "../Components/DecisionComponent.h"
#include "../Actor/MissileLauncher.h"

// Sets default values for this component's properties
UDecisionComponent::UDecisionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UDecisionComponent::BeginPlay()
{
	Super::BeginPlay();

	noiseFilterTimer = noiseFilterTimerValue;
	noiseThreshold = noiseFilterTimerValue;
}






// Called every frame
void UDecisionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	NoiseFilter(DeltaTime);

	if (detectedNoiseMap.Num() > 0)
	{

		for (auto& noiseElem : detectedNoiseMap)
		{
			AActor* noise = noiseElem.Key;
			float noiseTime = noiseElem.Value;
		}
	}

}

void UDecisionComponent::AddNoiseEntry(class AActor* _noise, float _dt)
{

	///
	/// Logic :
	/// Each Time the radar detect something it sends it to the decision component 
	/// If a new entity is found then we add a tag to find it back 
	/// If not a new entity add the delta time 
	/// ---> Go to NoiseFilter() to continue
	if (_noise)
	{
		bool newEntity = false;

		//Checks if actor has detection tag
		if (_noise->Tags.Num() <= 0)
		{
			newEntity = true;
		}
		else if (!_noise->Tags[0].ToString().Contains(detectionTag))
		{
			//TODO: if entity has !empty tag move it to last place
			newEntity = true;
		}

		if (newEntity)
		{
			FName noiseTag = FName(detectionTag + "-" + FString::FromInt(currentDetectedIndex++));
			if (_noise->Tags.Num() > 0)
			{
				_noise->Tags[0] = (noiseTag);
			}
			else
			{
				_noise->Tags.Add(noiseTag);
			}
			detectedNoiseMap.Emplace(_noise, 0.f);

		}
		else
		{
			for (auto& noiseElem : detectedNoiseMap)
			{
				AActor* noise = noiseElem.Key;
				float noiseTime = noiseElem.Value;

				if (_noise->Tags.Contains(noise->Tags[0]))
				{
					noiseTime += _dt;
					noiseElem.Value = noiseTime;
				}
			}
		}

	}
}



void UDecisionComponent::NoiseFilter(float _dt)
{

	///
	/// Logic :
	///When the noise filter arrives at 0 we check if any noise detected was parasite 
	/// If it is we remove it 
	/// If it's we send it as a target
	noiseFilterTimer -= _dt;
	if (noiseFilterTimer <= 0.0)
	{
		if (detectedNoiseMap.Num() > 0)
		{
			//Arrays to allow dynamic shrinking
			TArray<AActor*> toRemove;
			TArray<AActor*> toSend;
			for (auto& noiseElem : detectedNoiseMap)
			{
				AActor* noise = noiseElem.Key;
				float noiseTime = noiseElem.Value;

				//If actor disappear (wasn't detected any more by radar) 
				// noise time should be under noise Threshold/(2)->security to not remove potential target
				if (noiseTime <= noiseThreshold / 2)
				{
					toRemove.Add(noise);
				}
				else
				{
					toSend.Add(noise);
				}



			}

			detectedNoiseMap.Empty(0);

			for (AActor* noise : toRemove)
			{
				noise->Tags.RemoveAt(0);
				detectedNoiseMap.Remove(noise);
			}

			for (AActor* target : toSend)
			{
				actionReceiver->ReceiveAction(target);
			}

		}
		noiseFilterTimer = noiseFilterTimerValue;
	}


}


