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

// Lee un fichero y guarda los resultados en un map
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

// Calcula el recorrida inicial, es decir, el triángulo de ciudades mencionado en el guión
vector<int> recorridoInicial(map<int, pair<double, double> > &M){
  int norte = 1, este, oeste;
  este = norte;
  oeste = norte;
  double maxnorte = M[1].second, maxeste = M[1].first, maxoeste = M[1].first;
  vector<int> resultado;
  for(auto it = M.begin(); it != M.end(); ++it){
    if(it->second.second > maxnorte){
      maxnorte = it->second.second;
      norte = it->first;
    }

    if(it->second.first > maxeste){
      maxeste = it->second.first;
      este = it->first;
    }

    if(it->second.first < maxoeste){
      maxoeste = it->second.first;
      oeste = it->first;
    }
  }

  if (norte == este || este == oeste || norte == oeste) {
    cout << "GRAN PROBLEMO" << endl;
    exit(-1);
  }

  resultado.push_back(norte);
  resultado.push_back(este);
  resultado.push_back(oeste);

  return resultado;
}

// Calcula la distancia entre dos puntos
int distanciaEuclidea(int primero, int segundo, map<int, pair<double, double> > &M){
  return round(sqrt(pow(M[segundo].first - M[primero].first,2) + pow(M[segundo].second - M[primero].second,2)));

}

// Genera una matriz de distancia a partir del map de ciudades
vector<vector<double> > matrizDistancias(map<int, pair<double, double> > &M){
  int dimension = M.size()+1;
  double distancia = 0;
  vector<vector<double> > matriz(dimension,vector<double>(dimension, 0));


  for (int i = 1; i < dimension; ++i){
    for (int j = i; j < dimension; ++j){
      distancia = distanciaEuclidea(i, j, M);
      matriz[i][j] = distancia;
      matriz[j][i] = distancia;
    }
  }

  return matriz;
}

// Devuelve los indices de las ciudades que quedan por visitar (lo aplicamos a las
// ciudades ya visitadas)
vector<int> complementario(vector<int> v, map<int, pair<double, double> > &M){
  vector<int> comp;
  for (auto it = M.begin(); it!=M.end(); ++it){
    if(std::find(v.begin(), v.end(), it->first) == v.end()){
      comp.push_back(it->first);
    }
  }

  return comp;
}

// Devuelve la distancia total de todas las ciudades recorridas en cierto orden
double distanciaCompleta(vector<int> ciudades, const vector<vector<double> > &distancias){
  double resultado = distancias[*(ciudades.begin())][*(ciudades.end()-1)];

  for (auto it = ciudades.begin(); it != ciudades.end()-1; ++it){
    resultado += distancias[*it][*(it+1)];
  }

  return resultado;
}

// Incluye la mejor ciudad posible en un circuito dado
void mejorCiudad(vector<int> &cerrados, vector<int> &abiertos, const vector<vector<double> > &distancias, map<int, pair<double, double> > &M){
  vector<int> aux = cerrados;
  double distancia_aux = 0;
  aux.push_back(abiertos[0]); //primer elemento
  vector<int> mejores_ciudades = aux;
  double dist_minima = distanciaCompleta(aux, distancias); //Inicializamos la dist. minima a la del primer candidato

  aux = cerrados;
  for (auto it = abiertos.begin(); it != abiertos.end(); ++it){
    for (auto it2 = aux.begin()+1; it2 != aux.end(); ++it2){
      aux.insert(it2, *it);
      distancia_aux = distanciaCompleta(aux, distancias);
      if(distancia_aux < dist_minima){
        dist_minima = distancia_aux;
        mejores_ciudades = aux;
      }
      aux = cerrados;
    }
  }

  cerrados = mejores_ciudades;
  abiertos = complementario(cerrados, M);

}

// Añade todas las ciudades al circuito insertando, en cada caso, la mejor opción
void calculaMejoresCiudades(vector<int> &cerrados, const vector<vector<double> > &distancias, map<int, pair<double, double> > &M){
  vector<int> abiertos = complementario(cerrados, M);

  while(!abiertos.empty())
    mejorCiudad(cerrados, abiertos, distancias, M);	
  
}


int main(int argc, char *argv[]){
  map<int, pair<double, double> > M;
  vector<int> sol, rec_inicial, complementarios;
  vector<vector<double> > matriz_dist;
  if(argc < 2){
    cout << "Formato incorrecto" << endl;
    exit(-1);
  }

  string s = argv[1];
  int n = leerFichero(s, M);
  vector<bool> usados(n + 1, false);

  matriz_dist = matrizDistancias(M);

  rec_inicial = recorridoInicial(M);

  // cout << "Recorrido inicial" << endl;
  // for(auto it = rec_inicial.begin(); it != rec_inicial.end(); ++it){
  //   cout << *it << " ";
  // }
  // cout << endl;

  sol = rec_inicial;

  calculaMejoresCiudades(sol, matriz_dist, M);
  sol.push_back(*sol.begin());

  // cout << "Mejor recorrido" << endl;
  // for(auto it = sol.begin(); it != sol.end(); ++it){
  //   cout << *it << " ";
  // }
  // cout << endl;

  ofstream output("salida.tsp");
  if(!output){
    cout << "Error en el fichero de salida" << endl;
    exit(-1);
  }

  for(auto i : sol) {
    output << i << " " << M[i].first << " " << M[i].second << endl; 		
  }

  cout << "Distancia(viajante2) " << distanciaCompleta(sol, matriz_dist) << endl;

}
