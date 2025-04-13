#include <cstdint> // для size_t
#include <iostream>

struct TreeNode {
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
};

size_t get_tree_depth(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }

    size_t left_depth = get_tree_depth(root->left);
    size_t right_depth = get_tree_depth(root->right);

    return 1 + (left_depth > right_depth ? left_depth : right_depth);
}

// // making a test tree;
// TreeNode* create_test_tree() {
//     TreeNode* root = new TreeNode();
//     root->left = new TreeNode();
//     root->right = new TreeNode();
//
//     root->left->left = new TreeNode();
//
//     root->right->left = new TreeNode();
//     root->right->right = new TreeNode();
//
//     return root;
// }
//
// void delete_tree(TreeNode* root) {
//     if (root == nullptr) return;
//     delete_tree(root->left);
//     delete_tree(root->right);
//     delete root;
// }

// int main() {
//     TreeNode* root = create_test_tree();
//     std::cout << "tree depth: " << get_tree_depth(root) << std::endl;
//     delete_tree(root);
//     return 0;
// }
