#include "TicTacToe3Algorithm.h"

int TicTacToe3Algorithm::bestMove(std::vector<double> gameScore)
{
    int bestVal = -1000;
    int bestMove;
    bool oMove = false;
    if (gameScore[0] == 1) oMove = false;
    if (gameScore[0] == -1) oMove = true;

    // Traverse all cells, evaluate minimax function for
    // all empty cells. And return the cell with optimal
    // value.
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // Check if cell is empty
            if (gameScore[i * 3 + j] == 0)
            {
                // Make the move
                gameScore[i * 3 + j] = 1;

                // compute evaluation function for this
                // move.
                int moveVal = minimax(gameScore, 0, oMove);

                // Undo the move
                gameScore[i * 3 + j] = 0;

                // If the value of the current move is
                // more than the best value, then update
                // best/
                if (moveVal > bestVal)
                {
                    bestMove = i * 3 + j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

int TicTacToe3Algorithm::evaluate(std::vector<double> gameScore)
{
    // Checking for Rows for X or O victory.
    for (int row = 0; row < 3; row++)
    {
        if (gameScore[row * 3 + 0] == gameScore[row * 3 + 1] &&
            gameScore[row * 3 + 1] == gameScore[row * 3 + 2])
        {
            if (gameScore[row * 3 + 0] == 1)
                return +10;
            else if (gameScore[row * 3 + 0] == -1)
                return -10;
        }
    }

    // Checking for Columns for X or O victory.
    for (int col = 0; col < 3; col++)
    {
        if (gameScore[0 * 3 + col] == gameScore[1 * 3 + col] &&
            gameScore[1 * 3 + col] == gameScore[2 * 3 + col])
        {
            if (gameScore[0 * 3 + col] == 1)
                return +10;

            else if (gameScore[0 * 3 + col] == -1)
                return -10;
        }
    }

    // Checking for Diagonals for X or O victory.
    if (gameScore[0 * 3 + 0] == gameScore[1 * 3 + 1] && gameScore[1 * 3 + 1] == gameScore[2 * 3 + 2])
    {
        if (gameScore[0 * 3 + 0] == 1)
            return +10;
        else if (gameScore[0 * 3 + 0] == -1)
            return -10;
    }

    if (gameScore[0 * 3 + 2] == gameScore[1 * 3 + 1] && gameScore[1 * 3 + 1] == gameScore[2 * 3 + 0])
    {
        if (gameScore[0 * 3 + 2] == 1)
            return +10;
        else if (gameScore[0 * 3 + 2] == -1)
            return -10;
    }

    // Else if none of them have won then return 0
    return 0;
}

int TicTacToe3Algorithm::minimax(std::vector<double> gameScore, int depth, bool isMax)
{
    int score = evaluate(gameScore);

    // If Maximizer has won the game return his/her
    // evaluated score
    if (score == 10)
        return score;

    // If Minimizer has won the game return his/her
    // evaluated score
    if (score == -10)
        return score;

    // If this maximizer's move
    if (isMax)
    {
        int best = -1000;

        // Traverse all cells
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // Check if cell is empty
                if (gameScore[i * 3 + j] == 0)
                {
                    // Make the move
                    gameScore[i * 3 + j] = 1;

                    // Call minimax recursively and choose
                    // the maximum value
                    best = std::max(best, minimax(gameScore, depth + 1, !isMax));

                    // Undo the move
                    gameScore[i * 3 + j] = 0;
                }
            }
        }
        return best;
    }

    // If this minimizer's move
    else
    {
        int best = 1000;

        // Traverse all cells
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // Check if cell is empty
                if (gameScore[i * 3 + j] == 0)
                {
                    // Make the move
                    gameScore[i * 3 + j] = -1;

                    // Call minimax recursively and choose
                    // the minimum value
                    best = std::min(best, minimax(gameScore, depth + 1, !isMax));

                    // Undo the move
                    gameScore[i * 3 + j] = 0;
                }
            }
        }
        return best;
    }
}
