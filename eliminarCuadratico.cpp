#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <vector>
using namespace std;

bool yaExiste(vector<int> v, int x){
	bool encontrado = false;
	for(int i = 0; i < v.size() && !encontrado; i++)
		if(v[i] == x)
			encontrado = true;
	return encontrado;
}

vector<int> eliminarRepeticiones(vector<int> v){
	vector<int> v_res;
	for(int i = 0; i < v.size(); i++)
		if(!yaExiste(v_res, v[i]))
			v_res.push_back(v[i]);
	
	return v_res;
}

double uniforme() //Genera un número uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C.
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}

int main(int argc, char * argv[])
{
  clock_t tantes;
  clock_t tdespues;

  if (argc != 2)
    {
      cerr << "Formato " << argv[0] << " <num_elem>" << endl;
      return -1;
    }

  int n = atoi(argv[1]);
  vector<int> v;

  srand(time(0));
  //para generar un vector que pueda tener elementos repetidos
  for (int j=0; j<n; j++) {
    double u=uniforme();
    int k=(int)(n*u);
    v.push_back(k);
  }
  //cout << "Vector antes de eliminar duplicados" << endl;
  //for (int j=0; j<n; j++) {cout << T[j] << " ";}
  tantes = clock();
  v = eliminarRepeticiones(v);
  tdespues = clock();
  cout << n <<" "<<((double)(tdespues-tantes))/CLOCKS_PER_SEC << endl;

  //cout << "\nVector despues de eliminar duplicados" << endl;
  //for (int j=0; j<n1; j++) {cout << T[j] << " ";}

} 