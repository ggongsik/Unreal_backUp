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
        // �߸��� ȣ��: GM->AddToInventory(this);
        // �ùٸ� ȣ��: �� �������� Ŭ������ ���
        GM->AddToInventory(GetClass());

        UE_LOG(LogTemp, Log, TEXT("ItemBase picked up: %s"), *GetName());
        Destroy();
    }
}