#include "ActiveItemBase.h"
#include "FPSPlayer.h"      // �Ǵ� APawn Ÿ�Ը� �ʿ��ϴٸ� ���� ����
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
        // ��Ŭ������ ������ �Ѱ��ݴϴ�.
        GM->SetNewActiveItemClass(this->GetClass());
        UE_LOG(LogTemp, Warning, TEXT("Picked up and stored class %s"), *GetName());

        Destroy();  // �Ⱦ��� ���ʹ� ��� ����
    }
}

void AActiveItemBase::OnUse(APawn* InstigatorPawn)
{
    // ������ ��� �� ���� (��ٿ� üũ ��)
    UE_LOG(LogTemp, Log, TEXT("ActiveItem used"));
    if (bConsumable)
    {
        Destroy();
    }
}
