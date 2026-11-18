bool func0(int* arr1, int size1, int* arr2, int size2) {
    bool is_subset = true;
    
    for (int i = 0; i < size2; i++) {
        bool found = false;
        
        for (int j = 0; j < size1; j++) {
            if (arr2[i] == arr1[j]) {
                found = true;
                break;
            }
        }
        
        if (!found) {
            is_subset = false;
            break;
        }
    }
    
    return is_subset;
}