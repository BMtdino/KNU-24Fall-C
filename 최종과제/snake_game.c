// C program to build the complete 
// snake game 
#include <conio.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <io.h> 
#include <Windows.h>
#include <time.h>

#define MAX_LENGTH 100
#define MAX_OBSTACLES 10

int i, j, height = 20, width = 20;
int gameover, score;
int x, y, fruitx, fruity, flag;
int snakeX[MAX_LENGTH], snakeY[MAX_LENGTH]; // 뱀의 전체 위치
int length = 1;                             // 뱀의 초기 길이

// 2P 모드 관련 변수
int mode = 1; // 1: 1P 모드, 2: 2P 모드
int p2_x, p2_y, p2_flag, score_2p;
int snake2X[MAX_LENGTH], snake2Y[MAX_LENGTH]; // 2P 뱀 위치
int length2 = 1;

// 방해물 관련 변수
int obstacleX[MAX_OBSTACLES];
int obstacleY[MAX_OBSTACLES];
int obstacleCount = 0;				// 현재 활성화된 방해물 수
int obstacleTimer[MAX_OBSTACLES];	// 각 방해물의 타이머
int max_obstacles = 3;				// 초기 최대 방해물 개수
int obstacle_size = 1;				// 초기 방해물 크기 (1x1)

// 뱀의 속도 (Sleep 시간) 조절 변수
int snake_speed = 300; // 초기 속도: 300ms

// 아이템 박스 관련 변수
int boxX, boxY;             // 아이템 박스 위치
int box_active = 0;         // 아이템 박스 활성 상태
int box_spawn_time = 40;    // 박스 생성 간격
int box_duration = 10;      // 박스 유지 시간
clock_t last_box_time = 0;  // 마지막 박스 생성 시간

// 추가 점수 제공 열매
int bonusFruitX, bonusFruitY;
int bonus_fruit_active = 0;

// 경계선 배열
char boundary[20][20];

// 게임 시간 관리
clock_t start_time;
int elapsed_time = 0;

// 위치 이동 화면 표시
void gotoxy(int x, int y) {
	printf("\033[%d;%dH", x + 1, y + 1); // x, y는 0부터 시작하므로 +1
}

// 화면 초기화
void resetScreen() {
	system("cls");
}

// 경계선 배열 초기화
void initBoundary() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
				boundary[i][j] = '#'; // 경계선 벽
			}
			else {
				boundary[i][j] = ' '; // 빈 공간
			}
		}
	}
}

// 경계선 출력
void printBoundary() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			gotoxy(i, j);
			printf("%c", boundary[i][j]);
		}
	}
}

// 경계선 훼손 시 복구
void restoreBoundary() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (boundary[i][j] == '#' && boundary[i][j] != '#') {
				gotoxy(i, j);
				printf("#");
			}
		}
	}
}

// 특정 위치의 경계선 반환
char getBoundaryCharAt(int x, int y) {
	return boundary[x][y];
}

// 특정 위치에 오브젝트가 있는지 확인
int isPositionOccupied(int px, int py) {
	// 경계선 확인
	if (px <= 0 || px >= height - 1 || py <= 0 || py >= width - 1) return 1;

	// 뱀과 겹치는지 확인
	for (int i = 0; i < length; i++) {
		if (snakeX[i] == px && snakeY[i] == py) return 1;
	}

	if (mode == 2) {
		for (int i = 0; i < length2; i++) {
			if (snake2X[i] == px && snake2Y[i] == py) return 1;
		}
	}

	// 과일과 겹치는지 확인
	if (fruitx == px && fruity == py) return 1;

	// 방해물과 겹치는지 확인
	for (int i = 0; i < obstacleCount; i++) {
		if (obstacleX[i] == px && obstacleY[i] == py) return 1;
	}

	// 추가 점수 열매와 겹치는지 확인
	if (bonus_fruit_active && bonusFruitX == px && bonusFruitY == py) return 1;

	// 아이템 박스와 겹치는지 확인
	if (box_active && boxX == px && boxY == py) return 1;

	return 0; // 빈 위치
}

// 게임 초기 설정
void setup()
{
	// 난수 생성기 초기화
	srand(time(NULL)); // 현재 시간을 시드로 설정

	gameover = 0;

	// 모드 선택
	printf("Select Mode: 1(1P), 2(2P)\n");
	scanf_s("%d", &mode);
	if (mode != 1 && mode != 2) mode = 1; // 기본값 1P

	// 뱀 초기 설정 (1p)
	x = height / 2;
	y = width / 2;
	snakeX[0] = x;
	snakeY[0] = y;

	// 뱀 초기 설정 (2p)
	if (mode == 2) {
		p2_x = height / 2;
		p2_y = (3 * width) / 4;
		snake2X[0] = p2_x;
		snake2Y[0] = p2_y;
	}

	// 첫번째 과일 위치 생성
	fruitx = rand() % (height - 2) + 1;
	fruity = rand() % (width - 2) + 1;

	score = 0;
	if (mode == 2) {
		score_2p = 0;
	}
	obstacleCount = 0;

	// 경계선 초기화
	initBoundary();

	// 시작 시간 기록
	start_time = clock();

	//화면 초기화
	resetScreen();

	// 화면 초기화 및 경계선 출력
	resetScreen();
	printBoundary();

	// 최초 과일 출력
	gotoxy(fruitx, fruity);
	printf("*");
}

//화면 그리기
void draw()
{
	// 점수 출력 & 게임 강제 종료 조건 출력
	if (mode == 1) {
		gotoxy(height, 0);
		printf("Score : %d   ", score);				// 점수 출력
		printf("Time : %d sec   ", elapsed_time);	// 경과 시간 출력
		printf("Speed : %d ms   ", snake_speed);	// 속도 출력
		printf("Mode : 1p   ");					//모드 표시(1p)
		printf("\npress X to quit the game");
	}
	else if (mode == 2) {
		gotoxy(height, 0);
		printf("Score1 : %d   ", score);				// 점수 출력(1p)
		printf("Score2 : %d   ", score_2p);				// 점수 출력(2p)
		printf("Time : %d sec   ", elapsed_time);	// 경과 시간 출력
		printf("Speed : %d ms   ", snake_speed);	// 속도 출력
		printf("Mode : 2p   ");					//모드 표시(2p)
		printf("\npress X to quit the game");
	}
}

// 키 입력
void input()
{
	if (_kbhit()) {
		char key = getch();

		// 1p 키바인딩
		if (mode == 1 || (mode == 2 && key != 0)) {
			switch (key) {
			case 'a':
				if (flag != 3) flag = 1; // 왼쪽 이동 ( 오른쪽으로 이동 중이 아닐 때만 가능 )
				break;
			case 's':
				if (flag != 4) flag = 2; // 아래쪽 이동 ( 위로 이동 중이 아닐 때만 가능 )
				break;
			case 'd':
				if (flag != 1) flag = 3; // 오른쪽 이동 ( 왼쪽으로 이동 중이 아닐 때만 가능 )
				break;
			case 'w':
				if (flag != 2) flag = 4; // 위쪽 이동 ( 아래로 이동 중이 아닐 때만 가능 )
				break;
			case 'x':
				gameover = 1; // 게임 종료
				break;
			}
		}

		//2p 키바인딩
		if (mode == 2 && key != 0) {
			//key = getch();
			switch (key) {
			case 75: // ← 방향키
				if (p2_flag != 3) p2_flag = 1;
				break;
			case 80: // ↓ 방향키
				if (p2_flag != 4) p2_flag = 2;
				break;
			case 77: // → 방향키
				if (p2_flag != 1) p2_flag = 3;
				break;
			case 72: // ↑ 방향키
				if (p2_flag != 2) p2_flag = 4;
				break;
			}
		}
	}
}

// 아이템 박스 생성
void generateItemBox() {
	if (!box_active && elapsed_time >= box_spawn_time) {
		int valid = 0;
		while (!valid) {
			boxX = rand() % (height - 2) + 1;
			boxY = rand() % (width - 2) + 1;
			valid = 1;

			// 박스가 뱀, 과일, 방해물과 겹치지 않도록 설정
			if (boxX == fruitx && boxY == fruity) valid = 0;
			for (int i = 0; i < length; i++) {
				if (snakeX[i] == boxX && snakeY[i] == boxY) {
					valid = 0;
					break;
				}
			}
			for (int i = 0; i < obstacleCount; i++) {
				if ((boxX >= obstacleX[i] && boxX < obstacleX[i] + obstacle_size) &&
					(boxY >= obstacleY[i] && boxY < obstacleY[i] + obstacle_size)) {
					valid = 0;
					break;
				}
			}
		}
		box_active = 1;
		gotoxy(boxX, boxY);
		printf("□"); // 아이템 박스 표시
	}
}

// 아이템 박스 효과 적용
void applyItemBoxEffect() {
	int effect = rand() % 6; // 0: 속도 증가, 1: 방해물 제거, 2: 추가 점수 열매 생성
	// 3: 꼬리 감소, 4: 꼬리 추가, 5: 속도 감소

	if (effect == 0) {
		// 속도 증가
		if (snake_speed > 50) { // 최소 속도 제한
			snake_speed -= 10;
		}
		gotoxy(height + 2, 0);
		printf("\nSpeed increased!\n");
	}
	else if (effect == 1 && obstacleCount > 0) {
		// 방해물 제거
		for (int i = 0; i < obstacleCount; i++) {
			for (int dx = 0; dx < obstacle_size; dx++) {
				for (int dy = 0; dy < obstacle_size; dy++) {
					gotoxy(obstacleX[i] + dx, obstacleY[i] + dy);
					printf(" ");
				}
			}
		}
		obstacleCount = 0; // 모든 방해물 제거
		gotoxy(height + 2, 0);
		printf("\nObstacles removed!\n");
	}
	else if (effect == 2) {
		// 추가 점수 열매 생성
		int bonusX, bonusY, valid = 0;
		while (!valid) {
			bonusX = rand() % (height - 2) + 1;
			bonusY = rand() % (width - 2) + 1;
			valid = 1;

			// 추가 점수 열매가 다른 오브젝트와 겹치지 않도록 설정
			if (bonusX == fruitx && bonusY == fruity) valid = 0;
			for (int i = 0; i < length; i++) {
				if (snakeX[i] == bonusX && snakeY[i] == bonusY) {
					valid = 0;
					break;
				}
			}
			for (int i = 0; i < obstacleCount; i++) {
				if ((bonusX >= obstacleX[i] && bonusX < obstacleX[i] + obstacle_size) &&
					(bonusY >= obstacleY[i] && bonusY < obstacleY[i] + obstacle_size)) {
					valid = 0;
					break;
				}
			}
		}
		printf("&");
		gotoxy(height + 2, 0);
		printf("\nBonus fruit spawned!\n");
	}
	else if (effect == 3 && length > 1) { // 1p
		// 꼬리 감소
		gotoxy(snakeX[length - 1], snakeY[length - 1]);
		printf(" "); // 꼬리 제거
		length--;
		gotoxy(height + 2, 0);
		printf("\nTail removed!\n");
	}
	else if (mode == 2 && effect == 3 && length2 > 1) {	// 2p
		// 꼬리 감소
		gotoxy(snake2X[length2 - 1], snake2Y[length2 - 1]);
		printf(" "); // 꼬리 제거
		length2--;
		gotoxy(height + 2, 0);
		printf("\nTail removed!\n");
	}
	else if (effect == 4) { // 1p
		// 꼬리 추가
		length++;
		snakeX[length - 1] = snakeX[length - 2];
		snakeY[length - 1] = snakeY[length - 2];
		gotoxy(height + 2, 0);
		printf("\nTail added!\n");
	}
	else if (mode == 2 && effect == 4) { // 2p
		// 꼬리 추가
		length2++;
		snake2X[length2 - 1] = snake2X[length2 - 2];
		snake2Y[length2 - 1] = snake2Y[length2 - 2];
		gotoxy(height + 2, 0);
		printf("\nTail added!\n");
	}
	else if (effect == 5) {
		// 속도 감소
		if (snake_speed < 500) { // 최대 속도 제한
			snake_speed += 10;
		}
		printf("\nSpeed decreased!\n");
	}

	box_active = 0; // 박스 비활성화
	box_spawn_time = elapsed_time + 40; // 다음 생성 시간 설정
}

// 박스 유지 시간 관리
void manageItemBox() {
	if (box_active && elapsed_time >= box_spawn_time + box_duration) {
		gotoxy(boxX, boxY);
		printf(" "); // 박스 제거
		box_active = 0;
		box_spawn_time = elapsed_time + 40; // 다음 생성 시간 설정
	}
}

// 추가 점수 열매 관리
void manageBonusFruit() {
	if (bonus_fruit_active && x == bonusFruitX && y == bonusFruitY) {
		score += 20; // 추가 점수 제공
		bonus_fruit_active = 0;
		gotoxy(bonusFruitX, bonusFruitY);
		printf(" ");
	}
}

// 방해물 생성
void generateObstacle() {
	if (obstacleCount < max_obstacles) {
		int ox, oy, valid;

		do {
			valid = 1;

			// 방해물의 임의 위치 생성
			ox = rand() % (height - 2 - obstacle_size) + 1;
			oy = rand() % (width - 2 - obstacle_size) + 1;

			// 방해물이 뱀 또는 과일과 겹치지 않도록 확인
			if (valid && (ox == fruitx && oy == fruity)) valid = 0;
			for (int i = 0; i < length; i++) {
				if (valid && (snakeX[i] == ox && snakeY[i] == oy)) {
					valid = 0;
					break;
				}
			}

			// 방해물이 경계선을 침범하지 않도록 확인
			if (ox <= 0 || ox + obstacle_size >= height - 1 ||
				oy <= 0 || oy + obstacle_size >= width - 1) {
				valid = 0;
			}
		} while (!valid);

		// 방해물 위치와 타이머 설정
		obstacleX[obstacleCount] = ox;
		obstacleY[obstacleCount] = oy;
		obstacleTimer[obstacleCount] = elapsed_time + 5; // 방해물 유지 시간
		obstacleCount++;

		// 방해물 출력
		for (int dx = 0; dx < obstacle_size; dx++) {
			for (int dy = 0; dy < obstacle_size; dy++) {
				gotoxy(ox + dx, oy + dy);
				printf("@");
			}
		}
	}
}

// 방해물 관리 (시간 만료 시 제거)
void manageObstacles() {
	for (int i = 0; i < obstacleCount; i++) {
		if (elapsed_time >= obstacleTimer[i]) {
			// 시간이 만료된 방해물 제거
			for (int dx = 0; dx < obstacle_size; dx++) {
				for (int dy = 0; dy < obstacle_size; dy++) {
					gotoxy(obstacleX[i] + dx, obstacleY[i] + dy);
					printf(" ");
				}
			}

			// 방해물 데이터 삭제
			obstacleX[i] = obstacleX[obstacleCount - 1];
			obstacleY[i] = obstacleY[obstacleCount - 1];
			obstacleTimer[i] = obstacleTimer[obstacleCount - 1];
			obstacleCount--;
			i--;
		}
	}
}

// 시간에 따른 방해물 크기 및 생성 개수 증가
void updateObstacleParameters() {
	if (elapsed_time % 40 == 0 && elapsed_time > 0) { // 40초마다 증가
		if (max_obstacles < MAX_OBSTACLES) {
			max_obstacles++; // 방해물 최대 개수 증가
		}
		if (obstacle_size < 5) { // 방해물 크기 제한 (최대 5x5)
			obstacle_size++;
		}
	}
}

// 게임의 로직
void logic()
{
	Sleep(snake_speed);			//속도 조절

	// 경과 시간 업데이트
	elapsed_time = (clock() - start_time) / CLOCKS_PER_SEC;

	// 게임 시간이 경과함에 따라 방해물 생성 ( 주기 : 13초 / 생성 확률 : 50% )
	if (elapsed_time % 13 == 0 && rand() % 2 == 0) {
		generateObstacle();
	}

	// 아이템 박스 생성
	generateItemBox();

	// 아이템 박스 관리
	manageItemBox();

	// 아이템 박스 효과 적용
	if ((x == boxX && y == boxY && box_active) || (p2_x == boxX && p2_y == boxY && box_active)) {
		applyItemBoxEffect();
	}

	// 추가 점수 열매 관리
	manageBonusFruit();

	// 방해물 관리
	manageObstacles();

	// 이전 위치를 지우기 (1p)
	gotoxy(snakeX[length - 1], snakeY[length - 1]);
	printf(" ");

	// 이전 위치를 지우기 (2p)
	if (mode == 2) {
		gotoxy(snake2X[length2 - 1], snake2Y[length2 - 1]);
		printf(" ");
	}

	// 몸체 이동 (뒤에서부터 앞으로 이동) (1p)
	for (int i = length - 1; i > 0; i--) {
		snakeX[i] = snakeX[i - 1];
		snakeY[i] = snakeY[i - 1];
	}

	// 몸체 이동 (뒤에서부터 앞으로 이동) (2p)
	if (mode == 2) {
		for (int i = length2 - 1; i > 0; i--) {
			snake2X[i] = snake2X[i - 1];
			snake2Y[i] = snake2Y[i - 1];
		}
	}
	//뱀 이동 로직(1p)
	switch (flag) {
	case 1:
		y--;
		break;
	case 2:
		x++;
		break;
	case 3:
		y++;
		break;
	case 4:
		x--;
		break;
	default:
		break;
	}
	snakeX[0] = x;
	snakeY[0] = y;

	// 뱀 이동 로직(2p)
	if (mode == 2) {
		for (int i = length2 - 1; i > 0; i--) {
			snake2X[i] = snake2X[i - 1];
			snake2Y[i] = snake2Y[i - 1];
		}
		switch (p2_flag) {
		case 1:
			p2_y--;
			break;
		case 2:
			p2_x++;
			break;
		case 3:
			p2_y++;
			break;
		case 4:
			p2_x--;
			break;
		}
		snake2X[0] = p2_x;
		snake2Y[0] = p2_y;
	}

	// 뱀 벽 충돌 확인 (1p)
	if (x <= 0 || x >= height - 1 || y <= 0 || y >= width - 1) {
		gameover = 1;
		if (mode == 2) {
			gotoxy(height + 3, 0);
			printf(" Player 2 wins!\n");
		}
	}

	// 뱀 벽 충돌 확인 (2P)
	if (mode == 2 && (p2_x <= 0 || p2_x >= height - 1 || p2_y <= 0 || p2_y >= width - 1)) {
		gotoxy(height + 3, 0);
		printf(" Player 1 wins!\n");
		gameover = 1;
	}

	// 서로 충돌 확인
	if (mode == 2) {
		for (int i = 1; i < length2; i++) {
			if (snakeX[0] == snake2X[i] && snakeY[0] == snake2Y[i]) {
				gameover = 1;
				gotoxy(height + 3, 0);
				printf(" Player 2 wins!\n");
				break;
			}
		}
		for (int i = 1; i < length; i++) {
			if (snake2X[0] == snakeX[i] && snake2Y[0] == snakeY[i]) {
				gameover = 1;
				gotoxy(height + 3, 0);
				printf(" Player 1 wins!\n");
				break;
			}
		}
	}

	// 머리가 몸체에 충돌했는지 확인 (1p)
	for (int i = 1; i < length; i++) {
		if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
			gotoxy(height + 3, 0);
			printf(" Player 2 wins!\n");
			gameover = 1;
		}
	}
	// 머리가 몸체에 충돌했는지 확인 (2p)
	if (mode == 2) {
		for (int i = 1; i < length2; i++) {
			if (snake2X[0] == snake2X[i] && snake2Y[0] == snake2Y[i]) {
				gotoxy(height + 3, 0);
				printf("Player 1 wins!\n");
				gameover = 1;
			}
		}
	}

	// 방해물 충돌 확인 (1p)
	for (int i = 0; i < obstacleCount; i++) {
		if (snakeX[0] == obstacleX[i] && snakeY[0] == obstacleY[i]) {
			gotoxy(height + 3, 0);
			printf("Player 2 wins!\n");
			gameover = 1;
		}
	}
	// 방해물 충돌 확인 (2p)
	for (int i = 0; i < obstacleCount; i++) {
		if (snake2X[0] == obstacleX[i] && snake2Y[0] == obstacleY[i]) {
			gotoxy(height + 3, 0);
			printf("Player 1 wins!\n");
			gameover = 1;
		}
	}

	// 과일 충돌 (1P)
	if (x == fruitx && y == fruity) {
		score += 10;

		snakeX[length] = snakeX[length - 1];
		snakeY[length] = snakeY[length - 1];
		length++;

		fruitx = rand() % (height - 2) + 1;
		fruity = rand() % (width - 2) + 1;
		gotoxy(fruitx, fruity);
		printf("*");
		gotoxy(snakeX[i], snakeY[i]);
	}

	// 과일 충돌 (2P)
	if (mode == 2 && p2_x == fruitx && p2_y == fruity) {
		score_2p += 10;

		// 새 꼬리 위치를 마지막 꼬리 위치로 초기화
		snake2X[length2] = snake2X[length2 - 1];
		snake2Y[length2] = snake2Y[length2 - 1];
		length2++; // 꼬리 길이 증가
		if (length2 % 2 == 1) {
			length2++;
		}

		fruitx = rand() % (height - 2) + 1;
		fruity = rand() % (width - 2) + 1;
		gotoxy(fruitx, fruity);
		printf("*");
	}


	// 뱀 출력 (1p)
	for (int i = 0; i < length; i++) {
		gotoxy(snakeX[i], snakeY[i]);
		printf("0");
	}
	// 뱀 출력 (2p)

	for (int i = 0; i < length2; i++) {
		gotoxy(snake2X[i], snake2Y[i]);
		printf("0");
		/*if (length2 % 2 == 1 && length2 != 1) {
			printf("0");
		}*/
	}

	input();
}

void main()
{
	// 화면 구성
	setup();

	// 게임 오버 조건
	while (!gameover) {

		// 함수 호출 
		draw();
		input();
		logic();
	}

	// 게임 종료 메시지 출력 
	gotoxy(height + 2, 0);
	if (mode == 1) {
		printf("Game Over! Final Score: %d\n", score);
	}
	else if (mode == 2) {
		printf("Game Over! Final Score_1p : %d Score_2p : %d\n", score, score_2p);
	}


}