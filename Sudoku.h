#pragma once
// Sudoku 헤더 파일
// 클래스 생성 및 함수, 변수 선언 
class Sudoku {
private:
    int s_board[9][9] = { 0 }; // 게임판에 적힌 숫자를 저장할 데이터
    int s_selX = 0; // 커서의 현재 x 위치
    int s_selY = 0; // 커서의 현재 y 위치
    bool open_answer = false; // 답안 보기 여부

public:
    void init(int level); // 스도쿠 판 생성
    void Draw(); // 스도쿠 판 출력
    int CheckBoard(); // 스도쿠 보드의 숫자 중복 여부를 판단
    void ControlInput(); // 사용자의 입력 처리 
};


