void ecRotate(struct Point *p, double angle_sin, double angle_cos) {
    // p->y * angle_cos + p->x * angle_sin
    double new_y = p->y * angle_cos + p->x * angle_sin;
    
    // p->y * angle_sin - p->x * angle_cos
    // The XOR with 0x8000000000000000 is equivalent to negating a double.
    double new_x = p->y * angle_sin + (-p->x * angle_cos);
    
    p->y = new_y;
    p->x = new_x;
}