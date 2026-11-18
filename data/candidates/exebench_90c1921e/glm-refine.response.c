void __cdecl ifft8pt(complex_t *io, float scale)
{
    // Load 8 complex input values (16 floats)
    complex_t f0 = io[0];
    complex_t f1 = io[1];
    complex_t f2 = io[2];
    complex_t f3 = io[3];
    complex_t f4 = io[4];
    complex_t f5 = io[5];
    complex_t f6 = io[6];
    complex_t f7 = io[7];

    // Stage 1: 2-point IFFTs
    complex_t s0 = { f0.r + f1.r, f0.i + f1.i };
    complex_t s1 = { f0.r - f1.r, f0.i - f1.i };
    
    complex_t s2 = { f2.r + f3.r, f2.i + f3.i };
    complex_t s3 = { f2.r - f3.r, f2.i - f3.i };
    
    complex_t s4 = { f4.r + f5.r, f4.i + f5.i };
    complex_t s5 = { f4.r - f5.r, f4.i - f5.i };
    
    complex_t s6 = { f6.r + f7.r, f6.i + f7.i };
    complex_t s7 = { f6.r - f7.r, f6.i - f7.i };

    // Stage 2: 4-point IFFTs
    complex_t e0 = { s0.r + s2.r, s0.i + s2.i };
    complex_t e2 = { s0.r - s2.r, s0.i - s2.i };
    
    // IFFT twiddle multiplication by -j for odd elements
    complex_t e1 = { s1.r + s3.i, s1.i - s3.r };
    complex_t e3 = { s1.r - s3.i, s1.i + s3.r };
    
    complex_t e4 = { s4.r + s6.r, s4.i + s6.i };
    complex_t e6 = { s4.r - s6.r, s4.i - s6.i };
    
    complex_t e5 = { s5.r + s7.i, s5.i - s7.r };
    complex_t e7 = { s5.r - s7.i, s5.i + s7.r };

    // Stage 3: 8-point IFFT combination
    complex_t b0 = { e0.r + e4.r, e0.i + e4.i };
    complex_t b4 = { e0.r - e4.r, e0.i - e4.i };
    
    complex_t b2 = { e2.r + e6.i, e2.i - e6.r };
    complex_t b6 = { e2.r - e6.i, e2.i + e6.r };

    // Twiddle factors for 8-point IFFT (W8^1 and W8^3 = sqrt(0.5) * (1 - j) and (-1 - j))
    float sqrt_half = 0.70710677f;
    
    complex_t b1;
    b1.r = e1.r + (e5.r - e5.i) * sqrt_half;
    b1.i = e1.i - (e5.r + e5.i) * sqrt_half;
    
    complex_t b5;
    b5.r = e1.r - (e5.r - e5.i) * sqrt_half;
    b5.i = e1.i + (e5.r + e5.i) * sqrt_half;
    
    complex_t b3;
    b3.r = e3.r - (e7.r + e7.i) * sqrt_half;
    b3.i = e3.i + (e7.r - e7.i) * sqrt_half;
    
    complex_t b7;
    b7.r = e3.r + (e7.r + e7.i) * sqrt_half;
    b7.i = e3.i - (e7.r - e7.i) * sqrt_half;

    // Store scaled results
    io[0] = (complex_t){ scale * b0.r, scale * b0.i };
    io[1] = (complex_t){ scale * b1.r, scale * b1.i };
    io[2] = (complex_t){ scale * b2.r, scale * b2.i };
    io[3] = (complex_t){ scale * b3.r, scale * b3.i };
    io[4] = (complex_t){ scale * b4.r, scale * b4.i };
    io[5] = (complex_t){ scale * b5.r, scale * b5.i };
    io[6] = (complex_t){ scale * b6.r, scale * b6.i };
    io[7] = (complex_t){ scale * b7.r, scale * b7.i };
}