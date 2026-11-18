/**
 * @brief Calculates the n-th hexagonal number.
 * 
 * In mathematics, a hexagonal number is a figurate number that 
 * represents a hexagon. The formula for the n-th hexagonal number is:
 * H_n = n * (2n - 1)
 * 
 * @param n The index (position) of the hexagonal number.
 * @return int The computed n-th hexagonal number.
 */
int __cdecl get_hexagonal_number(int n)
{
    return n * (2 * n - 1);
}