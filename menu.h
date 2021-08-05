#include <SFML/Graphics.hpp>
#include <iostream>
#define MAX_NUMBER_OF_ITEMS 4
using namespace std;
class Menu{
    private:
        int selectedItemIndex;
        sf::Font font;
        sf::Image image;
        sf::Texture texture;
        sf::Sprite sprite;
        sf::Text menu[MAX_NUMBER_OF_ITEMS];
    public:
        Menu(float width, float height){
            if(!font.loadFromFile("fuente2.ttf")){
            }
            texture.loadFromFile("hex2.jpg");
            if(!texture.loadFromFile("hex2.jpg")){
            }
            sprite.setTexture(texture);
            sprite.setScale(0.4f,0.4f);
            sprite.setPosition(840.0f,500.0f);
            
            menu[0].setFont(font);
            menu[0].setColor(sf::Color::Green);
            menu[0].setString("HEX: THE GAME");
            menu[0].setPosition(sf::Vector2f(width /2,height /(MAX_NUMBER_OF_ITEMS + 1) * 1));


            menu[1].setFont(font);
            menu[1].setColor(sf::Color::White);
            menu[1].setString("Play");
            menu[1].setPosition(sf::Vector2f(width /2+70,(height /(MAX_NUMBER_OF_ITEMS + 1) * 2)+200));

            menu[2].setFont(font);
            menu[2].setColor(sf::Color::White);
            menu[2].setString("Instrucciones");
            menu[2].setPosition(sf::Vector2f(width /2+20,(height /(MAX_NUMBER_OF_ITEMS + 1) * 3)-50));

            menu[3].setFont(font);
            menu[3].setColor(sf::Color::White);
            menu[3].setString("Salir");
            menu[3].setPosition(sf::Vector2f(width /2+70,(height /(MAX_NUMBER_OF_ITEMS + 1) *3)+30));

            selectedItemIndex = 0;
        }
        ~Menu(){}
        
        void draw(sf::RenderWindow &window){
            for(int x=0;x<MAX_NUMBER_OF_ITEMS;x++){
                window.draw(menu[x]);
            }
            window.draw(sprite);
        }
        void Moveup(){
            if(selectedItemIndex- 1>0){
                menu[selectedItemIndex].setColor(sf::Color::White);
                selectedItemIndex--;
                menu[selectedItemIndex].setColor(sf::Color::Red);
            }
        }
        void MoveDown(){
            if(selectedItemIndex +1<MAX_NUMBER_OF_ITEMS){
                if(selectedItemIndex!=0){
                menu[selectedItemIndex].setColor(sf::Color::White);
                selectedItemIndex++;
                menu[selectedItemIndex].setColor(sf::Color::Red);
                }
                else {selectedItemIndex++;
                    menu[selectedItemIndex].setColor(sf::Color::Red);
                }
            }
        }
        int get_Pressed_Item(){
            return selectedItemIndex;
        }


};

