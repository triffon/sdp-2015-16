/*
 * main.cpp
 *
 *  Created on: 20.11.2015 г.
 *      Author: trifon
 */

#include "queue_stack_list.cpp"

void testQueueStackList() {
	QueueStackList<int> qsl;
	qsl.insertEnd(new QueueObject<int>);
	qsl.insertEnd(new StackObject<int>);
	qsl.insertEnd(new StackObject<int>);
	qsl.insertEnd(new QueueObject<int>);
	for(int i = 1; i<= 10; i++)
		for(LinkedListIterator<Object<int>*> it = qsl.begin(); it; ++it)
			(*it)->insert(i);
	cout << qsl << endl;
}


int main() {
	while (true)
	testQueueStackList();
	return 0;
}
