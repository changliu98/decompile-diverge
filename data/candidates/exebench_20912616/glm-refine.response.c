int __cdecl dupfd(int from, int *to)
{
    if (from == -1) {
        *to = -1;
        return 1;
    }

    *to = dup(from);
    return *to != -1;
}