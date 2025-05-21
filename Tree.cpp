#include <iostream>
using namespace std;

// ����������ڵ�ṹ
struct TreeNode {
    char data;
    TreeNode* left;
    TreeNode* right;
};

// �ݹ鹹���������������������ʽ���룩
TreeNode* buildTree() {
    char ch;
    cin >> ch;  // ��ȡһ���ַ�
    if (ch == '#') return nullptr;  // �� # ��ʾ�սڵ�
    TreeNode* node = new TreeNode{ ch, nullptr, nullptr };
    node->left = buildTree();
    node->right = buildTree();
    return node;
}

// �������
void preOrder(TreeNode* root) {
    if (root) {
        cout << root->data;  // ���ʸ��ڵ�
        preOrder(root->left);
        preOrder(root->right);
    }
}

// �������
void inOrder(TreeNode* root) {
    if (root) {
        inOrder(root->left);
        cout << root->data;  // ���ʸ��ڵ�
        inOrder(root->right);
    }
}

// �������
void postOrder(TreeNode* root) {
    if (root) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->data;  // ���ʸ��ڵ�
    }
}

int main() {
    cout << "����������������������� (ʹ�� # ����սڵ�):\n";
    TreeNode* root = buildTree();  // ���򹹽�������

    cout << "�������: ";
    preOrder(root);
    cout << endl;

    cout << "�������: ";
    inOrder(root);
    cout << endl;

    cout << "�������: ";
    postOrder(root);
    cout << endl;

    return 0;
}
