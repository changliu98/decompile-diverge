u16 ice_txd_use_count(unsigned int tx_ring_count)
{
#define ICE_TX_SIZE 256
#define ICE_TXD_HDR 128
	return ((tx_ring_count * ICE_TXD_HDR) / ICE_TX_SIZE) + 1;
}