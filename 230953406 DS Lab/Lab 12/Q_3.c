#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int vertices;
    Node** adjList;
} Graph;

Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->adjList = (Node**)malloc(vertices * sizeof(Node*));
    for (int i = 0; i < vertices; i++)
        graph->adjList[i] = NULL;
    return graph;
}

void addEdgeUndirected(Graph* graph, int start, int end) {
    Node* newNode = createNode(end);
    newNode->next = graph->adjList[start];
    graph->adjList[start] = newNode;

    newNode = createNode(start);
    newNode->next = graph->adjList[end];
    graph->adjList[end] = newNode;
}

void bfs(Graph* graph, int startVertex) {
    bool* visited = (bool*)malloc(graph->vertices * sizeof(bool));
    for (int i = 0; i < graph->vertices; i++)
        visited[i] = false;

    int queue[graph->vertices];
    int front = 0, rear = 0;

    visited[startVertex] = true;
    queue[rear++] = startVertex;

    while (front < rear) {
        int currentVertex = queue[front++];
        printf("Visited %d\n", currentVertex);

        Node* temp = graph->adjList[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }
    free(visited);
}

void displayGraph(Graph* graph) {
    for (int i = 0; i < graph->vertices; i++) {
        Node* current = graph->adjList[i];
        printf("Adjacency list for vertex %d: ", i);
        while (current != NULL) {
            printf("%d -> ", current->vertex);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int vertices, edges, start, end;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    Graph* graph = createGraph(vertices);
    printf("Enter the number of edges: ");
    scanf("%d", &edges);
    printf("Enter the edges (start and end vertex) separated by space:\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &start, &end);
        addEdgeUndirected(graph, start, end);
    }
    displayGraph(graph);
    printf("BFS starting from vertex 0:\n");
    bfs(graph, 0);
    return 0;
}
