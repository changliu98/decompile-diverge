int func0(int inputValue, int timeValue) {
    double resultValue;
    double scaledPowerValue;
    double timeScaledValue;
    double powerValue;
    
    // Calculate dVar1 using t and global constants DAT_00102020 and _DAT_00102028
    resultValue = (double)timeValue * DAT_00102020 + _DAT_00102028;
    
    // Calculate dVar2 as v raised to the power of DAT_00102008, then scaled by DAT_00102018
    scaledPowerValue = pow((double)inputValue, DAT_00102008);
    scaledPowerValue = scaledPowerValue * DAT_00102018;
    
    // Calculate dVar3 as t scaled by DAT_00102010
    timeScaledValue = DAT_00102010 * (double)timeValue;
    
    // Recalculate dVar4 as v raised to the power of DAT_00102008 (same as initial dVar2 calculation)
    powerValue = pow((double)inputValue, DAT_00102008);
    
    // Update dVar1 by rounding the sum of dVar3 * dVar4, dVar2, and the original dVar1
    resultValue = round(timeScaledValue * powerValue + scaledPowerValue + resultValue);
    
    // Return dVar1 cast to an integer
    return (int)resultValue;
}