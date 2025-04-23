#include <gtest/gtest.h>
#include <cstdint>

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

TreeNode* create_test_tree() {
    TreeNode* root = new TreeNode();
    root->left = new TreeNode();
    root->right = new TreeNode();
    root->left->left = new TreeNode();
    root->right->left = new TreeNode();
    root->right->right = new TreeNode();

    return root;
}

void delete_tree(TreeNode* root) {
    if (root == nullptr) return;
    delete_tree(root->left);
    delete_tree(root->right);
    delete root;
}

// -------- TESTS --------

TEST(GetTreeDepthTest, NullTreeReturnsZero) {
    TreeNode* root = nullptr;
    EXPECT_EQ(get_tree_depth(root), 0);
}

TEST(GetTreeDepthTest, SingleNodeTree) {
    TreeNode* root = new TreeNode();
    EXPECT_EQ(get_tree_depth(root), 1);
    delete root;
}

TEST(GetTreeDepthTest, CustomTestTree) {
    TreeNode* root = create_test_tree();
    EXPECT_EQ(get_tree_depth(root), 3); 
    delete_tree(root);
}

TEST(GetTreeDepthTest, LeftHeavyTree) {
    TreeNode* root = new TreeNode();
    root->left = new TreeNode();
    root->left->left = new TreeNode();
    EXPECT_EQ(get_tree_depth(root), 3);
    delete_tree(root);
}

TEST(GetTreeDepthTest, RightHeavyTree) {
    TreeNode* root = new TreeNode();
    root->right = new TreeNode();
    root->right->right = new TreeNode();
    root->right->right->right = new TreeNode();
    EXPECT_EQ(get_tree_depth(root), 4);
    delete_tree(root);
}
