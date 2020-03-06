/*************************************************************/
/*                                                           */
/*    starter file for a2                                    */
/*    													     */
/*                                                           */
/*************************************************************/

#include <string>
#include <utility>
#include <functional>
#include "mylist.h"
#ifdef _DEBUG
#include <iostream>
//using namespace std;
using std::cout;
using std::endl;
using std::operator<<;
#endif //_DEBUG

//Table is the abstract base class, describes the functianalities of the Table class
using std::string;
template <class TYPE>
class Table{
public:
	Table(){}
	virtual void update(const string& key, const TYPE& value)=0;
	virtual bool remove(const string& key)=0;
	virtual bool find(const string& key, TYPE& value)=0;
	virtual int numRecords() const = 0;
	virtual bool isEmpty() const = 0;
	virtual ~Table(){}
};

//SimpleTable implements the abstract table class
template <class TYPE>
class SimpleTable:public Table<TYPE>{

	struct Record{
		TYPE data_;
		string key_;
		Record(const string& key, const TYPE& data){
			key_=key;
			data_=data;
		}

	};

	Record** records_;   //the table
	int capacity_;       //capacity of the array

	void grow(){
		Record** tmp=new Record*[capacity_+10];               //1+1d
		for(int i=0;i<capacity_;i++){                         //1 + capacity + 1
			tmp[i]=records_[i];                               //capacity
		}
		for(int i=capacity_;i <capacity_+10;i++){             //10
			tmp[i]=nullptr;                                   //10
		}
		delete[] records_;                                    //1
		records_=tmp;                                         //1
		capacity_+=10;                                        //1
	}                                                         //26+2*capacity
                                                              //because capacity is consider as the n,so run time is O(n)
public:
	SimpleTable(int capacity);
	SimpleTable(const SimpleTable& other);
	SimpleTable(SimpleTable&& other);
	virtual void update(const string& key, const TYPE& value);
	virtual bool remove(const string& key);
	virtual bool find(const string& key, TYPE& value);
	virtual const SimpleTable& operator=(const SimpleTable& other);
	virtual const SimpleTable& operator=(SimpleTable&& other);
	virtual ~SimpleTable();
	virtual bool isEmpty() const{return numRecords()==0;}
	virtual int numRecords() const;
};

template <class TYPE>
int SimpleTable<TYPE>::numRecords() const{
    int rc=0;                                               //1             d
	for(int i=0;records_[i]!=nullptr;i++){                  //1+capacity+capacity     
		rc++;                                               //capacity
	}                                                       //2+3*capacity
	return rc;                                              //Totol is 3 + 6*capacity
}                                                           //Thus runtime is O(n)



template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int capacity): Table<TYPE>(){
	records_=new Record*[capacity];                         //1
	capacity_=capacity;                                     //1
	for(int i=0;i<capacity_;i++){                           //1+capacity+capacity
		records_[i]=nullptr;                                //capacity
	}                                                       //3+3*capacity
                                                            //Totol is 6 + 6 * capacity
}                                                           //Thus runtime is O(n)

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& other){
	records_=new Record*[other.capacity_];                  //1
	capacity_=other.capacity_;                              //1
	for(int i=0;i<other.numRecords();i++){                  //1+capacity+capacity
		update(other.records_[i]->key_,other.records_[i]->data_);  //O(n!)
	}
}                                                           //thus overall runtime is O(n!)

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& other){
	capacity_=other.capacity_;                          //1
	records_=other.records_;                            //1
	other.records_=nullptr;                            //1
	other.capacity_=0;                                 //1
}                                                      //runtime is O(1)

template <class TYPE>
void SimpleTable<TYPE>::update(const string& key, const TYPE& value){
	int idx=-1;                                         //1
	int size=numRecords();                              //1+O(n)
	for(int i=0;i<size;i++){                            //1+capacity +capacity
		if(records_[i]->key_ == key){                   //capacity
			idx=i;                                      //capacity
		}
	}
	if(idx==-1){                                       //1
		if(size == capacity_){                         //1
			grow();                                    //O(1)
		}
		records_[size++]=new Record(key,value);       //1
		for(int i=0;i<size-1;i++){                    //1+(capacity-1) +(capacity-1)
			for(int j=0;j<size-1-i;j++){               //1*(capacity-1)+(capacity-1)! +(capacity-1)!
				if(records_[j]->key_ > records_[j+1]->key_){  //(capacity-1)!
					Record* tmp=records_[j];                  //(capacity-1)!
					records_[j]=records_[j+1];                //(capacity-1)!
					records_[j+1]=tmp;                        //(capacity-1)!
				}
			}
		}
	}
	else{
		records_[idx]->data_=value;
	}                                                     //because bubble sort part is O(n^2)
                                                          //thus overall runtime is O(n^2)
}

template <class TYPE>
bool SimpleTable<TYPE>::remove(const string& key){
	int idx=-1;                                            //1
	for(int i=0;i<numRecords();i++){                       //1+(1+O(n))*capacity + capacity = 1 + capacity^2 + 2*capacity
		if(records_[i]->key_ == key){                       //capacity
			idx=i;                                          //capacity
		}
	}
	if(idx!=-1){                                       //1
		delete records_[idx];                          //1
		int size=numRecords();                         //1+O(n)
		for(int i=idx;i<size-1;i++){                   //1+(capacity-1) +(capacity-1)
			records_[i]=records_[i+1];                 //(capacity-1) +(capacity-1)
		}
		records_[size-1]=nullptr;                      //1
		return true;                                   //1
	}
	else{
		return false;
	}                                                   //thus overall runtime is O(n^2)
}

template <class TYPE>
bool SimpleTable<TYPE>::find(const string& key, TYPE& value){
	int idx=-1;                                      //1
	for(int i=0;i<numRecords();i++){               //1 + (1+O(n))*capacity + capacity = 1 + capacity^2 + 2*capacity
		if(records_[i]->key_ == key){               //capacity
			idx=i;                                  //capacity
		}
	}
	if(idx==-1)                                    //1
		return false;                              //1
	else{
		value=records_[idx]->data_;               //1
		return true;                              //1
	}
}                                               //thus overall runtime is O(n^2)

template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& other){
	if(this!=&other){                                       //1
		if(records_){                                        //1
			int sz=numRecords();                             //1+ O(n)
			for(int i=0;i<sz;i++){                           //1+capacity + capacity
				remove(records_[0]->key_);                   //capacity
			}
			delete [] records_;                               //1
		}
		records_=new Record*[other.capacity_];                //1
		capacity_=other.capacity_;                            //1
		int size=other.numRecords();                          //1
		for(int i=0;i<size;i++){                               //1+capacity + capacity
			update(other.records_[i]->key_,other.records_[i]->data_);   //capacity
		}

	}
	return *this;                                     //1
                                                   //thus overall runtime is O(n)
}
template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& other){
	std::swap(records_,other.records_);               //1
	std::swap(capacity_,other.capacity_);             //1
	return *this;                                //1
}                                                //runtime is O(1)
template <class TYPE>
SimpleTable<TYPE>::~SimpleTable(){
	if(records_){                                //1
		int sz=numRecords();                     //1 + O（n）
		for(int i=0;i<sz;i++){                   //1 + capacity + capacity
			remove(records_[0]->key_);           //capacity
		}
		delete [] records_;                      //1
	}                                            //thus overall runtime is O(n)
}

template <class TYPE>
class ChainingTable:public Table<TYPE>{
public:
	ChainingTable(int maxExpected, double maxLoadFactor);
	ChainingTable(const ChainingTable& other);
	ChainingTable(ChainingTable&& other);
	virtual void update(const string& key, const TYPE& value);
	virtual bool remove(const string& key);
	virtual bool find(const string& key, TYPE& value);
	virtual const ChainingTable& operator=(const ChainingTable& other);
	virtual const ChainingTable& operator=(ChainingTable&& other);
	virtual ~ChainingTable();
	virtual bool isEmpty() const {
		return numRecords_==0;
	}
	virtual int numRecords() const {
		return numRecords_;
	}

#ifdef _DEBUG
	void print(){
		cout << endl << "**********************************" << endl;
		cout << "Current list:" << endl
			<< "Size: " << size_ << endl
			<< "Records: " << numRecords_ << endl
			<< "Capacity: " << capacity_ << endl
			<< "currentLoadFactor: " << currentLoadFactor_ << endl
			<< "maxLoadFactor: " << maxLoadFactor_ << endl;
		for (size_t i = 0; i < capacity_; i++)
		{
			cout << i << ". ";
			if(!records_[i]){
				cout <<"Empty" << endl;
				continue;
			}
			for(auto& record : *records_[i]){
				cout << "[" << record.key << ", " << record.value << "]->";
			}
			cout << "nil" << endl;
		}
		cout << "**********************************" <<endl << endl;

	}
#endif //_DEBUG



private:
	struct Record
	{
		friend class ChainingTable;
		TYPE value = {}; 
		string key = {}; 
		Record(){};
		Record(const string& key, const TYPE& value){
			this->value = value;
			this->key = key;
		}
		Record(Record&& rhs){
			this->value = rhs.value;
			this->key = rhs.key;
			rhs.value = {};
			rhs.key = {};
		}
		Record& operator=(const Record& rhs){
			this->value = rhs.value;
			this->key = rhs.key;
			return *this;
		}
		Record& operator=(Record&& rhs){
			/*
			delete keys;
			this->value = rhs.value;
			this->key = rhs.key;
			rhs.value = {};
			rhs.key = {};
			return *this;
			*/
			return*this;
		}
	};
	DList<Record>** records_ = nullptr;
	size_t size_ = 0;
	size_t capacity_ = 0;
	size_t numRecords_ = 0;
	double maxLoadFactor_ = 0;
	double currentLoadFactor_ = 0;
	void expand();
};
template <class TYPE>
void ChainingTable<TYPE>::expand(){
#ifdef _DEBUG
	cout << "expanding" << endl;
	cout << "currentLoadFactor: " << currentLoadFactor_ << endl;
#endif
	auto prevCap = capacity_;
	capacity_ += capacity_;
	currentLoadFactor_ = 0; //reset currentLoadFactor
	size_ = 0;
	numRecords_ = 0;
	auto n = records_; //old records_;
	records_ = new DList<Record>* [capacity_];
	for (size_t i = 0; i < capacity_; i++)
	{
		records_[i] = nullptr;
	}
	
	for(size_t i = 0; i < prevCap; i++){
		//if Dlink is not empty, copy whole link, 
		if(n[i]){
			for(auto& record : *n[i]){                
				update(record.key, record.value);
			}
			delete n[i];
		}
	}
	delete[] n;
#ifdef _DEBUG
	cout << "expanded" << endl;
	cout << "currentLoadFactor: " << currentLoadFactor_ << endl;
#endif
}

template <class TYPE>
ChainingTable<TYPE>::ChainingTable(int capacity,double maxLoadFactor): Table<TYPE>(){
	capacity_ = capacity;
	maxLoadFactor_ = maxLoadFactor;
	records_ = new DList<Record>*[capacity_];
	for (size_t i = 0; i < capacity_; i++)
	{
		records_[i] = 0;
	}
	
}

template <class TYPE>
ChainingTable<TYPE>::ChainingTable(const ChainingTable<TYPE>& other){
	*this = ChainingTable(other.capacity_, other.maxLoadFactor_);
	for (size_t i = 0; i < other.capacity_; i++)
	{
		if(other.records_ && other.records_[i]){
			for(auto& record : *(other.records_[i])){
				update(record.key, record.value);
			}
		}
	}
}
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(ChainingTable<TYPE>&& other){
	this->capacity_ = other.capacity_;
	this->records_ = other.records_;
	this->numRecords_ = other.numRecords_;
	this->size_ = other.size_;
	this->maxLoadFactor_ = other.maxLoadFactor_;
	this->currentLoadFactor_ = other.currentLoadFactor_;
	other.records_ = nullptr;
	other.numRecords_ = 0;
	other.size_ = 0;
	other.currentLoadFactor_ = 0;
}

template <class TYPE>
void ChainingTable<TYPE>::update(const string& key, const TYPE& value){
	std::hash<std::string> hash;
	size_t idx = hash(key) % capacity_;
	if(!records_[idx]){//the key does not exist
		if(currentLoadFactor_ >= maxLoadFactor_) expand();
		records_[idx] = new DList<Record>();
		records_[idx]->push_back(Record(key, value));
		size_++;
		numRecords_++;
		currentLoadFactor_ = (double)numRecords_/(double)capacity_;
		return;
	}else{ //the key may exist
		for(auto& record : *records_[idx]){//iterate the list
			if(record.key == key){//the key exist
#ifdef _DEBUG
				cout << "updating k/v at " << idx << " of key " << record.key << " from " << record.value << " to " << value << endl;
#endif
				record.value = value;
				return;
			}
		}
		//the key does not exist
		records_[idx]->push_back(Record(key, value));
		numRecords_++;
		currentLoadFactor_ = (double)numRecords_/(double)capacity_;
		return;
	}
}

template <class TYPE>
bool ChainingTable<TYPE>::remove(const string& key){
	std::hash<std::string> hash;
	size_t idx = hash(key) % capacity_;
	for(auto itr = records_[idx]->begin(); itr != records_[idx]->end(); itr++){
		if((*itr).key == key) {		
#ifdef _DEBUG
			cout << "Do remove idx of " << idx <<" (*itr).key " << (*itr).key << " key "  << key << endl;
#endif				
			records_[idx]->remove(itr);
			if(records_[idx]->isEmpty()){
				delete records_[idx];
				records_[idx] = nullptr;
				size_--;
			}				
			numRecords_--;
			return true;
		}
	}
	return false;
}

template <class TYPE>
bool ChainingTable<TYPE>::find(const string& key, TYPE& value){
	std::hash<std::string> hash;
	size_t idx = hash(key) % capacity_;
	for(auto& record: *records_[idx]){
		if(record.key == key){
			value = record.value;
			return true;
		}	
	}
	return false;
}

template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(const ChainingTable<TYPE>& other){
	if(records_){
		for (size_t i = 0; i < capacity_; i++)
		{
			delete records_[i];
		}
		delete[] records_;
		records_ = nullptr;
	}
	*this = ChainingTable(other);
	return *this;

}
template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(ChainingTable<TYPE>&& other){
	if(records_){
		for (size_t i = 0; i < capacity_; i++)
		{
			delete records_[i];
		}
		delete[] records_;
	}
	this->capacity_ = other.capacity_;
	this->records_ = other.records_;
	this->numRecords_ = other.numRecords_;
	this->size_ = other.size_;
	this->maxLoadFactor_ = other.maxLoadFactor_;
	this->currentLoadFactor_ = other.currentLoadFactor_;
	other.records_ = nullptr;
	other.numRecords_ = 0;
	other.size_ = 0;
	other.currentLoadFactor_ = 0;
	return *this;

}
template <class TYPE>
ChainingTable<TYPE>::~ChainingTable(){
	if(records_){
		for (size_t i = 0; i < capacity_; i++)
		{
			delete records_[i];
		}
		delete[] records_;
	}
	
}


