#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "Dungeon.h"

#define MAX_INVEN_SIZE 7 

int sceneCounter = 0; //0은 초기 시작 화면
int maxScene = 8;

int select_input();

void gotoxy(int x, int y);

typedef struct itemStruct { ///아이템 구조체
    double hpIncrement;
    double damageIncrement;
    double armorIncrement;
    double criPerIncrement;
    char itemName[100];
    int itemCode;
} itemStruct;
itemStruct i1 = { 1,1,1,1,"아이템1",0 }; ///아이템 4개 정의
itemStruct i2 = { 2,2,2,2,"아이템2",1 };
itemStruct i3 = { 3,3,3,3,"아이템3",2 };
itemStruct i4 = { 4,4,4,4,"아이템4",3 };
double increment[4];

typedef struct inventory { ///인벤토리 구조채
    char* arr[7];  //원형덱이라서 +1
    int rear;
    int front;
    int invenCode[7]; //아이템 삭제 시 능력치를 어떻게 반환해야 할 지에 대한 인덱스
} inventory;

typedef struct playerStats { ///플레이어 스텟
    double playerHp;
    double playerDamage;
    double playerArmor;
    double playerCriPer;
    struct inventory playerInven;
} playerStats;

playerStats p1 = { 100,10,10,0,{" ", " ", " ", " ", " ", " ", " "} }; ///플레이어 스텟 정의. hp, atk, df, crt, pla

int is_empty(playerStats* p) { ///비어있는지
    return p->playerInven.rear == p->playerInven.front;
}

int is_full(playerStats* p) { //차있는지
    return (p->playerInven.rear + 1) % MAX_INVEN_SIZE == p->playerInven.front;
}

int is_stack = 1; ///1이면 인벤토리는 스텍으로 인식

void add_front(playerStats* p, itemStruct* i) { ///스텍이나 큐 구조라서 사실상 사용되지 않음
    if (is_full(p)) {
        printf("인벤토리가 가득 찼습니다.\n");
        return;
    }
    if ((p->playerInven.rear == p->playerInven.front) && (p->playerInven.rear != 0)) {
        p->playerInven.rear = 0;
        p->playerInven.front = 0;
    }
    p->playerHp += i->hpIncrement;
    p->playerDamage += i->damageIncrement;
    p->playerArmor += i->armorIncrement;
    p->playerCriPer += i->criPerIncrement;
    p->playerInven.arr[p->playerInven.front] = i->itemName;
    p->playerInven.invenCode[p->playerInven.front] = i->itemCode;
    p->playerInven.front = (p->playerInven.front - 1 + MAX_INVEN_SIZE) % MAX_INVEN_SIZE;
}

void add_rear(playerStats* p, itemStruct* i) { ///스텍이나 큐에서 push와 enqueue로 사용
    if (is_full(p)) {
        printf("인벤토리가 가득 찼습니다.\n");
        return;
    }
    if (p->playerInven.rear == p->playerInven.front != 0) {
        p->playerInven.rear = 0;
        p->playerInven.front = 0;
    }
    p->playerHp += i->hpIncrement;
    p->playerDamage += i->damageIncrement;
    p->playerArmor += i->armorIncrement;
    p->playerCriPer += i->criPerIncrement;
    p->playerInven.rear = (p->playerInven.rear + 1) % MAX_INVEN_SIZE;
    p->playerInven.arr[p->playerInven.rear] = i->itemName;
    p->playerInven.invenCode[p->playerInven.rear] = i->itemCode;
}

void codeMatching_rear(playerStats* p) {
    if (p->playerInven.invenCode[p->playerInven.rear] == 0) {
        increment[0] = 1;
        increment[1] = 1;
        increment[2] = 1;
        increment[3] = 1;
    }
    else if (p->playerInven.invenCode[p->playerInven.rear] == 1) {
        increment[0] = 2;
        increment[1] = 2;
        increment[2] = 2;
        increment[3] = 2;
    }
    else if (p->playerInven.invenCode[p->playerInven.rear] == 2) {
        increment[0] = 3;
        increment[1] = 3;
        increment[2] = 3;
        increment[3] = 3;
    }
    else if (p->playerInven.invenCode[p->playerInven.rear] == 3) {
        increment[0] = 4;
        increment[1] = 4;
        increment[2] = 4;
        increment[3] = 4;
    }
    //아이템 개수에 따른 분기문 작성
}

void codeMatching_front(playerStats* p) {
    if (p->playerInven.invenCode[p->playerInven.front + 1] == 0) {
        increment[0] = 1;
        increment[1] = 1;
        increment[2] = 1;
        increment[3] = 1;
    }
    else if (p->playerInven.invenCode[p->playerInven.front + 1] == 1) {
        increment[0] = 2;
        increment[1] = 2;
        increment[2] = 2;
        increment[3] = 2;
    }
    else if (p->playerInven.invenCode[p->playerInven.front + 1] == 2) {
        increment[0] = 3;
        increment[1] = 3;
        increment[2] = 3;
        increment[3] = 3;
    }
    else if (p->playerInven.invenCode[p->playerInven.front + 1] == 3) {
        increment[0] = 4;
        increment[1] = 4;
        increment[2] = 4;
        increment[3] = 4;
    }
    //아이템 개수에 따른 분기문 작성
}

void delete_rear(playerStats* p) { ///스텍에서 pop으로 사용
    if (is_stack != 1) {
        printf("큐 인벤토리이므로 사용 불가\n");
        return;
    }
    if (is_empty(p)) {
        printf("인벤토리가 비었습니다.\n");
        return;
    }
    codeMatching_rear(p); ///실행되면 increment가 삭제되는 아이템이 증가시키는 스텟이 되어 해당 수치만큼 플레이어 스텟에서 제거
    int prev = p->playerInven.rear;
    p->playerHp -= increment[0];
    p->playerDamage -= increment[1];
    p->playerArmor -= increment[2];
    p->playerCriPer -= increment[3];
    p->playerInven.rear = (p->playerInven.rear - 1 + MAX_INVEN_SIZE) % MAX_INVEN_SIZE;
    p->playerInven.arr[prev] = "";
}

void delete_front(playerStats* p) { ///큐에서 dequeue로 사용
    if (is_stack == 1) {
        printf("스택 인벤토리이므로 사용 불가\n");
        return;
    }
    if (is_empty(p)) {
        printf("인벤토리가 비었습니다.\n");
        return;
    }
    codeMatching_front(p);
    p->playerHp -= increment[0];
    p->playerDamage -= increment[1];
    p->playerArmor -= increment[2];
    p->playerCriPer -= increment[3];
    p->playerInven.front = (p->playerInven.front + 1) % MAX_INVEN_SIZE;
    p->playerInven.arr[p->playerInven.front] = " ";
}

void start_scene() //0
{
    int keyInput = 0;

    system("cls");

    gotoxy(10, 3);
    printf("'그' 게임");
    gotoxy(14, 8);
    printf("시작하려면 엔터를-");

    while (1)
    {
        if (kbhit()) //키 입력
        {
            keyInput = getch();

            if (keyInput == 13) //엔터, 실행
            {
                sceneCounter = 1;
                return;
            }
            break;
        }
    }
}

typedef struct storyScript {
    char script[100];
}storyScript;

void story_scene() //1
{
    int keyInput = 0;
    int storyCounter = 0;
    storyScript script[5];

    strcpy(script[0].script, "첫번쨰 스크립트");
    strcpy(script[1].script, "두번쨰 스크립트");
    strcpy(script[2].script, "세번쨰 스크립트");
    strcpy(script[3].script, "네번쨰 스크립트");
    strcpy(script[4].script, "다섯번쨰 스크립트");

    while (1)
    {
        system("cls");

        gotoxy(10, 3);
        printf("%s", script[storyCounter].script);
        gotoxy(18, 8);
        if (storyCounter == 4)
            printf("마을로 가기 위해 엔터...");
        else
            printf("계속하기 위해 엔터...");

        while (1)
        {
            if (kbhit()) //키 입력
            {
                keyInput = getch();

                if (keyInput == 13) //엔터, 실행
                {
                    storyCounter++;

                    if (storyCounter == 5)
                    {
                        sceneCounter = 2;
                        return;
                    }
                }
                break;
            }
        }
    }

}

typedef struct iconUI { //각 UI 식별코드 및 방향키 입력 시 이동할 주소 내장
    int iconCode; //0은 아이템, 1은 선택 UI
    int itemCode; //아이템이면 종류
    struct iconUI* leftLink; //상하좌우 주소
    struct iconUI* rightLink;
    struct iconUI* topLink;
    struct iconUI* bottomLink;
}iconUI;

iconUI* swichingBold(iconUI* bold, int direction)//해당 방향으로 볼드 아이콘 주소 옮기기
{
    switch (direction)
    {
    case 0://상
    {
        if (bold->topLink != NULL)
            bold = bold->topLink;
        break;
    }
    case 1://하
    {
        if (bold->bottomLink != NULL)
            bold = bold->bottomLink;
        break;
    }
    case 2://좌
    {
        if (bold->leftLink != NULL)
            bold = bold->leftLink;
        break;
    }
    case 3://우
    {
        if (bold->rightLink != NULL)
            bold = bold->rightLink;
        break;
    }
    }
    return bold;
}

void village_scene() //2
{
    int keyInput = 0; //키입력 저장
    int anchorX = 4; //gotoxy 시작할 좌표 초기화용
    int anchorY = 2;

    iconUI* boldIcon = (iconUI*)malloc(sizeof(iconUI));
    iconUI* storeIcon = (iconUI*)malloc(sizeof(iconUI));
    iconUI* statusIcon = (iconUI*)malloc(sizeof(iconUI));
    iconUI* dungeonIcon = (iconUI*)malloc(sizeof(iconUI));

    iconUI* boldIconTrash = boldIcon;

    boldIcon->iconCode = -1;
    boldIcon->topLink = NULL;
    boldIcon->bottomLink = storeIcon;
    boldIcon->leftLink = storeIcon;
    boldIcon->rightLink = dungeonIcon;

    storeIcon->iconCode = 1;
    storeIcon->topLink = NULL;
    storeIcon->bottomLink = statusIcon;
    storeIcon->leftLink = NULL;
    storeIcon->rightLink = dungeonIcon;

    statusIcon->iconCode = 2;
    statusIcon->topLink = storeIcon;
    statusIcon->bottomLink = NULL;
    statusIcon->leftLink = NULL;
    statusIcon->rightLink = dungeonIcon;

    dungeonIcon->iconCode = 3;
    dungeonIcon->topLink = NULL;
    dungeonIcon->bottomLink = statusIcon;
    dungeonIcon->leftLink = storeIcon;
    dungeonIcon->rightLink = NULL;


    while (1)
    {
        //그래픽 출력
        system("cls");

        anchorX = 4; //좌표앵커 초기화
        anchorY = 5;
        gotoxy(anchorX, anchorY); //아이템1
        if (boldIcon == storeIcon)
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
        printf("┎------------------┒ ");
        gotoxy(anchorX, anchorY + 1);
        printf("┃       상점       ┃ ");
        gotoxy(anchorX, anchorY + 2);
        printf("┖------------------┚ ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

        anchorX = 4; //좌표앵커 초기화
        anchorY = 14;
        gotoxy(anchorX, anchorY); //아이템1
        if (boldIcon == statusIcon)
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
        printf("┎------------------┒ ");
        gotoxy(anchorX, anchorY + 1);
        printf("┃      스탯창      ┃ ");
        gotoxy(anchorX, anchorY + 2);
        printf("┖------------------┚ ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

        anchorX = 4 + 22 + 8; //좌표앵커 초기화
        anchorY = 5;
        gotoxy(anchorX, anchorY); //아이템1
        if (boldIcon == dungeonIcon)
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
        printf("┎------------------┒ ");
        gotoxy(anchorX, anchorY + 1);
        printf("┃     던전입구     ┃ ");
        gotoxy(anchorX, anchorY + 2);
        printf("┖------------------┚ ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

        while (1)
        {
            if (kbhit()) //키 입력
            {
                keyInput = getch();
                if (keyInput == 224)
                {
                    keyInput = getch();
                    switch (keyInput)
                    {
                    case 72://상
                    {
                        boldIcon = swichingBold(boldIcon, 0);
                        break;
                    }
                    case 80://하
                    {
                        boldIcon = swichingBold(boldIcon, 1);
                        break;
                    }
                    case 75://좌
                    {
                        boldIcon = swichingBold(boldIcon, 2);
                        break;
                    }
                    case 77://우
                    {
                        boldIcon = swichingBold(boldIcon, 3);
                        break;
                    }
                    }
                }
                else if (keyInput == 13) //엔터, 실행
                {
                    if (boldIcon->iconCode == 1)
                    {
                        sceneCounter = 3;
                    }
                    else if (boldIcon->iconCode == 2)
                    {
                        sceneCounter = 4;
                    }
                    else if (boldIcon->iconCode == 3)
                    {
                        sceneCounter = 5;
                    }
                    else
                    {
                        continue;
                        printf("알수없는 오류 발생\n");
                    }
                    free(storeIcon);
                    free(statusIcon);
                    free(dungeonIcon);
                    free(boldIconTrash);
                    return;
                }
                break;
            }
        }
    }


    printf("C\n");
    sceneCounter = select_input(0, maxScene);
}

int coin = 500; //임시화폐 변수*********************************************


//방향키 누르면 볼드 아이콘 주소 바꾸고 재출력
//엔터 누르면 해당 아이콘의 기능 실행
//물건 구매일 경우 재질문창 출력 (예: 구매 하겠습니까? 예/ 아니오)
//물건 아이콘 볼드 처리 시 오른쪽에 물건 설명 출력


void store_scene(playerStats* p) //3
{
    int value = 0; //안쓰는듯
    int keyInput = 0; //키입력 저장

    iconUI* boldIcon = (iconUI*)malloc(sizeof(iconUI)); //강조 아이콘 주소
    iconUI* item_1 = (iconUI*)malloc(sizeof(iconUI)); //템
    iconUI* item_2 = (iconUI*)malloc(sizeof(iconUI));
    iconUI* item_3 = (iconUI*)malloc(sizeof(iconUI));
    iconUI* item_4 = (iconUI*)malloc(sizeof(iconUI));
    iconUI* yes = (iconUI*)malloc(sizeof(iconUI)); //선택 UI
    iconUI* no = (iconUI*)malloc(sizeof(iconUI));
    iconUI* exit = (iconUI*)malloc(sizeof(iconUI));

    iconUI* backTemp = (iconUI*)malloc(sizeof(iconUI)); //선택창 종료 후 돌아갈 아이콘 주소 저장용
    iconUI* boldIconTrash = boldIcon; //볼드 초기 동적할당 삭제용

    boldIcon->iconCode = -1; //-1 넣어서 초기엔 아무것도 볼드 안함
    boldIcon->topLink = NULL;
    boldIcon->bottomLink = item_1;
    boldIcon->leftLink = item_1;
    boldIcon->rightLink = exit;

    item_1->iconCode = 0;
    item_1->topLink = NULL;
    item_1->bottomLink = item_2;
    item_1->leftLink = NULL;
    item_1->rightLink = exit;
    item_1->itemCode = 0;

    item_2->iconCode = 0;
    item_2->topLink = item_1;
    item_2->bottomLink = item_3;
    item_2->leftLink = NULL;
    item_2->rightLink = exit;
    item_2->itemCode = 1;

    item_3->iconCode = 0;
    item_3->topLink = item_2;
    item_3->bottomLink = item_4;
    item_3->leftLink = NULL;
    item_3->rightLink = exit;
    item_3->itemCode = 2;

    item_4->iconCode = 0;
    item_4->topLink = item_3;
    item_4->bottomLink = exit;
    item_4->leftLink = NULL;
    item_4->rightLink = exit;
    item_4->itemCode = 3;

    yes->iconCode = 1;
    yes->topLink = NULL;
    yes->bottomLink = NULL;
    yes->leftLink = NULL;
    yes->rightLink = no;

    no->iconCode = 2;
    no->topLink = NULL;
    no->bottomLink = NULL;
    no->leftLink = yes;
    no->rightLink = NULL;

    exit->iconCode = 3;
    exit->topLink = item_4;
    exit->bottomLink = NULL;
    exit->leftLink = item_4;
    exit->rightLink = NULL;

    int anchorX = 4; //gotoxy 시작할 좌표 초기화용
    int anchorY = 2;
    int printYoN = -1; //선택창 출력 할건지 말건지
    int itemPrice[4] = { 100,100,100,100 }; //아이템 가격 배열


    while (1)
    {
        //printf("창 출력 그래픽\n");//각 아이콘 하나씩 if문으로 강조 후, 강조 전 그려야 할 부분 다르게 만들기, 함수화 필요->print_store()
        //키 입력받는 부분, kbhit(), getch()
        //switch로 상하좌우, 엔터 구분
        //switchingBold로 강조부분 바꾸기
        //엔터 눌리면 현재 bold->iconCode 확인
        //switch문으로 맞는 명령어 실행
        //아이템 구매라면 itemCode 확인
        //구매 함수 purchaseFunc 진행
        //화면 그리기

        /*
        * p->playerHp -= increment[0];
    p->playerDamage -= increment[1];
    p->playerArmor -= increment[2];
    p->playerCriPer -= increment[3];
        */
        system("cls");


        anchorX = 30; //좌표앵커 초기화, 로그창 프레임 출력
        anchorY = 2;
        gotoxy(anchorX, anchorY);
        printf("┎------------------------------------┒ ");
        for (int i = 1; i <= 11; i++)
        {
            gotoxy(anchorX, anchorY + i);
            printf("┃                                    ┃ ");
        }
        gotoxy(anchorX, anchorY + 12);
        printf("┖------------------------------------┚ ");

        if (boldIcon->iconCode == -1)
        {
            anchorX = 32; //좌표앵커 초기화, 로그창 프레임 출력
            anchorY = 4;
            gotoxy(anchorX, anchorY);
            printf("어서오세요~");
            gotoxy(anchorX, anchorY + 1);
            printf("물건은 몇개 없지만...");
            gotoxy(anchorX, anchorY + 3);
            printf("소품종 대량생산으로 운영하여");
            gotoxy(anchorX, anchorY + 4);
            printf("재고는 마르지 않는답니다~");
        }

        if (boldIcon == item_1)
        {
            anchorX = 32; //좌표앵커 초기화
            anchorY = 4;
            gotoxy(anchorX, anchorY); //아이템1
            printf("마시거나 몸에 뿌리면");
            gotoxy(anchorX, anchorY + 1);
            printf("체력이 회복된다.");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
        }
        anchorX = 4; //좌표앵커 초기화
        anchorY = 2;
        gotoxy(anchorX, anchorY); //아이템1
        printf("┎------------------┒ ");
        gotoxy(anchorX, anchorY + 1);
        printf("┃     회북물약     ┃ ");
        gotoxy(anchorX, anchorY + 2);
        printf("┖------------------┚ ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

        if (boldIcon == item_2)
        {
            anchorX = 32; //좌표앵커 초기화
            anchorY = 4;
            gotoxy(anchorX, anchorY); //아이템1
            printf("마시거나 몸에 뿌리면");
            gotoxy(anchorX, anchorY + 1);
            printf("방어력이 증가한다.");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
        }
        anchorX = 4; //좌표앵커 초기화
        anchorY = 5;
        gotoxy(anchorX, anchorY); //아이템2
        printf("┎------------------┒ ");
        gotoxy(anchorX, anchorY + 1);
        printf("┃     튼튼물약     ┃ ");
        gotoxy(anchorX, anchorY + 2);
        printf("┖------------------┚ ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

        if (boldIcon == item_3)
        {
            anchorX = 32; //좌표앵커 초기화
            anchorY = 4;
            gotoxy(anchorX, anchorY); //아이템1
            printf("마시거나 몸에 뿌리면");
            gotoxy(anchorX, anchorY + 1);
            printf("치명타 확률이 증가한다.");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
        }
        anchorX = 4; //좌표앵커 초기화
        anchorY = 8;
        gotoxy(anchorX, anchorY); //아이템3
        printf("┎------------------┒ ");
        gotoxy(anchorX, anchorY + 1);
        printf("┃     집중물약     ┃ ");
        gotoxy(anchorX, anchorY + 2);
        printf("┖------------------┚ ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

        if (boldIcon == item_4)
        {
            anchorX = 32; //좌표앵커 초기화
            anchorY = 4;
            gotoxy(anchorX, anchorY); //아이템1
            printf("마시거나 몸에 뿌리면");
            gotoxy(anchorX, anchorY + 1);
            printf("공격력이 증가한다.");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
        }
        anchorX = 4; //좌표앵커 초기화
        anchorY = 11;
        gotoxy(anchorX, anchorY); //아이템4
        printf("┎------------------┒ ");
        gotoxy(anchorX, anchorY + 1);
        printf("┃     뇌절물약     ┃ ");
        gotoxy(anchorX, anchorY + 2);
        printf("┖------------------┚ ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);


        anchorX = 4;
        anchorY = 15;
        gotoxy(anchorX, anchorY);
        printf("잔돈: %d 코인", coin);

        if (boldIcon == exit)
        {
            anchorX = 32; //좌표앵커 초기화, 로그창 프레임 출력
            anchorY = 4;
            gotoxy(anchorX, anchorY);
            printf("..가시게요?");
            gotoxy(anchorX, anchorY + 1);
            printf("안녕히가세요~");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
        }
        anchorX = 38; //좌표앵커 초기화, 나가기
        anchorY = 15;
        gotoxy(anchorX, anchorY); //아이템4
        printf("┎------------------┒ ");
        gotoxy(anchorX, anchorY + 1);
        printf("┃      나가기      ┃ ");
        gotoxy(anchorX, anchorY + 2);
        printf("┖------------------┚ ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

        if (printYoN != -1)
        {
            anchorX = 34; //좌표앵커 초기화
            anchorY = 4;
            gotoxy(anchorX, anchorY);
            printf("구매하시려는 제품 맞으신가요? ");

            anchorX = 34; //좌표앵커 초기화
            anchorY = 6;
            gotoxy(anchorX, anchorY);
            if (boldIcon == yes)
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
            printf("┎----------┒ ");
            gotoxy(anchorX, anchorY + 1);
            printf("┃    네    ┃ ");
            gotoxy(anchorX, anchorY + 2);
            printf("┖----------┚ ");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

            anchorX = 34 + 14 + 2; //좌표앵커 초기화
            anchorY = 6;
            gotoxy(anchorX, anchorY);
            if (boldIcon == no)
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
            printf("┎----------┒ ");
            gotoxy(anchorX, anchorY + 1);
            printf("┃ 잠시만...┃ ");
            gotoxy(anchorX, anchorY + 2);
            printf("┖----------┚ ");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        }

        while (1)
        {
            if (kbhit()) //키 입력
            {
                keyInput = getch();
                if (keyInput == 224)
                {
                    keyInput = getch();
                    switch (keyInput)
                    {
                    case 72://상
                    {
                        boldIcon = swichingBold(boldIcon, 0);
                        break;
                    }
                    case 80://하
                    {
                        boldIcon = swichingBold(boldIcon, 1);
                        break;
                    }
                    case 75://좌
                    {
                        boldIcon = swichingBold(boldIcon, 2);
                        break;
                    }
                    case 77://우
                    {
                        boldIcon = swichingBold(boldIcon, 3);
                        break;
                    }
                    }
                }
                else if (keyInput == 13) //엔터, 실행
                {
                    if (boldIcon->iconCode == 3)
                    {
                        sceneCounter = 2;
                        free(item_1);
                        free(item_2);
                        free(item_3);
                        free(item_4);
                        free(yes);
                        free(no);
                        free(exit);
                        free(boldIconTrash);
                        return;
                    }
                    else if (boldIcon->iconCode == 0)
                    {
                        printYoN = boldIcon->itemCode;
                        backTemp = boldIcon; //돌아갈 때 강조할 이이콘 저장
                        boldIcon = yes;
                    }
                    else if (boldIcon->iconCode == 1) //yes itemPrice
                    {
                        if (coin < itemPrice[printYoN])
                        {
                            anchorX = 32; //좌표앵커 초기화
                            anchorY = 10;
                            gotoxy(anchorX, anchorY);
                            printf("삑- 잔액이 부족합니다.");
                            gotoxy(anchorX, anchorY + 1);
                            printf("... ...");
                            gotoxy(anchorX, anchorY + 3);
                            printf("주인과 나는 머쓱해졋다...");
                        }
                        else
                        {
                            coin = coin - itemPrice[printYoN];
                            anchorX = 32; //좌표앵커 초기화
                            anchorY = 10;
                            gotoxy(anchorX, anchorY);
                            printf("결제 완료!");
                            gotoxy(anchorX, anchorY + 1);
                            printf("갑자기 주인이 물약을 나에게 던졌다!");
                            gotoxy(anchorX, anchorY + 2);
                            printf("효과가 바로 적용되었다...");
                            //물약은 itemCode 위에서 순서대로 0~3임, 이 부분에서 itemCode 확인해서 스텟 데이터 바꾸면 됌*******************************
                            switch (backTemp->itemCode)
                            {
                            case 0:
                            {
                                p->playerHp += 50;
                                break;
                            }
                            case 1:
                            {
                                p->playerArmor += 5;
                                break;
                            }
                            case 2:
                            {
                                p->playerCriPer += 5;
                                break;
                            }
                            case 3:
                            {
                                p->playerDamage += 5;
                                break;
                            }
                            default:
                            {
                                fprintf(stderr, "알 수 없는 오류");
                                return;
                            }
                            }
                        }
                        Sleep(3000);
                        printYoN = -1;
                        boldIcon = backTemp;
                    }
                    else if (boldIcon->iconCode == 2) //no
                    {
                        printYoN = -1;
                        boldIcon = backTemp;
                    }
                }
                break;
            }
        }
        //---------------밑은 임시용----------------------
        //키 입력 반복 중, while문 끊기면 안댐
        //회면 지우고 재출력도 반복
        //만약 키 입력 되면
        //어떤 키인지 switch문 돌리기
        //switchingBold돌려서 강조 아이콘 바꾸기
        //만약 엔터 눌리면
        //현재 강조되어있는 주소의 아이콘 코드 받아서 명령 실행
        //아이템 선택 후 엔터->다시 물어보기, 이 아이템을 구매하시겠습니까?
        //잔액이 충분하다면 구매 완료 후 물어보는 창 없애고 다시 상점창
        //잔액이 부족하다면 구매 실패 출력 후 다시 상점창
        //나가기 아이콘 강조 중 엔터 누르면 상점 함수 종료, 씬카운터 마을로 바꾸기
    }
}

void status_scene(playerStats* p) //4
{
    int keyInput;
    int anchorX = 4; //gotoxy 시작할 좌표 초기화용
    int anchorY = 2;
    int pointerX = 15;
    int isExit = 0; //나가기 버튼에 올라가있는지



    while (1)
    {
        system("cls"); //화면 초기화

        printf("체력 : %.2lf\n", p->playerHp);
        printf("공격력 : %.2lf\n", p->playerDamage);
        printf("방어력 : %.2lf\n", p->playerArmor);
        printf("치명타 : %.2lf%%\n", p->playerCriPer);

        printf("\n 스택 상태 시 %s(이)가 사라집니다.\n", p->playerInven.arr[p->playerInven.rear]);
        printf("큐 상태 시 %s(이)가 사라집니다.\n", p->playerInven.arr[(p->playerInven.front + 1) % MAX_INVEN_SIZE]);
        if (is_stack != 1) {
            printf("현재 큐 상태입니다.\n");
        }
        else {
            printf("현재 스택 상태입니다.\n");
        }

        anchorX = 4;
        anchorY = 11;
        gotoxy(anchorX, anchorY);
        printf("인벤토리 -> ");
        for (int i = 0; i < 7; i++) {
            printf("%s ", p->playerInven.arr[i]);
        }

        if (isExit != 1)
        {
            anchorX = pointerX;
            anchorY = 10;
            gotoxy(anchorX, anchorY);
            printf("▼");
        }


        if (isExit == 1)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
        }
        anchorX = 38; //좌표앵커 초기화, 나가기
        anchorY = 15;
        gotoxy(anchorX, anchorY); //아이템4
        printf("┎------------------┒ ");
        gotoxy(anchorX, anchorY + 1);
        printf("┃      나가기      ┃ ");
        gotoxy(anchorX, anchorY + 2);
        printf("┖------------------┚ ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

        while (1)
        {
            if (kbhit()) //키 입력
            {
                keyInput = getch();
                if (keyInput == 224)
                {
                    keyInput = getch();
                    switch (keyInput)
                    {
                    case 72://상
                    {
                        isExit = 0;
                        break;
                    }
                    case 80://하
                    {
                        isExit = 1;
                        break;
                    }
                    case 75://좌
                    {
                        if (15 < pointerX)
                        {
                            pointerX -= 5;
                        }
                        break;
                    }
                    case 77://우
                    {
                        if (pointerX < 30)
                        {
                            pointerX += 5;
                        }
                        break;
                    }
                    }
                }
                else if (keyInput == 13) //엔터, 실행
                {
                    if (isExit == 1)
                    {
                        sceneCounter = 2;
                    }
                    else
                    {
                        continue;
                        printf("알수없는 오류 발생\n");
                    }

                    return;
                }
                break;
            }
        }
    }
}

void stage_select_scene() //5
{
    printf("F\n");
    sceneCounter = select_input(0, maxScene);
}

void battle_scene() //8~
{
    printf("G\n");
    sceneCounter = select_input(0, maxScene);
}

void select_reward_scene() //6
{
    printf("H\n");
    sceneCounter = select_input(0, maxScene);
}

void select_job_scene() //7
{
    printf("I\n");
    sceneCounter = select_input(0, maxScene);
}

int select_input(int min, int max)
{
    int selectValue = -1;
    while (1)
    {
        printf("입력: ");
        scanf(" %d", &selectValue);
        if ((selectValue < min) || (max < selectValue)) //함수 개수에 따라 변경
        {
            printf("다시 입력하세요.\n");
            continue;
        }
        break;
    }
    return selectValue;
}

void temp_item_scene() //-1 임시 인벤 아이템 삽입 함수
{
    printf("숫자를 누르면 해당하는 아이템 구입(1~4)\n");
    printf("5는 delete_rear, 6은 delete_front\n");
    printf("add_front는 스택 or 큐이므로 넣지 않음\n");
    printf("7을 누르면 자료구조 형태 변환\n");
    int num = 0;
    scanf("%d", &num);
    switch (num)
    {
    case 1:
    {
        add_rear(&p1, &i1);
        break;
    }
    case 2:
    {
        add_rear(&p1, &i2);
        break;
    }
    case 3:
    {
        add_rear(&p1, &i3);
        break;
    }
    case 4:
    {
        add_rear(&p1, &i4);
        break;
    }
    case 5:
    {
        delete_rear(&p1);
        break;
    }
    case 6:
    {
        delete_front(&p1);
        break;
    }
    case 7:
    {
        if (is_stack == 1) {
            is_stack = 0;
            printf("스택 -> 큐로 변환\n");
            break;
        }
        else if (is_stack != 1) {
            is_stack = 1;
            printf("큐 -> 스택으로 변환\n");
            break;
        }
    }
    default:
        break;
    }

    sceneCounter = select_input(0, maxScene);
}

void gotoxy(int x, int y)
{
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main()
{
    while (1)
    {
        switch (sceneCounter)
        {
        case 0:
        {
            start_scene();
            break;
        }
        case 1:
        {
            story_scene();
            break;
        }
        case 2:
        {
            village_scene();
            break;
        }
        case 3:
        {
            store_scene(&p1);
            break;
        }
        case 4:
        {
            status_scene(&p1);
            break;
        }
        case 5:
        {
            stage_select_scene();
            break;
        }
        case 6:
        {
            select_reward_scene();
            break;
        }
        case 7:
        {
            select_job_scene();
            break;
        }
        case 8:
        {
            battle_scene();
            break;
        }
        default:
        {
            break;
        }
        }
    }
    return 0;
}