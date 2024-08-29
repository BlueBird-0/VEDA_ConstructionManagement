#include "manager.h"

Manager::Manager() {
    errorMessage = "init Manager error Message";
}

void Manager::setErrorMessage(string errorMessage)
{
    errorMessage = errorMessage;
}

void waitEnter()
{
	setCmdColor();
	cout << "\n계속하려면 Enter 키를 눌러주세요...";
	cin.ignore();
	cin.get();  // Enter 입력을 기다림
	setCmdColor();
}

void setCmdColor(int color)
{
	if (color == -1) // default
		printf("\033[0m");
	if (color == 0)  //blue
		printf("\033[30;94m");
	else if (color == 1) //white
		printf("\033[30;97m");
	else if (color == 2)	//yellow
		printf("\033[30;93m");
}
