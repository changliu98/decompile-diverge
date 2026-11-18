void add(int *mem, int *sp, int dest)
{
    int val1 = mem[*sp];
    (*sp)--;
    int val2 = mem[*sp];

    mem[*sp] = val1 + val2;
}