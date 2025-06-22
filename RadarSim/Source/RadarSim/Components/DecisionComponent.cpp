// Fill out your copyright notice in the Description page of Project Settings.


#include "../Components/DecisionComponent.h"

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

	// ...
	
}

void UDecisionComponent::RemoveNoiseEntry(class AActor* _noise)
{

}

void UDecisionComponent::SendAction()
{

}

// Called every frame
void UDecisionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDecisionComponent::AddNoiseEntry(class AActor* _noise)
{

}

