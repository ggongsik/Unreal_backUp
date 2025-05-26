#include "PassiveItemBase.h"
#include "Components/StaticMeshComponent.h"

APassiveItemBase::APassiveItemBase()
{
    PrimaryActorTick.bCanEverTick = false;

    // 메쉬 컴포넌트 생성 및 루트 지정
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    RootComponent = MeshComp;
}

void APassiveItemBase::OnInteract_Implementation(APawn* InstigatorPawn)
{
    // 상호작용 즉시 파괴
    Destroy();
}
