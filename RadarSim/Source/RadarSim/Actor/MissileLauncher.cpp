// Fill out your copyright notice in the Description page of Project Settings.


#include "../Actor/MissileLauncher.h"

// Sets default values
AMissileLauncher::AMissileLauncher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	missileLauncherMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	missileLauncherMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMissileLauncher::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMissileLauncher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMissileLauncher::ReceiveAction(class AActor* _targetLocation)
{

}

void AMissileLauncher::FireMissile(class AMissile* _missile)
{

}

void AMissileLauncher::SpawnMissile()
{

}

