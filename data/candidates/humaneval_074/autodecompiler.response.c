char** func0(char** arr1, int sz1, char** arr2, int sz2) {
    int len1 = 0, len2 = 0;
    for (int i = 0 ; i < sz1 ; ++i)
        len1 += strlen(arr1[i]);
    for (int i = 0 ; i < sz2 ; ++i)
        len2 += strlen(arr2[i]);

    char** ret;
    if (len1 < len2)
        ret = arr1;
    else if (len1 > len2)
        ret = arr2;
    else
        ret = arr1;

    return ret;
}