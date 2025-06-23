// Fill out your copyright notice in the Description page of Project Settings.


#include "../Actor/Radar.h"
#include "Components/StaticMeshComponent.h"
#include "../Components/DecisionComponent.h"


enum EMainAxisPoint
{
	START,
	END
};

// Sets default values
ARadar::ARadar()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");


	radarMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	radarMesh->SetupAttachment(RootComponent);

	actionArea = CreateDefaultSubobject<UStaticMeshComponent>("Action Area");
	actionArea->SetupAttachment(RootComponent),
		actionArea->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);


	decisionComponent = CreateDefaultSubobject<UDecisionComponent>("Decision Component");

}

// Called when the game starts or when spawned
void ARadar::BeginPlay()
{
	Super::BeginPlay();
	ResizeAreaActionVizualizer();
}

// Called every frame
void ARadar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> overlappingActors;
	actionArea->GetOverlappingActors(overlappingActors);

	for (AActor* actor : overlappingActors)
	{
		if (actor != this)
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, actor->GetName());
		

		if (CheckPresenceInActiveZone(actor->GetActorLocation()))
		{

			if (decisionComponent)
			{
				decisionComponent->AddNoiseEntry(actor);
			}

			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Green, FString::Printf(TEXT("Actor in zone at angle %f"), GetAngleFromMainAxisToDetectedNoise(actor->GetActorLocation())));

		}

	}



	FRotator radarSpin = FRotator(radarMesh->GetComponentRotation().Pitch, radarMesh->GetComponentRotation().Yaw + (rotationSpeed * DeltaTime), radarMesh->GetComponentRotation().Roll);
	radarMesh->SetWorldRotation(radarSpin);

	DrawDebugLine(GetWorld(), GetRadarZoneMainAxisPoints()[START], GetRadarZoneMainAxisPoints()[END], FColor::Green, false, -1, 0U, 10.f);
	DrawDebugLine(GetWorld(), GetRadarZoneMainAxisPoints()[START], GetLeftRadarRotatedAxis(), FColor::Cyan, false, -1, 0U, 5.f);
	DrawDebugLine(GetWorld(), GetRadarZoneMainAxisPoints()[START], GetRightRadarRotatedAxis(), FColor::Cyan, false, -1, 0U, 5.f);
}



bool ARadar::CheckPresenceInActiveZone(FVector _noiseLocation)
{
	bool isInZone = GetAngleFromMainAxisToDetectedNoise(_noiseLocation) < activeAngle;
	return isInZone;
}

float ARadar::GetAngleFromMainAxisToDetectedNoise(FVector _noiseLocation)
{
	FVector mainDirection = GetRadarZoneMainAxisPoints()[END] - GetRadarZoneMainAxisPoints()[START];
	FVector noiseDirection = _noiseLocation - GetRadarZoneMainAxisPoints()[START];

	mainDirection.Normalize();
	noiseDirection.Normalize();

	float dotProduct = FVector::DotProduct(mainDirection, noiseDirection);

	float angle  = FMath::Acos(FVector::DotProduct(mainDirection, noiseDirection));
	return FMath::Abs(angle*180/3.14);
	
}

void ARadar::CreateFalseNoise()
{
	if (FMath::RandRange(0, 100) < noiseRandChance)
	{
		if (decisionComponent)
		{
		}
	}
}

void ARadar::ResizeAreaActionVizualizer()
{
	actionArea->SetWorldScale3D(FVector(1 * actionAreaDiameter_Meter, 1 * actionAreaDiameter_Meter, actionArea->GetComponentTransform().GetScale3D().Z));
}



TArray<FVector> ARadar::GetRadarZoneMainAxisPoints()
{
	FVector startPoint = radarMesh->GetComponentLocation();
	FVector endPoint = radarMesh->GetComponentLocation() + (radarMesh->GetForwardVector() * (actionAreaDiameter_Meter * 100));

	TArray<FVector> mainAxisPoint;
	mainAxisPoint.Add(startPoint);
	mainAxisPoint.Add(endPoint);

	return mainAxisPoint;
}

FVector ARadar::GetLeftRadarRotatedAxis()
{

	float radianAngle = activeAngle * 3.14 / 180;
	FVector direction = GetRadarZoneMainAxisPoints()[END] - GetRadarZoneMainAxisPoints()[START];

	FVector endPointLeft = FVector(
		GetRadarZoneMainAxisPoints()[START].X + ((direction.X * FMath::Cos(-radianAngle)) - (direction.Y * FMath::Sin(-radianAngle)))
		, GetRadarZoneMainAxisPoints()[START].Y + ((direction.X * FMath::Sin(-radianAngle)) + (direction.Y * FMath::Cos(-radianAngle))),
		GetRadarZoneMainAxisPoints()[END].Z);

	return endPointLeft;

}

FVector ARadar::GetRightRadarRotatedAxis()
{
	float radianAngle = activeAngle * 3.14 / 180;
	FVector direction = GetRadarZoneMainAxisPoints()[END] - GetRadarZoneMainAxisPoints()[START];


	FVector endPointRight = FVector(
		GetRadarZoneMainAxisPoints()[START].X + ((direction.X * FMath::Cos(radianAngle)) - (direction.Y * FMath::Sin(radianAngle)))
		, GetRadarZoneMainAxisPoints()[START].Y + ((direction.X * FMath::Sin(radianAngle)) + (direction.Y * FMath::Cos(radianAngle))),
		GetRadarZoneMainAxisPoints()[END].Z);


	return endPointRight;
}

