/**
 * @brief Calculates the n-th term of a geometric progression.
 * 
 * Formula: a * r^(n-1)
 * 
 * @param first_term   The first term of the sequence (a).
 * @param term_index   The 1-based index of the term to retrieve (n).
 * @param common_ratio The common ratio of the sequence (r).
 * @return double      The value of the n-th term.
 */
double __cdecl calc_geometric_nth_term(int first_term, int term_index, int common_ratio)
{
    return (double)first_term * pow((double)common_ratio, (double)(term_index - 1));
}