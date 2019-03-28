//This program is modified from the original ring_queue.cpp

#include <iostream>


template <typename ItemType, int MAX_SIZE>
class RingQueue;



template <typename ItemType, int MAX_SIZE>
class RingQueue {
public:
	// Nested Forward declaration of RingQueue<ItemType,MAX_SIZE>::iterator.
	// This is needed if one plans to turn this home-made iterator into one of
	// the special categories of iterators (e.g., input, output, forward, etc.).
	class iterator;


	// Aliases.
	typedef ItemType* pointer;
	typedef ItemType& reference;


public:
	// Definition of RingQueue<ItemType,MAX_SIZE>::iterator
	class iterator {
	private:
		// A link to the parent container
		RingQueue* parent;

		// The position within the RingQueue is determined by how far ahead we
		// are from the begining of the queue.
		int offset;

	private: 
		iterator(RingQueue* _parent, int _offset = 0)
			: parent(_parent), offset(_offset) { }


		friend class RingQueue<ItemType, MAX_SIZE>;


	public:
		reference operator*() {
			
			return parent->buffer[offset];
		}

		iterator& operator++() {
			
			offset += 1;
			if (offset == MAX_SIZE)
				offset = 0;
			return *this;
		}

		iterator operator++(int unused) {

			iterator temp = *this;
			offset += 1;
			if (offset == MAX_SIZE)
				offset = 0;
			return temp;
		}

		bool operator==(const iterator& rhs) const {
			// Replace the line(s) below with your code.
			if (offset == rhs.offset)
				return true;
			else return false;
		}

		bool operator!=(const iterator& rhs) const {
			// Replace the line(s) below with your code.
			if (offset == rhs.offset)
				return false;
			else return true;
		}

	}; // end of iterator class

	friend class iterator;


private:

	ItemType buffer[MAX_SIZE];

	int begin_index;

	int ring_size;

	int end_index() const {
		int end_index;
		return end_index =   (begin_index + ring_size) % MAX_SIZE ;
	}



public:

	RingQueue() : begin_index(0), ring_size(0) { }

	// Accessors. Note: 'back()' is not considered part of the array.
	ItemType front() const {
		if (ring_size == 0) std::cerr << "Warning: Empty ring!\n";
		
		
		else return buffer[begin_index];
	}

	ItemType back() const {
		if (ring_size == 0) std::cerr << "Warning: Empty ring!";

		// return the element before buffer[end_index].
		else if (end_index == 0)
		{
			return buffer(MAX_SIZE);
		}
		else return buffer[end_index() - 1];
	}


	void push_back(const ItemType& value) {

		buffer[end_index()] = value;
		if (ring_size < MAX_SIZE)
		{
			ring_size++;
		}
		else if (ring_size == MAX_SIZE)
		{
			begin_index++;
			if (begin_index == MAX_SIZE)
			{
				begin_index = 0;
			}
		}
		return;
	}

	void pop_front() {
		
		begin_index++;
		if (begin_index == MAX_SIZE)
		{
			begin_index = 0;
		}
		if (ring_size >= 1)
		{
			ring_size--;
		}
		
		return;
	}


	// Functions that return iterators
	iterator begin() {
	
		return iterator(this, begin_index);
	}

	iterator end() {
		
		return iterator(this, end_index());
	}


	// Miscellaneous functions
	size_t size() const {
	
		return ring_size;
	}

	// Debugging functions
	void dump_queue() const {
		std::cout << "Raw queue...\n";
		for (size_t i = 0; i < MAX_SIZE; ++i)
			std::cout << "Val: " << buffer[i] << ", at: " << buffer + i << '\n';
		std::cout << '\n';
		return;
	}

};



int main() {
	RingQueue<int, 7> rq;
	rq.dump_queue();

	for (int i = 0; i < 8; ++i)
		rq.push_back(i + 1);

	rq.dump_queue();
	rq.pop_front();

	std::cout << "Queue via size:\n";

	// RingQueue<int,7>::iterator it = rq.begin() ;
	auto it = rq.begin();
	for (size_t i = 0; i < rq.size(); ++i) {
		std::cout <<"Value: " << *it << ", address: " << &(*it) << '\n';
		++it;
	}
	std::cout << '\n';



	std::cout << "Queue via iterators:\n";
	for ( auto it = rq.begin() ; it != rq.end() ; ++it ) {
		std::cout << "Value: " << *it << ", address: " << &(*it) << '\n';
	}
	std::cout << '\n';


	rq.dump_queue();

	system("pause");

	return 0;
}



/**
	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	The output of your program [once the missing code is added] should look more
	or less like the output below.

	Note: It is dependent on the device where this driver is executed. However,
	it should be clear that the difference between consecutive memory addresses
	is equal to the number reported by 'size_of( int )'.
	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		Raw queue...
		Val: 2, at: 0x7ffcdeeaab40
		Val: 0, at: 0x7ffcdeeaab44
		Val: 4198285, at: 0x7ffcdeeaab48
		Val: 0, at: 0x7ffcdeeaab4c
		Val: 0, at: 0x7ffcdeeaab50
		Val: 0, at: 0x7ffcdeeaab54
		Val: 0, at: 0x7ffcdeeaab58

		Raw queue...
		Val: 8, at: 0x7ffcdeeaab40
		Val: 2, at: 0x7ffcdeeaab44
		Val: 3, at: 0x7ffcdeeaab48
		Val: 4, at: 0x7ffcdeeaab4c
		Val: 5, at: 0x7ffcdeeaab50
		Val: 6, at: 0x7ffcdeeaab54
		Val: 7, at: 0x7ffcdeeaab58

		Queue via size:
		Value: 3, address: 0x7ffcdeeaab48
		Value: 4, address: 0x7ffcdeeaab4c
		Value: 5, address: 0x7ffcdeeaab50
		Value: 6, address: 0x7ffcdeeaab54
		Value: 7, address: 0x7ffcdeeaab58
		Value: 8, address: 0x7ffcdeeaab40

		Queue via iterators:
		Value: 3, address: 0x7ffcdeeaab48
		Value: 4, address: 0x7ffcdeeaab4c
		Value: 5, address: 0x7ffcdeeaab50
		Value: 6, address: 0x7ffcdeeaab54
		Value: 7, address: 0x7ffcdeeaab58
		Value: 8, address: 0x7ffcdeeaab40

		Raw queue...
		Val: 8, at: 0x7ffcdeeaab40
		Val: 2, at: 0x7ffcdeeaab44
		Val: 3, at: 0x7ffcdeeaab48
		Val: 4, at: 0x7ffcdeeaab4c
		Val: 5, at: 0x7ffcdeeaab50
		Val: 6, at: 0x7ffcdeeaab54
		Val: 7, at: 0x7ffcdeeaab58
 */