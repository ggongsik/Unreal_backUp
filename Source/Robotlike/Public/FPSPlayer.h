#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSPlayer.generated.h"

class UCameraComponent;
class UGameManager;
struct FHitResult;

UCLASS()
class ROBOTLIKE_API AFPSPlayer : public ACharacter
{
    GENERATED_BODY()

public:
    AFPSPlayer();

protected:
    virtual void BeginPlay() override;

    // Helper for line tracing
    bool PerformTrace(float Distance, FHitResult& OutHit);

    // Cached pointer to the game manager
    UPROPERTY()
    UGameManager* GameManager;

    // Trace range, ���� ����
    UPROPERTY(EditAnywhere, Category = "Interaction")
    float TraceDistance = 500.0f;

    // ī�޶� ������Ʈ
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UCameraComponent* FPSCamera;

    // �Է� ���ε�
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    // �̵� & ��ȣ�ۿ�
    void MoveForward(float Value);
    void MoveRight(float Value);
    void Interact();
    void UseActiveItem();

public:
    virtual void Tick(float DeltaTime) override;
};
