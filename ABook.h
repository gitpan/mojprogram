
#ifndef  _ABook
#define  _ABook

#include "Collection.h"
#include <string>
#include "ABItem.h"
class ostream;
class istream;


class AddressBook {
public:

	virtual ~AddressBook();
	static AddressBook* create (string name);

	const string getName () const { return myName; }
	void setName (string s) { myName = s; }

	virtual void read  (istream& is);
	virtual void write (ostream& os) const;

        void addItem (ABItem* i)         { myItems.add(i); }
        void removeItem (ABItem* i);
        Collection<ABItem*>* getItems () { return &myItems; }
        ABItem* getItem (string name) const;

protected:

	AddressBook (string name) { setName(name); }

private:

	string myName;

        Collection<ABItem*> myItems;

};


#endif

