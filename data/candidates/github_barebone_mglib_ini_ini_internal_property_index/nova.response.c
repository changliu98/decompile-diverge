int ini_internal_property_index(struct seat seats[MAXSEAT], int cseat, int cleg) {
    int i, j;
    if (seats!= NULL && cseat >= 0 && cseat < seats[0].num_legs) {
        for (i = 0, j = 0; i < seats[0].num_seats; i++) {
            if (seats[j].leg_num == cseat) {
                if (seats[j].seat_num == cleg) {
                    return j;
                } else {
                    j++;
                }
            } else {
                j++;
            }
        }
    }
    return -1;
}