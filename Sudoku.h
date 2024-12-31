#pragma once
// Sudoku ��� ����
// Ŭ���� ���� �� �Լ�, ���� ���� 
class Sudoku {
private:
    int s_board[9][9] = { 0 }; // �����ǿ� ���� ���ڸ� ������ ������
    int s_selX = 0; // Ŀ���� ���� x ��ġ
    int s_selY = 0; // Ŀ���� ���� y ��ġ
    bool open_answer = false; // ��� ���� ����

public:
    void init(int level); // ������ �� ����
    void Draw(); // ������ �� ���
    int CheckBoard(); // ������ ������ ���� �ߺ� ���θ� �Ǵ�
    void ControlInput(); // ������� �Է� ó�� 
};


