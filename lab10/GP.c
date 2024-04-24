#include"GP.h"
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
#include<ctype.h>

typedef struct Edge 
{
    int src, dest, weight;
}Edge;

typedef struct Subset 
{
    int parent;
    int rank;
}Subset;

void initializeGraph(Graf* graph) 
{
    graph->nr_noduri = 0;
    for (int i = 0; i < MAX_NR_NODURI; i++) 
    {
        for (int j = 0; j < MAX_NR_NODURI; j++) 
        {
            graph->Arce[i][j] = 0;
        }
    }
}

void insertNode(Graf* graph, Nod nod) 
{
    if (graph->nr_noduri < MAX_NR_NODURI) 
    {
        graph->Noduri[graph->nr_noduri++] = nod;
    } 
    else 
    {
        printf("Nu se poate insera nod: numărul maxim de noduri a fost atins.\n");
    }
}

void insertArc(Graf* graph, Arc arc) 
{
    if (arc.idx_nod_1 >= 0 && arc.idx_nod_1 < graph->nr_noduri && arc.idx_nod_2 >= 0 && arc.idx_nod_2 < graph->nr_noduri) {
        graph->Arce[arc.idx_nod_1][arc.idx_nod_2] = arc.weight;
        graph->Arce[arc.idx_nod_2][arc.idx_nod_1] = arc.weight;
    } 
    else 
    {
        printf("Nodurile specificate nu sunt valide: %d %d.\n",arc.idx_nod_1,arc.idx_nod_2);
    }
}

void deleteNode(Graf* graph, int node_index) 
{
    if (node_index < 0 || node_index >= graph->nr_noduri) 
    {
        printf("Nodul specificat nu există.\n");
        return;
    }
    for (int i = 0; i < graph->nr_noduri; i++) 
    {
        graph->Arce[node_index][i] = 0;
        graph->Arce[i][node_index] = 0;
    }
    graph->Noduri[node_index] = graph->Noduri[graph->nr_noduri - 1];
    graph->nr_noduri--;
}


void deleteArc(Graf* graph, int node_index_1, int node_index_2) 
{
    if (node_index_1 < 0 || node_index_1 >= graph->nr_noduri || node_index_2 < 0 || node_index_2 >= graph->nr_noduri) 
    {
        printf("Nodurile specificate nu sunt valide.\n");
        return;
    }
    if (graph->Arce[node_index_1][node_index_2] == 0) 
    {
        printf("Nu există arc între nodurile specificate.\n");
        return;
    }
    graph->Arce[node_index_1][node_index_2] = 0;
    graph->Arce[node_index_2][node_index_1] = 0;
}


void displayGraph(Graf* graph) 
{
    printf("Graful:\n");
    for (int i = 0; i < graph->nr_noduri; i++) 
    {
        printf("Nod %d (%d): ", i, graph->Noduri[i].cheie);
        for (int j = 0; j < graph->nr_noduri; j++) 
        {
            if (graph->Arce[i][j] != 0) 
            {
                printf("%d (greutate: %d) ", j, graph->Arce[i][j]);
            }
        }
        printf("\n");
    }
}

void Prim(Graf* graph, int start_node) 
{
    int parent[MAX_NR_NODURI];
    int key[MAX_NR_NODURI];
    int mstSet[MAX_NR_NODURI];
    for (int i = 0; i < graph->nr_noduri; i++) 
    {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }
    key[start_node] = 0;
    parent[start_node] = -1;
    for (int count = 0; count < graph->nr_noduri - 1; count++) 
    {
        int u, min = INT_MAX;
        for (int v = 0; v < graph->nr_noduri; v++) 
        {
            if (mstSet[v] == 0 && key[v] < min) 
            {
                min = key[v];
                u = v;
            }
        }
        mstSet[u] = 1;
        for (int v = 0; v < graph->nr_noduri; v++) 
        {
            if (graph->Arce[u][v] && mstSet[v] == 0 && graph->Arce[u][v] < key[v]) 
            {
                parent[v] = u;
                key[v] = graph->Arce[u][v];
            }
        }
    }
    printf("Graful ponderat folosind algoritmul lui Prim începând de la nodul %d:\n", graph->Noduri[start_node].cheie);
    for (int i = 0; i < graph->nr_noduri; i++) 
    {
        if (parent[i] != -1) 
        {
            printf("%d - %d\n", parent[i], i);
        }
    }
}

int compare(const void* a, const void* b) 
{
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

int find(Subset subsets[], int i) 
{
    if (subsets[i].parent != i) 
    {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void Union(Subset subsets[], int x, int y) 
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
    if (subsets[xroot].rank < subsets[yroot].rank) 
    {
        subsets[xroot].parent = yroot;
    } 
    else if (subsets[xroot].rank > subsets[yroot].rank) 
    {
        subsets[yroot].parent = xroot;
    } 
    else 
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int KruskalCuSortare(Graf* graph) 
{
    Edge result[MAX_NR_NODURI];
    int na=0;
    int e = 0;
    int i = 0;
    Edge* edges = (Edge*)malloc(graph->nr_noduri * graph->nr_noduri * sizeof(Edge));
    if(edges==NULL)
    {
        perror("Memorie insuficienta\n");
        exit(0);
    }
    for (int u = 0; u < graph->nr_noduri; u++) 
    {
        for (int v = 0; v < graph->nr_noduri; v++) 
        {
            if (graph->Arce[u][v] != 0) 
            {
                edges[e].src = u;
                edges[e].dest = v;
                edges[e].weight = graph->Arce[u][v];
                e++;
            }
        }
    }
    qsort(edges, e, sizeof(edges[0]), compare);
    Subset* subsets = (Subset*)malloc(graph->nr_noduri * sizeof(Subset));
    if(subsets==NULL)
    {
        perror("Memorie insuficienta\n");
        exit(0);
    }
    for (int v = 0; v < graph->nr_noduri; v++) 
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    /*while (i < graph->nr_noduri - 1 && e > 0) 
    {
        Edge next_edge = edges[e - 1];
        e--;
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);
        if (x != y) 
        {
            result[i++] = next_edge;
            Union(subsets, x, y);
            na=na+next_edge.weight;
        }
    }*/
    for(int j=0;j<e;j++) 
    {
        Edge next_edge = edges[j];
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);
        if (x != y) 
        {
            result[i++] = next_edge;
            Union(subsets, x, y);
            na=na+next_edge.weight;
        }
    }
    printf("Graful ponderat folosind algoritmul lui Kruskal cu sortare:\n");
    for (int j = 0; j < i; j++) 
    {
        printf("%d - %d\n", result[j].src, result[j].dest);
    }
    free(edges);
    free(subsets);
    return na;
}

int KruskalFaraSortare(Graf* graph) 
{
    Edge result[MAX_NR_NODURI];
    int na=0;
    int i = 0;
    Subset* subsets = (Subset*)malloc(graph->nr_noduri * sizeof(Subset));
    if(subsets==NULL)
    {
        perror("Memorie insuficienta\n");
        exit(0);
    }
    for (int v = 0; v < graph->nr_noduri; v++) 
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    for (int u = 0; u < graph->nr_noduri; u++) 
    {
        for (int v = 0; v < graph->nr_noduri; v++) 
        {
            if (graph->Arce[u][v] != 0) 
            {
                Edge next_edge;
                next_edge.src = u;
                next_edge.dest = v;
                next_edge.weight = graph->Arce[u][v];
                int x=find(subsets,next_edge.src);
                int y=find(subsets,next_edge.dest);
                if(x!=y)
                {
                    result[i++]=next_edge;
                    Union(subsets,x,y);
                    na=na+next_edge.weight;
                }
            }
        }
    }
    printf("Graful ponderat folosind algoritmul lui Kruskal fara sortare:\n");
    for (int j = 0; j < i; j++) 
    {
        printf("%d - %d\n", result[j].src, result[j].dest);
    }
    free(subsets);
    return na;
}