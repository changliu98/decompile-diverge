char *cJSON_SetValuestring(struct cJSON *item, char *string)
{
    if(!item || (item->type&cJSON_String)==0 || (item->type&cJSON_IsArray)!=0)
        return ((void *)0);
    if(!item->valuestring || !string)
        return ((void *)0);
    if(strlen(string)<=strlen(item->valuestring))
    {
        if(string < item->valuestring && item->valuestring < string + strlen(string))
            return ((void *)0);
        strcpy(item->valuestring,string);
    }
    else
    {
        char *newstring = cJSON_strdup(string);
        if(!newstring)
            return ((void *)0);
        if(item->valuestring)
            cJSON_free(item->valuestring);
        item->valuestring = newstring;
    }
    return item->valuestring;
}