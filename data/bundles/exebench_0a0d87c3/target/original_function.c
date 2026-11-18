void swap(int *param1, int *param2){ int buffer = 0;
    buffer = *param1;
    *param1 = *param2;
    *param2 = buffer;
}