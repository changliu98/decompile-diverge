int cJSON_GetArraySize(struct cJSON *array)
{
    struct cJSON *next;
    int count = 0;
    if(!array)
        return 0;
    for(next = array->child; next != ((void *)0); next = next->next)
        count++;
    return count;
}