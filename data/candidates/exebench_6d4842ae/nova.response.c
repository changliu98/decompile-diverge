static void load_and_store(struct kvm_vcpu *vcpu, u64 offset)
{
	vcpu->arch.tsc_offset += offset;
}