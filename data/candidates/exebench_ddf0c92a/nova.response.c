void h(struct kvm_vcpu *vcpu, int mode)
{
	vcpu->arch.emulate_regs.mode = mode;
}