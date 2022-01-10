// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/DEscapeSuccessVolume.h"


// Engine Includes
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


// Game Includes
#include "DGameModeBase.h"
#include "Player/DPlayerCharacter.h"


// Sets default values
ADEscapeSuccessVolume::ADEscapeSuccessVolume()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}


// Called when the game starts or when spawned
void ADEscapeSuccessVolume::BeginPlay()
{
	Super::BeginPlay();
	
	if (BoxComp)
	{
		BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ADEscapeSuccessVolume::OnBoxCompBeginOverlap);
	}
}


void ADEscapeSuccessVolume::OnBoxCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;
	
	ADPlayerCharacter* PlayerCharacter = Cast<ADPlayerCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		InformGameModeEscapeSuccess();
	}
}


void ADEscapeSuccessVolume::InformGameModeEscapeSuccess()
{
	ADGameModeBase* GameMode = Cast<ADGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->PlayerEscapeSuccess();
	}
}

