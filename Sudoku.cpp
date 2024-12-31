#include <iostream>
#include "StageMaker.h"
#include "Sudoku.h"

// Sudoku ���� ���� 

using namespace std;

// ������ �� ����
void Sudoku::init(int level) {
    MakeStage(s_board, level); // level ������ ���� ���� �־����� ���� ������ ������
}

// ������ �� ���
void Sudoku::Draw()
{
    for (int y = 0; y < 9; ++y) // �� �ݺ�
    {
        for (int x = 0; x < 9; ++x) // �� �ݺ�
        {
            if (s_board[x][y] > 10) // ����ڿ��� ���� ������ ������ ���
            {
                cout << " _ "; // ���� �� �����(_)�� �߰� 
            }
            else
            {
                cout << "   ";
            }

            if (x % 3 == 2) // 3x3 ����� �����ϱ� ���� ��ĭ �߰� 
                cout << "  ";
        }
        cout << "\n";

        // ������ �ǿ� ���� ��� 
        for (int x = 0; x < 9; ++x) // �� �ݺ�
        {
            if (s_selX == x && s_selY == y) // ���� Ŀ���� ��ġ�� ��ǥ�� ��� 
            {
                if (s_board[s_selX][s_selY] > 0) // ���ڰ� ä���� �ִٸ�
                {
                    cout << '(' << s_board[s_selX][s_selY] % 10 << ')'; // ( ) �� ���������� ǥ�� 
                }
                else // ���ڰ� ���� �� ä���� ���
                {
                    cout << "(.)";
                }
            }
            else 
            {
                if (s_board[x][y] > 0) // ���ڰ� ä���� �ִ� ���
                    cout << ' ' << s_board[x][y] % 10 << ' '; // ���ڸ� ���
                else // ���ڰ� ���� �� ä���� ���
                    cout << " . "; // . ���
            }

            if (x % 3 == 2) // 3x3 ����� �����ϱ� ���ؼ� �� ĭ �߰�
                cout << "  ";
        }
        cout << "\n";

        if (y % 3 == 2) // 3x3 ����� �����ϱ� ���� �ٹٲ�
            cout << "\n";
    }

    if (open_answer) // ��� ���� = true
    {
        DrawAnswer(s_board, open_answer); // ������ ���� ���� 
    }
}

// ������ ������ ���� �ߺ� ���θ� �Ǵ� 
int Sudoku::CheckBoard()
{
    // �����ٰ� ������ �˻�
    for (int i = 0; i < 9; ++i)
    {
        bool rowCheck[10] = { false }; // ������ ���� �ߺ� Ȯ�ο�
        bool colCheck[10] = { false }; // ������ ���� �ߺ� Ȯ�ο�

        for (int j = 0; j < 9; ++j)
        {
            // ������ �˻�
            if (s_board[j][i] > 0) // �����ٿ� ���ڰ� ������(�־��� ������ ���)
            {
                int num = s_board[j][i] % 10; // ���� �ڸ� �� ����(������ ���Ƿ� 10�� ����)
                if (rowCheck[num]) // �̹� ���� ������ ��� 
                    return 0; 
                rowCheck[num] = true; // ���� ����� ǥ�� 
            }

            // ������ �˻�
            if (s_board[i][j] > 0) // �����ٿ� ���ڰ� ������(�־��� ������ ���)
            {
                int num = s_board[i][j] % 10; // ���� �ڸ� �� ����(������ ���Ƿ� 10�� ����)
                if (colCheck[num]) // �̹� ���� ������ ��� 
                    return 0; 
                colCheck[num] = true; // ���� ����� ǥ�� 
            }
        }
    }

    // 3x3 ���� �˻�
    for (int startY = 0; startY < 9; startY += 3)
    {
        for (int startX = 0; startX < 9; startX += 3)
        {
            bool blockCheck[10] = { false }; // 3x3 ��� ���� �ߺ� Ȯ�ο�

            for (int y = 0; y < 3; ++y) // ����� ��
            {
                for (int x = 0; x < 3; ++x) // ����� ��
                {
                    int currentX = startX + x;
                    int currentY = startY + y;

                    if (s_board[currentX][currentY] > 0) // �־��� ���ڰ� ������
                    {
                        int num = s_board[currentX][currentY] % 10; // ���� �ڸ� �� ����(������ ���Ƿ� 10�� ����)
                        if (blockCheck[num]) // �̹� ���� ������ ��� 
                            return 0;
                        blockCheck[num] = true; // ���� ����� ǥ��
                    }
                }
            }

            for (int num = 1; num <= 9; ++num)
            {
                if (!blockCheck[num]) // 3x3 ��� ������ �ߺ��� �߰ߵ� ��� 
                    return 0; 
            }
        }
    }

    // ������, ������, 3x3 ��� �� 1~9 ������ �ߺ��� ���� ��� 
    return 1;
}

// ������� �Է� ó�� 
void Sudoku::ControlInput() {
    char inputChar;
    cin >> inputChar; // Ű���� �Է� (����ڿ��� �Է¹��� ������ �ﰢ �ƽ�Ű�ڵ�� ��ȯ)

    switch (inputChar) {
    case 'w': // ���� �̵�
        s_selY = max(0, s_selY - 1); // Ŀ�� ���� �̵�
        break;
    case 'a': // ���� �̵�
        s_selX = max(0, s_selX - 1); // Ŀ�� ���� �̵�
        break;
    case 's': // �Ʒ��� �̵�
        s_selY = min(8, s_selY + 1); // Ŀ�� �Ʒ��� �̵�
        break;
    case 'd': // ������ �̵�
        s_selX = min(8, s_selX + 1); // Ŀ�� ������ �̵�
        break;
    case '!': // ��� ����
        open_answer = !open_answer; // ��� ���� ���� ���� 
        break;
    case '0': // ���� �����
        if (s_board[s_selX][s_selY] <= 10) // ���� ������ ��ġ���� Ȯ��
            s_board[s_selX][s_selY] = 0; // 0���� �ʱ�ȭ
        break;
    case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9': // ���� �Է�
        if (s_board[s_selX][s_selY] <= 10) // ���� ������ ��ġ���� Ȯ��
            s_board[s_selX][s_selY] = inputChar - '0'; // �Է��� ���ڸ� ���忡 ����
        break;
    }

}

