void delete_buff_tail(struct buffer *buff, int len) {
    int current_len = strlen(buff->data + 8);
    
    if (current_len >= len) {
        buff->data[current_len - len + 8] = '\0';
        buff->length += len;
    }
}