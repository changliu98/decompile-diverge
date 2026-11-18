void measure(long *total_inches, int *inches_as_int, int *feet, int *yard, int *mile)
{
    // Set the input value to 0xf780 (63360 in decimal)
    *inches = 0xf780;
    
    // Cast the long value to int and store in inch
    *inch = (int)*inches;
    
    // Convert inches to feet by multiplying with a conversion factor
    *feet = (int)((double)*inches * _DAT_00102018);
    
    // Convert inches to yards by multiplying with a conversion factor
    *yard = (int)((double)*inches * DAT_00102010);
    
    // Convert inches to miles by multiplying with a conversion factor
    *mile = (int)((double)*inches * DAT_00102008);
}