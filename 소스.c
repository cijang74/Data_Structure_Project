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
    printf("  �ڡ�~�������� ���տ� ����          ");
    gotoxy(14, 5);
    printf("              ���� �κ��丮��              ");
    gotoxy(20, 6);
    printf("    �ڷᱸ�� ���°� �� �ǿ� ���Ͽ�~����  ");
    gotoxy(25, 7);
    printf("                                  ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

    x = 10;
    y = 12;
    gotoxy(x, y++);
    printf("  ��   ��");
    gotoxy(x, y++);
    printf(" /�塬 ��");
    gotoxy(x, y++);
    printf("/ �� ����");
    gotoxy(x, y++);
    printf("  ��   ��");
    gotoxy(x, y++);
    printf("  /��");
    gotoxy(x, y++);
    printf(" �� ��");
    gotoxy(x, y++);
    printf(" �� ��");
    gotoxy(x, y++);
    printf(" ��  ��");

    gotoxy(24, 13);
    printf("stack!");
    gotoxy(34, 9);
    printf("queue!");
    gotoxy(44, 11);
    printf("stack!");

    gotoxy(50, 21);
    printf("<���͸� ���� ���ӽ���...>");

    while (1)
    {
        if (kbhit()) //Ű �Է�
        {
            keyInput = getch();

            if (keyInput == 13) //����, ����
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

    strcpy(script[0].script, "����� �� �ӿ��� ������ ��Ÿ�� �ƹ� ������ ����\n          ������ ���ָ� �ɾ���.");
    strcpy(script[1].script, "�ῡ�� ��� ���� Ȯ���غ����� ������ ���� ���� ������.");
    strcpy(script[2].script, "�׷��� �κ��丮�� �� ����...����� ������ ���ְ� �ɷ��ִ� ����\n          �� �� �־���.");
    strcpy(script[3].script, "��� ����, ť ���·θ� ���� �� �־���,\n          �κ��丮���� ���������� ���� ���� �ı��Ǿ���.");
    strcpy(script[4].script, "�� ���ָ� Ǯ�� ���ؼ� ������ ���񷯾� �߰�,\n          ���� ������ �������� ���� ���� ������ ������ �����ߴ�.");

    while (1)
    {
        system("cls");

        gotoxy(10, 3);
        printf("%s", script[storyCounter].script);
        gotoxy(50, 21);
        if (storyCounter == 4)
            printf("<������ ���� ���� ����...>");
        else
            printf("<����ϱ� ���� ����...>");

        while (1)
        {
            if (kbhit()) //Ű �Է�
            {
                keyInput = getch();

                if (keyInput == 13) //����, ����
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