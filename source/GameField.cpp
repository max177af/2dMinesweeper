#include "GameField.h"
#include <iostream>
#include <filesystem>
#include <fstream>

//! Variable to check the number of bombs flagged.
unsigned int GameField::numFlaggedBombs = 0;

/**
 * @brief Constructor for the GameField class.
 * @param width Width of the game field.
 * @param height Height of the game field.
 * @param numMines Number of mines on the field.
 */
GameField::GameField(unsigned int width, unsigned int height, unsigned int numMines)
    : width(width), height(height), numMines(numMines), state(GameState::Playing)
{
	numFlaggedBombs = 0;
    initField();
    countAdjacentMines();
}

/**
 * @brief Resets the game field to the initial state.
 */
void GameField::reset()
{
    numFlaggedBombs = 0;
	state = GameState::Playing;
    initField();
    countAdjacentMines();
}

/**
 * @brief Checks if the game is over.
 * @return Returns true if the game is over.
 */
bool GameField::isGameOver() const
{
    return state != GameState::Playing;
}

/**
 * @brief Checks if the game is won.
 * @return Returns true if the game is won.
 */
bool GameField::isVictory() const
{
    return state == GameState::Victory;
}

/**
 * @brief Uncovers a cell on the field.
 * @param x X coordinate of the cell.
 * @param y Y coordinate of the cell.
 */
void GameField::uncover(unsigned int x, unsigned int y)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
        return;

    if (field[y][x] == CellState::Flagged)
        return;

	if (field[y][x] == CellState::FlaggedBomb)
		return;

    if (field[y][x] == CellState::Hidden)
    {
        field[y][x] = CellState::Revealed;

        if (numAdjacentMines[y][x] == 0)
        {
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    if (i == 0 && j == 0)
                        continue;
                    uncover(x + i, y + j);
                }
            }
        }
		return;
    }

	if (field[y][x] == CellState::HiddenBomb)
	{
		state = GameState::Defeat;
		return;
	}
}

/**
 * @brief Flags a cell on the field.
 * @param x X coordinate of the cell.
 * @param y Y coordinate of the cell.
 */
void GameField::flag(unsigned int x, unsigned int y)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
        return;

    if (field[y][x] == CellState::Hidden)
    {
        field[y][x] = CellState::Flagged;
    }
    else if (field[y][x] == CellState::Flagged)
    {
        field[y][x] = CellState::Hidden;
    }
	else if (field[y][x] == CellState::HiddenBomb)
    {
        field[y][x] = CellState::FlaggedBomb;
		numFlaggedBombs++;
		if (numFlaggedBombs == numMines)
			state = GameState::Victory;
    }
	else if (field[y][x] == CellState::FlaggedBomb)
    {
        field[y][x] = CellState::HiddenBomb;
		numFlaggedBombs--;
    }
}

/**
 * @brief Draws the game field and textures for cells.
 */
void GameField::draw(sf::RenderTarget& target) const
{
    sf::Texture cell_0, cell_1, cell_2, cell_3, cell_4, cell_5, cell_6, cell_7, cell_8, cell_unknown, cell_hiddenbomb, cell_flagged;
    cell_0.loadFromFile("textures/uncovered/0.png");
    cell_1.loadFromFile("textures/uncovered/1.png");
    cell_2.loadFromFile("textures/uncovered/2.png");
    cell_3.loadFromFile("textures/uncovered/3.png");
    cell_4.loadFromFile("textures/uncovered/4.png");
    cell_5.loadFromFile("textures/uncovered/5.png");
    cell_6.loadFromFile("textures/uncovered/6.png");
    cell_7.loadFromFile("textures/uncovered/7.png");
    cell_8.loadFromFile("textures/uncovered/8.png");
    cell_unknown.loadFromFile("textures/hidden/unknown.png");
    cell_hiddenbomb.loadFromFile("textures/hidden/hiddenbomb.png");
    cell_flagged.loadFromFile("textures/flagged/flagged.png");

    sf::Sprite uncovered_cell_0(cell_0);
    sf::Sprite uncovered_cell_1(cell_1);
    sf::Sprite uncovered_cell_2(cell_2);
    sf::Sprite uncovered_cell_3(cell_3);
    sf::Sprite uncovered_cell_4(cell_4);
    sf::Sprite uncovered_cell_5(cell_5);
    sf::Sprite uncovered_cell_6(cell_6);
    sf::Sprite uncovered_cell_7(cell_7);
    sf::Sprite uncovered_cell_8(cell_8);
    sf::Sprite uncovered_cell_unknown(cell_unknown);
    sf::Sprite hidden_bomb(cell_hiddenbomb);
    sf::Sprite flagged(cell_flagged);

    sf::Sprite sprite;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sf::RectangleShape cell(sf::Vector2f(32, 32));
            sprite.setPosition(j * 32, i * 32);

            if (field[i][j] == CellState::Hidden)
            {
                sprite.setTexture(cell_unknown);
            }
            else if (field[i][j] == CellState::HiddenBomb)
            {
                //sprite.setTexture(cell_hiddenbomb);
                sprite.setTexture(cell_unknown);
            }
            else if (field[i][j] == CellState::Flagged)
            {
                sprite.setTexture(cell_flagged);
            }
            else if (field[i][j] == CellState::FlaggedBomb)
            {
                sprite.setTexture(cell_flagged);
            }
            else if (field[i][j] == CellState::Revealed)
            {
                if (numAdjacentMines[i][j] >= 0)
                {
                    switch (numAdjacentMines[i][j])
                    {
                        case 0:
                            sprite.setTexture(cell_0);
                            break;
                        case 1:
                            sprite.setTexture(cell_1);
                            break;
                        case 2:
                            sprite.setTexture(cell_2);
                            break;
                        case 3:
                            sprite.setTexture(cell_3);
                        break;
                        case 4:
                            sprite.setTexture(cell_4);
                            break;
                        case 5:
                            sprite.setTexture(cell_5);
                            break;
                        case 6:
                            sprite.setTexture(cell_6);
                            break;
                        case 7:
                            sprite.setTexture(cell_7);
                            break;
                        case 8:
                            sprite.setTexture(cell_8);
                            break;
                    }
                }
            }
            target.draw(sprite);
        }
    }
}

/**
 * @brief Initializes the game field.
 */
void GameField::initField()
{
    field.clear();
    field.resize(height, std::vector<CellState>(width, CellState::Hidden));

    numAdjacentMines.clear();
    numAdjacentMines.resize(height, std::vector<unsigned int>(width, 0));

    // Place mines randomly
    for (int i = 0; i < numMines; i++)
    {
        int x = rand() % width;
        int y = rand() % height;

        while (field[y][x] == CellState::HiddenBomb)
        {
            x = rand() % width;
            y = rand() % height;
        }

        field[y][x] = CellState::HiddenBomb;
    }
	return;
}

/**
 * @brief Counts the mines adjacent to each cell.
 */
void GameField::countAdjacentMines()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (field[i][j] == CellState::Revealed)
                continue;

            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if (i + k < 0 || i + k >= height || j + l < 0 || j + l >= width)
                        continue;

                    if (field[i + k][j + l] == CellState::HiddenBomb)
                        numAdjacentMines[i][j]++;
                }
            }
        }
    }
	return;
}

/**
 * @brief Resets the game after it's over.
 */
void GameField::gameOverReset()
{
	if (state == GameState::Victory)
	{
		std::cout << "Victory!" << std::endl;
		reset();
	}
	else if (state == GameState::Defeat)
    {
		std::cout << "Game Over!" << std::endl;
        reset();
	}
	return;
}

void GameField::saveGame(const std::string& filename) 
{
    std::string saveDir = "saves/";
    std::string filePath;

    if (filename.find(saveDir) != std::string::npos) {
        filePath = filename;
    } else {
        filePath = saveDir + filename;
    }

    std::ofstream file(filePath, std::ios::binary);

    if (!file) {
        std::cerr << "Error opening file for saving: " << filePath << std::endl;
        return;
    }

    file.write((char*)&width, sizeof(unsigned int));
    file.write((char*)&height, sizeof(unsigned int));
    file.write((char*)&numMines, sizeof(unsigned int));
    file.write((char*)&numFlaggedBombs, sizeof(unsigned int));
    file.write((char*)&state, sizeof(GameState));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            file.write((char*)&field[i][j], sizeof(CellState));
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            file.write((char*)&numAdjacentMines[i][j], sizeof(unsigned int));
        }
    }

    if (!file.good()) {
        std::cerr << "Error writing to file: " << filePath << std::endl;
    }

    file.close();
}

void GameField::loadGame(const std::string& filename) 
{
    std::string saveDir = "saves/";
    std::string filePath;

    if (filename.find(saveDir) != std::string::npos) {
        filePath = filename;
    } else {
        filePath = saveDir + filename;
    }

    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file for loading: " << filePath << std::endl;
        return;
    }

    file.read((char*)&width, sizeof(unsigned int));
    file.read((char*)&height, sizeof(unsigned int));
    file.read((char*)&numMines, sizeof(unsigned int));
    file.read((char*)&numFlaggedBombs, sizeof(unsigned int));
    file.read((char*)&state, sizeof(GameState));

    field.clear();
    numAdjacentMines.clear();
    field.resize(height, std::vector<CellState>(width, CellState::Hidden));
    numAdjacentMines.resize(height, std::vector<unsigned int>(width, 0));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            file.read((char*)&field[i][j], sizeof(CellState));
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            file.read((char*)&numAdjacentMines[i][j], sizeof(unsigned int));
        }
    }

    file.close();
}