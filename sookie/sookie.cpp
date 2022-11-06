#include<cstdio>
#include"sookie.h"

bool con = 1;
point plr = START;

const point eps = (point){3, 3};
point pp;

int main(void){
//	if(!DebugFileCheck())
		if( !InitFile() ){
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
