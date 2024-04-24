#ifndef GP_H
#define GP_H

#define MAX_NR_NODURI 100

typedef struct TipNod 
{
    int cheie;
    int info;
}Nod;

typedef struct TipArc 
{
    int idx_nod_1, idx_nod_2;
    int weight;
}Arc;

typedef struct Graf 
{
    int nr_noduri;
    Nod Noduri[MAX_NR_NODURI];
    int Arce[MAX_NR_NODURI][MAX_NR_NODURI];
}Graf;

void initializeGraph(Graf* graph);
void insertNode(Graf* graph, Nod nod);
void insertArc(Graf* graph, Arc arc);
void deleteNode(Graf* graph, int node_index);
void deleteArc(Graf* graph, int node_index_1, int node_index_2);
void displayGraph(Graf* graph);
void Prim(Graf* graph, int start_node);
int KruskalCuSortare(Graf* graph);
int KruskalFaraSortare(Graf* graph);

#endif