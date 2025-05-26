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

    /** ��Ƽ�� ������ ��� �� ȣ�� (������) */
    virtual void OnUse(APawn* InstigatorPawn) override;

protected:
    /** ���� ������(��) */
    UPROPERTY(EditDefaultsOnly, Category = "Grenade")
    float ExplosionDelay = 2.0f;

    /** ���� �ݰ� */
    UPROPERTY(EditDefaultsOnly, Category = "Grenade")
    float ExplosionRadius = 300.0f;

    /** ���� ������ */
    UPROPERTY(EditDefaultsOnly, Category = "Grenade")
    float ExplosionDamage = 50.0f;

    /** ����ü �����Ʈ */
    UPROPERTY(VisibleAnywhere, Category = "Grenade")
    UProjectileMovementComponent* ProjMoveComp;

    /** ���� Ÿ�̸� �ڵ� */
    FTimerHandle TimerHandle_Explosion;

    /** ���� ó�� �Լ� */
    void Explode();

    /** ��ô �Ŀ��� ���̻� ��ȣ�ۿ���� �ʵ��� ȣ�� */
    void DisablePickupCollision();
};
