#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
int n; //cantidad de vertices
int INF = 1000;
vector<int> ancestros;
vector<int> ds; //shortest path estimates
//tambien creo un vector con los pesos de las aristas que conectan a cada vector con su ancestro, para 
//no tener que andar buscando ese valor cuando haga el chequeo por ciclos negativos
vector<int> ws_ancestros; //pesos de los ancestros

typedef map<int, vector<pair<int, int>>> grafo;
grafo g;

bool bellmanFord(int r){
  //la cantidad de vertices es
  n = g.size();
  //inicializo los vectores de ancestros para que tengan conjunto vacio (-1)
  ancestros.resize(n, -1);
  ancestros[r] = r;
  //inicializo el vector de pesos de ancestros
  ws_ancestros.resize(n, -1);
  ws_ancestros[r] = 0; //pues no tiene ancestros, entonces no tiene peso
  //inicializo el vector de camino minimo estimado al nodo raiz r en infinito, y en 0 a el mismo
  ds.resize(n);
  for (int i = 0; i < n; i++) ds[i] = (i == r) ? 0 : INF;
  for (const auto& [nodo, vecinos] : g){
    //cout << nodo << endl;
    //veo si tengo que actualizarme a mi mismo con info de los nodos que llegan a mi
    for (int i = 0; i < n; i++){
      //busco al nodo actual en el vecindarios del nodo i, para ver si este llega a el
      auto it = find_if(g[i].begin(), g[i].end(), [nodo](const auto& p) { return p.first == nodo; });
      if (it != g[i].end()){
        if (ds[i] + it->second < ds[nodo]) {
          //cout << "entro" << endl;
          ds[nodo] = ds[i] + it->second;
          ancestros[nodo] = i;
          ws_ancestros[nodo] = it->second;
        }
      }
    }
    //updateo los nodos a los que yo llego, con la mejor distancia que puedo tener ya updateada
    for (const auto& vecino : vecinos) {
      //cout << "{" << vecino.first << ", " << vecino.second << "}" << endl; 
      if (ds[nodo] + vecino.second < ds[vecino.first]) {
        //cout << "entro" << endl;
        ds[vecino.first] = ds[nodo] + vecino.second;
        ancestros[vecino.first] = nodo;
        ws_ancestros[vecino.first] = vecino.second;
      }
    }
  }
  for (int nodo = 0; nodo < n; nodo++){
    if (ds[nodo] > ds[ancestros[nodo]] + ws_ancestros[nodo]) {
      cout <<"nodo:" << nodo << " ds ancestro: " << ds[ancestros[nodo]] << ", peso ancestro nodo: " << ws_ancestros[nodo] << endl;
      return false;
    }
  }
  /*
  EXPLICACION DE LA DETECCION DE CICLOS NEGATIVOS
  La idea es ir mirando los ancestros de cada nodo i,y 'hacer una vuelta mas', esto es, ver si yendo nuevamente del ancestro al nodo usando
  la arista con peso w que los une, puedo reducir aun mas el camino minimo estimado de la raiz al nodo i.
  Si descubro que si, significa que me convenia hacer ese update al nodo, lo que a su vez hubiese disminuido el valor para volver a mi ancestro,
  entonces el estimado de camino minimo de mi ancestro tambien hubiese disminuido, y cuando haga la comparacion que hice al ppio de nuevo, otra
  vez se va a cumplir, pues ahora es incluso mejor tomar ese camino. Asi se repite el ciclo vicioso, y todo el ciclo se vuelve infinito negativo.
  */
  return true;
}

int main(){
  g = {{0, vector<pair<int, int>>{{1,6}, {2,7}}},
      {1, vector<pair<int, int>>{{2, 8}, {3, 5}, {4, -4}}},
      {2, vector<pair<int, int>>{{3, -3}, {4, 9}}},
      {3, vector<pair<int, int>>{{1, -2}}},
      {4, vector<pair<int, int>>{{0, 2}, {3, 7}}}
      };
  cout << bellmanFord(0) << endl;
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
  /*
  El error es que solo estoy considerando las aristas de ida desde un nodo, pero debo considerar tambien las aristas que llegan a el.
  Este approach funcionaria si el grafo no fuera dirigido, pues las aristas que van son las mismas que las que vienen, 
  pero como este grafo es dirigido, debo relajar todas las aristas, no solo las que salen del nodo, sino tambien las que llegan.
  
  Por eso la complejidad de BellmanFord es cantNodos * cantAristas, ya que en cada paso debo pararme en cada nodo 
  y mirar alrededor mio, a todas las aristas, tanto las que salen como las que llegan, para ver si algun update
  previo hizo que sea no solo mas facil llegar desde mi a otros vecino, sino desde otros vecinos hacia mi.
  
  El hecho de tener que mirar cada vez que llego a un nuevo nodo no solo a los vecinos a los que yo llego, sino a los 
  que llegan a mi, hace que esta implementacion sea mucho mas amigabe con lista de aristas. Asi es como la definen
  en el libro.
  
  Pero, si no las hubiese implementado como lista de adyacencias, no hubiese apreciado el hecho de que deben ser todas las aristas, no 
  solo las que salen del nodo en donde estoy parado, las que deben considerarse.
  De hecho, lo primero que hay que hacer es ver las aristas que llegan a mi, por si algun cambio en la estimacion de distancia minima
  de los nodos que llegan a mi hace que pueda mejorar mi propia estimacion de distancia minima, y eso hara que mejore a su vez la 
  de los nodos a los que yo llego.
  
  HOLE IN UNDERSTANDING:
  Si uso la lista de aristas... como se que estoy updateando primero las aristas que llegan a mi, antes de tratar de actualizar a las 
  que yo llego ? Porque si encuentro que un nodo de los que llegan a mi ahora tiene mejor distancia minima estimada, debo actualizarme a mi mismo
  antes de empezar a comparar que es lo que pasa con los demas, usandome como punto de referencia.
  Pero cuando llegue a ese nuevo que quiero salvaguardar de mi actualizacion tardia, el tambien va a ver por 
  las nuevas actualizaciones de los que llegan a el, y va a ver que el nodo que le esta llegando ahora tiene mejor distancia minima estimada,
  y lo va a actualizar. Lo mismo pasa con los nodos a los que llega este nuevo nodo, si ocurre que realizo una actualizacion tardia.
  Entonces, todos se actualizan correctamente porque siempre estan mirando hacia atras de nuevo, cuando ya estoy seguro que la actualizacion
  necesaria ya se hizo.
  HOLE SEALED
  */
  
}
