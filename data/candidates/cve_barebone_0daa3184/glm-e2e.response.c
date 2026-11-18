struct ByteStringNode *lookup_bytestring(struct Logger *logger, const char *str, unsigned int len) {
    unsigned int prefix0 = 0;
    unsigned int prefix1 = 0;
    unsigned int prefix2 = 0;

    if (len >= 6) {
        prefix0 = ((unsigned char)str[0] << 8) | (unsigned char)str[1];
        prefix1 = ((unsigned char)str[2] << 8) | (unsigned char)str[3];
        prefix2 = ((unsigned char)str[4] << 8) | (unsigned char)str[5];
    } else if (len >= 4) {
        prefix0 = ((unsigned char)str[0] << 8) | (unsigned char)str[1];
        prefix1 = ((unsigned char)str[2] << 8) | (unsigned char)str[3];
        prefix2 = 0;
    } else {
        prefix0 = 0;
        prefix1 = 0;
        prefix2 = 0;
    }

    unsigned int hash = (prefix2 ^ prefix1) & 0xfff;
    struct ByteStringNode *node = &bytestringtable[hash];

    while (node->next != NULL) {
        if (node->prefix[0] == prefix0 &&
            node->prefix[1] == prefix1 &&
            node->prefix[2] == prefix2 &&
            memcmp(str, node->data, len) == 0) {
            return node;
        }
        node = node->next;
    }

    node->prefix[0] = prefix0;
    node->prefix[1] = prefix1;
    node->prefix[2] = prefix2;
    node->data = calloc(1, len + 1);
    if (!node->data) {
        logger->log(logger, "Out of memory!");
    }
    memcpy(node->data, str, len);

    node->next = calloc(1, sizeof(struct ByteStringNode));
    if (!node->next) {
        logger->log(logger, "Out of memory!");
    }

    return node;
}