int func0(int* machines, int machinesSize, int k) {
    int ret, i, j, m = machines[0], c = 0;

    for (j = 1; ; ++j) {
        if (j < machinesSize)
            m = ((m) > (machines[j]) ? (m) : (machines[j]));
        else {
            for (i = 0; ; ++i) {
                if (i < machinesSize) {
                    if ((m - machines[i]) % k) {
                        ret = -1;
                        goto end;
                    }
                    c += (m - machines[i]) / k;
                }
                else {
                    ret = c;
                    goto end;
                }
            }
        }
    }

end:
    return ret;
}