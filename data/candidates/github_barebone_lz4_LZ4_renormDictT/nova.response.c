static void LZ4_renormDictT(struct kvm_vcpu *vcpu, u32 count)
{
	unsigned long exit_qualification;
	unsigned long old_count;
	int i;

	
	if (vcpu->arch.apf.msr_val + count > 0x80000000u) {
		old_count = vcpu->arch.apf.msr_val - 0x10000u;
		exit_qualification = vcpu->arch.apf.qual + vcpu->arch.apf.count;
		for (i = 0; i < 4096; i++) {
			if (vcpu->arch.apf.pages[i] > old_count)
				vcpu->arch.apf.pages[i] = 0;
			else
				vcpu->arch.apf.pages[i] -= old_count;
		}
		vcpu->arch.apf.msr_val = 0x10000u;
	}

	
	if (vcpu->arch.apf.count + count > 0x10000u)
		vcpu->arch.apf.count = 0x10000u;
	else
		vcpu->arch.apf.count += count;

	
	vcpu->arch.apf.qual += (0x10000u - vcpu->arch.apf.count);
}