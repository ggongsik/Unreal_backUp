#include "ActiveItemBase.h"
#include "FPSPlayer.h"      // 또는 APawn 타입만 필요하다면 생략 가능
#include "GameManager.h"

AActiveItemBase::AActiveItemBase()
{
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    RootComponent = MeshComp;
}

void AActiveItemBase::OnInteract_Implementation(APawn* InstigatorPawn)
{
    if (auto* GM = InstigatorPawn->GetGameInstance()->GetSubsystem<UGameManager>())
    {
        // “클래스” 정보를 넘겨줍니다.
        GM->SetNewActiveItemClass(this->GetClass());
        UE_LOG(LogTemp, Warning, TEXT("Picked up and stored class %s"), *GetName());

        Destroy();  // 픽업용 액터는 즉시 제거
    }
}

void AActiveItemBase::OnUse(APawn* InstigatorPawn)
{
    // 아이템 사용 시 동작 (쿨다운 체크 후)
    UE_LOG(LogTemp, Log, TEXT("ActiveItem used"));
    if (bConsumable)
    {
        Destroy();
    }
}
