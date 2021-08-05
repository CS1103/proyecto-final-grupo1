#pragma once
#include "shortest_path.h"
 
using namespace std;
 
bool find_element_in_vec(int element, vector<int> vec){
    /*
    bool found = false;
    for (auto e : vec){
        if (e == element){
            found = true;
        }
    }
    return found;
    */
   if (find(vec.begin(), vec.end(), element) == vec.end()){
       return false;
   }
   return true;
}
 
void update_starting_vertexes(unordered_map<int, vector<int>> real_adj, unordered_map<int, vector<int>> adj, unordered_map<int, bool> painted,
                                vector<int>& starting_vertexes, unordered_map<int, Hexagon> hexaMap){
    // Borrar repetidos
    for (auto e : starting_vertexes){
        if (painted[e]){
            starting_vertexes.erase(remove(starting_vertexes.begin(), starting_vertexes.end(), e), starting_vertexes.end());
        }
    }
 
    for (auto e : painted){
        if (e.second == true){
            for (auto i : adj[e.first]){
                if (find_element_in_vec(i, starting_vertexes) == false && !painted[i]){
                    if ((i < 10 && painted[i] == false) || bfs_to_border(adj, painted, i, hexaMap)){
                    starting_vertexes.push_back(i);
                    }
                }
            }
        }
    }
    sort(starting_vertexes.begin(), starting_vertexes.end() );
    starting_vertexes.erase( unique( starting_vertexes.begin(), starting_vertexes.end() ), starting_vertexes.end() );
}
 
void update_ending_vertexes(unordered_map<int, vector<int>> real_adj, unordered_map<int, vector<int>> adj, unordered_map<int, bool> painted,
                                vector<int>& ending_vertexes, unordered_map<int, Hexagon> hexaMap){
    // Borrar repetidos
    for (auto e : ending_vertexes){
        if (painted[e]){
            ending_vertexes.erase(remove(ending_vertexes.begin(), ending_vertexes.end(), e), ending_vertexes.end());
        }
    }
 
    for (auto e : painted){
        if (e.second == true){
            for (auto i : adj[e.first]){
                if (find_element_in_vec(i, ending_vertexes) == false && !painted[i]){
                    if ((i > 89 && painted[i] == false) || bfs_to_end_border(adj, painted, i, hexaMap)){
                    ending_vertexes.push_back(i);
                    }
                }
            }
        }
    }
    sort(ending_vertexes.begin(), ending_vertexes.end() );
    ending_vertexes.erase( unique( ending_vertexes.begin(), ending_vertexes.end() ), ending_vertexes.end() );
}
 
void delete_from_vector(vector<int> & vec, int value){
    remove(vec.begin(), vec.end(), value);
}
 
void add_elements_not_present(int adj_vertex, vector<int>& adj_vector, vector<int> vertex_vector, int key){
    // dos verctores &adj_vector, vertex_vector
    auto it = adj_vector.begin();
    for (auto e : vertex_vector){
        if (!find_element_in_vec(e, adj_vector)){
            adj_vector.push_back(e);
        }
    }
    adj_vector.erase(remove(adj_vector.begin(), adj_vector.end(), adj_vertex), adj_vector.end());
    adj_vector.erase(remove(adj_vector.begin(), adj_vector.end(), key), adj_vector.end());
}
 
class myGraph{
    unordered_map<int, vector<int>> adj_map;
    unordered_map<int, bool> painted;
    unordered_map<int, vector<int>> original_adj;
    unordered_map<int, Hexagon> hexaMap;
    vector<int> starting_vertexes;
    vector<int> ending_vertexes;
public:
    myGraph(unordered_map<int, Hexagon> h){
        hexaMap = h;
        for (int i = 1; i < 99; i++){
            painted[i] = false;
            if (i < 10){
                adj_map[i] = {i + 1, i - 1, i + 10, i + 9};
                original_adj[i] = {i + 1, i - 1, i + 10, i + 9};
            }
            else if (i % 10 == 0 && i != 90){
                adj_map[i] = {i - 10, i + 10, i - 9, i + 1};
                original_adj[i] = {i - 10, i + 10, i - 9, i + 1};
            }
            else if ((i + 1) % 10 == 0){
                adj_map[i] = {i - 10, i + 10, i + 9, i - 1};
                original_adj[i] = {i - 10, i + 10, i + 9, i - 1};
            }
            else if (i > 90){
                adj_map[i] = {i - 1, i + 1, i - 10, i - 9};
                original_adj[i] = {i - 1, i + 1, i - 10, i - 9};
            }
            else {
                adj_map[i] = {i + 1, i - 1, i - 10, i - 9, i + 10, i + 9};
                original_adj[i] = {i + 1, i - 1, i - 10, i - 9, i + 10, i + 9};
            }
        }
        adj_map[0] = {1,10};
        adj_map[99] = {89, 98};
        adj_map[9] = {8, 18, 19};
        adj_map[90] = {80, 81, 91};
        original_adj[0] = {1,10};
        original_adj[99] = {89, 98};
        original_adj[9] = {8, 18, 19};
        original_adj[90] = {80, 81, 91};
        starting_vertexes = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        ending_vertexes = {90, 91, 92, 93, 94, 95, 96, 97, 98, 99};
    }
    vector<int> get_starting_vertexes(){
        return starting_vertexes;
    }
    vector<int> get_ending_vertexes(){
        return ending_vertexes;
    }
    unordered_map<int, vector<int>> get_adj_map(){
        return adj_map;
    }
    unordered_map<int, Hexagon> get_hexaMap(){
        return hexaMap;
    }
    unordered_map<int, vector<int>> get_original_adj(){
        return original_adj;
    }
    unordered_map<int, bool> get_painted(){
        return painted;
    }
    void print_adj(){
        for (auto it : adj_map){
            cout << "Grafo Vertice " << it.first << ": ";
            for (auto e : it.second){
                cout << e << " ";
            }
            cout << endl;
        }
    }
    void print_original_adj(){
        for (auto it : original_adj){
            cout << "Grafo Vertice " << it.first << ": ";
            for (auto e : it.second){
                cout << e << " ";
            }
            cout << endl;
        }
    }
    void print_painted(){
        for (auto e : painted){
            cout << "Grafo Vertice " << e.first << ": ";
            cout << e.second;
            cout << endl;
        }
    }
    void print_starting_vertexes(){
        for (auto &e : starting_vertexes){
            cout << e << " ";
        }
        cout << endl;
    }
    void print_ending_vertexes(){
        for (auto &e : ending_vertexes){
            cout << e << " ";
        }
        cout << endl;
    }
    void is_red(int vertex){
        // se borra de starting vertexes
        delete_from_vector(starting_vertexes, vertex);
        delete_from_vector(ending_vertexes, vertex);
        painted[vertex] = true;
        hexaMap[vertex].setColor(1);
 
        // se borra el adj de los vectores que tienen al nodo/vertice
        for (auto i : adj_map[vertex]){
            for (auto it = adj_map[i].begin(); it != adj_map[i].end(); ){
                if (*it == vertex){
                    it = adj_map[i].erase(it);
                }
                else {
                    it++;
                }
            }
        }
        // se borra el nodo/vertice
        cout << "Borrando " << vertex << endl;
        adj_map.erase(vertex);
        original_adj.erase(vertex);
        update_starting_vertexes(adj_map, original_adj, painted, starting_vertexes, hexaMap);
        update_ending_vertexes(adj_map, original_adj, painted, ending_vertexes, hexaMap);
    }
    void is_blue(int vertex){
        // Pongo que esta pintado
        delete_from_vector(starting_vertexes, vertex);
        delete_from_vector(ending_vertexes, vertex);
        painted[vertex] = true;
        hexaMap[vertex].setColor(2);
 
        // los adjacentes del nodo que se va a borrar se 
        // agregan a los vectores de adjacentes del nodo mientras no
        // sean adjacentes de sus adjacentes
        vector<int> vertex_adj = adj_map[vertex];
        for (auto a_vertex : vertex_adj){
            add_elements_not_present(vertex, adj_map[a_vertex], vertex_adj, a_vertex);
        }
        adj_map.erase(vertex);
        update_starting_vertexes(adj_map, original_adj, painted, starting_vertexes, hexaMap);
        update_ending_vertexes(adj_map, original_adj, painted, ending_vertexes, hexaMap);
    }
};
 
void printShortestDistance(myGraph gr, unordered_map<int,vector<int>> adj, int s,
                           int dest, unordered_map<int, pair<int, int>>& paths_map) {
    unordered_map<int, int> pred;
    unordered_map<int, int> dist;
    unordered_map<int, bool> visited;
 
    for(int i = 0; i < 99; i++){
        pred[i] = -1;
        dist[i] = 2147483647; // INT_MAX
        visited[i] = false;
    }
 
    if (BFS(adj, s, dest, pred, dist, visited) == false) {
        return;
    }
 
    vector<int> path;
    int crawl = dest;
    path.push_back(crawl);
    while (pred[crawl] != -1) {
        path.push_back(pred[crawl]);
        crawl = pred[crawl];
    }
    paths_map[path.size()] = pair<int, int>(s, path[0]);
    /*
    cout << "Shortest path length is : "
         << dist[dest];
 
    cout << "\nPath is::\n";
    for (int i = path.size() - 1; i >= 0; i--)
        cout << path[i] << " ";
    */
}
 
vector<int> get_shortest_path(int src, int dest, unordered_map<int, vector<int>> adj){
    unordered_map<int, int> pred;
    unordered_map<int, int> dist;
    unordered_map<int, bool> visited;
 
    for(int i = 0; i < 99; i++){
        pred[i] = -1;
        dist[i] = 2147483647; // INT_MAX
        visited[i] = false;
    }
 
    BFS(adj, src, dest, pred, dist, visited);
    vector<int> path;
    int crawl = dest;
    path.push_back(crawl);
    while (pred[crawl] != -1) {
        path.push_back(pred[crawl]);
        crawl = pred[crawl];
    }
    cout << "Path: ";
    for (auto e : path){
        cout << e << " ";
    }
    cout << endl;
    return path;
}
