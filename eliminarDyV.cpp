#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <vector>




vector<int> eliminar(vector<int> v1, vector<int> v2){
    
    int i = 0, j = 0;
    int n1 = v1.size();
    int n2 = v2.size();

    vector<int> tmp;

    while (i < n1 && j < n2) {
        if (v1[i] < v2[j]){
            if(v1[i] != v1[i-1])
                tmp.push_back(v1[i]);
            i++;
        }
        else if(v1[i] > v2[j]){
            if(v2[j] != v2[j-1])
                tmp.push_back(v2[j]);
            j++;
        }
        else if(v1[i] == v2[j]){
            if(v1[i] != v1[i-1] && v2[i] != v2[i-1])
                tmp.push_back(v1[i]);
            i++;
            j++;
        }
        
    }
    while (i < n1){
        if(v1[i] != v1[i-1])
            tmp.push_back(v1[i]);
        i++;
    }

    while (j < n2){
        if(v2[j] != v2[j-1])
            tmp.push_back(v2[j]);
        j++;
    }
    v1.clear();
    v2.clear();
    return tmp;
}


vector<int> eliminarRepeticiones(vector<int> v){
    if (v.size() != 1){

        int m = (v.size())/2;
        vector<int> v1;
        vector<int> v2;

        for(int i = 0; i < m; i++)
            v1.push_back(v[i]);
        for(int i = m; i < v.size(); i++)
            v2.push_back(v[i]);
        

        v1 = eliminarRepeticiones(v1);
        v2 = eliminarRepeticiones(v2);

        
        v = eliminar(v1, v2);
    } 
    return v;
}



//generador de ejemplos para el problema de eliminar elementos repetidos. Simplemente, para rellenar el vector de tamaño n genera n enteros aleatorios entre 0 y n-1

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
  int n1;
  vector<int> v;

  srand(time(0));
  //para generar un vector que pueda tener elementos repetidos
  for (int j=0; j<n; j++) {
    double u=uniforme();
    int k=(int)(n*u);
    v.push_back(k);
  }
  //cout << "Vector antes de eliminar duplicados" << endl;
  //for (int j=0; j<n; j++) {cout << v[j] << " ";}

  //
 
  tantes = clock();
  v = eliminarRepeticiones(v);  
  tdespues = clock();
  cout << n <<" "<<((double)(tdespues-tantes))/CLOCKS_PER_SEC << endl;



  //cout << "\nVector despues de eliminar duplicados" << endl;
  //for (int j=0; j<n1; j++) {cout << T[j] << " ";}

} 