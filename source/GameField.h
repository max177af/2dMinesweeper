#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Enums.h"

class GameField {
    public:
        GameField(unsigned int width, unsigned int height, unsigned int numMines);
        void reset();
        bool isGameOver() const;
        bool isVictory() const;
        void uncover(unsigned int x, unsigned int y);
        void flag(unsigned int x, unsigned int y);
        void draw(sf::RenderTarget& target) const;
        void gameOverReset();
        void saveGame(const std::string& filename);
        void loadGame(const std::string& filename);

    private:
        void initField();
        void countAdjacentMines();
        std::vector<std::vector<CellState>> field;
        std::vector<std::vector<unsigned int>> numAdjacentMines;
        static unsigned int numFlaggedBombs;
        unsigned int width;
        unsigned int height;
        unsigned int numMines;
        GameState state;
    };
