int func0(int *arr, int n) {
    char buffer[256];
    char temp[16];
    
    memset(buffer, 0, 256);
    
    for (int i = 0; i < n; i++) {
        sprintf(temp, "%d", arr[i]);
        strcat(buffer, temp);
    }
    
    return atoi(buffer);
}