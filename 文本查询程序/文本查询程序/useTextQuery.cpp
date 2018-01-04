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
	//infile��һ��ifstream��ָ��Ҫ������ļ�
	TextQuery tq(infile);        //�����ļ���������ѯmap
	//���û���������ʾ�û�Ҫ�����ѯ�ĵ��ʣ���ɲ�ѯ����ӡ��ѯ���
	while (true) {
		cout << "enter the word you wang to query,or q to quit:";
		string s;
		if (!(cin >> s) || s == "q")
			break;
		cout << tq.query(s) << endl;
	}
}
