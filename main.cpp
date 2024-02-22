#include<iostream>
#include<windows.h>
#include<time.h>
#include<stdlib.h>
#include<cstdlib>
#include<conio.h>
#include<time.h>

using namespace std;

const int WIDTH = 60, HEIGHT =111;
const int dW = 1, dH =1 ;

char Obstaculo[12][2][8] = {
    {
        "+€+    ",
        "+ﬂ+    "
    },
    {
    	"‹€€‹   ",
    	"©  ©   "
	},
	{
		"‹€€€   ",
		"©  ©   "
	},
	{
    	"‹€‹‹   ",
    	"©  ©   "
	},
	{
		"‹€‹€€€ ",
		"©  © © "
	},
	{
		"<‹     ",
		"  ﬂ‹ﬂ  "
	},
	{
		">‹‹‹_  ",
		" + +   "
	}
};

struct coord {
    int x;
    int y;
};

struct dato {
    coord pos[12];
    char car[12];
};

dato pass [12];

void gotoxy(int x, int y) {
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

void dibujar(char plano[HEIGHT / dH][WIDTH / dW + 1 ], int A, int B, char c) {
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
    
    int PY[10] = {1,2,3,4,5,7,8,9,10,11};
    int NC[12] = {6,6,6,6,9,5,7,14,10,6,6,6};
    int PO[10] = {1,2,3,4,5,6,5,4,3,2};
    
    int niveles[12][10]={{2,3,2,1,2,3,4,3,2,2},
	                     {4,3,3,1,3,3,1,3,2,2},
	                     {4,4,2,2,1,3,3,1,2,1},
                         {4,4,4,3,3,2,2,1,3,1},
						 {4,4,4,3,3,2,2,1,3,1},
						 {4,4,4,2,2,3,3,2,1,1},
						 {4,4,4,3,3,2,2,1,3,1},
						 {4,4,4,1,2,3,3,2,1,1},
						 {4,4,4,2,2,3,3,2,1,1},
						 {4,4,4,1,2,3,3,2,1,1},
						 {4,4,2,2,1,3,3,2,2,2},
						 {4,4,4,3,3,3,2,2,3,1},
	                     };
	                     
    int lim [4][4]={{23, 1, 1, 1},
                    {17,46, 1, 1},
                    { 6,26,45, 1},
                    { 2,16,30,44},
                    };
						                     
coord car[12][5];

public:
	int retx()
	{
		return x;
	}
	
	int rety()
	{
		return y;
	}
	
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
            	if (i * dW >= 0 && i * dW < WIDTH && j * dH >= 0 && j * dH < HEIGHT) {
                if (i == 0 || i == WIDTH / dW - 1 || j == 0 || j == HEIGHT / dH - 1) {
                    dibujar(plano, i*dW, j*dH, '*');
                }
                if (j % 3 == 0) {
                    dibujar(plano, i*dW, j*dH, '_');
                }
				
            }
        }
    }
}
    void pasar() {
        for (int t = 0; t < 8; t++) {
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
    	prevX = x;
        prevY = Poss[y];
    	
        for (int i = 0; i < 6; i++) {
             borrar(plano, prevX * dW + pass[c].pos[i].x, prevY * dH + pass[c].pos[i].y);
        }
        
        
        for (int i = 0; i < 6; i++) {
            dibujar(plano, (x + pass[c].pos[i].x * dW), (Poss[y] + pass[c].pos[i].y * dH), pass[c].car[i]);
        }

    }
    
    void draw(char plano[HEIGHT / dH][WIDTH / dW + 1],int t, int u, int c)
    {
    	for(int j = 0; j < t; j++)
    {
    for(int i = 0; i < NC[c]; i++)
    {
        dibujar(plano, (car[u][j].x) + pass[c].pos[i].x, (Poss[car[u][j].y]) + pass[c].pos[i].y, pass[c].car[i]);
    }
}
	}
	
	void generacion(char plano[HEIGHT / dH][WIDTH / dW + 1],int nivel )
	{
		for(int i=0 ; i<10;i++)
		{
			draw(plano,niveles[nivel][i],i,PO[i]);
		}
	}
	
	void retxy(int nivel)
	{
		for(int j=0;j<10;j++)
		{
			for(int i=0;i<niveles[nivel][j];i++)
			{
				car[j][i].x=rand()%6+lim[(niveles[nivel][j]-1)][i];
				car[j][i].y=PY[j];
			}
		}
		
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
				if(y<12)
				y++;
				dir=0;
				break;
			case 2:
				if(x<55)
				x+=2;
				dir=0;
				break;
			case 3:
				if(y>0)
				y--;
				dir=0;
				break;
			case 4:
				if(x>1)
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
	
	
	srand(static_cast <unsigned>(time(0)));

    char plano[HEIGHT / dH][WIDTH / dW + 1];
    
    for (int i = 0; i < HEIGHT / dH; i++) {
        for (int j = 0; j < WIDTH / dW; j++) {
            plano[i][j] = ' ';
        }
        plano[i][WIDTH / dW] = '\n';
    }
    plano[HEIGHT / dH][WIDTH / dW] = '\0';

    mapa j1(28, 0, 0, 0);
    
	int nivel= 0;
    
    float fps=24.0f;
    float dt=1.0f/fps;
    float acumulador=0.0f;
    
  
    clock_t inicio = clock();
    
    j1.pasar();
    j1.retxy(nivel);

    bool game = true;
    
    int dir=0;
    
    
    while (game) {
    	system ("cls");
        
        
        for (int i = 0; i < HEIGHT / dH; i++) {
                cout << plano[i];
        }
        
    	clock_t final=clock();
    	acumulador+= float (final-inicio)/CLOCKS_PER_SEC;
    	inicio=final;
    	
    	if(acumulador >=0.2f) acumulador = 2.0f;
    	
    	for (int i = 0; i < HEIGHT / dH; i++) {
            for (int j = 0; j < WIDTH / dW; j++) {
                plano[i][j] = ' ';
            }
        }
     while (acumulador >= dt) {
            if (_kbhit()) {
                char key = _getch();
                switch (key) {
                case 'W':
                case 'w':
                if	(j1.rety() < 12)
                    j1.dir2();
                    dir = 1;
                    break;
                case 'S':
                case 's':
                if	(j1.rety() < 0)
                    j1.dir2();
                    dir = 3;
                    break;
                case 'D':
                case 'd':
                if	(j1.retx() < 55)	
                    j1.dir2();
                    dir = 2;
                    break;
                case 'A':
                case 'a':
                if	(j1.retx() < 1)
                    j1.dir2();
                    dir = 4;
                    break;
                case 27:  
                    game = false;
                    break;
                }
            }
    		
		j1.ejecucion(dir);
		j1.direccion(dir);
		acumulador -=dt;
		
		}
        gotoxy(0, 0);
       j1.Pmapa(plano);
       j1.generacion(plano,nivel);
       j1.draw(plano);
       
	 }



    return 0;
}
