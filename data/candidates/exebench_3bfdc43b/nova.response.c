static void norm(u32 *num, u32 *den, u32 div)
{
	u32 new_den;

	if (*den < div) {
		new_den = ((-1 * (u32)div) + 1) / div;
		*num -= new_den * (*den);
		*den = new_den;
	}

	if (*den >= div) {
		new_den = *den / div;
		*num += new_den;
		*den -= new_den * div;
	}
}