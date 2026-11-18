int check_height(struct Node *root, struct Node *node) {
    int left_height;
    int right_height;
    int balance;
    int max_height;

    // Base case: if the node is the sentinel (null leaf), height is 0
    if (node == sentinel) {
        return 0;
    }

    // Recursively check the left subtree
    left_height = check_height(root, node->left);
    if (left_height < 0) {
        return left_height; // Propagate error code -1
    }

    // Recursively check the right subtree
    right_height = check_height(root, node->right);
    if (right_height < 0) {
        return right_height; // Propagate error code -1
    }

    // Calculate the actual balance factor
    balance = right_height - left_height;

    // AVL trees must have a balance factor of -1, 0, or 1
    if (balance < -1 || balance > 1) {
        return -1;
    }

    // Check if the calculated balance factor matches the stored balance factor
    if (balance != node->balance) {
        return -1;
    }

    // Height is 1 + max(left_height, right_height)
    if (left_height > right_height) {
        max_height = left_height;
    } else {
        max_height = right_height;
    }

    return max_height + 1;
}