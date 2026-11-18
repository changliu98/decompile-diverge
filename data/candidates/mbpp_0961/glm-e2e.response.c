int func0(const char *s) {
    int map[256];
    memset(map, 0, 0x400);
    
    map['I'] = 1;
    map['V'] = 5;
    map['X'] = 10;
    map['Z'] = 50;
    map['L'] = 50;
    map['C'] = 100;
    map['D'] = 500;
    map['M'] = 1000;
    
    int total = 0;
    int len = strlen(s);
    
    for (int i = 0; i < len; i++) {
        if (i > 0 && map[(unsigned char)s[i]] > map[(unsigned char)s[i - 1]]) {
            total += map[(unsigned char)s[i]] - 2 * map[(unsigned char)s[i - 1]];
        } else {
            total += map[(unsigned char)s[i]];
        }
    }
    
    return total;
}