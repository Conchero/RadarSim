// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Actor/Enemies/Drones.h"

// Sets default values
ADrones::ADrones()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADrones::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADrones::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

