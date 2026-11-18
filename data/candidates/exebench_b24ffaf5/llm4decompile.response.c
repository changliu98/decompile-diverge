int OS_file_open(OS_file_handle *p_file_handle, const char *p_filename)
{
    int ret;

    *p_file_handle = (OS_file_handle)open(p_filename, 0);

    if(*p_file_handle == (OS_file_handle)-1)
    {
        ret = 0x1004;
    }
    else
    {
        ret = 0;
    }

    return ret;
}