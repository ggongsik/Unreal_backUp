#pragma once

#include "CoreMinimal.h"
#include "PassiveItemBase.h"
#include "PassiveAttckItem.generated.h"

/**
 * 상호작용 시 playerAttc 를 +0.1 해 주는 패시브 아이템
 */
UCLASS(DisplayName = "공격력 증강(1.1배)")
class ROBOTLIKE_API APassiveAttckItem : public APassiveItemBase
{
    GENERATED_BODY()

public:
    APassiveAttckItem();

    /** 상호작용 시 GameManager 에게 공격력 계수를 +0.1 해 달라고 요청 */
    virtual void OnInteract_Implementation(APawn* InstigatorPawn) override;
};
