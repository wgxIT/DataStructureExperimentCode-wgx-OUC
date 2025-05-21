#include <iostream>
using namespace std;

// 定义二叉树节点结构
struct TreeNode {
    char data;
    TreeNode* left;
    TreeNode* right;
};

// 递归构建二叉树（按先序遍历方式输入）
TreeNode* buildTree() {
    char ch;
    cin >> ch;  // 读取一个字符
    if (ch == '#') return nullptr;  // 用 # 表示空节点
    TreeNode* node = new TreeNode{ ch, nullptr, nullptr };
    node->left = buildTree();
    node->right = buildTree();
    return node;
}

// 先序遍历
void preOrder(TreeNode* root) {
    if (root) {
        cout << root->data;  // 访问根节点
        preOrder(root->left);
        preOrder(root->right);
    }
}

// 中序遍历
void inOrder(TreeNode* root) {
    if (root) {
        inOrder(root->left);
        cout << root->data;  // 访问根节点
        inOrder(root->right);
    }
}

// 后序遍历
void postOrder(TreeNode* root) {
    if (root) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->data;  // 访问根节点
    }
}

int main() {
    cout << "请输入先序遍历构建二叉树 (使用 # 代表空节点):\n";
    TreeNode* root = buildTree();  // 先序构建二叉树

    cout << "先序遍历: ";
    preOrder(root);
    cout << endl;

    cout << "中序遍历: ";
    inOrder(root);
    cout << endl;

    cout << "后序遍历: ";
    postOrder(root);
    cout << endl;

    return 0;
}
