#include <SFML/Graphics.hpp>
#include <iostream>
#include "hexagon.h"
#include "menu.h"
using namespace std;
void tablero()
{   
    sf::RenderWindow window(sf::VideoMode(2200, 1600), "HEX!", sf::Style::Close | sf::Style::Resize);
    sf::CircleShape player(50.f, 6);
    player.setFillColor(sf::Color::Green);
    //player.setOrigin(50.f, 50.f);

    vector<Hexagon> hexaVector;
    int boardSize = 10;

    for (int i = 0; i < boardSize; i++){
        int offsetHexagon = 50;
        for (int j = 0; j < boardSize; j++){
            hexaVector.push_back(Hexagon (55.f, 300.f + 110 * i + 55 * j, 320.f + 95 * j, 10 * i + j));
        }
    }

    myGraph gr;
    // for (int i = 1; i < 15; i++){
    //     gr.is_red(i);
    // }
    gr.is_blue(11);
    gr.print_adj();

    bool turn = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            
            switch (event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    //cout << "New window width:" << event.size.width << ". New window height:" << event.size.height << endl;
                    printf("New window width: %i New window height: %i\n", event.size.width, event.size.height);
                    break;

            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
            player.move(-3.0f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
            player.move(3.0f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
            player.move(0.0f, -3.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
            player.move(0.0f, +3.0f);
        }
        //if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        //    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        //    player.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        //}


        window.clear();
        for (int i = 0; i < hexaVector.size(); i++){
            window.draw(hexaVector[i].getShape());
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePos.x < (hexaVector[i].getPositionX() + 55 + 50) &&
                mousePos.x > (hexaVector[i].getPositionX() + 55 - 50) && mousePos.y < (hexaVector[i].getPositionY() + 55 + 50) &&
                mousePos.y > (hexaVector[i].getPositionY() + 55 - 50)){
                    if (turn == true && hexaVector[i].getColored() == 0){
                        hexaVector[i].setColor(1);
                        window.draw(hexaVector[i].getShape());
                        hexaVector[i].setColored(1);
                        turn = false;
                    }
                    else if (turn == false && hexaVector[i].getColored() == 0){
                        hexaVector[i].setColor(2);
                        window.draw(hexaVector[i].getShape());
                        hexaVector[i].setColored(1);
                        turn = true;
                    }
            }
        }
        window.draw(player);
        window.display();
    }

}
