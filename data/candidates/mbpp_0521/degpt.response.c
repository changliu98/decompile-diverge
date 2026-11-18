// Returns true if all three arguments are distinct, false otherwise.
_Bool func0(int first, int second, int third)
{
    // Returns true if x != y AND y != z AND z != x
    return !((first == second) || (second == third) || (third == first));
}