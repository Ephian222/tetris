#ifndef __CANVAS_H__
#define __CANVAS_H__
#include "block.h"
#include <iostream>
#include <string>

class Canvas {
private:
    vector<vector<string>> y;
    Block* B;
    Block* shadow;
    int score;
public:
    Canvas() : y(20, vector<string>(22, " ")), B(NULL), shadow(NULL), score(0) { //세로 20, 가로 22
        for(int i = 0; i < y.size(); i++) {
            y.at(i).at(0) = "||";
            y.at(i).at(21) = "||";
        }
    }

    string gets(int x1, int y1) {
        string s = y.at(y1).at(x1);
        return s;
    }

    string gets(vector<int> v) {
        string s = y.at(v.at(1)).at(v.at(0));
        return s;
    }

    int getscore() {
        return score;
    }

    void show() {
        for(int i = 0; i < y.size(); i++) {
            for(int j = 0; j < y.at(i).size(); j++) {
                vector<int> v = {j, i};
                if(v == B->getpos(1) || v == B->getpos(2) || v == B->getpos(3) || v == B->getpos(4)) {
                    cout << "O";
                }
                else if(v == shadow->getpos(1) || v == shadow->getpos(2) || v == shadow->getpos(3) || v == shadow->getpos(4)) cout << "*";
                else cout << y.at(i).at(j);
            }
            cout << endl;
        }
        cout << "========================" << endl;
        cout << "Now Score : " << score << endl;
    }

    void move(int w) {
        if(w == 1) {
            if(gets(B->getpos(1).at(0)-1, B->getpos(1).at(1)) != " " || gets(B->getpos(2).at(0)-1, B->getpos(2).at(1)) != " " 
            || gets(B->getpos(3).at(0)-1, B->getpos(3).at(1)) != " " || gets(B->getpos(4).at(0)-1, B->getpos(4).at(1)) != " ") return;
            B->move(1);
            checkarea();
        }
        else if(w == 2) {
            if(gets(B->getpos(1).at(0)+1, B->getpos(1).at(1)) != " " || gets(B->getpos(2).at(0)+1, B->getpos(2).at(1)) != " " 
            || gets(B->getpos(3).at(0)+1, B->getpos(3).at(1)) != " " || gets(B->getpos(4).at(0)+1, B->getpos(4).at(1)) != " ") return;
            B->move(2);
            checkarea();
        }
        else if(w == 3) {
            if(B->getpos(1).at(1)+1 == 20 || B->getpos(2).at(1)+1 == 20 || B->getpos(3).at(1)+1 == 20 || B->getpos(4).at(1)+1 == 20) {
                assign(*B);
                B = NULL;
                return;
            }
            else if(gets(B->getpos(1).at(0), B->getpos(1).at(1)+1) != " " || gets(B->getpos(2).at(0), B->getpos(2).at(1)+1) != " " 
            || gets(B->getpos(3).at(0), B->getpos(3).at(1)+1) != " " || gets(B->getpos(4).at(0), B->getpos(4).at(1)+1) != " ") {
                assign(*B);
                B = NULL;    
                return;
            }
            B->move(3);
            checkarea();
        }
        else if(w == 4) {
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
            B->fall(sub);
            assign(*B);
            B = NULL;
        }
        if(!isBlockEmpty()) {
            re_shadow();
        }
    }

    void rotate() {
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

    void initBlock(Block* b) {
        this->B = NULL;
        this->B = b;
        re_shadow();
    }

    bool isBlockEmpty() {
        if(B == NULL) return true;
        else return false;
    }

    void assign(int x1, int y1, string s) {
        y.at(y1).at(x1) = s;
    }

    void assign(Block& b) {
        for(int i = 1; i < 5; i++) {
            vector<int> v = b.getpos(i);
            y.at(v[1]).at(v[0]) = "O";
        }
    }

    void checkarea() {
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

    void re_shadow() {
        delete this->shadow;
        this->shadow = new Block(B->getpos(1), B->getpos(2), B->getpos(3), B->getpos(4));
        fall_shadow();
    }

    void fall_shadow() {
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

    bool isTopfull() {
        if(gets(B->getpos(1)) != " " || gets(B->getpos(2)) != " " || gets(B->getpos(3)) != " " || gets(B->getpos(4)) != " ") return true;
        else return false;
    }

    bool isVectorfull(vector<string> v) {
        for(int i = 1; i < 21; i++) {
            if(v.at(i) != "O") return false;
        }
        return true;
    }

    void clear() {
        int cnt = 0;
        for(int i = 0; i < 20; i++) {
            if(isVectorfull(y.at(i))) {
                for(int j = 1; j < 21; j++) {
                    y.at(i).at(j) = " ";
                }
                for(int j = i; j > 0; j--) {
                    y.at(j) = y.at(j-1);
                }
                cnt++;
                score += 1000;
            }
        }
        if(cnt > 1) score += cnt*100;

    }

    void clearCanvas() {
        for(int i = 0; i < y.size(); i++) {
            for(int j = 0; j < y.at(i).size(); j++) {
                if(j==0 || j == 21) continue;
                y.at(i).at(j) = " ";
            }
        }
    }
};

#endif