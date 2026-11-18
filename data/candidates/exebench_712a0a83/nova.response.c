static void advance_m1pos(struct ata_port *ap)
{
	ap->last_ctl = (ap->last_ctl + 1) % 61;
}