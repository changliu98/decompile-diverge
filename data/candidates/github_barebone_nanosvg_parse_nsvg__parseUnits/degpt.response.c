int nsvg__parseUnits(char *unitString)
{
    // Check if the unit string is "px" (pixels)
    if ((*unitString == 'p') && (unitString[1] == 'x')) return 1;
    // Check if the unit string is "pt" (points)
    if ((*unitString == 'p') && (unitString[1] == 't')) return 2;
    // Check if the unit string is "pc" (picas)
    if ((*unitString == 'p') && (unitString[1] == 'c')) return 3;
    // Check if the unit string is "mm" (millimeters)
    if ((*unitString == 'm') && (unitString[1] == 'm')) return 4;
    // Check if the unit string is "cm" (centimeters)
    if ((*unitString == 'c') && (unitString[1] == 'm')) return 5;
    // Check if the unit string is "in" (inches)
    if ((*unitString == 'i') && (unitString[1] == 'n')) return 6;
    // Check if the unit string is "%" (percentage)
    if (*unitString == '%') return 7;
    // Check if the unit string is "em" (relative to current font size)
    if ((*unitString == 'e') && (unitString[1] == 'm')) return 8;
    // Check if the unit string is "ex" (relative to x-height of current font)
    if ((*unitString == 'e') && (unitString[1] == 'x')) return 9;
    // Return 0 if the unit string is not recognized
    return 0;
}