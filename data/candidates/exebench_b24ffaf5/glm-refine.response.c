int __cdecl OS_file_open(uint64_t *p_file_handle, const char *p_filename)
{
    // open() with O_RDONLY (0) - Opens for reading only.
    *p_file_handle = open(p_filename, O_RDONLY);

    // Check if the file descriptor is invalid (-1)
    if (*p_file_handle == (uint64_t)-1)
    {
        return OS_ERR_OPEN_FAILED;
    }

    return OS_SUCCESS;
}