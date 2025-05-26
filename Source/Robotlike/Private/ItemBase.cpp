#include "ItemBase.h"
#include "GameManager.h"

AItemBase::AItemBase()
{
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    RootComponent = MeshComp;
}

void AItemBase::OnInteract_Implementation(APawn* InstigatorPawn)
{
    if (auto* GM = InstigatorPawn->GetGameInstance()->GetSubsystem<UGameManager>())
    {
        // 잘못된 호출: GM->AddToInventory(this);
        // 올바른 호출: 이 아이템의 클래스를 기록
        GM->AddToInventory(GetClass());

        UE_LOG(LogTemp, Log, TEXT("ItemBase picked up: %s"), *GetName());
        Destroy();
    }
}