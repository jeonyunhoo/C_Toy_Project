# Toy Project3, Raylib

궁극 목표: 뭐든 완성하기

## 1일차
목표: 되는 것 까지 만들기

### 만들 것
1. 이동 로직
2. 스텟

만들면서 생각해보기

### 작업 시작

#### player.h

플레이어 구조체 생성
```
typedef struct {

	double ATK;
	double HP;
	double DEF;
	double CRT;
	double EVA;
} Player_stat;
```
Idea.txt파일에 있는 스텟 구조를 생성하고 

```
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
```
각종 기본 플레이어에게 필요한 스텟을 정리함

```
void InitPlayer(Player* Player);
void UpdatePlayer(Player* Player);
void DrawPlayer(Player Player);
void LevelUp(Player* Player);
```
헤더 파일에서 미리 선언

#### player.c

InitPlayer에서 기본 상태를 설정함
```
Player->level = 1;
Player->exp = 0;
Player->stat_point = 0;

Player->stat.ATK = 12.0;
Player->stat.HP = 10.0;
Player->stat.DEF = 0.0;
Player->stat.CRT = 0.0;
Player->stat.EVA = 0.0;
```

이동 로직과 히트박스가 플레이어를 따라가도록 만듦
```
void UpdatePlayer(Player* Player) {

	if (IsKeyDown(KEY_UP)) Player->y -= Player->speed;
	if (IsKeyDown(KEY_DOWN)) Player->y += Player->speed;
	if (IsKeyDown(KEY_LEFT)) Player->x -= Player->speed;
	if (IsKeyDown(KEY_RIGHT)) Player->x += Player->speed;

	Player->hitbox.x = (float)Player->x;
	Player->hitbox.y = (float)Player->y;
}
```

#### main.c
기본 설정, 게임 실행 확인

