#include <iostream>
#include "Sudoku.h"
using namespace std;

int main()
{
    Sudoku sudoku; // Sudoku ��ü ���� 
    sudoku.init(50); // ����ڿ��� �־����� ������ ���� 

    while (true)
    {
        system("cls"); 
        sudoku.Draw(); // ������ �� �׸��� 

        if (sudoku.CheckBoard()) // ���� ���� ���� �ߺ� ���� ä���� ��� 
        {
            cout << "CLEAR!!!\n";
            break;
        }

        cout << "\n����Ű : �̵� / 1~9 : ���� �Է� / 0 : ���� ����� / ! : ��� ����\n";
        sudoku.ControlInput(); // ����� �Է� ó��
        
    }

    cout << "\n���α׷��� �����մϴ�.";
    return 0;
}
