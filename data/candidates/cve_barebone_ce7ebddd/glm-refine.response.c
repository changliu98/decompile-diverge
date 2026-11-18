void delete_buff_tail(buffheader_T *restrict buf, int slen) 
{
    // Cache the current buffer string pointer to avoid redundant pointer chasing
    char *restrict str = buf->bh_curr->b_str;
    size_t len = strlen(str);

    // Check if the requested deletion length is valid and within the string's length
    if (slen > 0 && (size_t)slen <= len) 
    {
        // Truncate the string by placing a null-terminator at the new end position
        str[len - slen] = '\0';
        
        // Reclaim the deleted space back into the buffer's available space counter
        buf->bh_space += slen;
    }
}