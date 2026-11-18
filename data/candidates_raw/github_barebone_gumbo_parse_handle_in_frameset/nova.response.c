static int func0(js_State *J, js_Buffer *sb)
{
	int cont;
	do {
		if (sb->length == 4) {
			func04(J, sb);
			cont = 1;
		} else if (sb->length == 3) {
			func03(J, js_tostring(J), sb);
			cont = 1;
		} else if (sb->length == 0) {
			func00(J, sb);
			js_pushnumber(J, 0);
			cont = 0;
		} else if (jsY_accept(sb, 1, 0)) {
			func01(J, sb);
			cont = 1;
		} else if (jsY_accept(sb, 1, 0x81)) {
			func01(J, sb);
			js_pushnumber(J, 0);
			cont = 0;
		} else if (jsY_accept(sb, 1, 0x82)) {
			func01(J, sb);
			js_pushnumber(J, 20);
			cont = 1;
		} else if (jsY_accept(sb, 1, 0x84)) {
			func01(J, sb);
			cont = 0;
		} else {
			cont = 1;
		}
	} while (cont);
	return cont;
}