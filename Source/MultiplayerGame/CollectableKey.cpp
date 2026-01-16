#include "CollectableKey.h"
#include "Net/UnrealNetwork.h"
#include "MultiplayerGameCharacter.h"

ACollectableKey::ACollectableKey()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(RootComp);

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	CapsuleComp->SetupAttachment(RootComp);
	CapsuleComp->SetIsReplicated(true);
	CapsuleComp->SetCollisionProfileName(FName("OverlapAllDynamic"));
	CapsuleComp->SetCapsuleHalfHeight(150.0f);
	CapsuleComp->SetCapsuleRadius(100.0f);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComp);
	Mesh->SetIsReplicated(true);
	Mesh->SetCollisionProfileName(FName("OverlapAllDynamic"));

	CollectAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("Collect Audio"));
	CollectAudio->SetupAttachment(RootComp);
	CollectAudio->SetAutoActivate(false);

	RotationSpeed = 100.0f;
}

void ACollectableKey::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACollectableKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		Mesh->AddRelativeRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));

		TArray<AActor*> OverlappingActors;
		CapsuleComp->GetOverlappingActors(OverlappingActors, AMultiplayerGameCharacter::StaticClass());

		if (OverlappingActors.Num() > 0)
		{
			if (!IsCollected)
			{
				IsCollected = true;
				OnRep_IsCollected();
			}
		}
	}
}

void ACollectableKey::OnRep_IsCollected()
{
	if (HasAuthority())
	{
		UE_LOG(LogTemp, Display, TEXT("OnRep_IsCollected called from the server!"));
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("OnRep_IsCollected called from the client!"))
	}

	Mesh->SetVisibility(!IsCollected);
	CollectAudio->Play();

	if (IsCollected)
	{
		if (KeyHolderRef)
		{
			KeyHolderRef->ActivateKeyMesh();
		}
	}
}

void ACollectableKey::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACollectableKey, IsCollected);
}

