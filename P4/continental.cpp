#include <iostream>
#include <vector>

using namespace std;

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
    return (y > 1 && tab[x-1][y] == 'o' && tab[x-2][y] == '-');
  else if(dir == 1)
    return (x < 5 && tab[x][y+1] == 'o' && tab[x][y+2] == '-');
  else if(dir == 2)
    return (y < 5 && tab[x+1][y] == 'o' && tab[x+2][y] == '-');
  else if(dir == 3)
    return (x > 1  && tab[x][y-1] == 'o' && tab[x][y-2] == '-');

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
  for(int i = 0; i < tab.size(); ++i)
    for(int j = 0; j < tab[i].size(); ++j)
      if(tab[i][j] == 'o')
        for(int k = 0; k < 4; ++k)
          if(movimientoLegal(tab, i , j , k)){
            movimiento tmp(i, j, k);
            res.push_back(tmp);
          }
        
  return res;
}


bool esSolucion(const vector<vector<char> > &tab){
  int fichas = 0;
  for(int i = 0; i < 7; ++i)
    for(int j = 0; j < 7; ++j)
      if(tab[i][j] == 'o' && (i != 3 || j != 3))
        return false;


  return true;
}

void muestraTablero(const vector<vector<char> > &tab) {
  for (auto fila : tab) {
    cout << endl;
    for (auto elemento: fila)
      cout << elemento << " ";
  }
}


bool encontrarSolucion(vector<vector<char>> &tab, vector<movimiento> &solucion){
  vector<movimiento> hijos = expandir(tab);
  vector<vector<char>> tmp;
  bool sol = false;

  if(hijos.size() == 0)
    return esSolucion(tab);

  for(auto it = hijos.begin(); it != hijos.end() && !sol; ++it){
    tmp = tab;
    hacerMovimiento(tmp, it->x, it->y, it->dir);
    sol = encontrarSolucion(tmp, solucion);
    if(sol){
      solucion.push_back(*it);
      return sol;
    }
  }
  return sol;
}

int main(){
  vector<movimiento> solucion;
  vector<vector<char> > tablero = {
    {'X','X','o','o','o','X','X'},
    {'X','X','o','o','o','X','X'},
    {'o','o','o','o','o','o','o'},
    {'o','o','o','-','o','o','o'},
    {'o','o','o','o','o','o','o'},
    {'X','X','o','o','o','X','X'},
    {'X','X','o','o','o','X','X'}
  };

  muestraTablero(tablero);
  encontrarSolucion(tablero, solucion);

  cout << "Solucion: " << endl; 
  for(auto it = solucion.begin(); it != solucion.end(); ++it)
    cout << it->x << " " << it->y << " " << it->dir << endl;


}
