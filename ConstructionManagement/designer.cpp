#include "designer.h"
#include <iostream>
#include <string>
using namespace std;

void designer::drawTitle(const string title, const string engTitle)
{
    int roop;

    cout << "��";
    for (int i = 0; i < WIDTH; i++)
		cout << "��";
    cout << "��" << endl;

    //title
    cout << "��";
	roop = (WIDTH - title.size()) / 2;
    for (int i = 0; i < roop; i++)
        cout << " ";
    cout << title;
    for (int i = 0; i < roop; i++)
        cout << " ";
    cout << "��" << endl;


    cout << "��";
    printf("%30s", engTitle.c_str());
    //roop = (WIDTH - engTitle.size()) / 2;
    //for (int i = 0; i < roop; i++)
    //    cout << " ";
    //cout << engTitle;
    for (int i = 0; i < roop+1; i++)
        cout << " ";
    cout << "��" << endl;


    cout << "��";
    for (int i = 0; i < WIDTH; i++)
        cout << "��";
    cout << "��" << endl;
    //cout << "��                   * " << title << " *                   ��" << endl;
    //cout << "��              (" << engTitle << ")              ��" << endl;
    //cout << "������������������������������������������������������������������������������������������������������������������������������������������" << endl;
}
