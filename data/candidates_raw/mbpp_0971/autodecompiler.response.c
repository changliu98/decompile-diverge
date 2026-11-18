int coin_change_problem(int N, int c1, int c2, int c3) {
    int table[N+10];
    int i;
    for (i = 0; i < N+10; ++i)
        table[i] = -1;

    table[0] = 0;

    int j;
    for (i = 0; i <= N; ++i) {
        if (table[i] == -1)
            continue;
        for (j = 1; j <= 3; ++j) {
            if (i + c1 * j > N)
                break;
            if (table[i] + 1 > table[i + c1 * j])
                table[i + c1 * j] = table[i] + 1;
        }
    }

    return table[N];
}