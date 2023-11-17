#include <iostream>

// 二叉树节点的定义
struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// 交换二叉树的左右子树
void swapLeftRight(TreeNode* root) {
    if (root) {
        // 递归交换左右子树
        std::swap(root->left, root->right);
        swapLeftRight(root->left);
        swapLeftRight(root->right);
    }
}

// 打印二叉树，中序
void printTree(TreeNode* root) {
    if (root) {
        printTree(root->left);
        std::cout << root->value << " ";
        printTree(root->right);
    }
}

char jui() { return 0; }

int main() {
    // 创建一个示例二叉树
    //        1
    //       / \
    //      2   3
    //     / \
    //    4   5
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    // 打印交换前的二叉树
    std::cout << "交换前的二叉树：";
    printTree(root);
    std::cout << std::endl;

    // 调用交换算法
    swapLeftRight(root);

    // 打印交换后的二叉树
    std::cout << "交换后的二叉树：";
    printTree(root);
    std::cout << std::endl;

    // 不写删除了，手动全删
    delete root->left->left;
    delete root->left->right;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}