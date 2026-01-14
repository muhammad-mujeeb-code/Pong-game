#include <iostream>
#include <conio.h>    // For _kbhit() and _getch() - non-blocking keyboard input
#include <windows.h>  // For Windows API functions like SetConsoleCursorPosition

using namespace std;

// Move cursor to (x,y) in console
void gotoxy(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Draw paddle, ball, borders, score, lives
void drawboard(int paddleX, int ballX, int ballY, int score, int lives){
    system("cls");

    gotoxy(paddleX, 20);
    cout<<"<====>";

    gotoxy(ballX, ballY);
    cout<<"O";

    // top & bottom borders
    for(int i=0; i<42; i++){
        gotoxy(i,0);
        cout<<"*";
        gotoxy(i,24);
        cout<<"*";
    }

    // left & right borders
    for(int i=0; i<25; i++){
        gotoxy(0,i);
        cout<<"*";
        gotoxy(41,i);
        cout<<"*";
    }

    gotoxy(45,5);
    cout<<"Score: "<<score;
    gotoxy(45,7);
    cout<<"Lives: "<<lives;
}


int main(){
    system("mode con: lines=30 cols=60");

    int paddleX = 20;
    int ballX = 32;
    int ballY = 19;
    int ballDirX = 1;
    int ballDirY = -1;
    int score = 0;
    int lives = 3;

    cout<<"Instructions: "<<endl;
    cout<<"*************"<<endl;
    cout<<"1. Press right and left arrow keys for move paddle."<<endl;
    cout<<"2. Press Esc key for quit game."<<endl; 

    system ("pause");

    while(lives>0){
        // input
        if(_kbhit()){
            char key = _getch();

            if(key == 75 && paddleX > 3){
                paddleX--;
                paddleX--;
                paddleX--;
            }

            else if(key == 77 && paddleX < 34){
                paddleX++;
                paddleX++;
                paddleX++;
            }

            else if(key == 27){
                break;
            }
        }

        // update ball
        ballX = ballX + ballDirX;
        ballY = ballY + ballDirY;

        // bounce on paddle
        if(ballY == 20 && ballX >= paddleX && ballX <= paddleX+5){
            ballDirY = -ballDirY;
            score++;
        }

        // bounce on walls
        if(ballX == 1 || ballX == 40){
            ballDirX = -ballDirX;
        }

        if(ballY == 1){
            ballDirY = -ballDirY;
        }

        // missed paddle → lose life
        if(ballY == 23){
            lives--;
            ballX = 20;
            ballY = 19;
            ballDirY = -ballDirY;
        }

        drawboard(paddleX, ballX, ballY, score, lives);
        Sleep(100);
    }

    // game over
    system("cls");
	
	gotoxy(15, 8);
	cout<<"Game Over!"<<endl;
	
	gotoxy(15, 9);
    cout << "Final Score: " << score << endl;
	
	gotoxy(15, 10);
	
    cout << "Press any key to exit..." << endl;
    _getch();

    return 0;
}