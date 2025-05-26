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

    /** 액티브 아이템 사용 시 호출 */
    UFUNCTION(BlueprintCallable, Category = "ActiveItem")
    virtual void OnUse(APawn* InstigatorPawn);

    /** 상호작용 시 획득 처리 */
    virtual void OnInteract_Implementation(APawn* InstigatorPawn);

    /** 쿨다운 반환 */
    float GetCooldown() const { return Cooldown; }

    /** 일회용 여부 반환 */
    bool IsConsumable() const { return bConsumable; }

protected:
    UPROPERTY(VisibleAnywhere, Category = "ActiveItem")
    UStaticMeshComponent* MeshComp;

    UPROPERTY(EditDefaultsOnly, Category = "ActiveItem")
    float Cooldown = 5.0f;

    UPROPERTY(EditDefaultsOnly, Category = "ActiveItem")
    bool bConsumable = true;
};