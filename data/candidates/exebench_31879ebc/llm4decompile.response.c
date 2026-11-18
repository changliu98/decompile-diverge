float vec4f_dot(t_vec4f *a, t_vec4f *b)
{
 return (a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w);
}