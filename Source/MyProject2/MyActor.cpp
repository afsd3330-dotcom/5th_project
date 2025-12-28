

#include "MyActor.h"
#include "Engine/Engine.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

AMyActor::AMyActor()
{
	PrimaryActorTick.bCanEverTick = true;

}


void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Hello World"));
	}
	PrintFVector2DArray();
	TriggerEventWithProbability(30.0f);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AActor* PlayerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerActor)
	{
		float Distance = FVector::Dist(PlayerActor->GetActorLocation(), GetActorLocation());
		if (Distance <= 500.0f)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Player is close!"));
			}
		}
	}
}
void AMyActor::TriggerEventWithProbability(float Probability)
{
	int32 RandomValue = FMath::RandRange(0, 100);
	if (RandomValue <= Probability)
	{
		UE_LOG(LogTemp, Log, TEXT("Event Triggered!"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Event Not Triggered."));
	}
}
void AMyActor::PrintFVector2DArray()
{
	TArray<FVector2D> VectorArray;

	for(int32 i = 0; i < 5; ++i)
	{
		VectorArray.Add(FVector2D(i * 10.0f, i * 20.0f));
	}

	for (int32 i = 0; i < VectorArray.Num(); i++)
	{
		const FVector2D& Vec = VectorArray[i];
		UE_LOG(LogTemp, Log, TEXT("Vector %d: X = %f, Y = %f"), i, Vec.X, Vec.Y);
	}
}

float AMyActor::Distance(FVector First, FVector Second)
{
	float dx = Second.X - First.X;
	float dy = Second.Y - First.Y;
	float dz = Second.Z - First.Z;
	return FMath::Sqrt(dx * dx + dy * dy + dz * dz);
}