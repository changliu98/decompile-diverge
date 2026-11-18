int pmic_thermal_is_aux(int address)
{
	int channel;

	if (address >= 4 && address <= 64 &&
		(address - 4) % 12 == 0)
		channel = 1;
	else if (address >= 8 && address <= 68 &&
		(address - 8) % 12 == 0)
		channel = 1;
	else
		channel = 0;

	return (channel % 2) ? 1 : 0;
}