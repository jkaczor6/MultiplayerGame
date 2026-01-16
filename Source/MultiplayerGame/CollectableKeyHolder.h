#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "CollectableKeyHolder.generated.h"

UCLASS()
class MULTIPLAYERGAME_API ACollectableKeyHolder : public AActor
{
	GENERATED_BODY()
	
public:	
	ACollectableKeyHolder();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	USceneComponent* RootComp;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UStaticMeshComponent* KeyMesh;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UFUNCTION()
	void ActivateKeyMesh();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RotationSpeed;
};
