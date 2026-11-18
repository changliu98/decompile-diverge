static void decrement(struct kvm_vcpu *vcpu)
{
	vcpu->arch.regs.nip -= 4;
}