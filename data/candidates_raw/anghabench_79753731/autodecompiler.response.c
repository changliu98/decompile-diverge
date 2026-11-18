__attribute__((used)) static bool ovs_key_attr_may_be_nested(u16 attr, u16 expected_type)
{
	char may_be_nested;

	if (expected_type == attr) {
		may_be_nested = 1;
	} else if (expected_type == OVS_ATTR_NESTED ||
		   expected_type == OVS_ATTR_VARIABLE) {
		may_be_nested = 1;
	} else {
		may_be_nested = 0;
	}

	return may_be_nested & 1;
}