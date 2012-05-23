#include "admission_umts.h"
#include <QtGui/QApplication>

#include <iostream>
#include "User.h"
#include "BaseStation.h"

using namespace std;

int main(int argc, char *argv[])
{
    srandt
	BaseStation base1(32,5000000,5,64,-100,0.4,30,0,2100000000,43,25);
	User user1(1,&base1);
	base1.addUser(user1);
	
	
	
	int a(2),b(2);
    cout << "Valeur de a : " << a << endl;
    cout << "Valeur de b : " << b << endl;
    //b = ajouteDeux(a);                     //Appel de la fonction
    cout << "Valeur de a : " << a << endl;
    cout << "Valeur de b : " << b << endl;

	//BaseStation base1 = 
	QApplication app(argc, argv);
	admission_umts w;
	w.show();
	return app.exec();
}
