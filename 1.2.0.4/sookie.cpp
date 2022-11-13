#include<cstdio>
#include"sookie.h"

bool con = 1;
point plr = START;

const point eps = (point){3, 3};
point pp;

int main(int argc, char** argv){
	
	if(argc > 1 && argv[1][1] == 'r'){
		MessageBox(NULL, "Welcome Back to Main Menu!", "", MB_OK);
		goto bk1;
	}
	
//	if(!DebugFileCheck())
		if( !InitFile() ){bk1:
			hello();
			system("cls");
		}
		else ReadData(cFileName);
	
	start = clock();
	while(pp != DN){
		system("cls"), printx(plr, START, END, 0);
		plr = pp = control(plr);
	}
	
	return 0;
}
