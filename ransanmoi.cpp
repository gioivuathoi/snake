#include <winbgim.h> 
#include<stdio.h>
#include<time.h>
#include<iostream>
using namespace std ;
#include<string.h>
#include "windows.h"

#define MINX 20
#define MINY 20
#define MAXX 480
#define MAXY 220
#define BACKGROUND 15

typedef struct Point {
	int x,y,x0,y0;
} P;

typedef struct HighScore {
	int point;
	char name[20];
} H;
void InitGame();
void drawPoint();
void Modern();
void classic();
void drawSnake();
void drawFood();
void drawGame();
void ChangeDirection();
void getHighScore();
void showHighSCore();
void mainloop();
bool checkPoint();
bool isempty();
bool endGame;
P snake[100];
int snakelength;
int level;
P food;
P direction;
H highscore;
int score;
const int D = 10;
void DrawPoint(int x, int y, int r) {
	circle(x,y,r);
	floodfill(x,y,getcolor());
}

bool CheckPoint() {
	if (snake[0].x == food.x && snake[0].y == food.y) 
	return false;
	else return true;
}

void InitGame() {
	setbkcolor(15);
	cleardevice();
	
	setfillstyle(1,6);
	bar(MINX,MINY,MAXX,MINY+5);
	bar(MINX,MINY,MINX+5,MAXY);
	bar (MINX,MAXY,MAXX,MAXY+5);
	bar(MAXX,MINY,MAXX+5,MAXY);
	setcolor(6);
	int up[] = {235,370,235,355,230,355,240,340,250,355,245,355,245,370,235,370};
	fillpoly(8,up);
	settextstyle(3,0,2); outtextxy(265,340,"Up");
	int down[] = {235,400,235,415,230,415,240,430,250,415,245,415,245,400,235,400};
	fillpoly(8,down);
	outtextxy(265,400,"Down");
	int right[] = {15,350,30,350,30,345,50,355,30,365,30,360,15,360,15,350};
	fillpoly(8,right);
	outtextxy(70,340,"Right");
	int left[] = {15,410,30,400,30,405,45,405,45,415,30,415,30,420,15,410};
	fillpoly(8,left);
	outtextxy(70,400,"Left");
	setfillstyle(1,0);
	bar(50,450,170,480); setcolor(15); settextstyle(3,0,1); outtextxy(60,455,"SPACE"); 
	setcolor(6); settextstyle(3,0,2); outtextxy(200,450,"Pause/Resum");
	setfillstyle(1,0);
	bar(50,500,170,530); setcolor(15); settextstyle(3,0,1); outtextxy(80,505,"ESC");
	setcolor(6); settextstyle(3,0,2); outtextxy(80,505,"Quit game");
	snake[0].x = 30; snake[0].y = 50;
	snake[1].x = 40; snake[1].y = 50;
	snake[2].x = 50; snake[2].y = 50;
	snakelength = 3;
	srand(time(NULL));
	do {
		food.x = 30 + rand()%(450);
		food.y = 30+ rand()%(190);
	} while(CheckPoint() == false);
}

void ChangeDirection(int x) {
	switch (x) {
	
		case 72 : if (direction.y != -D) {
			PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);
			direction.y = D; direction.x = 0;
		}
			break;
		case 80 : if (direction.y != D) {
			PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);
			direction.y = -D; direction.x = 0;
		}
			break;
		case 75 : if ( direction.x != D){
			PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);
			direction.x = -D; direction.y = 0;
		}
			break;
		case 77: if (direction.x != -D) {
			PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);
			direction.x = D; direction.y = 0;
		}	break;
		case 27 : endGame = true;
		break;
	
}}

void Modern() {
	for (int i =0; i< snakelength; i++) {
		if (i == 0) {
			snake[0].x0 = snake[0].x; snake[0].y0 = snake[0].y;
			snake[0].x = snake[0].x + direction.x;
			snake[0].y = snake[0].y + direction.y;
		}
		else {
			snake[i].x0 = snake[i].x; snake[i].y0 = snake[i].y;
			snake[i].x = snake[i-1].x0; snake[i].y = snake[i-1].y0;
			
		}
		if (snake[0].x > MAXX - 5 || snake[0].x < MINX + 5|| snake[0].y > MAXY -5 || snake[0].y < MINY +5 ) endGame = true;
		if ( i!= 0 && snake[0].x == snake[i].x && snake[0].y == snake[i].y) endGame = true;
	} 
	if (snake[0].x == food.x && snake[0].y == food.y) {
		PlaySound(TEXT("eatFood.wav"), NULL, SND_ASYNC);
		snake[snakelength].x = snake[snakelength - 1].x0;
		snake[snakelength].y = snake[snakelength -1].y0;
		snakelength++;
	}
	srand(time(NULL));
		do {
		food.x = 30 + rand()%(450);
		food.y = 30+ rand()%(190);
	} while(CheckPoint() == false);
}

void classic () {
	for (int i=0; i< snakelength; i++) {
		if (i == 0) {
			snake[0].x0 = snake[0].x; snake[0].y0 = snake[0].y;
			snake[0].x = snake[0].x + direction.x;
			snake[0].y = snake[0].y + direction.y;
		}
		else {
			snake[i].x0 = snake[i].x; snake[i].y0 = snake[i].y;
			snake[i].x = snake[i-1].x0; snake[i].y = snake[i-1].y0;
		}
		if (snake[0].x >= MAXX) snake[0].x = MINX + 5;
		if (snake[0].x <= MINX) snake[0].x = MAXX -5;
		if (snake[0].y >= MAXY) snake[0].y = MINY + 5;
		if (snake[0].x <= MINY) snake[0].y = MAXY -5;
		if ( i!= 0 && snake[0].x == snake[i].x && snake[0].y == snake[i].y) endGame = true;
	}
	if (snake[0].x == food.x && snake[0].y == food.y) {
		PlaySound(TEXT("eatFood.wav"), NULL, SND_ASYNC);
		snake[snakelength].x = snake[snakelength-1].x0;
		snake[snakelength].y = snake[snakelength-1].y0;
		snakelength++;
			}
		srand(time(NULL));	
			do {
		food.x = 30 + rand()%(450);
		food.y = 30+ rand()%(190);
	} while(CheckPoint() == false);
}
void drawSnake() {
	setfillstyle(1,1);
	for (int i=0; i< snakelength; i++) {
	DrawPoint(snake[i].x,snake[i].y,5);}
	int x = getcolor();
	setcolor(BACKGROUND);
	setfillstyle(1,BACKGROUND);
	circle(snake[snakelength -1].x0,snake[snakelength-1].y0,5);
	setcolor(x);
}
void drawFood() {
	setcolor(6);
	setfillstyle(1,6);
	DrawPoint(food.x,food.y,5);
	int x = getcolor();
	food.x0 = food.x; food.y0 = food.y;
	while (CheckPoint == false) {
		setcolor(BACKGROUND);
		setfillstyle(1,BACKGROUND);
		circle (food.x0,food.y0,5);
		setcolor(x);
	}
}
void drawGame() {
	drawSnake();
	drawFood();
	int x= getcolor();
	setcolor(0);
	score = snakelength*level*10 - level*30;
	char score_str[20];
	sprintf(score_str,"%d",score);
	settextstyle(4,0,3);
	outtextxy(510,20,"Score: ");
	outtextxy(520,20,score_str);
	setcolor(x);
}
void showHighScore() {
	FILE *f;
	H sh;
	f = fopen("F://C language//highscore1.txt", "r");
	if (f == NULL) {
		printf("loi khong mo duoc file diem cao");
		exit(1);
	}
	if (isempty) {
		strcpy(highscore.name, "Player");
		highscore.point = 0;
		getHighScore();
	}
	
	rewind(f);
	int i=0;
	setcolor(4);
	outtextxy(150,50,"HIGHSCORE: ");
	settextstyle(1,0,4);
	rewind(f);
	fscanf(f,"%d %s",&sh.point,&sh.name);
	outtextxy(150,70,sh.name);
	char spoint[20];
	sprintf(spoint,"%d",sh.point);
	outtextxy(150,90,spoint);
	
	fclose(f);
}
void getHighScore() {
	FILE *f;
	f = fopen("F://C language//highscore1.txt", "w");
	if (f == NULL) {
		printf(" moi khong mo duoc file diem cao");
		exit(1);
	}
	fscanf(f,"%d %s",&highscore.point,&highscore.name);
	if (highscore.point < score) {
	highscore.point = score;
	 outtextxy(150,50,"NEW HIGHSCORE: ");
	 char hpoint[20];
	 sprintf(hpoint,"%d",highscore.point);
	 outtextxy(150,70,hpoint);
	 outtextxy(150,90,"Ten cua ban: ");
	 int i=0;
	 char s[20];
	 char ch[2];
	 ch[1] = 0;
	 while (1) {
	 	ch[0] = getch();
	 	if (ch[0] == '\n' ) break;
	 	s[i] = ch[0];
	 	i++;
	 }
	 strcpy(highscore.name,s);
	 fprintf(f,"%d%s",highscore.point,highscore.name);
	 }
	 fclose(f);
}
bool isempty() {
	FILE *f;
	int n;
	f = fopen("F://C language//highscore1.txt", "r");
	fseek(f,0,SEEK_END);
	n = ftell(f);
	fclose(f);
	return (n == 0);
}
void mainloop(void (*xxx)()) {
	int x = getcolor();
	if (!kbhit()) {
		xxx();
	}
	else {
		char ch;
		ch = getch();
		if (ch == -32) ch = getch();
		if (ch == 32 ) {
			setcolor(4);
			outtextxy(100,100,"GAME PAUSE");
			ch = getch();
			while( ch != 32) {
				ch = getch();
				delay(0);
			}
			setcolor(BACKGROUND);
			outtextxy(100,100,"GAME PAUSE");
			delay(1000);
			setcolor(x);
		}
		ChangeDirection();
		mainloop(xxx);
	}
	
}
void showtextground( int x, int y, char *s, int color) {
	int bk = getbkcolor();
	setcolor(color);
	outtextxy(x,y,s);
	delay(250);
	setbkcolor(bk);
}
void run() {
	initwindow(800,600);
	showHighScore();
	int x =0;
	char *s = new char[5];
	while (x <=100) {
		cleardevice();
		setcolor(1); settextstyle(4,0,5); outtextxy(60,200,"GAME LOADING...");
		sprintf(s,"%d",x);
		outtextxy(500,240,strcat(s,"%"));
		if(x == 100) delay(1000);
		delay(20);
		x++;
	}
	
while(true) {
	x1 : 
	int bk = getbkcolor();
	cleardevice();
	setbkcolor(0);
	cleardevice();
	clearmouseclick(WM_LBUTTONDOWN);
	PlaySound(TEXT("faded.wav"), NULL , SND_ASYNC);
	while (!ismouseclick(WM_LBUTTONDOWN) || mousex() < 210 || mousex() > 580 || mousey() < 190 || mousey() >465 ) {
		settextstyle(4,0,6);
		setcolor(2);
		outtextxy(250,70,"NEW GAME");
		outtextxy(250, 210, "NEW GAME");
		outtextxy(250, 270, "HIGHEST SCORE");
		outtextxy(250, 340, "QUIT GAME");
		outtextxy ( 250, 410, " ABOUT AUTHOR");
	} 
	if (mousey() <= 253) {
		showtextground(250,210,"NEW GAME", 4);
		x2: 
		setbkcolor(6);
		int nameFunction;
		cleardevice();
		while(!ismouseclick(WM_LBUTTONDOWN) || mousex() < 210 || mousex() > 470 || mousey() < 210 || mousey() <400 ) {
			setcolor(1);
			settextstyle(4,0,6);
			outtextxy(250,150," GAME TYPE");
			outtextxy(250,250, "CLASSIC");
			outtextxy(250, 320, "MODERN");
		}
		if ( ismouseclick(WM_LBUTTONDOWN) && mousey() < 283 ) nameFunction = 1;
		if (ismouseclick(WM_LBUTTONDOWN) && mousey() < 353 && mousey() > 287) nameFunction = 2;
		
		setbkcolor(0);
		cleardevice();
		setcolor(1); settextstyle(4,0,6);
		outtextxy(300,150, "PLEASE CHOOSE LEVEL");
		int x = 300;
		char str[2];
		for (int i =1; i<=5; i++) {
			sprintf(str,"%d",i);
			outtextxy(x, 250, str);
			x = x+ 70;
		}
		if (ismouseclick(WM_LBUTTONDOWN) && mousey() < 283 && mousey() > 218) {
			if (mousex() < 360) level =1;
			else if( mousex() < 430 ) level = 2;
			else if( mousex() < 500) level = 3;
			else if (mousex() < 560) level = 4;
			else level =5;
		}
		PlaySound(TEXT("start.wav"), NULL , SND_ASYNC);
		InitGame();
		while(!endGame) {
			delay(240 - (level -1 ) * 40);
			if (nameFunction == 1) mainloop (classic);
			else mainloop (Modern);
			drawGame();
		}
		PlaySound(TEXT("endGame.wav"), NULL , SND_ASYNC);
		settextstyle(4,0,4);
		setcolor(4);
		outtextxy(100,100,"GAME OVER");
		outtextxy(100,140,"YOUR SCORE: ");
		char score_str[20];
		sprintf(score_str,"%d",score);
		outtextxy( 100,300,score_str);
		getHighScore();
		outtextxy(100,200,"Play again?");
		clearmouseclick(WM_LBUTTONDOWN);
		while(!ismouseclick(WM_LBUTTONDOWN)) {
			settextstyle(4,0,2);
			outtextxy(100, 210, "YES" ); outtextxy(150, 210, "NO");
		}
		if (ismouseclick(WM_LBUTTONDOWN)) {
			if (mousex() < 120) goto x2;
			if (mousex() < 170 && mousex() > 135) goto x1;
		}
	
	 }
	 else if (mousey() < 315) {
	 	cleardevice();
	 	showHighScore();
	    setcolor(1);
	    settextstyle(1,0,3);
	 	clearmouseclick(WM_LBUTTONDOWN);
	 	while(!ismouseclick(WM_LBUTTONDOWN)) {
	 		outtextxy (50,400,"BACK TO MENU");
		 }
		 if ( ismouseclick(WM_LBUTTONDOWN) && mousex() > 45 && mousey() >390 && mousey() < 420 )
		 goto x1;
	 	
		 
	 }
	 else if (mousey() < 385 ) exit(0);
	 else {
	 	int x = getcolor();
	 	setbkcolor(0);
	 	cleardevice();
	 	setcolor(3);
	 	settextstyle(10,0,4);
	 	outtextxy(260,20,"ABOUT: ");
	 	settextstyle(9,0,4);
	 	outtextxy( 260,40,"Hanoi University of science and technology");
	 	outtextxy(260,70, " Topic : Game Snake");
	 	outtextxy(260, 100, " Name: Vu Xuan Thinh");
	 	outtextxy (260, 130, " Main source : https://nguyenvanhieu.vn");
	 	clearmouseclick(WM_LBUTTONDOWN);
	 	while(!ismouseclick(WM_LBUTTONDOWN)) {
	 		outtextxy (50,400,"BACK TO MENU");
		 }
		 if ( ismouseclick(WM_LBUTTONDOWN) && mousex() > 45 && mousey() >390 && mousey() < 420 )
		 setcolor(x);
		 goto x1;
	 }
	
}
}
int main() {
	run();
	getch();
	closegraph();
	return 0;
}
