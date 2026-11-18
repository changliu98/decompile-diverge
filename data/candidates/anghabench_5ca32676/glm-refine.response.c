void __cdecl wht4x4(int16_t *coef)
{
    int a, b, c, d, t;

    // Horizontal transform (processes 4 rows)
    for (int row = 0; row < 4; ++row)
    {
        b = coef[row * 4 + 1];
        c = coef[row * 4 + 2];
        
        a = coef[row * 4 + 0] + b;
        d = coef[row * 4 + 3] - c;
        
        t = (a - d) / 2;
        b = t - b;
        c = t - c;
        
        coef[row * 4 + 0] = a - c;
        coef[row * 4 + 1] = c;
        coef[row * 4 + 2] = d + b;
        coef[row * 4 + 3] = b;
    }

    // Vertical transform (processes 4 columns)
    for (int col = 0; col < 4; ++col)
    {
        b = coef[4 + col];
        c = coef[8 + col];
        
        a = coef[0 + col] + b;
        d = coef[12 + col] - c;
        
        t = (a - d) / 2;
        b = t - b;
        c = t - c;
        
        // Note: The vertical pass scales the output by 2
        coef[0 + col]  = 2 * (a - c);
        coef[4 + col]  = 2 * c;
        coef[8 + col]  = 2 * (d + b);
        coef[12 + col] = 2 * b;
    }
}