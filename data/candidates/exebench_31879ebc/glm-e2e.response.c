float vec4f_dot(const vec4f *a, const vec4f *b) {
    return a->x * b->x + 
           a->y * b->y + 
           a->z * b->z + 
           a->w * b->w;
}