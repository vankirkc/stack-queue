#include <iostream>
#include "StackQueue.hpp"

using namespace std;

using result = stack_queue::result;

int  MAX = stack_queue::_MAX;

void test_wraparound_3_times() {
	stack_queue unit;

	result r;

	int item;

	// fill up the queue

	for( int i = 0; i < MAX; i++ ) {

		r  = unit.enqueue( i );

		assert( r == result::success );
	}

	// queue is now full

	for( int i = 0; i < MAX * 3; i++ ) {

		// make one space by dequeuing. this moves the head
		// forward by one
		r = unit.dequeue( &item );

		assert( r == result::success );
		assert( item == ( i % MAX ) );

		// now enqueue the item we just dequeued again
		r = unit.enqueue( item );

		// we should have 100 items again, straddling the end of the array
		assert( r == result::success );
		assert( unit.count() == MAX );
	}

	// now we should have 100 items in the array in the original order

	for( int i = 0; i < MAX; i++ ) {
		r = unit.dequeue( &item );

		assert( i == item );

 		assert( unit.count() == stack_queue::_MAX - i - 1 );
		assert( r == result::success );
	}

}


void test_wrap_around_cases() {
	test_wraparound_3_times();
}


void test_push_then_pop_until_empty() {

	// create an empty instance 
	stack_queue testunit; 

	result r;
	for( int i = 0; i < MAX; i++ ) {
		r = testunit.push( i );
		assert( r == result::success );
	}

	int item;

	for( int i = MAX-1; i >= 0; i-- ) {
		r = testunit.pop( &item );
		assert( r == result::success );
		assert( item == i );
	}

	assert( testunit.count() == 0 );
}

void test_enqueue_then_dequeue_until_empty() {
	// create an empty instance 
	stack_queue testunit; 

	result r;
	for( int i = 0; i < MAX; i++ ) {
		r = testunit.enqueue( i );
		assert( r == result::success );
	}

	int item;

	for( int i = 0; i < MAX; i++ ) {
		r = testunit.dequeue( &item );
		assert( r == result::success );
		assert( item == i );
	}

	assert( testunit.count() == 0 );
}

void test_dequeue_and_pop_when_empty() {
	stack_queue testunit;

	int item;

	result r = testunit.dequeue(&item);

	assert( r == result::underflow);
	
	assert( testunit.count() == 0 );

	stack_queue testunit2;

	r = testunit2.pop( &item );

	assert( r == result::underflow );

	assert( testunit2.count() == 0 );

}

void test_push_and_enqueue_when_empty() {
	stack_queue testunit;

	result r = testunit.push( 100 );

	assert( r == result::success );
	assert( testunit.count() == 1 );

	int item;

	r = testunit.pop( &item );

	assert( r == result::success );
	assert( testunit.count() == 0 );
	assert( item == 100 );

	r = testunit.enqueue( 300 );

	assert( r == result::success );
	assert( testunit.count() == 1 );

	r = testunit.dequeue( &item );

	assert( r == result::success );
	assert( testunit.count() == 0 );
	assert( item == 300 );

}


void test_empty_cases() {
	test_push_then_pop_until_empty();
	test_enqueue_then_dequeue_until_empty();
	test_dequeue_and_pop_when_empty();
	test_push_and_enqueue_when_empty();
}

void test_push_until_full() {
	stack_queue unit;

	result r;

	for( int i = 0; i < MAX; i++ ) {
		r = unit.push( i );
		assert( r == result::success );
	}

	assert( unit.count() == MAX );

	// now attempt to push one more item

	r = unit.push( 592 );

	assert( r == result::overflow );

}

void test_enqueue_until_full() {
	stack_queue unit;

	result r;

	for( int i = 0; i < MAX; i++ ) {
		r = unit.push( i );
		assert( r == result::success );
	}

	assert( unit.count() == MAX );

	// now attempt to push one more item

	r = unit.push( 592 );

	assert( r == result::overflow );
}

void test_full_cases() {
	test_push_until_full(); 
	test_enqueue_until_full();
}


void test_stack_peeking() {
	stack_queue unit;

	result r;
	int item;


	for( int i = 0 ; i < 100; i++ ) {
		r = unit.push( i );

		assert( r == result::success );
	}

	r = unit.pop( &item );
	assert( r == result::success );

	r = unit.push( 4782 );

	assert( r == result::success );

	r = unit.peek_stack( &item );

	assert( r == result::success );
	assert( item == 4782 );	
}

void test_queue_peeking() {
	stack_queue unit;

	result r;

	r = unit.enqueue( 4782 );


	for( int i = 0 ; i < 99; i++ ) {
		r = unit.enqueue( i );

		assert( r == result::success );
	}

	int item;

	r = unit.peek_stack( &item );

	assert( r == result::success );
	assert( item == 4782 );	
}

void test_peeking() {
	test_stack_peeking();


}
void run_all_tests() {
	test_wrap_around_cases();
 	test_empty_cases();
	test_full_cases();
	test_peeking();
}

int main() {
	
	run_all_tests();

	cout << "All tests completed!" << endl;

	return 0;
}


