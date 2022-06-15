#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <string.h>
#include "heder.h"

typedef struct inventory { ///�κ��丮 ����ä
    char* arr[7];  //�������̶� +1
    int rear;
    int front;
    int invenCode[7]; //������ ���� �� �ɷ�ġ�� ��� ��ȯ�ؾ� �� ���� ���� �ε���
} inventory;

// ĳ���� �������ͽ�
typedef struct Caracter {
    char name[8];
    char job[8];
    int lv;
    int hp;
    int max_hp;
    int mp;
    int df;
    int atk;
    int ct;
    int x;
    int y;
    int exp;
    struct inventory playerInven;
}Caracter;

// �� ���
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
    char name[20];
    int hp;
    int df;
    int atk;
    int ct;
}monster;

typedef struct itemStruct { ///������ ����ü
    double hpIncrement;
    double damageIncrement;
    double armorIncrement;
    double criPerIncrement;
    char itemName[100];
    int itemCode;
} itemStruct;

itemStruct i1 = { 1,0,0,0,"������ ��",0 }; ///������ 4�� ���� , hp, ������, ��, ũ����, �������̸�, �������ڵ�
itemStruct i2 = { 0,0,1,0,"������ ����",1 };
itemStruct i3 = { 0,2,2,0,"��ȭ�� ���� ��Ʈ",2 };
itemStruct i4 = { 4,4,0,0,"�������� ��",3 };

// ���
#define DEFAULT_CHARACTER_X 10
#define DEFAULT_CHARACTER_Y 10
#define UILINE_X 0
#define UILINE_Y 23
#define SIZE 9 // ���� �ִ� ũ��
#define MAX_INVEN_SIZE 5

#define REAL_ADD_X 10 // ĳ������ ���� ��ġ�� 10,10�̱⿡ �迭�� ��ġ�� ��� ��ǥ���� �����ϰ� ������ִ� �ݺ����� ������ �� �̸� ����ϱ� ���� ����
#define REAL_ADD_Y 5

int skill_damage = 5;
int stop_move = 0;
int is_deffence = 0;
int coin = 0; //�ӽ�ȭ�� ����
int first_flag = 0;

// init ���� �÷���
int flag = 0;
int flagg = 0;
int flaggg = 0;

// �̺�Ʈ, ��ȭâ, ���� ���� �÷���
int flag2 = 0;
int flag4 = 0;
int flag5 = 0;
int flag6 = 0;
int flag7 = 0;
int flag8 = 0;
int is_escape = 0;

// ������ �÷���
int level_2_flag= 0;
int level_3_flag = 0;
int level_4_flag = 0;

// ������ �÷���
int item_flag = 0;
int item_flag2 = 0;
int item_flag3 = 0;
int item_flag4 = 0;

int sceneCounter = 0; //0�� �ʱ� ���� ȭ��

// �� ��� �����ϴ� �÷���
int stage1_flag = 0;
int stage2_flag = 0;
int stage3_flag = 0;

// ��¦��¦�ϴ°� ���� �÷���
int color_flag = 0;
int color_flag2 = 0;
int color_flag3 = 0;

int is_clear = 0;
int select_turn = 1;
int stage_num = 1;
int default_choose = 1;
int my_turn = 1;
int running = 1;
char messege[40] = { '\0' };
double increment[4];

int is_stack = 1; ///1�̸� �κ��丮�� �������� �ν�

monster slime = { "������",4,0,1,0 }; // �̸�, hp, df, atk, ct
monster mini_army = { "������ ����", 8, 2, 2, 0 };
monster skeleton = { "����", 12, 4, 4, 0 };

struct Map_node node[SIZE][SIZE]; // ��������

Caracter caracter = { "BoiB", "�⺻", 1, 5, 5, 3, 0, 1, 10, DEFAULT_CHARACTER_X, DEFAULT_CHARACTER_Y , 0, {" ", " ", " ", " ", " ", " ", " "} }; ///�÷��̾� ���� ����. hp, maxhp, atk, df, crt, pla

//system("cls")�� �ʿ��� ���� ĳ���Ͱ� �ൿ�� ��, ĳ������ �������ͽ��� ������ ��, ���Ͱ� �ൿ�� ��, ������ �������ͽ��� ������ ��, �� �̵��� ��
// ������ ��

void codeMatching_rear(Caracter* p) { // hp atk df ct
    if (p->playerInven.invenCode[p->playerInven.rear] == 0) { // ������ ��
        increment[0] = 0;
        increment[1] = 1;
        increment[2] = 0;
        increment[3] = 0;
    }
    else if (p->playerInven.invenCode[p->playerInven.rear] == 1) { // ������ ����
        increment[0] = 0;
        increment[1] = 0;
        increment[2] = 1;
        increment[3] = 0;
    }
    else if (p->playerInven.invenCode[p->playerInven.rear] == 2) { // ��ȭ�� ��Ʈ
        increment[0] = 0;
        increment[1] = 2;
        increment[2] = 2;
        increment[3] = 0;
    }
    else if (p->playerInven.invenCode[p->playerInven.rear] == 3) {
        increment[0] = 4;
        increment[1] = 4;
        increment[2] = 0;
        increment[3] = 0;
    }
    //������ ������ ���� �б⹮ �ۼ�
}

void codeMatching_front(Caracter* p) {
    if (p->playerInven.invenCode[p->playerInven.front + 1] == 0) {
        increment[0] = 0;
        increment[1] = 1;
        increment[2] = 0;
        increment[3] = 0;
    }
    else if (p->playerInven.invenCode[p->playerInven.front + 1] == 1) {
        increment[0] = 0;
        increment[1] = 0;
        increment[2] = 1;
        increment[3] = 0;
    }
    else if (p->playerInven.invenCode[p->playerInven.front + 1] == 2) {
        increment[0] = 0;
        increment[1] = 2;
        increment[2] = 2;
        increment[3] = 0;
    }
    else if (p->playerInven.invenCode[p->playerInven.front + 1] == 3) {
        increment[0] = 4;
        increment[1] = 4;
        increment[2] = 0;
        increment[3] = 0;
    }
    //������ ������ ���� �б⹮ �ۼ�
}

void delete_rear(Caracter* p) { ///���ؿ��� pop���� ���
    if (is_stack != 1) {
        printf("ť �κ��丮�̹Ƿ� ��� �Ұ�\n");
        return;
    }
    if (is_empty(p)) {
        printf("�κ��丮�� ������ϴ�.\n");
        return;
    }
    codeMatching_rear(p); ///����Ǹ� increment�� �����Ǵ� �������� ������Ű�� ������ �Ǿ� �ش� ��ġ��ŭ �÷��̾� ���ݿ��� ����
    int prev = p->playerInven.rear;
    p->hp -= increment[0];
    p->atk -= increment[1];
    p->df -= increment[2];
    p->ct -= increment[3];
    p->playerInven.rear = (p->playerInven.rear - 1 + MAX_INVEN_SIZE) % MAX_INVEN_SIZE;
    p->playerInven.arr[prev] = "";
}

void delete_front(Caracter* p) { ///ť���� dequeue�� ���
    if (is_stack == 1) {
        printf("���� �κ��丮�̹Ƿ� ��� �Ұ�\n");
        return;
    }
    if (is_empty(p)) {
        printf("�κ��丮�� ������ϴ�.\n");
        return;
    }
    codeMatching_front(p);
    p->hp -= increment[0];
    p->atk -= increment[1];
    p->df -= increment[2];
    p->ct -= increment[3];
    p->playerInven.front = (p->playerInven.front + 1) % MAX_INVEN_SIZE;
    p->playerInven.arr[p->playerInven.front] = " ";
}

int is_empty(Caracter* p) { ///����ִ���
    return p->playerInven.rear == p->playerInven.front;
}

void delete_nene(Caracter* p)
{
    if (is_full(p)) {
        if (is_stack == 1)
        {
            delete_rear(p);
        }

        else if (is_stack == 0)
        {
            delete_front(p);
        }
        return;
    }
}

void add_rear(Caracter* p, itemStruct* i) { ///�����̳� ť���� push�� enqueue�� ���

    if (p->playerInven.rear == p->playerInven.front != 0) { // 
        p->playerInven.rear = 0;
        p->playerInven.front = 0;
    }
    p->hp += i->hpIncrement;
    p->atk += i->damageIncrement;
    p->df += i->armorIncrement;
    p->ct += i->criPerIncrement;
    p->playerInven.rear = (p->playerInven.rear + 1) % MAX_INVEN_SIZE;

    p->playerInven.arr[p->playerInven.rear] = i->itemName;

    p->playerInven.invenCode[p->playerInven.rear] = i->itemCode;
}

void exp_checking()
{
    if ((caracter.exp >= 5 && caracter.exp < 15) && level_2_flag == 0)
    {
        caracter.lv = 2;
        // �⺻ hp 5 / mp 3 / df 0 / atk 1
        caracter.hp = 6;
        caracter.mp = 4;
        caracter.df = 1;
        caracter.atk = 2;

        caracter.max_hp = 6;
        level_2_flag = 1;
    }

    else if ((caracter.exp >= 15 && caracter.exp < 20) && level_3_flag == 0)
    {
        caracter.lv = 3;
        // �⺻ hp 5 / mp 3 / df 0 / atk 1
        caracter.hp = 7;
        caracter.mp = 5;
        caracter.df = 2;
        caracter.atk = 3;

        caracter.max_hp = 7;
        level_3_flag = 1;
    }

    else if ((caracter.exp >= 20 && caracter.exp < 30) && level_4_flag == 0)
    {
        caracter.lv = 4;
        // �⺻ hp 5 / mp 3 / df 0 / atk 1
        caracter.hp = 8;
        caracter.mp = 6;
        caracter.df = 3;
        caracter.atk = 4;

        caracter.max_hp = 8;

        level_4_flag = 1;
    }
}

void print_text_ui(int key) // �ݺ��Ǵ� �Լ�
{
    switch (key)
    {
    case 1:
        if (flag2 == 0)
        {
            stop_move = 1;
            gotoxy(UILINE_X, UILINE_Y + 1);
            printf("������ �����մϴ�...[ctrl]");
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
    case 0: // �ƹ��͵� ����.
        gotoxy(40, 15);
        printf("����               ����");
        gotoxy(39, 16);
        printf("����                   ����");
        gotoxy(38, 17);
        printf("����                       ����");
        gotoxy(37, 18);
        printf("����                           ����");
        gotoxy(36, 19);
        printf("����                               ����");
        gotoxy(35, 20);
        printf("����                                   ����");
        gotoxy(34, 21);
        printf("����                                       ����");
        gotoxy(33, 22);
        printf("����                                           ����");
        break;

    case 1: // ������
        gotoxy(42, 8);
        printf("������������������������");
        gotoxy(42, 9);
        printf("��          ��");
        gotoxy(42, 10);
        printf("��          ��");
        gotoxy(42, 11);
        printf("��   �� ��  ��");
        gotoxy(42, 12);
        printf("��    ~~~   ��");
        gotoxy(42, 13);
        printf("������������������������");
        gotoxy(40, 15);
        printf("����               ����");
        gotoxy(39, 16);
        printf("����                   ����");
        gotoxy(38, 17);
        printf("����                       ����");
        gotoxy(37, 18);
        printf("����                           ����");
        gotoxy(36, 19);
        printf("����                               ����");
        gotoxy(35, 20);
        printf("����                                   ����");
        gotoxy(34, 21);
        printf("����                                       ����");
        gotoxy(33, 22);
        printf("����                                           ����");
        break;

    case 2: // ������ ����(����������)
        gotoxy(42, 8 + 3);
        printf("�ʿʿʿʿʿʿʿ�");
        gotoxy(42, 9 + 3);
        printf("  �ʿʿʿʿʿ�");
        gotoxy(42, 10 + 3);
        printf("    �ʿʿʿ�");
        gotoxy(42, 11 + 3);
        printf("      �ʿ�");

        gotoxy(40, 15);
        printf("����               ����");
        gotoxy(39, 16);
        printf("����                   ����");
        gotoxy(38, 17);
        printf("����                       ����");
        gotoxy(37, 18);
        printf("����                           ����");
        gotoxy(36, 19);
        printf("����                               ����");
        gotoxy(35, 20);
        printf("����                                   ����");
        gotoxy(34, 21);
        printf("����                                       ����");
        gotoxy(33, 22);
        printf("����                                           ����");
        break;

    case 3: // ���̷���
        gotoxy(42, 0);
        printf(" ��       ��");
        gotoxy(42, 1);
        printf("������������������������");
        gotoxy(42, 2);
        printf("��          ��");
        gotoxy(42, 3);
        printf("��  ����  ����  ��");
        gotoxy(42, 4);
        printf("��  ����  ����  ��");
        gotoxy(42, 5);
        printf("��  ����������");
        gotoxy(42, 6);
        printf("������������������������");
        gotoxy(45, 7);
        printf("��");
        gotoxy(43, 8);
        printf("������������������");
        gotoxy(43, 9);
        printf("��   ��   ��");
        gotoxy(43, 10);
        printf("��   ��   ��");
        gotoxy(43, 11);
        printf("��   ��   ��");
        gotoxy(43, 12);
        printf("��   ��   ��");
        gotoxy(43, 13);
        printf("��   ��   ��");
        gotoxy(44, 14);
        printf("��  ��");


        gotoxy(40, 15);
        printf("����   ��     ��   ����");
        gotoxy(39, 16);
        printf("����    ��        ��     ����");
        gotoxy(38, 17);
        printf("����      ��        ��       ����");
        gotoxy(37, 18);
        printf("����        ��        ��         ����");
        gotoxy(36, 19);
        printf("����          ��        ��           ����");
        gotoxy(35, 20);
        printf("����            ��        ��             ����");
        gotoxy(34, 21);
        printf("����           ___��        ��___            ����");
        gotoxy(33, 22);
        printf("����                                           ����");
        break;


    case 10: // �ⱸ
        gotoxy(41, 6);
        printf("������������������������������������");
gotoxy(41, 7);
printf("    ��->��  �ⱸ");
gotoxy(41, 8);
printf("������������������������������������");
gotoxy(41, 9);
printf("��                ��");
gotoxy(41, 10);
printf("��                ��");
gotoxy(41, 11);
printf("��                ��");
gotoxy(41, 12);
printf("��      _____     ��");
gotoxy(41, 13);
printf("��    _________   ��");
gotoxy(41, 14);
printf("��  _____________ ��");
gotoxy(40, 15);
printf("����               ����");
gotoxy(39, 16);
printf("����                   ����");
gotoxy(38, 17);
printf("����                       ����");
gotoxy(37, 18);
printf("����                           ����");
gotoxy(36, 19);
printf("����                               ����");
gotoxy(35, 20);
printf("����                                   ����");
gotoxy(34, 21);
printf("����                                       ����");
gotoxy(33, 22);
printf("����                                           ����");
break;

    case 11: // ����
        gotoxy(42, 8);
        printf("������������������������");
        gotoxy(42, 9);
        printf("��          ��");
        gotoxy(42, 10);
        printf("��          ��");
        gotoxy(42, 11);
        printf("����������������������");
        gotoxy(42, 12);
        printf("��          ��");
        gotoxy(42, 13);
        printf("������������������������");
        gotoxy(40, 15);
        printf("����               ����");
        gotoxy(39, 16);
        printf("����                   ����");
        gotoxy(38, 17);
        printf("����                       ����");
        gotoxy(37, 18);
        printf("����                           ����");
        gotoxy(36, 19);
        printf("����                               ����");
        gotoxy(35, 20);
        printf("����                                   ����");
        gotoxy(34, 21);
        printf("����                                       ����");
        gotoxy(33, 22);
        printf("����                                           ����");
        break;
    }
}

void print_map_ui()
// �ݺ��Ǵ� �Լ�
{
    gotoxy(0, 0);
    printf("[STAGE]: %d", stage_num);
    gotoxy(0, 1);
    printf("[HP]: %d", caracter.hp);
    gotoxy(0, 2);
    printf("[MP]: %d", caracter.mp);
    gotoxy(0, 3);
    printf("[LV]: %d", caracter.lv);


    gotoxy(UILINE_X, UILINE_Y);
    printf("========================================================================================================================");

    for (int i = 0; i < 23; i++)
    {
        gotoxy(29, i);
        printf("��");
    }

    gotoxy(caracter.x, caracter.y);
    printf("��");

    print_battle_ui(0); // <- �ݺ���

}

int is_full(Caracter* p) { //���ִ���
    return (p->playerInven.rear + 1) % MAX_INVEN_SIZE == p->playerInven.front;
}

void Move_caracter() //�÷��̾��� �������� ����ϴ� �Լ�
{
    node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].is_visited = 1;

    if (isKeyDown(VK_LEFT) && (caracter.x > 10)) //���࿡ ����Ű�� �����ٴ� ���� Ȯ���� �ȴٸ�
    {
        if (node[caracter.x - REAL_ADD_X - 1][caracter.y - REAL_ADD_Y].is_wall == 0)
        {
            if (stop_move != 1)
                caracter.x -= 1; //�÷��̾��� x���� 1 ����
        }
        system("cls");
        Sleep(30);
    }

    if (isKeyDown(VK_RIGHT) && (caracter.x <= 19)) //"������Ű
    {
        if (node[caracter.x - REAL_ADD_X + 1][caracter.y - REAL_ADD_Y].is_wall == 0) // ������
        {
            if (stop_move != 1)
                caracter.x += 1; //"x�� 1����
        }
        system("cls");
        Sleep(30);
    }

    if (isKeyDown(VK_UP) && (caracter.y >= 1))
    {
        if (node[caracter.x - REAL_ADD_X][caracter.y - 1 - REAL_ADD_Y].is_wall == 0) // ����
        {
            if (stop_move != 1)
                caracter.y -= 1;
        }
        system("cls");
        Sleep(30);
    }

    if (isKeyDown(VK_DOWN) && (caracter.y <= 19))
    {
        if (node[caracter.x - REAL_ADD_X][caracter.y + 1 - REAL_ADD_Y].is_wall == 0) // �Ʒ���
        {
            if (stop_move != 1)
                caracter.y += 1;
        }
        system("cls");
        Sleep(30);
    }
}

void map_node_init()
// �� ��� �ʱ�ȭ
{
    if (stage_num == 1) // ��������1�� �ʱ�ȭ
    {
        if (flag == 0) // �ѹ��� ����ǰ� �ؾ���.
        {
            for (int i = 0; i <= 9; i++)
                // �迭�� ��ġ�� ��� ��ǥ���� �����ϰ� ������ִ� �ݺ���
            {
                for (int j = 0; j <= 9; j++)
                {
                    node[i][j].x = REAL_ADD_X + i;
                    node[i][j].y = REAL_ADD_Y + j;
                    node[i][j].is_wall = 1; // ó������ ��� ������ ������ �ƴ϶�� �صѰ���
                    node[i][j].is_visited = 0;
                    node[i][j].is_item = 0;
                    node[i][j].is_monster = 0;
                    node[i][j].is_event = 0;
                }
            }
        }
        flag = 1;
    }

    if (stage_num == 2) //��������2�� �ʱ�ȭ
    {
        if (flagg == 0)
        {
            for (int i = 0; i <= 9; i++)
                // �迭�� ��ġ�� ��� ��ǥ���� �����ϰ� ������ִ� �ݺ���
            {
                for (int j = 0; j <= 9; j++)
                {
                    node[i][j].x = REAL_ADD_X + i;
                    node[i][j].y = REAL_ADD_Y + j;
                    node[i][j].is_wall = 1; // ó������ ��� ������ ������ �ƴ϶�� �صѰ���
                    node[i][j].is_visited = 0;
                    node[i][j].is_item = 0;
                    node[i][j].is_monster = 0;
                    node[i][j].is_event = 0;
                }
            }
            flag2 = 0;
            item_flag = 0;
            flag4 = 0;
            flag5 = 0;
            flag6 = 0;
            flag7 = 0;
            flag8 = 0;

            item_flag = 0;
            item_flag2 = 0;
            item_flag3 = 0;
            item_flag4 = 0;

            select_turn = 1;
            default_choose = 1;
            my_turn = 1;

            color_flag = 0;
            color_flag2 = 0;
            color_flag3 = 0;

            stage1_flag = 0;
            stage2_flag = 0;
            stage3_flag = 0;

            is_escape = 0;

            caracter.x = DEFAULT_CHARACTER_X;
            caracter.y = DEFAULT_CHARACTER_Y;

            slime.hp = 4;
            mini_army.hp = 8;

            caracter.hp = caracter.max_hp;
        }
        flagg = 1;
    }

    if (stage_num == 3) //��������3�� �ʱ�ȭ
    {
        if (flaggg == 0)
        {
            for (int i = 0; i <= 9; i++)
                // �迭�� ��ġ�� ��� ��ǥ���� �����ϰ� ������ִ� �ݺ���
            {
                for (int j = 0; j <= 9; j++)
                {
                    node[i][j].x = REAL_ADD_X + i;
                    node[i][j].y = REAL_ADD_Y + j;
                    node[i][j].is_wall = 1; // ó������ ��� ������ ������ �ƴ϶�� �صѰ���
                    node[i][j].is_visited = 0;
                    node[i][j].is_item = 0;
                    node[i][j].is_monster = 0;
                    node[i][j].is_event = 0;
                }
            }

            flag2 = 0;
            item_flag = 0;
            flag4 = 0;
            flag5 = 0;
            flag6 = 0;
            flag7 = 0;
            flag8 = 0;

            item_flag = 0;
            item_flag2 = 0;
            item_flag3 = 0;
            item_flag4 = 0;

            select_turn = 1;
            default_choose = 1;
            my_turn = 1;

            color_flag = 0;
            color_flag2 = 0;
            color_flag3 = 0;

            stage1_flag = 0;
            stage2_flag = 0;
            stage3_flag = 0;

            is_escape = 0;

            caracter.x = DEFAULT_CHARACTER_X;
            caracter.y = DEFAULT_CHARACTER_Y;

            slime.hp = 4;
            mini_army.hp = 8;

            caracter.hp = caracter.max_hp;

        }
        flaggg = 1;
    }


}

void check_arround_node()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (node[i][j].is_visited == 1 && !((node[i][j].x == caracter.x) && (node[i][j].y == caracter.y)))
            {
                gotoxy(node[i][j].x, node[i][j].y);
                printf("��");
            }
        }
    }

    if ((caracter.x <= 28 && caracter.x >= 10) && ((caracter.y >= 6) && (caracter.y <= 14)))
    {
        if (node[caracter.x - REAL_ADD_X + 1][caracter.y - REAL_ADD_Y].is_wall == 0) // ������
        {
            gotoxy(caracter.x + 1, caracter.y);
            printf("��");
        }

        if (node[caracter.x - REAL_ADD_X - 1][caracter.y - REAL_ADD_Y].is_wall == 0) // ����
        {
            if (!(caracter.x == node[0][5].x + 10 && caracter.y == node[0][6].y + 5))
            {
                gotoxy(caracter.x - 1, caracter.y);
                printf("��");
            }
        }

        if (node[caracter.x - REAL_ADD_X][caracter.y + 1 - REAL_ADD_Y].is_wall == 0) // ����
        {
            gotoxy(caracter.x, caracter.y + 1);
            printf("��");
        }

        if (node[caracter.x - REAL_ADD_X][caracter.y - 1 - REAL_ADD_Y].is_wall == 0) // �Ʒ���
        {
            gotoxy(caracter.x, caracter.y - 1);
            printf("��");
        }
    }
}

void drop_item(int key)
{
    switch (key)
    {
    case 1: // ������ ��

        while (item_flag == 0)
        {
            print_battle_ui(11);
            stop_move = 1;

            if (is_full(&caracter))
            {
                gotoxy(UILINE_X, UILINE_Y + 1);
                printf("�κ��丮�� ���� á���ϴ�.");

                if (is_stack == 1) // �����̸�
                {
                    gotoxy(UILINE_X, UILINE_Y + 2);
                    printf("%s(��)�� ������ϴ�.", caracter.playerInven.arr[caracter.playerInven.rear]);
                }

                else if (is_stack == 0) // ť��
                {
                    gotoxy(UILINE_X, UILINE_Y + 2);
                    printf("%s(��)�� ������ϴ�.", caracter.playerInven.arr[(caracter.playerInven.front + 1) % MAX_INVEN_SIZE]);
                }
                gotoxy(UILINE_X, UILINE_Y + 3);
                printf("���� �ȿ��� [������ ��]�� ȹ���Ͽ����ϴ�...");
                gotoxy(UILINE_X, UILINE_Y + 4);
                printf("���ݷ� 1 ����...[ctrl]");
            }

            else
            {
                gotoxy(UILINE_X, UILINE_Y + 1);
                printf("����� ���ڸ� �߰��߽��ϴ�...");
                gotoxy(UILINE_X, UILINE_Y + 2);
                printf("���� �ȿ��� [������ ��]�� ȹ���Ͽ����ϴ�...");
                gotoxy(UILINE_X, UILINE_Y + 3);
                printf("���ݷ� 1 ����...[ctrl]");
            }

            if (isKeyDown(VK_CONTROL))
            {
                stop_move = 0;
                item_flag = 1;
                if (is_full(&caracter))
                {
                    delete_nene(&caracter);
                }
                add_rear(&caracter, &i1);
                system("cls");
                Sleep(30);
            }
        }
        break;

    case 2: // ������ ����

        while (item_flag2 == 0)
        {
            print_battle_ui(11);
            stop_move = 1;

            if (is_full(&caracter))
            {
                gotoxy(UILINE_X, UILINE_Y + 1);
                printf("�κ��丮�� ���� á���ϴ�.");

                if (is_stack == 1) // �����̸�
                {
                    gotoxy(UILINE_X, UILINE_Y + 2);
                    printf("%s(��)�� ������ϴ�.", caracter.playerInven.arr[caracter.playerInven.rear]);
                }

                else if (is_stack == 0) // ť��
                {
                    gotoxy(UILINE_X, UILINE_Y + 2);
                    printf("%s(��)�� ������ϴ�.", caracter.playerInven.arr[(caracter.playerInven.front + 1) % MAX_INVEN_SIZE]);
                }

                gotoxy(UILINE_X, UILINE_Y + 3);
                printf("���� �ȿ��� [������ ����]�� ȹ���Ͽ����ϴ�...");
                gotoxy(UILINE_X, UILINE_Y + 4);
                printf("���� 1 ����...[ctrl]");
            }

            else
            {
                gotoxy(UILINE_X, UILINE_Y + 1);
                printf("����� ���ڸ� �߰��߽��ϴ�...");
                gotoxy(UILINE_X, UILINE_Y + 2);
                printf("���� �ȿ��� [������ ����]�� ȹ���Ͽ����ϴ�...");
                gotoxy(UILINE_X, UILINE_Y + 3);
                printf("���� 1 ����...[ctrl]");
            }

            if (isKeyDown(VK_CONTROL))
            {
                stop_move = 0;
                item_flag2 = 1;
                if (is_full(&caracter))
                {
                    delete_nene(&caracter);
                }
                add_rear(&caracter, &i2);
                system("cls");
                Sleep(30);
            }
        }
        break;

    case 3: // ��ȭ�� ���� ��Ʈ

        while (item_flag3 == 0)
        {
            print_battle_ui(11);
            stop_move = 1;

            if (is_full(&caracter))
            {
                gotoxy(UILINE_X, UILINE_Y + 1);
                printf("�κ��丮�� ���� á���ϴ�.");

                if (is_stack == 1) // �����̸�
                {
                    gotoxy(UILINE_X, UILINE_Y + 2);
                    printf("%s(��)�� ������ϴ�.", caracter.playerInven.arr[caracter.playerInven.rear]);
                }

                else if (is_stack == 0) // ť��
                {
                    gotoxy(UILINE_X, UILINE_Y + 2);
                    printf("%s(��)�� ������ϴ�.", caracter.playerInven.arr[(caracter.playerInven.front + 1) % MAX_INVEN_SIZE]);
                }
                gotoxy(UILINE_X, UILINE_Y + 3);
                printf("���� �ȿ��� [��ȭ�� ���� ��Ʈ]�� ȹ���Ͽ����ϴ�...");
                gotoxy(UILINE_X, UILINE_Y + 4);
                printf("���ݷ� 2 / ���� 2 ����...[ctrl]");
            }

            else
            {
                gotoxy(UILINE_X, UILINE_Y + 1);
                printf("����� ���ڸ� �߰��߽��ϴ�...");
                gotoxy(UILINE_X, UILINE_Y + 2);
                printf("���� �ȿ��� [��ȭ�� ���� ��Ʈ]�� ȹ���Ͽ����ϴ�...");
                gotoxy(UILINE_X, UILINE_Y + 3);
                printf("���ݷ� 2 / ���� 2 ����...[ctrl]");
            }

            if (isKeyDown(VK_CONTROL))
            {
                stop_move = 0;
                item_flag3 = 1;
                if (is_full(&caracter))
                {
                    delete_nene(&caracter);
                }
                add_rear(&caracter, &i3);
                system("cls");
                Sleep(30);
            }
        }
        break;

    case 4: // �������� ��

        while (item_flag4 == 0)
        {
            print_battle_ui(11);
            stop_move = 1;

            if (is_full(&caracter))
            {
                gotoxy(UILINE_X, UILINE_Y + 1);
                printf("�κ��丮�� ���� á���ϴ�.");

                if (is_stack == 1) // �����̸�
                {
                    gotoxy(UILINE_X, UILINE_Y + 2);
                    printf("%s(��)�� ������ϴ�.", caracter.playerInven.arr[caracter.playerInven.rear]);
                }

                else if (is_stack == 0) // ť��
                {
                    gotoxy(UILINE_X, UILINE_Y + 2);
                    printf("%s(��)�� ������ϴ�.", caracter.playerInven.arr[(caracter.playerInven.front + 1) % MAX_INVEN_SIZE]);
                }
                gotoxy(UILINE_X, UILINE_Y + 3);
                printf("���� �ȿ��� [�������� ��]�� ȹ���Ͽ����ϴ�...");
                gotoxy(UILINE_X, UILINE_Y + 4);
                printf("���ݷ� 4 / ü�� 4 ����...[ctrl]");
            }

            else
            {
                gotoxy(UILINE_X, UILINE_Y + 1);
                printf("����� ���ڸ� �߰��߽��ϴ�...");
                gotoxy(UILINE_X, UILINE_Y + 2);
                printf("���� �ȿ��� [�������� ��]�� ȹ���Ͽ����ϴ�...");
                gotoxy(UILINE_X, UILINE_Y + 3);
                printf("���ݷ� 4 / ü�� 4 ����...[ctrl]");
            }

            if (isKeyDown(VK_CONTROL))
            {
                stop_move = 0;
                item_flag4 = 1;
                if (is_full(&caracter))
                {
                    delete_nene(&caracter);
                }
                add_rear(&caracter, &i4);
                system("cls");
                Sleep(30);
            }
        }
        break;
    }
}

void battle_control(monster* monster) // �ݺ��Ǵ� �Լ� �ȿ� �ִ� �Լ�
{
    char temp[50] = { '\0' };
    char temp2[20] = { '\0' };

    gotoxy(55, 3);
    printf("[HP: %d]", monster->hp);

    if (my_turn == 1) // ���� ���϶�
    {
        if (select_turn)
        {
            gotoxy(5, UILINE_Y + default_choose);
            printf("��");
        }

        if (isKeyDown(VK_CONTROL) && select_turn == 1) // ����â���� ��Ʈ��Ű�� ��������
        {
            select_turn = 0;

            switch (default_choose)
            {
            case 1: // ����
                monster->hp = monster->hp - (caracter.atk - monster->df);
                system("cls");
                Sleep(30);

                strcpy(temp, monster->name); // �� �̸�
                strcat(temp, "���� ");

                _itoa((caracter.atk - monster->df), temp2, 10);
                strcat(temp2, "�� ���ظ� �־���.");

                strcat(temp, temp2);

                gotoxy(UILINE_X, UILINE_Y + 1);
                printf("%s", temp);
                break;

            case 2: //��ų
                if ((strstr(caracter.job, "�⺻")) != NULL)
                {
                    if (caracter.mp > 0) // mp�� 0 �̻��̾����
                    {
                        monster->hp = monster->hp - (caracter.atk + skill_damage - monster->df);
                        caracter.mp -= 1;
                        system("cls");
                        Sleep(30);

                        strcpy(temp, monster->name); // �� �̸�
                        strcat(temp, "���� ");

                        _itoa((caracter.atk + skill_damage - monster->df), temp2, 10);
                        strcat(temp2, "�� ���ظ� �־���.");

                        strcat(temp, temp2);

                        gotoxy(UILINE_X, UILINE_Y + 1);
                        printf("%s", temp);
                    }
                }
                break;


            case 3: // ���
                system("cls");
                Sleep(30);

                gotoxy(UILINE_X, UILINE_Y + 1);
                printf("���� ���ݿ� ����� ����� �ڼ��� ���Ѵ�!");

                caracter.df += caracter.lv;
                is_deffence = 1;

                break;
            }
        }

        else if ((isKeyDown(VK_CONTROL) && select_turn == 0)) // ����â�� �ƴҶ� ��Ʈ��Ű�� �����ٸ� (~�� �����ߴ� or ����ߴ� ��..)
        {
            my_turn = 0;
            system("cls");
        }

        if (isKeyDown(VK_DOWN) && default_choose < 3)
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

    else if (my_turn == 0) // ���� ���϶�
    {
        char temp3[20] = { '\0' };

        strcpy(messege, monster->name);
        strcat(messege, "�� ����! ���ظ� ");

        if (caracter.df >= monster->atk)
        {
            _itoa(0, temp3, 10);
        }

        else
        {
            _itoa((monster->atk - caracter.df), temp3, 10);
        }

        strcat(messege, temp3);
        strcat(messege, "�޾Ҵ�.");

        gotoxy(UILINE_X, UILINE_Y + 1);
        printf("%s", messege);

        if (isKeyDown(VK_CONTROL) && select_turn == 0) // ����â�� �ƴҶ� ��Ʈ��Ű�� �����ٸ� , ������ �ƴ϶��
        {
            my_turn = 1;
            select_turn = 1;

            if (caracter.df >= monster->atk)
            {
                caracter.hp - 0;
            }

            else
            {
                caracter.hp -= monster->atk - caracter.df;
            }

            if (caracter.df > 0 && is_deffence == 1)
            {
                caracter.df -= caracter.lv;
                is_deffence = 0;
            }
            system("cls");
        }
    }
}

void battle_monster(int key) // �ݺ��Ǵ� �Լ� �ȿ� �ִ� �Լ�
{
    switch (key)
    {
    case 1:
        print_battle_ui(1);

        while (flag4 == 0)
        {
            stop_move = 1;
            gotoxy(UILINE_X, UILINE_Y + 1);
            printf("[������]�� ����� �����ؿԴ�!!...[ctrl]");

            if (color_flag == 0)
            {
                system("COLOR f0");
                Sleep(30);
                system("COLOR 0f");
                Sleep(30);
                system("COLOR f0");
                Sleep(30);
                system("COLOR 0f");
                color_flag = 1;
            }

            if (isKeyDown(VK_CONTROL))
            {
                system("COLOR 0f");
                flag4 = 1;
                system("cls");
                Sleep(30);
            }
        }

        if (slime.hp > 0)
        {
            stop_move = 1;

            if (select_turn == 1 && my_turn == 1) // ����â ������ True�϶�, �����϶�
            {
                gotoxy(UILINE_X, UILINE_Y + 1);
                printf("[����]");

                gotoxy(UILINE_X, UILINE_Y + 2);
                printf("[��ų]");

                gotoxy(UILINE_X, UILINE_Y + 3);
                printf("[���]");
            }
            battle_control(&slime);
        }

        if (slime.hp <= 0)
        {
            node[4][5].is_monster = 0;
            node[2][2].is_monster = 0;
            node[4][7].is_monster = 0;
            gotoxy(UILINE_X, UILINE_Y + 2);
            printf("�������� �����ƴ�!");
            my_turn = 1;
            select_turn = 1;
            caracter.exp += 5;
        }

        break;

    case 2:
        print_battle_ui(2);

        while (flag5 == 0)
        {
            stop_move = 1;
            gotoxy(UILINE_X, UILINE_Y + 1);
            printf("[����������]�� ����� �����ؿԴ�!!...[ctrl]");

            if (color_flag2 == 0)
            {
                system("COLOR f0");
                Sleep(30);
                system("COLOR 0f");
                Sleep(30);
                system("COLOR f0");
                Sleep(30);
                system("COLOR 0f");
                color_flag2 = 1;
            }

            if (isKeyDown(VK_CONTROL))
            {
                system("COLOR 0f");
                flag5 = 1;
                system("cls");
                Sleep(30);
            }
        }

        if (mini_army.hp > 0)
        {
            stop_move = 1;

            if (select_turn == 1 && my_turn == 1) // ����â ������ True�϶�, �����϶�
            {
                gotoxy(UILINE_X, UILINE_Y + 1);
                printf("[����]");

                gotoxy(UILINE_X, UILINE_Y + 2);
                printf("[��ų]");

                gotoxy(UILINE_X, UILINE_Y + 3);
                printf("[���]");
            }
            battle_control(&mini_army);
        }

        if (mini_army.hp <= 0)
        {
            node[6][3].is_monster = 0;
            node[6][7].is_monster = 0;
            gotoxy(UILINE_X, UILINE_Y + 2);
            printf("������ ������ �����ƴ�!");
            my_turn = 1;
            select_turn = 1;
            caracter.exp += 10;
        }

        break;

    case 3:
        print_battle_ui(3);

        while (flag6 == 0)
        {
            stop_move = 1;
            gotoxy(UILINE_X, UILINE_Y + 1);
            printf("[����]�� ����� �����ؿԴ�!!...[ctrl]");

            if (color_flag3 == 0)
            {
                system("COLOR f0");
                Sleep(30);
                system("COLOR 0f");
                Sleep(30);
                system("COLOR f0");
                Sleep(30);
                system("COLOR 0f");
                color_flag3 = 1;
            }

            if (isKeyDown(VK_CONTROL))
            {
                system("COLOR 0f");
                flag6 = 1;
                system("cls");
                Sleep(30);
            }
        }

        if (skeleton.hp > 0)
        {
            stop_move = 1;

            if (select_turn == 1 && my_turn == 1) // ����â ������ True�϶�, �����϶�
            {
                gotoxy(UILINE_X, UILINE_Y + 1);
                printf("[����]");

                gotoxy(UILINE_X, UILINE_Y + 2);
                printf("[��ų]");

                gotoxy(UILINE_X, UILINE_Y + 3);
                printf("[���]");
            }
            battle_control(&skeleton);
        }

        if (skeleton.hp <= 0)
        {
            node[8][5].is_monster = 0;
            gotoxy(UILINE_X, UILINE_Y + 2);
            printf("������ �����ƴ�!");
            my_turn = 1;
            select_turn = 1;
            caracter.exp += 15;
        }

        break;
    }
}

void event_control(int key)
{
    if (select_turn == 1)
    {
        gotoxy(10, UILINE_Y + default_choose);
        printf("��");
    }

    switch (key)
    {
    case 1:
        if (isKeyDown(VK_CONTROL) && select_turn == 1)
        {
            switch (default_choose)
            {
            case 1:
                system("cls");
                Sleep(30);

                select_turn = 0;

                gotoxy(UILINE_X, UILINE_Y + 1);
                printf("���� Ŭ����!");
                gotoxy(UILINE_X, UILINE_Y + 2);
                printf("�������� 100G�� �����!");
                is_escape = 1;
                break;

            case 2:
                select_turn = 0;
                stop_move = 0;
                default_choose = 1;
                select_turn = 1;
                break;
            }
        }

        if (isKeyDown(VK_DOWN) && default_choose < 2)
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
}

void event_manage(int key) // �ݺ��Ǵ� �Լ�
{
    switch (key)
    {
    case 1:
        print_battle_ui(10);

        while (flag5 == 0) // �ⱸ �߰� �̺�Ʈ
        {
            stop_move = 1;
            gotoxy(UILINE_X, UILINE_Y + 1);
            printf("����� �ⱸ�� �߰��Ͽ����ϴ�.");

            if (isKeyDown(VK_CONTROL))
            {
                flag5 = 1;
                system("cls");
                Sleep(30);
            }

            default_choose = 1;
            select_turn = 1;
        }

        if (select_turn == 1)
        {
            gotoxy(UILINE_X, UILINE_Y + 1);
            printf("[Ż���Ѵ�]");

            gotoxy(UILINE_X, UILINE_Y + 2);
            printf("[Ż������ �ʴ´�]");
        }

        event_control(key);

        if (isKeyDown(VK_CONTROL) && is_escape == 1)
        {
            if (stage_num == 3)
            {
                is_clear = 1;
            }
            sceneCounter = 2;
            Sleep(100);
            system("cls");
            running = 0;
        }
    }
}

void stage1() // �ݺ��Ǵ� �Լ�
{
    map_node_init();

    if (stage1_flag == 0)
    {
        node[0][5].is_wall = 0;

        node[1][5].is_wall = 0;

        node[2][5].is_wall = 0;
        node[2][5].is_item = 1; // ������ ��

        node[3][5].is_wall = 0;
        node[3][5].is_item = 1;

        node[4][5].is_wall = 0;
        node[4][5].is_monster = 1;

        node[5][5].is_wall = 0;
        node[5][5].is_event = 1;

        stage1_flag = 1;
    }

    print_text_ui(1); // <- �ݺ���

    if (node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].is_item == 1) // ���� �湮�� ��尡 �������� ����ϴ� ������� �˻��ϴ� �Լ�
    {
        if ((node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].x == 13) && (node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].y == 10)) // 15.9 ������ ����
        {
            drop_item(2);
        }

        else if ((node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].x == 12) && (node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].y == 10)) // 12,11 ��������
        {
            drop_item(1);
        }
    }

    if (node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].is_monster == 1) // ���� �湮�� ��尡 ���Ϳ� �ο�� ������� �˻��ϴ� �Լ�
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

void stage2()
{
    map_node_init();

    if (stage2_flag == 0)
    {
        node[0][5].is_wall = 0;

        node[1][5].is_wall = 0;

        node[2][5].is_wall = 0;

        node[3][5].is_wall = 0;

        node[4][5].is_wall = 0;

        node[5][5].is_wall = 0;

        node[5][4].is_wall = 0; // ������ ���
        node[5][4].is_item = 1; // ������ ����

        node[2][6].is_wall = 0; // ������ ���
        node[2][6].is_item = 1; // ������ ��

        node[2][7].is_wall = 0;

        node[3][7].is_wall = 0;

        node[4][7].is_wall = 0; // ���⿡ ���� ������.
        node[4][7].is_monster = 1;

        node[5][7].is_wall = 0;

        node[5][8].is_wall = 0; // ������ ���
        node[5][8].is_item = 1; // ��ȭ�� ��Ʈ

        node[6][7].is_wall = 0; // ���⿡ ���� ������.
        node[6][7].is_monster = 1;

        node[7][7].is_wall = 0; // ���� �ⱸ
        node[7][7].is_event = 1;

        stage2_flag = 1;
    }

    print_text_ui(1); // <- �ݺ���

    if (node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].is_item == 1) // ���� �湮�� ��尡 �������� ����ϴ� ������� �˻��ϴ� �Լ�
    {
        if ((node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].x == 15) && (node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].y == 9)) // 15.9 ������ ����
        {
            drop_item(2);
        }

        else if ((node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].x == 12) && (node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].y == 11)) // 12,11 ��������
        {
            drop_item(1);
        }

        else if ((node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].x == 15) && (node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].y == 13)) // 15,13 �����
        {
            drop_item(4);
        }
    }

    if (node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].is_monster == 1) // ���� �湮�� ��尡 ���Ϳ� �ο�� ������� �˻��ϴ� �Լ�
    {

        if ((node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].x == 14) && (node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].y == 12)) // 4,7�̸�
        {
            battle_monster(1);
        }

        else if ((node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].x == 16) && (node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].y == 12)) // 4,7�̸�
        {
            battle_monster(2);
        }
    }

    if (node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].is_event == 1)
    {
        event_manage(1);
    }

    Move_caracter();
    check_arround_node();
}

void stage3()
{
    map_node_init();

    if (stage3_flag == 0)
    {
        node[0][5].is_wall = 0;

        node[1][5].is_wall = 0;

        node[2][5].is_wall = 0;

        node[2][4].is_wall = 0;

        node[2][3].is_wall = 0;

        node[2][2].is_wall = 0; // ���� ����(������)
        node[2][2].is_monster = 1;

        node[1][2].is_wall = 0;

        node[3][2].is_wall = 0;

        node[3][1].is_wall = 0;

        node[4][1].is_wall = 0;

        node[5][1].is_wall = 0; // ���� ������ ���Ѱ���
        node[5][1].is_item = 1;

        node[3][5].is_wall = 0;

        node[4][5].is_wall = 0;

        node[5][5].is_wall = 0;

        node[5][3].is_wall = 0;

        node[6][3].is_wall = 0; // ���� ����(������)
        node[6][3].is_monster = 1;

        node[7][3].is_wall = 0;

        node[7][2].is_wall = 0;

        node[8][2].is_wall = 0;

        node[8][1].is_wall = 0; // ���� ������ ���Ѱ���.
        node[8][1].is_item = 1;

        node[5][4].is_wall = 0;

        node[2][6].is_wall = 0;

        node[2][7].is_wall = 0;

        node[3][7].is_wall = 0;

        node[4][7].is_wall = 0;

        node[5][7].is_wall = 0;

        node[5][8].is_wall = 0; // ���� ������ ���Ѱ���.
        node[5][8].is_item = 1;

        node[6][7].is_wall = 0;

        node[7][7].is_wall = 0;

        node[8][7].is_wall = 0;

        node[8][8].is_wall = 0;

        node[8][6].is_wall = 0;

        node[8][5].is_wall = 0; // ���� ������ �������.
        node[8][5].is_monster = 1;

        node[7][5].is_wall = 0; // ���� �ⱸ.
        node[7][5].is_event = 1;

        stage3_flag = 1;
    }

    print_text_ui(1); // <- �ݺ���

    if (node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].is_item == 1) // ���� �湮�� ��尡 �������� ����ϴ� ������� �˻��ϴ� �Լ�
    {
        if ((node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].x == 15) && (node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].y == 6)) // 15.6 ������ ��
        {
            drop_item(1);
        }

        else if ((node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].x == 18) && (node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].y == 6)) // 18,6 ��ȭ�� ��Ʈ
        {
            drop_item(2);
        }

        else if ((node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].x == 15) && (node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].y == 13)) // 15,13 ���� ����
        {
            drop_item(1);
        }
    }

    if (node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].is_monster == 1) // ���� �湮�� ��尡 ���Ϳ� �ο�� ������� �˻��ϴ� �Լ�
    {
        if ((node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].x == 12) && (node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].y == 7)) // 2,2�̸�
        {
            battle_monster(1);
        }

        else if ((node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].x == 16) && (node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].y == 8)) // 6,3�̸�
        {
            battle_monster(2);
        }

        else if ((node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].x == 18) && (node[caracter.x - REAL_ADD_X][caracter.y - REAL_ADD_Y].y == 10)) // 8,5�̸�
        {
            battle_monster(3);
        }
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
    system("cls");
    CursorView(0);

    while (caracter.hp > 0 && running == 1)
    {
        if (stage_num == 1)
        {
            stage1();
        }

        else if (stage_num == 2)
        {
            stage2();
        }

        else if (stage_num == 3)
        {
            stage3();
        }

        exp_checking();
        print_map_ui();
    }

    if (caracter.hp <= 0)
    {
        system("cls");
        gotoxy(0, 0);
        printf("���ӿ���\n");
        system("pause");
    }

    if (is_clear == 1)
    {
        system("cls");
        gotoxy(0, 0);
        printf("������ ���������� �κ��丮�� ���ִ� Ǯ���� �ʾҴ�...");
        gotoxy(0, 1);
        printf("�Ƹ� ������ ���Ŀ� ������ ���ִ°� ����...");
        gotoxy(0, 2);
        printf("[GAME CLEAR]");
        system("pause");
    }
}