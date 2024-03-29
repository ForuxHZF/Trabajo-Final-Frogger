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
        "+�+    ",
        "+�+    "
    },
    {
    	"����   ",
    	"�  �   "
	},
	{
		"����   ",
		"�  �   "
	},
	{
    	"����   ",
    	"�  �   "
	},
	{
		"������ ",
		"�  � � "
	},
	{
		"<�     ",
		"  ���  "
	},
	{
		">���_  ",
		" + +   "
	}
};

struct coord {
    int x ;
    int y;
};

struct dato {
    coord pos[14];
    char car[14];
};

dato pass [12];

dato choqueR[1];
dato choqueC[12][5];

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
    int p1=0,p2=0,p3=0,p4=0;
    float vy=0.0f;
    int s ,con = 8;
    int min = 300;
    int Poss[13] = {0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36};
    int prevX, prevY; 
    
    int PY[10] = {1,2,3,4,5,7,8,9,10,11};
    int NC[12] = {6,6,6,6,9,5,7,14,10,6,6,6};
    int PO[10] = {1,2,3,4,5,6,5,4,3,2};
    int GR[12] = {5,5,4,4,3,3,2,2,1,1,1,1};
    
     
    
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
coord car1[1];

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
        for (int t = 0; t < 12; t++) {
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

    void draw(char plano[HEIGHT / dH][WIDTH / dW + 1],dato choqueR[1]) 
	{
    	prevX = x;
        prevY = Poss[y];
    	
        for (int i = 0; i < 6; i++) {
             borrar(plano, prevX * dW + pass[c].pos[i].x, prevY * dH + pass[c].pos[i].y);
        }
        
        
        for (int i = 0; i < 6; i++) {
            dibujar(plano, (x + pass[c].pos[i].x * dW), (Poss[y] + pass[c].pos[i].y * dH), pass[c].car[i]);
            choqueR[0].pos[i].x =(x + pass[c].pos[i].x * dW);
            choqueR[0].pos[i].y=(Poss[y] + pass[c].pos[i].y * dH);
        }

    }
    
    void draw(char plano[HEIGHT / dH][WIDTH / dW + 1],int t, int u, int c, dato choqueC[12][5])
    {
    	for(int j = 0; j < t; j++)
    {
    for(int i = 0; i < NC[c]; i++)
    {
        dibujar(plano, (car[u][j].x) + pass[c].pos[i].x, (Poss[car[u][j].y]) + pass[c].pos[i].y, pass[c].car[i]);
        choqueC[u][j].pos[i].x = (car[u][j].x) + pass[c].pos[i].x ;
        choqueC[u][j].pos[i].y = (Poss[car[u][j].y]) + pass[c].pos[i].y;
    }
}
	}
	
	void generacion(char plano[HEIGHT / dH][WIDTH / dW + 1],int nivel,dato choque[12][5] )
	{
		for(int i=0 ; i<10;i++)
		{
			draw(plano,niveles[nivel][i],i,PO[i],choque);
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
	void des()
	{
	p1++;
	if(p1>2000){	
	p1=0;
}
	p2++;
	if(p2>3000){	
	p2=0;
}
	p3++;
	if(p3>3500){	
	
	p3=0;
}
	p4++;
	if(p4>4000)
	{	  
	p4=0;
	
    }
    min--;
}
	void desplazamiento(int nivel)
	{
		if(p1==2000)
		{
			for(int i =0;i<niveles[nivel][7];i++)
			{
				car[7][i].x++;
				if(car[7][i].x>60)
				car[7][i].x=0;
			}
		}
	if(p2==3000)
		{
			for(int i =0;i<niveles[nivel][3];i++)
			{
				car[3][i].x--;
				if(car[3][i].x>60)
				car[3][i].x=0;
			}
			for(int i =0;i<niveles[nivel][5];i++)
			{
				car[5][i].x--;
				if(car[5][i].x<0)
				car[5][i].x=60;
			}
		}
		if(p3==3500)
		{
			for(int i =0;i<niveles[nivel][1];i++)
			{
				car[1][i].x++;
				if(car[1][i].x>60)
				car[1][i].x=0;
			}
			for(int i =0;i<niveles[nivel][8];i++)
			{
				car[8][i].x--;
				if(car[8][i].x<0)
				car[8][i].x=60;
			}
		}
		if(p4==4000)
		{
			for(int j=0;j<5;j+=2)
			{
				
			
			for(int i =0;i<niveles[nivel][j];i++)
			{
				car[j][i].x--;
				if(car[j][i].x<0)
				car[j][i].x=60;
			}
		}
            for(int j=6;j<10;j+=3)    		
			for(int i =0;i<niveles[nivel][j];i++)
			{
				car[j][i].x++;
				if(car[j][i].x>60)
				car[j][i].x=0;
			}
		}
			
	}
	
	int col(dato choqueR[1], dato choqueC[12][5], int r, int l, int nivel) 
	{
    for (int t = 0; t < niveles[nivel][l-1]; t++) {
        for (int i = 0; i < NC[0]; i++) {
            for (int j = 0; j < NC[1]; j++) {
                if (choqueR[0].pos[i].x == choqueC[l-1][t].pos[j].x && choqueR[0].pos[i].y == choqueC[l-1][t].pos[j].y) {
                    return r;  
                }
            }
        }
    }
    return 0;  
}
	void colision (dato choqueR[1],dato choqueC[12][5],int &nivel)
	{
		switch(y)
		{
			case 0:
				break;
				
			case 1:
				if(col(choqueR,choqueC,0,y,nivel)== 0)
				{
					muerte(nivel);
				}
				
				break;
				
			case 2:
				if(col(choqueR,choqueC,0,y,nivel)== 0)
				{
					muerte(nivel);
				}
				
				break;
				
			case 3:
				if(col(choqueR,choqueC,0,y,nivel)== 0)
				{
					muerte(nivel);
				}
				
				break;
				
			case 4:
				if(col(choqueR,choqueC,0,y,nivel)== 0)
				{
					muerte(nivel);
				}
				
				break;
				
			case 5:
				if(col(choqueR,choqueC,0,y,nivel)== 0)
				{
					muerte(nivel);
				}
				
				break;
				
					case 6:
				break;
				
					case 7:
				if(col(choqueR,choqueC,0,y,nivel)== 0)
				{
					muerte(nivel);
				}
				
				break;
				
					case 8:
				if(col(choqueR,choqueC,0,y,nivel)== 0)
				{
					muerte(nivel);
				}
				
				break;
				
					case 9:
				if(col(choqueR,choqueC,0,y,nivel)== 0)
				{
					muerte(nivel);
				}
				
				break;
				
					case 10:
				if(col(choqueR,choqueC,0,y,nivel)== 0)
				{
					muerte(nivel);
				}
				
				break;
				
					case 11:
				if(col(choqueR,choqueC,0,y,nivel)== 0)
				{
					muerte(nivel);
				}
				break;
				
					case 12:
						ganar(nivel);
						nivel++;
						con=8;
						min = 300;
						
				break;
		}
	}
	void muerte (int nivel)
	{
		x=25;
		y=0;
		con--;
		limpiar();
		retxy(nivel);
	}
	void limpiar()
	{
		for(int i=0; i<11;i++)
		{
			for(int j=0; j<5;j++)
			{
				car[i][j]= car1[0];
			}
		}
	}
	void ganar(int &nivel)
	{
		y=0;
		x=28;
		limpiar();
		retxy(nivel);
	}
	void reinicio (int &nivel)
	{
		con=8;
		nivel=0;
		min=300;
		limpiar();
		retxy(nivel);
	}
	void perder (int & nivel)
	{
		
		if(con<=0)
		reinicio(nivel);
		
		if (min <= 0)
		con--;
	}
	void portada()
	{
		gotoxy(80,0);cout<<"------------------------";
	    gotoxy(80,1);cout<<"--------FROGGER---------";
	    gotoxy(80,2);cout<<"------------------------";
	    gotoxy(80,3);cout<<"-------Iniciar-Juego-----";
	    gotoxy(80,4);cout<<"------------------------";
	    
	    gotoxy(70,8);cout<<"------Instrucciones-----";
	    gotoxy(70,9);cout<<"-------------------------------";
	    gotoxy(70,10);cout<<"--Movimiento-De-La-Rana--------";
	    gotoxy(70,11);cout<<"--W-Para-Moverse-Hacia-Arriba------------------";
	    gotoxy(70,12);cout<<"--S-Para-Moverse-Hacia-Abajo-------------------";
	    gotoxy(70,13);cout<<"--A-Para-Moverse-Hacia-La-Izquierda------------";
	    gotoxy(70,14);cout<<"--D-Para-Moverse-Hacia-La-Derecha--------------";
	    gotoxy(70,15);cout<<"-----------------------------------------------";
	    gotoxy(70,16);cout<<"-Si-Los-Obstaculos-Te-Chocan-Perderas-Una-Vida-";
	    
	    gotoxy(80,20);cout<<"----Presiona-ESC-Para-Salir-----";
	    gotoxy(80,22);cout<<"Tiempo:  ";
	    gotoxy(95,22);cout<<"Vidas:   ";
	    gotoxy(88,24);cout<<"nivel:   ";
	    
	    
	}
	
	void marcador(int nivel)
	{
		gotoxy(88,22);cout<<min;
		gotoxy(103,22);cout<<con;
		gotoxy(100,24);cout<<nivel;
		if(min==99)
		{
		gotoxy(96,24);cout<<"    ";		
		}
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
    
    float fps=5.0f;
    float dt=1.0f/fps;
    float acumulador=0.0f;
    
  
    clock_t inicio = clock();
    
    j1.pasar();
    j1.retxy(nivel);
    j1.portada();
    
    bool game = true;
    
    int dir=0;

    
    while (game) {
    	
    	

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
                case 'P':
                case 'p':
                j1.reinicio(nivel);
                break;
                }
            }
    		
		j1.ejecucion(dir);
		j1.direccion(dir);
		acumulador -=dt;
		}
		
	   j1.marcador(nivel); 
       j1.des();
       j1.Pmapa(plano);
       j1.generacion(plano,nivel,choqueC);
       j1.draw(plano,choqueR);
       j1.desplazamiento(nivel);
       j1.colision(choqueR,choqueC,nivel);
       j1.perder(nivel);
       
	   gotoxy(0,0);
       Sleep(80);
  }



    return 0;
}
