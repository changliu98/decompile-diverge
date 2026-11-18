int __cdecl func0(float a, float b, float c) {
    // All three values must be whole numbers
    if (!is_integer(a) || !is_integer(b) || !is_integer(c)) {
        return 0;
    }

    // Check if any two numbers add up to the third
    if ((float)(a + b) == c) return 1;
    if ((float)(a + c) == b) return 1;
    if ((float)(b + c) == a) return 1;

    return 0;
}