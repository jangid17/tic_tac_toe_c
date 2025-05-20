#include <stdio.h>
#include <stdlib.h>

// Draw the Tic Tac Toe board
void drawBoard(char B[3][3]) {
    printf("\n\t\t\t\t\t\t\t %c | %c | %c \n", B[0][0], B[0][1], B[0][2]);
    printf("\t\t\t\t\t\t\t---|---|---\n");
    printf("\t\t\t\t\t\t\t %c | %c | %c \n", B[1][0], B[1][1], B[1][2]);
    printf("\t\t\t\t\t\t\t---|---|---\n");
    printf("\t\t\t\t\t\t\t %c | %c | %c \n\n", B[2][0], B[2][1], B[2][2]);
}

// Clear the input buffer
void clearInputBuffer() {
    while (getchar() != '\n');
}

// Check if move is valid
int isMoveValid(char B[3][3], int row, int col) {
    if (row < 0 || row > 2 || col < 0 || col > 2) return 0;
    return B[row][col] == ' ';
}

// Check the game situation
int gameSituation(char B[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (B[i][0] == B[i][1] && B[i][1] == B[i][2] && B[i][0] != ' ') return 1;
        if (B[0][i] == B[1][i] && B[1][i] == B[2][i] && B[0][i] != ' ') return 1;
    }
    if ((B[0][0] == B[1][1] && B[1][1] == B[2][2] && B[0][0] != ' ') ||
        (B[0][2] == B[1][1] && B[1][1] == B[2][0] && B[0][2] != ' ')) return 1;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (B[i][j] == ' ') return 0;

    return -1; // Draw
}

// Check if the current player can win with this move
int canWin(char B[3][3], int row, int col, char player) {
    if (B[row][(col + 1) % 3] == player && B[row][(col + 2) % 3] == player) return 1;
    if (B[(row + 1) % 3][col] == player && B[(row + 2) % 3][col] == player) return 1;
    if (row == col && B[(row + 1) % 3][(col + 1) % 3] == player && B[(row + 2) % 3][(col + 2) % 3] == player) return 1;
    if (row + col == 2 && B[(row + 1) % 3][(col + 2) % 3] == player && B[(row + 2) % 3][(col + 1) % 3] == player) return 1;
    return 0;
}

// Check if opponent can win (block them)
int canBlock(char B[3][3], int row, int col, char player) {
    char opponent = player;
    if (B[row][(col + 1) % 3] == opponent && B[row][(col + 2) % 3] == opponent) return 1;
    if (B[(row + 1) % 3][col] == opponent && B[(row + 2) % 3][col] == opponent) return 1;
    if (row == col && B[(row + 1) % 3][(col + 1) % 3] == opponent && B[(row + 2) % 3][(col + 2) % 3] == opponent) return 1;
    if (row + col == 2 && B[(row + 1) % 3][(col + 2) % 3] == opponent && B[(row + 2) % 3][(col + 1) % 3] == opponent) return 1;
    return 0;
}

// Get the computer's move
void getComputerMove(char B[3][3], int *row, int *col) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (B[i][j] == ' ' && canWin(B, i, j, 'O')) {
                *row = i; *col = j; return;
            }

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (B[i][j] == ' ' && canBlock(B, i, j, 'X')) {
                *row = i; *col = j; return;
            }

    if (B[1][1] == ' ') { *row = 1; *col = 1; return; }
    if (B[2][0] == ' ') { *row = 2; *col = 0; return; }

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (B[i][j] == ' ') {
                *row = i; *col = j; return;
            }
}

// Make the move
void makeMove(char B[3][3], int row, int col, char player) {
    B[row][col] = player;
}

int main() {
    char board[3][3] = {{' ', ' ', ' '},{' ', ' ', ' '},{' ', ' ', ' '}};
    int row, col;
    int gameOver = 0;
    int noOfPlayer;

    printf("\t\t\t\t\t\tWelcome To The Game.\n");
    printf("\t\t\t\t\t\t    |TIC TAC TOE|\n\n");

    while (1) {
        printf("Select mode:\n");
        printf("\t\t\tSingle Player(1)\t\t\t\t\tDouble Player(2)\n");
        printf("\t\t\t\t\tEnter the mode you want to play (1 or 2): ");
        if (scanf("%d", &noOfPlayer) != 1 || (noOfPlayer != 1 && noOfPlayer != 2)) {
            printf("Invalid input. Please enter 1 or 2.\n");
            clearInputBuffer();
        } else {
            break;
        }
    }

    clearInputBuffer();
    int playingPlayer = 1;

    while (!gameOver) {
        drawBoard(board);

        if (noOfPlayer == 1 && playingPlayer == 2) {
            printf("Computer's move:\n");
            getComputerMove(board, &row, &col);
        } else {
            while (1) {
                printf("Player %d's turn.\n", playingPlayer);
                printf("Enter row (0-2): ");
                if (scanf("%d", &row) != 1) {
                    printf("Invalid input. Try again.\n");
                    clearInputBuffer();
                    continue;
                }

                printf("Enter column (0-2): ");
                if (scanf("%d", &col) != 1) {
                    printf("Invalid input. Try again.\n");
                    clearInputBuffer();
                    continue;
                }

                clearInputBuffer();
                if (isMoveValid(board, row, col)) break;
                printf("Invalid move. Try again.\n");
            }
        }

        char playerChar = (playingPlayer == 1) ? 'X' : 'O';
        makeMove(board, row, col, playerChar);

        int result = gameSituation(board);
        if (result == 1) {
            drawBoard(board);
            if (noOfPlayer == 1 && playingPlayer == 2)
                printf("\t\t\t\t\t\t\tComputer wins! Better luck next time.\n");
            else
                printf("\t\t\t\t\t\t\tPlayer %d wins!\n", playingPlayer);
            gameOver = 1;
        } else if (result == -1) {
            drawBoard(board);
            printf("\t\t\t\t\t\t\tMatch Draw!\n");
            gameOver = 1;
        } else {
            playingPlayer = 3 - playingPlayer;  // Toggle between 1 and 2
        }
    }

    return 0;
}
