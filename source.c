#include <stdio.h>
#include <string.h>
#include "heder.h"

// 캐릭터 스테이터스
typedef struct Caracter {
    char name[8];
    int hp;
    int df;
    int atk;
    int ct;
    int x;
    int y;
}Caracter;

// 맵 노드
typedef struct Map_node {
    int is_wall;
    int monster_num;
    int item_num;
    int event_num;
    int x;
    int y;
}Map_node;

// 상수
#define DEFAULT_CHARACTER_X 10
#define DEFAULT_CHARACTER_Y 10
#define UILINE_X 0
#define UILINE_Y 23
#define SIZE 9 // 맵의 최대 크기

#define REAL_ADD_X 10 // 캐릭터의 실제 위치는 10,10이기에 배열의 위치와 노드 좌표값을 동일하게 만들어주는 반복문을 실행할 때 이를 고려하기 위한 변수
#define REAL_ADD_Y 5

int flag = 0;
int test = 0;
int stage_num = 1;
Caracter caracter = { "BoiB", 5, 0, 1, 10, DEFAULT_CHARACTER_X, DEFAULT_CHARACTER_Y};

//system("cls")가 필요할 떄는 캐릭터가 행동할 때, 캐릭터의 스테이터스가 변동될 때, 몬스터가 행동할 때, 몬스터의 스테이터스가 변동될 떄, 맵 이동할 떄
// 전직할 때

void map_node_init(Map_node node[][9])
// 맵 노드 초기화
{
    if (flag == 0) // 한번만 실행되게 해야함.
    {
        for (int i = 0; i < 9; i++)
            // 배열의 위치와 노드 좌표값을 동일하게 만들어주는 반복문
        {
            for (int j = 0; j < 9; j++)
            {
                node[i][j].x = REAL_ADD_X+i;
                node[i][j].y = REAL_ADD_Y+j;
                node[i][j].is_wall = 1; // 처음에는 통과 가능한 지역이 아니라고 해둘거임
                node[i][j].monster_num = 0;
                node[i][j].item_num = 0;
                node[i][j].event_num = 0;
            }
        }
    }
}

void check_arround_node(Map_node node[][9])
{
    if ((caracter.x <= 28 && caracter.x >= 10) && ((caracter.y >= 6) && (caracter.y <= 14)))
    {
        if (node[caracter.x - REAL_ADD_X + 1][caracter.y - REAL_ADD_Y].is_wall == 0) // 오른쪽
        {
            gotoxy(caracter.x + 1, caracter.y);
            printf("□");
        }

        if (node[caracter.x - REAL_ADD_X - 1][caracter.y - REAL_ADD_Y].is_wall == 0) // 왼쪽
        {
            gotoxy(caracter.x - 1, caracter.y);
            printf("□");
        }

        if (node[caracter.x - REAL_ADD_X][caracter.y + 1 - REAL_ADD_Y].is_wall == 0) // 윗쪽
        {
            gotoxy(caracter.x, caracter.y + 1);
            printf("□");

            gotoxy(1, 1);
            printf("응애");
        }

        if (node[caracter.x - REAL_ADD_X][caracter.y - 1 - REAL_ADD_Y].is_wall == 0) // 아래쪽
        {
            gotoxy(caracter.x, caracter.y - 1);
            printf("□");
        }
    }
}

void stage1() // 반복되는 함수
{
    struct Map_node node[SIZE][SIZE];
    caracter.x = DEFAULT_CHARACTER_X;
    caracter.y = DEFAULT_CHARACTER_Y;
    map_node_init(node);

    node[0][5].is_wall = 0;

    node[1][5].is_wall = 0;

    node[2][5].is_wall = 0;

    node[3][5].is_wall = 0;

    node[4][5].is_wall = 0;

    check_arround_node(node);
}

void print_text_ui(int key)
{
    gotoxy(UILINE_X, UILINE_Y);
    printf("========================================================================================================================");

    switch (key)
    {
    case 1:
        gotoxy(UILINE_X, UILINE_Y + 1);
        printf("모험을 시작합니다.");
        break;
    }
}

void print_map_ui()
// 반복되는 함수
{
    gotoxy(DEFAULT_CHARACTER_X, DEFAULT_CHARACTER_Y);
    printf("■");

    print_text_ui(1);

}

void print_battle_ui()
{
    gotoxy(UILINE_X, UILINE_Y);
    printf("========================================================================================================================");
}

void Dungeon()
{
    CursorView(0);

    while (caracter.hp > 0)
    {
        print_map_ui();

        if (stage_num == 1)
        {
            stage1();
        }
    }
}

int main()
{
    Dungeon();
}