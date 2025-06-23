// Fill out your copyright notice in the Description page of Project Settings.


#include "../Components/DecisionComponent.h"
#include "../Actor/MissileLauncher.h"

// Sets default values for this component's properties
UDecisionComponent::UDecisionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDecisionComponent::BeginPlay()
{
	Super::BeginPlay();

	noiseFilterTimer = noiseFilterTimerValue;

}



	
		

// Called every frame
void UDecisionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ConfirmTarget(DeltaTime);
	NoiseFilter(DeltaTime);


	if (detectedNoiseMap.Num() > 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Green, FString::Printf(TEXT("Noise Map")));
		for (auto& noiseElem : detectedNoiseMap)
		{
			AActor* noise = noiseElem.Key;
			float noiseTime = noiseElem.Value;
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Green, FString::Printf(TEXT("Actor [%s], Time[%f]"), *noise->GetName(), noiseTime));
		}
	}


	//if (lockedTargetArray.Num() > 0)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("Locked Array")));
	//	for (int i = 0; i < lockedTargetArray.Num(); i++)
	//	{
	//		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("Actor [%s], Index[%d]"), *lockedTargetArray[i]->GetName(), i));
	//	}
	//}




}

void UDecisionComponent::AddNoiseEntry(class AActor* _noise)
{
	if (_noise)
	{
		bool newEntity = false;
		if (_noise->Tags.Num() <= 0)
		{
			newEntity = true;
		}
		else if (!_noise->Tags[0].ToString().Contains(detectionTag))
		{
			newEntity = true;
		}

		if (newEntity)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("Entry Detected")));

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
			noiseFilterTimer = noiseFilterTimerValue;
		}
	}
}



void UDecisionComponent::NoiseFilter(float _dt)
{

	UE_LOG(LogTemp, Warning, TEXT("Noise Filter"));

	noiseFilterTimer -= _dt;
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Magenta, FString::Printf(TEXT("Noise filter value %f"), noiseFilterTimer));

	if (noiseFilterTimer <= 0.f)
	{

		if (detectedNoiseMap.Num() > 0)
		{
			for (auto& noiseElem : detectedNoiseMap)
			{
				AActor* noise = noiseElem.Key;
				float noiseTime = noiseElem.Value;


				if (noiseTime <= 0)
				{
					RemoveNoiseEntry(noise);
				}
			}

			noiseFilterTimer = noiseFilterTimerValue;
		}
	}
	else {
		noiseFilterTimer = noiseFilterTimerValue;
	}

}


void UDecisionComponent::ConfirmTarget(float _dt)
{
	TMap<AActor*, float> newDetectionWithoutTarget;

	if (detectedNoiseMap.Num() > 0)
	{
		for (auto& noiseElem : detectedNoiseMap)
		{
			AActor* noise = noiseElem.Key;
			float noiseTime = noiseElem.Value;

		     noiseTime += _dt;
			noiseElem.Value = noiseTime;

			if (noise && noiseTime >= timeBeforeLock)
			{
				actionReceiver->ReceiveAction(noise);
			}
			else
			{
				newDetectionWithoutTarget.Emplace(noise,noiseTime);
			}
		}
	}


	detectedNoiseMap = newDetectionWithoutTarget;
}

void UDecisionComponent::RemoveNoiseEntry(class AActor* _noise)
{
	if (detectedNoiseMap.Num() > 0)
	{
		for (auto& noiseElem : detectedNoiseMap)
		{
			AActor* noise = noiseElem.Key;
			float noiseTime = noiseElem.Value;

			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("Noise removed")));

			if (_noise->Tags.Contains(noise->Tags[0]))
			{
				detectedNoiseMap.Remove(_noise);
			}
		}
	}
}