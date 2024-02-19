#include<iostream>
#include<windows.h>
#include<time.h>
#include<stdlib.h>
#include<cstdlib>
#include<conio.h>
#include<time.h>

using namespace std;

const int WIDTH = 60, HEIGHT = 111;
const int dW = 1, dH =1 ;

char Obstaculo[12][2][8] = {
    {
        "+U+    ",
        "+U+    "
    }
};

struct coord {
    int x;
    int y;
};

struct dato {
    coord pos[10];
    char car[10];
};

dato pass [12];

void gotoxy(int x, int y) {
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

void dibujar(char plano[HEIGHT / dH][WIDTH / dW + 1], int A, int B, char c) {
    B = HEIGHT / dH - 1 - B;
    if (A < 0 || B < 0 || A >= WIDTH / dW || B >= HEIGHT / dH) return;
    plano[B][A] = c;
}

void borrar(char plano[HEIGHT / dH][WIDTH / dW + 1], int A, int B) {
    B = HEIGHT / dH - 1 - B;
    if (A < 0 || B < 0 || A >= WIDTH / dW || B >= HEIGHT / dH) return;
    plano[B][A] = ' ';
}

class mapa {
private:
    int x, y, c, m;
    float vy=0.0f;
    int Poss[13] = {0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36};
    int prevX, prevY; 

public:
    mapa(int x1, int y1, int c1, int m1) {
        x = x1;
        y = y1;
        c = c1;
        m = m1;
        prevX = x;
        prevY = Poss[y];
    }

    void Pmapa(char plano[HEIGHT / dH][WIDTH / dW + 1]) {
        for (int i = 0; i < WIDTH / dW; i++) {
            for (int j = 0; j < HEIGHT / dH; j++) {
                if (i == 0 || i == WIDTH / dW - 1 || j == 0 || j == HEIGHT / dH - 1) {
                    dibujar(plano, i, j, '*');
                }
                if (j % 3 == 0) {
                    dibujar(plano, i, j, '_');
                }
				
            }
        }
    }

    void pasar() {
        for (int t = 0; t < 1; t++) {
            int q = 0;
            int y;
            for (int i = 0; i < 2; i++) {
                y = 2 - i;
                for (int j = 0; j < 7; j++) {
                    if (Obstaculo[t][i][j] != ' ') {
                        pass[t].pos[q] = {j, y};
                        pass[t].car[q] = Obstaculo[t][i][j];
                        q++;
                    }
                }
            }
        }
    }

    void draw(char plano[HEIGHT / dH][WIDTH / dW + 1]) {
        for (int i = 0; i < 6; i++) {
            borrar(plano, prevX + pass[c].pos[i].x, prevY + pass[c].pos[i].y);
        }
        for (int i = 0; i < 6; i++) {
            dibujar(plano, x + pass[c].pos[i].x, Poss[y] + pass[c].pos[i].y, pass[c].car[i]);
        }

        prevX = x;
        prevY = Poss[y];
    }
    void ejecucion(int &dir){
    	vy-=1150.0f*0.0416;
    	if(vy>=752.0f)
    	  direccion(dir);
	}
	void direccion(int &dir)
	{
		switch(dir)
		{
			case 1:
				y++;
				dir=0;
				break;
			case 2:
				x+=2;
				dir=0;
				break;
			case 3:
				y--;
				dir=0;
				break;
			case 4:
				x-=2;
				dir=0;
				break;
		}
	}
	void dir2()
	{
		if(vy<=600.0f)
		vy=800.0f;
	}
};

int main() {

    char plano[HEIGHT / dH][WIDTH / dW + 1];
    
    for (int i = 0; i < HEIGHT / dH; i++) {
        for (int j = 0; j < WIDTH / dW; j++) {
            plano[i][j] = ' ';
        }
        plano[i][WIDTH / dW] = '\n';
    }
    plano[HEIGHT / dH][WIDTH / dW] = '\0';

    mapa j1(28, 0, 0, 0);
    
    float fps=24.0f;
    float dt=1.0f/fps;
    float acumulador=0.0f;
    
  
    clock_t inicio = clock();
    
    j1.pasar();

    bool game = true;
    
    int dir=0;
    
    
    while (game) {
    	
        
    	clock_t final=clock();
    	acumulador+= float (final-inicio)/CLOCKS_PER_SEC;
    	inicio=final;
    	
    	if(acumulador >=0.2f) acumulador = 2.0f;
    	system("cls");
    	
     while (acumulador >= dt) {
            if (_kbhit()) {
                char key = _getch();
                switch (key) {
                case 'W':
                case 'w':
                    j1.dir2();
                    dir = 1;
                    break;
                case 'S':
                case 's':
                    j1.dir2();
                    dir = 3;
                    break;
                case 'D':
                case 'd':
                    j1.dir2();
                    dir = 2;
                    break;
                case 'A':
                case 'a':
                    j1.dir2();
                    dir = 4;
                    break;
                case 27:  
                    game = false;
                    break;
                }
            }
    		
		j1.ejecucion(dir);
		acumulador -=dt;
		
		}
        gotoxy(0, 0);
       j1.Pmapa(plano);
       j1.draw(plano);
       
    for (int i = 0; i < HEIGHT / dH; i++) {
                cout << plano[i];
        }
	 }


    return 0;
}
