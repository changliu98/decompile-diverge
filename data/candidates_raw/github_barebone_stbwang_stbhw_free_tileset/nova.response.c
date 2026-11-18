static void func0(struct bnx2fc_hba *hba)
{
	int i;

	
	for (i = 0; i < hba->num_rx_rings; i++) {
		kfree(hba->rx_ring[i].bd_list);
		hba->rx_ring[i].bd_list = NULL;
	}

	
	for (i = 0; i < hba->num_tx_rings; i++) {
		kfree(hba->tx_ring[i].bd_list);
		hba->tx_ring[i].bd_list = NULL;
	}

	kfree(hba->rx_ring);
	kfree(hba->tx_ring);
	hba->rx_ring = NULL;
	hba->tx_ring = NULL;
	hba->num_rx_rings = 0;
	hba->num_tx_rings = 0;
}