/*
    Name: Nikolas
    Surname: Antoniou
    ID: U234N0848
    Project Name: Tic Tac Toe - Assignment 2
    Course: COMP-113
    Date: 19/01/2025
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// structure declaration
class TicTacToe
{
    public:
        TicTacToe(); // constructor - initializes the board of the game
        bool PlayMove(int Player, int row, int col); // player's move
        int Winner() const; // check if there is a winner
        bool GameOver() const; // game over check
        void DisplayBoard() const; // display
        void Comp_move(int level, int &row, int &col); // computer's move

    private:
        int NoOfMoves; // number of moves 
        int Board[3][3]; // matrix which stores the board
        bool check_move(int row, int col) const; // checking if the move made is valid
        void random_move(int &row, int &col) const; // random move
        bool winning_move(int Player, int &row, int &col); // checking if there is a winning move
};

// constructor
TicTacToe::TicTacToe()
{
    NoOfMoves = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Board[i][j] = 0;
        }
    }
}

// checking if the move is valid
bool TicTacToe::check_move(int row, int col) const
{
    // making sure the positions are correct
    return (row >= 0 && row < 3 && col >= 0 && col < 3 && Board[row][col] == 0);
}

// player's move
bool TicTacToe::PlayMove(int Player, int row, int col)
{
    // checking the positions
    if (!check_move(row, col))
    {
        return false;
    }
    Board[row][col] = Player;
    NoOfMoves++;
    return true;
}

// checking for a winner
int TicTacToe::Winner() const
{
    // checking for the winner in the matrix
    for (int i = 0; i < 3; i++)
    {
        if (Board[i][0] != 0 && Board[i][0] == Board[i][1] && Board[i][1] == Board[i][2])
        {
            return Board[i][0];
        }

        if (Board[0][i] != 0 && Board[0][i] == Board[1][i] && Board[1][i] == Board[2][i])
        {
            return Board[0][i];
        }
    }

    if (Board[0][0] != 0 && Board[0][0] == Board[1][1] && Board[1][1] == Board[2][2])
    {
        return Board[0][0];
    }

    if (Board[0][2] != 0 && Board[0][2] == Board[1][1] && Board[1][1] == Board[2][0])
    {
        return Board[0][2];
    }

    return 0;
}

// game over check
bool TicTacToe::GameOver() const
{
    return Winner() != 0 || NoOfMoves == 9;
}

// computer's random move
void TicTacToe::random_move(int &row, int &col) const
{
    do
    {
        row = rand() % 3;
        col = rand() % 3;
    } while (!check_move(row, col));
}

// checking for a winning move
bool TicTacToe::winning_move(int Player, int &row, int &col)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (check_move(i, j))
            {
                Board[i][j] = Player;
                if (Winner() == Player)
                {
                    Board[i][j] = 0;
                    row = i;
                    col = j;
                    return true;
                }
                Board[i][j] = 0;
            }
        }
    }
    return false;
}

// computer's move based on level
void TicTacToe::Comp_move(int level, int &row, int &col)
{
    if (level == 1)
    {
        random_move(row, col);
    }
    else if (level == 2)
    {
        if (!winning_move(2, row, col) && !winning_move(1, row, col))
        {
            random_move(row, col);
        }
    }
    else
    {
        if (winning_move(2, row, col) || winning_move(1, row, col))
        {
            return;
        }

        if (check_move(1, 1))
        {
            row = 1;
            col = 1;
        }
        else
        {
            random_move(row, col);
        }
    }
}

// clearing the screen
void ClearScreen()
{
#ifdef _WIN32
    system("CLS");
#else
    system("clear");
#endif
}

// displaying the board
void TicTacToe::DisplayBoard() const
{
    ClearScreen();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (Board[i][j] == 0)
            {
                cout << "   "; // Empty cell
            }
            else if (Board[i][j] == 1)
            {
                cout << " X "; // Player X
            }
            else
            {
                cout << " O "; // Player O
            }

            if (j < 2) cout << "|"; // Vertical divider
        }
        cout << endl;
        if (i < 2) cout << "---+---+---" << endl; // Horizontal divider
    }
}

// main function
int main()
{
    srand(time(0));
    // declare the object
    TicTacToe mygame;
    // declare the difficulty level, the rows, and the columns
    int level, row, col;
    // declare the player
    int Player = 1;
    string name;

    // prompt the user to enter their name
    cout << "WELCOME TO THE TIC-TAC-TOE GAME!\n";
    cout << "Please enter your name: ";
    getline(cin, name);

    // prompt for difficulty level
    cout << "Hello, " << name << "! Please select a level:\n";
    cout << "1.) Nikolas Level - Easy\n";
    cout << "2.) Classic Level\n";
    cout << "3.) Mission Impossible\n";
    cout << "Give me your choice (1-3): ";
    cin >> level;

    // check if the level is invalid
    while (level < 1 || level > 3)
    {
        cout << "Invalid level, please re-enter your choice (1-3): ";
        cin >> level;
    }

    // game
    while (!mygame.GameOver())
    {
        mygame.DisplayBoard();
        if (Player == 1)
        {
            cout << name << ", enter your move (row, col): ";
            cin >> row >> col;
            if (!mygame.PlayMove(Player, row, col))
            {
                cout << "Invalid Move! Please try again!\n";
                continue;
            }
        }
        else
        {
            mygame.Comp_move(level, row, col);
            mygame.PlayMove(Player, row, col);
            cout << "Computer moves to (" << row << ", " << col << ").\n";
        }
        Player = 3 - Player;
    }

    // display the game
    mygame.DisplayBoard();
    int winner = mygame.Winner();
    if (winner == 1)
    {
        cout << "Congratulations, " << name << "! You made the computer look stupid!\n";
    }
    else if (winner == 2)
    {
        cout << "AH HA HA HA! YOU LOST! OOPSIE!\n";
    }
    else
    {
        cout << "OMG - IT IS A DRAW\n";
    }

    return 0;
}
