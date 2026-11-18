static unsigned long func0(struct kvm_vcpu *vcpu)
{
	unsigned long nr_running;
	unsigned long nr_threads;

	if (!vcpu) {
		nr_running = 0;
	} else if (vcpu->arch.cputm_enabled == -1UL) {
		
		nr_running = 0;
	} else {
		nr_threads = vcpu->arch.cputm_enabled;
		if (vcpu->arch.cputm_start <= vcpu->arch.cputm)
			nr_threads -= vcpu->arch.cputm_start;
		else
			nr_threads -= vcpu->arch.cputm;

		if (vcpu->arch.cputm_deadline <= vcpu->arch.cputm)
			nr_threads -= vcpu->arch.cputm_deadline;
		else
			nr_threads -= vcpu->arch.cputm;
	}

	if (!kvm_read_cr4_bits(vcpu, X86_CR4_TIMER_GATE))
		nr_running = 0;
	else
		nr_running = nr_threads;

	return nr_running;
}