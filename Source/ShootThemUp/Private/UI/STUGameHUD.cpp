// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUGameHUD.h"
#include "Engine/Canvas.h"

void ASTUGameHUD::DrawHUD()
{
	DrawCross();
}

void ASTUGameHUD::DrawCross()
{
	const TInterval<float> SizeInterval(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);
	int32 Offset = 10;
	int32 Thikness = 2;
	FLinearColor Color = FLinearColor::Green;

	DrawLine(SizeInterval.Min - Offset, SizeInterval.Max, SizeInterval.Min + Offset, SizeInterval.Max, Color, Thikness);
	DrawLine(SizeInterval.Min, SizeInterval.Max - Offset, SizeInterval.Min, SizeInterval.Max + Offset, Color, Thikness);
}
