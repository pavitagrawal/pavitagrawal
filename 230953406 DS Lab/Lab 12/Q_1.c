#include <stdio.h>
#define MAX_VERTICES 100

int adjMatrix[MAX_VERTICES][MAX_VERTICES];

void initializeGraph(int v)
{
    int i, j;
    for (i = 0; i < v; i++)
    {
        for (j = 0; j < v; j++)
            adjMatrix[i][j] = 0;
    }
}

void addEdge(int start, int end, int isDir)
{
    adjMatrix[start][end] = 1;
    if (!isDir)
        adjMatrix[end][start] = 1;
}

void display(int v)
{
    int i, j;
    printf("Adjacency Matrix:\n");
    for (i = 0; i < v; i++)
    {
        for (j = 0; j < v; j++)
            printf("%d ", adjMatrix[i][j]);
        printf("\n");
    }
}

int main()
{
    int v, e, i, start, end, isDir;
    printf("Enter the number of vertices: ");
    scanf("%d", &v);
    initializeGraph(v);
    printf("Is the graph directed? (1 for yes, 0 for no): ");
    scanf("%d", &isDir);
    printf("Enter the number of edges: ");
    scanf("%d", &e);
    printf("Enter the edges (start and end vertex) separated by space:\n");
    for (i = 0; i < e; i++)
    {
        scanf("%d %d", &start, &end);
        addEdge(start, end, isDir);
    }
    display(v);
    return 0;
}
