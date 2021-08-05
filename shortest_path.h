#pragma once
#include "hexagon.h"
#include <list>
#include <limits>
using namespace std;
 
 
bool bfs_to_border(unordered_map<int, vector<int>> adj, unordered_map<int, bool> painted, int value, 
                    unordered_map<int, Hexagon> hexaMap){
 
    unordered_map<int, bool> visited;
    for (int i = 0; i < 99; i++){
        visited[i] = false;
    }
    list<int> queue;
    queue.push_back(value);
    visited[value] = true;
 
    while (!queue.empty()){
        int u = queue.front();
        queue.pop_front();
        for (auto i : adj[u]){
            if (!visited[i] && hexaMap[i].getColor() == 1){ // 1 is blue
            visited[i] = true;
            queue.push_back(i);
            }
            for (int j = 0; j < 10; j++){
                if (j == i && hexaMap[i].getColor() == 1){
                    return true;
                }
            }
        }
    }
    return false;
}
 
bool bfs_to_end_border(unordered_map<int, vector<int>> adj, unordered_map<int, bool> painted, int value, 
                    unordered_map<int, Hexagon> hexaMap){
 
    unordered_map<int, bool> visited;
    for (int i = 0; i < 99; i++){
        visited[i] = false;
    }
    list<int> queue;
    queue.push_back(value);
    visited[value] = true;
 
    while (!queue.empty()){
        int u = queue.front();
        queue.pop_front();
        for (auto i : adj[u]){
            if (!visited[i] && hexaMap[i].getColor() == 1){ // 1 is blue
            visited[i] = true;
            queue.push_back(i);
            }
            for (int j = 90; j < 100; j++){
                if (j == i && hexaMap[i].getColor() == 1){
                    return true;
                }
            }
        }
    }
    return false;
}
 
bool BFS(unordered_map<int,vector<int>> adj, int src, int dest,
        unordered_map<int,int> &pred, unordered_map<int,int> &dist,
        unordered_map<int,bool>& visited){
    int v = 99;
    list<int> queue;
    for(auto &i:visited){
        i.second = false;
    }
    for(auto &i:dist){
        i.second = 2147483647; // INT_MAX
    }
    for(auto &i:pred){
        i.second = -1;
    }
 
    visited[src] = true;
    dist[src] = 0;
    queue.push_back(src);
 
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();
        for (int i = 0; i < adj[u].size(); i++) {
            if (visited[adj[u][i]] == false) {
                visited[adj[u][i]] = true;
                dist[adj[u][i]] = dist[u] + 1;
                pred[adj[u][i]] = u;
                queue.push_back(adj[u][i]);
 
 
                if (adj[u][i] == dest)
                    return true;
            }
        }
    }
 
    return false;
}
 
bool BFS2(unordered_map<int,vector<int>> adj, int src, int dest, unordered_map<int,bool>& visited,
         unordered_map<int, Hexagon> hexaMap){
    int v = 99;
    list<int> queue;
    for(auto &i:visited){
        i.second = false;
    }
 
    visited[src] = true;
    queue.push_back(src);
 
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();
        for (int i = 0; i < adj[u].size(); i++) {
            if (visited[adj[u][i]] == false && hexaMap[adj[u][i]].getColor() == 1) {
                visited[adj[u][i]] = true;
                queue.push_back(adj[u][i]);
 
 
                if (adj[u][i] == dest)
                    return true;
            }
        }
    }
 
    return false;
}
 
bool bfs_to_victory(unordered_map<int, Hexagon> hexaMap, unordered_map<int, vector<int>> or_adj){
    unordered_map<int, bool> visited;
    for(int i = 0; i < 99; i++){
        visited[i] = false;
    }
    for (int i = 0; i < 10; i++){
        for (int j = 90; j < 99; j++){
            if (BFS2(or_adj, i, j, visited, hexaMap)){
                return true;
            }
        }
    }
    return false;
}
 
int get_smallest_path(unordered_map<int, pair<int, int>> paths_map){
    int number = 100;
    for (auto e : paths_map){
        if (e.first < number){
            number = e.first;
        }
    }
    return number;
}
