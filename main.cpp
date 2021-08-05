#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "graph.h"
#include "menu.h"
using namespace std;
string resultados;

int resultado(sf::RenderWindow* window,string resultado,int width, int height){
    sf::Font font;
    sf::Text texto[3];
    bool mantenimiento = false;
    int veracidad=0;
    texto[0].setString(resultado);
    texto[1].setString("Preciona la tecla arriba para volver al inicio");
    texto[2].setString("Presione la tecla abajo para salir");

    texto[0].setScale(2.0f,2.0f);
    
    texto[0].setPosition(sf::Vector2f(width /2-100,height /(MAX_NUMBER_OF_ITEMS + 1) * 2));
    texto[1].setPosition(sf::Vector2f(width /2-300,height /(MAX_NUMBER_OF_ITEMS + 1) * 2.5));
    texto[2].setPosition(sf::Vector2f(width /2-250,(height /(MAX_NUMBER_OF_ITEMS + 1) * 2.5)+100));


    if(!font.loadFromFile("fuente2.ttf")){
                //
    }
    for(auto &i:texto)
        i.setFont(font);
    if(resultado == "GANASTE")
        texto[0].setColor(sf::Color::White);
    else 
        texto[0].setColor(sf::Color::Red);
    while(!mantenimiento){
        sf::Event event;
        while(window->pollEvent(event)){
            switch(event.type){
                case sf::Event::KeyReleased:
                    switch(event.key.code){
                        case sf::Keyboard::Up:
                            mantenimiento = true;
                            break;
                        case sf::Keyboard::Down:
                            mantenimiento = true;
                            veracidad = 3;
                            break;   
                        }
                }
            }
        window->clear();
        for(auto &i:texto){
            window->draw(i);
        }
        window->display();

   }
   return veracidad;
}



void tablero(sf::RenderWindow *window)
{   
    sf::Music buffer;
    if(!buffer.openFromFile("geo.ogg")){
        cout << "Error de audio"<<endl;
    }
    buffer.play();
    buffer.setVolume(3.f);
    sf::CircleShape player(50.f, 6);
    
    //player.setOrigin(50.f, 50.f);
    //vector<Hexagon> hexaVector;
    unordered_map<int, Hexagon> hexaMap;
    int boardSize = 10;
 
    for (int i = 0; i < boardSize; i++){
        int offsetHexagon = 50;
        for (int j = 0; j < boardSize; j++){
            //hexaVector.push_back(Hexagon (55.f, 300.f + 110 * i + 55 * j, 320.f + 95 * j, 10 * i + j));
            hexaMap[10 * i + j] = Hexagon (55.f, 300.f + 110 * i + 55 * j, 320.f + 95 * j, 10 * i + j);
        }
    }
 
    myGraph gr(hexaMap);

    bool turn = true;
 
    bool playing  = true;
 
    int counter = 0;
 
    int final_num = 0;

    bool ganador = false;
    while (!ganador) {
        sf::Event event;
        while (window->pollEvent(event)) {
            
            switch (event.type){
                case sf::Event::Closed:
                    window->close();
                    break;
                case sf::Event::Resized:
                    printf("New window width: %i New window height: %i\n", event.size.width, event.size.height);
                    break;
 
            }
        }
        window->clear();

 
        // Computer's Turn
        if (turn == false && playing){ // blue's turn
 
            // Algortimo de busqueda de hexagono
            unordered_map<int, pair<int, int>> paths_map;
            vector<int> starting_vertexes = gr.get_starting_vertexes();
            vector<int> ending_vertexes = gr.get_ending_vertexes();
            paths_map.clear();
            for (auto starting_vertex : starting_vertexes){
                for (auto ending_vertex : ending_vertexes){
                    printShortestDistance(gr, gr.get_adj_map(), starting_vertex, ending_vertex, paths_map);
                }
            }

            int smallest_path = get_smallest_path(paths_map);
            cout << smallest_path << " es smallest path" << endl;
            cout << "Uno de los caminos mas cortos es " << paths_map[smallest_path].first << "-" <<
            paths_map[smallest_path].second << " con distancia " << smallest_path << endl;
            
            if (smallest_path == 100){
                playing = false;
                resultados = "GANASTE";
                ganador = true;
            }
            else if (counter == 1){
                vector<int> path = get_shortest_path(paths_map[smallest_path].first, paths_map[smallest_path].second, gr.get_adj_map());
                gr.is_blue(final_num);
                auto hM = gr.get_hexaMap();
                for (int i = 0; i < hM.size(); i++){
                if (hM[i].getColor() == 1 && hexaMap[i].getColored() == 0){
                    cout << "Se agrego:" << i << endl;
                    hexaMap[i].setColor(2);
                    window->draw(hexaMap[i].getShape());
                    hexaMap[i].setColored(1);
                    }   
                }
                playing = false;
                resultados = "PERDISTE";
                ganador = true;
            }
            else {
                vector<int> path = get_shortest_path(paths_map[smallest_path].first, paths_map[smallest_path].second, gr.get_adj_map());
                if (path.size() == 2){
                    gr.is_blue(path[1]);
                    final_num = path[0];
                    auto hM = gr.get_hexaMap();
                    for (int i = 0; i < hM.size(); i++){
                    if (hM[i].getColor() == 1 && hexaMap[i].getColored() == 0){
                        cout << "Se agrego:" << i << endl;
                        hexaMap[i].setColor(2);
                        window->draw(hexaMap[i].getShape());
                        hexaMap[i].setColored(1);
                        }   
                    }
                    counter++;
                }
                else {
                    int random = rand() % (path.size());
                gr.is_blue(path[random]);
                // Paint hexagons blue
                auto hM = gr.get_hexaMap();
                for (int i = 0; i < hM.size(); i++){
                    if (hM[i].getColor() == 1 && hexaMap[i].getColored() == 0){
                        cout << "Se agrego:" << i << endl;
                        hexaMap[i].setColor(2);
                        window->draw(hexaMap[i].getShape());
                        hexaMap[i].setColored(1);
                        }   
                    }
                }
 
                turn = true;
            }
        }
 
        // Player clicks hexagons -> turns red
        for (int i = 0; i < hexaMap.size(); i++){
 
            window->draw(hexaMap[i].getShape());
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePos.x < (hexaMap[i].getPositionX() + 55 + 50) &&
                mousePos.x > (hexaMap[i].getPositionX() + 55 - 50) && mousePos.y < (hexaMap[i].getPositionY() + 55 + 50) &&
                mousePos.y > (hexaMap[i].getPositionY() + 55 - 50)){
                    if (turn == true && hexaMap[i].getColored() == 0 && playing){ // Our turn
                        hexaMap[i].setColor(1);
                        gr.is_red(i);
                        window->draw(hexaMap[i].getShape());
                        hexaMap[i].setColored(1);
                        turn = false;
                    }
                }
        }
        window->draw(player);
        window->display();
    }
}


void Instrucciones(sf::RenderWindow* window,int x, int y){
    bool veracidad = false;
    sf::Text texto[4];
    sf::Font font;
    texto[0].setString("Instrucciones:");
    texto[1].setString("Atacas de arriba a abajo");
    texto[2].setString("une un camino de hexagonos para ganar el juego!\n");
    texto[3].setString("Presiona arriba para salir");
    texto[0].setPosition(sf::Vector2f(x /2,y /(MAX_NUMBER_OF_ITEMS + 1) * 1));
    texto[1].setPosition(sf::Vector2f(x /2-50,y /(MAX_NUMBER_OF_ITEMS + 1) * 2));
    texto[2].setPosition(sf::Vector2f(x /2-210,(y /(MAX_NUMBER_OF_ITEMS + 1) * 2.4)));
    texto[3].setPosition(sf::Vector2f(x /2-50,y /(MAX_NUMBER_OF_ITEMS + 1) * 2.8));
    if(!font.loadFromFile("fuente2.ttf")){
                //
    }

    for(auto &i:texto){
        i.setFont(font);
        i.setColor(sf::Color::White);
    }
    while(!veracidad){
        sf::Event event;
        while (window->pollEvent(event)) {
            switch (event.type){
                case sf::Event::KeyReleased:
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Up:
                        veracidad = true;
                        break;
                    }    
                case sf::Event::Resized:
                    printf("New window width: %i New window height: %i\n", event.size.width, event.size.height);
                    break;
                default:
                    break;
            }
        }
        window->clear();
        for(auto &i:texto){
            window->draw(i);
        }
        window->display();
    }
}

int menu(sf::RenderWindow *window,int x, int y){
    int veracidad = 0;
    Menu menu(x-250,y);
    while (veracidad==0) {
        sf::Event event;
        while (window->pollEvent(event)) {
            switch (event.type){
                case sf::Event::KeyReleased:
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Up:
                        menu.Moveup();
                        break;
                    case sf::Keyboard::Down:
                        menu.MoveDown();
                        break;
                    case sf::Keyboard::Return:
                        switch (menu.get_Pressed_Item())
                        {
                        case 1:
                            veracidad = 1;
                            break;
                        case 2:
                            veracidad = 2;
                            break;
                        case 3:
                            window->close();
                            break;                            
                        default:
                            break;
                        }
                    default:
                        break;
                    }
                    default:
                        break;
                
                case sf::Event::Closed:
                    window->close();
                    break;
                case sf::Event::Resized:
                    //cout << "New window width:" << event.size.width << ". New window height:" << event.size.height << endl;
                    printf("New window width: %i New window height: %i\n", event.size.width, event.size.height);
                    break;
            }
        }
        window->clear();
        menu.draw(*window);
        window->display();
    }
    return veracidad;
}

int main()
{   
    int veracidad = 0;
    sf::RenderWindow window(sf::VideoMode(2200,1600), "HEX!", sf::Style::Close | sf::Style::Resize);
    int x = window.getSize().x, y = window.getSize().y;
    while(window.isOpen()){
        if(veracidad==0){
            veracidad = menu(&window,x,y);
        }
        else if(veracidad ==1){
            tablero(&window);
            veracidad = 4;
        } 
        else if(veracidad ==2){ 
            Instrucciones(&window,x-250,y);
            veracidad = 0;
        }
        else if(veracidad==3){
            window.close();
        }
        else if(veracidad==4){
            veracidad = resultado(&window,resultados,x,y);
        }
    }
}




