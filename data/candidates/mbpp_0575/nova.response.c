int func0(int n, int t, int k, int d) {
    int time = 0, refunc0der;
    refunc0der = k;
    while (1) {
        if (refunc0der <= d) {
            if (refunc0der % n!= 0)
                time++;
            if (time == t)
                break;
        }
        refunc0der++;
    }
    return refunc0der;
}