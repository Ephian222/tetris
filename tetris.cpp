#include "canvas.h"
#include "block.h"
#include <conio.h>	// 키보드 입력을 위한 헤더파일
#include <cstdlib>	// 블럭 랜덤 생성을 위한 랜덤함수 헤더파일
#include <ctime>	// 난수 초기화를 위한 srand 헤더파일
#include <windows.h>	// 시스템상 딜레이를 주기 위해 추가

void PlayGame(Canvas& can);	// 게임 진행을 위한 반복 함수
Block* MakeBlock();		// 블럭 랜덤 생성 함수

int main() {
    srand(time(NULL));
    Canvas can;
    PlayGame(can);
    cout << "Game is Over!" << endl;
    cout << "Your Score is : " << can.getscore() << endl;
}

void PlayGame(Canvas& can) {
    Block* b = MakeBlock();
    int time = 1;
    can.initBlock(b);
    can.show();
    while(true) {
        int c = 0;
        if(can.isBlockEmpty()) {		// 블럭이 맨 밑으로 내려가 Canvas::B가 할당이 해제되었을 때, 새로 할당해주기 위한 if문
            b = MakeBlock();
            can.initBlock(b);
            if(can.isTopfull()) break;		// 새로 할당될 블럭의 위치가 이미 차있다면 GameOver를 위해 반복문을 부순다.
            system("cls");
            can.show();
        }
        if(time % 50 == 0) {			// 일정 시간마다 블럭이 아래로 내려가는 것을 위한 if문
            can.move(3);
            if(!can.isBlockEmpty()) {
               system("cls");
               can.show(); 
            }
        } 
        Sleep(10);
        if(kbhit()) {
            c = getch();
            switch(c) {
            case 72: // up
                can.rotate();
                break;
		    case 80: // down
                can.move(3);
                break;
		    case 75: // left
                can.move(1);
                break;
		    case 77: // right
                can.move(2);
                break;
            case 100: // fall
                can.move(4);
                break;
            }
            if(!can.isBlockEmpty()) {
                system("cls");
                can.show();
            }
        }
        can.clear();
        time++;
    }
}

Block* MakeBlock() {		// 블럭을 랜덤으로 하나 할당한 뒤 그 블럭의 주소값을 반환
    int ran = rand() % 7;
    Block* b;
    switch(ran) {
    case 0: // I 
        b = new IMino();
        return b;
    case 1: // S
        b = new SMino();
        return b;
    case 2: // Z
        b = new ZMino();
        return b;
    case 3: // L
        b = new LMino();
        return b;
    case 4: // J   
        b = new JMino();
        return b;
    case 5: // O
        b = new OMino();
        return b;
    case 6: // T
        b = new TMino();
        return b;
    }
}
