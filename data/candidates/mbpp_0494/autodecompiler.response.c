char * func0(int tup[], int dim) {
    int num = 0;
    int i = 0;
    while (1) {
        if (i >= dim) break;
        num += tup[i] * pow(2.0, (double)(dim-1-i));
        i++;
    }
    char * str = (char *)malloc(sizeof(char)*12);
    sprintf(str, "%d", num);
    return str;
}