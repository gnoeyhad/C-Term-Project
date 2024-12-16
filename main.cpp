#include <iostream>
#include "Sudoku.h"
using namespace std;

int main()
{
    Sudoku sudoku; // Sudoku 객체 생성 
    sudoku.init(50); // 사용자에게 주어지는 숫자의 개수 

    while (true)
    {
        system("cls"); 
        sudoku.Draw(); // 스도쿠 판 그리기 

        if (sudoku.CheckBoard()) // 보드 판이 전부 중복 없이 채워진 경우 
        {
            cout << "CLEAR!!!\n";
            break;
        }

        cout << "\n방향키 : 이동 / 1~9 : 숫자 입력 / 0 : 숫자 지우기 / ! : 답안 보기\n";
        sudoku.ControlInput(); // 사용자 입력 처리
        
    }

    cout << "\n프로그램을 종료합니다.";
    return 0;
}
