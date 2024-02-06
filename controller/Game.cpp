#include "Game.hpp"
#include <chrono>
#include <thread>
#include "MRandom.hpp"

/** * * * * * * **
 *  CONSTRUCTOR  *
 ** * * * * * * **/
Game::Game() : m_nbRounds(0) {
    //Set grid
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            m_grid[r][c] = ' ';
            m_cellsPlayed[r][c] = false;
        }
    }
}

/** * * * * * * **
 *    SETTER     *
 ** * * * * * * **/
void Game::setAllCellsPlayed(bool ToF) {
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            m_cellsPlayed[r][c] = ToF;
        }
    }
}

/** * * * * * * **
 *    GETTER     *
 ** * * * * * * **/
char Game::getCell(int row, int column) const {
    return m_grid[row][column];
}

std::wstring Game::getCellInWstring(int row, int column) const {
    char tempCharArray[] = {getCell(row, column)};
    std::wstring tempWstr( &tempCharArray[0], &tempCharArray[1]);
    return tempWstr;
}

bool Game::isCellPlayed(int row, int column) const {
    return m_cellsPlayed[row][column];
}

bool Game::isAllCellsPlayed() const {
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if(!m_cellsPlayed[r][c]){
                return false;
            }
        }
    }
    return true;
}

int Game::getNbRounds() const {
    return m_nbRounds;
}

/** * * * * * * **
 *   FUNCTIONS   *
 ** * * * * * * **/
 // This method is used to make a player play
void Game::playCell(int row, int column, char symbol) {
    m_grid[row][column] = symbol;
    m_cellsPlayed[row][column] = true;
    m_nbRounds++;
}

// This method is used to make the computer (called 'AI' in the game) play
void Game::autoPlay(char symbol) {
    // Simulating game time (between 1 and 2s)
    int sleepTime = randomInt(1000, 2000);
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));

    // Priority 1: Align a 3rd symbol
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (m_grid[r][c] == ' ') {
                m_grid[r][c] = symbol;
                if (checkVictory(symbol)) {
                    playCell(r, c, symbol);
                    return;
                }
                m_grid[r][c] = ' ';
            }
        }
    }

    // Priority 2: Block the opponent if he has 2 symbols lined up
    char opponentSymbol = (symbol == 'X') ? 'O' : 'X';
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (m_grid[r][c] == ' ') {
                m_grid[r][c] = opponentSymbol;
                if (checkVictory(opponentSymbol)) {
                    playCell(r, c, symbol);
                    return;
                }
                m_grid[r][c] = ' ';
            }
        }
    }

    // Priority 3: Play in a random cell
    int row, column;
    do {
        row = randomInt(0, 2);
        column = randomInt(0, 2);
    } while (m_grid[row][column] != ' ');
    playCell(row, column, symbol);
}

bool Game::checkVictory(char symbol) {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if ((m_grid[i][0] == symbol && m_grid[i][1] == symbol && m_grid[i][2] == symbol) ||
            (m_grid[0][i] == symbol && m_grid[1][i] == symbol && m_grid[2][i] == symbol)) {
            return true; //Victory on a row or a column
        }
    }

    // Check diagonal
    if ((m_grid[0][0] == symbol && m_grid[1][1] == symbol && m_grid[2][2] == symbol) ||
        (m_grid[0][2] == symbol && m_grid[1][1] == symbol && m_grid[2][0] == symbol)) {
        return true; //Victory on a diagonal
    }

    // No victory detected
    return false;
}


