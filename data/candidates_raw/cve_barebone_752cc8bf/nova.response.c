static void func0(struct kvm_vcpu *vcpu, struct kvm_mmu_page *sp)
{
	struct kvm_mmu_page *parent;
	unsigned long *sptep;
	unsigned long *parent_sptep;
	unsigned long *spte;
	unsigned long *parent_spte;
	unsigned long *last_spte;
	unsigned long *first_spte;
	unsigned long *first_spte_parent;
	unsigned long *last_spte_parent;

	
	while (1) {
		sptep = sp->spt;
		spte = sptep + 12;
		if ((*spte & PT64_BASE_ADDR_MASK)!= 0x0c)
			break;
		sptep = kvm_mmu_page_role(vcpu, sptep);
		*sptep = (*sptep & ~0x0000000000000fff) |
			 ((*spte & 0x0000000000000fff) >> 11);
		sptep = kvm_mmu_page_role(vcpu, sptep);
		sp->spt = sptep;
		sp = sptep;
	}

	
	parent = sp->parent;
	if (parent->unsync)
		sptep = parent->spt;
	else
		sptep = vcpu->arch.mmu.pae_root;
	sp->spt = sptep;
	kvm_mmu_page_role(vcpu, sp);
	kvm_mmu_page_role(vcpu, sptep);

	
	first_spte = sptep;
	last_spte = sptep;
	parent_spte = kvm_mmu_page_role(sp, spte);
	first_spte_parent = parent_spte;
	last_spte_parent = parent_spte;
	while (1) {