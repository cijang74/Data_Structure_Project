#include <stdio.h>
#include <string.h>
#include "heder.h"

typedef struct Caracter_status {
    char name[8];
    int hp;
    int df;
    int atk;
    int ct;
}Caracter_status;

#define DEFAULT_CHARACTER_X 10
#define DEFAULT_CHARACTER_Y 10
#define UILINE_X 0
#define UILINE_Y 23

Caracter_status caracter_status = { "BoiB", 5, 0, 1, 10 };

//system("cls")�� �ʿ��� ���� ĳ���Ͱ� �ൿ�� ��, ĳ������ �������ͽ��� ������ ��, ���Ͱ� �ൿ�� ��, ������ �������ͽ��� ������ ��, �� �̵��� ��
// ������ ��

void print_ui_text(int key)
{
    if (key == 1)
    {
        gotoxy(UILINE_X, UILINE_Y+1);
        printf("������ �����մϴ�.");
    }


}

void print_map_ui()
{
    gotoxy(DEFAULT_CHARACTER_X, DEFAULT_CHARACTER_Y);
    printf("��");

    gotoxy(UILINE_X, UILINE_Y);
    printf("========================================================================================================================");

    print_ui_text(1);
}

void print_battle_ui()
{
    gotoxy(UILINE_X, UILINE_Y);
    printf("========================================================================================================================");
}

void Dungeon()
{
    CursorView(0);

    while (caracter_status.hp > 0)
    {
        print_map_ui();
    }
}

int main()
{
    Dungeon();
}