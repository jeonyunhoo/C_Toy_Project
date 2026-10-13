#pragma once
#include "raylib.h"

typedef struct {

	double ATK;
	double HP;
	double DEF;
	double CRT;
	double EVA;
} Player_stat;

typedef struct {

	double PlusATK;
	double PlusHP;
	double PlusDEF;
	double PlusCRT;
	double PlusEVA;
} Plus_stat;

typedef struct {

	float x, y;
	float speed;

	Rectangle hitbox;

	int level;
	long exp;
	int stat_point;

	Player_stat stat;
	Plus_stat plus_stat;

	double current_hp;
} Player;

void InitPlayer(Player* Player);
void UpdatePlayer(Player* Player);
void DrawPlayer(Player Player);
void LevelUp(Player* Player);