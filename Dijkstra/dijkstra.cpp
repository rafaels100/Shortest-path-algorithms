#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;
int n; //cantidad de vertices
int INF = 1000;
vector<int> ancestros;
vector<int> ds; //shortest path estimates
//tambien creo un vector con los pesos de las aristas que conectan a cada vector con su ancestro, para 
//no tener que andar buscando ese valor en la lista de adyacencias si lo necesito
vector<int> ws_ancestros; //pesos de los ancestros, de la arista con la que llego desde mi ancestro al nodo i

typedef map<int, vector<pair<int, int>>> grafo;
grafo g;

struct comparator {
    bool operator()(tuple<int, int>& t1, tuple<int, int>& t2) {
         return get<1>(t1) > get<1>(t2);
     }
 };

void dijkstra(int root){
  //inicializo el vector de shortest-path-estimate
  ds.resize(g.size(), INF);
  ds[root] = 0;
  //el ancestro es el mismo
  ancestros.resize(g.size(), -1);
  ancestros[root] = root;
  //los pesos de los ancestros
  ws_ancestros.resize(g.size(), -1);
  //no tiene peso el ancestros porque es el mismo, digamos 0
  ws_ancestros[root] = 0;
  //agrego a la cola de prioridad
  priority_queue<tuple<int, int>, vector<tuple<int, int>>, comparator> pq;
  for (int i = 0; i < g.size(); i++) pq.push(make_tuple(i, ds[i]));
  //una lista que me diga si ya termine con cierto nodo
  vector<int> finalizados(g.size(), 0);
  //veo la cola de prioridad
  while (!pq.empty()){
    //cout << get<0>(pq.top()) << endl;
    int nodo = get<0>(pq.top());
    finalizados[nodo] = 1;
    pq.pop();
    //relajo a todos los nodos de llegada del nodo actual
    for (pair<int, int> vecino : g[nodo]) {
      if (!finalizados[get<0>(vecino)]) {
        if (ds[get<0>(vecino)] > ds[nodo] + get<1>(vecino)) {
          ds[get<0>(vecino)] = ds[nodo] + get<1>(vecino);
          ancestros[get<0>(vecino)] = nodo;
          ws_ancestros[get<0>(vecino)] = get<1>(vecino);
          pq.push(make_tuple(get<0>(vecino), ds[get<0>(vecino)]));
        }
        //voy insertando segun vea otras buenas opciones, que se van a posicionar sobre las otras peores en la cola de prioridad.
        //cuando explore esas mejores opciones, voy a dar a ese nodo por finalizado en el vector de finalizados, por lo que 
        //las 'copias' que deje en el camino, con unas distancias peores a las mas cortas que fui encontrando, no
        //van a pasar el test de !finalizados, y van a salir de mi cola de prioiridad sin haber agregar nada a la misma
      }
    }
  }
  return;
}


int main(){
  g = {{0, vector<pair<int, int>>{{1,10}, {2,5}}},
      {1, vector<pair<int, int>>{{2, 2}, {3, 1}}},
      {2, vector<pair<int, int>>{{1, 3}, {3, 9}, {4, 2}}},
      {3, vector<pair<int, int>>{{4, 4}}},
      {4, vector<pair<int, int>>{{0, 7}, {3, 6}}}
      };
  dijkstra(0);
  cout << "ds, los caminos minimos estimados que al final son camino minimo: " << endl;
  for (int elem : ds) cout << elem << " ";
  cout << endl;
  cout << "ancestros: " << endl;
  for (int elem : ancestros) cout << elem << " ";
  cout << endl;
  cout << "pesos ancestros:" << endl;
  for (int elem : ws_ancestros) cout << elem << " ";
  cout << endl;
  return 0;
}
