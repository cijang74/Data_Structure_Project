#include <stdio.h>
#include <stdlib.h>//system, sleep
#include <Windows.h>//SetConsoleCursorPosition, GetStdHandle, STD_OUTPUT_HANDLE
#include <mmsystem.h>

void gotoxy(int x, int y) //콘솔 좌표계를 설정해주는 함수
{
    COORD pos = { 2 * x, y }; //CORD 구초제 안의 멤버 pos에 위치값를 저장
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); //SetConsoleCursorPosition(핸들 값, 위치 값) : 커서 위치를 이동
}

int isKeyDown(int key) //특정 키를 눌렀는지 확인하는 함수, 맞으면 1 반환
{
    return ((GetAsyncKeyState(key) & 0x8000) != 0);
}

void CursorView(char show) //커서를 숨겨주는 함수
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor; //핸들과 콘솔 등 시스템 내의 구조체 맴버를 불러옴

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //기본 핸들값을 hConsol에 저장

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor); //시스템 내의 함수에 커서를 숨겨주게 하는 값을 전달
}