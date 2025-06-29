// Fill out your copyright notice in the Description page of Project Settings.


#include "../Actor/RadarAnalyser.h"
#include "Components/WidgetComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
ARadarAnalyser::ARadarAnalyser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root Component");


	consoleMesh = CreateDefaultSubobject<UStaticMeshComponent>("Console Mesh");
	consoleMesh->SetupAttachment(RootComponent);

	savedTargetVisualizerMesh = CreateDefaultSubobject<UStaticMeshComponent>("Saved Target Mesh");
	savedTargetVisualizerMesh->SetupAttachment(RootComponent);

	savedTarget_UI = CreateDefaultSubobject<UWidgetComponent>("Saved Target UI");
	savedTarget_UI->SetupAttachment(RootComponent);
	
	
	radarVisualizerMesh = CreateDefaultSubobject<UStaticMeshComponent>("Radar Visualizer");
	radarVisualizerMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ARadarAnalyser::BeginPlay()
{
	Super::BeginPlay();
	
	radarVizualizer_MT = UMaterialInstanceDynamic::Create(radarVisualizerMesh->GetMaterial(0),this);
	radarVisualizerMesh->SetMaterial(0,radarVizualizer_MT);

}


void ARadarAnalyser::SetRadarAnaylserMaterialParameter(float rotationSpeed,float _dt)
{
	float deltaRotation = (rotationSpeed * radarVisualizerSpeedFactor) * _dt;
	radarAngleDegrees += deltaRotation;
	radarAngleDegrees = FMath::Fmod(radarAngleDegrees, 360.f);

	float radarAngleRadians = FMath::DegreesToRadians(radarAngleDegrees);

	radarVizualizer_MT->SetScalarParameterValue("RadarAngle", radarAngleRadians);

}



// Called every frame
void ARadarAnalyser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

