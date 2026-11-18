void _vector_swap(ch_vector_t* first, ch_vector_t* second)
{
    ch_vector_t temp = *first;
    *first = *second;
    *second = temp;
}