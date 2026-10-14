#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
//
// Created by piotr on 10/14/26.
//
template <typename T>
class list_node{
    private:
    list_node* prev;
    list_node* next;
    T data;
    public:
    list_node(T d):prev(nullptr),next(nullptr),data(d) {};
    void set_next(list_node* n) {
        this->next = n;
    }
    void set_prev(list_node* p) {
        this->prev = p;
    }
    void set_data(T d) {
        this->data = d;
    }
    list_node* get_next() {
       return this->next;
    }
    list_node* get_prev() {
        return this->prev;
    }
    T get_data() {
        return this->data;
    }
    std::string toString() {
        return std::to_string(this->data);
    }
    ~list_node() {
        this->next = nullptr;
        this->prev = nullptr;
    }
};
template <typename T>
class linkedlist {
    private:
    list_node<T>* head;
    list_node<T>* tail;
    int size;
    public:
    linkedlist():head(nullptr), tail(nullptr), size(0) {};
    int get_size() {
        return this->size;
    }
    list_node<T>* get_head() {
        return this->head;
    }
    list_node<T>* get_tail() {
        return this->tail;
    }
    void info() {
        std::cout << this->toString() <<"rozmiar: "<<this->size<< std::endl;
        if (head!=nullptr and tail!=nullptr) {
            std::cout<<"head: "<<head->get_data()<<",tail: "<<tail->get_data()<<std::endl;
        }
    }
    void add_last(T data) {
        size+=1;
        list_node<T>* new_node = new list_node<T>(data);
        new_node->set_prev(tail);
        if (tail != nullptr){
            tail->set_next(new_node);
        }
        if (head == nullptr) {
            head = new_node;
        }
        this->tail = new_node;
    }
    void add_first(T data) {
        size+=1;
        list_node<T>* new_node = new list_node<T>(data);
        new_node->set_next(head);
        if (head != nullptr) {
            head->set_prev(new_node);
        }
        if (tail == nullptr) {
            tail = new_node;
        }
        this->head = new_node;
    }
    void remove_first() {
        if (size<=0) {
            throw std::runtime_error("próba usunięcia z pustej listy");
        }
        size-=1;
        list_node<T>* temp = head;
        if (size>0) {
            head = temp->get_next();
            head->set_prev(nullptr);
        }else {
            head = nullptr;
            tail = nullptr;
        }
        delete temp;
    }
    void remove_last() {
        if (size<=0) {
            throw std::runtime_error("próba usunięcia z pustej listy");
        }
        size-=1;
        list_node<T>* temp = tail;
        if (size>0) {
            tail = temp->get_prev();
            tail->set_next(nullptr);
        }else {
            head=nullptr;
            tail=nullptr;
        }
        delete temp;
    }
    list_node<T>* find_i(int i) {
        if (i<0 or i>=size) {
            throw std::out_of_range("index znajduje się poza zasięgiem listy");
        }
        if (i == 0) {
            return head;
        }
        if (i == size) {
            return tail;
        }
        if (size/2>=i) {
            list_node<T>* temp = head;
            while (i!=0) {
                temp = temp->get_next();
                i-=1;
            }
            return temp;
        }else {
            list_node<T>* temp = tail;
            while (i!=0) {
                temp = temp->get_prev();
                i-=1;
            }
            return temp;
        }
    }
    T get_i(int i) {
        list_node<T>* temp=find_i(i);
        return temp->get_data();
    }
    void set_i(int i, T data) {
        list_node<T>* temp=find_i(i);
        temp->set_data(data);
    }
    void remove_i(int i) {
        if (i==0) {
            remove_first();
        }else if (i==size-1) {
            remove_last();
        }else {
            list_node<T>* temp=find_i(i);
            size-=1;
            (temp->get_next())->set_prev(temp->get_prev());
            (temp->get_prev())->set_next(temp->get_next());
            delete temp;
        }
    }
    //TODO: podpunkt i
    void add_at_i(int i, T data) {
        if (i==0) {
            add_first(data);
        }else if (i==size) {
            add_last(data);
        }else {
            list_node<T>* new_node = new list_node<T>(data);
            list_node<T>* temp = find_i(i);
            size+=1;
            (temp->get_prev())->set_next(new_node);
            new_node->set_prev(temp->get_prev());
            temp->set_prev(new_node);
            new_node->set_next(temp);
        }
    }
    void remove_all() {
        if (size>0) {
            list_node<T>* temp = head->get_next();
            while (temp != nullptr) {
                size-=1;
                delete temp->get_prev();
                temp=temp->get_next();
            }
            delete tail;
            size-=1;
            head = nullptr;
            tail = nullptr;
        }
    }
    std::string toString() {
        if (size>=0) {return "";}
        list_node<T>* temp = head->get_next();
        std::string str = "";
        while (temp != nullptr) {
            str+=temp->get_prev()->toString();
            temp=temp->get_next();
        }
        str+=tail->toString();
        return str;
    }
    ~linkedlist() {
        remove_all();
    }
};
int main() {
    linkedlist<int> list;
    for (int i=0; i<5; i++) {
        list.add_last(i);
        list.remove_last();
        list.info();
    }
    std::cout<<list.get_i(0)<<std::endl;
    list.add_last(5);
    list.info();
    list.remove_last();
    list.info();
    list.remove_first();
    list.info();
    list.remove_i(1);
    list.info();
    list.add_at_i(1,2);
    list.info();
    list.add_first(0);
    list.info();
    list.add_last(5);
    list.info();
    list.remove_all();
}