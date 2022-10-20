#include <iostream>

using namespace std;

template <typename T>
class dll {
    struct node {
        node* prev{ NULL };
        T data{ NULL };
        node* next{ NULL };
    };
    int dllSize{ 0 };
    node* head{ NULL };
    node* tail{ NULL };

public:
    ~dll(){
        deleteAllNodes();
    }

    void addStart(T data) {
        node* newNode = new node;
        newNode->data = data;
        dllSize++;
        if(head){
           newNode->next = head;
           head->prev = newNode;
           head = newNode;
           return;
        }
        head = newNode;
        tail = head;
    }
    void addEnd(T data) {
        if(!head){
            addStart(data);
            return;
        }
        node* newNode = new node;
        newNode->data = data;
        dllSize++;
        newNode->prev = tail;
        tail->next = newNode;

        tail = newNode;
    }
    void deleteEnd() {
        if(!tail){
            return;
        }
        if(tail->prev){
            node* temp = tail->prev;
            delete tail;
            tail = temp;
            tail->next = NULL;
        }else{
            delete tail;
            head = NULL;
            tail = head;
        }
        dllSize--;
    }
    void deleteStart() {
        if(!head){
            return;
        }
        if(head->next){
            node* temp = head->next;
            delete head;
            head = temp;
            head->prev = NULL;
        }else{
            delete head;
            tail = NULL;
        }
        dllSize--;
    }
    node* nodeData(int index) {
        if(!head || index < 0 || index >= dllSize){
            return NULL;
        }
        node* temp;
        int halfSize = dllSize/2;
        if(index <= halfSize){
            temp = head;
            for(int i = 0; i < index; i++){
                if(!temp->next) break;
                temp = temp->next;
            }
            return temp;
        }else{
            temp = tail;
            for(int j = dllSize - 1; j > index; j--){
                if(!temp->prev) break;
                temp = temp->prev;
            }
            return temp;
        }
    }
    bool changeNodeData(int index, T data) {
        node* temp = nodeData(index);
        if(!temp) return false;
        temp->data = data;
        return true;
    }
    node* searchElement(T data) {
        for(int i = 0; i < dllSize; i++){
            if(nodeData(i)->data == data){
                return nodeData(i);
            }
        }
        return NULL;
    }
    bool searchDelete(T data) {
        node* temp = searchElement(data);
        if(temp){
            if(temp == head){
                deleteStart();
            }else if(temp == tail){
                deleteEnd();
            }else{
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                delete temp->data;
                delete temp;
                dllSize--;
            }
        }else{
            return false;
        }
        return true;
    }
    void addInOrder(int index, T data) {
        if(index < 0 || index > dllSize) return;
        if(index == 0){
            addStart(data);
            return;
        }
        if(index == dllSize){
            addEnd(data);
            return;
        }
        node* newNode = new node;
        newNode->data = data;
        dllSize++;

        node* temp = nodeData(index);

        newNode->next = temp;
        temp->prev->next = newNode;

        newNode->prev = temp->prev;
        temp->prev = newNode;

    }
    void deleteAllNodes() {
        if(!head) return;

        int tempSize = dllSize;

        for(int i = 0; i < tempSize; i++){
            deleteEnd();
        }
    }
    void toString() {
        cout<<"Current head of dll: "<<head<<endl;
        cout<<"Current tail of dll: "<<tail<<endl;
        cout<<"dll size: " << dllSize << endl;
        cout<<"data chain from head (first 100)"<<endl;
        for(int i = 0; i < 100; i++){
            if(nodeData(i)){
                cout<<nodeData(i)<<endl;
            }
        }
    }
};

int main()
{
    dll<int>* li = new dll<int>;

    li->addStart(5);
    li->addEnd(10);

    li ->toString();

    delete li;

    return 0;
}
