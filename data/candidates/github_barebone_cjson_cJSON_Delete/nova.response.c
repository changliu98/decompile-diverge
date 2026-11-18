void cJSON_Delete(YYSTACKDATA *data) {
    free(data);
    data = NULL;
}