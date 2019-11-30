#ifndef __STACK_QUEUE__
#define __STACK_QUEUE__


class stack_queue {

public:
	static constexpr int _MAX = 100;

	stack_queue() : // initialize members
		_head(-1), 
		_tail(-1)
	{
		for( int i = 0; i < _MAX + 1; i++ ) { 
			_array[i] = 0;
		}
	};


	enum result { empty, success, underflow, overflow };

	result enqueue( int value );
	result dequeue( int *output );
	result push( int value );
	result pop( int *output );
	result peek_queue( int *output );
	result peek_stack( int *output );
	int count();

private:

	void reset();
	
	int _head;
	int _tail;
	int _array[_MAX];
};

#endif

