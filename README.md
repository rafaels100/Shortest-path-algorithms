# Shortest-path-algorithms
Implementation of famous algorithms for finding the shortest path between nodes in a graph

## Bellman Ford
This algorithm is capable of finding the shortest path from one node to the others. Its complexity is O(N * M), since for each node, we'll be checking each edge
and seeing if we are able to update the shortest path estimate to a smaller value.

In the implementation, I use the example provided in the book 'Introduction to Algorithms' - Thomas H. Cormen. Here it is:
![Example of BellmanFord aplication](./BellmanFord/ej_BellmanFord_CORMEN.png)

### HOW IT WORKS
Two important quantities are to be stored in this algorithm, that is:

$ds$ : The 'shortest-path estimate'

And

$v.\pi$ : the predecesor of v


