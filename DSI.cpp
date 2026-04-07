#include<iostream>
#include<string>
 using namespace std;

 //Phan tich:
 //ban chat bai toan:quan ly cac file trong thu muc D>Document 
 //moi file co: ten, thoi gian tao(cho viec sap xep), dung luong(tinh toan y 3,4)
 //thuc hien:
 //1. khai bao cau truc:la cau truc danh sach lien ket don
 //2. copy file
 //3. tinh tong dung luong cua cac file trong thu muc
 //4. sao luu file vao USB
 //mo ta thuoc tinh cua danh sach va file:
 // -string: name
 // -long long: size
 // -long long: time
 // -> danh sach lket don dung de luu tru cac file theo thu tu thoi gian
 // 1.node: data của file và con trỏ link 
 // 2.con tro head
 // mo ta cac ham can thuc thi:
 // 1. ham khoi tao danh sach
 // 2. ham tao new node
 // 3. ham chen file
 // 4. ham copy file
 // 5. ham tinh tong dung luong thu muc 
struct File {
    string name;
    long long size;  
    long long time;   
};
struct Node {
    File data;
    Node* link;
};
struct List {
    Node* head;
};

void init(List &list) {
    list.head = NULL;
}

Node* tao_Node(File D) {
    Node* p = new Node;
    p->data = D;
    p->link = NULL;
    return p;
}

Node* node_min(List list) {
    Node* q = list.head;
    Node* min_Node = q;
    while (q != NULL) {
        if (q->data.size < min_Node->data.size) {
            min_Node = q;
        }
        q = q->link;
    }
    return min_Node;
}

void insert(List &list, File D) {
    Node* new_Node = tao_Node(D);

    if (list.head == NULL || D.time < list.head->data.time) {
        new_Node->link = list.head;
        list.head = new_Node;
        return;
    }

    Node* q = list.head;
    while (q->link != NULL && q->link->data.time < D.time) {
        q = q->link;
    }

    new_Node->link = q->link;
    q->link = new_Node;
}

void copy(List &list, string name, long long size, long long time) {
    File f;
    f.name = name;
    f.size = size;
    f.time = time;

    insert(list, f);
}

long long tong(List list) {
    long long S = 0;
    Node* q = list.head;

    while (q != NULL) {
        S += q->data.size;
        q = q->link;
    }

    return S;
}

void in(List list) {
    Node* q = list.head;
    while (q != NULL) {
        cout << q->data.name << " | "
             << q->data.size << " | "
             << q->data.time << endl;
        q = q->link;
    }
}

void xoa_Node(List &list, Node* t) {
    if (list.head == NULL || t == NULL) return;

    if (list.head == t) {
        Node* temp = list.head;
        list.head = list.head->link;
        delete temp;
        return;
    }

    Node* q = list.head;
    while (q->link != NULL && q->link != t) {
        q = q->link;
    }

    if (q->link == t) {
        Node* temp = q->link;
        q->link = t->link;
        delete temp;
    }
}

void USB(List &list, int &dem) {
    long long limit = 32LL * 1024 * 1024 * 1024;
    long long sum = tong(list);
    dem = 0;
    while (sum > limit) {
        Node* minnode = node_min(list);
        sum -= minnode->data.size;
        xoa_Node(list, minnode);
        dem++;
    }
}

int main() {
    List list;
    int dem;
    init(list);
    copy(list, "file1.cpp", 1000000, 24);
    copy(list, "file2.cpp", 2000000, 15);
    copy(list, "file3.cpp", 150000000, 17);
    cout<<"Danh sach file:\n";
    in(list);
    cout<<"\nTong dung luong: "<<tong(list)<<" bytes\n";

    long long limit = 32LL * 1024 * 1024 * 1024;
    USB(list, dem);
    if(dem==0) cout<<"Sao luu thanh cong"<<endl;
    else cout<<"Sao luu thanh cong sau khi xoa:"<<dem<<" file"<<endl;
    return 0;
}