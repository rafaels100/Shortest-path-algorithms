#include <vector>
#include <iostream>

using namespace std;
int INF = 1000;
int n;
//uso matriz de adyacencia
vector<vector<int>> g = {{0, 2, INF, 3},
                         {3, 0, 2, INF},
                         {INF, INF, 0, 4},
                         {-2, 6, INF, 0}};
  vector<vector<int>> ancestros = {{-1, 0, -1, 0},
                                   {1, -1, 1, -1},
                                   {-1, -1, -1, 2},
                                   {3, 3, -1, -1}};

void FW(){
  
  vector<vector<int>> M = g;
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (M[i][j] > M[i][k] + M[k][j]){
          M[i][j] = M[i][k] + M[k][j];
          ancestros[i][j] = k;
        }
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << M[i][j] << " ";
    }
    cout << endl;
  }
  cout << "ancestros" << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << ancestros[i][j] << " ";
    }
    cout << endl;
  }
  return;
}

vector<int> caminoMinimo(int i, int j) {
    if (ancestros[i][j] == i)
        return {};

    vector<int> result;
    if (ancestros[ancestros[i][j]][j] != ancestros[i][j]) {
        vector<int> left = caminoMinimo(i, ancestros[i][j]);
        vector<int> right = caminoMinimo(ancestros[i][j], j);
        result.insert(result.end(), left.begin(), left.end());
        result.push_back(ancestros[i][j]);
        result.insert(result.end(), right.begin(), right.end());
    } else {
        vector<int> left = caminoMinimo(i, ancestros[i][j]);
        result.insert(result.end(), left.begin(), left.end());
        result.push_back(ancestros[i][j]);
    }
    return result;
}

/*
HOW IT WORKS:
Es una traduccion directa del codigo que hice en python, que practicamente parece pseudocodigo:
def caminoMinimo(i, j):
    if ancestros[i][j] == i:
        return []
    
    if ancestros[ancestros[i][j]][j] != ancestros[i][j]:
        return caminoMinimo(i, ancestros[i][j]) + [ancestros[i][j]] + caminoMinimo(ancestros[i][j], j)
    return  caminoMinimo(i, ancestros[i][j]) + [ancestros[i][j]]
    
La idea es mirar si entre los nodos hay algun nodo intermedio.
Si lo hay, miro tanto la parte izquierda como la parte derecha del camino, y me pregunto si hay mas nodos 'ocultos' en alguna de ellas.
Es como ir creando 'articulaciones', los nodos que estan 'ocultos' van apareciendo nuevamente y creando el camino.
Recursivamente inserto las articulaciones a izquierda, con el nodo que descubri esta entremedio de estos, en el medio, y luego
inserto a derecha las otras articulaciones que pueden surgir a derecha.
*/

int main(){
  n = g.size();
  FW();
  vector<char> nodos = {'A', 'B', 'C', 'D'};
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j) {
        cout << "De " << nodos[i] << " -> " << nodos[j] << ": " << nodos[i] << " ";
        vector<int> camino = caminoMinimo(i, j);
        for (int elem : camino) cout << nodos[elem] << " ";
        cout << nodos[j] << endl;
      }
      
    }
  }
  return 0;
}
