#ifndef UPDATE_DATA_H_
#define UPDATE_DATA_H_

#include<cstdio>
#include<windows.h>
#include<stdlib.h>

bool exist(const char* filename){
	FILE *fp;
	fp = fopen(filename,"r");
	return fp != NULL;
}

char cUserNameBuffer[512];
char cFileName[1024];

bool InitFile(void){
    DWORD dwUserNameSize = 256;
    
    if(GetUserName(cUserNameBuffer, &dwUserNameSize)){
    	sprintf(cFileName, "~%s.ini", cUserNameBuffer);
	
		if( !exist(cFileName) )return 0;
		char str[303];
		sprintf(str, "'%s' exists, start new game? ", cFileName);
	
		auto _i = MessageBox(NULL, str, "</>", MB_YESNOCANCEL);
		switch(_i){
			case IDYES:
				return 1;
			case IDNO:
				return 0;
			case IDCANCEL:
				exit(0);
			default: ;
				//{ Igame(0xc44); return 0; }
		}
	}
    
    else {
    	char str[50];
        sprintf(str, "Get user name failed with error: %lu \n", GetLastError());
        MessageBox(NULL, str, "File Error!", MB_OK);
    }
    return 0;
}

bool DebugFileCheck(void){
	if(!exist("debug.ini"))return 0;
	freopen("debug.ini", "r", stdin);
	int k;int l[5] = {0xfffffff, 0, 0xfffffff, 0, 0xfffffff };
	
	for(int i = 1; i <= 7; i++)scanf("%d", &k), l[0] &= k;
	for(int i = 1; i <= 7; i++)scanf("%d", &k), l[1] |= k;
	for(int i = 1; i <= 7; i++)scanf("%d", &k), l[2] &= k;
	for(int i = 1; i <= 7; i++)scanf("%d", &k), l[3] |= k;	
	
	fclose(stdin);

	return ~(l[0] ^ l[1] ^ l[2] ^ l[3]) >> 1 == -1;
}

#endif

#undef UPDATE_DATA_H_