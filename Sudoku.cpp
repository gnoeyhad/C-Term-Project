#include <iostream>
#include "StageMaker.h"
#include "Sudoku.h"

// Sudoku 구현 파일 

using namespace std;

// 스도쿠 판 생성
void Sudoku::init(int level) {
    MakeStage(s_board, level); // level 변수의 값에 따라 주어지는 숫자 개수가 설정됨
}

// 스도쿠 판 출력
void Sudoku::Draw()
{
    for (int y = 0; y < 9; ++y) // 행 반복
    {
        for (int x = 0; x < 9; ++x) // 열 반복
        {
            if (s_board[x][y] > 10) // 사용자에게 사전 공개된 숫자인 경우
            {
                cout << " _ "; // 숫자 위 언더바(_)를 추가 
            }
            else
            {
                cout << "   ";
            }

            if (x % 3 == 2) // 3x3 블록을 구분하기 위한 빈칸 추가 
                cout << "  ";
        }
        cout << "\n";

        // 스도쿠 판에 숫자 출력 
        for (int x = 0; x < 9; ++x) // 열 반복
        {
            if (s_selX == x && s_selY == y) // 현재 커서가 위치한 좌표인 경우 
            {
                if (s_board[s_selX][s_selY] > 0) // 숫자가 채워져 있다면
                {
                    cout << '(' << s_board[s_selX][s_selY] % 10 << ')'; // ( ) 로 선택중임을 표시 
                }
                else // 숫자가 아직 안 채워진 경우
                {
                    cout << "(.)";
                }
            }
            else 
            {
                if (s_board[x][y] > 0) // 숫자가 채워져 있는 경우
                    cout << ' ' << s_board[x][y] % 10 << ' '; // 숫자를 출력
                else // 숫자가 아직 안 채워진 경우
                    cout << " . "; // . 출력
            }

            if (x % 3 == 2) // 3x3 블록을 구분하기 위해서 빈 칸 추가
                cout << "  ";
        }
        cout << "\n";

        if (y % 3 == 2) // 3x3 블록을 구분하기 위해 줄바꿈
            cout << "\n";
    }

    if (open_answer) // 답안 보기 = true
    {
        DrawAnswer(s_board, open_answer); // 스도쿠 정답 공개 
    }
}

// 스도쿠 보드의 숫자 중복 여부를 판단 
int Sudoku::CheckBoard()
{
    // 가로줄과 세로줄 검사
    for (int i = 0; i < 9; ++i)
    {
        bool rowCheck[10] = { false }; // 가로줄 숫자 중복 확인용
        bool colCheck[10] = { false }; // 세로줄 숫자 중복 확인용

        for (int j = 0; j < 9; ++j)
        {
            // 가로줄 검사
            if (s_board[j][i] > 0) // 가로줄에 숫자가 있으면(주어진 숫자인 경우)
            {
                int num = s_board[j][i] % 10; // 일의 자리 값 추출(사전에 임의로 10을 더함)
                if (rowCheck[num]) // 이미 사용된 숫자인 경우 
                    return 0; 
                rowCheck[num] = true; // 숫자 사용을 표시 
            }

            // 세로줄 검사
            if (s_board[i][j] > 0) // 세로줄에 숫자가 있으면(주어진 숫자인 경우)
            {
                int num = s_board[i][j] % 10; // 일의 자리 값 추출(사전에 임의로 10을 더함)
                if (colCheck[num]) // 이미 사용된 숫자인 경우 
                    return 0; 
                colCheck[num] = true; // 숫자 사용을 표시 
            }
        }
    }

    // 3x3 영역 검사
    for (int startY = 0; startY < 9; startY += 3)
    {
        for (int startX = 0; startX < 9; startX += 3)
        {
            bool blockCheck[10] = { false }; // 3x3 블록 숫자 중복 확인용

            for (int y = 0; y < 3; ++y) // 블록의 행
            {
                for (int x = 0; x < 3; ++x) // 블록의 열
                {
                    int currentX = startX + x;
                    int currentY = startY + y;

                    if (s_board[currentX][currentY] > 0) // 주어진 숫자가 있으면
                    {
                        int num = s_board[currentX][currentY] % 10; // 일의 자리 값 추출(사전에 임의로 10을 더함)
                        if (blockCheck[num]) // 이미 사용된 숫자인 경우 
                            return 0;
                        blockCheck[num] = true; // 숫자 사용을 표시
                    }
                }
            }

            for (int num = 1; num <= 9; ++num)
            {
                if (!blockCheck[num]) // 3x3 블록 내에서 중복이 발견된 경우 
                    return 0; 
            }
        }
    }

    // 가로줄, 세로줄, 3x3 블록 내 1~9 숫자의 중복이 없는 경우 
    return 1;
}

// 사용자의 입력 처리 
void Sudoku::ControlInput() {
    char inputChar;
    cin >> inputChar; // 키보드 입력 (사용자에게 입력받을 때마다 즉각 아스키코드로 반환)

    switch (inputChar) {
    case 'w': // 위쪽 이동
        s_selY = max(0, s_selY - 1); // 커서 위로 이동
        break;
    case 'a': // 왼쪽 이동
        s_selX = max(0, s_selX - 1); // 커서 왼쪽 이동
        break;
    case 's': // 아래쪽 이동
        s_selY = min(8, s_selY + 1); // 커서 아래로 이동
        break;
    case 'd': // 오른쪽 이동
        s_selX = min(8, s_selX + 1); // 커서 오른쪽 이동
        break;
    case '!': // 답안 보기
        open_answer = !open_answer; // 답안 보기 상태 변경 
        break;
    case '0': // 숫자 지우기
        if (s_board[s_selX][s_selY] <= 10) // 수정 가능한 위치인지 확인
            s_board[s_selX][s_selY] = 0; // 0으로 초기화
        break;
    case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9': // 숫자 입력
        if (s_board[s_selX][s_selY] <= 10) // 수정 가능한 위치인지 확인
            s_board[s_selX][s_selY] = inputChar - '0'; // 입력한 숫자를 보드에 저장
        break;
    }

}

