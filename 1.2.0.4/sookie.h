#ifndef SOOKIE_H_
#define SOOKIE_H_

#include"init.h"
#include<conio.h>
#include<stdio.h>
#include<windows.h>
#include"random.h"


void hello(void){
	system("title Sookie_x32.exe Version:1.0_Release Author:Linxinyang -jpgzx");
	
	printf("Hello Unknown Player! Welcome to Sookie Says!\n\n");
	printf("Rules:\n");
	printf("\t1.In each turn, Sookie will reset the mine in the map randomly.\n");
	printf("\t2.You need to avoid touching mines as MUCH as you can, you can try if there's any mines by throwing stones.\n");
	printf("\t3.The faster you get to the finish point, the more points you get!\n");
	printf("\t\t P.S. The stones can explode the mines in a 3*3 grid around it, the mine won't hurt you after it has exploded.\n");
	putchar(10);
	printf("Unless you reach the 'P' point safely, you lose the game!!\n\n");
	
	printf("Copyright: Golden Apple Jincheng No.1 Secondary School Linxinyang\n");
	printf("Contact: std6051@outlook.com\n");
	printf("THIS GAME IS JUST FOR ENTERTAINMENT, DO NOT SPREAD RIP VERSION GAMES!\n");
	
	putchar(0xa);
	
	printf("Press any key twice to start the game.\n>");getch();getche();system("cls");
	
	printf("Use WASD to control youself.\nUse J to throw the stones, Space Button can launch it, and E can exit the throwing mode.\n");
	printf("The letter '$' means the grid id safe.\n");printf("Press Y to sign the safe grid.\n");
	printf("There is something for surprise......\n \nScore calculation method:\n\tTotalScore = 200 + Remaining Life(-ves)*1 + Stone*2 + Mine(that you have exploded)*1 + (300 - Time(you have used / SEC) )*3\n");
	printf("\nCopyright: Golden Apple Jincheng No.1 Secondary School _Linxinyang\n");
	printf("/ CopyRight / \n");
	
		ChooseDifficultyLevel();
	system("cls");
	
	gotoxy(35, 15);printf("Loading......\n");
	
	gotoxy(37, 16);printf("Game board initializing.> ");Sleep(150);Ginit();Sleep(150);printf("Completed +\n");
	gotoxy(37, 17);printf("Game objects initializing.> ");Sleep(150);GetObjects();Sleep(150);printf("Completed +\n");
	Sleep(503);
}

static point calibration(point& p){
	if(p.x > 16 || p.y > 33){
		Igame(0xa1b);
		p.x = min(p.x, 16);
		p.y = min(p.y, 33);
	}
	if(p.x < 1 || p.y < 1){
		Igame(0xa1b);
		p.x = max(p.x, 1);
		p.y = max(p.y, 1);
	}
	return p;
}

#include<queue>
using std:: queue;

void launch(const point& ps){
	queue<point> q; 
	for(int i = 0; i <= 8; ++i){
		if(crt[ps.x + dirx[i]][ps.y + diry[i]] == '#'){
			q.push( (point){ps.x + dirx[i], ps.y + diry[i]} );
			crt[ps.x + dirx[i]][ps.y + diry[i]] = '.';
		}
	}
	--stone;
	gotoxy(69, 7);
	printf("Launch Data:\n");int loop = 1;
	while(!q.empty()){
		gotoxy(73, 7 + loop);
		printf("$ Position { %d, %d } = mine, ~ Exploded; \n", q.front().y, q.front().x);
		q.pop();
		loop++;
	}
	gotoxy(69, 8 + loop);printf(">` Press any key to continue... >%d>", loop - 1);
	getche();
	score += loop - 1;
}

void _throw(const point& plr){//Default position
	point df = df.getRP(11, 22);

	do{
		system("cls");
		printx(plr, START, END, 0, df, 1);
		
		char _ip = getch();
		if(_ip < 0) _ip = getch();
		switch(_ip){
			case 'E': case 'e':
				return ;
				
			case 'W': case 'w': case 72: 
					df.x --;
				break;
				
			case 'A': case 'a': case 75:
					df.y --;
				break;
				
			case 'S': case 's': case 80:
					df.x ++;
				break;
				
			case 'D': case 'd': case 77:
					df.y ++;
				break;
				
			case 0x1b:
					Igame(0xff, 0, plr);
				break;
				
			case 0x20:
					launch(df);
				break;
				
			default:
				Igame(0x98fe, _ip);
		}
		
		calibration(df);
	}while(true);
}

point control(point& p){
	char _ip = getch();
	if(_ip < 0) _ip = getch();
	switch(_ip){
		case '\a':
				p = (point){ 15, 32 };
			break;
		case 'W': 
			if(crt[p.x-1][p.y] != '#')p.x -= 2;
			else Igame(3316), --life;			
		case 'w': case 72: 
				p.x --;
			break;
		case 'A': 
			if(crt[p.x][p.y-1] != '#')p.y -= 2;
			else Igame(3316), --life;		
		case 'a': case 75:
				p.y --;
			break;
		case 'S': 
			if(crt[p.x+1][p.y] != '#')p.x += 2;
			else Igame(3316), --life;
		case 's': case 80:
				p.x ++;
			break;
		case 'D': 
			if(crt[p.x][p.y+1] != '#')p.y += 2;
			else Igame(3316), --life;
		case 'd': case 77:
				p.y ++;
			break;
			
		case 0x1b:
				Igame(0xff, 0, p);
			break;
			
		case 'J': case 'j':
				_throw(p);
			break;
			
		case 'Y': case 'y':
				crt[p.x][p.y] = '$';
			break;
			
		default:
			Igame(0x98fe, _ip);
	}
	p = calibration(p);
	
	switch( crt[p.x][p.y]  ){
		case '#':
			Igame(3316);
			--life;
			return (point){ 1, 1 };
		case '*':
			Igame(0x55b, 0, p);
			++stone;
			crt[p.x][p.y] = '.';
			break;
		case '+':
			Igame(0x55b, 1, p);
			++life;
			crt[p.x][p.y] = '.';
			break;
		case 'R':
			p = p.getRP();
			Igame(0x43d, 5, p);
			break;
		default: ;
	}
	
	if(p == END){finish = clock();Igame(0x0f);}
	else return p;
	
	return DN;
}

#endif