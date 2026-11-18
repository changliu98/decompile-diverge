int **func0(int **graph, int v, int *indegree, int n, int *count) {
    int **queue = (int **)malloc(100 * sizeof(int *));
    int front = 0, rear = 0;
    for (; rear < v; rear++) {
        int i = indegree[rear] - 1;
        for (; i >= 0; i--) {
            if (graph[rear][i] == n) {
                queue[front] = (int *)malloc(2 * sizeof(int));
                queue[front][0] = rear;
                queue[front][1] = i;
                front++;
            }
        }
    }
    *count = front;
    return queue;
}