#pragma once
#include <stdlib.h>
#include <windows.h>
#include <time.h>

int horizontalCheck[9][10] = { 0 }; // 가로 영역 숫자 사용 여부 체크
int verticalCheck[9][10] = { 0 }; // 세로 영역 숫자 사용 여부 체크
int boxCheck[9][10] = { 0 }; // 3x3 영역 숫자 사용 여부 체크


int solved = 0; // 풀이 된 상태 확인 
int a_board[9][9] = { 0, };// 스도쿠 보드 상태를 임시 저장 

void ShuffleRow(int board[9][9]); // 행(row)을 무작위로 섞음
void ShuffleCol(int board[9][9]); // 열(col)을 무작위로 섞음
void ShuffleNum(int board[9][9]); // 특정한 두개의 숫자를 교환하여 보드를 섞음

int SolveBoardRecursion(int s_board[9][9]); // 스도쿠 퍼즐 풀이 (재귀적 알고리즘 - 백트래킹 사용)
void SolveBoard(int s_board[9][9]); // 보드 풀이를 초기화한 뒤, 스도쿠 퍼즐 풀이(Recursion) 호출
void DrawAnswer(int s_board[9][9], bool open_answer); // 정답 공개 함수 

// 콘솔의 커서를 이동하는 함수 
void gotoxy(int x, int y)
{
	COORD pos = { x, y }; // x, y를 가지고 있는 구조체 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); // 커서 이동
}

// 정답 공개 함수 
void DrawAnswer(int s_board[9][9], bool open_answer)
{
	if (open_answer) // 사용자가 정답 공개 키를 눌렀을 경우 
	{
		if (!solved) // 아직 풀이가 되지 않았다면 
		{
			solved = 1; // 풀이가 된 상태로 변경
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					a_board[i][j] = s_board[i][j]; // 현재 보드를 복사
				}
			}
			SolveBoard(a_board); // 보드를 풀기
		}

		// 보드를 콘솔에 출력
		int posy = 0;
		gotoxy(40, posy); // 콘솔 커서 이동 

		for (int y = 0; y < 9; ++y) // 스도쿠 보드에 숫자 출력
		{

			for (int x = 0; x < 9; ++x) // 첫번째 줄 출력
			{
				if (a_board[x][y] > 10) // 사전에 채워진 값인 경우
				{
					printf(" _ "); // _ 출력
				}
				else
				{
					printf("   "); 
				}

				if (x % 3 == 2) // 3칸마다 공백 출력 3x3 블록 구분
					printf("  ");
			}

			gotoxy(40, ++posy); // 커서 이동 (다음 줄)
			for (int x = 0; x < 9; ++x) // 두번째 줄 출력
			{
				if (a_board[x][y] > 0) // 사전에 채워진 값인 경우
					printf(" %d ", a_board[x][y] % 10); // 숫자 출력
				else
					printf(" . "); // . 출력 (사용자가 채워야 하는 값)

				if (x % 3 == 2) // 3칸마다 공백 출력 3x3 블록 구분
					printf("  ");
			}

			gotoxy(40, ++posy); /// 커서 이동 (다음 줄)
			if (y % 3 == 2) // 3줄마다 줄 이동 
				gotoxy(40, ++posy); // 커서 이동 (다음 줄)
		}

		gotoxy(0, posy); // 숫자이 출력이 다 끝난 뒤 왼쪽으로 이동
	}
}

// 스도쿠 퍼즐 풀이 (재귀적 알고리즘 - 백트래킹 사용)
int SolveBoardRecursion(int s_board[9][9])
{
	int x = -1, y = -1; // 빈칸의 좌표를 저장하는 변수 
	int tx, ty; 

	// 보드 전체를 돌면서 0인 값을 찾음(빈칸)
	for (ty = 0; ty < 9; ty++) // 행
	{
		for (tx = 0; tx < 9; tx++) // 열
		{
			if (s_board[tx][ty] == 0) // 빈칸 발견 시 
			{
				x = tx; // 빈칸의 x좌표 저장
				y = ty; // 빈칸의 y좌표 저장
				break;
			}
		}
		if (x != -1) // 빈칸이 이미 발견됐을 시 종료 
			break;
	}

	// 보드에 빈칸이 없는 경우 
	if (x == -1) 
	{
		return 1; 
	}

	// 빈칸에 숫자 1~9를 대입
	for (int num = 1; num <= 9; num++)
	{
		// 숫자 중복 체크(가로, 세로, 3x3 박스)
		if (horizontalCheck[y][num] == 0 && verticalCheck[x][num] == 0 && boxCheck[(x / 3) + (y / 3) * 3][num] == 0) // 가로 세로 박스에 중복이 없을 시
		{
			horizontalCheck[y][num] = 1; // 가로 영역에 숫자 입력
			verticalCheck[x][num] = 1; // 세로 영역에 숫자 입력
			boxCheck[x / 3 + (y / 3) * 3][num] = 1; // 3x3 박스에 숫자 입력
			s_board[x][y] = num; // 스도쿠 보드에 숫자 배치 

			if (SolveBoardRecursion(s_board)) // 재귀적으로 다음 칸에 숫자 배치
			{
				return 1; // 스도쿠에 풀이가 잘 된 경우 
			}
			else
			{
				horizontalCheck[y][num] = 0; // 숫자를 가로 영역에서 제거
				verticalCheck[x][num] = 0; // 숫자를 세로 영역에서 제거
				boxCheck[x / 3 + (y / 3) * 3][num] = 0; // 숫자를 3x3 박스에서 제거 
				s_board[x][y] = 0; // 스도쿠 보드에 숫자를 0으로 변경하여 제거 
			}
		}
	}
	return 0;
}
 
// 보드 풀이를 초기화한 뒤, 스도쿠 퍼즐 풀이(Recursion) 호출
void SolveBoard(int s_board[9][9])
{
	int num;

	// 중복을 체크하는 배열 초기화
	for (int i = 0; i < 9; i++) { 
		for (int j = 0; j < 10; j++) {
			horizontalCheck[i][j] = 0; // 가로 체크 배열 초기화
			verticalCheck[i][j] = 0; // 세로 체크 배열 초기화
			boxCheck[i][j] = 0; // 3x3 박스 체크 배열 초기화 
		}
	}

	// 현재 숫자 사용 여부(s_board)를 check배열에 기록
	for (int ty = 0; ty < 9; ty++)
	{
		for (int tx = 0; tx < 9; tx++)
		{
			if (s_board[tx][ty] != 0) // 빈칸이 아닌 경우 
			{
				num = s_board[tx][ty]; // 현재 칸의 숫자 

				if (num > 10) { // 주어진 숫자의 경우 
					num = num % 10;
					horizontalCheck[ty][num] = 1; // 가로 영역에 숫자 입력
					verticalCheck[tx][num] = 1; // 세로 영역에 숫자 입력
					boxCheck[tx / 3 + (ty / 3) * 3][num] = 1; // 3x3 박스에 숫자 입력
				}
				else {
					horizontalCheck[ty][num] = 0; // 숫자를 가로 영역에서 제거
					verticalCheck[tx][num] = 0; // 숫자를 세로 영역에서 제거
					boxCheck[tx / 3 + (ty / 3) * 3][num] = 0; // 숫자를 3x3 박스에서 제거 
					s_board[tx][ty] = 0; // 스도쿠 보드에 숫자를 0으로 변경하여 제거 
				}

			}
		}
	}

	SolveBoardRecursion(s_board); // 백트래킹 호출하여 퍼즐 풀이 
}

// 새로운 스도쿠를 생성, level: 제공되는 숫자 수 
void MakeStage(int board[9][9], int level)
{
	srand((unsigned int)time(NULL)); // random 난수 생성을 위한 시드 설정
	int seed[9][9]; // 초기 스도쿠 시드
	int num = 0; // 초기 값 숫자

	// 3x3 박스 규칙에 맞게 초기화 
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			seed[i][j] = ((i / 3 + num++) % 9) + 1; // 숫자 배치 
		}
		num += 3; // 행 이동 
	}

	// 10회 셔플을 돌려서 무작위로 보드를 구성
	for (int i = 0; i < 10; ++i)
	{
		int randAct = rand() % 3; // 0~2의 난수 생성
		switch (randAct) 
		{
		case 0:
			ShuffleRow(seed); // 행 섞기
			break;
		case 1:
			ShuffleCol(seed); // 열 섞기
			break;
		default:
			ShuffleNum(seed); // 숫자 섞기 
			break;
		}
	}

	// 난이도에 따라서 보드에 숫자를 추가(사전에 사용자에게주어지는 숫자)
	for (int i = 0; i < level; ++i) 
	{
		int x = rand() % 9; // 0~8의 난수 생성하여 x좌표 선택
		int y = rand() % 9; // 0~8의 난수 생성하여 y좌표 선택 

		board[x][y] = 10 + seed[x][y]; // 사전에 채워진 숫자를 설정
									   // 이후 10 이상의 숫자를 제외한 곳에만
									   // 사용자가 숫자를 채울 수 있도록 하기 위한 처리
	}
}

// 행(row)을 무작위로 섞음 - 블록 내에서만 숫자를 변경하면서 스도쿠의 규칙 유지 
void ShuffleRow(int board[9][9]) 
{
	int area = rand() % 3; // 3x3 블록 중 하나를 선택
	int row1 = area * 3 + rand() % 3; // 선택한 블록에서 랜덤으로 두 행을 선택
	int row2 = area * 3 + rand() % 3;

	if (row1 == row2) // 행이 같으면 섞을 필요 x
		return;

	for (int i = 0; i < 9; ++i) // 두개의 행을 선택하여 교환
	{
		int tmp = board[i][row1];
		board[i][row1] = board[i][row2];
		board[i][row2] = tmp;
	}
}

// 열(col)을 무작위로 섞음 - 블록 내에서만 숫자를 변경하면서 스도쿠의 규칙 유지 
void ShuffleCol(int board[9][9]) 
{
	int area = rand() % 3; // 3x3 블록 중 하나를 선택
	int row1 = area * 3 + rand() % 3; // 선택한 블록에서 랜덤으로 두 열을 선택
	int row2 = area * 3 + rand() % 3;

	if (row1 == row2) // 열이 같다면 섞을 필요 x
		return;

	for (int i = 0; i < 9; ++i) // 두개의 열을 선택하여 교환
	{
		int tmp = board[row1][i];
		board[row1][i] = board[row2][i];
		board[row2][i] = tmp;
	}
}

// 특정한 두개의 숫자를 교환하여 보드를 섞음 - 숫자의 위치를 유지하면서 바꾸기에 규칙 유지
void ShuffleNum(int board[9][9])
{
	int num1 = rand() % 9; // 0~8 사이의 랜덤 숫자 
	int num2 = rand() % 9; // 0~8 사이의 랜덤 숫자 

	if (num1 == num2) // 숫자가 같다면 교환할 필요 x
		return;

	for (int i = 0; i < 9; ++i) // 보드 내 num1 숫자를 전부 0으로 변경
	{
		for (int j = 0; j < 9; ++j)
		{
			if (board[i][j] == num1) // 랜덤숫자(num1)과 같다면 0으로 변경
				board[i][j] = 0;
		}
	}

	for (int i = 0; i < 9; ++i) // 보드 내 num2 숫자를 전부 num1로 변경
	{
		for (int j = 0; j < 9; ++j)
		{
			if (board[i][j] == num2) // 랜덤숫자(num2)와 같다면 num1로 변경
				board[i][j] = num1;
		}
	}

	for (int i = 0; i < 9; ++i) // 보드 내 0을 전부 num2로 변경 
	{
		for (int j = 0; j < 9; ++j)
		{
			if (board[i][j] == 0) // 0과 같다면 랜덤숫자(num2)로 변경
				board[i][j] = num2;
		}
	}
}