char * func0(int year) {
    int zodiac = (year - 2000) % 12;
    if (zodiac < 0) {
        zodiac += 12;
    }
    switch (zodiac) {
        case 0: return "Dragon";
        case 1: return "Snake";
        case 2: return "Horse";
        case 3: return "sheep";
        case 4: return "Monkey";
        case 5: return "Rooster";
        case 6: return "Dog";
        case 7: return "Pig";
        case 8: return "Rat";
        case 9: return "Ox";
        case 10: return "Tiger";
        default: return "Hare";
    }
}