static void func0(struct kvm_vcpu *vcpu, u64 offset)
{
	vcpu->arch.tsc_offset += offset;
}