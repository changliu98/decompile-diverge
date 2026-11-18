void removeSocketFromCache(int socket, int socketCache[], int *socketCounter) {
    int i = 0;
    while (1) {
        if (i >= 3) {
            break;
        }
        if (socketCache[i] == socket) {
            socketCache[i] = 0;
        } else {
            i++;
        }
    }
    close(socket);
    (*socketCounter)--;
}