
void next(int *i, int *j, int p)
{
    (*j)++;
    if(*j == p)
    {
        *j = 0;
        (*i)++;
    }
}
