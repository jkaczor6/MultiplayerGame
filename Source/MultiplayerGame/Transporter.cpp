#include "Transporter.h"
#include "PressurePlate.h"

UTransporter::UTransporter()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);

	MoveTime = 3.0f;
	ActivatedTriggerCount = 0;

	ArePointsSet = false;
	StartPoint = FVector::Zero();
	EndPoint = FVector::Zero();
}


void UTransporter::BeginPlay()
{
	Super::BeginPlay();
	
	for (AActor* TA : TriggerActors)
	{
		APressurePlate* PressurePlate = Cast<APressurePlate>(TA);
		if (PressurePlate)
		{
			PressurePlate->OnActivated.AddDynamic(this, &UTransporter::OnPressurePlateActivated);
			PressurePlate->OnDeactivated.AddDynamic(this, &UTransporter::OnPressurePlateDeactivated);
		}
	}
}


void UTransporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TriggerActors.Num() > 0)
	{
		AllTriggerActorsTriggered = (ActivatedTriggerCount >= TriggerActors.Num());
		if (AllTriggerActorsTriggered)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, TEXT("AllTriggerActorsTriggered!"));
		}
	}

	AActor* MyOwner = GetOwner();
	if (MyOwner && MyOwner->HasAuthority() && ArePointsSet)
	{
		FVector CurrentLocation = MyOwner->GetActorLocation();
		float Speed = FVector::Distance(StartPoint, EndPoint) / MoveTime;

		FVector TargetLocation = AllTriggerActorsTriggered ? EndPoint : StartPoint;
		if (!CurrentLocation.Equals(TargetLocation))
		{
			FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
			MyOwner->SetActorLocation(NewLocation);
		}
	}
}

void UTransporter::SetPoints(FVector Point1, FVector Point2)
{
	if (Point1.Equals(Point2)) return;

	StartPoint = Point1;
	EndPoint = Point2;
	ArePointsSet = true;
}

void UTransporter::OnPressurePlateActivated()
{
	ActivatedTriggerCount++;
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, FString::Printf(TEXT("Activated: %d"), ActivatedTriggerCount));
}

void UTransporter::OnPressurePlateDeactivated()
{
	ActivatedTriggerCount--;
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, FString::Printf(TEXT("Deactivated: %d"), ActivatedTriggerCount));
}

