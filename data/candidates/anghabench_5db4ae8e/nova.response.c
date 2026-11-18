int rtl8xxxu_gen1_channel_to_group(int x) {
    int i;
    if (x < 5)
        i = 0;
    else if (x < 11)
        i = 1;
    else
        i = 2;
    return i;
}