INF = 1000
M = [[0, 2, INF, 3],
     [3, 0, 2, INF],
     [INF, INF, 0, 4],
     [-2, 6, INF, 0]]

ancestros = [[-1, 0, -1, 0],
             [1, -1, 1, -1],
             [-1, -1, -1, 2],
             [3, 3, -1, -1]]
     
def FW():
    for k in range(len(M)):
        for i in range(len(M[0])):
            for j in range(len(M[0])):
                if (M[i][j] > M[i][k] + M[k][j]):
                    M[i][j] = M[i][k] + M[k][j]
                    ancestros[i][j] = k;
    return

def caminoMinimo(i, j):
    if ancestros[i][j] == i:
        return []
    
    if ancestros[ancestros[i][j]][j] != ancestros[i][j]:
        return caminoMinimo(i, ancestros[i][j]) + [ancestros[i][j]] + caminoMinimo(ancestros[i][j], j)
    return  caminoMinimo(i, ancestros[i][j]) + [ancestros[i][j]]
"""
La idea es mirar si entre los nodos hay algun nodo intermedio.
Si lo hay, miro tanto la parte izquierda como la parte derecha del camino, y me pregunto si hay mas nodos 'ocultos' en alguna de ellas.
Es como ir creando 'articulaciones', los nodos que estan 'ocultos' van apareciendo nuevamente y creando el camino.
Recursivamente inserto las articulaciones a izquierda, con el nodo que descubri esta entremedio de estos, en el medio, y luego
inserto a derecha las otras articulaciones que pueden surgir a derecha.
"""

if __name__ == "__main__":
    FW()
    print(M)
    print(ancestros)
    print(caminoMinimo(3, 1))
    
    for i in range(len(M)):
        for j in range(len(M)):
            if (j != i):
                print(f"De {i} -> {j}")
                print([i] + caminoMinimo(i, j) + [j])

