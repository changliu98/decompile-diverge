int get_list(int *list, int *first)
{
    int size = 10 - 1;
    int cnt = 0;
    int i = 0;

    while (1) {
        if (i >= size) {
            break;
        }
        if (list[i] != 0) {
            cnt++;
            if (first) {
                *first = list[i];
            }
        } else {
            i++;
            continue;
        }
        i++;
    }

    return cnt;
}