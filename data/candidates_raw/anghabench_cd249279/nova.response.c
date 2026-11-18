int func0(int pid) {
    int i;
    int index;

    for (i = 0; i < MAXJOBS; i++) {
        if (jobs[i].pid == pid) {
            index = i;
            break;
        }
    }
    if (i == MAXJOBS)
        index = -1;
    return index;
}