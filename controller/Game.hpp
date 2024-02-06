#ifndef OXO_GAME_HPP
#define OXO_GAME_HPP

#include <string>

class Game {
protected:
    char m_grid[3][3]{};
    bool m_cellsPlayed[3][3]{};
    int m_nbRounds;

public:
    // Constructor
    Game();

    // Setter
    void setAllCellsPlayed(bool ToF);

    // Getter
    char getCell(int row, int column) const;
    std::wstring getCellInWstring(int row, int column) const;
    bool isCellPlayed(int row, int column) const;
    bool isAllCellsPlayed() const;
    int getNbRounds() const;

    // Functions
    void playCell(int row, int column, char symbol);
    void autoPlay(char symbol);
    bool checkVictory(char symbol);
};


#endif //OXO_GAME_HPP
