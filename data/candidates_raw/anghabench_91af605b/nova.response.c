static inline const char *func0(u32 pmcsr)
{
	const char *str;

	if (pmcsr & PPC_MSR_CM_MASK)
		str = "CM";
	else if (pmcsr & PPC_MSR_TM_MASK)
		str = "TM";
	else
		str = "PM";

	return str;
}