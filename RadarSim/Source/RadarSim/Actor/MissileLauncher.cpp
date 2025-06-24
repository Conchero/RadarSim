// Fill out your copyright notice in the Description page of Project Settings.


#include "../Actor/MissileLauncher.h"
#include "Projectiles/Missile.h"
#include "Components/SceneComponent.h"
#include "Kismet/BlueprintFunctionLibrary.h"

// Sets default values
AMissileLauncher::AMissileLauncher()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");


	missileLauncherMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	missileLauncherMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMissileLauncher::BeginPlay()
{
	Super::BeginPlay();

	fireRate = fireRateValue;
	reloadTime = reloadTimeValue;

}

// Called every frame
void AMissileLauncher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MissileManagement(DeltaTime);

}

bool AMissileLauncher::ReceiveAction(class AActor* _target)
{
	targetArray.Add(_target);

	return true;
}

bool AMissileLauncher::MissileManagement(float _dt)
{
	if (canShoot && (!is_reloading && missileActorArray.Num() > 0) && targetArray.Num() > 0)
	{
		bool shotFired = false;
		if (targetArray[0])
		{

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("target was aimed %s"), *targetArray[0]->GetName()));

			shotFired = true;
			canShoot = false;

			LaunchMissile();
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





void AMissileLauncher::GetMissileAttachedToMissileLauncherFromStart(TArray<class AMissile*> missiles)
{
	if (missiles.Num() <= 0)
		return;

	for (AMissile* missile : missiles)
	{
		if (Cast<AMissile>(missile))
		{

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("alors salut ")));

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("Actor Name %s, relative transform = %s"), *missile->GetName(), *missile->GetRootComponent()->GetRelativeTransform().ToString()));

			missileActorArray.Add(missile);
			missileRelativeTransform.Add(missile->GetRootComponent()->GetRelativeTransform());
		}
	}
}

void AMissileLauncher::LaunchMissile()
{

	if (missileActorArray.Num() <= 0)
		return;

	int32 lastIndex = missileActorArray.Num() - 1;
	if (lastIndex < missileActorArray.Num())
	{
		AMissile* missileToDestroy = missileActorArray[lastIndex];
		missileActorArray.RemoveAt(lastIndex);
		
		if (missileToDestroy)
		missileToDestroy->Destroy();
	}


	if (missileActorArray.Num() <= 0)
	is_reloading = true;

}


