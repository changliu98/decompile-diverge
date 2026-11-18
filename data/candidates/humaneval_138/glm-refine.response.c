bool is_valid_size(int n)
{
    // Returns true if n is even and greater than or equal to 8
    return (n >= 8) && !(n & 1);
}