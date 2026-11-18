int func0(char *dateString)
{
    int index;
    int month, day, year;

    // Check if the date string length is exactly 10 characters (MM-DD-YYYY)
    if (strlen(dateString) != 10) {
        return 0;
    }

    // Validate the format: positions 2 and 5 must be '-', others must be digits
    for (index = 0; index < 10; index++) {
        if (index == 2 || index == 5) {
            if (dateString[index] != '-') {
                return 0;
            }
        } else if (dateString[index] < '0' || dateString[index] > '9') {
            return 0;
        }
    }

    // Parse month, day, and year from the string
    month = atoi(dateString);
    day = atoi(dateString + 3);
    year = atoi(dateString + 6);

    // Validate month range (1-12)
    if (month < 1 || month > 12) {
        return 0;
    }
    // Validate day range (1-31)
    if (day < 1 || day > 31) {
        return 0;
    }
    // Validate days in months with 30 days (April, June, September, November)
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day == 31) {
        return 0;
    }
    // Validate February days (max 29)
    if (month == 2 && day > 29) {
        return 0;
    }

    // Return 1 if the date is valid
    return 1;
}