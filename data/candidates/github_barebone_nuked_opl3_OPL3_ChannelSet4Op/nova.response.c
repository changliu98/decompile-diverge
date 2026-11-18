void OPL3_ChannelSet4Op(struct sudoku *puzzle, char c) {
    unsigned char i;
    for (i = 0; i < 9; i++) {
        if (check_row(puzzle, i, c) == 1) {
            puzzle->possibilities[i][64] = 1;
            puzzle->possibilities[i][65] = 2;
            print_puzzle(puzzle);
        } else {
            puzzle->possibilities[i][64] = 0;
            puzzle->possibilities[i][65] = 0;
            print_puzzle(puzzle);
            OPL3_ChannelSet4Op(puzzle, i + 3);
        }
    }
}