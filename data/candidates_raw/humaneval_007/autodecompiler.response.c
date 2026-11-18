char** filter_array(char** array, int size, char* str, int* return_size)
{
    char** ret = NULL;
    int ret_size = 0;

    for(int i = 0; i < size; ++i)
    {
        if(strstr(array[i], str) != NULL)
        {
            ret = realloc(ret, sizeof(char*) * (ret_size + 1));
            ret[ret_size] = array[i];
            ret_size++;
        }
    }

    *return_size = ret_size;
    return ret;
}