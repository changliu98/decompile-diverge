int stb_combinations(int n, int t, int ***combinations)
{
	int **comb;
	int *c = calloc(t + 3, sizeof(int));
	int current = 0;
	/* The number of combinations = n! / (t! * (n-t)!) */
	int nCr = stb_factorial(n) / (stb_factorial(t) * stb_factorial(n - t));
	/* Allocate matrix */
	comb = (int **)stb_allocmat(nCr, t, sizeof(int));

	int j, x;
	/* Initialize */
	for (j = 1; j <= t; j++) {
		c[j] = j - 1;
	}

	c[t + 1] = n;
	c[t + 2] = 0;
	j = t;

	for (;;) {
		stb_visit(c, t, &comb, current++);

		while (j > 0) {
			x = j;
			/* Increase */
			c[j] = x;
			j = j - 1;
			stb_visit(c, t, &comb, current++);
		}

		while ((c[1] + 1) < c[2]) {
			c[1] = c[1] + 1;
			stb_visit(c, t, &comb, current++);

			while (j > 0) {
				x = j;
				/* Increase */
				c[j] = x;
				j = j - 1;
				stb_visit(c, t, &comb, current++);
			}
		}

		j = 2;

		/* Find J */
		c[j - 1] = j - 2;
		x = c[j] + 1;

		while (x == c[j + 1]) {
			j = j + 1;
			c[j - 1] = j - 2;
			x = c[j] + 1;
		}

		/* Done? */
		if (j > t) {
			*combinations = comb;
			free(c);
			return nCr;
		}

		c[j] = x;
		j = j - 1;
	}
}