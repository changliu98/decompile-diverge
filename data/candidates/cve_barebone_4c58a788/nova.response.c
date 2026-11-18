static int usb_class_request_get_descriptor(struct hpi_adapter_obj *pao,
	struct hpi_message *phm, struct hpi_response *phr)
{
	struct hpi_hw_obj *phw = pao->priv;
	unsigned short *pw;
	int i, rc;

	
	while (1) {
		if (!pao) {
			rc = 258;
			break;
		}
		if (!pao->priv) {
			rc = 258;
			break;
		}
		if (!phm) {
			rc = 258;
			break;
		}
		if (!phm->object) {
			rc = 258;
			break;
		}
		rc = hpi_check_message(pao, 5000);
		if (rc) {
			rc = rc;
			break;
		}
		if (phw->outstream_size > phm->object->size + 8) {
			rc = 260;
			break;
		}
		pw = (unsigned short *)(phw->outstream);
		pw[0] = phm->object->size;
		pw[1] = phm->object->type;
		pw[2] = phm->object->index;
		pw[3] = phm->object->subindex;
		pw[4] = phm->object->size;
		rc = hpi_send_message(pao, phm->object->size + 8, 5000);
		if (rc) {
			rc = rc;
			break;
		}
		phw->outstream_size -= 8;
		if (phw->outstream_size <= phm->object->size)
			break;
		memcpy(phw->outstream + 8, phm->object->data, phm->object->size);
	}
	hpi_free_message(pao