#include <iostream>
#include <Windows.h>
#include <list>
#include <thread>
#include <conio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

int nScreenWidth = 120;
int nScreenHeight = 30;

struct sSnakeSegment
{
    int x;
    int y;
};

int main()
{
    srand((unsigned)time(0));
    //Create Screen Buffer
    wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
    for (int i = 0; i < nScreenWidth * nScreenHeight; i++) screen[i] = L' ';
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;
    int nRekord = 0;
    int nRekordOld = 0;

    string line;
    ifstream  myfile("SnakeDaten2.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            stringstream geek(line);
            int line = 0;
            geek >> line;

            nRekordOld = line;
        }
        myfile.close();
    }


    do {

        wsprintf(&screen[ 7 * nScreenWidth + 28], L"   XXXX     XXXX    XX         XX         XX    XX   XXXXXXX ");
        wsprintf(&screen[ 8 * nScreenWidth + 28], L"  XX  XX    XXXX    XX        XXXX        XX   XXX   XX      ");
        wsprintf(&screen[ 9 * nScreenWidth + 28], L" XX    XX   XXXXX   XX        XXXX        XX   XX    XX      ");
        wsprintf(&screen[10 * nScreenWidth + 28], L" XX    XX   XXXXX   XX       XX  XX       XX   XX    XX      ");
        wsprintf(&screen[11 * nScreenWidth + 28], L"  XX   XX   XX XX   XX       XX  XX       XX  XX     XX      ");
        wsprintf(&screen[12 * nScreenWidth + 28], L"   XX       XX XXX  XX      XX    XX      XX XX      XX      ");
        wsprintf(&screen[13 * nScreenWidth + 28], L"    XX      XX  XX  XX      XXXXXXXX      XXXXX      XXXXXXX ");
        wsprintf(&screen[14 * nScreenWidth + 28], L"     XX     XX  XXX XX     XX      XX     XXXXX      XX      ");
        wsprintf(&screen[15 * nScreenWidth + 28], L"      XX    XX   XX XX     XX      XX     XX XX      XX      ");
        wsprintf(&screen[16 * nScreenWidth + 28], L" XX    XX   XX   XXXXX    XX        XX    XX  XX     XX      ");
        wsprintf(&screen[17 * nScreenWidth + 28], L" XX    XX   XX    XXXX    XX        XX    XX   XX    XX      ");
        wsprintf(&screen[18 * nScreenWidth + 28], L"  XX  XX    XX    XXXX   XX          XX   XX   XXX   XX      ");
        wsprintf(&screen[19 * nScreenWidth + 28], L"   XXXX     XX     XXX   XX          XX   XX    XX   XXXXXXX ");

        wsprintf(&screen[21 * nScreenWidth + 48], L"PRESS   'SPACE' TO PLAY");


        WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);

    } while ((0x8000 & GetAsyncKeyState((unsigned char)('\x20'))) == 0);

    while (1)
    {

        list<sSnakeSegment> snake = { {60, 15}, {61, 15}, { 62, 15 }, { 63, 15 }, { 64, 15 }, { 65, 15 }, { 66, 15 }, { 67, 15 }, { 68, 15 }, { 69, 15 } };
        int nFoodX = 30;
        int nFoodY = 15;
        int nScore = 0;
        int nScoreOld = 0;

        int nSnakeDirection = 3;
        bool bPause = false;
        bool bDead = false;
        bool bChef = false;
        bool bKeyRight = false, bKeyLeft = false, bKeyUp = false, bKeyDown = false, bKeyLeave = false, bKeyPause = false, bKeyResume = false, bKeyChef = false, bKeyPlay = false, bKeyChefOld = false;


        while (!bDead)
        {
            // Timing & Inputu

            // Get Input
            auto t1 = chrono::system_clock::now();
            while ((chrono::system_clock::now() - t1) < ((nSnakeDirection % 2 == 1) ? 70ms : 110ms)) //70 110
            {
                if (nScore > 10)
                {
                    (nSnakeDirection % 2 == 1) ? 20ms : 30ms; //57 90
                }

                if (nScore > 20)
                {
                    (nSnakeDirection % 2 == 1) ? 38ms : 60ms;
                }

                if (nScore > 30)
                {
                    (nSnakeDirection % 2 == 1) ? 31ms : 50ms;
                }

                if (nScore > 40)
                {
                    (nSnakeDirection % 2 == 1) ? 25ms : 40ms;
                }

                if (nScore > 50)
                {
                    (nSnakeDirection % 2 == 1) ? 20ms : 30ms;
                }

                bKeyRight = (0x8000 & GetAsyncKeyState((unsigned char)('\x27'))) != 0;  //27
                bKeyLeft = (0x8000 & GetAsyncKeyState((unsigned char)('\x25'))) != 0;  //25 
                bKeyUp = (0x8000 & GetAsyncKeyState((unsigned char)('\x26'))) != 0;  //26
                bKeyDown = (0x8000 & GetAsyncKeyState((unsigned char)('\x28'))) != 0; //28
                bKeyLeave = (0x8000 & GetAsyncKeyState((unsigned char)('\x4C'))) != 0; //4C entspricht l
                bKeyPause = (0x8000 & GetAsyncKeyState((unsigned char)('\x50'))) != 0; //50 entspricht p
                bKeyResume = (0x8000 & GetAsyncKeyState((unsigned char)('\x52'))) != 0; //52 entspricht r
                bKeyChef = (0x8000 & GetAsyncKeyState((unsigned char)('\x43'))) != 0; //43 entspricht c

                if (bKeyRight)
                {
                    nSnakeDirection++;
                    nSnakeDirection = 1;
                }

                if (bKeyLeft)
                {
                    nSnakeDirection--;
                    nSnakeDirection = 3;
                }

                if (bKeyUp)
                {
                    nSnakeDirection--;
                    nSnakeDirection = 0;
                }

                if (bKeyDown)
                {
                    nSnakeDirection--;
                    nSnakeDirection = 2;
                }

                if (bKeyPause)
                {
                    bPause = true;
                }

                if (bKeyResume)
                {
                    bPause = false;
                }

                if (bKeyLeave)
                {
                    return EXIT_SUCCESS;
                }

                if (bKeyChef && !bKeyChefOld)
                {
                    ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
                    bPause = true;
                    using namespace std::chrono;
                    (system_clock::now() + seconds(1));
                    bKeyChefOld = bKeyChef;
                }

            }

            // Game Logic

            // Update Snake Position
            switch (nSnakeDirection)
            {
            case 0: // UP
                snake.push_front({ snake.front().x, snake.front().y - 1 });
                break;
            case 1: //RIGHT
                snake.push_front({ snake.front().x + 1, snake.front().y });
                break;
            case 2: //DOWN
                snake.push_front({ snake.front().x, snake.front().y + 1 });
                break;
            case 3: //LEFT
                snake.push_front({ snake.front().x - 1, snake.front().y });
                break;
            case 4: //Dont Move
                snake.push_front({ snake.front().x, snake.front().y });
                break;
            }

            // Collision Detect Snake V World
            if (snake.front().x < 0 || snake.front().x >= nScreenWidth)
                bDead = true;
            if (snake.front().y < 3 || snake.front().y >= nScreenHeight)
                bDead = true;

            // Collision Detect Snake V Food
            if (snake.front().x == nFoodX && snake.front().y == nFoodY)
            {
                nScore++;
                while (screen[nFoodY * nScreenWidth + nFoodX] != L' ')
                {
                    nFoodX = rand() % nScreenWidth;
                    nFoodY = (rand() % (nScreenHeight - 3)) + 3;
                }

                for (int i = 0; i < 5; i++)
                    snake.push_back({ snake.back().x, snake.back().y });
            }
            // Rekord output

            nScoreOld = nScore;
            if (nScore > nRekordOld)
            {
                nRekordOld = nScore;
                nRekord = nScore;
            }
            else
            {
                nRekord = nRekordOld;
            }

            if (line < to_string(nRekord))
            {
                ofstream myfile("SnakeDaten2.txt");
                if (myfile.is_open())
                {
                    myfile << nRekord;
                    myfile.close();
                }
            }

            // Collision Detect Snake V Snake
            for (list<sSnakeSegment>::iterator i = snake.begin(); i != snake.end(); i++)
                if (i != snake.begin() && i->x == snake.front().x && i->y == snake.front().y)
                    bDead = true;

            // Chop off Snakes tail
            snake.pop_back();

            // Display to player

            // Clear Screen
            for (int i = 0; i < nScreenWidth * nScreenHeight; i++) screen[i] = L' ';

            // Draw Stats & Border
            for (int i = 0; i < nScreenWidth; i++)
            {
                screen[i] = L'=';
                screen[2 * nScreenWidth + i] = L'=';
            }
            wsprintf(&screen[nScreenWidth + 5], L"SNAKE !!   SCORE:%d  Rekord:%d", nScore, nRekord);

            // Snake Body Color


            // Draw Snake Body
            for (auto s : snake)
                screen[s.y * nScreenWidth + s.x] = bDead ? L'+' : L'o';

            // Draw Snake Head
            screen[snake.front().y * nScreenWidth + snake.front().x] = bDead ? L'X' : L'☺';

            // Draw Food
            screen[nFoodY * nScreenWidth + nFoodX] = L'\xF000';

            // Draw Game-Over menue

            if (bDead)
            {
                wsprintf(&screen[10 * nScreenWidth + 48], L"          GAME OVER");
                wsprintf(&screen[12 * nScreenWidth + 48], L"           Score:%d", nScore);
                wsprintf(&screen[13 * nScreenWidth + 48], L"           Record:%d", nRekord);
                wsprintf(&screen[16 * nScreenWidth + 48], L"PRESS   'SPACE' TO PLAY AGAIN");
                wsprintf(&screen[18 * nScreenWidth + 48], L"PRESS   'L' To Leave the Game");
            }

            if (bPause)
            {
                do {
                    wsprintf(&screen[10 * nScreenWidth + 58], L"PAUSE");
                    wsprintf(&screen[12 * nScreenWidth + 57], L"Score:%d", nScore);
                    wsprintf(&screen[13 * nScreenWidth + 57], L"Record:%d", nRekord);
                    wsprintf(&screen[15 * nScreenWidth + 50], L"PRESS   'R' TO RESUME");

                    WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);

                    bKeyChef = (0x8000 & GetAsyncKeyState((unsigned char)('\x43'))) != 0;
                    bKeyChefOld = bKeyChef;

                    /*if (bKeyChefOld = true)
                    {
                           ShowWindow(GetConsoleWindow(), SW_RESTORE);
                            bPause = false;
                    }*/

                } while ((0x8000 & GetAsyncKeyState((unsigned char)('\x52'))) == 0);
                bPause = false;
            }

            // Display Frame
            WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);

        }

        // Wait for space
        do {
            bKeyLeave = (0x8000 & GetAsyncKeyState((unsigned char)('\x4C'))) != 0; //4C entspricht l
            if (bKeyLeave)
            {
                return EXIT_SUCCESS;
            }
        } while ((0x8000 & GetAsyncKeyState((unsigned char)('\x20'))) == 0);

    }
    return EXIT_SUCCESS;
}
