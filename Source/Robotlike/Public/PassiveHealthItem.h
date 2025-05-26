#pragma once

#include "CoreMinimal.h"
#include "PassiveItemBase.h"
#include "PassiveHealthItem.generated.h"

/**
 * 상호작용 시 최대체력을 +10 해 주는 패시브 아이템 “근육(머슬)”
 */
UCLASS(DisplayName = "근육(머슬)")
class ROBOTLIKE_API APassiveHealthItem : public APassiveItemBase
{
    GENERATED_BODY()

public:
    APassiveHealthItem();

    /** 상호작용 시 최대체력 +10 효과 적용 */
    virtual void OnInteract_Implementation(APawn* InstigatorPawn) override;
};
