
#ifndef _CGroup
#define _CGroup

#include "Collection.h"
#include <string.h>
#include "ABItem.h"
class AddressBook;


class ContactGroup : public ABItem {
public:

	virtual ~ContactGroup () {}
	static ContactGroup* create (AddressBook*, string name);

	virtual string getName () const { return myName; }
	void setName ( string s) { myName = s; }

	virtual void read  (istream& is);
	virtual void write (ostream& os) const;
	virtual void writeEmail (ostream& os) const;

        void addItem (ABItem* i)         { myItems.add(i); }
        void removeItem (ABItem* i)      { myItems.remove(i); }
        Collection<ABItem*>* getItems () { return &myItems; }
        ABItem* getItem (string name) const;

protected:

	ContactGroup (AddressBook* ab, string name) : myABook(ab) { setName(name); }

private:

	string myName;

        Collection<ABItem*> myItems;
        AddressBook* myABook;

};


#endif

