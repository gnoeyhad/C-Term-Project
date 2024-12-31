#pragma once
#include <stdlib.h>
#include <windows.h>
#include <time.h>

int horizontalCheck[9][10] = { 0 }; // ���� ���� ���� ��� ���� üũ
int verticalCheck[9][10] = { 0 }; // ���� ���� ���� ��� ���� üũ
int boxCheck[9][10] = { 0 }; // 3x3 ���� ���� ��� ���� üũ


int solved = 0; // Ǯ�� �� ���� Ȯ�� 
int a_board[9][9] = { 0, };// ������ ���� ���¸� �ӽ� ���� 

void ShuffleRow(int board[9][9]); // ��(row)�� �������� ����
void ShuffleCol(int board[9][9]); // ��(col)�� �������� ����
void ShuffleNum(int board[9][9]); // Ư���� �ΰ��� ���ڸ� ��ȯ�Ͽ� ���带 ����

int SolveBoardRecursion(int s_board[9][9]); // ������ ���� Ǯ�� (����� �˰��� - ��Ʈ��ŷ ���)
void SolveBoard(int s_board[9][9]); // ���� Ǯ�̸� �ʱ�ȭ�� ��, ������ ���� Ǯ��(Recursion) ȣ��
void DrawAnswer(int s_board[9][9], bool open_answer); // ���� ���� �Լ� 

// �ܼ��� Ŀ���� �̵��ϴ� �Լ� 
void gotoxy(int x, int y)
{
	COORD pos = { x, y }; // x, y�� ������ �ִ� ����ü 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); // Ŀ�� �̵�
}

// ���� ���� �Լ� 
void DrawAnswer(int s_board[9][9], bool open_answer)
{
	if (open_answer) // ����ڰ� ���� ���� Ű�� ������ ��� 
	{
		if (!solved) // ���� Ǯ�̰� ���� �ʾҴٸ� 
		{
			solved = 1; // Ǯ�̰� �� ���·� ����
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					a_board[i][j] = s_board[i][j]; // ���� ���带 ����
				}
			}
			SolveBoard(a_board); // ���带 Ǯ��
		}

		// ���带 �ֿܼ� ���
		int posy = 0;
		gotoxy(40, posy); // �ܼ� Ŀ�� �̵� 

		for (int y = 0; y < 9; ++y) // ������ ���忡 ���� ���
		{

			for (int x = 0; x < 9; ++x) // ù��° �� ���
			{
				if (a_board[x][y] > 10) // ������ ä���� ���� ���
				{
					printf(" _ "); // _ ���
				}
				else
				{
					printf("   "); 
				}

				if (x % 3 == 2) // 3ĭ���� ���� ��� 3x3 ��� ����
					printf("  ");
			}

			gotoxy(40, ++posy); // Ŀ�� �̵� (���� ��)
			for (int x = 0; x < 9; ++x) // �ι�° �� ���
			{
				if (a_board[x][y] > 0) // ������ ä���� ���� ���
					printf(" %d ", a_board[x][y] % 10); // ���� ���
				else
					printf(" . "); // . ��� (����ڰ� ä���� �ϴ� ��)

				if (x % 3 == 2) // 3ĭ���� ���� ��� 3x3 ��� ����
					printf("  ");
			}

			gotoxy(40, ++posy); /// Ŀ�� �̵� (���� ��)
			if (y % 3 == 2) // 3�ٸ��� �� �̵� 
				gotoxy(40, ++posy); // Ŀ�� �̵� (���� ��)
		}

		gotoxy(0, posy); // ������ ����� �� ���� �� �������� �̵�
	}
}

// ������ ���� Ǯ�� (����� �˰��� - ��Ʈ��ŷ ���)
int SolveBoardRecursion(int s_board[9][9])
{
	int x = -1, y = -1; // ��ĭ�� ��ǥ�� �����ϴ� ���� 
	int tx, ty; 

	// ���� ��ü�� ���鼭 0�� ���� ã��(��ĭ)
	for (ty = 0; ty < 9; ty++) // ��
	{
		for (tx = 0; tx < 9; tx++) // ��
		{
			if (s_board[tx][ty] == 0) // ��ĭ �߰� �� 
			{
				x = tx; // ��ĭ�� x��ǥ ����
				y = ty; // ��ĭ�� y��ǥ ����
				break;
			}
		}
		if (x != -1) // ��ĭ�� �̹� �߰ߵ��� �� ���� 
			break;
	}

	// ���忡 ��ĭ�� ���� ��� 
	if (x == -1) 
	{
		return 1; 
	}

	// ��ĭ�� ���� 1~9�� ����
	for (int num = 1; num <= 9; num++)
	{
		// ���� �ߺ� üũ(����, ����, 3x3 �ڽ�)
		if (horizontalCheck[y][num] == 0 && verticalCheck[x][num] == 0 && boxCheck[(x / 3) + (y / 3) * 3][num] == 0) // ���� ���� �ڽ��� �ߺ��� ���� ��
		{
			horizontalCheck[y][num] = 1; // ���� ������ ���� �Է�
			verticalCheck[x][num] = 1; // ���� ������ ���� �Է�
			boxCheck[x / 3 + (y / 3) * 3][num] = 1; // 3x3 �ڽ��� ���� �Է�
			s_board[x][y] = num; // ������ ���忡 ���� ��ġ 

			if (SolveBoardRecursion(s_board)) // ��������� ���� ĭ�� ���� ��ġ
			{
				return 1; // ������ Ǯ�̰� �� �� ��� 
			}
			else
			{
				horizontalCheck[y][num] = 0; // ���ڸ� ���� �������� ����
				verticalCheck[x][num] = 0; // ���ڸ� ���� �������� ����
				boxCheck[x / 3 + (y / 3) * 3][num] = 0; // ���ڸ� 3x3 �ڽ����� ���� 
				s_board[x][y] = 0; // ������ ���忡 ���ڸ� 0���� �����Ͽ� ���� 
			}
		}
	}
	return 0;
}
 
// ���� Ǯ�̸� �ʱ�ȭ�� ��, ������ ���� Ǯ��(Recursion) ȣ��
void SolveBoard(int s_board[9][9])
{
	int num;

	// �ߺ��� üũ�ϴ� �迭 �ʱ�ȭ
	for (int i = 0; i < 9; i++) { 
		for (int j = 0; j < 10; j++) {
			horizontalCheck[i][j] = 0; // ���� üũ �迭 �ʱ�ȭ
			verticalCheck[i][j] = 0; // ���� üũ �迭 �ʱ�ȭ
			boxCheck[i][j] = 0; // 3x3 �ڽ� üũ �迭 �ʱ�ȭ 
		}
	}

	// ���� ���� ��� ����(s_board)�� check�迭�� ���
	for (int ty = 0; ty < 9; ty++)
	{
		for (int tx = 0; tx < 9; tx++)
		{
			if (s_board[tx][ty] != 0) // ��ĭ�� �ƴ� ��� 
			{
				num = s_board[tx][ty]; // ���� ĭ�� ���� 

				if (num > 10) { // �־��� ������ ��� 
					num = num % 10;
					horizontalCheck[ty][num] = 1; // ���� ������ ���� �Է�
					verticalCheck[tx][num] = 1; // ���� ������ ���� �Է�
					boxCheck[tx / 3 + (ty / 3) * 3][num] = 1; // 3x3 �ڽ��� ���� �Է�
				}
				else {
					horizontalCheck[ty][num] = 0; // ���ڸ� ���� �������� ����
					verticalCheck[tx][num] = 0; // ���ڸ� ���� �������� ����
					boxCheck[tx / 3 + (ty / 3) * 3][num] = 0; // ���ڸ� 3x3 �ڽ����� ���� 
					s_board[tx][ty] = 0; // ������ ���忡 ���ڸ� 0���� �����Ͽ� ���� 
				}

			}
		}
	}

	SolveBoardRecursion(s_board); // ��Ʈ��ŷ ȣ���Ͽ� ���� Ǯ�� 
}

// ���ο� ������ ����, level: �����Ǵ� ���� �� 
void MakeStage(int board[9][9], int level)
{
	srand((unsigned int)time(NULL)); // random ���� ������ ���� �õ� ����
	int seed[9][9]; // �ʱ� ������ �õ�
	int num = 0; // �ʱ� �� ����

	// 3x3 �ڽ� ��Ģ�� �°� �ʱ�ȭ 
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			seed[i][j] = ((i / 3 + num++) % 9) + 1; // ���� ��ġ 
		}
		num += 3; // �� �̵� 
	}

	// 10ȸ ������ ������ �������� ���带 ����
	for (int i = 0; i < 10; ++i)
	{
		int randAct = rand() % 3; // 0~2�� ���� ����
		switch (randAct) 
		{
		case 0:
			ShuffleRow(seed); // �� ����
			break;
		case 1:
			ShuffleCol(seed); // �� ����
			break;
		default:
			ShuffleNum(seed); // ���� ���� 
			break;
		}
	}

	// ���̵��� ���� ���忡 ���ڸ� �߰�(������ ����ڿ����־����� ����)
	for (int i = 0; i < level; ++i) 
	{
		int x = rand() % 9; // 0~8�� ���� �����Ͽ� x��ǥ ����
		int y = rand() % 9; // 0~8�� ���� �����Ͽ� y��ǥ ���� 

		board[x][y] = 10 + seed[x][y]; // ������ ä���� ���ڸ� ����
									   // ���� 10 �̻��� ���ڸ� ������ ������
									   // ����ڰ� ���ڸ� ä�� �� �ֵ��� �ϱ� ���� ó��
	}
}

// ��(row)�� �������� ���� - ��� �������� ���ڸ� �����ϸ鼭 �������� ��Ģ ���� 
void ShuffleRow(int board[9][9]) 
{
	int area = rand() % 3; // 3x3 ��� �� �ϳ��� ����
	int row1 = area * 3 + rand() % 3; // ������ ��Ͽ��� �������� �� ���� ����
	int row2 = area * 3 + rand() % 3;

	if (row1 == row2) // ���� ������ ���� �ʿ� x
		return;

	for (int i = 0; i < 9; ++i) // �ΰ��� ���� �����Ͽ� ��ȯ
	{
		int tmp = board[i][row1];
		board[i][row1] = board[i][row2];
		board[i][row2] = tmp;
	}
}

// ��(col)�� �������� ���� - ��� �������� ���ڸ� �����ϸ鼭 �������� ��Ģ ���� 
void ShuffleCol(int board[9][9]) 
{
	int area = rand() % 3; // 3x3 ��� �� �ϳ��� ����
	int row1 = area * 3 + rand() % 3; // ������ ��Ͽ��� �������� �� ���� ����
	int row2 = area * 3 + rand() % 3;

	if (row1 == row2) // ���� ���ٸ� ���� �ʿ� x
		return;

	for (int i = 0; i < 9; ++i) // �ΰ��� ���� �����Ͽ� ��ȯ
	{
		int tmp = board[row1][i];
		board[row1][i] = board[row2][i];
		board[row2][i] = tmp;
	}
}

// Ư���� �ΰ��� ���ڸ� ��ȯ�Ͽ� ���带 ���� - ������ ��ġ�� �����ϸ鼭 �ٲٱ⿡ ��Ģ ����
void ShuffleNum(int board[9][9])
{
	int num1 = rand() % 9; // 0~8 ������ ���� ���� 
	int num2 = rand() % 9; // 0~8 ������ ���� ���� 

	if (num1 == num2) // ���ڰ� ���ٸ� ��ȯ�� �ʿ� x
		return;

	for (int i = 0; i < 9; ++i) // ���� �� num1 ���ڸ� ���� 0���� ����
	{
		for (int j = 0; j < 9; ++j)
		{
			if (board[i][j] == num1) // ��������(num1)�� ���ٸ� 0���� ����
				board[i][j] = 0;
		}
	}

	for (int i = 0; i < 9; ++i) // ���� �� num2 ���ڸ� ���� num1�� ����
	{
		for (int j = 0; j < 9; ++j)
		{
			if (board[i][j] == num2) // ��������(num2)�� ���ٸ� num1�� ����
				board[i][j] = num1;
		}
	}

	for (int i = 0; i < 9; ++i) // ���� �� 0�� ���� num2�� ���� 
	{
		for (int j = 0; j < 9; ++j)
		{
			if (board[i][j] == 0) // 0�� ���ٸ� ��������(num2)�� ����
				board[i][j] = num2;
		}
	}
}