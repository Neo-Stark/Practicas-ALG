#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

// Lee un fichero y guarda los resultados en un map
int leerFichero(string &nombre, map<int, pair<double, double>> &M) {
  ifstream datos;
  string s;
  pair<double, double> p;
  int n, act;

  datos.open(nombre.c_str());
  if (datos.is_open()) {
    datos >> s;  // Leo "dimension:"
    datos >> n;
    for (int i = 0; i < n; i++) {
      datos >> act >> p.first >> p.second;
      M[act] = p;
    }
    datos.close();
  } else {
    cout << "Error de Lectura en " << nombre << endl;
  }
  return n;
}

// Calcula el recorrida inicial, es decir, el triángulo de ciudades mencionado
// en el guión
vector<int> recorridoInicial(map<int, pair<double, double>> &M) {
  int norte = 1, este, oeste;
  este = norte;
  oeste = norte;
  stack<int> pila_norte;
  double maxnorte = M[1].second, maxeste = M[1].first, maxoeste = M[1].first;
  vector<int> resultado;
  for (auto it = M.begin(); it != M.end(); ++it) {
    if (it->second.second > maxnorte) {
      maxnorte = it->second.second;
      pila_norte.push(it->first);
    }

    if (it->second.first > maxeste) {
      maxeste = it->second.first;
      este = it->first;
    }

    else if (it->second.first < maxoeste) {
      maxoeste = it->second.first;
      oeste = it->first;
    }
  }

  norte = pila_norte.top();
  pila_norte.pop();
  if (norte == este || norte == oeste) {
    cout << "GRAN PROBLEMO" << endl;
    norte = pila_norte.top();
  }

  resultado.push_back(norte);
  resultado.push_back(este);
  resultado.push_back(oeste);

  return resultado;
}

// Calcula la distancia entre dos puntos
int distanciaEuclidea(int primero, int segundo,
                      map<int, pair<double, double>> &M) {
  return round(sqrt(pow(M[segundo].first - M[primero].first, 2) +
                    pow(M[segundo].second - M[primero].second, 2)));
}

// Genera una matriz de distancia a partir del map de ciudades
vector<vector<double>> matrizDistancias(map<int, pair<double, double>> &M) {
  int dimension = M.size() + 1;
  double distancia = 0;
  vector<vector<double>> matriz(dimension, vector<double>(dimension, 0));

  for (int i = 1; i < dimension; ++i) {
    for (int j = i; j < dimension; ++j) {
      distancia = distanciaEuclidea(i, j, M);
      matriz[i][j] = distancia;
      matriz[j][i] = distancia;
    }
  }

  return matriz;
}

// Devuelve los indices de las ciudades que quedan por visitar (lo aplicamos a
// las ciudades ya visitadas)
vector<int> complementario(vector<int> v, map<int, pair<double, double>> &M) {
  vector<int> comp;
  for (auto it = M.begin(); it != M.end(); ++it) {
    if (std::find(v.begin(), v.end(), it->first) == v.end()) {
      comp.push_back(it->first);
    }
  }

  return comp;
}

// Devuelve la distancia total de todas las ciudades recorridas en cierto orden
double distanciaCompleta(vector<int> ciudades,
                         const vector<vector<double>> &distancias) {
  double resultado = distancias[*(ciudades.begin())][*(ciudades.end() - 1)];

  for (auto it = ciudades.begin(); it != ciudades.end() - 1; ++it) {
    resultado += distancias[*it][*(it + 1)];
  }

  return resultado;
}

// Incluye la mejor ciudad posible en un circuito dado
void mejorCiudad(vector<int> &cerrados, vector<int> &abiertos,
                 const vector<vector<double>> &distancias,
                 map<int, pair<double, double>> &M) {
  vector<int> aux = cerrados;
  double distancia_aux = 0;
  aux.push_back(abiertos[0]);  // primer elemento
  vector<int> mejores_ciudades = aux;
  double dist_minima = distanciaCompleta(
      aux,
      distancias);  // Inicializamos la dist. minima a la del primer candidato

  aux = cerrados;
  for (auto it = abiertos.begin(); it != abiertos.end(); ++it) {
    for (auto it2 = aux.begin() + 1; it2 != aux.end(); ++it2) {
      aux.insert(it2, *it);
      distancia_aux = distanciaCompleta(aux, distancias);
      if (distancia_aux < dist_minima) {
        dist_minima = distancia_aux;
        mejores_ciudades = aux;
      }
      aux = cerrados;
    }
  }

  cerrados = mejores_ciudades;
  abiertos = complementario(cerrados, M);
}

// Añade todas las ciudades al circuito insertando, en cada caso, la mejor
// opción
void calculaMejoresCiudades(vector<int> &cerrados,
                            const vector<vector<double>> &distancias,
                            map<int, pair<double, double>> &M) {
  vector<int> abiertos = complementario(cerrados, M);

  while (!abiertos.empty()) mejorCiudad(cerrados, abiertos, distancias, M);
}

// Calcula un recorrido greedy
int greedy(map<int, pair<double, double>> &M) {
  vector<int> rec_inicial = recorridoInicial(M);
  vector<int> solucion = rec_inicial;
  vector<vector<double>> matriz_dist = matrizDistancias(M);
  calculaMejoresCiudades(solucion, matriz_dist, M);
  return distanciaCompleta(solucion, matriz_dist);
}

// Calcula la distancia minima de una ciudad
int distanciaMinima(int ciudad, const vector<vector<double>> &matriz_dist) {
  int min = 10000000;
  int temp;
  for (int i = 1; i < matriz_dist.size(); ++i) {
    temp = matriz_dist[i][ciudad];
    if (temp < min && temp != 0) min = temp;
  }

  return min;
}

// Calcula el recorrido más optimista
int optimista(const vector<int> &sol, map<int, pair<double, double>> &M) {
  vector<int> sin_recorrer = complementario(sol, M);
  vector<vector<double>> matriz_dist = matrizDistancias(M);
  int min = 0;
  for (auto it = sin_recorrer.begin(); it != sin_recorrer.end(); ++it)
    min += distanciaMinima(*it, matriz_dist);

  // cout << "Minimo " << min << endl;
  return distanciaCompleta(sol, matriz_dist) + min;
}

// Calcula hijos
vector<vector<int>> generarHijos(const vector<int> &sol,
                                 map<int, pair<double, double>> &M) {
  vector<int> comp = complementario(sol, M);
  vector<int> padre;
  vector<vector<int>> resultado;
  for (auto ciudad : comp) {
    padre = sol;
    padre.push_back(ciudad);
    resultado.push_back(padre);
  }

  return resultado;
}

// Devuelve si es una solucion valida
bool esSolucion(const vector<int> &sol, map<int, pair<double, double>> &M) {
  vector<int> comp = complementario(sol, M);
  return comp.size() == 0;
}

void ByB(vector<int> &sol, const vector<vector<double>> &matriz_dist,
         map<int, pair<double, double>> &M) {
  queue<vector<int>> C;
  sol.push_back(1);
  vector<vector<int>> hijos;

  int CG = greedy(M);
  cout << "Greedy " << CG << endl;
  for (auto i : matriz_dist) {
    for (auto j : i) cout << j << "\t";
    cout << endl;
  }

  C.push(sol);
  do {
    sol = C.front();
    C.pop();

    hijos = generarHijos(sol, M);

    for (auto it : hijos) {
      if (optimista(it, M) < CG) {  // ES FACTIBLE
        if (esSolucion(it, M)) {
          sol = it;
          CG = distanciaCompleta(sol, matriz_dist);
        } else
          C.push(it);
      }
    }
  } while (!C.empty());
  sol.push_back(1);
}
