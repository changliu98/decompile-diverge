const char* func0(int year) {
    int remainder = (year - 2000) % 12;
    if (remainder < 0) {
        remainder += 12;
    }
    
    const char* result;
    switch (remainder) {
        case 0:
            result = "Dragon";
            break;
        case 1:
            result = "Snake";
            break;
        case 2:
            result = "Horse";
            break;
        case 3:
            result = "Goat";
            break;
        case 4:
            result = "Monkey";
            break;
        case 5:
            result = "Rooster";
            break;
        case 6:
            result = "Dog";
            break;
        case 7:
            result = "Pig";
            break;
        case 8:
            result = "Rat";
            break;
        case 9:
            result = "Ox";
            break;
        case 10:
            result = "Tiger";
            break;
        default:
            result = "Rabbit";
            break;
    }
    
    return result;
}