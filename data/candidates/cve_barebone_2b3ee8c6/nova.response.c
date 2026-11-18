static int zip_read_mac_metadata(struct kvm_vcpu *vcpu, struct kvm_run *run,
			     struct kvm_translation *tr)
{
	unsigned long *cr3 = (unsigned long *)vcpu->arch.mmu->root_hpa;
	unsigned long *pdptrs;
	unsigned long *pdpte;
	unsigned long *pte;
	unsigned long *pte_addr;
	unsigned long *pte_addr_end;
	unsigned long *pte_end;
	unsigned long *pte_start;
	unsigned long *pte_start_addr;
	unsigned long *pte_start_end;
	unsigned long *pte_start_end_addr;
	unsigned long *pte_start_end_addr_1;
	unsigned long *pte_start_end_addr_2;
	unsigned long *pte_start_end_addr_3;
	unsigned long *pte_start_end_addr_4;
	unsigned long *pte_start_end_addr_5;
	unsigned long *pte_start_end_addr_6;
	unsigned long *pte_start_end_addr_7;
	unsigned long *pte_start_end_addr_8;
	unsigned long *pte_start_end_addr_9;
	unsigned long *pte_start_end_addr_10;
	unsigned long *pte_start_end_addr_11;
	unsigned long *pte_start_end_addr_12;
	unsigned long *pte_start_end_addr_13;
	unsigned long *pte_start_end_addr_14;
	unsigned long *pte_start_end_addr_15;
	unsigned long *pte_start_end_addr_16;
	unsigned long *pte_start_end_addr_17;
	unsigned long *pte_start_end_addr_18;
	unsigned long *pte_start_end_addr_19;
	unsigned long *pte_start_end_addr_20;
	unsigned long *pte_start_end_