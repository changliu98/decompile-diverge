static char func0(const vec3_t normal)
{
	char axis;

	if (normal[0] > AXIS_NORMAL_EPSILON)
	{
		axis = 'x';
	} 
	else if (normal[1] > AXIS_NORMAL_EPSILON)
	{
		axis = 'y';
	} 
	else if (normal[2] > AXIS_NORMAL_EPSILON)
	{
		axis = 'z';
	} 
	else
	{
		if (normal[0] + normal[1] > normal[2])
		{
			if (normal[0] / (normal[0] + normal[1]) > AXIS_NORMAL_EPSILON)
			{
				axis = '{';
			} 
			else
			{
				axis = '}';
			} 
		} 
		else
		{
			axis = '|';
		} 
	} 
	return axis;
}