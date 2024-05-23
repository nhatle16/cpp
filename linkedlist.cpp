/*
    Indices in methods are all zero-based;
    Create a temp node to traverse the linked list instead of using this->head;
 */

#include <iostream>
#include <stdexcept>

struct node {
    int data;
    node *next;

    node(int value) : data(value), next(NULL) {}
};

class LinkedList {
public:
    // public attributes for easier access
    node *head;
    int length;

    // public methods to work with the linked list
    void insertFirst(int data) {
        node *newnode = new node(data);
        newnode->next = head;
        this->head = newnode;
        this->length++;
        return;
    }

    void insertLast(int data) {
        node *newnode = new node(data);
        if (this->head == NULL) {
            this->head = newnode;
            this->length++;
            return;
        }

        node *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newnode;
        this->length++;
        return;
    }   

    void insertAt(int data, int index) {
        int count = 0;
        if (index < 0 || index > this->length) {
            throw std::out_of_range("Error! Index out of range.");
        }

        if (index == 0) {
            this->insertFirst(data);
            return;
        }

        node *newnode = new node(data);
        node *temp = head; 
        while (count < index-1) {
            temp = temp->next;
            count++;
        }

        newnode->next = temp->next;
        temp->next = newnode;
        this->length++;
        return;
    }

    void deleteFirst() {
        // if the list is empty
        if (this->head == NULL) {
            throw std::out_of_range("Error! Linked list is empty.");
        }

        node *temp = this->head;
        this->head = this->head->next;
        this->length--;
        delete temp;        // deallocate the memory of the deleted node
        return;
    }

    void deleteLast() {
        // if the list is empty
        if (this->head == NULL) {
            throw std::out_of_range("Error! Linked list is empty.");
        }
        // if the list has one node only
        else if (this->head->next == NULL){
            delete head;
            this->head = NULL;
        }

        node *temp = this->head;
        while (temp->next->next != NULL) {      // stop at second-to-last node
            temp = temp->next;
        }
        node *deletedNode = temp->next;
        temp->next = NULL;
        delete deletedNode;      // deallocate the memory of the deleted node
        this->length--;
        return;
    }

    void deleteAt(int index) {
        if (index < 0 || index >= this->length) {
            throw std::out_of_range("Error! Index out of range.");
        }
        // delete the index at the begin
        if (index == 0) {
            this->deleteFirst();
            return;
        }
        // delete the index at the end
        if (index == this->length - 1) {
            this->deleteLast();
            return;
        }

        int count = 0;
        node *temp = head;
        while (count < index-1) {
            temp = temp->next;
            count++;
        }

        node *deletedNode = temp->next;
        temp->next = temp->next->next;
        delete deletedNode;     // deallocate the memory of the deleted node
        this->length--;
        return;
    }

    void print() {
        node *temp = this->head;
        while (temp != NULL) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    LinkedList llist1 = LinkedList();
    llist1.insertLast(10);  // 10
    llist1.insertLast(20);  // 10 20
    llist1.insertLast(30);  // 10 20 30
    llist1.insertLast(40);  // 10 20 30 40 
    llist1.insertLast(50);  // 10 20 30 40 50 
    llist1.deleteAt(3);     // 10 20 30 50
    
    llist1.print();
    return 0;
}