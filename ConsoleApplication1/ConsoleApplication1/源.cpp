#include <iostream>
#include <string>
using namespace std;

struct CandyBar {
	string name;
	float weight;
	int Calorie_content;
};

 int main() {
	CandyBar snack = {
		"Mocha Munch",
		2.3,
		350
	};
	cout << snack.name << endl;
	cout << snack.weight << endl;
	cout << snack.Calorie_content << endl;
	
	CandyBar * ptr = new CandyBar;
	
	cout << ptr->name << " " << ptr->weight << " " << ptr->Calorie_content << endl;
	cout << "Please enter the new Bar name" << endl;
	cin >> ptr->name;
	cout << ptr->name;

	delete [] ptr;
	return 0;
}