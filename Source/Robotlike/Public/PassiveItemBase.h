#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "PassiveItemBase.generated.h"

/**
 * 상호작용하면 즉시 사라지는 기본 패시브 아이템
 */
UCLASS()
class ROBOTLIKE_API APassiveItemBase : public AActor, public IInteractable
{
    GENERATED_BODY()

public:
    APassiveItemBase();

    /** E키 상호작용 시 호출되어 아이템을 제거 */
    virtual void OnInteract_Implementation(APawn* InstigatorPawn) override;

protected:
    /** 월드에 표시될 메쉬 */
    UPROPERTY(VisibleAnywhere, Category = "PassiveItem")
    UStaticMeshComponent* MeshComp;
};
