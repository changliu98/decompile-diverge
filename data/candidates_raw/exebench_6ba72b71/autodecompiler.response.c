void meters_to_units(long *meters, long *feet, long *inches, long *yards, long *miles)
{
    *feet = *meters * 3.280839895;
    *inches = *meters * 39.37007874;
    *yards = *meters * 1.0936132983;
    *miles = *meters * 0.000621371192;
}