#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
using namespace std;

string ghost1[5] =
    {
        "    /  _  \\    ",
        "  ***********  ",
        "| '|   |   |' | ",
        "|  |   |   |  |",
        "|  '---|---'  |"};
string ghost2[5] =
    {
        "    / _ \\    ",
        "  *********  ",
        "|**|  |  |**| ",
        "|**|  |  |**|",
        "|  '--|--'  |"};
string ghost3[5] =
    {
        "    / _ \\    ",
        "  *********  ",
        "|**|  |  |**| ",
        "|**|  |  |**|",
        "|  '--|--'  |"};
string rocket[7] =
    {
        "      ^      ",
        "     / \\     ",
        "    / _ \\    ",
        "   |     |   ",
        " /'|  |  |'\\ ",
        "|  |  |  |  |",
        "|.-'--|--'-.|"};
string grid[560];

HANDLE variable = GetStdHandle(STD_OUTPUT_HANDLE);

void input();
void gotoxy(int x, int y);

bool ser_cursor(bool visible);
bool g2d = true, g3d = false;
int playerC = 20, playerR = 28;
int bulletX, bulletY, bulletState = 0;
int g1bulletX, g1bulletY, g1bulletState = 0;
int g2bulletX, g2bulletY, g2bulletState = 0;
int g3bulletX, g3bulletY, g3bulletState = 0;
int g1r = 0, g2r = 6, g3r = 11;
int g1c = 70, g2c = 6, g3c = 144;
int lives = 3, g1health = 5, g2health = 3, g3health = 3;
int time;
void intro();
void fire();
void left2();
void right2();
void fire2();
void printingGhosts();
void deletingGhosts();
void movingGhosts();
void bullets();
void youwin();
void youlose();
void left();
void right();
// void player

main()
{
    ser_cursor(false);
    input();
    intro();
    int score = 0;
    int looper = 520;
    system("cls");
    ser_cursor(false);
    system("color 01");
    gotoxy(30, 170);
    cout << "Score";
    gotoxy(31, 170);
    cout << "Lives";
    gotoxy(0, 0);

    while (true)
    {
        score++;
        // Sleep(10);
        system("color 01");

        // gotoxy(30, 179);
        // cout << score;
        // gotoxy(31, 179);
        // cout << lives;
        gotoxy(0, 0);

        if (GetAsyncKeyState(VK_LEFT))
        {
            left();
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            right();
        }
        if (GetAsyncKeyState(VK_SPACE))
        {
            fire();
        }

        playerR = looper + 33; // to move character upward with respect to the frame
        if (bulletState == 1)
        {
            grid[bulletY][bulletX] = ' ';
            bulletY = bulletY - 3;
            grid[bulletY][bulletX] = '^';
            if (bulletY < playerR - 35)
            {
                grid[bulletY][bulletX] = ' ';
                bulletState = 0;
            }
        }
        for (int i = looper, x = 0; x < 40; i++, x++) // looper containe the index of first line printed in each frame
        {                                             // the purpose of x in for(***) is to run loop for exact 40 iterations
            cout << grid[i] << endl;
        }
        // yaha par player print karana or us k grid ma coordinate bhi change karnay
        //  playerC;
        //--------------------------------------------------------------------
        for (int r = 0; r < 7; r++)
        {
            for (int c = 0; c < 13; c++)
            {
                grid[playerR + r - 1][playerC + c] = rocket[r][c];
            }
        }
        //==========================asteroids==================================
        if (grid[playerR - 2][playerC] == '*' || grid[playerR - 2][playerC + 1] == '*' || grid[playerR - 2][playerC + 2] == '*' ||
            grid[playerR - 2][playerC + 3] == '*' || grid[playerR - 2][playerC + 4] == '*' || grid[playerR - 2][playerC + 5] == '*' ||
            grid[playerR - 2][playerC + 6] == '*' || grid[playerR - 2][playerC + 7] == '*' || grid[playerR - 2][playerC + 8] == '*' ||
            grid[playerR - 2][playerC + 9] == '*' || grid[playerR - 2][playerC + 10] == '*' || grid[playerR - 2][playerC + 11] == '*' ||
            grid[playerR - 2][playerC + 12] == '*' || grid[playerR - 2][playerC + 13] == '*')
        {
            lives--;
            playerC = 144;
        }
        if (lives == 0)
        {
            youlose();
        }
        //=====================================================================
        looper--;
        if (looper == 7)
        {
            // looper=520;
            break;
        }
    }

    system("cls");
    bulletState = 0;
    gotoxy(31, 170);
    cout << "     ";
    gotoxy(30, 170);
    cout << "Time ";
    time = 350;

    playerR -= 7;
    while (true)
    {
        Sleep(20);
        gotoxy(30, 176);
        cout << time - 100;
        time--;
        // if(time-100<=100)
        // {
        //     youlose();
        // }
        deletingGhosts();
        for (int r = 0; r < 7; r++) // clearing previous rocket in grid
        {
            for (int c = 0; c < 13; c++)
            {
                grid[playerR + r][playerC + c] = ' ';
            }
        }

        if (GetAsyncKeyState(VK_LEFT))
        {
            left2();
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            right2();
        }
        if (GetAsyncKeyState(VK_SPACE))
        {
            fire2();
        }

        if (bulletState == 1) // moving player bullet
        {
            grid[bulletY][bulletX] = ' ';
            bulletY = bulletY - 2;
            grid[bulletY][bulletX] = '^';
            if (bulletY < playerR - 26)
            {
                grid[bulletY][bulletX] = ' ';
                bulletState = 0;
            }
        }
        bullets();
        movingGhosts();
        printingGhosts();
        // health of ghost
        if ((bulletY == 6 && (bulletX <= g1c + 15 && bulletX >= g1c)))
        {
            grid[bulletY][bulletX] = ' ';
            bulletY = 0;
            bulletState = 0;
            g1health--;
        }
        if ((bulletY == 12 && (bulletX <= g2c + 15 && bulletX >= g2c)))
        {
            grid[bulletY][bulletX] = ' ';
            bulletY = 0;
            bulletState = 0;
            g2health--;
        }
        if ((bulletY == 16 && (bulletX <= g3c + 15 && bulletX >= g3c)))
        {
            grid[bulletY][bulletX] = ' ';
            bulletY = 0;
            bulletState = 0;
            g3health--;
        }

        // printing new rocket in grid
        for (int r = 0; r < 7; r++)
        {
            for (int c = 0; c < 13; c++)
            {
                grid[playerR + r - 1][playerC + c] = rocket[r][c];
            }
        }
        for (int i = 0, x = 0; x < 40; i++, x++) // looper containe the index of first line printed in each frame
        {
            gotoxy(x, 0); // the purpose of x in for(***) is to run loop for exact 40 iterations
            cout << grid[i] << endl;
        }
        if (g1health < 1 && g2health < 1 && g3health < 1)
        {
            gotoxy(0, 0);
            for (int i = 0, x = 0; x < 35; i++, x++)
            {
                cout << grid[i] << endl;
            }
            deletingGhosts();
            printingGhosts();
            youwin();
        }
    }
}

void intro()
{
    system("cls");

    ser_cursor(false);
    gotoxy(16, 60);
    cout << " _   _          _    _                _   _                      ";
    gotoxy(17, 60);
    cout << "| \\ | |        | |  | |              | | | |                     ";
    gotoxy(18, 60);
    cout << "|  \\| | ___    | |  | | __ _ _   _   | |_| | ___  _ __ ___   ___ ";
    gotoxy(19, 60);
    cout << "| . ` |/ _ \\   | |/\\| |/ _` | | | |  |  _  |/ _ \\| '_ ` _ \\ / _ \\";
    gotoxy(20, 60);
    cout << "| |\\  | (_) |  \\  /\\  / (_| | |_| |  | | | | (_) | | | | | |  __/";
    gotoxy(21, 60);
    cout << "\\_| \\_/\\___/    \\/  \\/ \\__,_|\\__, |  \\_| |_/\\___/|_| |_| |_|\\___|";
    gotoxy(22, 60);
    cout << "                              __/ |                              ";
    gotoxy(23, 60);
    cout << "                             |___/                               ";
    getch();
}

void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = y;
    coordinates.Y = x;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void left()
{
    if (playerC > 6)
    {
        playerC = playerC - 2;
    }
}
void right()
{
    if (playerC < 143)
    {
        playerC = playerC + 2;
    }
}
void fire()
{
    if (bulletState == 0)
    {
        bulletX = playerC + 6;
        bulletY = playerR - 1;
        bulletState = 1;
    }
}

void left2()
{

    if (playerC > 6)
    {
        playerC = playerC - 2;
    }
}
void right2()
{
    if (playerC < 143)
    {
        playerC = playerC + 2;
    }
}
void fire2()
{
    if (bulletState == 0)
    {
        bulletX = playerC + 6;
        bulletY = playerR - 2;
        bulletState = 1;
    }
}

void printingGhosts()
{
    // ghost1
    if (g1health > 0)
    {
        // ghost1[2][8]=char(g1health)+48;
        for (int r = 0; r < 5; r++)
        {
            for (int c = 0; c < 15; c++)
            {
                grid[r + g1r][c + g1c] = ghost1[r][c];
            }
        }
    }
    // ghost2
    if (g2health > 0)
    {
        // ghost2[2][7]=char(g2health)+48;
        for (int r = 0; r < 5; r++)
        {
            for (int c = 0; c < 13; c++)
            {
                grid[r + g2r][c + g2c] = ghost2[r][c];
            }
        }
    }
    // ghost3
    if (g3health > 0)
    {
        // ghost3[2][7]=char(g3health)+48;
        for (int r = 0; r < 5; r++)
        {
            for (int c = 0; c < 13; c++)
            {
                grid[r + g3r][c + g3c] = ghost3[r][c];
            }
        }
    }
}
void deletingGhosts()
{
    for (int r = 0; r < 5; r++)
    {
        for (int c = 0; c < 15; c++)
        {
            grid[r + g1r][c + g1c] = ' ';
        }
    }
    for (int r = 0; r < 5; r++)
    {
        for (int c = 0; c < 13; c++)
        {
            grid[r + g2r][c + g2c] = ' ';
        }
    }
    for (int r = 0; r < 5; r++)
    {
        for (int c = 0; c < 13; c++)
        {
            grid[r + g3r][c + g3c] = ' ';
        }
    }
}
void movingGhosts()
{
    // direction inversion g1 and g2
    if (g2c == 144)
    {
        g2d = false;
    }
    if (g2c == 6)
    {
        g2d = true;
    }
    if (g3c == 144)
    {
        g3d = false;
    }
    if (g3c == 6)
    {
        g3d = true;
    }

    // moving g1 and g2
    if (g2d == true)
    {
        g2c++;
    }
    else
    {
        g2c--;
    }
    if (g3d == true)
    {
        g3c++;
    }
    else
    {
        g3c--;
    }

    if (g1c > playerC)
    {
        if (g1c > 6)
        {
            g1c--;
        }
    }
    if (g1c < playerC)
    {
        if (g1c < 143)
        {
            g1c++;
        }
    }
}

void bullets()
{
    if (g1bulletState == 1 && g1health > 0)
    {
        grid[g1bulletY][g1bulletX] = ' ';
        g1bulletY = g1bulletY + 1;
        grid[g1bulletY][g1bulletX] = '*';
        if (g1bulletY > playerR + 2)
        {
            grid[g1bulletY][g1bulletX] = ' ';
            g1bulletState = 0;
        }
    }
    else
    {
        g1bulletState = 1;
        g1bulletX = g1c + 8;
        g1bulletY = g1r;
    }
    if (g2bulletState == 1 && g2health > 0)
    {
        grid[g2bulletY][g2bulletX] = ' ';
        g2bulletY = g2bulletY + 1;
        grid[g2bulletY][g2bulletX] = '*';
        if (g2bulletY > playerR + 2)
        {
            grid[g2bulletY][g2bulletX] = ' ';
            g2bulletState = 0;
        }
    }
    else
    {
        g2bulletState = 1;
        g2bulletX = g2c + 7;
        g2bulletY = g2r;
    }
    if (g3bulletState == 1 && g3health > 0)
    {
        grid[g3bulletY][g3bulletX] = ' ';
        g3bulletY = g3bulletY + 1;
        grid[g3bulletY][g3bulletX] = '*';
        if (g3bulletY > playerR + 2)
        {
            grid[g3bulletY][g3bulletX] = ' ';
            g3bulletState = 0;
        }
    }
    else
    {
        g3bulletState = 1;
        g3bulletX = g3c + 7;
        g3bulletY = g3r;
    }
}
void youwin()
{
    system("cls");
    SetConsoleTextAttribute(variable, 2);
    gotoxy(16, 65);
    cout << "__   __            _    _ _     ";
    gotoxy(17, 65);
    cout << "\\ \\ / /            | |  | (_)    ";
    gotoxy(18, 65);
    cout << " \\ V /___  _   _   | |  | |_ _ __ ";
    gotoxy(19, 65);
    cout << "  \\ // _ \\| | | |  | |/\\| | | '_ \\ ";
    gotoxy(20, 65);
    cout << "  | | (_) | |_| |  \\  /\\  / | | | |";
    gotoxy(21, 65);
    cout << "  \\_/\\___/ \\__,_|   \\/  \\/|_|_| |_|";
    gotoxy(22, 65);
    abort();
}
void youlose()
{
    system("cls");
    char temp;
    SetConsoleTextAttribute(variable, 4);
    gotoxy(31, 179);
    cout << lives;
    gotoxy(16, 65);
    cout << "__   __             _                    ";
    gotoxy(17, 65);
    cout << "\\ \\ / /            | |                   ";
    gotoxy(18, 65);
    cout << " \\ V /___  _   _   | |     ___  ___  ___ ";
    gotoxy(19, 65);
    cout << "  \\ // _ \\| | | |  | |    / _ \\/ __|/ _ \\";
    gotoxy(20, 65);
    cout << "  | | (_) | |_| |  | |___| (_) \\__ \\  __/";
    gotoxy(21, 65);
    cout << "  \\_/\\___/ \\__,_|  \\_____/\\___/|___/\\___|";
    gotoxy(22, 65);
    getch();
    abort();
}
bool ser_cursor(bool visible)
{
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = visible;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void input()
{
    string line;
    int i = 0;
    fstream file;
    file.open("maze.txt", ios::in);
    // cin.ignore();
    while (!file.eof())
    {
        getline(file, line);
        grid[i] = line;
        i++;
    }
    file.close();
}
