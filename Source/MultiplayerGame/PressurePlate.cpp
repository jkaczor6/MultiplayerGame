// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate.h"

// Sets default values
APressurePlate::APressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);

	Activated = false;
	
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(RootComp);

	TriggerShape = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Trigger Shape"));
	TriggerShape->SetupAttachment(RootComp);
	TriggerShape->SetIsReplicated(true);

	auto TriggerMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder"));
	if (TriggerMeshAsset.Succeeded())
	{
		TriggerShape->SetStaticMesh(TriggerMeshAsset.Object);
		TriggerShape->SetRelativeScale3D(FVector(3.3f, 3.3f, 0.2f));
		TriggerShape->SetRelativeLocation(FVector(0.0f, 0.0f, 10.0f));
	}

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComp);
	Mesh->SetIsReplicated(true);

	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/Stylized_Egypt/Meshes/building/SM_building_part_08.SM_building_part_08"));
	if (MeshAsset.Succeeded())
	{
		Mesh->SetStaticMesh(MeshAsset.Object);
		Mesh->SetRelativeScale3D(FVector(4.0f, 4.0f, 0.5f));
		Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, 7.2f));
	}
	
	Transporter = CreateDefaultSubobject<UTransporter>(TEXT("Transporter"));
	Transporter->MoveTime = 0.25f;
	Transporter->OwnerIsTriggerActor = true;
}

// Called when the game starts or when spawned
void APressurePlate::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerShape->SetVisibility(false);
	TriggerShape->SetCollisionProfileName(FName("OverlapAll"));

	FVector Point2 = GetActorLocation() + FVector(0.0f, 0.0f, -10.0f);
	Transporter->SetPoints(GetActorLocation(), Point2);
}

// Called every frame
void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		TArray<AActor*> OverlappingActors;
		AActor* TriggerActor = 0;
		TriggerShape->GetOverlappingActors(OverlappingActors);

		for (int i = 0; i < OverlappingActors.Num(); i++)
		{
			AActor* A = OverlappingActors[i];
			if (A->ActorHasTag("TriggerActor"))
			{
				TriggerActor = OverlappingActors[i];
				break;
			}

		}
		if (TriggerActor)
		{
			if (!Activated)
			{
				Activated = true;
				//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, TEXT("Activated"));
				OnActivated.Broadcast();
			}
		}
		else
		{
			if (Activated)
			{
				Activated = false;
				//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, TEXT("Deactivated"));
				OnDeactivated.Broadcast();
			}
		}
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, FString::Printf(TEXT("Name: %s"), *TriggerActor->GetName()));
	}
}

