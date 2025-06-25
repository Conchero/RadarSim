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
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Magenta, FString::Printf(TEXT("Reloading %f"), reloadTime));
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
		if (Cast<AMissile>(missile))
		{
			missileActorArray.Add(missile);
			missileRelativeTransform.Add(missile->GetRootComponent()->GetRelativeTransform());
		}
	}
}



void AMissileLauncher::CanSendMissile()
{

	if (canShoot && (!is_reloading && missileActorArray.Num() > 0) && targetArray.Num() > 0)
	{
		bool shotFired = false;
		if (targetArray[0])
		{

			shotFired = true;
			canShoot = false;

			LaunchMissile(targetArray[0]);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("target was  null")));
		}

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


		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Oh la la")));


		AMissile* missileToSpawn = GetWorld()->SpawnActor<AMissile>(missileType, missileRelativeTransform[i].GetLocation(), missileRelativeTransform[i].GetRotation().Rotator(), FActorSpawnParameters());

		if (missileToSpawn)
		{

			FAttachmentTransformRules attachRule = FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, true);
			missileToSpawn->AttachToComponent(missileLauncherMesh, attachRule);
			missileActorArray.Add(missileToSpawn);
		}
	}

}

