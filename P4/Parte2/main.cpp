#include <chrono>
#include <utils.cpp>
using namespace std::chrono;

int main(int argc, char *argv[]) {
  map<int, pair<double, double>> M;
  vector<int> sol;
  if (argc < 2) {
    cout << "Formato incorrecto" << endl;
    exit(-1);
  }
  string s = argv[1];

  int n = leerFichero(s, M);
  vector<vector<double>> matriz_dist = matrizDistancias(M);

  duration<double, std::milli> tiempo;
  auto start = high_resolution_clock::now();
  ByB_V2(sol, matriz_dist, M);
  auto stop = high_resolution_clock::now();

  tiempo = stop - start;
  ofstream output("salida.tsp");
  if (!output) {
    cout << "Error en el fichero de salida" << endl;
    exit(-1);
  }
  for (auto i : sol) {
    output << i << " " << M[i].first << " " << M[i].second << endl;
  }

  for (int i : sol) cout << i << endl;
  cout << "Ciudades:\t" << sol.size() << endl;
  cout << "Distancia(ByB)\t" << distanciaCompleta(sol, matriz_dist) << endl;
  cout << "Tiempo:\t" << tiempo.count() << endl;

  return 0;
}