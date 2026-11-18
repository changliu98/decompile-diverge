void
delete_buff_tail(buffheader_T *buf, int slen)
{
    int len;

    if ((len = strlen(buf->bh_curr->b_str)) >= slen)
    {
 buf->bh_curr->b_str[len - slen] = '\0';
 buf->bh_space += slen;
    }
}