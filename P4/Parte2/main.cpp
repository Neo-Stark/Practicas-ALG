#include <utils.cpp>

int main(int argc, char *argv[]){
	map<int, pair<double, double> > M;
	vector<int> sol;
	if(argc < 2){
		cout << "Formato incorrecto" << endl;
		exit(-1);
	}
	string s = argv[1];

	int n = leerFichero(s, M);
  vector<vector<double>> matriz_dist = matrizDistancias(M);

  ByB(sol, matriz_dist, M);
	ofstream output("salida.tsp");
	if(!output){
		cout << "Error en el fichero de salida" << endl;
		exit(-1);
	}
	for(auto i : sol){
		output << i << " " << M[i].first << " " << M[i].second << endl; 		
	}

  for (int i : sol)
  cout << i << endl;
  cout << "Ciudades: " << sol.size() << endl;
	cout << "Distancia(ByB) " << distanciaCompleta(sol, matriz_dist) << endl;

	return 0;
	
}