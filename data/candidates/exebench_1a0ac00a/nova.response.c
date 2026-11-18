void agrega(int *front, int *rear, int item, int queue[]) {
    if (*front == -1) {
        *front = *rear = item;
    } else {
        queue[*rear] = item;
        *rear = item;
    }
    queue[*rear] = -1;
}