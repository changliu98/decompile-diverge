char *zodiac(int year) {
    int z = (year - 2000) % 12;
    if (z < 0) z += 12;

    char *c;
    switch (z) {
        case 0: c = "Dragon"; break;
        case 1: c = "Snake"; break;
        case 2: c = "Horse"; break;
        case 3: c = "sheep"; break;
        case 4: c = "Monkey"; break;
        case 5: c = "Rooster"; break;
        case 6: c = "Dog"; break;
        case 7: c = "Pig"; break;
        case 8: c = "Rat"; break;
        case 9: c = "Ox"; break;
        case 10: c = "Tiger"; break;
        case 11: c = "Hare"; break;
    }
    return c;
}