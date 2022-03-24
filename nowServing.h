/***********************************************************************
 * Header:
 *    NOW SERVING
 * Summary:
 *    This creates a data type that can be used inside main for the deque
 *		It simulates help requests in a lab and has information on priority and time created
 * Author
 *    Brandon Jarrell
 ************************************************************************/

#ifndef NOW_SERVING_H
#define NOW_SERVING_H

#include <string>
#include "deque.h"     // for DEQUE
using namespace std;
// the interactive nowServing program
void nowServing();


class request
{
private:
	string section;
	string name;
	int minutes;
	bool emergency = false;

public:
	request() : section(""), name(""), minutes(0) {}
	request(string c, string n, int m) : section(c), name(n), minutes(m) {}
	request(const request& rhs)
	{
		section = rhs.section;
		name = rhs.name;
		minutes = rhs.minutes;
		emergency = rhs.emergency;
	}

	// Getters
	string getClass() { return section; }
	string getName() { return name; }
	int getMin() { return minutes; }

	// Setters
	void setEmergency(bool tf)
	{
		this->emergency = tf;
	}

	void lowerTime()
	{
		this->minutes -= 1;
	}

	// Over all display function
	void display()
	{
		if (emergency)
		{
			cout << "\tEmergency for " << getName() << " for class " << getClass()
				<< ". Time left: " << getMin() << endl;
			lowerTime();
		}
		else
		{
			cout << "\tCurrently serving " << getName() << " for class " << getClass()
				<< ". Time left: " << getMin() << endl;
			lowerTime();
		}
	}
};

#endif // NOW_SERVING_H