int func0(int a, int b, int c) {
    int arr[3] = {a, b, c};
    int count = 0;
    int visited[3];
    memset(visited, 0, sizeof(visited));
    
    for (int i = 0; i < 3; i++) {
        int is_duplicate = 0;
        for (int j = 0; j < i; j++) {
            if (arr[j] == arr[i]) {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate) {
            count++;
        }
    }
    
    if (count == 3) {
        return 0;
    } else {
        return 4 - count;
    }
}