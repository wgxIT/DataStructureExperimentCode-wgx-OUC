#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

bool isPrintable(char c) {
    return c >= 32 && c <= 126;
}

// �ж��Ƿ�Ϊ�հ��ַ�
bool isWhitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n';
}

// Huffman ���ڵ�ṹ
struct HuffmanNode {
    char ch;               
    int freq;              
    string code;           
    int lchild = -1, rchild = -1, parent = -1;
};

// ͳ��ÿ���ַ��ĳ���Ƶ��
map<char, int> countCharacterFrequencies(const string& text) {
    map<char, int> freqMap;
    for (char c : text) {
        if (isPrintable(c)) {
            freqMap[c]++;
        }
    }
    return freqMap;
}

// ���� Huffman ��
void buildHuffmanTree(HuffmanNode* tree, const map<char, int>& freqMap) {
    int n = freqMap.size();
    int i = 0;
    for (auto& pair : freqMap) {
        tree[i].ch = pair.first;
        tree[i].freq = pair.second;
        ++i;
    }
    for (int k = n; k < 2 * n - 1; ++k) {
        int s1 = -1, s2 = -1;
        vector<pair<int, int>> candidates; // pair<freq, index>
        for (int i = 0; i < k; ++i) {
            if (tree[i].parent == -1 && tree[i].freq > 0) {
                candidates.emplace_back(tree[i].freq, i);
            }
        }
        sort(candidates.begin(), candidates.end());
        s1 = candidates[0].second;
        s2 = candidates[1].second;

        tree[k].freq = tree[s1].freq + tree[s2].freq;
        tree[k].lchild = s1;
        tree[k].rchild = s2;
        tree[s1].parent = tree[s2].parent = k;
    }
}

// Ϊ Huffman ����ÿ���ַ����ɱ���
void generateHuffmanCodes(HuffmanNode* tree, int n) {
    for (int i = 0; i < n; ++i) {
        string code;
        int current = i;
        while (tree[current].parent != -1) {
            int parent = tree[current].parent;
            code = (tree[parent].lchild == current ? "0" : "1") + code;
            current = parent;
        }
        tree[i].code = code;
    }
}

// ʹ�� Huffman ������ı����б���
string encodeTextWithHuffman(const string& text, HuffmanNode* tree, int n) {
    map<char, string> codeMap;
    for (int i = 0; i < n; ++i) {
        codeMap[tree[i].ch] = tree[i].code;
    }
    string encoded;
    for (char c : text) {
        if (codeMap.count(c)) {
            encoded += codeMap[c];
        }
    }
    return encoded;
}

// ʹ�� Huffman ���Ա����ı����н���
string decodeHuffmanEncodedText(const string& encoded, HuffmanNode* tree, int root) {
    string decoded;
    int current = root;
    for (char bit : encoded) {
        current = (bit == '0') ? tree[current].lchild : tree[current].rchild;
        if (tree[current].lchild == -1) { // ��Ҷ�ӽڵ�
            decoded += tree[current].ch;
            current = root;
        }
    }
    return decoded;
}

int main() {
    const string inputFile = "a.txt";
    ifstream input(inputFile, ios::binary);
    string text((istreambuf_iterator<char>(input)), istreambuf_iterator<char>());

    cout << "ԭʼ�ı�:\n" << text << endl;

    map<char, int> freqMap = countCharacterFrequencies(text);
    int n = freqMap.size();

    HuffmanNode* huffmanTree = new HuffmanNode[2 * n - 1];
    buildHuffmanTree(huffmanTree, freqMap);
    generateHuffmanCodes(huffmanTree, n);

    cout << "Huffman�����:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "�ַ� ";
        if (isWhitespace(huffmanTree[i].ch)) {
            cout << "�ո�";
        }
        else {
            cout << huffmanTree[i].ch;
        }
        cout << " : " << huffmanTree[i].code << endl;
    }

    string encoded = encodeTextWithHuffman(text, huffmanTree, n);
    ofstream outEncoded("b.txt", ios::binary);
    outEncoded << encoded;
    cout << "�������ѱ�����b.txt " << endl;

    int root = 2 * n - 2;
    string decoded = decodeHuffmanEncodedText(encoded, huffmanTree, root);
    ofstream outDecoded("c.txt", ios::binary);
    outDecoded << decoded;

    cout << "���룺" << decoded << endl;
    cout << "������֤���: " << (text == decoded ? "�ɹ�" : "ʧ��") << endl;

    delete[] huffmanTree;
    return 0;
}
