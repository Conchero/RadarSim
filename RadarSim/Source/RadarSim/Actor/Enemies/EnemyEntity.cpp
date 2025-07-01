// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Actor/Enemies/EnemyEntity.h"

// Sets default values
AEnemyEntity::AEnemyEntity()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyEntity::BeginPlay()
{
	Super::BeginPlay();

}

void AEnemyEntity::Destroyed()
{
	OnEnemyDestroyed.Broadcast(this);
	Super::Destroyed();
}

// Called every frame
void AEnemyEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

