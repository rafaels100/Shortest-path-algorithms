# Shortest-path-algorithms
Implementation of famous algorithms for finding the shortest path between nodes in a graph

## Bellman Ford
This algorithm is capable of finding the shortest path from one node to the others, and is also able to tell us if there's a negative cycle in the graph. 
Its complexity is O(N * M), since for each node we'll be checking each edge and seeing if we are able to update the shortest path estimate to a smaller value.
Since there are other algorithms, like Dijkstra, which are able to find the shortest path with better time complexity, why is this algorithm useful?
Its strength lies in the fact that it can work with negative edges, and it's also able to detect negative cycles.

## Dijkstra
Coming soon to a street near you
