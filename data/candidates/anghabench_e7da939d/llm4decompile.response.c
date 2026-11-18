char *test_to_str(enum test_type test)
{
	char *str;

	switch (test) {
	case SENDPAGE:
		str = "sendpage";
		break;
	case SENDMSG:
		str = "sendmsg";
		break;
	default:
		str = "unknown";
	}
	return str;
}