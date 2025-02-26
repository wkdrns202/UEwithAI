#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyFirstCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UWidgetComponent;
struct FInputActionValue;
// extern int ItemCounts;

UCLASS()
class CPP_LECTURE_020525_API AMyFirstCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyFirstCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* OverheadWidget;


	virtual void Tick(float DeltaTime) override;

	// Camera Rotation Speed
	UPROPERTY(EditAnywhere, Category = "Camera")
	float CameraRotationSpeed;

	UFUNCTION(BlueprintCallable, Category = "Practice|PrintToScreen")
	void PrintToScreen(const FString& Message, FColor Color = FColor::Black, float Duration = 2.0f);

	// Mouse Input Values
	float MouseX, MouseY;
	float DefaultArmLength = 300.0f;
	float SprintArmLength = 800.0f;
	float CameraLerpSpeed = 1.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprinting")
	bool bIsSprinting = false;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	FVector CameraOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MouseSensitivity = 0.5f; // 기본 감도를 0.5로 설정
	float balancedYawInput = 0.0f;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void AddHealth(float Amount);


protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void JumpStart(const FInputActionValue& value);
	UFUNCTION()
	void JumpEnd(const FInputActionValue& value);
	/*UFUNCTION()
	void Look(const FInputActionValue& value);*/
	UFUNCTION()
	void SprintStart(const FInputActionValue& value);
	UFUNCTION()
	void SprintEnd(const FInputActionValue& value);
	UFUNCTION()
	void UpdateMouseX(const FInputActionValue& Value);
	UFUNCTION()
	void UpdateMouseY(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category= "Health")
	float MaxHealth;
	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = "Health")
	float Health;

	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser) override;

	virtual void BeginPlay() override;

	void OnDeath();
	void UpdateOverheadHP();

private:	

	float NormalSpeed;
	float SprintSpeedMultiplier;
	float SprintSpeed;
};
