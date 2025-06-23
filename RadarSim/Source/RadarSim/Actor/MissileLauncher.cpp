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
	FireMissile();
}

bool AMissileLauncher::ReceiveAction(class AActor* _target)
{
	targetArray.Add(_target);

	return true;
}

bool AMissileLauncher::FireMissile()
{
	if (canShoot && targetArray.Num() > 0)
	{
		bool shotFired = false;
		if (targetArray[0])
		{

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("target was hit %s"), *targetArray[0]->GetName()));

			SpawnMissile();
			shotFired = true;
		}

		if (shotFired)
		{
			targetArray.RemoveAt(0);
		}
	}

	if (targetArray.Num() > 0)
	{

		GEngine->AddOnScreenDebugMessage(-0, 5.f, FColor::Red, FString::Printf(TEXT("target Array Missile Launcher")));
		for (AActor* target : targetArray)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("Actor [%s]"), *target->GetName()));
		}
	}

	return true;

}

void AMissileLauncher::SpawnMissile()
{

}

