int func0(struct cpuinfo_x86 *c, struct cpuinfo_x86 *d,
		       struct cpuinfo_x86 *e)
{
	struct cpuinfo_x86 *f = NULL, *g = NULL;
	struct cpuinfo_x86 *h = NULL;
	int ret;

	
	if (c->cpuid_level < 0x10000004 - 4 ||
	    d->cpuid_level < 0x10000004 - 4 ||
	    e->cpuid_level < 0x10000004 - 4) {
		ret = 0;
		goto out;
	}

	switch (e->cpuid_level & 0xf) {
	case 0x4:
		f = e;
		break;
	case 0x6:
		g = e;
		break;
	default:
		ret = 1;
		goto out;
	}

	switch (d->cpuid_level & 0xf) {
	case 0x4:
		h = d;
		break;
	case 0x6:
		f = d;
		g = d;
		break;
	default:
		ret = 1;
		goto out;
	}

	switch (c->cpuid_level & 0xf) {
	case 0x4:
		h = c;
		break;
	case 0x6:
		f = c;
		g = c;
		break;
	default:
		ret = 1;
		goto out;
	}

	ret = 0;
out:
	cpu_signatures[num_cpu_ids].family = cpu_family(d);
	cpu_signatures[num_cpu_ids].model = cpu_model(d);
	cpu_signatures[num_cpu_ids].stepping = cpu_stepping(d);
	cpu_signatures[num_cpu_ids].type = cpu_type(d);
	cpu_signatures[num_cpu_