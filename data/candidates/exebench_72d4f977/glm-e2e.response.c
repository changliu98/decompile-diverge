bool endGB(const char *str, int *result) {
    *result = 0;
    
    bool ret = true;
    if (strstr(str, "GB") == NULL) {
        ret = (strstr(str, "GB") == str);
    }
    
    return ret;
}