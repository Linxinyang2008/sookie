#ifndef INIT_H_
#define INIT_H_

#include<time.h>

#ifndef CLOCK_PER_SEC
clock_t start, finish;
#endif

#include"random.h"
#include<windows.h>

int life = 0x15, stone = 0x25, score = 0, total = 0;
int StoneGrid = random_number(20, 31), SafeGrid = random_number(11, 17), MineCount, MediGrid;
	
bool SAVE = true;

#ifdef SOOKIE_H_

struct point{
	int x, y;
	
	point getRP(int x_max = 17, int y_max = 33){ 
		return (point){ random_number(1, x_max), random_number(1, y_max)} ;
	}
	point transpose(void){
		return (point){ y, x };
	}
	bool operator == (const point& ex){
		return ex.x == x && ex.y == y;
	}
	point operator + (const point& ex){
		return (point){ ex.x + x, ex.y + y };
	}
	point operator - (const point& ex){
		return (point){ ex.x - x, ex.y - y };
	}
	bool operator <= (const point& ex){
		return ex.x <= x && ex.y <= y;
	}
	bool operator != (const point& ex){
		return x != ex.x || y != ex.y;
	}
};

const point START = {1, 1}, END = {16, 33}, DN = {2147483647, 2147483647};

char crt[17][34];

void printx(const point& plr = DN, const point& start = START, const point& end = END, bool display = true, 
			const point& target = DN, bool control = false){
				
		if(plr.x != 1 || plr.y != 1)crt[START.x][START.y] = '.';
	
		for(int i = start.x; i <= end.x; i++){
			for(int j = start.y; j <= end.y; j++){
				if(control){
					//if( (i == target.x - 1 || i == target.x + 1) && j == target.y){ putchar('|');continue; }
					if( j == target.y - 1 && i == target.x ){	putchar('>');continue; }
					if( j == target.y + 1 && i == target.x ){   putchar('<');continue; }
					if( (point){ i, j } == target ){ putchar('*');continue; }				
				}
				if(display){
					putchar(crt[i][j]); continue; }
				if( (point){ i, j } == plr ) putchar('@');
				else if( (point){ i, j } == END ) putchar(crt[i][j]);
					else crt[i][j] == '.' || crt[i][j] == '$'? putchar(crt[i][j] == '.'? '.' : '$') : putchar('.');
			}
			putchar(0xa);
		}
	
	if(SAVE)printf("\nYour position: { X : %d, Y : %d }\nYour remaining life(-ves): %d\nYour remaining stones: %d\n", plr.y, plr.x, life, stone);
}

#include<iostream>
using std:: min, std:: max;

HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

void gotoxy(int x, int y){
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOut, pos);
}

void Ginit(const point& start = START, const point& end = END){
	for(int i = start.x; i <= end.x; i++){
		for(int j = start.y; j <= end.y; j++)
			crt[i][j] = '.';
	}
}

void GetObjects(void){

	for(int i = 1; i <= MineCount; ++i){
		point a = a. getRP();
		crt[a.x][a.y] = '#';
	}

	for(int i = 1; i <= SafeGrid;){
		point poi = poi.getRP();
		if(crt[poi.x][poi.y] != '#')crt[poi.x][poi.y] = '$', ++i;
	}
	
	for(int i = 1; i <= StoneGrid;){
		point poi = poi.getRP();
		if(crt[poi.x][poi.y] != '#' && crt[poi.x][poi.y] != '$')crt[poi.x][poi.y] = '*', ++i;
	}
	
	for(int i = 1; i <= MediGrid;){
		point poi = poi.getRP();
		if(crt[poi.x][poi.y] != '#' && crt[poi.x][poi.y] != '$' 
				&& crt[poi.x][poi.y] != '*')crt[poi.x][poi.y] = '+', ++i;
	}
	
	point poi = poi.getRP(12, 24);
	crt[poi.x][poi.y] = 'R';

	crt[1][1] = '@';
	crt[15][32] = '.';
	crt[16][33] = 'P';
}

#include<conio.h>

void ChooseDifficultyLevel(void){
	system("cls");
	printf("Sookie offers two difficulty level:\n\t1.Easy:  Mine: 55 ~ 113; MedicBagGrid: 20 Stone: 27.");
	printf("\n\t2.Normal:  Mine: 252 ~ 388; MedicBagGrid: 15 ~ 21 Stone: 20 ~ 31\n\n");
	printf("'~' means randomly choose.");
	
	char ch = 32;
	bool cs, f = 1;
	printf("\n\n1.Easy \n2.Normal\n");
	do{
		system("cls");
		printf("Sookie offers two difficulty level:\n\t1.Easy:  Mine: 55 ~ 113; MedicBagGrid: 20 Stone: 27.");
		printf("\n\t2.Normal:  Mine: 252 ~ 388; MedicBagGrid: 15 ~ 21 Stone: 20 ~ 31\n\n");
		printf("'~' means randomly choose.");
	
		switch(ch){
			case 'W': case 'w': case 72: case 49: 
				printf("\n\n1.Easy <\n2.Normal\n");//1
				cs = 1;f = 0;
				break;
			case 'S': case 's': case 80: case 50:
				printf("\n\n1.Easy \n2.Normal <\n");//0
				cs = 0;f = 0;
				break;
			default:
				printf("\n\n1.Easy \n2.Normal\n");
		}
		ch = getch();
		if(ch < 0)ch = getch();
		if(ch == 13 && !f)break;
	}while(true);
	
	cs? MineCount = random_number(55, 114), MediGrid = 20, stone = 27  :
		 MineCount = random_number(252, 389), MediGrid = random_number(15, 22), stone = random_number(20, 32);
}
#include"data.h"

void SaveData(const char* File, const point& plr = DN, const point& start = START, const point& end = END){
	freopen(File, "w", stdout);SAVE = false;
	printx(plr, start, end);
	fclose(stdout);SAVE = true;
}

void EndGame(void){
	system("cls");
	int duration = 300 - (int)(finish - start - 1) / CLOCKS_PER_SEC;
	printf("Your Total Score = 200 + %d(Life)*1 + %d(Stone)*2 + %d(Mine)*1 + %d(Time)*3 = %d\n\n", life, stone, score, duration, score + stone * 2 + life + duration * 3 + 200);
	printx(END, START, END);
}
void EndGameEx(){
	char str[75];
	sprintf(str, "%s~.dat", cUserNameBuffer);
	freopen(str, "w", stdout);
	EndGame();
	fclose(stdout);
}

static char str[50];
void Igame(int stopcode, char chi = 0x0, const point& tp = DN){
	memset(str, 0, sizeof(str) );
	switch(stopcode){
		case 0xff:{
			auto _i = MessageBox(NULL, "Do you want to EXIT ?", "EXIT", MB_OKCANCEL);

			switch (_i){
				case IDCANCEL:
					return ;
				case IDOK:
					SaveData(cFileName, tp);
					exit(0);
			}
			break;
		}
		case 0x0f:{
			EndGame(); EndGameEx();
			if(MessageBox(NULL, "Wanna Restart Game?", "?", MB_YESNO) == IDYES){
				system("cls");
				system("sookie.exe -r");
			}
			break;}
		case 0x98fe:{
			sprintf(str, "Keyboard Input Error!\nchar = %d", chi);
			MessageBox(NULL, str, "!", MB_OK);
			break;}
		case 0xcf4:
			MessageBox(NULL, "You touched the mine!", "RIP", MB_OK);
			break;
		case 0xa1b:
			MessageBox(NULL, "Boundary Overflow!", ":(", MB_OK);
			break;
		case 0xca33:
			sprintf(str, "Your remaining life is less than 5! (%d)", life);
			MessageBox(NULL, str, "Warning", MB_OK);
		case 0x55b:{
			const char *typ = (chi == 0)? "stone" : (chi == 1)? "medic bag" : "unknown object";
			sprintf(str, "You have found a %s at { %d, %d }.", typ, tp.y, tp.x);
			MessageBox(NULL, str, "Object Found!", MB_OK);
			break; }
		case 0x43d:
			sprintf(str, "Jump to { %d , %d }.", tp.y, tp.x);
			MessageBox(NULL, str, "Portal", MB_OK);
			break;
		default:
			MessageBox(NULL, "Unknown Error!\n 0x00042ff", "UKE", WN_RETRY);
	}
}

/*
mine #
space 32\ascii
Player @
stone *
*/

const int dirx[]={ 0,-1,-1, 0, 1, 1, 1, 0,-1};//[8]
const int diry[]={ 0, 0, 1, 1, 1, 0,-1,-1,-1};//[8]

void ReadData(const char* File = NULL, const point& start = START, const point& end = END){
	
	freopen(File, "r", stdin);
	
	for(int i = start.x; i <= end.x; i++){
		for(int j = start.y; j <= end.y; j++)
			crt[i][j] = getchar();
		getchar();
	}
	scanf("%d%d%d%d", &life, &stone, &score, &total);
	
	fclose(stdin);
	
	char cmd[129] = "del /Q *.ini";
	//sprintf(cmd, "del /Q '%s'\n", File);
	system(cmd);	
	//MessageBox(NULL, cmd, "cmd", MB_OK);
}
#endif

#endif