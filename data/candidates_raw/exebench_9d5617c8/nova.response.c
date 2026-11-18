static void func0(NVGpoint* p, float c)
{
	float x = p->x;
	float y = p->y;
	float dx = p->tangent1.x;
	float dy = p->tangent1.y;
	float ddx = dx + dy;
	float ddy = -dx + dy;
	dx = dx * c;
	dy = dy * c;
	ddx = ddx * c;
	ddy = ddy * c;
	p->x = x + dx;
	p->y = y + dy;
	p->tangent1.x = dx + ddx;
	p->tangent1.y = dy + ddy;
}