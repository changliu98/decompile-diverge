static int func0(RAnal *anal, const char *func, ut64 addr) {
	if (addr > 0 && func[0]!= '\0') {
		anal->fcn_cur = func[0];
		return 1;
	}
	return 0;
}