void load_xps(struct Matrix4x4 *dst, const struct Matrix4x4 *src) {
    // The assembly performs a matrix transpose.
    // It reads elements from `src` in row-major order 
    // and writes them to `dst` in column-major order.
    
    dst->m[0][0] = src->m[0][0];
    dst->m[1][0] = src->m[0][1];
    dst->m[2][0] = src->m[0][2];
    dst->m[3][0] = src->m[0][3];
    
    dst->m[0][1] = src->m[1][0];
    dst->m[1][1] = src->m[1][1];
    dst->m[2][1] = src->m[1][2];
    dst->m[3][1] = src->m[1][3];
    
    dst->m[0][2] = src->m[2][0];
    dst->m[1][2] = src->m[2][1];
    dst->m[2][2] = src->m[2][2];
    dst->m[3][2] = src->m[2][3];
    
    dst->m[0][3] = src->m[3][0];
    dst->m[1][3] = src->m[3][1];
    dst->m[2][3] = src->m[3][2];
    dst->m[3][3] = src->m[3][3];
}