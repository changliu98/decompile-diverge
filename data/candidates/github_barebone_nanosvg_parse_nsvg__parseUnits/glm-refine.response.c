int __cdecl nsvg__parseUnits(const char *units)
{
    if (units[0] == 'p' && units[1] == 'x')
        return NSVG_UNITS_PX;
    if (units[0] == 'p' && units[1] == 't')
        return NSVG_UNITS_PT;
    if (units[0] == 'p' && units[1] == 'c')
        return NSVG_UNITS_PC;
    if (units[0] == 'm' && units[1] == 'm')
        return NSVG_UNITS_MM;
    if (units[0] == 'c' && units[1] == 'm')
        return NSVG_UNITS_CM;
    if (units[0] == 'i' && units[1] == 'n')
        return NSVG_UNITS_IN;
    if (units[0] == '%')
        return NSVG_UNITS_PERCENT;
    if (units[0] == 'e' && units[1] == 'm')
        return NSVG_UNITS_EM;
    if (units[0] == 'e' && units[1] == 'x')
        return NSVG_UNITS_EX;
    return NSVG_UNITS_USER;
}