#ifndef _Contact
#define _Contact


#include <string.h>
#include "ABItem.h"
class ostream;
class istream;


class Contact : public ABItem {
public:

	virtual ~Contact() {}

	static Contact* create (string firstName, string lastName, string email,string phoneNum);

        virtual string getName     () const { return firstName; }

	const string getFirstName () const { return firstName; }
	const string getLastName  () const { return lastName; }
	const string getEmail     () const { return email; }
	const string getPhoneNum  () const { return phoneNum; }

	void setFirstName (string s) { firstName = s; }
	void setLastName  (string s) { lastName = s; }
	void setEmail     (string s) { email = s; }
	void setPhoneNum  (string s) { phoneNum = s; }

	virtual void read  (istream& is);
	virtual void write (ostream& os) const;
        virtual void writeEmail (ostream& os) const { os<<email<<"; "; }

protected:

	Contact (string fn, string ln, string em, string phn);

private:

	string firstName;
	string lastName;
	string email;
	string phoneNum;

};


#endif

