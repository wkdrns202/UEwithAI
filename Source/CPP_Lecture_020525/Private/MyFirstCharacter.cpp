#include "MyFirstCharacter.h"
#include "MyFirstPlayerController.h"
#include "MySecondGameState.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"

// int ItemCounts = 0;

AMyFirstCharacter::AMyFirstCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    bUseControllerRotationYaw = false;

    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArmComp->SetupAttachment(RootComponent);
    SpringArmComp->TargetArmLength = 300.0f;
    SpringArmComp->bUsePawnControlRotation = true;
    SpringArmComp->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));

    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
    CameraComp->bUsePawnControlRotation = false;

    OverheadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidget"));
    OverheadWidget->SetupAttachment(GetMesh());
    OverheadWidget->SetWidgetSpace(EWidgetSpace::Screen);

    // Initialize values
    CameraRotationSpeed = 3.0f; // Adjust speed as needed
    CameraOffset = FVector(0.0f, 0.0f, 100.0f);

    NormalSpeed = 600.0f;
    SprintSpeedMultiplier = 1.7f;
    SprintSpeed = NormalSpeed * SprintSpeedMultiplier;

    GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
    // 자동 회전 기능 비활성화 (이제 Move() 함수 내에서 수동 회전 적용)
    GetCharacterMovement()->bOrientRotationToMovement = false;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

    MaxHealth = 100.0f;
    Health = MaxHealth;
       
}

void AMyFirstCharacter::BeginPlay()
{
    Super::BeginPlay();
    UpdateOverheadHP();
    
}


void AMyFirstCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (AMyFirstPlayerController* PlayerController = Cast<AMyFirstPlayerController>(GetController()))
        {
            // ✅ Move
            if (PlayerController->MoveActionCool)
            {
                EnhancedInput->BindAction(
                    PlayerController->MoveActionCool,
                    ETriggerEvent::Triggered,
                    this,
                    &AMyFirstCharacter::Move
                );
            }

            // ✅ Jump
            if (PlayerController->JumpActionYes)
            {
                EnhancedInput->BindAction(
                    PlayerController->JumpActionYes,
                    ETriggerEvent::Triggered,
                    this,
                    &AMyFirstCharacter::JumpStart
                );


                EnhancedInput->BindAction(
                    PlayerController->JumpActionYes,
                    ETriggerEvent::Completed,
                    this,
                    &AMyFirstCharacter::JumpEnd
                );
            }

            // ✅ Mouse Look (X)
            if (PlayerController->TurnActionBravo)
            {
                EnhancedInput->BindAction(
                    PlayerController->TurnActionBravo,
                    ETriggerEvent::Triggered,
                    this,
                    &AMyFirstCharacter::UpdateMouseX
                );
            }

            // ✅ Mouse Look (Y)
            if (PlayerController->LookUpActionBravo)
            {
                EnhancedInput->BindAction(
                    PlayerController->LookUpActionBravo,
                    ETriggerEvent::Triggered,
                    this,
                    &AMyFirstCharacter::UpdateMouseY
                );
            }

            // ✅ Sprint
            if (PlayerController->SprintActionNice)
            {
                EnhancedInput->BindAction(
                    PlayerController->SprintActionNice,
                    ETriggerEvent::Triggered,
                    this,
                    &AMyFirstCharacter::SprintStart
                );
                EnhancedInput->BindAction(
                    PlayerController->SprintActionNice,
                    ETriggerEvent::Completed,
                    this,
                    &AMyFirstCharacter::SprintEnd
                );
            }
        }
    }
}

void AMyFirstCharacter::Move(const FInputActionValue& Value)
{
    if (!Controller) return;

    const FVector2D MoveInput = Value.Get<FVector2D>();

    if (!MoveInput.IsNearlyZero())
    {
        // 1️⃣ 카메라 컴포넌트의 현재 회전값 사용 (컨트롤러 회전 대신)
        FRotator CameraRotation = CameraComp->GetComponentRotation();
        CameraRotation.Pitch = 0.0f; // 수평 이동을 위해 Pitch 제거
        CameraRotation.Roll = 0.0f;  // Roll 제거

        // 2️⃣ 카메라 회전값으로부터 Forward & Right 벡터 계산
        FVector ForwardVector = CameraRotation.Vector();
        FVector RightVector = FRotationMatrix(CameraRotation).GetUnitAxis(EAxis::Y);

        // 3️⃣ 입력 벡터에 따라 이동 방향 결정 (W: Y, A/D: X)
        FVector MoveDirection = (ForwardVector * MoveInput.Y) + (RightVector * MoveInput.X);
        MoveDirection.Normalize();

        // 4️⃣ 캐릭터 이동 적용
        AddMovementInput(MoveDirection);

        // 5️⃣ 캐릭터가 이동 방향을 바라보도록 수동 회전 (부드럽게)
        if (!MoveDirection.IsNearlyZero())
        {
            FRotator TargetRotation = MoveDirection.Rotation();
            TargetRotation.Pitch = 0.0f;
            TargetRotation.Roll = 0.0f;
            SetActorRotation(FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 10.0f));
        }
    }
}

void AMyFirstCharacter::JumpStart(const FInputActionValue& value)
{
    if (value.Get<bool>())
    {
        Jump();
    }

    else
    {
        //GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("Jump Failed!"));
    }

}

void AMyFirstCharacter::JumpEnd(const FInputActionValue& value)
{
    if (!value.Get<bool>())
    {
        StopJumping();
    }
}

void AMyFirstCharacter::SprintStart(const FInputActionValue& value)
{
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
        FString SpeedMessage = "Your Current Speed is:" + FString::SanitizeFloat(SprintSpeed);
        bIsSprinting = true;
        //PrintToScreen(SpeedMessage, FColor::Green, 0.000005f);
    }
}

void AMyFirstCharacter::SprintEnd(const FInputActionValue& value)
{
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
        FString SpeedMessage = "Your Current Speed is:" + FString::SanitizeFloat(SprintSpeed);
        bIsSprinting = false;
    }

    else
    {
        FString SpeedMessage = "bIsSprinting is still true";
    }
}

void AMyFirstCharacter::PrintToScreen(const FString& Message, FColor Color, float Duration)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, Duration, Color, Message);
    }
}

void AMyFirstCharacter::UpdateMouseX(const FInputActionValue& Value)
{
    
    AddControllerYawInput(Value.Get<float>());
}

void AMyFirstCharacter::UpdateMouseY(const FInputActionValue& Value)
{
    balancedYawInput = Value.Get<float>() * MouseSensitivity;
    AddControllerPitchInput(balancedYawInput);
}

void AMyFirstCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    float TargetLength = bIsSprinting ? SprintArmLength : DefaultArmLength;
    SpringArmComp->TargetArmLength = FMath::FInterpTo(SpringArmComp->TargetArmLength, TargetLength, DeltaTime, CameraLerpSpeed);
    //GEngine->AddOnScreenDebugMessage(-1, 0.05f, FColor::Blue, bIsSprinting ? TEXT("true") : TEXT("false"));

   /* if (!ItemCounts)
    {
        GEngine->AddOnScreenDebugMessage(-1,
            2.0f,
            FColor::Green,
            FString::Printf(TEXT("There is a no item")));
    }*/
}

float AMyFirstCharacter::GetHealth() const
{
    return Health;
}

void AMyFirstCharacter::AddHealth(float Amount)
{
    Health = FMath::Clamp(Health + Amount, 0.0f, MaxHealth);
    UpdateOverheadHP();
}

float AMyFirstCharacter::TakeDamage(
    float DamageAmount,
    struct FDamageEvent const& DamageEvent,
    AController* EventInstigator,
    AActor* DamageCauser)
{
    float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    Health = FMath::Clamp(Health - DamageAmount, 0.0f, MaxHealth);
    UpdateOverheadHP();

    if (Health <= 0)
    {
        OnDeath();
    }

    return ActualDamage;
}

void AMyFirstCharacter::OnDeath()
{
    AMySecondGameState* GameState = GetWorld() ? GetWorld()->GetGameState<AMySecondGameState>() : nullptr;
    if (GameState)
    {
        GameState->OnGameOver();
    }
}

void AMyFirstCharacter::UpdateOverheadHP()
{
    if (!OverheadWidget) return;

    UUserWidget* OverheadWidgetInstance = OverheadWidget->GetUserWidgetObject();
    if (!OverheadWidgetInstance) return;

    if (UTextBlock* HPText = Cast<UTextBlock>(OverheadWidgetInstance->GetWidgetFromName(TEXT("OverHeadHP"))))
    {
        HPText->SetText(FText::FromString(FString::Printf(TEXT("%.0f / %.0f"), Health, MaxHealth)));
    }
}