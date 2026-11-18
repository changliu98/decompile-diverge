char *test_to_str(int test)
{
	switch (test) {
	case SENDMSG:
		return "sendmsg";
	case SENDPAGE:
		return "sendpage";
	}
	return "unknown";
}