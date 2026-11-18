int stream_open(void* arg1, int arg2, int* arg3) {
    if (arg1 == 0) {
        arg2 = 1;
    }
    
    *arg3 = 1;
    
    return 0;
}