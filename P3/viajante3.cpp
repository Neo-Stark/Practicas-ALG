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
	return round(sqrt(pow(M[segundo].first - M[primero].first, 2) + pow(M[segundo].second - M[primero].second, 2)));
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


int distanciaTrayecto(vector<int> sol, map<int, pair<double, double> > M){
	int distancia_total = 0;
	for(auto it = sol.begin(); it != sol.end() - 1; ++it)
		distancia_total += distanciaEuclidea(*it, *(it + 1), M);
	
	return distancia_total;
}

vector<int> hillClimbing(vector<int> sol, map<int, pair<double, double> > M){
	vector<int> tmp_sol, restart, mejor = sol;
	int mejor_distancia = distanciaTrayecto(sol, M), tmp;

	for(int i = 1; i < sol.size() - 2; ++i){
		restart = tmp_sol = mejor;
		for(int j = i; j < sol.size() - 2; ++j){
			tmp = tmp_sol[i];
			tmp_sol[i] = tmp_sol[j];
			tmp_sol[j] = tmp;

			int nueva_distancia = distanciaTrayecto(tmp_sol, M);
			if(nueva_distancia < mejor_distancia){
				mejor_distancia = nueva_distancia;
				mejor = tmp_sol;
			}
			tmp_sol = restart;
		}
	}
	return mejor;
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
	// inicio solucion inicial
	int vec_cercano = M.begin()->first;
	sol.push_back(vec_cercano);
	usados[vec_cercano] = true;
	while(count(usados.begin() + 1, usados.end(), false) > 0){
		vec_cercano = vecinoMasCercano(vec_cercano, M, usados);
		usados[vec_cercano] = true;
		sol.push_back(vec_cercano);
	}
	sol.push_back(M.begin()->first);
	//final solucion inicial
	
	sol = hillClimbing(sol, M);
	cout << endl << endl;
	

	ofstream output("salida.tsp");
	if(!output){
		cout << "Error en el fichero de salida" << endl;
		exit(-1);
	}
	for(auto i : sol){
		output << i << " " << M[i].first << " " << M[i].second << endl; 		
	}

	// for(auto i : sol){
	// 	cout << i << " " << M[i].first << " " << M[i].second << endl; 		
	// }
	// cout << endl;

	cout << "Distancia(Viajante3) " << distanciaTrayecto(sol, M) << endl;

	return 0;
	
}