/**************************************************/
/*  Put your linked list code into this file      */
/**************************************************/
/**************************************************/
/*                                                */
/*  Lab 4 linkedlist file                         */
/**************************************************/

#include <string>
#include <iostream>

template <typename T>
class DList{
    struct Node{
        T data_;
        Node* next_;
        Node* prev_;
        Node(const T& data=T{},Node* next=nullptr, Node* prev=nullptr){
            data_=data;
            next_=next;
            prev_=prev;
        }
    };
    Node* front_;
    Node* back_;
    
public:
    DList(){
        front_=nullptr;
        back_=nullptr;
    }
    void push_front(const T& data);
    void push_back(const T& data);
    void pop_front();
    void pop_back();
    void print() const;
    void reversePrint() const;
    bool isEmpty() const {return front_ == nullptr && back_ == nullptr;}
    ~DList();
    
    class const_iterator{
        template <typename> friend class DList;
        const DList* myList_;
        Node* curr_;
        const_iterator(Node* curr, const DList* theList){
            curr_ = curr;
            myList_=theList;
        }
    public:
        const_iterator(){
            myList_=nullptr;
            curr_=nullptr;
        }
        //prefix
        const_iterator operator++(){
            //        if(curr_ != myList_->back_)
            curr_ = curr_->next_;
            return *this;
        }
        //postfix
        const_iterator operator++(int){
            const_iterator old(*this);
            if (curr_ != myList_->back_->next_)
                curr_ = curr_->next_;
            return  old;
        }
        //prefix
        const_iterator operator--(){
            if(curr_){
                curr_=curr_->prev_;
            }
            else{
                if(myList_){
                    curr_=myList_->back_;
                }
            }
            return *this;
        }
        //postfix
        const_iterator operator--(int){
            const_iterator old(*this);
            if(curr_){
                curr_=curr_->prev_;
            }
            else{
                if(myList_){
                    curr_=myList_->back_;
                }
            }
            return  old;
        }
        const T& operator*() const{return curr_->data_;}
        bool operator==(const_iterator rhs) const{
            bool rc=false;
            if(myList_==rhs.myList_ && curr_==rhs.curr_)
                rc=true;
            return rc;
        }
        bool operator!=(const_iterator rhs) const{
            return !(*this==rhs);
        }
    };
    class iterator:public const_iterator{
        template <typename> friend class DList;
    protected:
    public:
        iterator(Node* curr,DList* theList):const_iterator(curr,theList){}
        iterator():const_iterator(){}
        iterator operator++(){
            if (this->curr_ != this->myList_->back_->next_)
                (const_iterator)(*this)++;
            return *this;
        }
        iterator operator++(int){
            iterator rc(*this);
            if (this->curr_ != this->myList_->back_->next_)
                const_iterator::operator++();
            return rc;
        }
        iterator operator--(){
            --(*this);
            return *this;
        }
        iterator operator--(int){
            iterator rc (*this);
            --(*this);
            return rc;
        }
        T& operator*(){
            return this->curr_->data_;
        }
        const T& operator*()const{
            return this->curr_->data_;
        }
    };

    //This function deletes the node that itr iterator points to.
    //return the iterator (and set this iterator) that points to the node that after the deleleted node.
    //e.g. case 1:
    //before remove
    //a <-> b <-> c <-> d <-> e
    //      ^
    //
    //after remove
    //a <-> c <-> d <-> e
    //      ^
    //case 2:
    //before remove
    //a <-> b <-> c
    //            ^
    //after remove
    //a <-> b
    //      ^
    DList::iterator remove(DList::iterator itr){
        if(itr.myList_ != this) throw "Not in this List";
        if(itr.curr_ == nullptr) return end();
        auto toDelete = itr.curr_;
        if (toDelete == front_)
        {
            front_ = toDelete->next_;
            if(front_ != nullptr)
                front_->prev_ = nullptr;
            else//case: the list only contains one node
                back_ = nullptr;
            delete toDelete;
            return begin();
        }else if(toDelete == back_){
            back_ = toDelete->prev_;
            back_->next_ = nullptr;
            auto n = end();
            n--;
            delete toDelete;
            return n;
        }else{
            toDelete->prev_->next_ = toDelete->next_;
            toDelete->next_->prev_ = toDelete->prev_;
            auto toReturn = DList::iterator(toDelete->next_, this);
            delete toDelete;
            return toReturn;
        }
    }

    DList::const_iterator cbegin() const{
        if(front_ != nullptr)
            return DList::const_iterator(front_, this);
        else
            return DList::const_iterator(nullptr, this);
    }
    DList::iterator begin(){
        if (front_ != nullptr)
            return DList::iterator(front_, this);
        
        else
            return DList::iterator(nullptr, this);
    }
    DList::const_iterator cend() const{
        return DList::const_iterator(nullptr,this);
    }
    
    DList::iterator end(){
        if(front_ == nullptr)
            return DList::iterator(front_,this);
        else
            return DList::iterator(back_->next_,this);
    }
    
};

//template <typename T>
//DList<T>::~DList(){
//    Node* curr = front_;
//    while (curr!= back_){
//        curr = curr->next_;
//        delete curr->prev_;
//    }
//    if(back_!= nullptr){
//        delete back_;
//    }
//}
template <typename T>
DList<T>::~DList(){
    Node* curr = front_;
    
    while (curr!= nullptr){
        Node* rm = curr;
        curr = curr->next_;
        delete rm;
    }
}
template <typename T>
void DList<T>::push_front(const T& data){
    
    Node* nn=new Node(data,front_);
    if(front_!=nullptr){
        front_->prev_=nn;
    }
    else{
        back_ = nn;
    }
    front_ = nn;
}

template <typename T>
void DList<T>::push_back(const T& data){
    Node* nn = new Node(data, nullptr,back_);
    if(back_!= nullptr){
        back_->next_ = nn;
    }else{
        front_ = nn;
    }
    back_ = nn;
}

template <typename T>
void DList<T>::pop_front(){
    if(front_!=nullptr){
        Node* rm = front_;
        if(front_->next_!=nullptr){
            front_=front_->next_;
            front_->prev_=nullptr;
        }
        else{
            front_=nullptr;
            back_=nullptr;
        }
        
        delete rm;
    }
}
template <typename T>
void DList<T>::pop_back(){
    if(back_!=nullptr){
        Node* rm = back_;
        if(back_->prev_!=nullptr){
            back_=back_->prev_;
            back_->next_=nullptr;
        }
        else{
            front_=nullptr;
            back_=nullptr;
        }
        delete rm;
    }
}
template <typename T>
void DList<T>::print() const{
    Node* curr=front_;
    while(curr!=nullptr){
        std::cout << curr->data_ << " ";
        curr=curr->next_;
    }
    if(!front_){
        std::cout << "empty list";
    }
    std::cout << std::endl;
}
template <typename T>
void DList<T>::reversePrint() const{
    Node* curr=back_;
    while(curr!=nullptr){
        std::cout << curr->data_ << " ";
        curr=curr->prev_;
    }
    if(!back_){
        std::cout << "empty list";
    }
    std::cout << std::endl;
}
