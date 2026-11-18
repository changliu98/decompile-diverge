int romanToInt(char* s) {
    int i;
    int num = 0;
    int rom[256];
    memset(rom, 0, sizeof(rom));
    rom['I'] = 1;
    rom['V'] = 5;
    rom['X'] = 10;
    rom['L'] = 50;
    rom['C'] = 100;
    rom['D'] = 500;
    rom['M'] = 1000;
    int len = strlen(s);
    for (i = 0; i < len; i++) {
        if (i > 0 && rom[s[i]] > rom[s[i-1]]) {
            num += rom[s[i]] - 2 * rom[s[i-1]];
        } else {
            num += rom[s[i]];
        }
    }
    return num;
}