#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

void no_money_end() {

	printf("==========================\n");
	printf("         파산 엔딩        \n");
	printf("==========================\n");
}

void no_stamina_end() {

	printf("==========================\n");
	printf("       스테미나 고갈        \n");
	printf("==========================\n");
}

int main() {

	srand((unsigned int)time(NULL));

	int money = 100;

	int day = 0;

	int rest_timer = 0;

	int stamina = 100;
	int stamina_leak = 0;

	int health = 100;

	int goblen_vel = 0;

	while (1) {

		START:
		printf("==========================\n");
		printf("%d일차\n", day);
		printf("소지금: %dG\n", money);
		printf("스테미나: %d\n", stamina);
		printf("1. 전진(스테미나 -20), 2. 휴식(스테미나 +30)\n");
		printf("==========================\n");

		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		char select = _getch();

		if (select == '1') { // 전투

			if (stamina < 20) {
				
				if (stamina_leak == 1) {

					no_stamina_end();
					break;
				}
				printf("스테미나가 부족한 것 같다.\n");
				stamina_leak++;
				goto START;
			}

			int battle_select = rand() % 2;

			if (battle_select == 0) {

				printf("주사위 배틀 도망가시겠습니까?(Y/N) \n");

				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
				char skip_battle = _getch();

				if (skip_battle == 'Y' || skip_battle == 'y') {

					printf("무사히 도망쳤다.\n");
					goto BATTLEEND;
				}

				printf("\n");

				printf("주사위 전투 돌입\n");

				printf("적의 주사위가 던져졌다!\n");
				printf(".");
				Sleep(500);
				printf(".");
				Sleep(500);
				printf(".");
				Sleep(500);

				int en_dice = (rand() % 6) + 1;
				printf("적 주사위 값: %d\n", en_dice);
				Sleep(100);

				printf("\n");
				Sleep(500);

				printf("나의 주사위가 던져졌다!\n");
				printf(".");
				Sleep(500);
				printf(".");
				Sleep(500);
				printf(".");
				Sleep(500);

				int ply_dice = (rand() % 6) + 1;
				printf("나의 주사위 값: %d\n", ply_dice);
				Sleep(100);

				if (en_dice > ply_dice) {

					printf("패배\n");
					money -= 10;
				} else if (en_dice < ply_dice) {

					printf("승리\n");
					money += 10;
				} else {

					printf("무승부\n");
				}
			} else if(battle_select == 1) {

				printf("정찰중인 고블린의 뒤를 잡았다.\n");
				printf("1. 몰래 뒤따라간다. 2. 죽인다. 3. 도주한다.\n");

				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
				char select = _getch();
				if (select == '1') {

					int follow_goblen = rand() % 3;

					if (follow_goblen == 0) {

						printf(".");
						Sleep(500);
						printf(".");
						Sleep(500);
						printf(".");
						Sleep(500);
						printf("중간에 놓친 듯 하다...\n");
					} else if (follow_goblen == 1) {

						printf("\n");
						printf("고블린 부락을 찾았다.\n");
						printf("\n");
						printf("쳐들어갈까?(Y/N)\n");
						printf("거부 시 고블린 부락의 위치를 저장합니다.(부락의 위치는 중복으로 저장할 수 없습니다.)\n");

						char select = _getch();
						if (select == "Y" || select == 'y') {

							// 전투 방식 생각
							printf("전투 스킵");
						}

						printf("부락의 위치를 기록하고 돌아왔다.\n");
						goblen_vel = 1;
					} else if (follow_goblen == 2) {

						printf("고블린에게 들켰다!\n");

						printf("고블린과의 전투\n");

						// 전투 방식 생각
						printf("전투 스킵");
					}
				} else if (select == '2') {

					printf("고블린을 뒤에서 습격했다.\n");
					printf("고블린을 처치했다.\n");
					printf("15G를 획득했다.\n");
					money += 15;
				} else if (select == '3') {

					printf("무사히 도망쳤다\n");
				} else {

					printf("알 수 없는 입력\n");
				}
			}

			if (money < 0) {

				no_money_end();
				break;
			}

			BATTLEEND:
			stamina -= 20;
			rest_timer = 0;

			printf("\n");

		} else { // 휴식

			if (rest_timer == 1) {

				printf("연속 휴식은 불가능한 듯 하다.\n");
				printf("\n");
				goto START;
			}

			printf(".");
			Sleep(500);
			printf(".");
			Sleep(500);
			printf(".");
			Sleep(500);

			printf("\n");

			int merchant_probability = (rand() % 10) + 1;

			if (merchant_probability >= 8 && merchant_probability <= 10) {

				printf("==========================\n");
				printf("상인 등장\n");
				printf("판매 목록(아직 없음)\n");
				printf("R: 가챠(1회 10G) 0~50까지 랜덤한 G획득\n");
				printf("==========================\n");

				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
				char draw_btn = _getch();
				if (draw_btn == 'r' || draw_btn == 'R') {

					int get_draw_g = (rand() % 50) + 1;
					printf(".");
					Sleep(500);
					printf(".");
					Sleep(500);
					printf(".");
					Sleep(500);
					printf("!");
					printf("\n");
					Sleep(500);
					printf("획득한 G: %d\n", get_draw_g);
					money += get_draw_g;
				}

			} else {

				printf("아무 일도 일어나지 않았다.\n");
			}

			if (stamina < 100) {

				stamina += 30;

				if (stamina > 100) {

					stamina = 100;
				}
			}

			rest_timer = 1;
			stamina_leak = 0;

			printf("\n");
		}

		NEXTDAY:
		day++;
	}
}