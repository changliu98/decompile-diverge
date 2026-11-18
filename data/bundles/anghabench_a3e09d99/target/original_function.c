unsigned int ring_size_to_bytes(unsigned int ring_size)
{
	return ring_size * sizeof(union mgmt_port_ring_entry);
}