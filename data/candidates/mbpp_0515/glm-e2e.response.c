bool func0(int *arr, int n, int m) {
    bool result;
    bool *visited = alloca(m);
    
    if (n > m) {
        return true;
    }
    
    for (int i = 0; i < m; i++) {
        visited[i] = false;
    }
    
    for (int i = 0; i < n; i++) {
        if (visited[0]) {
            result = true;
            return result;
        }
        
        bool *new_visited = alloca(m);
        for (int j = 0; j < m; j++) {
            new_visited[j] = false;
        }
        
        for (int j = 0; j < m; j++) {
            if (visited[j]) {
                int next = (j + arr[i]) % m;
                if (!visited[next]) {
                    new_visited[next] = true;
                }
            }
        }
        
        for (int j = 0; j < m; j++) {
            if (new_visited[j]) {
                visited[j] = true;
            }
        }
        
        visited[arr[i] % m] = true;
    }
    
    result = visited[0];
    return result;
}