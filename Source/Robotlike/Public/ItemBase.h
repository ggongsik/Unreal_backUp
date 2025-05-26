#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "ItemBase.generated.h"

UCLASS()
class ROBOTLIKE_API AItemBase : public AActor, public IInteractable
{
    GENERATED_BODY()

public:
    AItemBase();

    /** ��ȣ�ۿ� �� ȣ�� */
    virtual void OnInteract_Implementation(APawn* InstigatorPawn);

protected:
    UPROPERTY(VisibleAnywhere, Category = "Item")
    UStaticMeshComponent* MeshComp;
};
