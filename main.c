#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>

void textattr(int);
void gotoxy(int, int);
void drawBox(int);
void clearScreen();

#define lineNum 8
#define up 72 //instead of home cause me home key is left arrow
#define down 80 // instead of end cause me end key is the right arrow
#define right 77
#define left 75
#define enter 13
#define backspace 8
#define DELETE 83

int main()
{
    int index = 0,size=20;
    char text[20]= {""};
    char ch;
    int first = 50, current = 50, last = 50;
    char* pfirst = text;
    char* pcurrent = text;
    char* plast = text;

    clearScreen();
    drawBox(20);
    gotoxy(current, 8);
    do
    {

        gotoxy(current, lineNum);
        ch = getch();
        _flushall();
        switch (ch)
        {
        case -32:
            ch = getch();
            switch (ch)
            {
            case right:
                current++;
                pcurrent++;
                if (current >= last)
                {
                    current = last;
                    pcurrent = plast;
                }
                break;
            case left:
                current--;
                pcurrent--;
                if (current <= first)
                {
                    current = first;
                    pcurrent = pfirst;
                }
                break;
            case up:
                current = first;
                pcurrent = pfirst;
                break;
            case down:
                current = last;
                pcurrent = plast;
                break;
            case DELETE:
                if (current <= first)
                {
                    current = first;
                    pcurrent = pfirst;
                }
                for (int i = 0; i < last-50; i++)
                {
                    text[i] = text[i+1];
                }
                last--;
                plast--;
                current=first;
                pcurrent=pfirst;
                gotoxy(first, 8);
                for (int i = 0; i < last-50; i++)
                {
                    printf("%c", text[i]);
                }
                printf(" ");
                gotoxy(current, 8);

                break;
            }
            break;
           case backspace:
            if (current > first)
            {
                for (int i = current - first - 1; i < last - 50; i++)
                {
                    text[i] = text[i + 1];
                }
                last--;
                plast--;
                current--;
                pcurrent--;
                gotoxy(current, 8);
                for (int i = current - first; i < last - 50; i++)
                {
                    printf("%c", text[i]);
                }
                printf(" ");
                gotoxy(last, 8);
            }
            break;
        default:
            if (isprint(ch) && index <=size)
            {
                text[index] = ch;
                pcurrent++;
                current++;
                last++;
                plast++;
                index++;
                printf("%c", ch);
            }
            break;
        }
    }
    while (ch != enter);

    // Print what the user entered
    gotoxy(50,9);
    printf("User entered: %s\n", text);

    printf("\n\n");
    return 0;
}

void drawBox(int len)
{
    textattr(80);
    for (int i = 0; i < len; i++)
    {
        gotoxy(50 + i, 8);
        _cprintf(" ");
    }
}

void textattr(int i)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clearScreen()
{
    system("cls");
}
