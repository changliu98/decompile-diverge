int q_GetMemoryInformation(q_size_t *total, q_size_t *free)
{
    *total = 10 * 1024 * 1024;
    *free = 5 * 1024 * 1024;

    return 0;
}