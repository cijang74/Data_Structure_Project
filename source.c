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
    int is_visited;
    int is_item;
    int is_monster;
    int is_event;
    int x;
    int y;
}Map_node;

typedef struct Monster {
    int hp;
    int df;
    int atk;
    int ct;
}monster;

// 상수
#define DEFAULT_CHARACTER_X 10
#define DEFAULT_CHARACTER_Y 10
#define UILINE_X 0
#define UILINE_Y 23
#define SIZE 9 // 맵의 최대 크기

#define REAL_ADD_X 10 // 캐릭터의 실제 위치는 10,10이기에 배열의 위치와 노드 좌표값을 동일하게 만들어주는 반복문을 실행할 때 이를 고려하기 위한 변수
#define REAL_ADD_Y 5

int stop_move = 0;
int flag = 0;
int flag2 = 0;
int flag3 = 0;
int flag4 = 0;
int stage1_flag = 0;
int select_turn = 1;
int test = 0;
int cc = 0;
int stage_num = 1;
int default_choose = 1;

monster slime = { 4,0,1,0 }; // 이거 반복되면 안됨

Caracter caracter = { "BoiB", 5, 0, 1, 10, DEFAULT_CHARACTER_X, DEFAULT_CHARACTER_Y };
struct Map_node node[SIZE][SIZE]; // 전역변수

//system("cls")가 필요할 떄는 캐릭터가 행동할 때, 캐릭터의 스테이터스가 변동될 때, 몬스터가 행동할 때, 몬스터의 스테이터스가 변동될 떄, 맵 이동할 떄
// 전직할 때

void print_text_ui(int key) // 반복되는 함수
{
    switch (key)
    {
    case 1:
        if (flag2 == 0)
        {
            stop_move = 1;
            gotoxy(UILINE_X, UILINE_Y + 1);
            printf("모험을 시작합니다...[ctrl]");
        }

        if (isKeyDown(VK_CONTROL))
        {
            stop_move = 0;
            flag2 = 1;
            system("cls");
        }
        break;
    }
}

void print_battle_ui(int key)
{
    switch (key)
    {
    case 0: // 아무것도 없슴.
        gotoxy(40, 15);
        printf("／／               ＼＼");
        gotoxy(39, 16);
        printf("／／                   ＼＼");
        gotoxy(38, 17);
        printf("／／                       ＼＼");
        gotoxy(37, 18);
        printf("／／                           ＼＼");
        gotoxy(36, 19);
        printf("／／                               ＼＼");
        gotoxy(35, 20);
        printf("／／                                   ＼＼");
        gotoxy(34, 21);
        printf("／／                                       ＼＼");
        gotoxy(33, 22);
        printf("／／                                           ＼＼");
        break;

    case 1: // 슬라임
        gotoxy(42, 8);
        printf("└──────────┘");
        gotoxy(42, 9);
        printf("│          │");
        gotoxy(42, 10);
        printf("│          │");
        gotoxy(42, 11);
        printf("│   □ □  │");
        gotoxy(42, 12);
        printf("│    ~~~   │");
        gotoxy(42, 13);
        printf("└──────────┘");
        gotoxy(40, 15);
        printf("／／               ＼＼");
        gotoxy(39, 16);
        printf("／／                   ＼＼");
        gotoxy(38, 17);
        printf("／／                       ＼＼");
        gotoxy(37, 18);
        printf("／／                           ＼＼");
        gotoxy(36, 19);
        printf("／／                               ＼＼");
        gotoxy(35, 20);
        printf("／／                                   ＼＼");
        gotoxy(34, 21);
        printf("／／                                       ＼＼");
        gotoxy(33, 22);
        printf("／／                                           ＼＼");
        break;

    case 10: // 출구
        gotoxy(41, 6);
        printf("──────────────────");
        gotoxy(41, 7);
        printf("    옷->ㅁ  출구");
        gotoxy(41, 8);
        printf("──────────────────");
        gotoxy(41, 9);
        printf("│                │");
        gotoxy(41, 10);
        printf("│                │");
        gotoxy(41, 11);
        printf("│                │");
        gotoxy(41, 12);
        printf("│                │");
        gotoxy(41, 13);
        printf("│                │");
        gotoxy(41, 14);
        printf("│                │");
        gotoxy(40, 15);
        printf("／／               ＼＼");
        gotoxy(39, 16);
        printf("／／                   ＼＼");
        gotoxy(38, 17);
        printf("／／                       ＼＼");
        gotoxy(37, 18);
        printf("／／                           ＼＼");
        gotoxy(36, 19);
        printf("／／                               ＼＼");
        gotoxy(35, 20);
        printf("／／                                   ＼＼");
        gotoxy(34, 21);
        printf("／／                                       ＼＼");
        gotoxy(33, 22);
        printf("／／                                           ＼＼");
        break;
    }
}

void print_map_ui()
// 반복되는 함수
{
    gotoxy(0, 0);
    printf("[HP]: %d", caracter.hp);
    gotoxy(UILINE_X, UILINE_Y);
    printf("========================================================================================================================");

    for (int i = 0; i < 23; i++)
    {
        gotoxy(29, i);
        printf("∥");
    }

    gotoxy(caracter.x, caracter.y);
    printf("■");

    print_battle_ui(0); // <- 반복됨

}

void Move_caracter() //플레이어의 움직임을 담당하는 함수
{
    node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].is_visited = 1;

    if (isKeyDown(VK_LEFT) && (caracter.x > 10)) //만약에 왼쪽키를 눌렀다는 것이 확인이 된다면
    {
        if (node[caracter.x - REAL_ADD_X - 1][caracter.y - REAL_ADD_Y].is_wall == 0)
        {
            if (stop_move != 1)
                caracter.x -= 1; //플레이어의 x값을 1 감소
        }
        system("cls");
        Sleep(30);
    }

    if (isKeyDown(VK_RIGHT) && (caracter.x < 19)) //"오른쪽키
    {
        if (node[caracter.x - REAL_ADD_X + 1][caracter.y - REAL_ADD_Y].is_wall == 0) // 오른쪽
        {
            if (stop_move != 1)
                caracter.x += 1; //"x값 1증가
        }
        system("cls");
        Sleep(30);
    }

    if (isKeyDown(VK_UP) && (caracter.y > 6))
    {
        if (node[caracter.x - REAL_ADD_X][caracter.y + 1 - REAL_ADD_Y].is_wall == 0) // 윗쪽
        {
            if (stop_move != 1)
                caracter.y -= 1;
        }
        system("cls");
        Sleep(30);
    }

    if (isKeyDown(VK_DOWN) && (caracter.y < 14))
    {
        if (node[caracter.x - REAL_ADD_X][caracter.y - 1 - REAL_ADD_Y].is_wall == 0) // 아래쪽
        {
            if (stop_move != 1)
                caracter.y += 1;
        }
        system("cls");
        Sleep(30);
    }
}

void map_node_init()
// 맵 노드 초기화
{
    if (flag == 0) // 한번만 실행되게 해야함.
    {
        for (int i = 0; i < 9; i++)
            // 배열의 위치와 노드 좌표값을 동일하게 만들어주는 반복문
        {
            for (int j = 0; j < 9; j++)
            {
                node[i][j].x = REAL_ADD_X + i;
                node[i][j].y = REAL_ADD_Y + j;
                node[i][j].is_wall = 1; // 처음에는 통과 가능한 지역이 아니라고 해둘거임
                node[i][j].is_visited = 0;
                node[i][j].is_item = 0;
                node[i][j].is_monster = 0;
                node[i][j].is_event = 0;
            }
        }
    }
    flag = 1;
}

void check_arround_node()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (node[i][j].is_visited == 1)
            {
                gotoxy(node[i][j].x, node[i][j].y);
                printf("□");
            }
        }
    }

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
        }

        if (node[caracter.x - REAL_ADD_X][caracter.y - 1 - REAL_ADD_Y].is_wall == 0) // 아래쪽
        {
            gotoxy(caracter.x, caracter.y - 1);
            printf("□");
        }
    }
}

void drop_item(int key)
{
    switch (key)
    {
    case 1:
        
        while (flag3 == 0)
        {
            stop_move = 1;
            gotoxy(UILINE_X, UILINE_Y + 1);
            printf("당신은 상자를 발견했습니다...");
            gotoxy(UILINE_X, UILINE_Y + 2);
            printf("상자 안에서 [무뎌진 검]을 획득하였습니다...[ctrl]");

            if (isKeyDown(VK_CONTROL))
            {
                stop_move = 0;
                flag3 = 1;
                system("cls");
                Sleep(30);
            }
        }
    }
}

void enemy_attack(monster* monster)
{

}

void battle_control(monster* monster) // 반복되는 함수 안에 있는 함수
{
    gotoxy(42, 5);
    printf("[HP: %d]", monster->hp);

    if (select_turn)
    {
        gotoxy(5, UILINE_Y + default_choose);
        printf("◀");
    }

    if (isKeyDown(VK_CONTROL) && select_turn == 1) // 선택창에서 컨트롤키를 눌렀을떄
    {
        select_turn = 0;

        switch (default_choose)
        {
        case 1: // 공격
            monster->hp = monster->hp - (caracter.atk - monster->df);
            system("cls");
            Sleep(30);

            gotoxy(UILINE_X, UILINE_Y + 1);
            printf("[슬라임]에게 %d 만큼의 피해를 주었다![ctrl]", caracter.atk - monster->df);
            break;
        }
    }

    else if (isKeyDown(VK_CONTROL) && select_turn == 0) // 선택창이 아닐때 컨트롤키를 눌렀다면
    {
        select_turn = 1;
        system("cls");
    }

    if (isKeyDown(VK_DOWN) && default_choose < 4)
    {
        default_choose++;
        Sleep(30);
    }

    else if (isKeyDown(VK_UP) && default_choose > 1)
    {
        default_choose--;
        Sleep(30);
    }
}

void battle_monster(int key) // 반복되는 함수 안에 있는 함수
{
    switch (key)
    {
    case 1:
        print_battle_ui(1);

        while (flag4 == 0)
        {
            stop_move = 1;
            gotoxy(UILINE_X, UILINE_Y + 1);
            printf("[슬라임]이 당신을 공격해왔다!!...[ctrl]");

            if (isKeyDown(VK_CONTROL))
            {
                stop_move = 0;
                flag4 = 1;
                system("cls");
                Sleep(30);
            }
        }

        if (slime.hp > 0)
        {
            stop_move = 1;

            if (select_turn == 1) // 선택창 변수가 True일때
            {
                gotoxy(UILINE_X, UILINE_Y + 1);
                printf("[공격]");

                gotoxy(UILINE_X, UILINE_Y + 2);
                printf("[스킬]");

                gotoxy(UILINE_X, UILINE_Y + 3);
                printf("[방어]");

                gotoxy(UILINE_X, UILINE_Y + 4);
                printf("[아이템]");
            }
            battle_control(&slime);
        }

        if (slime.hp <= 0)
        {
            node[4][5].is_monster = 0;
            gotoxy(UILINE_X, UILINE_Y + 2);
            printf("슬라임을 물리쳤다!");
        }

        break;
    }
}

void event_manage(int key) // 반복되는 함수
{

}

void stage1() // 반복되는 함수
{
    map_node_init();

    if (stage1_flag == 0)
    {
        node[0][5].is_wall = 0;

        node[1][5].is_wall = 0;

        node[2][5].is_wall = 0;
        node[2][5].is_item = 1;

        node[3][5].is_wall = 0;

        node[4][5].is_wall = 0;
        node[4][5].is_monster = 1;

        node[5][5].is_wall = 0;
        node[5][5].is_event = 1;

        stage1_flag = 1;
    }

    print_text_ui(1); // <- 반복됨

    if (node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].is_item == 1) // 내가 방문한 노드가 아이템을 드롭하는 노드인지 검사하는 함수
    {
        drop_item(1);
    }

    if (node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].is_monster == 1) // 내가 방문한 노드가 몬스터와 싸우는 노드인지 검사하는 함수
    {
        battle_monster(1);
    }

    if (node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].is_event == 1)
    {
        event_manage(1);
    }

    Move_caracter();
    check_arround_node();
}

void Dungeon()
{
    CursorView(0);

    while (caracter.hp > 0)
    {
        if (stage_num == 1)
        {
            stage1();
        }
        print_map_ui();
    }
}

int main()
{
    Dungeon();
}