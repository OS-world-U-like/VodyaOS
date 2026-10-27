/* double precision helpers used by V7 libm and libc. */

double
frexp(double x, int *e)
{
	int ex = 0;
	double v = x;
	int neg = 0;

	if (v < 0) {
		neg = 1;
		v = -v;
	}
	if (v == 0.0) {
		*e = 0;
		return 0.0;
	}
	while (v >= 1.0) {
		v /= 2.0;
		ex++;
	}
	while (v < 0.5) {
		v *= 2.0;
		ex--;
	}
	*e = ex;
	return neg ? -v : v;
}

double
ldexp(double x, int n)
{
	while (n > 0) {
		x *= 2.0;
		n--;
	}
	while (n < 0) {
		x /= 2.0;
		n++;
	}
	return x;
}

double
modf(double x, double *iptr)
{
	double ip;

	if (x >= 0)
		ip = (double)(long long)x;
	else
		ip = (double)(long long)x;
	*iptr = ip;
	return x - ip;
}
