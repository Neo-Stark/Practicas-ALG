#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <thread>
#include <chrono>

using namespace std;

string matrixToString(vector<vector<char>> m) {
  string cad = "";
  for (auto fila : m)
    for (auto elemento : fila)
      cad += elemento;
  return cad;
}

struct movimiento{
  int x,y,dir;
  movimiento(int _x, int _y, int _dir):x(_x), y(_y), dir(_dir){}
  movimiento():x(0), y(0), dir(0){}
};


//0->arriba, 1->derecha, 2->abajo, 3->izquierda
bool movimientoLegal(const vector<vector<char> > &tab, int x, int y, int dir){
  if(tab[x][y]!='o')
    return false;

  if(dir == 0)
    return (x > 2 && tab[x-1][y] == 'o' && tab[x-2][y] == '-');
  else if(dir == 1)
    return (y < 5 && tab[x][y+1] == 'o' && tab[x][y+2] == '-');
  else if(dir == 2)
    return (x < 5 && tab[x+1][y] == 'o' && tab[x+2][y] == '-');
  else if(dir == 3)
    return (y > 2 && tab[x][y-1] == 'o' && tab[x][y-2] == '-');

  cout << "Hay un problema gordo si salta este mensaje" << endl;
  return false;
}

//0->arriba, 1->derecha, 2->abajo, 3->izquierda
void hacerMovimiento(vector<vector<char> > &tab, int x, int y, int dir){
  tab[x][y] = '-';
  if(dir == 0){
    tab[x-1][y] = '-';
    tab[x-2][y] = 'o';
  }else if(dir == 1){
    tab[x][y+1] = '-';
    tab[x][y+2] = 'o';
  }else if(dir == 2){
    tab[x+1][y] = '-';
    tab[x+2][y] = 'o';
  }else if(dir == 3){
    tab[x][y-1] = '-';
    tab[x][y-2] = 'o';
  }
}



vector<movimiento> expandir(const vector<vector<char>> &tab){
  vector<movimiento> res;
  int fil = tab.size();
  int col = fil;
  for(int i = 0; i < fil; ++i)
    for(int j = 0; j < col; ++j)
      if(tab[i][j] == 'o')
        for(int k = 0; k < 4; ++k)
          if(movimientoLegal(tab, i , j , k)){
            movimiento tmp(i, j, k);
            res.push_back(tmp);
          }

  return res;
}


bool esSolucion(const vector<vector<char> > &tab){
  for(int i = 0; i < 7; ++i)
    for(int j = 0; j < 7; ++j)
      if(tab[i][j] == 'o' && (i != 3 || j != 3))
        return false;


  return true;
}

void muestraTablero(const vector<vector<char> > &tab) {
  for (auto fila : tab) {
    for (auto elemento: fila)
      cout << elemento << " ";
    cout << endl;
  }
  cout << endl;
}

set<string> estados;

bool encontrarSolucion(vector<vector<char>> &tab, vector<movimiento> &solucion){
  vector<movimiento> hijos = expandir(tab);
  vector<vector<char>> tmp;
  bool sol = false;

  if(hijos.size() == 0) {
    return esSolucion(tab);
  }

  for(auto it = hijos.begin(); it != hijos.end(); ++it){
    tmp = tab;
    hacerMovimiento(tmp, it->x, it->y, it->dir);
    if(estados.find(matrixToString(tmp)) == estados.end()){
      estados.insert(matrixToString(tmp));
      if(encontrarSolucion(tmp, solucion)){
        sol = true;
        solucion.push_back(*it);
        return sol;
      }
    }
  }
  return sol;
}

int main(){
  vector<movimiento> solucion;
  vector<vector<char> > tablero = {
    {' ',' ','o','o','o',' ',' '},
    {' ',' ','o','o','o',' ',' '},
    {'o','o','o','o','o','o','o'},
    {'o','o','o','-','o','o','o'},
    {'o','o','o','o','o','o','o'},
    {' ',' ','o','o','o',' ',' '},
    {' ',' ','o','o','o',' ',' '}
  };

  system("clear");
  muestraTablero(tablero);
  this_thread::sleep_for(chrono::milliseconds(300));
  auto start = chrono::high_resolution_clock::now();
  encontrarSolucion(tablero, solucion);
  auto diff = chrono::high_resolution_clock::now() - start;
  auto t1 = chrono::duration_cast<chrono::duration<double>>(diff);
  

  /*
  cout << "Solucion: " << endl;
  for(auto it = solucion.rbegin(); it != solucion.rend(); ++it)
    cout << it->x << " " << it->y << " " << it->dir << endl;
    */

  //cout << "Tablero solucion " << endl;
  for(auto it = solucion.rbegin(); it != solucion.rend(); ++it){
    hacerMovimiento(tablero, it->x, it->y, it->dir);
    this_thread::sleep_for(chrono::milliseconds(100));
    system("clear");
    muestraTablero(tablero);
  }

  cout << "Movimientos: " << solucion.size() << endl;
  cout << "Tiempo: " << t1.count() << endl;
}
