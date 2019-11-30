#include "StackQueue.hpp"

void stack_queue::reset() {
	_head = -1;
	_tail = -1;
}

stack_queue::result stack_queue::enqueue( int value ) {

	int c = count();

	// first check if we have sufficient room to add a value
	if( c < stack_queue::_MAX ) {
		// there is room for another value

		if( _head < 0 ) {
			// collection was empty, so set _head in addition to _tail
			_head = 0;
			_tail = 0;
		} else {
			_tail++;

			if( _tail == stack_queue::_MAX ) {
				// we're off the end, so wrap around
				_tail = 0;
			}
		}
		_array[_tail] = value;

		return stack_queue::result::success;
	} else {
		// collection is full. return overflow error
		return stack_queue::result::overflow;
	}
}

stack_queue::result stack_queue::dequeue( int *output ) {
	int c = count();

	if( c == 0 ) {
		return stack_queue::result::underflow;
	} else if( c == 1 ) {
		// reset the collection since it's now empty
		*output = _array[_head];

		reset(); 

		return stack_queue::result::success;
	} else {
		*output = _array[_head];

		_head++;

		if( _head == stack_queue::_MAX ) {
			_head = 0;
		}

		return stack_queue::result::success;
	}
}

stack_queue::result stack_queue::push( int value ) {
	// push is semantically identical to enqueue...
	return enqueue( value );
}

stack_queue::result stack_queue::pop( int *output ) {
	int c = count();

	if( c == 0 ) {
		return stack_queue::result::underflow;
	} else if( c == 1 ) {
		// reset the collection since it's now empty
		*output = _array[_tail];

		reset();

		return stack_queue::result::success;
	} else  {
		*output = _array[_tail];

		_tail--;
		if( _tail < 0 ) {
			_tail += stack_queue::_MAX - 1;
		} 

		return stack_queue::result::success;
	} 
}

stack_queue::result stack_queue::peek_queue( int *output ) {
	if( count() > 0 ) {
		*output = _array[_head];
		return stack_queue::result::success;
	} else {
		*output = 0;
		return stack_queue::result::empty;
	}
}

stack_queue::result stack_queue::peek_stack( int *output ) {
	if( count() > 0 ) {
		int offset = _tail;
		if( offset < 0 ) {
			offset += stack_queue::_MAX;
		} 
		*output = _array[offset];
		return stack_queue::result::success;
	} else {
		*output = 0;
		return stack_queue::result::empty;
	}
}

int stack_queue::count() {
	int c = 0; 

	if( _head >= 0 ) {
		if( _tail >= _head ) {
			c = _tail - _head + 1;
		} else {
			c = _MAX - _head + _tail + 1;
		} 
	}

	return c;
}