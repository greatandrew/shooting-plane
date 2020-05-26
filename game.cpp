#include <algorithm>
#include <windows.h>
#include <cstring>
#include <cstdio>
#include <cmath>
 
const int N = 40;
char c;
int where1;//player
int where2 = 20;//plane
int count;
int gunRow = 20;

 
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
/*
#define PERR(bSuccess, api) {
    if(!(bSuccess)) 
	    printf("%s:Error %d from %s on line %d\n", __FILE__, GetLastError(), api, __LINE__);
	}
    void MyCls(HANDLE) ;
    inline void clrscr(void) {
    HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
    MyCls(hStdOut);
    return;
}
*/

void setCursor (int row, int col) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = {col, row};//The mouse return to (0,0) after the screen is cleaned
    BOOL bSuccess = SetConsoleCursorPosition(hConsole, coordScreen);
} 
 /*
void MyCls(HANDLE hConsole) {
	COORD coordScreen = {0, 0};//The mouse return to (0,0) after the screen is cleaned
	BOOL bSuccess;
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;//set suffer data
	DWORD dwConSize;//The number of now buffer can afford
	bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);//Get the data of the buffer
	PERR(bSuccess,"GetConsoleScreenBufferInfo");
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;//The number of buffer's data
	bSuccess = FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten);
	PERR(bSuccess, "FillConsoleOutputCharacter");
	bSuccess = GetConsoleScreenBufferInfo(hConsole,  &csbi);
	PERR(bSuccess, "ConsoleScreenBufferInfo");
	bSuccess = FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	PERR(bSuccess,"FillConsoleOutputAttribute"); 
	bSuccess = SetConsoleCursorPosition(hConsole, coordScreen);
	PERR(bSuccess, "SetConsoleCursorPosition");
	return;
}*/
 
int check(char c){//if a botton is pressed
	if(KEY_DOWN(c)) {
	    return 1;
    }
	 
	 return 0;
}


inline void printA (int x) {

	for(int i = 1; i <= 3; i ++ ) {
		setCursor( i - 1, x );
		printf("  ■■■■■  ");
		printf("\n");
	}
}

inline void printB (int x) {
	for(int i = 1; i <= 3; i ++) {
		if(i != 3) {
    	    setCursor( gunRow + i - 1, x );
			printf("      ■ \n");
		}
		else {
    	    setCursor( gunRow + i - 1, x );
			printf("  ■■■■■ ");
		}
	}
}

inline void print () {
	printA(where2);
    
	printB(where1);
	printf("\n  ");
	for(int i = 1; i <= N; i ++ ) {
		printf("=");
	}
	printf("\n");
	printf("score:%d", count);
}

void shoot () {
	for(int i = gunRow - 4; i > 0; i -- ) {
	    setCursor(i, where1 + 6);
	    printf("■");
	    Sleep(75);
	    setCursor(i, where1 + 6);
	    printf("  ");
    }
}

int main () {
    while(1) {
		print();
		Sleep (50);
    	int t = rand() % 2;
    	if(t == 0) if(where2 != 0) where2 -= 2;
    	if(t == 1) if(where2 != N - 10) where2 += 2;
    	if( check( 'A') ) {
    		if(where1 == 0) {
    			continue;
			}
			else {
				where1 -=2 ;
			}
		}
    	if(check ('D') ) {
    		if(where1 + 10 == N) {
    			continue;
			}
			else {
				where1 += 2;
			}
		}
		if(check ('W')) {
			shoot();
			if(abs(where1 + 3 - (where2 + 5)) < 3 ) {
				count ++ ;
			}
		}
	}

	return 0;
}
