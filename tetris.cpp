#include "canvas.h"
#include "block.h"
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>

void PlayGame(Canvas& can);
Block* MakeBlock();

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
        if(can.isBlockEmpty()) {
            b = MakeBlock();
            can.initBlock(b);
            if(can.isTopfull()) break;
            system("cls");
            can.show();
        }
        if(time % 50 == 0) {
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

Block* MakeBlock() {
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