#include "admission_umts.h"
#include <QtGui/QApplication>

#include <iostream>
#include "User.h"
#include "BaseStation.h"
#include <time.h> 
#include <ctime>


using namespace std;


void wait_until_next_second()
{
    time_t before = time(0);
    while (difftime(time(0), before) < 1);
}


int main(int argc, char *argv[])
{
    int i=3;
	float _time;
	srand(time(NULL));
	BaseStation base1(32,5000000,5,64,-100,0.4,30,0,2100000000,43,25);
	User user1(1,&base1);
	User user2(2,&base1);
	base1.addUser(&user1);
	base1.addUser(&user2);
	cout << "salut" ;
	wait_until_next_second();
	
	while(i<10)
	{
		
		
		
		
		User * user3 = new User(i,&base1);
		base1.addUser(user3);
		i++;
		base1.computeTotalTransmitted();
		wait_until_next_second();




	}
	
	
	
   

	//BaseStation base1 = 
	QApplication app(argc, argv);
	admission_umts w;
	w.show();
	return app.exec();
}


