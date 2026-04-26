#include <iostream>
#include <cstring>
 using namespace std;

 struct Ngay { 
    int ngay, thang, nam; 
};
 
 struct SinhVien { 
    char maSV[8]; 
    char hoTen[50]; 
    int gioiTinh; 
    Ngay ngaySinh; 
    char diaChi[100]; 
    char lop[12]; 
    char khoa[7];
};

 struct Node { 
    SinhVien data; 
    Node *link; 
};

 struct List { 
    Node *first; 
    Node *last; 
};

 void tao_list(List &list) {
    list.first = list.last = NULL;
 }

 Node* tao_node(SinhVien sv) {
    Node *p = new Node;
    p->data = sv;
    p->link = NULL;
    return p;
 }

 SinhVien nhap_SV() {
    SinhVien sv;
    cin.ignore();
    cout<<"Nhap ma SV:";
    cin.getline(sv.maSV, 8);
    cin.ignore();
    cout<<"Nhap ho ten SV:";
    cin.getline(sv.hoTen, 50);
    cout<<"Nhap gioi tinh SV:";
    cin>>sv.gioiTinh;
    cout<<"Nhap ngay sinh cua SV:";
    cin>>sv.ngaySinh.ngay>>sv.ngaySinh.thang>>sv.ngaySinh.nam;
    cin.ignore();
    cout<<"Nhap dia chi SV:";
    cin.getline(sv.diaChi, 100);
    cout<<"Nhap lop SV:";
    cin.getline(sv.lop, 12);
    cout<<"Nhap khoa SV:";
    cin.getline(sv.khoa, 7);
    return sv;
 }

 void inSV(SinhVien sv) {
    cout<<sv.maSV<<endl;
    cout<<sv.hoTen<<endl;
    cout<<sv.gioiTinh<<endl;
    cout<<sv.ngaySinh.ngay<<"/"<<sv.ngaySinh.thang<<"/"<<sv.ngaySinh.nam<<endl;
    cout<<sv.diaChi<<endl;
    cout<<sv.lop<<endl;
    cout<<sv.khoa<<endl;
 }

 void inDS(List &list) {
    Node *p = list.first;
    while(p!=NULL) {
        cout<<p->data.maSV<<endl;
        cout<<p->data.hoTen<<endl;
        cout<<(p->data.gioiTinh ? "Nam":"Nu")<<endl;
        cout<<p->data.ngaySinh.ngay<<"/"<<p->data.ngaySinh.thang<<"/"<<p->data.ngaySinh.nam<<endl;
        cout<<p->data.diaChi<<endl;
        cout<<p->data.lop<<endl;
        cout<<p->data.khoa<<endl;
        p = p->link;
    }
 }

 void sap_xep(List &list, SinhVien sv) {
    Node *q = new Node;
    q->data = sv;
    q->link = NULL;

    if (list.first == NULL) list.first = list.last = q;

    else if (strcmp(q->data.maSV, list.first->data.maSV) < 0) {
        q->link = list.first->link;
        list.first = q;
    }

    else {
        Node *check = list.first;
        while (check->link != NULL && strcmp(check->link->data.maSV, q->data.maSV) < 0) check = check->link;
        q->link = check->link;
        check->link = q;
        if (q->link = NULL) list.last = q;
    }
 }

 void nhap_DS(List &list) {
    int n;
    cout<<"Nhap so SV:";
    cin>>n;
    for (int i=1; i<=n; i++) {
        cout<<"Nhap SV thu"<<i<<":";
        SinhVien sv = nhap_SV();
        sap_xep(list, sv);
    }
 }

 void func_check_cungngaysinh(List list) {
    int n = 0;
    Node *p = list.first;
    while (p != NULL) {
        n++;
        p = p->link;
    }

    Node **A = new Node*[n];
    bool *high_light = new bool[n]();
    p = list.first;
    for (int i=0; i<n; i++) {
        A[i] = p;
        p = p->link;
    }

    for (int i=0; i<n-1; i++) {
        for (int j=i+1; j<n; j++) {
            if (A[i]->data.ngaySinh.ngay == A[j]->data.ngaySinh.ngay && A[i]->data.ngaySinh.thang == A[j]->data.ngaySinh.thang) 
            high_light[i] = high_light[j] = true;
        }
    }

    bool kq = false;
    for (int i=0; i<n; i++) {
        if (high_light[i]) {
            cout<<A[i]->data.maSV<<endl;
            cout<<A[i]->data.hoTen<<endl;
            cout<<(A[i]->data.gioiTinh ? "Nam":"Nu")<<endl;
            cout<<A[i]->data.ngaySinh.ngay<<"/"<<p->data.ngaySinh.thang<<"/"<<p->data.ngaySinh.nam<<endl;
            cout<<A[i]->data.diaChi<<endl;
            cout<<A[i]->data.lop<<endl;
            cout<<A[i]->data.khoa<<endl;
            kq = true;
        }
    }
    if (!kq) cout<<"Ko tim thay SV cung ngay sinh"<<endl;
    delete[] A;
    delete[] high_light;
 }

 void del(List &list) {
    int n = 0;
    Node *p = list.first;
    while (p != NULL) {
        n++;
        p = p->link;
    }

    Node **A = new Node*[n];
    bool *high_light = new bool[n]();
    p = list.first;
    for (int i=0; i<n; i++) {
        A[i] = p;
        p = p->link;
    }

    for (int i=0; i<n-1; i++) {
        for (int j=i+1; j<n; j++) {
            if (A[i]->data.ngaySinh.ngay == A[j]->data.ngaySinh.ngay && A[i]->data.ngaySinh.thang == A[j]->data.ngaySinh.thang) 
            high_light[i] = high_light[j] = true;
        }
    }

    Node fake;
    fake.link = list.first;
    Node *check = &fake;

    for (int i=0; i<n; i++) {
        if (high_light[i]) {
            check->link = A[i]->link;
            delete A[i];
        }
        else check = A[i];
    }

    list.first = fake.link;
    list.last = (check == &fake) ? NULL : check;
    delete[] A;
    delete[] high_light;
 }

 int main() {
    List L;
    tao_list(L);
    nhap_DS(L);

    cout<<"Danh sach sap xep theo maSV la:"<<endl;
    inDS(L);

    cout<<"Them SV:"<<endl;
    SinhVien new_sv = nhap_SV();
    sap_xep(L, new_sv);
    cout<<"Danh sach sau khi them:"<<endl;
    inDS(L);

    cout<<"Nhung SV co cung ngay sinh"<<endl;
    func_check_cungngaysinh(L);

    cout<<"Danh sach sau khi xoa nhung SV co cung ngay sinh"<<endl;
    del(L);
    inDS(L);

    return 0;
 }