#include <iostream>
#include <vector>

using namespace std;

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

int main(){
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

  cout << movimientoLegal(tablero, 1, 3, 2) << endl;
  hacerMovimiento(tablero, 1, 3, 2);
  muestraTablero(tablero);

}
