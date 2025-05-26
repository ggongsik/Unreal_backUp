#pragma once

#include "CoreMinimal.h"
#include "ActiveItemBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GrenadeItem.generated.h"

UCLASS()
class ROBOTLIKE_API AGrenadeItem : public AActiveItemBase
{
    GENERATED_BODY()

public:
    AGrenadeItem();

    /** 액티브 아이템 사용 시 호출 (던지기) */
    virtual void OnUse(APawn* InstigatorPawn) override;

protected:
    /** 폭발 딜레이(초) */
    UPROPERTY(EditDefaultsOnly, Category = "Grenade")
    float ExplosionDelay = 2.0f;

    /** 폭발 반경 */
    UPROPERTY(EditDefaultsOnly, Category = "Grenade")
    float ExplosionRadius = 300.0f;

    /** 폭발 데미지 */
    UPROPERTY(EditDefaultsOnly, Category = "Grenade")
    float ExplosionDamage = 50.0f;

    /** 투사체 무브먼트 */
    UPROPERTY(VisibleAnywhere, Category = "Grenade")
    UProjectileMovementComponent* ProjMoveComp;

    /** 폭발 타이머 핸들 */
    FTimerHandle TimerHandle_Explosion;

    /** 폭발 처리 함수 */
    void Explode();

    /** 투척 후에는 더이상 상호작용되지 않도록 호출 */
    void DisablePickupCollision();
};
