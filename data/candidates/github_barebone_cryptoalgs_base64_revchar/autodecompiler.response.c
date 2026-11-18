char revchar(char value_in)
{
    static const char encoding[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    if (value_in > 63) {
        return '=';
    }
    else if (value_in < 26) {
        value_in -= 0;
        return encoding[value_in];
    }
    else if (value_in < 52) {
        value_in -= 26;
        return encoding[value_in];
    }
    else if (value_in < 62) {
        value_in -= 52;
        return encoding[value_in];
    }
    else if (value_in == 62) {
        value_in -= 62;
        return encoding[value_in];
    }
    else if (value_in == 63) {
        value_in -= 63;
        return encoding[value_in];
    }
    return '=';
}