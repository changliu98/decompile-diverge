void dstsub4(int n, struct Point *p) {
    float local_float = 1.0f; // Loaded from 0xe11(%rip)
    int half_n = n >> 1;

    if (half_n == 2) {
        float v1 = local_float * 2.0f; // Loaded from 0xdf9(%rip)
        float v2 = local_float * 1.5f; // Loaded from 0xde3(%rip)
        
        // Calculate new y
        float temp_y = p->y * v1;
        // Bitwise flip of the sign bit (equivalent to negating the float)
        uint32_t temp_bits = *(uint32_t*)&temp_y ^ 0x80000000;
        float neg_temp_y = *(float*)&temp_bits;
        
        float new_y = v2 * p->w + neg_temp_y;
        
        // Calculate new w
        float new_w = v1 * p->w + (p->y * v2);
        
        p->w = new_w;
        p->y = new_y;
    }

    // Scale the element at index half_n
    p[half_n].x *= local_float;
}