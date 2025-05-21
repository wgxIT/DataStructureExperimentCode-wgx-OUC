#include <iostream>
using namespace std;

// �������ʽ�ڵ�ṹ
struct Term {
    int coeff; // ϵ��
    int exp;   // ָ��
    Term* next;
    Term(int c, int e) : coeff(c), exp(e), next(nullptr) {}
};

class Polynomial {
public:
    Term* head=nullptr;
    Polynomial() : head(nullptr) {}

    // �������ʽ�����ָ������
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
        if (curr && curr->exp == exp) { // �ϲ�ͬ����
            curr->coeff += coeff;
            if (curr->coeff == 0) { // ɾ��ϵ��Ϊ0����
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

    // ��ȡ����ʽ
    void readPolynomial() {
        int n, coeff, exp;
        cout << "������������";
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cout << "�������" << i + 1 << "���ϵ����ָ����";
            cin >> coeff >> exp;
            insertTerm(coeff, exp);
        }
    }

    // �������ʽ
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

    // ����ʽ�˷�
    void multiply(Polynomial* result,Polynomial* other) {

        for (Term* a = head; a; a = a->next) {
            for (Term* b = other->head; b; b = b->next) {
                result->insertTerm(a->coeff * b->coeff, a->exp + b->exp);
            }
        }
        return;
    }

    // �ͷ��ڴ�
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

    cout << "�����һ������ʽ: " << endl;
    poly1.readPolynomial();
    cout << "����ڶ�������ʽ: " << endl;
    poly2.readPolynomial();

    cout << "��һ������ʽ: ";
    poly1.printPolynomial();
    cout << "�ڶ�������ʽ: ";
    poly2.printPolynomial();

    poly1.multiply(&result, &poly2);
    cout << "�˻�����ʽ: ";
    result.printPolynomial();

    return 0;
}
