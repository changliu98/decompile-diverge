static int func0(struct kvm_vcpu *vcpu)
{
	int r;

	if (vcpu->arch.pio.count >= 1) {
		vcpu->arch.pio.count++;
		r = 1;
	} else
		r = 0;

	return r;
}