static int nsvg__parseUnits(const char* units)
{
	if (units[0] == 'p' && units[1] == 'x')
		return NSVG_UNITS_PX;
	else if (units[0] == 'p' && units[1] == 't')
		return NSVG_UNITS_PT;
	else if (units[0] == 'p' && units[1] == 'c')
		return NSVG_UNITS_PC;
	else if (units[0] == 'm' && units[1] == 'm')
		return NSVG_UNITS_MM;
	else if (units[0] == 'c' && units[1] == 'm')
		return NSVG_UNITS_CM;
	else if (units[0] == 'i' && units[1] == 'n')
		return NSVG_UNITS_IN;
	else if (units[0] == '%')
		return NSVG_UNITS_PERCENT;
	else if (units[0] == 'e' && units[1] == 'm')
		return NSVG_UNITS_EM;
	else if (units[0] == 'e' && units[1] == 'x')
		return NSVG_UNITS_EX;
	return NSVG_UNITS_USER;
}