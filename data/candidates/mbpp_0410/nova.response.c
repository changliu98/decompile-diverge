int func0(char **lines, int n) {
    int i, min = INT_MAX, dist;
    for (i = 0; i < n; i++) {
        if (sscanf(lines[i], " #%*[0 ]%n", &dist) == 0)
            continue;
        if (dist < min)
            min = dist;
    }
    return min;
}