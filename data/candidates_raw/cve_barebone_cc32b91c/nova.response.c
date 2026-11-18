int func0(struct seat seats[MAXSEAT], struct seat *seat, int cid,
              char *sid) {
    int i = seat->row;
    int j = seat->col;
    int found = 0;
    int k = seat_id;
    struct seat *s;

    do {
        s = &seats[k];
        if (s->row == i && s->col == j && s->state == OCCUP) {
            if (s->sid == seat_id(seats, &seats[k])) {
                seat_id = k;
                *sid = s->letter;
                found = 1;
            }
        }
        if (++k >= MAXSEAT)
            k = 0;
    } while (k!= seat_id &&!found);

    return found;
}