#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <set>
#include <utility>
#include <SFML/Graphics.hpp>
#include <cstdlib>
 
using namespace std;
 
class Hexagon{
private:
    sf::CircleShape h;
    float diameter;
    float pos_x;
    float pos_y;
    bool colored;
    int color; // 0 if red, 1 if blue
    int number; // para idenfiticar con el algoritmo para la computadora
public:
    Hexagon() = default;
    Hexagon(float d, float x, float y, int n){
        number = n;
        diameter = d;
        pos_x = x;
        pos_y = y;
        h = sf::CircleShape (diameter, 6);
        h.setPosition(pos_x, pos_y);
        h.setFillColor(sf::Color::White);
        colored = false;
        color = 2;
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
 
    int getColor(){
        return color;
    }
 
    void setColor(int n){
        if(n == 1){
            h.setFillColor(sf::Color::Red);
            color = 0;
        }
        else if(n == 2){
            h.setFillColor(sf::Color::Blue);
            color = 1;
        }
        else if(n == 0){
            h.setFillColor(sf::Color::White);
            color = 2;
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
