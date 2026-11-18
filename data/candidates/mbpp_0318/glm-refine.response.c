int __cdecl func0(int s)
{
    int max_product = 0;

    // 'a' represents the first integer. 
    // It only needs to iterate up to 's - 2' because 'b' and 'c' must be at least 1.
    for (int a = 1; a < s - 1; ++a)
    {
        // 'b' represents the second integer.
        for (int b = 1; b < s; ++b)
        {
            // 'c' is derived as the remainder to satisfy the sum constraint: a + b + c = s
            int c = s - a - b;

            // Since 'a' and 'b' are strictly positive (>= 1), 'c' will only be positive 
            // if a + b < s. If c <= 0, the product is non-positive and won't affect max_product.
            if (c > 0)
            {
                int current_product = a * b * c;
                if (current_product > max_product)
                {
                    max_product = current_product;
                }
            }
        }
    }

    return max_product;
}