#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Menu.h"
#include "Player.h"
#include "Bullet.h"
#include "Gameover.h"

#define GAME_MENU 0
#define GAME_PLAY 1
#define GAME_SCOREBOARD 2
#define GAME_OVER 3

using namespace sf;
void setTiles();
void setWalls();
void setstars();

std::vector<std::vector<int>> tiles;

sf::RectangleShape wall;
std::vector<sf::RectangleShape> walls;

sf::CircleShape star;
std::vector<sf::CircleShape> stars;

using namespace sf;

Vector2f normalize(const Vector2f& source)
{
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0)
        return Vector2f(source.x / length, source.y / length);
    else
        return source;
}

int main()
{
    RenderWindow window(VideoMode(1600,720), "Game", Style::Titlebar | Style::Close);
    window.setFramerateLimit(60);
    Menu menu(window.getSize().x, window.getSize().y);
    Gameover gameover(window.getSize().x, window.getSize().y);

    sf::Texture texturebg;
    if (!texturebg.loadFromFile("menu.PNG")) //ใส่background
    {
        //haddle error
    }
    sf::Sprite background;
    background.setTexture(texturebg);

    sf::Music music;
    if (!music.openFromFile("Mainmusic.OGG"))
    {
        std::cout << "ERROR" << std::endl;
    }

    music.play();

    sf::SoundBuffer collectsound;
    if (!collectsound.loadFromFile("collectsound.OGG"))
    {
        std::cout << "ERROR" << std::endl;
    }

    sf::Sound sound;
    sound.setBuffer(collectsound);

    //map
    sf::Texture mapTex;
    sf::Sprite map;
    mapTex.loadFromFile("background.PNG");
    map.setTexture(mapTex);

    //game over
    sf::Texture gameoverTex;
    sf::Sprite gameoverbg;
    gameoverTex.loadFromFile("gameover.PNG");
    gameoverbg.setTexture(gameoverTex);

    //RectangleShape wall;
    wall.setFillColor(sf::Color::Transparent);
    wall.setSize(sf::Vector2f(40.f, 40.f));
    setTiles();
    setWalls();

    //star
    star.setRadius(12.f);   
    sf::Texture money;
    if (!money.loadFromFile("money.PNG"))
    {
        std::cout << "ERROR ERROR ERROR" << std::endl;
    }
    star.setTexture(&money);
    setstars();

    //item
    sf::Texture pngtime2;
    pngtime2.loadFromFile("scoretime2.PNG");
    sf::Sprite time2;
    time2.setTexture(pngtime2);
    time2.setScale(.07f, .07f);
    time2.setPosition(1200, (rand() % (70 + 1 - 10)) + 10);

    sf::Texture pngitem;
    pngitem.loadFromFile("sunny.PNG");
    sf::Sprite item;
    item.setTexture(pngitem);
    item.setScale(.07f, .07f);
    item.setPosition((rand() % (70 + 1 - 10)) + 10, 520);

    //animation
    float movementSpeed = 6.f;
    float preWidth = 115.f;
    float preHeight = 102.f;
    float width = 86.f;
    float height = 155.f;
    bool moving = false;
    int standNum = 1;
    int moveNum = 1;
    bool turnLeft = false;

    IntRect currentFrame = IntRect(preWidth, preHeight, width, height);
    Clock aniTime;

    sf::Texture texture;
    sf::Sprite sprite;
    texture.loadFromFile("player.PNG");
    sprite.setTexture(texture);
    sprite.setTextureRect(currentFrame);
    sprite.scale(.30f, .30f);
    sprite.setPosition(45.f, 45.f);

    int iPos = sprite.getPosition().x;
    int jPos = sprite.getPosition().y;

    sf::Vector2f playerPosition = sf::Vector2f(iPos, jPos);

    //collision wall
    FloatRect nextPos;

    //score
    int score = 0;

    sf::Font puimek;
    puimek.loadFromFile("puimek.ttf");

    sf::Text lblScore;
    lblScore.setCharacterSize(45);
    lblScore.setPosition({ 1335,270 });
    lblScore.setFont(puimek);
    lblScore.setFillColor(sf::Color::White);
    lblScore.setString("Score : " + to_string(score));

    //exit while play game
    sf::Text exit;
    exit.setCharacterSize(50);
    exit.setPosition({ 1390,365 });
    exit.setFont(puimek);
    exit.setFillColor(sf::Color::White);
    exit.setString("EXIT");

    //enemy
    sf::Texture preenemy;
    sf::Sprite enemy;
    preenemy.loadFromFile("enemy.PNG");
    enemy.setTexture(preenemy);
    enemy.scale(.2f, .2f);
    enemy.setPosition(1000.f, 600.f);

    Vector2f dir;
    Vector2f dir_norm;

    int xPos = enemy.getPosition().x;
    int yPos = enemy.getPosition().y;

    sf::Vector2f enemyPosition = sf::Vector2f(xPos, yPos);
    dir = playerPosition - enemyPosition;
    dir_norm = normalize(dir);

    float enemyspeed = 0.003f;

    //bullet
    //define object
    std::vector<Bullet> bulletVec;

    std::vector<sf::RectangleShape> bullet;

    bool isFiring = false;

    int game_state = GAME_MENU;

    while (window.isOpen())
    {   
        if(game_state == GAME_MENU) 
        {
            Event ev;
            while (window.pollEvent(ev)) {
                
                if (ev.type == Event::Closed) window.close();
                
                switch (ev.type) {
                    case sf::Event::KeyReleased:
                        switch (ev.key.code) {
                            case sf::Keyboard::Up:
                                menu.MoveUp();
                                break;

                            case sf::Keyboard::Down:
                                menu.MoveDown();
                                break;

                            case sf::Keyboard::Return:
                                switch (menu.GetPressedItem()) 
                                {
                                    case 0:
                                        std::cout << "PLAY has been pressed" << std::endl;
                                        game_state = GAME_PLAY;
                                        break;
                                    
                                    case 1:
                                        std::cout << "Leaderboard has been pressed" << std::endl;
                                        //game_state = GAME_SCOREBOARD;
                                        break;
                                    
                                    case 2:
                                        window.close();
                                        break;
                                }
                                break;
                        }
                        break;
                }
            }
        }
        if (game_state == GAME_PLAY)
        {
            Event ev;
            while (window.pollEvent(ev)) {
                
                if (ev.type == Event::Closed) window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                isFiring = true;
            }

            if (Keyboard::isKeyPressed(Keyboard::A))
            {
                sprite.move(-movementSpeed, 0.f);
                moving = true;
                turnLeft = true;

                if (Keyboard::isKeyPressed(Keyboard::W))
                {
                    sprite.move(0.f, -movementSpeed);
                }
                else if (Keyboard::isKeyPressed(Keyboard::S))
                {
                    sprite.move(0.f, movementSpeed);
                }
            }
            else if (Keyboard::isKeyPressed(Keyboard::D))
            {
                sprite.move(movementSpeed, 0.f);
                moving = true;
                turnLeft = false;
                if (Keyboard::isKeyPressed(Keyboard::W))
                {
                    sprite.move(0.f, -movementSpeed);
                }
                else if (Keyboard::isKeyPressed(Keyboard::S))
                {
                    sprite.move(0.f, movementSpeed);
                }
            }
            else if (Keyboard::isKeyPressed(Keyboard::W))
            {
                sprite.move(0.f, -movementSpeed);
                moving = true;
            }
            else if (Keyboard::isKeyPressed(Keyboard::S))
            {
                sprite.move(0.f, movementSpeed);
                moving = true;
            }
            else
            {
                moving = false;
            }
            if (standNum >= 5)
            {
                standNum = 1;
            }
            if (moveNum >= 7)
            {
                moveNum = 1;
            }
            if (aniTime.getElapsedTime().asSeconds() >= 0.1f)
            {
                if (moving == false)
                {
                    moveNum = 1;
                    preHeight = 102.f;
                    width = 86.f;
                    switch (standNum)
                    {
                    case 1: preWidth = 271.f;
                        break;
                    case 2: preWidth = 421.f;
                        break;
                    case 3: preWidth = 573.f;
                        break;
                    case 4: preWidth = 115.f;
                        break;
                    default:
                        break;
                    }
                    standNum++;
                }
                if (moving == true)
                {
                    standNum = 1;
                    preHeight = 332.f;
                    width = 91.f;
                    switch (moveNum)
                    {
                    case 1: preWidth = 113.f;
                        break;
                    case 2: preWidth = 272.f;
                        break;
                    case 3: preWidth = 424.f;
                        break;
                    case 4: preWidth = 576.f;
                        break;
                    case 5: preWidth = 735.f;
                        break;
                    case 6: preWidth = 891.f;
                        break;
                    default:
                        break;
                    }
                    moveNum++;
                }
                if (turnLeft == false)
                {
                    currentFrame = IntRect(preWidth, preHeight, width, height);
                }
                else if (turnLeft == true)
                {
                    currentFrame = IntRect(preWidth + width, preHeight, -width, height);
                }
                sprite.setTextureRect(currentFrame);
                aniTime.restart();
            }
            //exit while play
            if (Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                if (Keyboard::isKeyPressed(sf::Keyboard::Home))
                {
                    window.close();
                }
            }

            //collision wall
            for (auto& wall : walls)
            {
                FloatRect playerBounds = sprite.getGlobalBounds();
                FloatRect wallBounds = wall.getGlobalBounds();

                nextPos = playerBounds;

                if (wallBounds.intersects(nextPos))
                {
                    //right
                    if (playerBounds.left < wallBounds.left
                        && playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
                        && playerBounds.top < wallBounds.top + wallBounds.height
                        && playerBounds.top + playerBounds.height > wallBounds.top)
                    {
                        //movementSpeed = 0.f;
                        sprite.setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
                    }
                    //left
                    else if (playerBounds.left > wallBounds.left
                        && playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
                        && playerBounds.top < wallBounds.top + wallBounds.height
                        && playerBounds.top + playerBounds.height > wallBounds.top)
                    {
                        //movementSpeed = 0.f;
                        sprite.setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
                    }
                    //bottom
                    if (playerBounds.top < wallBounds.top
                        && playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
                        && playerBounds.left < wallBounds.left + wallBounds.width
                        && playerBounds.left + playerBounds.width > wallBounds.left)
                    {
                        //movementSpeed = 0.f;
                        sprite.setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
                    }
                    //top
                    else if (playerBounds.top > wallBounds.top
                        && playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
                        && playerBounds.left < wallBounds.left + wallBounds.width
                        && playerBounds.left + playerBounds.width > wallBounds.left)
                    {
                        //movementSpeed = 0.f;
                        sprite.setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
                    }
                }
            }
            //enemy move
            dir = sprite.getPosition() - enemy.getPosition();
            enemy.move(enemyspeed * dir);

            //enemy collision wall
            //left
            if (enemy.getPosition().x < 0.f)
            {
                enemy.setPosition(0.f, enemy.getPosition().y);
                if (enemy.getPosition().x == 0)
                {
                    enemy.move(enemyspeed * dir);
                }
            }
            //top
            if (enemy.getPosition().y < 0.f)
            {
                enemy.setPosition(enemy.getPosition().x, 0.f);
                if (enemy.getPosition().y == 0)
                {
                    enemy.move(enemyspeed * dir);
                }
            }
            //right
            if (enemy.getPosition().x + enemy.getGlobalBounds().width > 1280)
            {
                enemy.setPosition(1280 - enemy.getGlobalBounds().width, enemy.getPosition().y);
                if (enemy.getPosition().x > 1280)
                {
                    enemy.move(enemyspeed * dir);
                }
            }
            //bottom
            if (enemy.getPosition().y + enemy.getGlobalBounds().height > 720)
            {
                enemy.setPosition(enemy.getPosition().x, 720 - enemy.getGlobalBounds().height);
                if (enemy.getPosition().y > 720)
                {
                    enemy.move(enemyspeed * dir);
                }
            }
            //collision star
            for (auto& star : stars)
            {
                FloatRect playerBounds = sprite.getGlobalBounds();
                FloatRect starBounds = star.getGlobalBounds();

                nextPos = playerBounds;
                //score
                if (starBounds.intersects(nextPos))
                {
                    sound.play();
                    score = score + 2;
                    lblScore.setString("Score : " + to_string(score));
                    star.setPosition(sf::Vector2f(4234432, 4234423));
                }
            }

            //collision time2
            FloatRect time2Bounds = time2.getGlobalBounds();
            if (time2Bounds.intersects(nextPos))
            {
                score = score * 2;
                lblScore.setString("Score : " + to_string(score));
                time2.setPosition(sf::Vector2f(4234432, 4234423));
            }

            //collision item
            FloatRect itemBounds = item.getGlobalBounds();
            if (itemBounds.intersects(nextPos))
            {
                //skill
                score = score * 10;
                lblScore.setString("Score : " + to_string(score));
                item.setPosition(sf::Vector2f(4234432, 4234423));
            }

            //collision enemy
            FloatRect playerBounds = sprite.getGlobalBounds();
            FloatRect enemyBounds = enemy.getGlobalBounds();
            nextPos = playerBounds;
            if (enemyBounds.intersects(nextPos))
            {
                //sound
                game_state == GAME_OVER;
            }

            //collision screen
            //left
            if (sprite.getPosition().x < 0.f)
                sprite.setPosition(0.f, sprite.getPosition().y);
            //top
            if (sprite.getPosition().y < 0.f)
                sprite.setPosition(sprite.getPosition().x, 0.f);
            //right
            if (sprite.getPosition().x + sprite.getGlobalBounds().width > 1280)
                sprite.setPosition(1280 - sprite.getGlobalBounds().width, sprite.getPosition().y);
            //bottom
            if (sprite.getPosition().y + sprite.getGlobalBounds().height > 720)
                sprite.setPosition(sprite.getPosition().x, 720 - sprite.getGlobalBounds().height);

            //bullet
            if (isFiring == true)
            {
                Bullet newBullet(sf::Vector2f(30, 10));
                newBullet.setPos(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y));
                bulletVec.push_back(newBullet);
                isFiring = false;
            }
        }  
        
        /*if (game_state == GAME_SCOREBOARD)
        {

        }*/

        if (game_state == GAME_OVER)
        {
            Event ev;
            while (window.pollEvent(ev))
            {
                switch (ev.type)
                {
                case sf::Event::KeyReleased:
                    switch (ev.key.code)
                    {
                    case sf::Keyboard::Up:
                        gameover.MoveUp();
                        break;

                    case sf::Keyboard::Down:
                        gameover.MoveDown();
                        break;

                    case sf::Keyboard::Return:
                        switch (menu.GetPressedItem())
                        {
                        case 0:
                            std::cout << "SAVE SCORE has been pressed" << std::endl;
                            //save score
                            break;

                        case 1:
                            std::cout << "PLAY AGAIN has been pressed" << std::endl;
                            //game_state = GAME_PLAY
                            break;

                        case 2:
                            game_state = GAME_MENU;
                            break;
                        }
                        break;
                    }
                    break;
                }
            }
        }

        //collision enemy
        FloatRect playerBounds = sprite.getGlobalBounds();
        FloatRect enemyBounds = enemy.getGlobalBounds();
        nextPos = playerBounds;
        if (enemyBounds.intersects(nextPos))
        {
            game_state == GAME_OVER;
        }

        window.clear();

        if (game_state == GAME_MENU) 
        {
            /* วาดเมนู */
            window.draw(background);
            menu.draw(window);
        } 
        if (game_state == GAME_PLAY) 
        {
            /* วาดเกม (ผู้เล่น, ศัตรู, ไอเทม) */
            window.draw(map);
            for (auto& wall : walls)
            {
                window.draw(wall);
            }
            for (auto& star : stars)
            {
                window.draw(star);
            }
            window.draw(sprite);
            window.draw(enemy);
            window.draw(item);
            window.draw(time2);
            for (int i = 0;i < bulletVec.size();i++)
            {
                bulletVec[i].draw(window);
                bulletVec[i].fire(3);
            }
            for (int i = 0;i < bulletVec.size();i++)
            {
                if (bulletVec[i].getRight() >= enemy.getPosition().x &&
                    bulletVec[i].getTop() < enemy.getPosition().y + enemy.getScale().y &&
                    bulletVec[i].getBottom() > enemy.getPosition().y)
                {
                    enemy.setPosition(sf::Vector2f(4234432, 4234423));
                    bulletVec[i].setPos(sf::Vector2f(4234432, 4234423));
                }
                FloatRect wallBounds = wall.getGlobalBounds();
                if (bulletVec[i].getRight() == wallBounds.left ||
                    bulletVec[i].getTop() == wallBounds.top ||
                    bulletVec[i].getBottom() == wallBounds.top)
                {
                    bulletVec[i].setPos(sf::Vector2f(4234432, 4234423));
                }
            }
            window.draw(lblScore);
            window.draw(exit);
        }
        if (game_state == GAME_OVER)
        {
            window.draw(gameoverbg);
            gameover.draw(window);
        }
        window.display();
    }
    return 0;
}

void setTiles()
{
    tiles = {
         {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
         {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
         {1,0,1,1,0,1,1,1,1,1,0,0,1,1,1,0,1,1,1,0,0,1,1,1,1,1,1,0,1,1,0,1},
         {1,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1},
         {1,0,0,0,1,1,0,1,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,1,1,0,1,1,0,0,0,1},
         {1,0,0,1,1,0,0,0,0,1,0,0,0,1,1,0,1,1,0,0,0,1,0,0,0,0,0,1,1,0,0,1},
         {1,0,1,1,0,0,1,0,0,1,0,0,0,1,1,0,1,1,0,0,0,1,0,0,1,1,0,0,1,1,0,1},
         {1,0,1,0,0,1,1,1,0,1,0,0,1,1,1,0,1,1,1,0,0,1,0,1,1,1,1,0,0,1,0,1},
         {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
         {1,0,1,1,1,1,1,0,0,1,0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,1,1,1,1,1,0,1},
         {1,0,1,0,0,0,0,0,1,1,1,0,0,1,1,0,1,1,0,0,1,1,1,0,0,0,0,0,0,1,0,1},
         {1,0,1,0,1,1,0,0,0,1,0,0,0,1,1,0,1,1,0,0,0,1,0,0,0,0,1,1,0,1,0,1},
         {1,0,1,0,1,1,0,0,0,0,0,0,1,1,1,0,1,1,1,0,0,0,0,0,0,0,1,1,0,1,0,1},
         {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
         {1,0,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,1,1,0,1},
         {1,0,1,1,0,1,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1,1,0,1,1,1,1,0,1,1,0,1},
         {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
         {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
}

void setWalls()
{
    for (int x = 0;x < 32;x++)
    {
        for (int y = 0;y < 18;y++)
        {
            if (tiles[y][x] == 1)
            {
                wall.setPosition(40.f * x, 40.f * y);
                walls.push_back(wall);
            }
        }
    }
}

void setstars()
{
    for (int x = 0;x < 32;x++)
    {
        for (int y = 0;y < 18;y++)
        {
            if (tiles[y][x] == 0)
            {
                //ใส่ดาว
                star.setPosition((40.5f * x) + 2.5, (40.5f * y) + 7);
                stars.push_back(star);
            }
        }
    }
}