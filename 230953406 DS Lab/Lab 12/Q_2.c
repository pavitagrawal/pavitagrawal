#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph
{
    int vertices;
    Node** adjList;//array of ll
} Graph;

Node* createNode(int vertex)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) //vertices is the number of vertices
{
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;// no of vertices bataye
    graph->adjList = (Node**)malloc(vertices * sizeof(Node*));//adjlist ko sahi size diya ie saare vertices
    for (int i = 0; i < vertices; i++)
        graph->adjList[i] = NULL;//default setup
    return graph;
}

void addEdgeUndirected(Graph* graph, int start, int end)//inset begin of nodes
{
    Node* newNode = createNode(end);
    newNode->next = graph->adjList[start];
    graph->adjList[start] = newNode;

    newNode = createNode(start);
    newNode->next = graph->adjList[end];
    graph->adjList[end] = newNode;
}

void addEdgeDirected(Graph* graph, int start, int end)
{
    Node* newNode = createNode(end);
    newNode->next = graph->adjList[start];
    graph->adjList[start] = newNode;
}

void displayGraph(Graph* graph)
{
    for (int i = 0; i < graph->vertices; i++)
    {
        Node* current = graph->adjList[i];
        printf("Adjacency list for vertex %d: ", i);
        while (current != NULL)
        {
            printf("%d -> ", current->vertex);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int vertices, edges, i, start, end, isDirected;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    Graph* graph = createGraph(vertices);
    printf("Is the graph directed? (1 for yes, 0 for no): ");
    scanf("%d", &isDirected);
    printf("Enter the number of edges: ");
    scanf("%d", &edges);
    printf("Enter the edges (start and end vertex) separated by space:\n");
    for (i = 0; i < edges; i++)
    {
        scanf("%d %d", &start, &end);
        if (isDirected)
            addEdgeDirected(graph, start, end);
        else
            addEdgeUndirected(graph, start, end);
    }
    displayGraph(graph);
    return 0;
}
