#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;



int leerFichero(string &nombre, map<int, pair<double, double> > &M){
	ifstream datos;
    string s;
    pair<double,double> p;
    int n,act;
    
    
    datos.open(nombre.c_str());
    if (datos.is_open()) {
	    datos >> s; // Leo "dimension:"
	    datos >> n;
	    for (int i = 0; i < n; i++) {
	        datos >> act >> p.first >> p.second;
			M[act] = p;
   		}
    	datos.close();
    }
    else { 
      cout << "Error de Lectura en " << nombre << endl;
    }
    return n;
}

int distanciaEuclidea(int primero, int segundo, map<int, pair<double, double> > &M){
	return round(sqrt(pow(M[segundo].first - M[primero].first,2) + pow(M[segundo].second - M[primero].second,2)));
}

int distanciaTrayecto(vector<int> sol, map<int, pair<double, double> > M){
	int distancia_total = 0;
	for(auto it = sol.begin(); it != sol.end() - 1; ++it)
		distancia_total += distanciaEuclidea(*it, *(it + 1), M);
	
	return distancia_total;
}



int vecinoMasCercano(int actual, map<int, pair<double, double> > &M,vector<bool> usados){
	int min = 100000;
	int pos_min = -1;

	for(auto it = M.begin(); it != M.end(); it++){
		if(!usados[it->first]){
			int distancia_actual = distanciaEuclidea(actual, it->first, M);
			if( distancia_actual < min){
				min = distancia_actual;
				pos_min = it->first;
			}
		}
	}

	return pos_min;
}




int main(int argc, char *argv[]){
	map<int, pair<double, double> > M;
	vector<int> sol;
	if(argc < 2){
		cout << "Formato incorrecto" << endl;
		exit(-1);
	}

	string s = argv[1];
	int n = leerFichero(s, M);
	vector<bool> usados(n + 1, false);

	int vec_cercano = M.begin()->first;
	sol.push_back(vec_cercano);
	usados[vec_cercano] = true;
	while(count(usados.begin() + 1, usados.end(), false) > 0){
		vec_cercano = vecinoMasCercano(vec_cercano, M, usados);
		usados[vec_cercano] = true;
		sol.push_back(vec_cercano);

	}
	sol.push_back(M.begin()->first);

	ofstream output("salida.tsp");
	if(!output){
		cout << "Error en el fichero de salida" << endl;
		exit(-1);
	}
	for(auto i : sol){
		output << i << " " << M[i].first << " " << M[i].second << endl; 		
	}


	cout << "Distancia(Viajante1) " << distanciaTrayecto(sol, M) << endl;

	return 0;
	
}