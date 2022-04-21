#ifndef __BLOCK_H__
#define __BLOCK_H__
#include <vector>
#include "canvas.h"
#include <iostream>

using namespace std;

class Block {
protected:
    vector<int> b1, b2, b3, b4;         // 블럭이 갖고 있는 4칸 모두 각자 좌표를 가지고 있다
public:
    Block(vector<int> a, vector<int> b, vector<int> c, vector<int> d) {
        b1 = a;
        b2 = b;
        b3 = c;
        b4 = d;
    }
    
    Block(char b) {     // 블럭 모양에 따른 좌표 할당
        switch(b) {
        case 'I' :
            b1 = {11, 0};
            b2 = {11, 1};
            b3 = {11, 2};
            b4 = {11, 3};
            break;
        case 'S' :
            b1 = {11, 0};
            b2 = {10, 0};
            b3 = {10, 1};
            b4 = {9, 1};
            break;
        case 'Z' :
            b1 = {10, 0};
            b2 = {11, 0};
            b3 = {11, 1};
            b4 = {12, 1};
            break;
        case 'O' :
            b1 = {10, 0};
            b2 = {11, 0};
            b3 = {10, 1};
            b4 = {11, 1};
            break;
        case 'L' :
            b1 = {10, 0};
            b2 = {11, 0};
            b3 = {11, 1};
            b4 = {11, 2};
            break;
        case 'J' :
            b1 = {11, 0};
            b2 = {10, 0};
            b3 = {10, 1};
            b4 = {10, 2};
            break;
        case 'T' :
            b1 = {11, 0};
            b2 = {10, 1};
            b3 = {11, 1};
            b4 = {11, 2};
            break;
        }
    }

    vector<int> getpos(int n) {     // 매개변수에 맞는 칸의 좌표를 반환한다.
        if(n == 1) return b1;
        else if(n == 2) return b2;
        else if(n == 3) return b3;
        else if(n == 4) return b4;
    }

    void move(int w) {
        // 1이면 좌, 2이면 우, 3이면 아래, 4이면 위
        if(w == 1) {
            b1 = {b1.at(0) - 1, b1.at(1)};
            b2 = {b2.at(0) - 1, b2.at(1)};
            b3 = {b3.at(0) - 1, b3.at(1)};
            b4 = {b4.at(0) - 1, b4.at(1)};
        }
        else if(w == 2) {
            b1 = {b1.at(0) + 1, b1.at(1)};
            b2 = {b2.at(0) + 1, b2.at(1)};
            b3 = {b3.at(0) + 1, b3.at(1)};
            b4 = {b4.at(0) + 1, b4.at(1)};
        }
        else if(w == 3) {
            b1 = {b1.at(0), b1.at(1) + 1};
            b2 = {b2.at(0), b2.at(1) + 1};
            b3 = {b3.at(0), b3.at(1) + 1};
            b4 = {b4.at(0), b4.at(1) + 1};            
        }
        else if(w == 4) {
            b1 = {b1.at(0), b1.at(1) - 1};
            b2 = {b2.at(0), b2.at(1) - 1};
            b3 = {b3.at(0), b3.at(1) - 1};
            b4 = {b4.at(0), b4.at(1) - 1};
        }
    }

    void fall(int m) {
        b1.at(1) = b1.at(1) + m;
        b2.at(1) = b2.at(1) + m;
        b3.at(1) = b3.at(1) + m;
        b4.at(1) = b4.at(1) + m;
    }

    virtual void rotate() {
        
    }
};

class IMino : public Block {
private:
    int nrot;
public:
    IMino() : Block('I'){
        nrot = 0;
    }

    virtual void rotate() {
        if(nrot == 0) {
            b2 = {b2.at(0)+1, b2.at(1)-1};
            b3 = {b3.at(0)+2, b3.at(1)-2};
            b4 = {b4.at(0)+3, b4.at(1)-3};
            nrot = 1;
        }
        else if(nrot == 1) {
            b2 = {b2.at(0)-1, b2.at(1)+1};
            b3 = {b3.at(0)-2, b3.at(1)+2};
            b4 = {b4.at(0)-3, b4.at(1)+3};
            nrot = 0;
        }
    }
};

class SMino : public Block {
private:
    int nrot;
public:
    SMino() : Block('S') {
        nrot = 0;
    }

    virtual void rotate() {
        if(nrot == 0) {
            b1 = {b1.at(0)-1, b1.at(1)+1};
            b3 = {b3.at(0)-1, b3.at(1)-1};
            b4 = {b4.at(0), b4.at(1)-2};
            nrot = 1;
        }
        else if(nrot == 1) {
            b1 = {b1.at(0)+1, b1.at(1)-1};
            b3 = {b3.at(0)+1, b3.at(1)+1};
            b4 = {b4.at(0), b4.at(1)+2};
            nrot = 0;
        }
    }
};

class ZMino : public Block {
private:
    int nrot;
public:
    ZMino() : Block('Z') {
        nrot = 0;
    }

    virtual void rotate() {
        if(nrot == 0) {
            b1 = {b1.at(0)+1, b1.at(1)-1};
            b3 = {b3.at(0)-1, b3.at(1)-1};
            b4 = {b4.at(0)-2, b4.at(1)};
            nrot = 1;
        }
        else if(nrot == 1) {
            b1 = {b1.at(0)-1, b1.at(1)+1};
            b3 = {b3.at(0)+1, b3.at(1)+1};
            b4 = {b4.at(0)+2, b4.at(1)};
            nrot = 0;
        }
    }
};

class OMino : public Block {
public:
    OMino() : Block('O') {
        
    }

    virtual void rotate() {

    }
};

class JMino : public Block {
private:
    int nrot;
public:
    JMino() : Block('J') {
        nrot = 2;
    }

    virtual void rotate() {
        if(nrot == 0) {
            b1 = {b1.at(0), b1.at(1)-2};
            b2 = {b2.at(0)-1, b2.at(1)-1};
            b4 = {b4.at(0)+1, b4.at(1)+1};
            nrot = 1;
        }
        else if(nrot == 1) {
            b1 = {b1.at(0)+2, b1.at(1)};
            b2 = {b2.at(0)+1, b2.at(1)-1};
            b4 = {b4.at(0)-1, b4.at(1)+1};
            nrot = 2;
        }
        else if(nrot == 2) {
            b1 = {b1.at(0), b1.at(1)+2};
            b2 = {b2.at(0)+1, b2.at(1)+1};
            b4 = {b4.at(0)-1, b4.at(1)-1};
            nrot = 3;
        }
        else if(nrot == 3) {
            b1 = {b1.at(0)-2, b1.at(1)};
            b2 = {b2.at(0)-1, b2.at(1)+1};
            b4 = {b4.at(0)+1, b4.at(1)-1};
            nrot = 0;
        }
    }
};

class LMino : public Block {
private:
    int nrot;
public:
    LMino() : Block('L') {
        nrot = 2;
    }

    virtual void rotate() {
        if(nrot == 0) {
            b1 = {b1.at(0)-2, b1.at(1)};
            b2 = {b2.at(0)-1, b2.at(1)-1};
            b4 = {b4.at(0)+1, b4.at(1)+1};
            nrot = 1;
        }
        else if(nrot == 1) {
            b1 = {b1.at(0), b1.at(1)-2};
            b2 = {b2.at(0)+1, b2.at(1)-1};
            b4 = {b4.at(0)-1, b4.at(1)+1};
            nrot = 2;
        }
        else if(nrot == 2) {
            b1 = {b1.at(0)+2, b1.at(1)};
            b2 = {b2.at(0)+1, b2.at(1)+1};
            b4 = {b4.at(0)-1, b4.at(1)-1};
            nrot = 3;
        }
        else if(nrot == 3) {
            b1 = {b1.at(0), b1.at(1)+2};
            b2 = {b2.at(0)-1, b2.at(1)+1};
            b4 = {b4.at(0)+1, b4.at(1)-1};
            nrot = 0;
        }
    }
};

class TMino : public Block {
private:
    int nrot;
public:
    TMino() : Block('T') {
        nrot = 0;
    }

    virtual void rotate() {
        if(nrot == 0) {
            b1 = {b1.at(0)+1, b1.at(1)+1};
            b2 = {b2.at(0)+1, b2.at(1)-1};
            b4 = {b4.at(0)-1, b4.at(1)-1};
            nrot = 1;
        }
        else if(nrot == 1) {
            b1 = {b1.at(0)-1, b1.at(1)+1};
            b2 = {b2.at(0)+1, b2.at(1)+1};
            b4 = {b4.at(0)+1, b4.at(1)-1};
            nrot = 2;
        }
        else if(nrot == 2) {
            b1 = {b1.at(0)-1, b1.at(1)-1};
            b2 = {b2.at(0)-1, b2.at(1)+1};
            b4 = {b4.at(0)+1, b4.at(1)+1};
            nrot = 3;
        }
        else if(nrot == 3) {
            b1 = {b1.at(0)+1, b1.at(1)-1};
            b2 = {b2.at(0)-1, b2.at(1)-1};
            b4 = {b4.at(0)-1, b4.at(1)+1};
            nrot = 0;
        }
    }
};
#endif