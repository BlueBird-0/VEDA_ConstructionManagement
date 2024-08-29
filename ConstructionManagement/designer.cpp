#include "designer.h"
#include <iostream>
#include <string>
using namespace std;

void designer::drawTitle(const string title, const string engTitle)
{
    int roop;

    cout << "忙";
    for (int i = 0; i < WIDTH; i++)
		cout << "式";
    cout << "忖" << endl;

    //title
    cout << "弛";
	roop = (WIDTH - title.size()) / 2;
    for (int i = 0; i < roop; i++)
        cout << " ";
    cout << title;
    for (int i = 0; i < roop; i++)
        cout << " ";
    cout << "弛" << endl;


    cout << "弛";
    printf("%30s", engTitle.c_str());
    //roop = (WIDTH - engTitle.size()) / 2;
    //for (int i = 0; i < roop; i++)
    //    cout << " ";
    //cout << engTitle;
    for (int i = 0; i < roop+1; i++)
        cout << " ";
    cout << "弛" << endl;


    cout << "戍";
    for (int i = 0; i < WIDTH; i++)
        cout << "式";
    cout << "扣" << endl;
    //cout << "弛                   * " << title << " *                   弛" << endl;
    //cout << "弛              (" << engTitle << ")              弛" << endl;
    //cout << "弛式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式" << endl;
}
