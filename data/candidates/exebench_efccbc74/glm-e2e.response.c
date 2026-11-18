int meat_time_which_month(const char *str, unsigned long len) {
    static const char a_ref_month[12][3] = {
        {'J', 'a', 'n'}, {'F', 'e', 'b'}, {'M', 'a', 'r'}, {'A', 'p', 'r'},
        {'M', 'a', 'y'}, {'J', 'u', 'n'}, {'J', 'u', 'l'}, {'A', 'u', 'g'},
        {'S', 'e', 'p'}, {'O', 'c', 't'}, {'N', 'o', 'v'}, {'D', 'e', 'c'}
    };
    
    int month = 0;
    char found = 0;

    if (len == 3) {
        while (!found && month < 12) {
            if (str[0] == a_ref_month[month][0] &&
                str[1] == a_ref_month[month][1] &&
                str[2] == a_ref_month[month][2]) {
                found = 1;
            } else {
                month++;
            }
        }
    }

    if (!found) {
        return -1;
    }
    
    return month;
}