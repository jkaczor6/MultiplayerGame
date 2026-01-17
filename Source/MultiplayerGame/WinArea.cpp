#include "WinArea.h"
#include "MultiplayerGameCharacter.h"

AWinArea::AWinArea()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	WinAreaBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(WinAreaBox);

	WinCondition = false;
}

void AWinArea::BeginPlay()
{
	Super::BeginPlay();
	
}
void AWinArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		if (!WinCondition)
		{
			TArray<AActor*> OverlappingActors;
			WinAreaBox->GetOverlappingActors(OverlappingActors, AMultiplayerGameCharacter::StaticClass());

			WinCondition = (OverlappingActors.Num() == 2);
			if (WinCondition)
			{
				UE_LOG(LogTemp, Display, TEXT("WIN"));
				MulticastRPCWin();
			}
		}
	}
}

void AWinArea::MulticastRPCWin_Implementation()
{
	OnWinCondition.Broadcast();
}

