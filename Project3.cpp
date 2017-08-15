#include <iostream>
using namespace std;

//implementation of the partition class
class Partition {
protected:
	int beginAddress; // beginning address of the partition
	int endAddress; //end address of the partition
	bool hole; //holds the value determining if free space
	int processID; //holds the process id if needed or -1 for free space
public:
	Partition();//empty constructor
	Partition(int start, int end, bool free, int id);//nonempty constructor
	virtual ~Partition();//destructor
	void copy(const Partition& p);//copy method
	Partition(const Partition& p);//copy constructor
	void operator=(const Partition& p);//operator=
	bool operator==(const Partition& p);//operator== compares only processID attribute
	bool operator!=(const Partition& p);//operator!= compares only processID attribute
	int getBeginAddress();//returns the beginAddress attribute
	int getEndAddress();//returns the endAddress attribute
	int getSize();//returns the end - begin address
	int getProcessID();//returns the processID attribute
	bool checkOpen();//returns the value of the hole attribute
	void setBeginAddress(int value);//changes the beginAddress to the entered value
	void setEndAddress(int value);//changes the endAddress to the entered value
	void setProcessID(int value);//sets the value of processID
	void changeRange(int start, int end);//sets the begin and end address values to start and end values
	void makeFree();//sets the value of hole to true and processID to -1
	void display(ostream& s);//display information about the partition object
	friend ostream& operator<<(ostream& s, Partition& p);//override for operator<<
};

Partition::Partition() {
	beginAddress = 0;
	endAddress = 0;
	hole = true;
	processID = -1;
}

Partition::Partition(int start, int end, bool free, int id) {
	beginAddress = start;
	endAddress = end;
	hole = free;
	processID = id;
}

Partition::~Partition() {

}

void Partition::copy(const Partition& p) {
	beginAddress = p.beginAddress;
	endAddress = p.endAddress;
	hole = p.hole;
	processID = p.processID;
}

Partition::Partition(const Partition& p) {
	copy(p);
}

void Partition::operator=(const Partition& p) {
	copy(p);
}

bool Partition::operator==(const Partition& p) {
	if (processID == p.processID) {
		return true;
	}
	return false;
}

bool Partition::operator!=(const Partition& p) {
	if (processID != p.processID) {
		return true;
	}
	return false;
}

int Partition::getBeginAddress() {
	return beginAddress;
}

int Partition::getEndAddress() {
	return endAddress;
}

int Partition::getSize() {
	return endAddress - beginAddress;
}

int Partition::getProcessID() {
	return processID;
}

bool Partition::checkOpen() {
	return hole;
}

void Partition::setBeginAddress(int value) {
	beginAddress = value;
}

void Partition::setEndAddress(int value) {
	endAddress = value;
}

void Partition::setProcessID(int value) {
	processID = value;
}

void Partition::changeRange(int start, int end) {
	beginAddress = start;
	endAddress = end;
}

void Partition::makeFree() {
	hole = true;
	processID = -1;
}

void Partition::display(ostream& s) {
	if (processID != -1) {
		s << "Process #: " << processID << endl;
		cout << "Start Address: " << beginAddress << endl;
		cout << "End Address: " << endAddress << endl;
		cout << "Size: " << endAddress - beginAddress + 1 << endl;
	}
	else {
		s << "Free Space start and end address: " << beginAddress << ", " << endAddress << endl;
	}
}

ostream& operator<<(ostream&s, Partition& p) {
	p.display(s);
	return s;
}

//exceptions for linkedlist class
class LinkedListException : public exception {};
class LinkedListMemory : public LinkedListException {};
class LinkedListBounds : public LinkedListException {};
class LinkedListNotFound : public LinkedListException {};
class LinkedListAttachToEmpty : public LinkedListException {};
class EnumerationException : public exception {};

//abstract enumeration class
template <class DT>
class Enumeration 
{
public:
	virtual bool hasMoreElements() = NULL;
	//bool method which determines whether there are any more elements in the data structure being Enumerated
	virtual DT& nextElement() = NULL;
	//returns the object which is the next element
};

//creating abstract linkedlist class
template <class DT>
class AbstractLinkedList
{
public:
	virtual DT& info() = NULL;
		//returns the object in the head of the linked list,
		//or throws a bounds error if the list is empty
	virtual AbstractLinkedList<DT>* next() = NULL;
		//returns the LinkedList pointed by this LinkedList
	virtual bool isEmpty() = NULL;
		//returns true if the list is empty
		//but otherwise returns false
	virtual void add(const DT& object) = NULL;
		//adds object to the beginning of the list
	virtual AbstractLinkedList<DT>* setNext(AbstractLinkedList<DT>* next) = NULL;
		//attaches next as _next field of list
		//returns old _next field
		//if current list is empty throws exception
	virtual void insertAt(const DT& newObj, int position) = NULL;
		//inserts newObj so that it will be at node number position
		//(counting the head node as 0)
	virtual DT& infoAt(int position) = NULL;
		//return the object in the linked list at the location
		//specified by position, or throws exception if position
		//is beyond the end of the linked list
	virtual DT& find(const DT& key) = NULL;
		//returns a node matching key or
		//throws exception if none matches
	virtual DT remove() = NULL;
		//deletes the first node of the linked list, if any, and returns it
	virtual DT removeAt(int position) = NULL;
		//deletes the object in the linked list at the location
		//specified by position and returns it, or throws exception if position
		//is beyond the end of the linked list
	virtual DT remove(const DT& key) = NULL;
		//deletes the first node of the linked list, if any, and returns it
	virtual int size() = NULL;
		//returns the number of nodes in the list
	virtual Enumeration<DT>* enumerator();
		//returns an enumeration of the fata contained in the list
	virtual void display(ostream& s);
		//display the nodes of the linked list
	friend ostream& operator<<(ostream& s, AbstractLinkedList<DT>& ll) {
		ll.display(s);
		return s;
	}
		//ostream operator<< override
};

//linkedlistenumerator implementation
template <class DT>
class LLEnumerator : public Enumeration<DT>
{
	friend AbstractLinkedList<DT>;//allow access to AbstractLinkedList
protected:
	AbstractLinkedList<DT>* _LL;//Holds the linkedlist
public:
	LLEnumerator();//empty constructor
	LLEnumerator(AbstractLinkedList<DT>* LL);//nonempty constructor
	virtual bool hasMoreElements();//implement hasMoreElements
	virtual DT& nextElement();//implement nextElement
};

template <class DT>
LLEnumerator<DT>::LLEnumerator() {
	_LL = NULL;
}

template <class DT>
LLEnumerator<DT>::LLEnumerator(AbstractLinkedList<DT>* LL) {
	_LL = LL;
}

template <class DT>
bool LLEnumerator<DT>::hasMoreElements() {
	return ((_LL != NULL) && (!_LL->isEmpty()));
}

template <class DT>
DT& LLEnumerator<DT>::nextElement() {
	if ((_LL != NULL) || (!_LL->isEmpty()))
		throw LinkedListBounds();
	AbstractLinkedList<DT>* curr = _LL;
	_LL = _LL->next();
	return curr->info();
}

template <class DT>
Enumeration<DT>* AbstractLinkedList<DT>::enumerator() {
	return new LLEnumerator<DT>(this);
}

template<class DT>
void AbstractLinkedList<DT>::display(ostream& s) {
	Enumeration<DT>* e = enumerator();
	while (e->hasMoreElements())
	{
		s << e->nextElement();
	}
	delete e;
}



//implementation of the linkedlist class
template <class DT>
class LinkedList : public AbstractLinkedList<DT> 
{
protected:
	DT* _info; // object stored in node of linked list
	LinkedList<DT>* _next; // pointer to the next linked list object
public:
	LinkedList();//empty constructor
	LinkedList(const DT& info);//constructor without a pointer to next
	LinkedList(const DT& info, LinkedList<DT>* next);//constructor with both parameters
	virtual ~LinkedList();//destructor
	void copy(const LinkedList<DT>& ll);//copy method
	LinkedList(const LinkedList<DT>& ll);//copy constructor
	void operator=(const LinkedList<DT>& ll);//operator=
	DT& info();
	//returns the object in the head of the linked list,
	//or throws a bounds error if the list is empty
	AbstractLinkedList<DT>* next();
	//returns the LinkedList pointed by this LinkedList
	bool isEmpty();
	//returns true if the list is empty
	//but otherwise returns false
	void add(const DT& object);
	//adds object to the beginning of the list
	AbstractLinkedList<DT>* setNext(AbstractLinkedList<DT>* next);
	//attaches next as _next field of list
	//returns old _next field
	//if current list is empty throws exception
	void insertAt(const DT& newObj, int position);
	//inserts newObj so that it will be at node number position
	//(counting the head node as 0)
	DT& infoAt(int position);
	//return the object in the linked list at the location
	//specified by position, or throws exception if position
	//is beyond the end of the linked list
	DT& find(const DT& key);
	//returns a node matching key or
	//throws exception if none matches
	int findPosition(const DT& key);
	//find the position in the linkedlist of the object
	DT remove();
	//deletes the first node of the linked list, if any, and returns it
	DT removeAt(int position);
	//deletes the object in the linked list at the location
	//specified by position and returns it, or throws exception if position
	//is beyond the end of the linked list
	DT remove(const DT& key);
	//deletes the first node of the linked list, if any, and returns it
	int size();
	//returns the number of nodes in the list
	void display(ostream& s);
	//display the nodes of the linked list
};



template <class DT>
LinkedList<DT>::LinkedList()
{
	_info = NULL;
	_next = NULL;
}

template<class DT>
LinkedList<DT>::LinkedList(const DT& info)
{
	_info = new DT(info);
	if (_info == NULL)
		throw LinkedListMemory();
	_next = NULL;
}

template<class DT>
LinkedList<DT>::LinkedList(const DT& info, LinkedList<DT>* next)
{
	_info = new DT(info);
	if (_info == NULL)
		throw LinkedListMemory();
	_next = next;
}

template <class DT>
LinkedList<DT>::~LinkedList()
{
	if (_info != NULL) {
		delete _info;
		_info = NULL;
	}

	if (_next != NULL) {
		delete _next;
		_next = NULL;
	}
}


template <class DT>
void LinkedList<DT>::copy(const LinkedList<DT>& ll)
{
	if (ll._info == NULL)
		_info = NULL;
	else
	{
		_info = new DT(*(ll._info));
		if (_info == NULL)
			throw LinkedListMemory();
	}
	if (ll._next == NULL)
		_next = NULL;
	else
	{
		_next = new DT(*(ll._next));
		if (_next == NULL)
			throw LinkedListMemory();
	}
}

template <class DT>
LinkedList<DT>::LinkedList(const LinkedList<DT>& ll) {
	copy(ll);
}


template <class DT>
void LinkedList<DT>::operator=(const LinkedList<DT>& ll) {
	if (_info != NULL)
		delete _info;
	if (_next != NULL)
		delete _next;
	copy(ll);
}

template <class DT>
DT& LinkedList<DT>::info() {
	if (isEmpty())
		throw LinkedListBounds();
	return *_info;
}

template <class DT>
AbstractLinkedList<DT>* LinkedList<DT>::next() {
	return _next;
}

template <class DT>
bool LinkedList<DT>::isEmpty() {
	return (_info == NULL);
}

template <class DT>
void LinkedList<DT>::add(const DT& object) {
	if (_info == NULL)
		_info = new DT(object);
	else {
		LinkedList<DT>* newList = new LinkedList<DT>(*_info, _next);
		if (newList == NULL)
			throw LinkedListMemory();
		*_info = object;
		_next = newList;
	}
}

template <class DT>
AbstractLinkedList<DT>* LinkedList<DT>::setNext(AbstractLinkedList<DT>* next) {
	if (isEmpty())
		throw LinkedListAttachToEmpty();
	AbstractLinkedList<DT>* temp = _next;
	_next = (LinkedList<DT>*) next;
	return temp;
}

template <class DT>
void LinkedList<DT>::insertAt(const DT& newObj, int position) {
	if (position == 0)
		add(newObj);
	else
	{
		if (_next == NULL)
		{
			_next = new LinkedList(newObj);
			if (_next == NULL)
				throw LinkedListMemory();
		}
		else
			_next->insertAt(newObj, position - 1);
	}
}

template <class DT>
DT& LinkedList<DT>::infoAt(int position) {
	if (isEmpty())
		throw LinkedListBounds();
	if (position == 0)
		return *_info;
	if (_next == NULL)
		throw LinkedListBounds();
	return _next->infoAt(position - 1);
}

template <class DT>
DT& LinkedList<DT>::find(const DT& key) {
	if (isEmpty())
		throw LinkedListNotFound();
	if (*key == **_info)
		return *_info;
	if (_next == NULL)
		throw LinkedListBounds();
	return _next->find(key);
}

template <class DT>
int LinkedList<DT>::findPosition(const DT& key) {
	int result = 0;
	if (*key != **_info) {
		result = 1 + _next->findPosition(key);
	}
	return result;
}

template <class DT>
DT LinkedList<DT>::remove() {
	if (isEmpty())
		throw LinkedListBounds();
	DT temp = *_info;
	delete _info;
	if (_next == NULL)
		_info = NULL;
	else {
		LinkedList<DT>* oldnext = _next;
		_info = _next->_info;
		_next = _next->_next;
		oldnext->_info = NULL;
		oldnext->_next = NULL;
		delete oldnext;
	}
	return temp;
}

template <class DT>
DT LinkedList<DT>::removeAt(int position) {
	if (isEmpty())
		throw LinkedListBounds();
	if (position == 0)
		return remove();
	if (_next == NULL)
		throw LinkedListBounds();
	return _next->removeAt(position - 1);
}

template <class DT>
DT LinkedList<DT>::remove(const DT& key) {
	if (isEmpty())
		throw LinkedListBounds();
	if (key == *_info)
		return remove();
	if (_next == NULL)
		throw LinkedListBounds();
	return _next->remove(key);
}

template <class DT>
int LinkedList<DT>::size() {
	if (_next == NULL) {
		if (_info == NULL)
			return 0;
		else
			return 1;
	}
	else
		return 1 + _next->size();
}

template <class DT>
void LinkedList<DT>::display(ostream& s) {
	s << **_info << endl;
	if (_next != NULL)
		_next->display(s);
}

//main method
int main() {
	int process; //will hold the first user input value which holds the process to be added
	int size;//will hold the second user input value which holds the size of process to be added
	int numPartition = 1;//holds the current number of partitions including freespace partitions
	int freeSpace = 128;//holds the value of the amount of total freespace left
	int temp = -1;//this temp value holds a counter allowing the compaction to work correctly
	bool itemAdded = false;//this flag allows process adding to go smoothly
	Partition* found;//holds the partition found by find function
	Partition* initial = new Partition(0, 128, true, -1);//creates the first freespace partition with size 128
	LinkedList<Partition*>* partitionHolder = new LinkedList<Partition*>();//creates the linked list to hold all partitions
	partitionHolder->add(initial);//add the freespace to the linkedlist

	//read in file with a priming read
	cin >> process;
	while (!cin.eof()) {
		cin >> size;
		cout << process << " " << size << endl;//print out what was read in
		if (process == -1) {//print total free space remaining scenario
			cout << "The total amount of free space remaining is: " << freeSpace << endl;
		}
		else if (process == 0) {//print the contents of the linked list scenario
			cout << "Current Process:" << endl;
			cout << *partitionHolder << endl;
		}
		else {//scenario involving a process with a positive integer
			if (size == 0) {//turn process into freespace scenario

				found = partitionHolder->find(new Partition(0,0,true,process));
				partitionHolder->find(found)->makeFree();
				
				freeSpace += found->getSize() + 1;
				if (found->getEndAddress() == 127)
					found->setEndAddress(128);
			}
			else if (size > 0) {//allocating memory
				//look through linkedlist and remove process if it already exists
				try {
					found = partitionHolder->find(new Partition(0, 0, true, process));
					size += found->getSize() + 1;
					found->makeFree();
					freeSpace += found->getSize() + 1;
				}
				catch (LinkedListBounds& e) {

				}
				//find a spot and add the process to the linked list
				for (int i = 0; i < numPartition; i++) {
					if (partitionHolder->infoAt(i)->checkOpen()) {
						if (size <= partitionHolder->infoAt(i)->getSize()) {
							//add new partition
							partitionHolder->insertAt(new Partition(partitionHolder->infoAt(i)->getBeginAddress(), partitionHolder->infoAt(i)->getBeginAddress() + size - 1, false, process),i);
							partitionHolder->infoAt(i+1)->setBeginAddress(partitionHolder->infoAt(i)->getEndAddress() + 1);
							numPartition++;
							freeSpace -= size;
							itemAdded = true;
							break;
						}
					}				
				}
				//there is enough total freespace but compaction is needed first
				if (!itemAdded) {
					//compaction and add
					for (int i = 0; i < numPartition; i++) {
						if (partitionHolder->infoAt(i)->checkOpen()) {
							if (temp == -1) {
								temp = partitionHolder->infoAt(i)->getBeginAddress();
								partitionHolder->removeAt(i);
								numPartition--;
								i--;
							}
							else {
								partitionHolder->removeAt(i);
								numPartition--;
								i--;
							}			
						}
						else {
							if (temp != -1) {
								partitionHolder->infoAt(i)->changeRange(temp, temp + partitionHolder->infoAt(i)->getSize());
								temp = partitionHolder->infoAt(i)->getEndAddress() + 1;
							}
						}
					}
					if (128 - temp >= size) {
						partitionHolder->insertAt(new Partition(temp, temp + size - 1, false, process), numPartition);
						freeSpace -= size;
						numPartition++;
						itemAdded = true;
					}
					if (freeSpace != 0) {
						partitionHolder->insertAt(new Partition(temp + size + 1, temp + size  + freeSpace, true, -1), numPartition);
						numPartition++;
					}
					temp = -1;
				}

				//there was not enough freespace for user request
				if (!itemAdded) 
					cout << "The request was rejected becuase there was not enough space" << endl;
				
				itemAdded = false;
				
			}
			else {//shrinking size of partition in the case of negative size value
				found = partitionHolder->find(new Partition(0, 0, true, process));
				if (found->getSize() + size + 1 == 0) {
					found->makeFree();
					freeSpace -= size;
					if (found->getEndAddress() == 127)
						found->setEndAddress(128);
				}
				else {
					found->setEndAddress(found->getEndAddress() + size);
					partitionHolder->insertAt(new Partition(found->getEndAddress() + 1, found->getEndAddress() - size, true, -1), partitionHolder->findPosition(found)+1);
					numPartition++;
					freeSpace -= size;
				}
			}
		}
		cin >> process;
	}
	return 0;
}