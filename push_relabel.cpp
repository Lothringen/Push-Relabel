#define TP using
#define Final namespace
#define AEDIII std;
#include <vector>
#include <iostream>
#include <fstream>
#include <list>
#include <queue>
#include <climits>
#include "bfs.cpp"

TP Final AEDIII


typedef struct node{
	int height;
	int excess;
} Node;

typedef list<int>::iterator listIterator;

int n, m;
graph R; //Red Residual
graph neighbours; //[0] = s, [n-1] = t 
vector<int> current_N; // Vecino actual para cada nodo ([0] y [n-1] no se usan)
vector<Node> nodes;
list<int> L; //lista global de nodos
queue<int> Q; //Cola de vértices activos
vector<bool> in_Q; //Diccionario lineal de pertenencia en Q


void push(int v, int w){
	int delta_flux = min(nodes[v].excess, R[v][w]);
	R[v][w] -= delta_flux;
	R[w][v] += delta_flux;
	nodes[v].excess -= delta_flux;
	nodes[w].excess += delta_flux; 
}

void relabel(int v){
	int w;
	int min_h = inf;
	for (int i = 0; i < neighbours[v].size(); i++){
		w = neighbours[v][i];
		//Solo vecinos de la red residual
		if(R[v][w]>0) min_h = min(min_h, nodes[w].height);
	}
	nodes[v].height = min_h + 1;
}

void discharge(int v){
	while(nodes[v].excess > 0){
		int index_N = current_N[v]; //w es apunta al vecino actual de v
		if(index_N == neighbours[v].size()){ //Si no me quedan vecinos para dar exceso de flujo
			relabel(v);
			current_N[v] = 0; 
		}else{
			int w = neighbours[v][index_N];
			//Si hay un eje admisible, mando flujo 	
			if(R[v][w] > 0 && nodes[v].height == (nodes[w].height + 1)) push(v, w); 
			else current_N[v] = index_N + 1; //De lo contrario, intento con el siguiente vecino 	
		}
	}	
}

void push_relabel_to_back(int v){
	int index_N = 0;
	while(nodes[v].excess > 0 && index_N != neighbours[v].size()){
		int w = neighbours[v][index_N];
		if(R[v][w] > 0 && nodes[v].height == (nodes[w].height + 1)) push(v, w);
		index_N++;
		if(w != 0 && w != n-1 && !in_Q[w]){
			Q.push(w);
			in_Q[w] = true;	
		}
	}	
}

void init_preflow(){
	//Inicializo preflow
	nodes[0].height = n;
	//Saturo vecinos de la fuente s 
	for (int i = 0; i<neighbours[0].size(); i++){
		int w = neighbours[0][i];
		nodes[w].excess = R[0][w];
		nodes[0].excess -= R[0][w];
		//OBS: += para el caso FIFO cuando existe aristas sv y vs
		R[w][0] += R[0][w];    //C_f(w, v) = f(v, w)   
		R[0][w] = 0;		//sature el flujo del eje (0,w)	
	}
}

void push_to_front(){
	init_preflow();
	for (int i = 1; i < n-1; ++i) L.push_back(i); //Armo lista de nodos sin s ni t
	listIterator it_v = L.begin();
	while (it_v !=L.end()){
		int v = *it_v;
		int old_height = nodes[v].height;
		discharge(v);
		if (nodes[v].height > old_height){
			L.remove(v);
			L.push_front(v);
			it_v = L.begin();
		}
		it_v++;
	}
} 

void relabel_to_back(){
	init_preflow();
	vector<int> min_heights = bfs(neighbours,n-1);
	in_Q.assign(n, false);
	for(int i = 1; i < n-1; i++) nodes[i].height = min_heights[i];
	for (int i = 0; i<neighbours[0].size(); i++){
		if(neighbours[0][i] != n-1){
			Q.push(neighbours[0][i]);
			in_Q[neighbours[0][i]] = true;	
		}
	}
	while(!Q.empty()){
		int v = Q.front();
		Q.pop();
		in_Q[v] = false;
		push_relabel_to_back(v);
		if(nodes[v].excess > 0 ){
			relabel(v);
			Q.push(v);
			in_Q[v] = true;
		}
	}
}

int main(int argc, char** argv){
	//Ingresa cantidad de nodos y cantidad de aristas
    cin >> n >> m;
	R.assign(n,vector<int> (n,0));
	current_N.assign(n, 0);
    neighbours.reserve(n);  
    nodes.reserve(n);

    //Ingresan m ejes con origen destino y capacidad
    int v, w, c;
    for (int i = 0; i < m; ++i){
    	cin >> v >> w >> c;
		R[v][w] = c;
		if(R[w][v] == 0){ //Si es el primer eje entre v y w, lo agrego
    		neighbours[v].push_back(w);			
			neighbours[w].push_back(v);
		}//sino es porque ya existía el eje wv
    }
    //Inicializo alturas y excesos por default de los n nodos
    for (int i = 0; i < n; ++i){
    	nodes[i].height = 0;
    	nodes[i].excess = 0;
    }

    //Algoritmo push_relabel
    string algo = argc>1 ? argv[1] : "";
    string test = argc>2 ? argv[2] : "";
    if (algo == "-back") relabel_to_back();
    	else if (algo == "-front") push_to_front();
    	else{
			cout << "Correr con parámetro <<-back>> o <<-front>> según el algoritmo deseado con <<path-a-grafo>>" << endl;
			return 0;
		}

	int max_flux = nodes[n-1].excess;
	
	if(test == "-test"){
		int max_flux_test;
	    cin >> max_flux_test;
		cout << "Flujo Máximo TEST: " << max_flux_test << " Resultado de relabel-to" << algo << ": " << max_flux << endl;
    	if(max_flux == max_flux_test) cout << "TEST CORRECTO" << endl;
    		else cout << " TEST INCORRECTO" << endl;
	}else cout << max_flux << endl;

    return 0;
}
