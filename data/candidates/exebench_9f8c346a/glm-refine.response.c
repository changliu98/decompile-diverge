void __cdecl bn_sqr_comba4(unsigned __int64 *r, const unsigned __int64 *a)
{
    unsigned __int64 c1, c2, c3;   // 192-bit accumulator (c1:low, c2:mid, c3:high)
    unsigned __int64 lo, hi;       // Temporary storage for 128-bit product halves
    unsigned __int64 t;            // Temporary variable for sums

    // --- Round 0 ---
    // c1:c2:c3 = a[0] * a[0]
    lo = a[0] * a[0];
    hi = __umulh(a[0], a[0]);
    c1 = lo;
    c2 = hi;
    c3 = 0;
    r[0] = c1;

    // --- Round 1 ---
    // c1:c2:c3 += 2 * (a[0] * a[1])
    lo = a[0] * a[1];
    hi = __umulh(a[0], a[1]);
    
    t = c2 + lo;
    c3 += (t < c2);            // carry from c2 + lo
    c2 = t + lo;
    c3 += (c2 < t);            // carry from t + lo (doubling)
    c3 += hi + hi;             // add doubled high part
    
    r[1] = c2;

    // --- Round 2 ---
    // c1:c2:c3 = c3:c2 (shift accumulator right by 64 bits)
    c1 = c2;
    c2 = c3;
    c3 = 0;
    
    // c1:c2:c3 += 2 * (a[0] * a[2])
    lo = a[0] * a[2];
    hi = __umulh(a[0], a[2]);
    
    t = c2 + lo;
    c3 += (t < c2);
    c2 = t + lo;
    c3 += (c2 < t);
    c3 += hi + hi;
    
    // c1:c2:c3 += a[1] * a[1]
    lo = a[1] * a[1];
    hi = __umulh(a[1], a[1]);
    
    t = c2 + lo;
    c3 += (t < c2);
    c2 = t;
    c3 += hi;
    
    r[2] = c2;

    // --- Round 3 ---
    // c1:c2:c3 = c3:c2
    c1 = c2;
    c2 = c3;
    c3 = 0;
    
    // c1:c2:c3 += 2 * (a[0] * a[3])
    lo = a[0] * a[3];
    hi = __umulh(a[0], a[3]);
    
    t = c2 + lo;
    c3 += (t < c2);
    c2 = t + lo;
    c3 += (c2 < t);
    c3 += hi + hi;
    
    // c1:c2:c3 += 2 * (a[1] * a[2])
    lo = a[1] * a[2];
    hi = __umulh(a[1], a[2]);
    
    t = c2 + lo;
    c3 += (t < c2);
    c2 = t + lo;
    c3 += (c2 < t);
    c3 += hi + hi;
    
    r[3] = c2;

    // --- Round 4 ---
    // c1:c2:c3 = c3:c2
    c1 = c2;
    c2 = c3;
    c3 = 0;
    
    // c1:c2:c3 += 2 * (a[1] * a[3])
    lo = a[1] * a[3];
    hi = __umulh(a[1], a[3]);
    
    t = c2 + lo;
    c3 += (t < c2);
    c2 = t + lo;
    c3 += (c2 < t);
    c3 += hi + hi;
    
    // c1:c2:c3 += a[2] * a[2]
    lo = a[2] * a[2];
    hi = __umulh(a[2], a[2]);
    
    t = c2 + lo;
    c3 += (t < c2);
    c2 = t;
    c3 += hi;
    
    r[4] = c2;

    // --- Round 5 ---
    // c1:c2:c3 = c3:c2
    c1 = c2;
    c2 = c3;
    c3 = 0;
    
    // c1:c2:c3 += 2 * (a[2] * a[3])
    lo = a[2] * a[3];
    hi = __umulh(a[2], a[3]);
    
    t = c2 + lo;
    c3 += (t < c2);
    c2 = t + lo;
    c3 += (c2 < t);
    c3 += hi + hi;
    
    r[5] = c2;

    // --- Round 6 ---
    // c1:c2:c3 = c3:c2
    c1 = c2;
    c2 = c3;
    c3 = 0;
    
    // c1:c2:c3 += a[3] * a[3]
    lo = a[3] * a[3];
    hi = __umulh(a[3], a[3]);
    
    t = c2 + lo;
    c3 += (t < c2);
    c2 = t;
    c3 += hi;
    
    r[6] = c2;
    r[7] = c3;
}