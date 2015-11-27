/*
 * main.cpp
 *
 *  Created on: 20.11.2015 г.
 *      Author: trifon
 */

#include "queue_stack_list.cpp"
#include "slist.cpp"

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

void testSList() {
	SList* sl = new SList;
		SList* sl12 = new SList;
			SList* sl2 = new SList;
			sl2->insertEnd(new IntElement(2));
		sl12->insertEnd(new IntElement(1));
		sl12->insertEnd(sl2);

			SList* sl34 = new SList;
				SList* sl3 = new SList;
				sl3->insertEnd(new IntElement(3));
			sl34->insertEnd(sl3);
			sl34->insertEnd(new IntElement(4));

			SList* sl56 = new SList;
				SList* sl6 = new SList;
				sl6->insertEnd(new IntElement(6));
			sl56->insertEnd(new IntElement(5));
			sl56->insertEnd(sl6);

			SList* sl7 = new SList;
			sl7->insertEnd(new IntElement(7));

		SList* sl34567 = new SList;
		sl34567->insertEnd(sl34);
		sl34567->insertEnd(sl56);
		sl34567->insertEnd(new SList);
		sl34567->insertEnd(sl7);

	sl->insertEnd(sl12);
	sl->insertEnd(sl34567);
	sl->insertEnd(new IntElement(8));
	sl->print(cout);
	cout << endl;

	LinkedList<int> l;
	sl->collectInts(l);
	cout << l;
	delete sl;
}

int main() {
	while (true)
	//testQueueStackList();
	testSList();
	return 0;
}
