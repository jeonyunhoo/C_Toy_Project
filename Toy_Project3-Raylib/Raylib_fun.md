# Raylib

## 많이 쓰이는 함수

1. 창 제어 및 게임 루프  
    - InitWindow(int width, int heigth, const char *title)
        - 역할: 지정한 크기와 제목으로 게임 창을 엶(가장 먼저 호출해야 함)
    - CloseWindow(void)
        - 역할: 게임 창을 닫고 사용하던 메모리를 정리함(게임이 끝날 때 호출)
    - SetTargetFPS(int fps)
        - 역할: 게임의 초당 프레임(FPS)을 고정. 보통 60으로 설정하여 CPU가 100%할당되는 것을 막음
    - WindowShouldClose(void)
        - 역할: 유저가 창 닫기 버튼(X)을 눌렀거나 ESC키를 눌렀는지 확인하여 ture/false를 반환함(whlie루프 조건식에 사용됨)

2. 드로잉(화면)
    - BeginDrawing(void) / EndDrawing(void)
        - 역할: 프레임 단위로 화면에 그릴 내용을 시작하고 끝내는 쌍둥이 함수. 모든 그리기 작업은 반드시 이 두 함수 사이에 들어가야 함
    - ClearBackground(Color color)
        - 역할: 화면 전체를 특정 색상으로 싹 지움.(보통 루프 시작하자마자 배경색을 칠할 때 사용)
    - DrawRectangle(int posX, int posY, int width, int heigth, Color color)
        - 역할: 네모 박스를 그림. 타일, 벽, 혹은 임시 플레이어/몬스터를 표현할 때 유용함.
    - DrawTexture(Texture2D texture, int posX, int posY, Color tint)
        - 준비된 2D 스프라이트를 지정한 좌표에 그림. 캐릭터나 아이템을 화면에 띄울 때 핵심

3. 입력 처리
    - IsKeyDown(int key)
        - 역할: 특정 키를 꾹 누르고 있는 동안 계속 ture를 반환.(캐릭터를 상하좌우를 이동시킬 때 자주 사용)
        - ex) if(IsKeyDown(KEY_RIGHT)) player.x += 2.0f;
    
## 대표적 구조체 및 변수

1. 위치와 이동(Vector2)
- Vector2: 2차원 좌표인 x와 y값을 담고있는 구조체. 캐릭터의 위치, 이동 방향, 속도 등을 표한할 때 무조건 쓰임
    - 주요 멤버 변수: float x, float y
    - 사용 예시
    ```
    Vector2 playerPos = { 100.0f, 200.0f };
    playerPos.x += 2.0f; // 오른쪽으로 이동
    ```

2. 충돌과 영역(Rectangle)
- Rectangle: 사각형의 시작 좌표(x, y)와 크기(너비, 높이)를 정의하는 구조체. 2D RPG에서 캐릭터의 충돌 판정(Hitbox), 벽, 아이템 획득 범위 등을 처리할 때 핵심.
    - 주요 변수: float x, float y, float width, float height
    - 사용 예시
    ```
    Rectangle playerHitbox = { playerPos.x, playerPos.y, 32, 32 };
    ```

3. 그래픽과 색상(Texture2D, Color)
- Texture2D: 이미지 파일(PNG 등)을 로드해서 화면에 그릴 수 있게 담아두는 텍스처 변수.(캐릭터 스프라이트, 배경 타일 등)
- Color: 색상을 나타내는 구조체로, 빨강, 초록, 파랑, 투명도(r, g, b, a)값을 가짐.
    - 사용 예시
    ```
    Color customColor = { 255, 128, 0, 255}; (주황색)
    ```

4. 카메라 시점(Camera2D)
- Camera2D: 플레이어가 이동할 때 화면이 자연스럽게 캐릭터를 따라오도록(스크롤) 만들어주는 카메라 구조체
    - 주요 멤벼 변수: Vector2 target(따라갈 대상의 위치), Vector2 offset(화면 기준점), float zoom(확대 축소)