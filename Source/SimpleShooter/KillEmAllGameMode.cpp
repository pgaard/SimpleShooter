// Fill out your copyright notice in the Description page of Project Settings.

#include "KillEmAllGameMode.h"

void AKillEmAllGameMode::PawnKilled(APawn *KilledPawn)
{
  UE_LOG(LogTemp, Display, TEXT("Pawn Killed"));
}
