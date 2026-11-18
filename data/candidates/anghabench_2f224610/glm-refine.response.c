bool is_dup(int *seq, int index, int val)
{
    for (int i = 0; i < index; ++i)
    {
        if (seq[i] == val)
            return true;
    }
    return false;
}