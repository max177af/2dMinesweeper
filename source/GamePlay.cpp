#include "GamePlay.h"

using namespace sf;

void gamePlay(unsigned int width, unsigned int height, unsigned int mines)
{
    unsigned int window_width = width * 32 + 200;
    unsigned int window_height = height * 32;

    RenderWindow Game(VideoMode(window_width, window_height), "Minesweeper", Style::Default);
    Game.setFramerateLimit(60);

    GameField gameField(width, height, mines);

    Clock clock; 
    bool gameStarted = false;

    Texture texture; 
    if (!texture.loadFromFile("textures/timer/timer.png")) {
        std::cerr << "Error loading image" << std::endl;
        return;
    }

    Font font;
    if (!font.loadFromFile("fonts/ArialRegular.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return;
    }

    unsigned int texture_pos_x = width * 32 + 1;

    Sprite sprite(texture);
    sprite.setPosition(texture_pos_x, 0);

    unsigned int timer_pos_x = width * 32 + 70;

    RectangleShape save_button_field(Vector2f(150, 64));
    save_button_field.setPosition(width * 32, 32 * 2 + 1);

    RectangleShape load_button_field(Vector2f(150, 64));
    load_button_field.setPosition(width * 32, 32 * 4 + 1);

    Text save_button_text;
    save_button_text.setFont(font);
    save_button_text.setCharacterSize(30);
    save_button_text.setPosition(width * 32 + 16, 32 * 2 + 32);
    save_button_text.setFillColor(Color::White);
    save_button_text.setString("Save Game");  

    Text load_button_text;
    load_button_text.setFont(font);
    load_button_text.setCharacterSize(30);
    load_button_text.setPosition(width * 32 + 16, 32 * 4 + 32);
    load_button_text.setFillColor(Color::White);
    load_button_text.setString("Load Game");
    
    Text timer_text;
    timer_text.setFont(font);
    timer_text.setCharacterSize(24);
    timer_text.setPosition(timer_pos_x, 0);
    timer_text.setFillColor(Color::White);
    timer_text.setString("Timer:");

    Text time_output;
    time_output.setFont(font);
    time_output.setCharacterSize(24);
    time_output.setPosition(timer_pos_x, 35);
    time_output.setFillColor(Color::White);

    while (Game.isOpen())
    {
        int seconds = clock.getElapsedTime().asSeconds();
        int minutes = seconds / 60;
        seconds %= 60;
        int hours = minutes / 60;
        minutes %= 60;

        std::string timerString = std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds); 
        time_output.setString(timerString);

        Event event_game;
        while (Game.pollEvent(event_game))
        {
            if (event_game.type == Event::Closed)
            {
                Game.close();
            }
            else 
            {
                if (event_game.key.code == Keyboard::Escape)
                {
                    Game.close();
                }
                else if (event_game.type == Event::MouseButtonPressed)
                {
                    if (event_game.mouseButton.button == Mouse::Left)
                    {
                        if (!gameStarted)
                        {
                            clock.restart();
                            gameStarted = true;
                        }
                        gameField.uncover(event_game.mouseButton.x / 32, event_game.mouseButton.y / 32);
                        if (save_button_field.getGlobalBounds().contains(event_game.mouseButton.x, event_game.mouseButton.y))
                        {
                            gameField.saveGame("saves/savegame.save"); 
                        }
                        if (load_button_field.getGlobalBounds().contains(event_game.mouseButton.x, event_game.mouseButton.y))
                        {
                            gameField.loadGame("saves/savegame.save");
                        }
                    }
                    else if (event_game.mouseButton.button == Mouse::Right)
                    {
                        gameField.flag(event_game.mouseButton.x / 32, event_game.mouseButton.y / 32);
                    }
                    
                }
            }
        }
        Game.clear(Color::White);
        gameField.draw(Game);
        Game.draw(sprite);
        Game.draw(timer_text);
        Game.draw(time_output);
        Game.draw(save_button_text);
        Game.draw(load_button_text);
        Game.display();
        gameField.gameOverReset();
    }
}

void gameMenu()
{
    RenderWindow Menu(VideoMode(800, 600), "Minesweeper_Menu", Style::Default);
        
    RectangleShape menu_field(Vector2f(800, 600));

    RectangleShape play_button_field(Vector2f(200, 70));
    play_button_field.setPosition(300, 200);

    RectangleShape height_input_field(Vector2f(120, 50));
    height_input_field.setPosition(100, 400);

    RectangleShape width_input_field(Vector2f(120, 50));
    width_input_field.setPosition(340, 400);

    RectangleShape difficulty_input_field(Vector2f(120, 50));
    difficulty_input_field.setPosition(580, 400);

    Font font;
    if (!font.loadFromFile("fonts/ArialRegular.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return;
    }
    
    Text play_button_text;
    play_button_text.setFont(font);
    play_button_text.setCharacterSize(30);
    play_button_text.setPosition(315, 210);
    play_button_text.setFillColor(Color::Black);
    play_button_text.setString("Start Game");

    Text height_text;
    height_text.setFont(font);
    height_text.setCharacterSize(24);
    height_text.setPosition(15, 410);
    height_text.setFillColor(Color::Black);
    height_text.setString("Height:");

    Text width_text;
    width_text.setFont(font);
    width_text.setCharacterSize(24);
    width_text.setPosition(265, 410);
    width_text.setFillColor(Color::Black);
    width_text.setString("Width:");

    Text difficulty_text;
    difficulty_text.setFont(font);
    difficulty_text.setCharacterSize(24);
    difficulty_text.setPosition(490, 410);
    difficulty_text.setFillColor(Color::Black);
    difficulty_text.setString("Difficult:");

    Text height_input_text;
    height_input_text.setFont(font);
    height_input_text.setCharacterSize(24);
    height_input_text.setPosition(105, 410);
    height_input_text.setFillColor(Color::Black);
    std::string height_inputString;

    Text width_input_text;
    width_input_text.setFont(font);
    width_input_text.setCharacterSize(24);
    width_input_text.setPosition(345, 410);
    width_input_text.setFillColor(Color::Black);
    std::string width_inputString;

    Text difficulty_input_text;
    difficulty_input_text.setFont(font);
    difficulty_input_text.setCharacterSize(24);
    difficulty_input_text.setPosition(585, 410);
    difficulty_input_text.setFillColor(Color::Black);
    std::string difficulty_inputString;  

    Texture texture_menu; 
    if (!texture_menu.loadFromFile("textures/menu/menu.png")) {
        std::cerr << "Error loading image" << std::endl;
        return;
    }
    menu_field.setTexture(&texture_menu);

    while (Menu.isOpen())
    {
        Event event_menu;
        while (Menu.pollEvent(event_menu))
        {
            if (event_menu.type == Event::Closed)
            {
                Menu.close();
            }
            else 
            {
                if (event_menu.key.code == Keyboard::Escape)
                {
                    Menu.close();
                }
                else if (event_menu.type == Event::MouseButtonPressed)
                {
                    if (event_menu.mouseButton.button == Mouse::Left)
                    {
                        if (play_button_field.getGlobalBounds().contains(event_menu.mouseButton.x, event_menu.mouseButton.y) && !height_inputString.empty() && !width_inputString.empty() && !difficulty_inputString.empty())
                        {
                            int height = std::stoi(height_inputString);
                            int width = std::stoi(width_inputString);
                            int max_mines = std::stoi(height_inputString) * std::stoi(width_inputString);
                            int difficulty = std::stoi(difficulty_inputString);
                            int mines;

                            if (height >= 2)
                            {
                                if (difficulty == 1) 
                                    mines = max_mines / 10;    
                                else if (difficulty == 2) 
                                    mines = max_mines / 7;   
                                else if (difficulty == 3) 
                                    mines = max_mines / 5; 
                                
                                Menu.close();
                                if (!Menu.isOpen())
                                    gamePlay(width, height, mines);
                            }
                            else 
                                continue;
                            
                        }
                    }
                }
                else if (event_menu.type == Event::TextEntered)
                {
                    if (event_menu.text.unicode < 128 &&  event_menu.text.unicode != 8) // ввод символов
                    {
                        if (height_inputString.size() < 2 && height_input_field.getGlobalBounds().contains(Mouse::getPosition(Menu).x, Mouse::getPosition(Menu).y)) // ввод числового значения в поле "высота игрового поля"
                        {
                            height_inputString += static_cast<char>(event_menu.text.unicode);
                            int height_value = std::stoi(height_inputString);
                            if (height_value >= 1 && height_value <= 25) 
                                height_input_text.setString(height_inputString);
                        }
                        else if (width_inputString.size() < 2 && width_input_field.getGlobalBounds().contains(Mouse::getPosition(Menu).x, Mouse::getPosition(Menu).y)) // ввод числового значения в поле "ширина игрового поля"
                        {
                            width_inputString += static_cast<char>(event_menu.text.unicode);
                            int width_value = std::stoi(width_inputString);
                            if (width_value >= 1 && width_value <= 35) 
                                width_input_text.setString(width_inputString);
                        }
                        else if (difficulty_inputString.size() < 1 && difficulty_input_field.getGlobalBounds().contains(Mouse::getPosition(Menu).x, Mouse::getPosition(Menu).y)) // ввод числового значения в поле "количество мин на игровом поля"
                        {
                            difficulty_inputString += static_cast<char>(event_menu.text.unicode);
                            int difficulty_value = std::stoi(difficulty_inputString);
                            if (difficulty_value >= 1 && difficulty_value <= 3) 
                                difficulty_input_text.setString(difficulty_inputString);
                        }
                    }
                    else if (event_menu.text.unicode == 8) // удаление символов (backspace)
                    {
                        if (height_input_field.getGlobalBounds().contains(Mouse::getPosition(Menu).x, Mouse::getPosition(Menu).y)) // удаление одного символа значении поля "высота игрового поля"
                        {
                            if (!height_inputString.empty())
                            {
                                height_inputString.pop_back();
                                height_input_text.setString(height_inputString);
                            }
                        }
                        else if (width_input_field.getGlobalBounds().contains(Mouse::getPosition(Menu).x, Mouse::getPosition(Menu).y)) // удаление одного символа значении поля "ширина игрового поля"
                        {
                            if (!width_inputString.empty())
                            {
                                width_inputString.pop_back();
                                width_input_text.setString(width_inputString);
                            }
                        }
                        else if (difficulty_input_field.getGlobalBounds().contains(Mouse::getPosition(Menu).x, Mouse::getPosition(Menu).y)) // удаление одного символа значении поля "количество мин на игровом поля"
                        {
                            if (!difficulty_inputString.empty())
                            {
                                difficulty_inputString.pop_back();
                                difficulty_input_text.setString(difficulty_inputString);
                            }
                        }
                    }
                }
            }
        }

        Menu.clear(Color::White);
        Menu.draw(menu_field);
        Menu.draw(play_button_field);
        Menu.draw(height_input_field);
        Menu.draw(width_input_field);
        Menu.draw(difficulty_input_field);
        Menu.draw(play_button_text);
        Menu.draw(height_text);
        Menu.draw(width_text);
        Menu.draw(difficulty_text);
        Menu.draw(height_input_text); 
        Menu.draw(width_input_text); 
        Menu.draw(difficulty_input_text);
        Menu.display();
    }  
}