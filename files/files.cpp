/*
 * files.cpp
 *
 *  Created on: 16.10.2015 г.
 *      Author: trifon
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

void testifiles() {
	ifstream fi("files.cpp");
	const int MAX = 100;
	char line[MAX] = "";
	int counter = 1;
	while (fi.getline(line, MAX)) {
		cout << counter++ << ": " << line << endl;
	}
	fi.close();

	fi.open("Debug/files", ios::in | ios::binary);
	const int CHUNK_SIZE = 16;
	unsigned char chunk[CHUNK_SIZE];
	counter = 1;
	while(fi) {
		fi.read((char*)chunk, CHUNK_SIZE);
		if (fi.gcount() > 0) {
			cout << dec << counter++ << ": ";
			for(int i = 0; i < fi.gcount(); i++) {
				cout << hex << setw(2) << setfill('0');
				cout << (int)chunk[i] << ' ';
			}
			cout << endl;
		}
	}
}

void testofiles() {
	ofstream fo("email.txt", ios::out | ios::app);
	fo << "Hello: " << 1.2 << ' ' << hex << 56 << endl;
	fo << "Second line" << endl;
	fo.close();

	const int SIZE = 100;
	int d[SIZE];
	for (int i = 0; i < SIZE; i++)
		d[i] = 2 * i;

	fo.open("evens.dat", ios::out | ios::binary);
	fo.write((char const*)d, SIZE * sizeof(int));
	fo.close();
}

void testiofiles() {
	fstream f("email.txt", ios::in | ios::out);
	const int MAX = 100;
	char line[MAX];
	f.getline(line, MAX);
	cout << "Read line: " << line << endl;
	f << "Ignore the following lines, please!\n";
	f.seekp(1, ios::end);
	f << "END OF EMAIL" << endl;
	f.close();
}

int main() {
	// testifiles();
	// testofiles();
	testiofiles();
	return 0;
}


