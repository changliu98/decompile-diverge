int hci_req_sync(struct hci_dev *hdev, struct hci_request *req,
		 unsigned long opt, u32 timeout, u8 *hci_status)
{
	int err;

	if (!test_bit(0, &hdev->flags))
		return -100;

	mutex_lock(&hdev->req_lock);
	err = __hci_req_sync(hdev, req, opt, timeout, hci_status);
	mutex_unlock(&hdev->req_lock);

	return err;
}