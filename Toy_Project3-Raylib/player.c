#include "raylib.h"
#include "player.h"

void InitPlayer(Player* Player) {

	Player->x = 400.0f;
	Player->y = 300.0f;
	Player->speed = 4.0f;

	Player->level = 1;
	Player->exp = 0;
	Player->stat_point = 0;

	Player->stat.ATK = 12.0;
	Player->stat.HP = 10.0;
	Player->stat.DEF = 0.0;
	Player->stat.CRT = 0.0;
	Player->stat.EVA = 0.0;

	Player->plus_stat.PlusATK = 0.0;
	Player->plus_stat.PlusHP = 0.0;
	Player->plus_stat.PlusDEF = 0.0;
	Player->plus_stat.PlusCRT = 0.0;
	Player->plus_stat.PlusEVA = 0.0;

	Player->current_hp = 100.0;

	Player->hitbox = (Rectangle){ Player->x, Player->y, 32, 32 };
}

void UpdatePlayer(Player* Player) {

	if (IsKeyDown(KEY_UP)) Player->y -= Player->speed;
	if (IsKeyDown(KEY_DOWN)) Player->y += Player->speed;
	if (IsKeyDown(KEY_LEFT)) Player->x -= Player->speed;
	if (IsKeyDown(KEY_RIGHT)) Player->x += Player->speed;

	Player->hitbox.x = (float)Player->x;
	Player->hitbox.y = (float)Player->y;
}

void DrawPlayer(Player Player) {

	DrawRectangleRec(Player.hitbox, GREEN);
}

void LevelUP(Player* Player) {

	if (Player->level == 2) {
		Player->stat_point += 8;
	} else if (Player->level % 10 == 0) {
		Player->stat_point += 10;
	} else if (Player->level % 5 == 0) {
		Player->stat_point += 5;
	} else {
		Player->stat_point += 4;
	}
}