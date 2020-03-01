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
		Record** tmp=new Record*[capacity_+10];
		for(int i=0;i<capacity_;i++){
			tmp[i]=records_[i];
		}
		for(int i=capacity_;i <capacity_+10;i++){
			tmp[i]=nullptr;
		}
		delete[] records_;
		records_=tmp;
		capacity_+=10;
	}
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
	int rc=0;
	for(int i=0;records_[i]!=nullptr;i++){
		rc++;
	}
	return rc;
}



template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int capacity): Table<TYPE>(){
	records_=new Record*[capacity];
	capacity_=capacity;
	for(int i=0;i<capacity_;i++){
		records_[i]=nullptr;
	}
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& other){
	records_=new Record*[other.capacity_];
	capacity_=other.capacity_;
	for(int i=0;i<other.numRecords();i++){
		update(other.records_[i]->key_,other.records_[i]->data_);
	}
}
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& other){
	capacity_=other.capacity_;
	records_=other.records_;
	other.records_=nullptr;
	other.capacity_=0;
}

template <class TYPE>
void SimpleTable<TYPE>::update(const string& key, const TYPE& value){
	int idx=-1;
	int size=numRecords();
	for(int i=0;i<size;i++){
		if(records_[i]->key_ == key){
			idx=i;
		}
	}
	if(idx==-1){
		if(size == capacity_){
			grow();
		}
		records_[size++]=new Record(key,value);
		for(int i=0;i<size-1;i++){
			for(int j=0;j<size-1-i;j++){
				if(records_[j]->key_ > records_[j+1]->key_){
					Record* tmp=records_[j];
					records_[j]=records_[j+1];
					records_[j+1]=tmp;
				}
			}
		}
	}
	else{
		records_[idx]->data_=value;
	}

}

template <class TYPE>
bool SimpleTable<TYPE>::remove(const string& key){
	int idx=-1;
	for(int i=0;i<numRecords();i++){
		if(records_[i]->key_ == key){
			idx=i;
		}
	}
	if(idx!=-1){
		delete records_[idx];
		int size=numRecords();
		for(int i=idx;i<size-1;i++){
			records_[i]=records_[i+1];
		}
		records_[size-1]=nullptr;
		return true;
	}
	else{
		return false;
	}
}

template <class TYPE>
bool SimpleTable<TYPE>::find(const string& key, TYPE& value){
	int idx=-1;
	for(int i=0;i<numRecords();i++){
		if(records_[i]->key_ == key){
			idx=i;
		}
	}
	if(idx==-1)
		return false;
	else{
		value=records_[idx]->data_;
		return true;
	}
}

template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& other){
	if(this!=&other){
		if(records_){
			int sz=numRecords();
			for(int i=0;i<sz;i++){
				remove(records_[0]->key_);
			}
			delete [] records_;
		}
		records_=new Record*[other.capacity_];
		capacity_=other.capacity_;
		int size=other.numRecords();
		for(int i=0;i<size;i++){
			update(other.records_[i]->key_,other.records_[i]->data_);
		}

	}
	return *this;
}
template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& other){
	swap(records_,other.records_);
	swap(capacity_,other.capacity_);
	return *this;
}
template <class TYPE>
SimpleTable<TYPE>::~SimpleTable(){
	if(records_){
		int sz=numRecords();
		for(int i=0;i<sz;i++){
			remove(records_[0]->key_);
		}
		delete [] records_;
	}
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
	virtual bool isEmpty() const {}
	virtual int numRecords() const {}

};
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(int capacity,double maxLoadFactor): Table<TYPE>(){

}

template <class TYPE>
ChainingTable<TYPE>::ChainingTable(const ChainingTable<TYPE>& other){

}
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(ChainingTable<TYPE>&& other){

}
template <class TYPE>
void ChainingTable<TYPE>::update(const string& key, const TYPE& value){

}

template <class TYPE>
bool ChainingTable<TYPE>::remove(const string& key){
	return true;
}

template <class TYPE>
bool ChainingTable<TYPE>::find(const string& key, TYPE& value){
	return true;
}

template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(const ChainingTable<TYPE>& other){
	return *this;

}
template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(ChainingTable<TYPE>&& other){
	return *this;

}
template <class TYPE>
ChainingTable<TYPE>::~ChainingTable(){

}


