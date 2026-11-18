char *func0(int a, int b, int c)
{
    char *result;
    int sq_a = pow(a, 2.0);
    int sq_b = pow(b, 2.0);
    int sq_c = pow(c, 2.0);

    if (sq_a == sq_b + sq_c || sq_b == sq_a + sq_c || sq_c == sq_a + sq_b)
        result = "Right-angled Triangle";
    else if (sq_a > sq_b + sq_c || sq_b > sq_a + sq_c || sq_c > sq_a + sq_b)
        result = "Obtuse-angled Triangle";
    else
        result = "Acute-angled Triangle";

    return result;
}