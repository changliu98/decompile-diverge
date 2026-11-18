bool __cdecl pmic_thermal_is_aux(int address)
{
    if (address >= 4 && address <= 64 && (address - 4) % 12 == 0)
        return true;

    if (address >= 8 && address <= 68 && (address - 8) % 12 == 0)
        return true;

    return false;
}