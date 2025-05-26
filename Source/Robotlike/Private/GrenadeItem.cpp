#include "GrenadeItem.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

AGrenadeItem::AGrenadeItem()
{
    PrimaryActorTick.bCanEverTick = false;

    // 베이스 OnUse 에서 Destroy()되지 않도록
    bConsumable = false;

    // 투사체 무브 컴포넌트 생성
    ProjMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjMoveComp"));
    ProjMoveComp->bRotationFollowsVelocity = true;
    ProjMoveComp->bShouldBounce = true;

    // 무엇을 움직일지 지정 (Root 또는 MeshComp)
    ProjMoveComp->UpdatedComponent = RootComponent;
}

void AGrenadeItem::OnUse(APawn* InstigatorPawn)
{
    // **여기 로그가 찍혀야** Override가 호출되었음을 알 수 있습니다.
    UE_LOG(LogTemp, Warning, TEXT("AGrenadeItem::OnUse 호출: %s"), *GetName());

    Super::OnUse(InstigatorPawn); // 이제 Destroy() 없음

    if (!InstigatorPawn)
        return;

    // 플레이어 앞 100 유닛 위치로 이동
    FVector SpawnLoc = InstigatorPawn->GetActorLocation() + InstigatorPawn->GetControlRotation().Vector() * 100.0f;
    SetActorLocation(SpawnLoc);
    SetActorRotation(InstigatorPawn->GetControlRotation());

    // 속도 설정
    ProjMoveComp->Velocity = InstigatorPawn->GetControlRotation().Vector() * 1000.0f;

    // 딜레이 후 폭발
    GetWorld()->GetTimerManager().SetTimer(
        TimerHandle_Explosion, this, &AGrenadeItem::Explode, ExplosionDelay);
}

void AGrenadeItem::Explode()
{
    const FVector Loc = GetActorLocation();

    // ──────────────────────────────
    // 구형 와이어프레임 그리기
    // ──────────────────────────────
    const int32 Segments = 16;     // 세로/가로 분할 수
    const float Thickness = 2.0f;   // 선 두께
    const float Duration = 2.0f;   // 화면에 표시될 시간
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

    // ──────────────────────────────
    // 반경 데미지 적용
    // ──────────────────────────────
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

    // ──────────────────────────────
    // 액터 파괴
    // ──────────────────────────────
    Destroy();
}
