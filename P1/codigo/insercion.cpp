/**
   @file Ordenaci�n por inserci�n
*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <chrono>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;
using namespace std::chrono;

/* ************************************************************ */ 
/*  M�todo de ordenaci�n por inserci�n  */

/**
   @brief Ordena un vector por el m�todo de inserci�n.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: n�mero de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de inserci�n.
*/
inline static 
void insercion(int T[], int num_elem);



/**
   @brief Ordena parte de un vector por el m�todo de inserci�n.

   @param T: vector de elementos. Tiene un n�mero de elementos 
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posici�n que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posici�n detr�s de la �ltima de la parte del
                   vector a ordenar. 
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de inserci�n.
*/
static void insercion_lims(int T[], int inicial, int final);



/**
   Implementaci�n de las funciones
**/

inline static void insercion(int T[], int num_elem)
{
  insercion_lims(T, 0, num_elem);
}


static void insercion_lims(int T[], int inicial, int final)
{
  int i, j;
  int aux;
  for (i = inicial + 1; i < final; i++) {
    j = i;
    while ((T[j] < T[j-1]) && (j > 0)) {
      aux = T[j];
      T[j] = T[j-1];
      T[j-1] = aux;
      j--;
    };
  };
}

int main(int argc, char *argv[])
{
  const unsigned GAP = 12;
  ofstream salida("salidas/insercion.dat", ios::app);
  if (!salida)
  {
    cerr << "Error al abrir el fichero de salida";
    exit(1);
  }

  if (argc != 2)
  {
    cerr << "Formato " << argv[0] << " <num_elem>" << endl;
    return -1;
  }

  int n = atoi(argv[1]);

  int *T = new int[n];
  assert(T);

  srandom(time(0));

  for (int i = 0; i < n; i++)
  {
    T[i] = random();
  }
  std::vector<duration<double, std::milli>> score(100);

  for (auto &s : score)
  {
    auto start = high_resolution_clock::now();
    insercion(T, n);
    auto stop = high_resolution_clock::now();

    s = stop - start;
  }

  std::nth_element(score.begin(),
                   score.begin() + score.size() / 2,
                   score.end());
  for (unsigned i = 0; i < n; i++)
    cout << T[i];

  salida << std::setw(GAP) << n
         // << std::setw(GAP) << std::fixed << std::setprecision(1)
         << std::setw(GAP) << score[score.size() / 2].count()
         << std::endl;

  delete[] T;
  salida.close();

  return 0;
};