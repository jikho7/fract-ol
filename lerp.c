//lerp.c
double lerp(double start, double end, double alpha);
double invlerp(double start, double end, double value);
double remap(double input_a, double input_b, double out_a, double out_b, double value);

double lerp(double start, double end, double alpha)
{
	return (end - start) * alpha + start;
}

double invlerp(double start, double end, double value)
{
	return (value - start) / (end - start);
}

double remap(double input_a, double input_b, double out_a, double out_b, double value)
{
	return lerp(out_a, out_b, invlerp(input_a, input_b, value));
}

int ft_center_f(double *x, double *y)
{
	*x = ((WID / 4) * 2) + (*x);
	*y = ((HEI / 4) * 2) - (*y);

	*x = -2 + (*x / WID) * 4;
	*y = -2 + (*y / HEI) * 4;
	return (0);
}
