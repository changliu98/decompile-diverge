void operacao_dist(struct Point *p1, struct Point *p2, int dx, int dy) {
    int new_x = p1->x + dx;
    int new_y = p1->y + dy;
    
    p2->x = new_x;
    p2->y = new_y;
}