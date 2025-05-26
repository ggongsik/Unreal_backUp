#pragma once

#include "CoreMinimal.h"
#include "PassiveItemBase.h"
#include "PassiveMoveSpeedItem.generated.h"

/**
 * 상호작용 시 moveSpeed 를 +150 해 주는 패시브 아이템
 */
UCLASS(DisplayName = "이동속도 증가(+150)")
class ROBOTLIKE_API APassiveMoveSpeedItem : public APassiveItemBase
{
    GENERATED_BODY()

public:
    APassiveMoveSpeedItem();

    /** 상호작용 시 GameManager 의 moveSpeed 를 +150 해 주고 파괴 */
    virtual void OnInteract_Implementation(APawn* InstigatorPawn) override;
};
