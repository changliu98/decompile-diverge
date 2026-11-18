void delete_buff_tail(StringBuilder *strBuilder, int count) {
    int length = (int)strlen(strBuilder->buffer);
    if (length >= count) {
        strBuilder->buffer[length - count] = '\0';
        strBuilder->length += count;
    }
}