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
int snakeX[MAX_LENGTH], snakeY[MAX_LENGTH]; // ���� ��ü ��ġ
int length = 1;                             // ���� �ʱ� ����

// 2P ��� ���� ����
int mode = 1; // 1: 1P ���, 2: 2P ���
int p2_x, p2_y, p2_flag, score_2p;
int snake2X[MAX_LENGTH], snake2Y[MAX_LENGTH]; // 2P �� ��ġ
int length2 = 1;

// ���ع� ���� ����
int obstacleX[MAX_OBSTACLES];
int obstacleY[MAX_OBSTACLES];
int obstacleCount = 0;				// ���� Ȱ��ȭ�� ���ع� ��
int obstacleTimer[MAX_OBSTACLES];	// �� ���ع��� Ÿ�̸�
int max_obstacles = 3;				// �ʱ� �ִ� ���ع� ����
int obstacle_size = 1;				// �ʱ� ���ع� ũ�� (1x1)

// ���� �ӵ� (Sleep �ð�) ���� ����
int snake_speed = 300; // �ʱ� �ӵ�: 300ms

// ������ �ڽ� ���� ����
int boxX, boxY;             // ������ �ڽ� ��ġ
int box_active = 0;         // ������ �ڽ� Ȱ�� ����
int box_spawn_time = 40;    // �ڽ� ���� ����
int box_duration = 10;      // �ڽ� ���� �ð�
clock_t last_box_time = 0;  // ������ �ڽ� ���� �ð�

// �߰� ���� ���� ����
int bonusFruitX, bonusFruitY;
int bonus_fruit_active = 0;

// ��輱 �迭
char boundary[20][20];

// ���� �ð� ����
clock_t start_time;
int elapsed_time = 0;

// ��ġ �̵� ȭ�� ǥ��
void gotoxy(int x, int y) {
	printf("\033[%d;%dH", x + 1, y + 1); // x, y�� 0���� �����ϹǷ� +1
}

// ȭ�� �ʱ�ȭ
void resetScreen() {
	system("cls");
}

// ��輱 �迭 �ʱ�ȭ
void initBoundary() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
				boundary[i][j] = '#'; // ��輱 ��
			}
			else {
				boundary[i][j] = ' '; // �� ����
			}
		}
	}
}

// ��輱 ���
void printBoundary() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			gotoxy(i, j);
			printf("%c", boundary[i][j]);
		}
	}
}

// ��輱 �Ѽ� �� ����
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

// Ư�� ��ġ�� ��輱 ��ȯ
char getBoundaryCharAt(int x, int y) {
	return boundary[x][y];
}

// Ư�� ��ġ�� ������Ʈ�� �ִ��� Ȯ��
int isPositionOccupied(int px, int py) {
	// ��輱 Ȯ��
	if (px <= 0 || px >= height - 1 || py <= 0 || py >= width - 1) return 1;

	// ��� ��ġ���� Ȯ��
	for (int i = 0; i < length; i++) {
		if (snakeX[i] == px && snakeY[i] == py) return 1;
	}

	if (mode == 2) {
		for (int i = 0; i < length2; i++) {
			if (snake2X[i] == px && snake2Y[i] == py) return 1;
		}
	}

	// ���ϰ� ��ġ���� Ȯ��
	if (fruitx == px && fruity == py) return 1;

	// ���ع��� ��ġ���� Ȯ��
	for (int i = 0; i < obstacleCount; i++) {
		if (obstacleX[i] == px && obstacleY[i] == py) return 1;
	}

	// �߰� ���� ���ſ� ��ġ���� Ȯ��
	if (bonus_fruit_active && bonusFruitX == px && bonusFruitY == py) return 1;

	// ������ �ڽ��� ��ġ���� Ȯ��
	if (box_active && boxX == px && boxY == py) return 1;

	return 0; // �� ��ġ
}

// ���� �ʱ� ����
void setup()
{
	// ���� ������ �ʱ�ȭ
	srand(time(NULL)); // ���� �ð��� �õ�� ����

	gameover = 0;

	// ��� ����
	printf("Select Mode: 1(1P), 2(2P)\n");
	scanf_s("%d", &mode);
	if (mode != 1 && mode != 2) mode = 1; // �⺻�� 1P

	// �� �ʱ� ���� (1p)
	x = height / 2;
	y = width / 2;
	snakeX[0] = x;
	snakeY[0] = y;

	// �� �ʱ� ���� (2p)
	if (mode == 2) {
		p2_x = height / 2;
		p2_y = (3 * width) / 4;
		snake2X[0] = p2_x;
		snake2Y[0] = p2_y;
	}

	// ù��° ���� ��ġ ����
	fruitx = rand() % (height - 2) + 1;
	fruity = rand() % (width - 2) + 1;

	score = 0;
	if (mode == 2) {
		score_2p = 0;
	}
	obstacleCount = 0;

	// ��輱 �ʱ�ȭ
	initBoundary();

	// ���� �ð� ���
	start_time = clock();

	//ȭ�� �ʱ�ȭ
	resetScreen();

	// ȭ�� �ʱ�ȭ �� ��輱 ���
	resetScreen();
	printBoundary();

	// ���� ���� ���
	gotoxy(fruitx, fruity);
	printf("*");
}

//ȭ�� �׸���
void draw()
{
	// ���� ��� & ���� ���� ���� ���� ���
	if (mode == 1) {
		gotoxy(height, 0);
		printf("Score : %d   ", score);				// ���� ���
		printf("Time : %d sec   ", elapsed_time);	// ��� �ð� ���
		printf("Speed : %d ms   ", snake_speed);	// �ӵ� ���
		printf("Mode : 1p   ");					//��� ǥ��(1p)
		printf("\npress X to quit the game");
	}
	else if (mode == 2) {
		gotoxy(height, 0);
		printf("Score1 : %d   ", score);				// ���� ���(1p)
		printf("Score2 : %d   ", score_2p);				// ���� ���(2p)
		printf("Time : %d sec   ", elapsed_time);	// ��� �ð� ���
		printf("Speed : %d ms   ", snake_speed);	// �ӵ� ���
		printf("Mode : 2p   ");					//��� ǥ��(2p)
		printf("\npress X to quit the game");
	}
}

// Ű �Է�
void input()
{
	if (_kbhit()) {
		char key = getch();

		// 1p Ű���ε�
		if (mode == 1 || (mode == 2 && key != 0)) {
			switch (key) {
			case 'a':
				if (flag != 3) flag = 1; // ���� �̵� ( ���������� �̵� ���� �ƴ� ���� ���� )
				break;
			case 's':
				if (flag != 4) flag = 2; // �Ʒ��� �̵� ( ���� �̵� ���� �ƴ� ���� ���� )
				break;
			case 'd':
				if (flag != 1) flag = 3; // ������ �̵� ( �������� �̵� ���� �ƴ� ���� ���� )
				break;
			case 'w':
				if (flag != 2) flag = 4; // ���� �̵� ( �Ʒ��� �̵� ���� �ƴ� ���� ���� )
				break;
			case 'x':
				gameover = 1; // ���� ����
				break;
			}
		}

		//2p Ű���ε�
		if (mode == 2 && key != 0) {
			//key = getch();
			switch (key) {
			case 75: // �� ����Ű
				if (p2_flag != 3) p2_flag = 1;
				break;
			case 80: // �� ����Ű
				if (p2_flag != 4) p2_flag = 2;
				break;
			case 77: // �� ����Ű
				if (p2_flag != 1) p2_flag = 3;
				break;
			case 72: // �� ����Ű
				if (p2_flag != 2) p2_flag = 4;
				break;
			}
		}
	}
}

// ������ �ڽ� ����
void generateItemBox() {
	if (!box_active && elapsed_time >= box_spawn_time) {
		int valid = 0;
		while (!valid) {
			boxX = rand() % (height - 2) + 1;
			boxY = rand() % (width - 2) + 1;
			valid = 1;

			// �ڽ��� ��, ����, ���ع��� ��ġ�� �ʵ��� ����
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
		printf("��"); // ������ �ڽ� ǥ��
	}
}

// ������ �ڽ� ȿ�� ����
void applyItemBoxEffect() {
	int effect = rand() % 6; // 0: �ӵ� ����, 1: ���ع� ����, 2: �߰� ���� ���� ����
	// 3: ���� ����, 4: ���� �߰�, 5: �ӵ� ����

	if (effect == 0) {
		// �ӵ� ����
		if (snake_speed > 50) { // �ּ� �ӵ� ����
			snake_speed -= 10;
		}
		gotoxy(height + 2, 0);
		printf("\nSpeed increased!\n");
	}
	else if (effect == 1 && obstacleCount > 0) {
		// ���ع� ����
		for (int i = 0; i < obstacleCount; i++) {
			for (int dx = 0; dx < obstacle_size; dx++) {
				for (int dy = 0; dy < obstacle_size; dy++) {
					gotoxy(obstacleX[i] + dx, obstacleY[i] + dy);
					printf(" ");
				}
			}
		}
		obstacleCount = 0; // ��� ���ع� ����
		gotoxy(height + 2, 0);
		printf("\nObstacles removed!\n");
	}
	else if (effect == 2) {
		// �߰� ���� ���� ����
		int bonusX, bonusY, valid = 0;
		while (!valid) {
			bonusX = rand() % (height - 2) + 1;
			bonusY = rand() % (width - 2) + 1;
			valid = 1;

			// �߰� ���� ���Ű� �ٸ� ������Ʈ�� ��ġ�� �ʵ��� ����
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
		// ���� ����
		gotoxy(snakeX[length - 1], snakeY[length - 1]);
		printf(" "); // ���� ����
		length--;
		gotoxy(height + 2, 0);
		printf("\nTail removed!\n");
	}
	else if (mode == 2 && effect == 3 && length2 > 1) {	// 2p
		// ���� ����
		gotoxy(snake2X[length2 - 1], snake2Y[length2 - 1]);
		printf(" "); // ���� ����
		length2--;
		gotoxy(height + 2, 0);
		printf("\nTail removed!\n");
	}
	else if (effect == 4) { // 1p
		// ���� �߰�
		length++;
		snakeX[length - 1] = snakeX[length - 2];
		snakeY[length - 1] = snakeY[length - 2];
		gotoxy(height + 2, 0);
		printf("\nTail added!\n");
	}
	else if (mode == 2 && effect == 4) { // 2p
		// ���� �߰�
		length2++;
		snake2X[length2 - 1] = snake2X[length2 - 2];
		snake2Y[length2 - 1] = snake2Y[length2 - 2];
		gotoxy(height + 2, 0);
		printf("\nTail added!\n");
	}
	else if (effect == 5) {
		// �ӵ� ����
		if (snake_speed < 500) { // �ִ� �ӵ� ����
			snake_speed += 10;
		}
		printf("\nSpeed decreased!\n");
	}

	box_active = 0; // �ڽ� ��Ȱ��ȭ
	box_spawn_time = elapsed_time + 40; // ���� ���� �ð� ����
}

// �ڽ� ���� �ð� ����
void manageItemBox() {
	if (box_active && elapsed_time >= box_spawn_time + box_duration) {
		gotoxy(boxX, boxY);
		printf(" "); // �ڽ� ����
		box_active = 0;
		box_spawn_time = elapsed_time + 40; // ���� ���� �ð� ����
	}
}

// �߰� ���� ���� ����
void manageBonusFruit() {
	if (bonus_fruit_active && x == bonusFruitX && y == bonusFruitY) {
		score += 20; // �߰� ���� ����
		bonus_fruit_active = 0;
		gotoxy(bonusFruitX, bonusFruitY);
		printf(" ");
	}
}

// ���ع� ����
void generateObstacle() {
	if (obstacleCount < max_obstacles) {
		int ox, oy, valid;

		do {
			valid = 1;

			// ���ع��� ���� ��ġ ����
			ox = rand() % (height - 2 - obstacle_size) + 1;
			oy = rand() % (width - 2 - obstacle_size) + 1;

			// ���ع��� �� �Ǵ� ���ϰ� ��ġ�� �ʵ��� Ȯ��
			if (valid && (ox == fruitx && oy == fruity)) valid = 0;
			for (int i = 0; i < length; i++) {
				if (valid && (snakeX[i] == ox && snakeY[i] == oy)) {
					valid = 0;
					break;
				}
			}

			// ���ع��� ��輱�� ħ������ �ʵ��� Ȯ��
			if (ox <= 0 || ox + obstacle_size >= height - 1 ||
				oy <= 0 || oy + obstacle_size >= width - 1) {
				valid = 0;
			}
		} while (!valid);

		// ���ع� ��ġ�� Ÿ�̸� ����
		obstacleX[obstacleCount] = ox;
		obstacleY[obstacleCount] = oy;
		obstacleTimer[obstacleCount] = elapsed_time + 5; // ���ع� ���� �ð�
		obstacleCount++;

		// ���ع� ���
		for (int dx = 0; dx < obstacle_size; dx++) {
			for (int dy = 0; dy < obstacle_size; dy++) {
				gotoxy(ox + dx, oy + dy);
				printf("@");
			}
		}
	}
}

// ���ع� ���� (�ð� ���� �� ����)
void manageObstacles() {
	for (int i = 0; i < obstacleCount; i++) {
		if (elapsed_time >= obstacleTimer[i]) {
			// �ð��� ����� ���ع� ����
			for (int dx = 0; dx < obstacle_size; dx++) {
				for (int dy = 0; dy < obstacle_size; dy++) {
					gotoxy(obstacleX[i] + dx, obstacleY[i] + dy);
					printf(" ");
				}
			}

			// ���ع� ������ ����
			obstacleX[i] = obstacleX[obstacleCount - 1];
			obstacleY[i] = obstacleY[obstacleCount - 1];
			obstacleTimer[i] = obstacleTimer[obstacleCount - 1];
			obstacleCount--;
			i--;
		}
	}
}

// �ð��� ���� ���ع� ũ�� �� ���� ���� ����
void updateObstacleParameters() {
	if (elapsed_time % 40 == 0 && elapsed_time > 0) { // 40�ʸ��� ����
		if (max_obstacles < MAX_OBSTACLES) {
			max_obstacles++; // ���ع� �ִ� ���� ����
		}
		if (obstacle_size < 5) { // ���ع� ũ�� ���� (�ִ� 5x5)
			obstacle_size++;
		}
	}
}

// ������ ����
void logic()
{
	Sleep(snake_speed);			//�ӵ� ����

	// ��� �ð� ������Ʈ
	elapsed_time = (clock() - start_time) / CLOCKS_PER_SEC;

	// ���� �ð��� ����Կ� ���� ���ع� ���� ( �ֱ� : 13�� / ���� Ȯ�� : 50% )
	if (elapsed_time % 13 == 0 && rand() % 2 == 0) {
		generateObstacle();
	}

	// ������ �ڽ� ����
	generateItemBox();

	// ������ �ڽ� ����
	manageItemBox();

	// ������ �ڽ� ȿ�� ����
	if ((x == boxX && y == boxY && box_active) || (p2_x == boxX && p2_y == boxY && box_active)) {
		applyItemBoxEffect();
	}

	// �߰� ���� ���� ����
	manageBonusFruit();

	// ���ع� ����
	manageObstacles();

	// ���� ��ġ�� ����� (1p)
	gotoxy(snakeX[length - 1], snakeY[length - 1]);
	printf(" ");

	// ���� ��ġ�� ����� (2p)
	if (mode == 2) {
		gotoxy(snake2X[length2 - 1], snake2Y[length2 - 1]);
		printf(" ");
	}

	// ��ü �̵� (�ڿ������� ������ �̵�) (1p)
	for (int i = length - 1; i > 0; i--) {
		snakeX[i] = snakeX[i - 1];
		snakeY[i] = snakeY[i - 1];
	}

	// ��ü �̵� (�ڿ������� ������ �̵�) (2p)
	if (mode == 2) {
		for (int i = length2 - 1; i > 0; i--) {
			snake2X[i] = snake2X[i - 1];
			snake2Y[i] = snake2Y[i - 1];
		}
	}
	//�� �̵� ����(1p)
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

	// �� �̵� ����(2p)
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

	// �� �� �浹 Ȯ�� (1p)
	if (x <= 0 || x >= height - 1 || y <= 0 || y >= width - 1) {
		gameover = 1;
		if (mode == 2) {
			gotoxy(height + 3, 0);
			printf(" Player 2 wins!\n");
		}
	}

	// �� �� �浹 Ȯ�� (2P)
	if (mode == 2 && (p2_x <= 0 || p2_x >= height - 1 || p2_y <= 0 || p2_y >= width - 1)) {
		gotoxy(height + 3, 0);
		printf(" Player 1 wins!\n");
		gameover = 1;
	}

	// ���� �浹 Ȯ��
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

	// �Ӹ��� ��ü�� �浹�ߴ��� Ȯ�� (1p)
	for (int i = 1; i < length; i++) {
		if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
			gotoxy(height + 3, 0);
			printf(" Player 2 wins!\n");
			gameover = 1;
		}
	}
	// �Ӹ��� ��ü�� �浹�ߴ��� Ȯ�� (2p)
	if (mode == 2) {
		for (int i = 1; i < length2; i++) {
			if (snake2X[0] == snake2X[i] && snake2Y[0] == snake2Y[i]) {
				gotoxy(height + 3, 0);
				printf("Player 1 wins!\n");
				gameover = 1;
			}
		}
	}

	// ���ع� �浹 Ȯ�� (1p)
	for (int i = 0; i < obstacleCount; i++) {
		if (snakeX[0] == obstacleX[i] && snakeY[0] == obstacleY[i]) {
			gotoxy(height + 3, 0);
			printf("Player 2 wins!\n");
			gameover = 1;
		}
	}
	// ���ع� �浹 Ȯ�� (2p)
	for (int i = 0; i < obstacleCount; i++) {
		if (snake2X[0] == obstacleX[i] && snake2Y[0] == obstacleY[i]) {
			gotoxy(height + 3, 0);
			printf("Player 1 wins!\n");
			gameover = 1;
		}
	}

	// ���� �浹 (1P)
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

	// ���� �浹 (2P)
	if (mode == 2 && p2_x == fruitx && p2_y == fruity) {
		score_2p += 10;

		// �� ���� ��ġ�� ������ ���� ��ġ�� �ʱ�ȭ
		snake2X[length2] = snake2X[length2 - 1];
		snake2Y[length2] = snake2Y[length2 - 1];
		length2++; // ���� ���� ����
		if (length2 % 2 == 1) {
			length2++;
		}

		fruitx = rand() % (height - 2) + 1;
		fruity = rand() % (width - 2) + 1;
		gotoxy(fruitx, fruity);
		printf("*");
	}


	// �� ��� (1p)
	for (int i = 0; i < length; i++) {
		gotoxy(snakeX[i], snakeY[i]);
		printf("0");
	}
	// �� ��� (2p)

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
	// ȭ�� ����
	setup();

	// ���� ���� ����
	while (!gameover) {

		// �Լ� ȣ�� 
		draw();
		input();
		logic();
	}

	// ���� ���� �޽��� ��� 
	gotoxy(height + 2, 0);
	if (mode == 1) {
		printf("Game Over! Final Score: %d\n", score);
	}
	else if (mode == 2) {
		printf("Game Over! Final Score_1p : %d Score_2p : %d\n", score, score_2p);
	}


}