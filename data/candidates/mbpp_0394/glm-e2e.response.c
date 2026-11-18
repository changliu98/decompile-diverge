bool func0(int *arr, int n) {
    bool is_unique = true;
    int seen[n];
    int seen_count = 0;

    for (int i = 0; i < n; i++) {
        int current = arr[i];
        bool found = false;
        
        for (int j = 0; j < seen_count; j++) {
            if (seen[j] == current) {
                found = true;
                break;
            }
        }
        
        if (found) {
            is_unique = false;
            break;
        }
        
        seen[seen_count] = current;
        seen_count++;
    }
    
    return is_unique;
}