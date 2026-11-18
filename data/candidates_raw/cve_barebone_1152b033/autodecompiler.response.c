int hci_req_sync(struct hci_dev *hdev, hci_req_func_t req, u32 opt,
		 u16 timeout, u8 *status)
{
	int err;

	if (!test_bit(HCI_RUNNING, &hdev->flags)) {
		err = -100;
		goto out;
	}

	mutex_lock(&hdev->req_mutex);

	err = __hci_req_sync(hdev, req, opt, timeout, status);

	mutex_unlock(&hdev->req_mutex);

out:
	return err;
}