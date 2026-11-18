char* func0(int interval1_start, int interval1_end, int interval2_start, int interval2_end) {
    int start = interval1_start > interval2_start ? interval1_start : interval2_start;
    int end = interval1_end < interval2_end ? interval1_end : interval2_end;
    int interval = end - start;
    if (interval < 2)
        return "NO";
    for (int i = 2; i * i <= interval; i++)
        if (interval % i == 0)
            return "NO";
    return "YES";
}