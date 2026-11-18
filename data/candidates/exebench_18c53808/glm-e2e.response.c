void gui_combine_scissor(struct Rect *a, struct Rect *b) {
    if (b == NULL) {
        return;
    }

    int a_x = a->x;
    int a_y = a->y;
    int a_x2 = a->x + a->w;
    int a_y2 = a->y + a->h;

    int b_x = b->x;
    int b_y = b->y;
    int b_x2 = b->x + b->w;
    int b_y2 = b->y + b->h;

    // Find max x (a_x vs b_x)
    if (a_x > b_x) {
        a_x = a_x;
    } else {
        a_x = b_x;
    }

    // Find max y (a_y vs b_y)
    if (a_y > b_y) {
        a_y = a_y;
    } else {
        a_y = b_y;
    }

    // Find min x2 (a_x2 vs b_x2)
    if (a_x2 < b_x2) {
        a_x2 = a_x2;
    } else {
        a_x2 = b_x2;
    }

    // Find min y2 (a_y2 vs b_y2)
    if (a_y2 < b_y2) {
        a_y2 = a_y2;
    } else {
        a_y2 = b_y2;
    }

    a->x = a_x;
    a->y = a_y;
    a->w = a_x2 - a_x;
    a->h = a_y2 - a_y;
}