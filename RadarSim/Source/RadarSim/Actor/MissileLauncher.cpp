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

	fireRate = fireRateValue;
	ammoInLauncher = maxAmmo;
	reloadTime = reloadTimeValue;
}

// Called every frame
void AMissileLauncher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FireMissile(DeltaTime);
}

bool AMissileLauncher::ReceiveAction(class AActor* _target)
{
	targetArray.Add(_target);

	return true;
}

bool AMissileLauncher::FireMissile(float _dt)
{
	if (canShoot && (!is_reloading && ammoInLauncher > 0) && targetArray.Num() > 0)
	{
		bool shotFired = false;
		if (targetArray[0])
		{

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("target was aimed %s"), *targetArray[0]->GetName()));

			SpawnMissile();
			shotFired = true;
			canShoot = false;
			ammoInLauncher--;
			if (ammoInLauncher <= 0)
			{
				is_reloading = true;
			}
		}

		if (shotFired)
		{
			targetArray.RemoveAt(0);
		}
	}


	if (!canShoot)
	{
		fireRate -= _dt;

		if (fireRate <= 0)
		{
			fireRate = fireRateValue;
			canShoot = true;
		}
	}

	if (is_reloading)
	{
		reloadTime -= _dt;
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Magenta, FString::Printf(TEXT("Reloading %f"), reloadTime));
		if (reloadTime <= 0)
		{
			is_reloading = false;
			ammoInLauncher = 6;
			reloadTime = reloadTimeValue;
		}
	}


	if (targetArray.Num() > 0)
	{
		GEngine->AddOnScreenDebugMessage(-0, 5.f, FColor::Red, FString::Printf(TEXT("target Array Missile Launcher")));
		for (AActor* target : targetArray)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("Actor In Array Missile Launcher [%s]"), *target->GetName()));
		}
	}

	return true;

}

void AMissileLauncher::SpawnMissile()
{

}

