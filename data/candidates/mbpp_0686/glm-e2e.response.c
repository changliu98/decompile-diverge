char* func0(int* arr, int n) {
    long unique[50];
    int counts[50];
    int unique_count = 0;
    char* result = malloc(1000);
    char buffer[50];

    result[0] = '\0';
    strcat(result, "(");

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < unique_count; j++) {
            if (unique[j] == arr[i]) {
                counts[j]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            unique[unique_count] = arr[i];
            counts[unique_count] = 1;
            unique_count++;
        }
    }

    for (int i = 0; i < unique_count; i++) {
        sprintf(buffer, "(%ld %d)", unique[i], counts[i]);
        strcat(result, buffer);
        if (i < unique_count - 1) {
            strcat(result, ", ");
        }
    }

    strcat(result, ")");
    return result;
}