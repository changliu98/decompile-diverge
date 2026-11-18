char * func0(char * test_list[], int size) {
    int i;
    double first, second;
    char point[100];

    strcpy(func0::res, "[");
    for (i = 0; i < size; i += 2) {
        first = atof(test_list[i]);
        second = atof(test_list[i + 1]);
        snprintf(point, 100, "(%.2f, %.2f)", first, second);
        strcat(func0::res, point);
        if (i < size - 2) {
            strcat(func0::res, ", ");
        }
    }
    strcat(func0::res, "]");

    return func0::res;
}