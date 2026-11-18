int func0(int radius)
{
    int a, b, rectangles = 0;
    for (a = 1; a < 2 * radius; a++)
        for (b = 1; b < 2 * radius; b++)
            if (a * a + b * b <= 2 * radius * 2 * radius)
                rectangles++;
    return rectangles;
}