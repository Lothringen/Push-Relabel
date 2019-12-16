
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>
using namespace std;

typedef vector<vector<int>> graph;
int inf = INT_MAX;

vector<int> bfs(const vector<vector<int>> &N, const int s){ //i es el nodo al que le quiero calcular las distancias minimas
	int n, v, w;	
	vector<int> D; //distancias del nodo origen s a los demas nodos del grafo
	queue<int> Q;	
	n = N.capacity();
	D.assign(n, inf);
	Q.push(s);
	D[s] = 0;
	while(!Q.empty()){
		v = Q.front();
		Q.pop();
		for(int i=0; i<N[v].size(); i++){		//para todos los vecinos de v
			w = N[v][i];		
			if(D[w] == inf){			//es un vecino no visitado? 
				D[w] = D[v] + 1;		//actualizo D: w esta a una arista mas de distancia que v
				Q.push(w);												
			}		
		}		
	}
	return D;	
}


