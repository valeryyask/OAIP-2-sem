#include <iostream>
#include <string>
#include <limits>

using namespace std;

struct Tree {
    int key;         // ����
    string text;     // �����
    Tree* Left;
    Tree* Right;
    Tree* Parent;    // ��������� �� ����� � ������ �����
};

Tree* makeTree(Tree* Root);       // �������� ������
Tree* list(int i, const string& s);       // �������� ������ ��������
Tree* insertElem(Tree* Root, int key, const string& s);  // ���������� ������ ��������
Tree* search(Tree* n, int key);   // ����� �������� �� ����� 
Tree* delet(Tree* Root, int key); // �������� �������� �� �����
void view(Tree* t, int level);    // ����� ������ 
void delAll(Tree* t);             // ������� ������
int sumLeafNodes(Tree* tree);     // ����� �������� ���� �������

Tree* Root = NULL;                // ��������� �����

int sumLeafNodes(Tree* tree) {
    if (tree == NULL) {
        return 0;
    }

    if (tree->Left == NULL && tree->Right == NULL) {
        return tree->key;
    }

    return sumLeafNodes(tree->Left) + sumLeafNodes(tree->Right);
}

int main() {
    setlocale(0, "Russian");
    int key, choice, leafSum = 0;
    string s;

    for (;;) {
        cout << "1 - �������� ������\n";
        cout << "2 - ���������� ��������\n";
        cout << "3 - ����� �� �����\n";
        cout << "4 - �������� ��������\n";
        cout << "5 - ����� ������\n";
        cout << "6 - ������� ������\n";
        cout << "7 - ����� �������� ���� �������\n";
        cout << "8 - �����\n";
        cout << "��� �����?\n";

        // �������� �� ���� �����
        if (!(cin >> choice)) {
            cout << "������: ������� �����. ����������, ������� �����.\n";
            cin.clear(); // ������� ������ ������ �����
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ������� ������ �����
            continue; // ���������� ������� �������� �����
        }

        cout << "\n";
        cin.ignore();  // ������� ������ ����� ����������� ������
        switch (choice) {
        case 1:
            Root = makeTree(Root);
            break;
        case 2:
            cout << "\n������� ����: ";
            cin >> key;
            cin.ignore();  // ������� ������ ����� ����������� ������
            cout << "������� �����: ";
            getline(cin, s);
            insertElem(Root, key, s);
            break;
        case 3:
            cout << "\n������� ����: ";
            // �������� �� ���������� ���� ����� (����� �����)
            while (!(cin >> key)) {
                cout << "������: ������� ����� ����� ��� �����: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "��������� ����� = ";
            if (search(Root, key) != NULL) {
                cout << search(Root, key)->text;
            }
            else {
                cout << "������� � ����� ������ �� ������";
            }
            cout << endl;
            break;

        case 4:
            cout << "\n������� ��������� ����: ";
            // �������� �� ���������� ���� ����� (����� �����)
            while (!(cin >> key)) {
                cout << "������: ������� ����� ����� ��� �����: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            Root = delet(Root, key);
            break;

        case 5:
            if (Root != NULL) {
                cout << "������ ��������� �� 90 ����. �����" << endl;
                view(Root, 0);
            }
            else {
                cout << "������ ������\n";
            }
            break;

        case 6:
            delAll(Root);
            Root = NULL;
            cout << "������ �������\n";
            break;

        case 7:
            leafSum = sumLeafNodes(Root);
            cout << "����� �������� ���� ������� = " << leafSum << endl;
            break;

        case 8:
            exit(0);
        }
    }
}

Tree* makeTree(Tree* Root)    //�������� ������
{
    int key;
    string s;    // ��� ����� � ������

    cout << "����� ����� - ������������� �����\n\n";

    // �������� �� ���������� ���� ����� ����� (��������������� �����)
    do {
        cout << "������� ���� ����� (��������������� �����): ";
        while (!(cin >> key)) {
            cout << "������: ������� ����� ����� ��� ����� �����: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (key < 0) {
            cout << "������: ���� ����� ������ ���� ���������������.\n";
        }
    } while (key < 0);

    // �������� �� ���������� ���� ����� �����
    cin.ignore();  // ������� ������ ����� ����������� ������
    cout << "������� ������ �����: ";
    getline(cin, s);

    Root = list(key, s);    // ��������� ��������� �� ������

    while (1)                //���������� ���������
    {
        // �������� �� ���������� ���� ����� ��������
        cout << "\n������� ����: ";
        while (!(cin >> key)) {
            cout << "������: ������� ����� ����� ��� ����� ��������: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (key < 0) break;       //������� ������ (���� < 0)   

        // �������� �� ���������� ���� ����� ��������
        cin.ignore();  // ������� ������ ����� ����������� ������
        cout << "������� ������: ";
        getline(cin, s);

        insertElem(Root, key, s);
    }

    return Root;
}

Tree* list(int i, const string& s)     //�������� ������ ��������
{
    Tree* t = new Tree;        // ��������� ������
    t->key = i;            // ����
    t->text = s;   // �������� ������
    t->Left = t->Right = NULL;            // ������ � ����� �����
    return t;
}

Tree* insertElem(Tree* t, int key, const string& s) {
    Tree* Prev = NULL;
    int find = 0;

    // ����� ����� ��� ������� ������ ��������
    while (t && !find) {
        Prev = t;
        if (key == t->key)
            find = 1;
        else if (key < t->key)
            t = t->Left;
        else
            t = t->Right;
    }

    if (!find) {
        // �������� ������ ����
        Tree* newNode = list(key, s);

        // ������� ������ ��������
        if (!Prev) // ���� ������ ������
            t = newNode;
        else if (key < Prev->key)
            Prev->Left = newNode;
        else
            Prev->Right = newNode;

        return newNode; // ���������� ��������� �� ����� �������
    }
    else {
        cout << "������� � ������ " << key << " ��� ����������." << endl;
        return NULL;
    }
}

Tree* delet(Tree* Root, int key)  //�������� �������� �� �����
{
    Tree* Del, * Prev_Del, * R, * Prev_R;
    Del = Root;
    Prev_Del = NULL;
    while (Del != NULL && Del->key != key) {   //����� �������� � ��� �������� 
        Prev_Del = Del;
        if (Del->key > key)
            Del = Del->Left;
        else
            Del = Del->Right;
    }
    if (Del == NULL) {             // ������� �� ������
        cout << "\n��� ������ �����\n";
        return Root;
    }
    if (Del->Right == NULL) // ����� �������� R ��� ������
        R = Del->Left;        // ������� �� ����� �����
    else if (Del->Left == NULL)
        R = Del->Right;        // ��� �� ������
    else {
        Prev_R = Del; //����� ������ ������� �������� � ����� ���������
        R = Del->Left;
        while (R->Right != NULL) {
            Prev_R = R;
            R = R->Right;
        }
        if (Prev_R == Del) // ������ ������� ��� ������ R � ��� �������� Prev_R 
            R->Right = Del->Right;
        else {
            R->Right = Del->Right;
            Prev_R->Right = R->Left;
            R->Left = Prev_R;
        }
    }
    if (Del == Root)
        Root = R;    //�������� ����� � ������ ��� �� R
    else {
        // ��������� R �������������� � �������� ���������� ����
        if (Del->key < Prev_Del->key)
            Prev_Del->Left = R; // �� ����� ����� 
        else
            Prev_Del->Right = R;    // �� ������ �����
    }
    int tmp = Del->key;
    cout << "\n������ ������� � ������ " << tmp << endl;
    delete Del;
    return Root;
}

Tree* search(Tree* n, int key)  //����� �������� �� ����� 
{
    Tree* rc = n;
    while (rc != NULL && rc->key != key) {
        if (key < rc->key)
            rc = rc->Left;
        else if (key > rc->key)
            rc = rc->Right;
    }
    return rc;
}

void view(Tree* t, int level) {
    if (t) {
        // ����������� ����� ��� ������� ��������� � ����������� ������
        view(t->Right, level + 1);

        // ����� �������� ��� �������� ������
        for (int i = 0; i < level; i++)
            cout << "   ";

        // ����� ������ � ����������� �������� ����
        cout << "������� " << level << ": " << t->key << ' ' << t->text << endl;

        // ����������� ����� ��� ������ ��������� � ����������� ������
        view(t->Left, level + 1);
    }
}

void delAll(Tree* t) //������� ������
{
    if (t != NULL) {
        delAll(t->Left);
        delAll(t->Right);
        delete t;
    }
}
