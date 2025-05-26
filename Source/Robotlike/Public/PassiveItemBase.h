#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "PassiveItemBase.generated.h"

/**
 * ��ȣ�ۿ��ϸ� ��� ������� �⺻ �нú� ������
 */
UCLASS()
class ROBOTLIKE_API APassiveItemBase : public AActor, public IInteractable
{
    GENERATED_BODY()

public:
    APassiveItemBase();

    /** EŰ ��ȣ�ۿ� �� ȣ��Ǿ� �������� ���� */
    virtual void OnInteract_Implementation(APawn* InstigatorPawn) override;

protected:
    /** ���忡 ǥ�õ� �޽� */
    UPROPERTY(VisibleAnywhere, Category = "PassiveItem")
    UStaticMeshComponent* MeshComp;
};
