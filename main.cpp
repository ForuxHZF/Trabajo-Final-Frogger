#include<iostream>
#include<windows.h>
#include<time.h>
#include<stdlib.h>
#include<cstdlib>
#include<conio.h>
#include<time.h>

using namespace std;

const int WIDTH = 60, HEIGHT = 40;
const int dW = 1, dH = 1;

void gotoxy(int x, int y) {
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

void dibujar(char plano[HEIGHT/dH][WIDTH/dW+1], int A, int B, char c) {
    B = HEIGHT/dH - 1 - B;
    if (A < 0 || B < 0 || A >= WIDTH/dW || B >= HEIGHT/dH) return;
    plano[B][A] = c;
}

class mapa {
public:
    void Pmapa(char plano[HEIGHT/dH][WIDTH/dW+1]) {
        for (int i = 0; i < WIDTH/dW; i++) {
            for (int j = 0; j < HEIGHT/dH; j++) {
                if (i == 0 || i == WIDTH/dW - 1 || j == 0 || j == HEIGHT/dH - 1) {
                    dibujar(plano, i, j, '*');
                }
                if (j % 3 == 0) {
                    dibujar(plano, i, j, '_');
                }
            }
        }
    }
};

int main() {
    char plano[HEIGHT/dH][WIDTH/dW + 1];
    for (int i = 0; i < HEIGHT/dH; i++) {
        for (int j = 0; j < WIDTH/dW; j++) {
            plano[i][j] = ' ';
        }
        plano[i][WIDTH/dW] = '\n';
    }
    plano[HEIGHT/dH][WIDTH/dW] = '\0';

    mapa j1;
    j1.Pmapa(plano);

    bool game = true;

    while (game) {
        gotoxy(0, 0);
        for (int i = 0; i < HEIGHT/dH; i++) {
            cout << plano[i];
        }
    }

    return 0;
}
