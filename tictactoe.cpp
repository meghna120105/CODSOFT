#include <iostream>
#include <vector>

using namespace std;

const char PLAYER_X = 'X';
const char PLAYER_O = 'O';
const char EMPTY = ' ';

// Function to initialize the board
void initializeBoard(vector<vector<char>>& board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = EMPTY;
        }
    }
}

// Function to print the board
void printBoard(const vector<vector<char>>& board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << endl;
        if (i < 2) cout << "---------" << endl;
    }
}

// Check if a player has won
bool isWinner(const vector<vector<char>>& board, char player) {
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    return false;
}

// Check if the board is full
bool isBoardFull(const vector<vector<char>>& board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == EMPTY) return false;
        }
    }
    return true;
}

// Minimax algorithm to find the best move
int minimax(vector<vector<char>>& board, bool isMaximizing, int depth) {
    if (isWinner(board, PLAYER_X)) return -10 + depth;
    if (isWinner(board, PLAYER_O)) return 10 - depth;
    if (isBoardFull(board)) return 0;

    if (isMaximizing) {
        int bestScore = -1000;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER_O;
                    int score = minimax(board, false, depth + 1);
                    board[i][j] = EMPTY;
                    bestScore = max(score, bestScore);
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER_X;
                    int score = minimax(board, true, depth + 1);
                    board[i][j] = EMPTY;
                    bestScore = min(score, bestScore);
                }
            }
        }
        return bestScore;
    }
}

// Find the best move for the AI
pair<int, int> findBestMove(vector<vector<char>>& board) {
    int bestScore = -1000;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == EMPTY) {
                board[i][j] = PLAYER_O;
                int moveScore = minimax(board, false, 0);
                board[i][j] = EMPTY;
                if (moveScore > bestScore) {
                    bestScore = moveScore;
                    bestMove = {i, j};
                }
            }
        }
    }
    return bestMove;
}

int main() {
    vector<vector<char>> board(3, vector<char>(3));
    initializeBoard(board);
    
    bool playerTurn = true; // true for X, false for O
    bool gameEnded = false;

    while (!gameEnded) {
        printBoard(board);

        if (playerTurn) {
            int row, col;
            cout << "Enter row and column for X (0, 1, 2): ";
            cin >> row >> col;

            if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == EMPTY) {
                board[row][col] = PLAYER_X;
                if (isWinner(board, PLAYER_X)) {
                    printBoard(board);
                    cout << "Player X wins!" << endl;
                    gameEnded = true;
                } else if (isBoardFull(board)) {
                    printBoard(board);
                    cout << "It's a draw!" << endl;
                    gameEnded = true;
                }
                playerTurn = false;
            } else {
                cout << "Invalid move, try again." << endl;
            }
        } else {
            pair<int, int> bestMove = findBestMove(board);
            board[bestMove.first][bestMove.second] = PLAYER_O;
            if (isWinner(board, PLAYER_O)) {
                printBoard(board);
                cout << "Player O wins!" << endl;
                gameEnded = true;
            } else if (isBoardFull(board)) {
                printBoard(board);
                cout << "It's a draw!" << endl;
                gameEnded = true;
            }
            playerTurn = true;
        }
    }
    
    return 0;
}
