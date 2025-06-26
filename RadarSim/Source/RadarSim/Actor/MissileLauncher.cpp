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
	CanSendMissile();
	FireRateManagement(_dt);
	ReloadManagement(_dt);
	return true;
}





void AMissileLauncher::FireRateManagement(float _dt)
{

	if (!canShoot)
	{
		fireRate -= _dt;

		if (fireRate <= 0)
		{
			fireRate = fireRateValue;
			canShoot = true;
		}
	}
}

void AMissileLauncher::ReloadManagement(float _dt)
{
	if (is_reloading)
	{
		reloadTime -= _dt;
		if (reloadTime <= 0)
		{
			Reload();
			is_reloading = false;
			reloadTime = reloadTimeValue;
		}
	}

}

void AMissileLauncher::GetMissileAttachedToMissileLauncherFromStart(TArray<class AMissile*> missiles)
{
	if (missiles.Num() <= 0)
		return;

	for (AMissile* missile : missiles)
	{
		//Should already be missile actor but for security purpose made a cast
		if (Cast<AMissile>(missile))
		{
			missileActorArray.Add(missile);
			//Save relative transform for later reloading
			missileRelativeTransform.Add(missile->GetRootComponent()->GetRelativeTransform());
		}
	}
}



void AMissileLauncher::CanSendMissile()
{

	if (canShoot && (!is_reloading && missileActorArray.Num() > 0) && targetArray.Num() > 0)
	{
		bool shotFired = false;
		//First In, First Out Logic 
		if (targetArray[0])
		{

			shotFired = true;
			canShoot = false;

			LaunchMissile(targetArray[0]);
		}
		else
		{
		}


		//Don't remove target if it couldn't shoot rocker for any reason
		if (shotFired)
		{
			targetArray.RemoveAt(0);
		}
	}
}


void AMissileLauncher::LaunchMissile(AActor* _target)
{


	if (missileActorArray.Num() <= 0 || !_target)
		return;


	//Last In First Out
	int32 lastIndex = missileActorArray.Num() - 1;
	if (lastIndex < missileActorArray.Num())
	{
		AMissile* missileToDestroy = missileActorArray[lastIndex];
		missileActorArray.RemoveAt(lastIndex);

		if (missileToDestroy)
		{
			missileToDestroy->SetTarget(_target);
		}
		else
		{
		}

	}


	if (missileActorArray.Num() <= 0)
		is_reloading = true;

}

void AMissileLauncher::Reload()
{

	if (missileRelativeTransform.Num() <= 0)
		return;


	for (int i = 0; i < missileRelativeTransform.Num(); i++)
	{
		AMissile* missileToSpawn = GetWorld()->SpawnActor<AMissile>(missileType, missileRelativeTransform[i].GetLocation(), missileRelativeTransform[i].GetRotation().Rotator(), FActorSpawnParameters());

		if (missileToSpawn)
		{
			FAttachmentTransformRules attachRule = FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, true);
			missileToSpawn->AttachToComponent(missileLauncherMesh, attachRule);
			missileActorArray.Add(missileToSpawn);
		}
	}

}

