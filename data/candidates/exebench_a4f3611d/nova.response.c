static inline int sync_test_and_change_bit(int bit, void *addr)
{
	addr = mb_correct_addr_and_bit(&bit, addr);
	return ext4_test_bit(bit, addr)? 1 : 0;
}