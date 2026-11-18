__attribute__((used)) static int
l2tp_show_sopts(struct l2tp_show_info *info, unsigned char *cp, unsigned int length)
{
	unsigned int i = 0;
	unsigned int sopt_type;
	unsigned int sopt_len;

	while (i < length) {
		if (info->offset > info->length - 2 || i + 1 > info->length - 2) {
			trunc;
			break;
		}

		sopt_type = cp[i];
		if (sopt_type == 0) {
			sopt_len = 1;
		} else if (i + 1 < length) {
			if (info->offset > info->length - 2 || i + 2 > info->length - 2) {
				trunc;
				break;
			}
			sopt_len = cp[i + 1] + 2;
		} else {
			trunc;
			break;
		}

		if (i + sopt_len > length) {
			trunc;
			break;
		}

		if (info->offset > info->length - 2 || i + sopt_len > info->length - 2) {
			trunc;
			break;
		}

		switch (sopt_type) {
		case 0:
			info->show(info, "(pad1)");
			break;
		case 1:
			if (length - i < 3) {
				info->show(info, "(padn: trunc)");
				trunc;
			} else
				info->show(info, "(padn)");
			break;
		case 2:
			if (length - i < 5) {
				info->show(info, "(refresh: trunc)");
				trunc;
			} else
				info->show(info, "(refresh: %u)", EXTRACT_16BITS(cp + i + 2) * 4);
			break;
		case 3:
			if (length - i < 19) {
				info->show(info, "(altcoa: trunc)");
				trunc;
			} else
				info->show(info, "(alt-CoA: %s)", getname6(info, cp + i + 2));
			break;
		case 4:
			if (length - i < 7) {
				info->show(info, "(ni: trunc)");
				trunc;
			} else
				info->show(info, "(ni: ho=0x%04x co=0x%04x)",
					   EXTRACT_16BITS(cp + i + 2),
					   EXTRACT_16BITS(cp + i + 4));
			break;
		case 5:
			if (length - i < 13) {
				info->show(info, "(auth: trunc)");
				trunc;
			} else
				info->show(info, "(auth)");
			break;
		default:
			if (length - i < 3) {
				info->show(info, "(sopt_type %u: trunc)", sopt_type);
				trunc;
			} else
				info->show(info, "(type-0x%02x: len=%u)", sopt_type, cp[i + 1]);
			break;
		}

		i += sopt_len;
	}

	int done = 0;
	if (i < length)
		done = 1;

	return done;
}