#include "GrenadeItem.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

AGrenadeItem::AGrenadeItem()
{
    PrimaryActorTick.bCanEverTick = false;

    // ���̽� OnUse ���� Destroy()���� �ʵ���
    bConsumable = false;

    // ����ü ���� ������Ʈ ����
    ProjMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjMoveComp"));
    ProjMoveComp->bRotationFollowsVelocity = true;
    ProjMoveComp->bShouldBounce = true;

    // ������ �������� ���� (Root �Ǵ� MeshComp)
    ProjMoveComp->UpdatedComponent = RootComponent;
}

void AGrenadeItem::OnUse(APawn* InstigatorPawn)
{
    // **���� �αװ� ������** Override�� ȣ��Ǿ����� �� �� �ֽ��ϴ�.
    UE_LOG(LogTemp, Warning, TEXT("AGrenadeItem::OnUse ȣ��: %s"), *GetName());

    Super::OnUse(InstigatorPawn); // ���� Destroy() ����

    if (!InstigatorPawn)
        return;

    // �÷��̾� �� 100 ���� ��ġ�� �̵�
    FVector SpawnLoc = InstigatorPawn->GetActorLocation() + InstigatorPawn->GetControlRotation().Vector() * 100.0f;
    SetActorLocation(SpawnLoc);
    SetActorRotation(InstigatorPawn->GetControlRotation());

    // �ӵ� ����
    ProjMoveComp->Velocity = InstigatorPawn->GetControlRotation().Vector() * 1000.0f;

    // ������ �� ����
    GetWorld()->GetTimerManager().SetTimer(
        TimerHandle_Explosion, this, &AGrenadeItem::Explode, ExplosionDelay);
}

void AGrenadeItem::Explode()
{
    const FVector Loc = GetActorLocation();

    // ������������������������������������������������������������
    // ���� ���̾������� �׸���
    // ������������������������������������������������������������
    const int32 Segments = 16;     // ����/���� ���� ��
    const float Thickness = 2.0f;   // �� �β�
    const float Duration = 2.0f;   // ȭ�鿡 ǥ�õ� �ð�
    const FColor SphereColor = FColor::Red;

    DrawDebugSphere(
        GetWorld(),
        Loc,
        ExplosionRadius,
        Segments,
        SphereColor,
        /*bPersistentLines=*/ false,
        Duration,
        /*DepthPriority=*/ 0,
        Thickness
    );

    // ������������������������������������������������������������
    // �ݰ� ������ ����
    // ������������������������������������������������������������
    UGameplayStatics::ApplyRadialDamage(
        this,
        ExplosionDamage,
        Loc,
        ExplosionRadius,
        nullptr,
        TArray<AActor*>(),
        this,
        nullptr,
        true
    );

    // ������������������������������������������������������������
    // ���� �ı�
    // ������������������������������������������������������������
    Destroy();
}
