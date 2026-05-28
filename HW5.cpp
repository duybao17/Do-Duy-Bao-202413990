#include <iostream>
using namespace std;

struct Node {
    int date;
    Node* trai;
    Node* phai;
    Node(int ns) : date(ns), trai(nullptr), phai(nullptr) {}
};

Node* insert(Node* goc, int date) {
    if (goc == nullptr)
        return new Node(date);
    if (date < goc->date)
        goc->trai = insert(goc->trai, date);
    else if (date > goc->date)
        goc->phai = insert(goc->phai, date);
    return goc;
}

Node* search(Node* goc, int date) {
    if (goc == nullptr || goc->date == date)
        return goc;
    if (date < goc->date)
        return search(goc->trai, date);
    else
        return search(goc->phai, date);
}

int main() {
    int data[] = {2001, 2002, 2006, 2007, 2003, 2004, 2005, 2001, 1999, 2004};
    int n = sizeof(data) / sizeof(data[0]);
    int date_can_tim;

    cin>>date_can_tim;

    Node* goc = nullptr;
    for (int i = 0; i < n; i++)
        goc = insert(goc, data[i]);

    Node* Kq = search(goc, date_can_tim);
    if (Kq)
        cout<<"Tim thay sinh vien co nam sinh: "<<Kq->date<<endl;
    else
        cout<<"Khong tim thay."<<endl;
    return 0;
}
//Trường hợp                          Độ phức tạp                               Bài này
//Best case                           O(1)                                      Tìm 2001 → 1 bước
//Trung bình                          O(log n)                                  Lý tưởng: 3 bước
//Worst case                          O(n)                                      Cây suy biến: 8 bước
//Độ phức tạp bài toán                O(n)                                      Tìm 2004: 5 bước