#include <utils.cpp>

int main(int argc, char *argv[]){
	map<int, pair<double, double> > M;
	vector<int> sol;
	if(argc < 2){
		cout << "Formato incorrecto" << endl;
		exit(-1);
	}
  vector<vector<double>> matriz_dist = matrizDistancias(M);
	string s = argv[1];
	int n = leerFichero(s, M);

  ByB(sol, matriz_dist, M);
	ofstream output("salida.tsp");
	if(!output){
		cout << "Error en el fichero de salida" << endl;
		exit(-1);
	}
	for(auto i : sol){
		output << i << " " << M[i].first << " " << M[i].second << endl; 		
	}


	cout << "Distancia(Viajante1) " << distanciaCompleta(sol, matriz_dist) << endl;

	return 0;
	
}