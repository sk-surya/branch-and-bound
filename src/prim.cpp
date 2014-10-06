/*
 * @file prim.h
 *      
 * @author: Fabio Cruz B. de Albuquerque
 * 
 * Algoritmo de prim adaptado de 
 * http://geeksforgeeks.org/greedy-algorithms-set-5-prims-minimum-spanning-tree-mst-2
 * 
 * @date: 04/10/14
 */

#include "../include/prim.h"

// A utility function to find the vertex with minimum key value, from
// the set of vertices not yet included in MST
int minKey(int key[], bool mstSet[], const unsigned dim) {
    // Initialize min value
    int min_index = -1, min = inf;

    for (unsigned v = 1; v < dim; v++)
        if (mstSet[v] == false && min > key[v])
            min = key[v], min_index = v;

    return min_index;
}

// A utility function to print the constructed MST stored in parent[]
void printMST(int parent[], int ** graph, const unsigned dim) {
    printf("Edge   Weight\n");
    for (unsigned i = 1; i < dim; i++)
        printf("%d - %d    %d \n", parent[i], i, graph[i][parent[i]]);
}

// Function to construct and print MST for a graph represented using adjacency
// matrix representation
void prim1Tree(const unsigned dim, int ** graph, unsigned * degree, bool ** sol1Tree, unsigned &cost) {
    int parent[dim]; // Array to store constructed MST
    int key[dim];   // Key values used to pick minimum weight edge in cut
    bool mstSet[dim];  // To represent set of vertices not yet included in MST

    unsigned count, i, v;
    int u;

    // Initialize all keys as INFINITE
    for (i = 0; i < dim; i++)
        key[i] = inf, mstSet[i] = false, degree[i] = 0, parent[i] = 0;

    // Always include first 1st vertex in MST.
    key[1] = 0;     // Make key 0 so that this vertex is picked as first vertex
    parent[1] = -1; // First node is always root of MST

    // The MST will have dim vertices
    for (count = 0; count < dim-2; count++) {
        // Pick thd minimum key vertex from the set of vertices
        // not yet included in MST

        u = minKey(key, mstSet, dim);
        // solucao inviavel, descarta construcao de MST
        if (u == -1)
            return;

        // Add the picked vertex to the MST Set
        mstSet[u] = true;

        // Update key value and parent index of the adjacent vertices of
        // the picked vertex. Consider only those vertices which are not yet
        // included in MST
        for (v = 1; v < dim; v++)

            // graph[u][v] is non zero only for adjacent vertices of m
            // mstSet[v] is false for vertices not yet included in MST
            // Update the key only if graph[u][v] is smaller than key[v]
            if (graph[u][v] && mstSet[v] == false && graph[u][v] <  key[v])
                parent[v]  = u, key[v] = graph[u][v];
    }

    // print the constructed MST
    //printMST(parent, graph, dim);

    for (i = 2; i < dim; i++) {
        degree[i]++, degree[parent[i]]++;
        sol1Tree[i][parent[i]] = sol1Tree[parent[i]][i] = true;
        cost += graph[i][parent[i]];
    }

    //    delete[] parent;
    //    delete[] key;
    //    delete[] mstSet;
}