int read_new_config_info(struct config *config, struct buffer *b) {
    int len = b->len;
    char *data = b->data;
    config->valid = 1;
    config->size = 0;
    config->capacity = 0;
    config->name[0] = '\0';
    while (len) {
        int i;
        while (len && (data[0] =='' || data[0] == '\0')) {
            data++;
            len--;
        }
        config->name[0] = data[0];
        data++;
        len--;
        while (len && (data[0]!='' && data[0]!= '\0')) {
            config->name[config->size] = data[0];
            data++;
            len--;
        }
        if (len) {
            config->size++;
        } else {
            break;
        }
    }
    while (len) {
        config->name[config->size] = data[0];
        data++;
        len--;
    }
    return 1;
}