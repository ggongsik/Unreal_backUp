#pragma once

#include "CoreMinimal.h"
#include "PassiveItemBase.h"
#include "PassiveMoveSpeedItem.generated.h"

/**
 * ��ȣ�ۿ� �� moveSpeed �� +150 �� �ִ� �нú� ������
 */
UCLASS(DisplayName = "�̵��ӵ� ����(+150)")
class ROBOTLIKE_API APassiveMoveSpeedItem : public APassiveItemBase
{
    GENERATED_BODY()

public:
    APassiveMoveSpeedItem();

    /** ��ȣ�ۿ� �� GameManager �� moveSpeed �� +150 �� �ְ� �ı� */
    virtual void OnInteract_Implementation(APawn* InstigatorPawn) override;
};
