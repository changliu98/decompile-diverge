intptr_t __cdecl atomic_fetch_and(intptr_t *object, intptr_t operand)
{
    intptr_t old_value = *object;
    *object = old_value & operand;
    return old_value;
}