#include <iostream>
using namespace std;

// 定义多项式节点结构
struct Term {
    int coeff; // 系数
    int exp;   // 指数
    Term* next;
    Term(int c, int e) : coeff(c), exp(e), next(nullptr) {}
};

class Polynomial {
public:
    Term* head=nullptr;
    Polynomial() : head(nullptr) {}

    // 插入多项式项，保持指数降序
    void insertTerm(int coeff, int exp) {
        if (coeff == 0) return;
        Term* newTerm = new Term(coeff, exp);
        if (!head || head->exp < exp) {
            newTerm->next = head;
            head = newTerm;
            return;
        }
        Term* curr = head;
        Term* prev = nullptr;
        while (curr && curr->exp > exp) {
            prev = curr;
            curr = curr->next;
        }
        if (curr && curr->exp == exp) { // 合并同类项
            curr->coeff += coeff;
            if (curr->coeff == 0) { // 删除系数为0的项
                if (prev) prev->next = curr->next;
                else head = curr->next;
                delete curr;
            }
            delete newTerm;
        }
        else {
            newTerm->next = curr;
            if (prev) prev->next = newTerm;
        }
    }

    // 读取多项式
    void readPolynomial() {
        int n, coeff, exp;
        cout << "请输入项数：";
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cout << "请输入第" << i + 1 << "项的系数和指数：";
            cin >> coeff >> exp;
            insertTerm(coeff, exp);
        }
    }

    // 输出多项式
    void printPolynomial() {
        Term* curr = head;
        int count = 0;
        while (curr) {
            count++;
            curr = curr->next;
        }
        cout <<"n=" <<count<<" ";
        curr = head;
        int i = 0;
        while (curr) {
            cout << "c" << ++i << "=" << curr->coeff << " e" << i << "=" << curr->exp << " ";
            curr = curr->next;
        }
        cout << endl;
    }

    // 多项式乘法
    void multiply(Polynomial* result,Polynomial* other) {

        for (Term* a = head; a; a = a->next) {
            for (Term* b = other->head; b; b = b->next) {
                result->insertTerm(a->coeff * b->coeff, a->exp + b->exp);
            }
        }
        return;
    }

    // 释放内存
    ~Polynomial() {
        while (head) {
            Term* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    Polynomial poly1, poly2, result;

    cout << "输入第一个多项式: " << endl;
    poly1.readPolynomial();
    cout << "输入第二个多项式: " << endl;
    poly2.readPolynomial();

    cout << "第一个多项式: ";
    poly1.printPolynomial();
    cout << "第二个多项式: ";
    poly2.printPolynomial();

    poly1.multiply(&result, &poly2);
    cout << "乘积多项式: ";
    result.printPolynomial();

    return 0;
}
