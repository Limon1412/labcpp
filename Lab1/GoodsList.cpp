#include "GoodsList.h"

GoodsList::~GoodsList() {
    Node* obj = head;

    while (obj != nullptr) {
        Node* temp = obj->next;
        delete obj;
        obj = temp;
    }
}

void GoodsList::addGood(Goods& good) {
    Node* node = new Node(&good, nullptr);

    if(head == nullptr) {
        head = node;
    } else {
        Node* obj = head;

        while(obj->next !=nullptr) {
            obj = obj->next;
        }

        obj->next = node;
    }

    nodesCount++;
}

void GoodsList::deleteLastGood() {
    Node* obj = head;

    if (head == nullptr) {
        return;
    }
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
    } else {
        while(obj->next->next != nullptr) {
            obj = obj->next;
        }

        delete (obj->next);
        obj->next = nullptr; 
    }
    
    nodesCount--;
}

void GoodsList::insertGood(int index, Goods& good) {
    if (index > nodesCount || index < 0) {
        return;
    }

    if(index == 0) {
        Node* node = new Node(&good, head);
        head = node;
    } else{
        Node* obj = head;
        int cur = 0;

        while(cur++ != (index - 1)){
            obj = obj->next;
        }

        Node* node = new Node(&good, obj->next);
        obj->next = node;
    }

    nodesCount++;
}

void GoodsList::deleteGoodByIndex(int index) {
    if (index >= nodesCount || index < 0) {
        return;
    }

    if (head == nullptr) {
        return;
    }

    if (index == 0) {
        Node* old = head;
        head = head->next;
        delete old;
    } else {
        Node* obj = head;
        int cur = 0;
        while(cur++ != (index - 1)) {
            obj = obj->next;
        }

        Node* old = obj->next;
        obj->next = old->next;
        delete old;
    }

    nodesCount--;
}

Goods* GoodsList::findGoodByName(const std::string& name) const {
    Node* obj = head;

    while(obj != nullptr) {
        if (name == obj->data->getName()) {
            return obj->data;
        } 

        obj = obj->next;
    }

    return nullptr;
}

void GoodsList::printAllGoods() const {
    Node* obj = head;

    while(obj!= nullptr) {
        std::cout << obj->data->toString() << '\n';

        obj = obj->next;
    }
}