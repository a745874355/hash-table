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
		Record** tmp=new Record*[capacity_+10];                          //1+1 ------------------------------>need update because this is not efficient in grow capacity.
		for(int i=0;i<capacity_;i++){                                    //1 + capacity + 1
			tmp[i]=records_[i];                                          //capacity
		}
		for(int i=capacity_;i <capacity_+10;i++){                        //10
			tmp[i]=nullptr;                                              //10
		}
		delete[] records_;                                               //1
		records_=tmp;                                                    //1
		capacity_+=10;                                                   //1
	}                                                                    //26+2*capacity
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
    int rc=0;                                                                   //1                  -------------------------> can change to:
	for(int i=0;records_[i]!=nullptr;i++){                                      //1+capacity+capacity                          for(int i=0;records_[i]!=nullptr&&i<capacity;i++)"
		rc++;                                                                   //capacity
	}                                                                           //2+3*capacity
	return rc;                                                                  //runtime is O(n)
}



template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int capacity): Table<TYPE>(){                    //
	records_=new Record*[capacity];                                             //1
	capacity_=capacity;                                                         //1
	for(int i=0;i<capacity_;i++){                                               //1+capacity+capacity
		records_[i]=nullptr;                                                    //capacity
	}                                                                           //3+3*capacity
                                                                                //runtime is O(n)
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& other){
	records_=new Record*[other.capacity_];                                      //1
	capacity_=other.capacity_;                                                  //1
	for(int i=0;i<other.numRecords();i++){                                      //1+capacity+capacity
		update(other.records_[i]->key_,other.records_[i]->data_);               //O(n!)
	}                                                                           //thus overall runtime is O(n!)
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& other){
	capacity_=other.capacity_;                                                  //1
	records_=other.records_;                                                    //1
	other.records_=nullptr;                                                     //1
	other.capacity_=0;                                                          //1
}                                                                               //runtime is O(1)

template <class TYPE>
void SimpleTable<TYPE>::update(const string& key, const TYPE& value){           //
	int idx=-1;                                                                 //1
	int size=numRecords();                                                      //1+O(n)
	for(int i=0;i<size;i++){                                                    //1+capacity +capacity
		if(records_[i]->key_ == key){                                           //capacity
			idx=i;                                                              //capacity
		}
	}
	if(idx==-1){                                                                //1
		if(size == capacity_){                                                  //1
			grow();                                                             //O(1)
		}
		records_[size++]=new Record(key,value);                                 //1
                                                                                //----->bubble sort is slow, could be improved by changing to Insertion sort，becuuse the datasturcture
                                                                                //is sortted array, so do the sort insertion could be much faster than the other sort methord
		for(int i=0;i<size-1;i++){                                              //1+(capacity-1) +(capacity-1)
			for(int j=0;j<size-1-i;j++){                                        //1*(capacity-1)+(capacity-1)! +(capacity-1)!
				if(records_[j]->key_ > records_[j+1]->key_){                    //(capacity-1)!
					Record* tmp=records_[j];                                    //(capacity-1)!
					records_[j]=records_[j+1];                                  //(capacity-1)!
					records_[j+1]=tmp;                                          //(capacity-1)!
				}
			}
		}
	}
	else{
		records_[idx]->data_=value;
	}                                                                           //because (capacity-1)! is O(n!)
                                                                                //thus overall runtime is O(n)
}

template <class TYPE>
bool SimpleTable<TYPE>::remove(const string& key){
	int idx=-1;                                                                 //1
	for(int i=0;i<numRecords();i++){                                            //1+(1+O(n))*capacity + capacity = 1 + capacity^2 + 2*capacity
                                                                                // ------------->need fix, put numRecords() out of the for loop, then the runtime could be O(n)
		if(records_[i]->key_ == key){                                           //capacity
			idx=i;                                                              //capacity
		}
	}
	if(idx!=-1){                                                                //1
		delete records_[idx];                                                   //1
		int size=numRecords();                                                  //1+O(n)
		for(int i=idx;i<size-1;i++){                                            //1+(capacity-1) +(capacity-1)
			records_[i]=records_[i+1];                                          //(capacity-1) +(capacity-1)
		}
		records_[size-1]=nullptr;                                               //1
		return true;                                                            //1
	}
	else{
		return false;
	}                                                                           //thus overall runtime is O(n^2)
}

template <class TYPE>
bool SimpleTable<TYPE>::find(const string& key, TYPE& value){
	int idx=-1;                                                                 //1
	for(int i=0;i<numRecords();i++){                                            //1 + (1+O(n))*capacity + capacity = 1 + capacity^2 + 2*capacity
                                                                                // ------------->need fix, put numRecords() out of the for loop,then the runtime could be O(n)
		if(records_[i]->key_ == key){                                           //capacity
			idx=i;                                                              //capacity
		}
	}
	if(idx==-1)                                                                 //1
		return false;                                                           //1
	else{
		value=records_[idx]->data_;                                             //1
		return true;                                                            //1
	}
}                                                                               //thus overall runtime is O(n^2)

template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& other){
	if(this!=&other){                                                           //1
		if(records_){                                                           //1
			int sz=numRecords();                                                //1+ O(n)
			for(int i=0;i<sz;i++){                                              //1+capacity + capacity
				remove(records_[0]->key_);                                      //capacity
			}
			delete [] records_;                                                 //1
		}
		records_=new Record*[other.capacity_];                                  //1
		capacity_=other.capacity_;                                              //1
		int size=other.numRecords();                                            //1
		for(int i=0;i<size;i++){                                                //1+capacity + capacity
			update(other.records_[i]->key_,other.records_[i]->data_);           //capacity
		}

	}
	return *this;                                                               //1
                                                                                //thus overall runtime is O(n)
}
template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& other){
	swap(records_,other.records_);                                              //1
	swap(capacity_,other.capacity_);                                            //1
	return *this;                                                               //1
}                                                                               //runtime is O(1)
template <class TYPE>
SimpleTable<TYPE>::~SimpleTable(){
	if(records_){                                                               //1
		int sz=numRecords();                                                    //1 + O（n）
		for(int i=0;i<sz;i++){                                                  //1 + capacity + capacity
			remove(records_[0]->key_);                                          //capacity
		}
		delete [] records_;                                                     //1
	}                                                                           //thus overall runtime is O(n)
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


