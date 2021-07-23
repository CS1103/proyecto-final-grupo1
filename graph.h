#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

bool find_element_in_vec(int element, vector<int> vec){
    bool found = false;
    for (auto e : vec){
        if (e == element){
            found = true;
        }
    }
    return found;
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
public:
    myGraph(){
        for (int i = 1; i < 99; i++){
            if (i < 10){
                adj_map[i] = {i + 1, i - 1, i + 10, i + 9};
            }
            else if (i % 10 == 0 && i != 90){
                adj_map[i] = {i - 10, i + 10, i - 9, i + 1};
            }
            else if ((i + 1) % 10 == 0){
                adj_map[i] = {i - 10, i + 10, i + 9, i - 1};
            }
            else if (i > 90){
                adj_map[i] = {i - 1, i + 1, i - 10, i - 9};
            }
            else {
                adj_map[i] = {i + 1, i - 1, i - 10, i - 9, i + 10, i + 9};
            }
        }
        adj_map[0] = {1,10};
        adj_map[99] = {89, 98};
        adj_map[9] = {8, 18, 19};
        adj_map[90] = {80, 81, 91};
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
    void is_red(int vertex){
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
        adj_map.erase(vertex);
    }
    void is_blue(int vertex){
        // los adjacentes del nodo que se va a borrar se 
        // agregan a los vectores de adjacentes del nodo mientras no
        // sean adjacentes de sus adjacentes
        vector<int> vertex_adj = adj_map[vertex];
        for (auto a_vertex : vertex_adj){
            add_elements_not_present(vertex, adj_map[a_vertex], vertex_adj, a_vertex);
        }
        adj_map.erase(vertex);
    }
};