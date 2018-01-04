#include <iostream>
#include <fstream>
#include "TextQuery.h"
#include "Query.h"
using namespace std;

void runQueries(ifstream &infile);

int main(int argc,char *argv[])
{
	/*ifstream infile(argv[1]);*/
	/*ifstream infile("test.txt");
	runQueries(infile);
	return 0;*/


	ifstream infile("test.txt");
	TextQuery tq(infile);
	Query q = Query("fiery") & Query("bird") | Query("wind");
	cout << q << q.eval(tq) << endl;

	cin.get();
	return 0;





}

void runQueries(ifstream & infile)
{
	//infile是一个ifstream，指向要处理的文件
	TextQuery tq(infile);        //保存文件并建立查询map
	//与用户交互：提示用户要输入查询的单词，完成查询并打印查询结果
	while (true) {
		cout << "enter the word you wang to query,or q to quit:";
		string s;
		if (!(cin >> s) || s == "q")
			break;
		cout << tq.query(s) << endl;
	}
}
