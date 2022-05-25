#include <stdio.h>
#include <stdlib.h>//system, sleep
#include <Windows.h>//SetConsoleCursorPosition, GetStdHandle, STD_OUTPUT_HANDLE
#include <mmsystem.h>

void gotoxy(int x, int y) //�ܼ� ��ǥ�踦 �������ִ� �Լ�
{
    COORD pos = { 2 * x, y }; //CORD ������ ���� ��� pos�� ��ġ���� ����
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); //SetConsoleCursorPosition(�ڵ� ��, ��ġ ��) : Ŀ�� ��ġ�� �̵�
}

int isKeyDown(int key) //Ư�� Ű�� �������� Ȯ���ϴ� �Լ�, ������ 1 ��ȯ
{
    return ((GetAsyncKeyState(key) & 0x8000) != 0);
}

void CursorView(char show) //Ŀ���� �����ִ� �Լ�
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor; //�ڵ�� �ܼ� �� �ý��� ���� ����ü �ɹ��� �ҷ���

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //�⺻ �ڵ鰪�� hConsol�� ����

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor); //�ý��� ���� �Լ��� Ŀ���� �����ְ� �ϴ� ���� ����
}