#include <iostream>
#include <vector>

using namespace std;
int n, m;
int INF = 1000;
vector<pair<int, int>> E;
vector<vector<int>> W;
vector<int> ancestros;
vector<int> ws_ancestros;
vector<int> ds;

bool BF(int r){
  ds.clear();
  ds.resize(n, INF);
  ds[r] = 0;
  ancestros.resize(n, -1);
  ancestros[r] = r;
  for (int i = 0; i < n; i++) {
    for (pair<int, int> arista : E) {
      if (arista.first == i || arista.second == i) {
        if (arista.first == i) {
          //significa que voy del nodo i en el que estoy parado a otro. Debo relajar comparando lo que puedo
          //ofrecer con lo que el otro nodo ya tiene.
          if (ds[arista.second] > ds[i] + W[i][arista.second]) {
            ds[arista.second] = ds[i] + W[i][arista.second];
            ancestros[arista.second] = i;
          }
        }else{
          //significa que es una arista que llega a mi. Veo si lo que ofrece el nodo que llega + la arista que compartimos,
          //es mejor de lo que yo ya tengo
          if (ds[i] > ds[arista.first] + W[arista.first][i]) {
            ds[i] = ds[arista.first] + W[arista.first][i];
            ancestros[i] = arista.first;
          }
        }
      }
    }
  }
  //chequeo por ciclos negativos
  //para ello, para cada nodo i veo que pasa con su ancestro, y si otra 'vuelta' del ancestro al nodo i usando el peso w seria capaz de mejorar
  //el estimado de camino minimo de la raiz al nodo i. Si es asi, significa que hay un ciclo negativo, pues empezaria a updatearse con valores
  //mas y mas negativos cada vez que hago la comparacion.
  for (int i = 0; i < n; i++) {
    if (ds[i] < ds[ancestros[i]] + W[ancestros[i]][i]) {
      return false;
    }
  }
  return true;
}

int main(){
  n = 5;
  m = 10;
  W.resize(n, vector<int>(n, -1));
  E = {{0, 1}, {0, 2}, {1, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4}, {3, 1}, {4, 0}, {4, 3}};
  W[0][1] = 6;
  W[0][2] = 7;
  W[1][2] = 8;
  W[1][3] = 5;
  W[1][4] = -4;
  W[2][3] = -3;
  W[2][4] = 9;
  W[3][1] = -2;
  W[4][0] = 2;
  W[4][3] = 7;
  cout << BF(0) << endl;
  cout << "ds, los caminos minimos estimados que al final son camino minimo: " << endl;
  for (int elem : ds) cout << elem << " ";
  cout << endl;
  cout << "ancestros: " << endl;
  for (int elem : ancestros) cout << elem << " ";
  cout << endl;
  //creo una matriz que tendra la distancia de todos a todos. Inicialmente la distancia de todos a todos es infinita, excepto
  //por la diagonal, que tiene la distancia de los nodos a si mismos
  vector<vector<int>> M_ds(n, vector<int>(n, INF));
  for (int i = 0; i < n; i++) M_ds[i][i] = 0;
  //de hecho este paso no es necesario, cuando corra BF la distancia de cada nodo a si mismo se va a setear sola a 0
  
  //itero por cada vertice y calculo el vector de distancias ds para cada vertice, hacia todos los demas
  for (int i = 0; i < n; i++) {
    BF(i);
    M_ds[i] = ds;
  }
  //veo la matriz de distancias
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << M_ds[i][j] << " ";
    }
    cout << endl;
  }
  return 0;
}
