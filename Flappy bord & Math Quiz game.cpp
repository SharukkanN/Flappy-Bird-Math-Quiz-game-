#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // Handle for console output
COORD CursorPosition; // Structure to store cursor position

// Function to set the cursor position
void gotoxy(int x, int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

// Function to set cursor visibility and size
void setcursor(bool visible, DWORD size) {
    if (size == 0)
        size = 20;

    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

// Constants for screen dimensions and game parameters
const int SCREEN_WIDTH = 90;
const int SCREEN_HEIGHT = 26;
const int WIN_WIDTH = 70;
const int MENU_WIDTH = 20;
const int GAP_SIZE = 7;
const int PIPE_DIF = 45;

int pipePos[3]; // Array to store pipe positions
int gapPos[3];  // Array to store gap positions
int pipeFlag[3]; // Array to store pipe flags (whether the pipe is active or not)
char bird[2][6] = { '/', '-', '-', 'o', '\\', ' ', '|', '', '', '_', ' ', '>' }; // Bird characters
int birdPos = 6; // Initial bird position
int score = 0;   // Game score

// Function to draw the border of the game screen
void drawBorder() {
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        gotoxy(i, 0); cout << "?";
        gotoxy(i, SCREEN_HEIGHT); cout << "?";
    }

    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        gotoxy(0, i); cout << "?";
        gotoxy(SCREEN_WIDTH, i); cout << "?";
    }
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        gotoxy(WIN_WIDTH, i); cout << "?";
    }
}

// Function to generate a new pipe
void genPipe(int ind) {
    gapPos[ind] = 3 + rand() % 14;
}

// Function to draw a pipe
void drawPipe(int ind) {
    if (pipeFlag[ind] == true) {
        for (int i = 0; i < gapPos[ind]; i++) {
            gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "*";
        }
        for (int i = gapPos[ind] + GAP_SIZE; i < SCREEN_HEIGHT - 1; i++) {
            gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "*";
        }
    }
}

// Function to erase a pipe
void erasePipe(int ind) {
    if (pipeFlag[ind] == true) {
        for (int i = 0; i < gapPos[ind]; i++) {
            gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "   ";
        }
        for (int i = gapPos[ind] + GAP_SIZE; i < SCREEN_HEIGHT - 1; i++) {
            gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "   ";
        }
    }
}

// Function to draw the bird
void drawBird() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            gotoxy(j + 2, i + birdPos); cout << bird[i][j];
        }
    }
}

// Function to erase the bird
void eraseBird() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            gotoxy(j + 2, i + birdPos); cout << " ";
        }
    }
}

// Function to check for collision between the bird and pipes
int collision() {
    if (pipePos[0] >= 61) {
        if (birdPos < gapPos[0] || birdPos > gapPos[0] + GAP_SIZE) {
            return 1;
        }
    }
    return 0;
}

// Function to display the game over screen
void gameover() {
    system("cls");
    cout << endl;
    cout << "\t\t--------------------------" << endl;
    cout << "\t\t-------- Game Over -------" << endl;
    cout << "\t\t--------------------------" << endl << endl;
    cout << "\t\tPress any key to go back to the menu.";
    getch();
}

// Function to update the game score on the screen
void updateScore() {
    gotoxy(WIN_WIDTH + 7, 5); cout << "Score: " << score << endl;
}

// Function to display game instructions
void instructions() {
    system("cls");
    cout << "Instructions";
    cout << "\n----------------";
    cout << "\n Press spacebar to make bird fly";
    cout << "\n\nPress any key to go back to the menu";
    getch();
}

// Function to play the Flappy Bird game
void playGame1() {
    birdPos = 6;
    score = 0;
    pipeFlag[0] = 1;
    pipeFlag[1] = 0;
    pipePos[0] = pipePos[1] = 4;

    system("cls");
    drawBorder();
    genPipe(0);
    updateScore();

    gotoxy(WIN_WIDTH + 5, 2); cout << "FLAPPY BIRD";
    gotoxy(WIN_WIDTH + 6, 4); cout << "----------";
    gotoxy(WIN_WIDTH + 6, 6); cout << "----------";
    gotoxy(WIN_WIDTH + 7, 12); cout << "Control ";
    gotoxy(WIN_WIDTH + 7, 13); cout << "-------- ";
    gotoxy(WIN_WIDTH + 2, 14); cout << " Spacebar = jump";

    gotoxy(10, 5); cout << "Press any key to start";
    getch();
    gotoxy(10, 5); cout << "                      ";

    while (1) {
        if (kbhit()) {
            char ch = getch();
            if (ch == 32) {
                if (birdPos > 3)
                    birdPos -= 3;
            }
            if (ch == 27) {
                break;
            }
        }

        drawBird();
        drawPipe(0);
        drawPipe(1);
        if (collision() == 1) {
            gameover();
            return;
        }
        Sleep(100);
        eraseBird();
        erasePipe(0);
        erasePipe(1);
        birdPos += 1;

        if (birdPos > SCREEN_HEIGHT - 2) {
            gameover();
            return;
        }

        if (pipeFlag[0] == 1)
            pipePos[0] += 2;

        if (pipeFlag[1] == 1)
            pipePos[1] += 2;

        if (pipePos[0] >= 40 && pipePos[0] < 42) {
            pipeFlag[1] = 1;
            pipePos[1] = 4;
            genPipe(1);
        }
        if (pipePos[0] > 68) {
            score++;
            updateScore();
            pipeFlag[1] = 0;
            pipePos[0] = pipePos[1];
            gapPos[0] = gapPos[1];
        }
    }
}

// Function to play the Math Quiz Game
void playGame2() {
    srand(static_cast<unsigned>(time(nullptr)));

    int totalScore = 0;
    int numQuestions;

    cout << "Welcome to the Math Quiz Game!" << endl;

    for (int level = 1; level <= 3; level++) {
        switch (level) {
        case 1:
            numQuestions = 5;
            break;
        case 2:
            numQuestions = 7;
            break;
        case 3:
            numQuestions = 10;
            break;
        }

        int score = 0;

        for (int i = 0; i < numQuestions; i++) {
            int operand1 = rand() % 20 + 1;
            int operand2 = rand() % 20 + 1;
            int operation = rand() % 4 + 1; // 1: Addition, 2: Subtraction, 3: Multiplication, 4: Division

            int correctAnswer;
            char operatorSymbol;

            switch (operation) {
            case 1:
                correctAnswer = operand1 + operand2;
                operatorSymbol = '+';
                break;
            case 2:
                correctAnswer = operand1 - operand2;
                operatorSymbol = '-';
                break;
            case 3:
                correctAnswer = operand1 * operand2;
                operatorSymbol = '*';
                break;
            case 4:
                if (operand2 == 0) {
                    cout << "Division by zero! Skipping this question." << endl;
                    continue; // Skip this question if division by zero
                }
                correctAnswer = operand1 / operand2;
                operatorSymbol = '/';
                break;
            default:
                correctAnswer = 0;
                operatorSymbol = '?';
                break;
            }

            cout << "Level " << level << " - Question " << i + 1 << ": " << operand1 << " " << operatorSymbol << " " << operand2 << " = ";

            double userAnswer;
            cin >> userAnswer;

            if (userAnswer == correctAnswer) {
                cout << "Correct!" << endl;
                score++;
            }
            else {
                cout << "Wrong. The correct answer is " << correctAnswer << "." << endl;
            }
        }

        totalScore += score;
        cout << "Level " << level << " completed. Your score: " << score << "/" << numQuestions << endl;

        if (level < 3) {
            cout << "Moving on to the next level..." << endl;
        }
    }

    cout << "Quiz completed. Your total score: " << totalScore << "/22" << endl;
}

int main() {
    setcursor(0, 0);
    srand(static_cast<unsigned>(time(nullptr)));

    do {
        system("cls");
        gotoxy(10, 5); cout << " -------------------------- ";
        gotoxy(10, 6); cout << " |      Game Selection     | ";
        gotoxy(10, 7); cout << " --------------------------";
        gotoxy(10, 9); cout << "1. Flappy Bird (Game 1)";
        gotoxy(10, 10); cout << "2. Math Quiz Game (Game 2)";
        gotoxy(10, 11); cout << "3. Instructions";
        gotoxy(10, 12); cout << "4. Quit";
        gotoxy(10, 14); cout << "Select an option: ";

        char option = getche();

        switch (option) {
        case '1':
            playGame1();
            break;
        case '2':
            system("cls");  // Clear the screen before running Game 2
            playGame2();
            break;
        case '3':
            instructions();
            break;
        case '4':
            exit(0);
        default:
            break;
        }
    } while (1);

    return 0;
}