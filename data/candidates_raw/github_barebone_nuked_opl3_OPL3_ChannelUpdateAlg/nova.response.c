void func0(struct seat seat) {
    seat.facing = seat.facing_history[9];

    if (seat.neighbours[332 + 121] == '#') {
        if (seat.facing == 1) {
            seat.neighbours[332 + 121] = '4' | (seat.state << 1);
            seat.facing = 8;
        } else if (seat.facing == 2) {
            seat.neighbours[332 + 121] = '4' | (seat.state << 1);
            seat.facing = 8;
            func0(seat);
        } else {
            func0(seat);
        }
    } else {
        func0(seat);
    }
}