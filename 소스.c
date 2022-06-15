void start_scene() //0
{
    int keyInput = 0;
    int x;
    int y;
    system("cls");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
    gotoxy(16, 3);
    printf("                            ");
    gotoxy(12, 4);
    printf("  ★『~할짓없는 마왕에 의해          ");
    gotoxy(14, 5);
    printf("              나의 인벤토리가              ");
    gotoxy(20, 6);
    printf("    자료구조 형태가 된 건에 대하여~』☆  ");
    gotoxy(25, 7);
    printf("                                  ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

    x = 10;
    y = 12;
    gotoxy(x, y++);
    printf("  ■   ｜");
    gotoxy(x, y++);
    printf(" /▼＼ ｜");
    gotoxy(x, y++);
    printf("/ ｜ ＼┼");
    gotoxy(x, y++);
    printf("  ｜   ｜");
    gotoxy(x, y++);
    printf("  /＼");
    gotoxy(x, y++);
    printf(" ｜ ｜");
    gotoxy(x, y++);
    printf(" ｜ ｜");
    gotoxy(x, y++);
    printf(" ┘  └");

    gotoxy(24, 13);
    printf("stack!");
    gotoxy(34, 9);
    printf("queue!");
    gotoxy(44, 11);
    printf("stack!");

    gotoxy(50, 21);
    printf("<엔터를 눌러 게임시작...>");

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
    char script[150];
}storyScript;

void story_scene() //1
{
    int keyInput = 0;
    int storyCounter = 0;
    storyScript script[5];

    strcpy(script[0].script, "어느날 꿈 속에서 마왕이 나타나 아무 이유도 없이\n          나에게 저주를 걸었다.");
    strcpy(script[1].script, "잠에서 깨어나 몸을 확인해봤지만 다행히 변한 것은 없었다.");
    strcpy(script[2].script, "그러나 인벤토리를 연 순간...상당히 괴랄한 저주가 걸려있는 것을\n          볼 수 있었다.");
    strcpy(script[3].script, "장비를 스텍, 큐 형태로만 넣을 수 있었고,\n          인벤토리에서 빠져나가는 순간 장비는 파괴되었다.");
    strcpy(script[4].script, "이 저주를 풀기 위해선 마왕을 무찔러야 했고,\n          지금 마왕의 던전으로 가기 위한 마지막 마을에 도착했다.");

    while (1)
    {
        system("cls");

        gotoxy(10, 3);
        printf("%s", script[storyCounter].script);
        gotoxy(50, 21);
        if (storyCounter == 4)
            printf("<마을로 가기 위해 엔터...>");
        else
            printf("<계속하기 위해 엔터...>");

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