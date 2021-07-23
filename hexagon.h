#include <SFML/Graphics.hpp>
#include "graph.h"

using namespace std;

class Hexagon{
private:
    sf::CircleShape h;
    float diameter;
    float pos_x;
    float pos_y;
    bool colored;
    int number;
public:
    Hexagon(float d, float x, float y, int n){
        number = n;
        diameter = d;
        pos_x = x;
        pos_y = y;
        h = sf::CircleShape (diameter, 6);
        h.setPosition(pos_x, pos_y);
        h.setFillColor(sf::Color::White);
        colored = false;
    }
    sf::CircleShape getShape(){
        return h;
    }

    float getPositionX(){
        return pos_x;
    }

    float getPositionY(){
        return pos_y;
    }

    bool getColored(){
        return colored;
    }

    void setColor(int n){
        if(n == 1){
            h.setFillColor(sf::Color::Red);
        }
        else if(n == 2){
            h.setFillColor(sf::Color::Blue);
        }
        else if(n == 0){
            h.setFillColor(sf::Color::White);
        }
    }

    void setColored(int n){
        if (n == 1){
            colored = 1;
        }
        else if (n == 0){
            colored = 0;
        }
    }
};