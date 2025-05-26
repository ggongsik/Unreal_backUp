#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "ActiveItemBase.generated.h"

UCLASS()
class ROBOTLIKE_API AActiveItemBase : public AActor, public IInteractable
{
    GENERATED_BODY()

public:
    AActiveItemBase();

    /** ��Ƽ�� ������ ��� �� ȣ�� */
    UFUNCTION(BlueprintCallable, Category = "ActiveItem")
    virtual void OnUse(APawn* InstigatorPawn);

    /** ��ȣ�ۿ� �� ȹ�� ó�� */
    virtual void OnInteract_Implementation(APawn* InstigatorPawn);

    /** ��ٿ� ��ȯ */
    float GetCooldown() const { return Cooldown; }

    /** ��ȸ�� ���� ��ȯ */
    bool IsConsumable() const { return bConsumable; }

protected:
    UPROPERTY(VisibleAnywhere, Category = "ActiveItem")
    UStaticMeshComponent* MeshComp;

    UPROPERTY(EditDefaultsOnly, Category = "ActiveItem")
    float Cooldown = 5.0f;

    UPROPERTY(EditDefaultsOnly, Category = "ActiveItem")
    bool bConsumable = true;
};