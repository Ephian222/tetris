#ifndef __CANVAS_H__
#define __CANVAS_H__
#include "block.h"
#include <iostream>         
#include <string>  

class Canvas {
private:
    vector<vector<string>> y;       // 좌표를 벡터로 표현하기 위해서 이차원 벡터를 사용
    Block* B;                       // 현재 사용자가 조작하고 있는 블럭을 가르키기 위한 포인터
    Block* shadow;                  // 블럭의 하드드롭 위치를 나타내주는 블럭의 포인터
    int score;
public:
    Canvas() : y(20, vector<string>(22, " ")), B(NULL), shadow(NULL), score(0) { //세로 20, 가로 22
        for(int i = 0; i < y.size(); i++) {
            y.at(i).at(0) = "||";                   // 경계를 표현
            y.at(i).at(21) = "||";
        }
    }

    string gets(int x1, int y1) {       // 캔버스의 x1, y1의 위치에 존재하는 문자를 반환
        string s = y.at(y1).at(x1);
        return s;
    }

    string gets(vector<int> v) {        // 위 함수의 오버로딩
        string s = y.at(v.at(1)).at(v.at(0));
        return s;
    }

    int getscore() {
        return score;
    }

    void show() {                                       // 캔버스를 출력하는 함수
        for(int i = 0; i < y.size(); i++) {
            for(int j = 0; j < y.at(i).size(); j++) {
                vector<int> v = {j, i};
                if(v == B->getpos(1) || v == B->getpos(2) || v == B->getpos(3) || v == B->getpos(4)) {      // 사용자가 조작하는 블럭 표시. 캔버스에 "O"가 담겨져 있는 것이 아님
                    cout << "O";
                }
                else if(v == shadow->getpos(1) || v == shadow->getpos(2) || v == shadow->getpos(3) || v == shadow->getpos(4)) cout << "*"; // 하드드롭의 예측 위치 표시
                else cout << y.at(i).at(j);             // 그 외에는 캔버스에 담긴 것을 출력한다
            }
            cout << endl;
        }
        cout << "========================" << endl;
        cout << "Now Score : " << score << endl;
    }

    void move(int w) {      // 블럭의 이동
        if(w == 1) {
            if(gets(B->getpos(1).at(0)-1, B->getpos(1).at(1)) != " " || gets(B->getpos(2).at(0)-1, B->getpos(2).at(1)) != " " 
            || gets(B->getpos(3).at(0)-1, B->getpos(3).at(1)) != " " || gets(B->getpos(4).at(0)-1, B->getpos(4).at(1)) != " ") return;
            B->move(1);
            //checkarea();
        }
        else if(w == 2) {
            if(gets(B->getpos(1).at(0)+1, B->getpos(1).at(1)) != " " || gets(B->getpos(2).at(0)+1, B->getpos(2).at(1)) != " " 
            || gets(B->getpos(3).at(0)+1, B->getpos(3).at(1)) != " " || gets(B->getpos(4).at(0)+1, B->getpos(4).at(1)) != " ") return;
            B->move(2);
            //checkarea();
        }
        else if(w == 3) {
            if(B->getpos(1).at(1)+1 == 20 || B->getpos(2).at(1)+1 == 20 || B->getpos(3).at(1)+1 == 20 || B->getpos(4).at(1)+1 == 20) {      // 바닥까지 내려온 경우
                assign(*B);
                B = NULL;
                return;
            }
            else if(gets(B->getpos(1).at(0), B->getpos(1).at(1)+1) != " " || gets(B->getpos(2).at(0), B->getpos(2).at(1)+1) != " " 
            || gets(B->getpos(3).at(0), B->getpos(3).at(1)+1) != " " || gets(B->getpos(4).at(0), B->getpos(4).at(1)+1) != " ") {        // 밑이 비어있지 않은 경우 (블럭이 쌓여 있는 경우)
                assign(*B);
                B = NULL;    
                return;
            }
            B->move(3);
            //checkarea();
        }
        else if(w == 4) {       // 하드드롭. 맨 밑 혹은 블럭이 있는 곳 까지의 거리를 계산한 다음 그 수치만큼 블럭의 좌표를 바꿔준다
            int sub = 0;
            for(int i = 0; i < 20; i++) {
                if(B->getpos(1).at(1)+1+i == 20 || B->getpos(2).at(1)+1+i == 20 || B->getpos(3).at(1)+1+i == 20 || B->getpos(4).at(1)+1+i == 20) {
                    sub += i;
                    break;
                }
                else if(gets(B->getpos(1).at(0), B->getpos(1).at(1)+1+i) != " " || gets(B->getpos(2).at(0), B->getpos(2).at(1)+1+i) != " " 
                || gets(B->getpos(3).at(0), B->getpos(3).at(1)+1+i) != " " || gets(B->getpos(4).at(0), B->getpos(4).at(1)+1+i) != " ") {
                    sub += i;
                    break;
                }
            }
            B->fall(sub);   // 블럭의 좌표를 위 계산한 sub만큼 바꾸어 주는 함수
            assign(*B);
            B = NULL;
        }
        if(!isBlockEmpty()) {
            re_shadow();
        }
    }

    void rotate() {     // 회전. 회전하려는 위치에 다른 블럭이 있는 경우 회전을 하지 않아야 하므로, 좌표를 한번 바꿔준 뒤 만약 그 위치에 블럭이 존재한다면 다시 회전을 반복하여 처음 상태로 돌아간다
        B->rotate();
        checkarea();
        if(gets(B->getpos(1)) == "O" || gets(B->getpos(2)) == "O" || gets(B->getpos(3)) == "O" || gets(B->getpos(4)) == "O") {
            B->rotate();
            B->rotate();
            B->rotate();
            checkarea();
        }
        re_shadow();
    }

    void initBlock(Block* b) {      // 블럭의 재할당
        this->B = NULL;
        this->B = b;
        re_shadow();
    }

    bool isBlockEmpty() {       // 블럭 포인터가 비었는지 확인하는 함수
        if(B == NULL) return true;
        else return false;
    }

    void assign(int x1, int y1, string s) {     // 캔버스 상 x1, y1 위치에 s를 집어넣는다
        y.at(y1).at(x1) = s;
    }

    void assign(Block& b) {         // 위 함수의 오버로딩. 블럭의 좌표에 해당하는 캔버스 위치에 "O"를 넣어준다 
        for(int i = 1; i < 5; i++) {
            vector<int> v = b.getpos(i);
            y.at(v[1]).at(v[0]) = "O";
        }
    }

    void checkarea() {      // 블럭이 경계(양옆, 아래, 위)를 넘어가지 않게 조정해주는 함수. 만약 넘어간다면 넘어간 만큼 반대로 이동하는 함수를 호출한다
        if(B->getpos(1).at(1) > 19 || B->getpos(2).at(1) > 19 || B->getpos(3).at(1) > 19 || B->getpos(4).at(1) > 19) {
            while(B->getpos(1).at(1) > 19 || B->getpos(2).at(1) > 19 || B->getpos(3).at(1) > 19 || B->getpos(4).at(1) > 19)
                B->move(4);
        }
        else if(B->getpos(1).at(1) < 0 || B->getpos(2).at(1) < 0 || B->getpos(3).at(1) < 0 || B->getpos(4).at(1) < 0) {
            while(B->getpos(1).at(1) < 0 || B->getpos(2).at(1) < 0 || B->getpos(3).at(1) < 0 || B->getpos(4).at(1) < 0)
                B->move(3);
        }
        else if(B->getpos(1).at(0) < 1 || B->getpos(2).at(0) < 1 || B->getpos(3).at(0) < 1 || B->getpos(4).at(0) < 1) {
            while(B->getpos(1).at(0) < 1 || B->getpos(2).at(0) < 1 || B->getpos(3).at(0) < 1 || B->getpos(4).at(0) < 1)
                B->move(2);
        }
        else if(B->getpos(1).at(0) > 20 || B->getpos(2).at(0) > 20 || B->getpos(3).at(0) > 20 || B->getpos(4).at(0) > 20){
            while(B->getpos(1).at(0) > 20 || B->getpos(2).at(0) > 20 || B->getpos(3).at(0) > 20 || B->getpos(4).at(0) > 20)
                B->move(1);
        }
    }

    void re_shadow() {      // 하드드롭의 위치를 표시해주는 블럭 재할당
        delete this->shadow;
        this->shadow = new Block(B->getpos(1), B->getpos(2), B->getpos(3), B->getpos(4));
        fall_shadow();
    }

    void fall_shadow() {    // 하드드롭의 위치를 알기 위해선 하드드롭을 해야한다. 이를 위한 함수
        int sub = 0;
            for(int i = 0; i < 20; i++) {
                if(shadow->getpos(1).at(1)+1+i == 20 || shadow->getpos(2).at(1)+1+i == 20 || shadow->getpos(3).at(1)+1+i == 20 || shadow->getpos(4).at(1)+1+i == 20) {
                    sub += i;
                    break;
                }
                else if(gets(shadow->getpos(1).at(0), shadow->getpos(1).at(1)+1+i) != " " || gets(shadow->getpos(2).at(0), shadow->getpos(2).at(1)+1+i) != " " 
                || gets(shadow->getpos(3).at(0), shadow->getpos(3).at(1)+1+i) != " " || gets(shadow->getpos(4).at(0), shadow->getpos(4).at(1)+1+i) != " ") {
                    sub += i;
                    break;
                }
            }
            shadow->fall(sub);
    }

    bool isTopfull() {      // 블럭의 좌표에 해당하는 캔버스 위치에 빈 공간이 있으면 false, 없으면 true
        if(gets(B->getpos(1)) != " " || gets(B->getpos(2)) != " " || gets(B->getpos(3)) != " " || gets(B->getpos(4)) != " ") return true;
        else return false;
    }

    bool isVectorfull(vector<string> v) {       // 한 줄이 가득 찼는지를 확인하는 함수. 한 줄 완성시 이를 없애기 위해 만들었다
        for(int i = 1; i < 21; i++) {
            if(v.at(i) != "O") return false;
        }
        return true;
    }

    void clear() {      // 한 줄이 완성된 줄을 지우기 위한 함수. 점수도 이곳에서 올려준다.
        int cnt = 0;
        for(int i = 0; i < 20; i++) {
            if(isVectorfull(y.at(i))) {
                for(int j = 1; j < 21; j++) {   // 가득찬 줄을 공백으로 바꿔주고,
                    y.at(i).at(j) = " ";
                }
                for(int j = i; j > 0; j--) {    // 위에서 한줄씩 땡겨온다.
                    y.at(j) = y.at(j-1);
                }
                cnt++;
                score += 1000;
            }
        }
        if(cnt > 1) score += cnt*100;

    }

    void clearCanvas() {        // 캔버스 전체를 지워버리는 함수
        for(int i = 0; i < y.size(); i++) {
            for(int j = 0; j < y.at(i).size(); j++) {
                if(j==0 || j == 21) continue;
                y.at(i).at(j) = " ";
            }
        }
    }
};

#endif