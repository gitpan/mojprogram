
#include <iostream.h>
#include "CGroup.h"
#include "ABook.h"


typedef IteratorCollection<ABItem*> Iterator;


ContactGroup* ContactGroup::create (AddressBook* ab, string name) {
  return new ContactGroup(ab,name);
}


void ContactGroup::read(istream& is) {
  is.ignore(1000,'{'); is.ignore(1000,'\n');
  if (is.eof()) return;

  // Read name:
  static const int MAXLEN=100;
  char buff[MAXLEN];
  string s;
  is.getline(buff,MAXLEN);
  s=buff;
  setName(s);

  // Read elements:
  if (myABook==0) return;
  myItems.clear();
  while (!is.eof()) {
    const char ch = is.peek();
    if (ch=='}') break;
    is.getline(buff,MAXLEN);
    s=buff;
    ABItem* c = myABook->getItem(s);
    if (c) addItem(c);
  }
  is.ignore(1000,'}');
}


void ContactGroup::write(ostream& os) const {
  os<< "{\n" << getName() << "\n";
  Iterator* it = myItems.createIterator();
  for (it->reset(); !it->isDone(); it->next()) {
    ABItem* item = *it->currentItem();
    os<< item->getName() << "\n";
  }
  os<< "}\n";
  delete it;
}


void ContactGroup::writeEmail(ostream& os) const {
  Iterator* it = myItems.createIterator();
  for (it->reset(); !it->isDone(); it->next()) {
    ABItem* item = *it->currentItem();
    item->writeEmail(os);
  }
  delete it;
}


ABItem* ContactGroup::getItem (const string name) const {
  Iterator* it = myItems.createIterator();
  ABItem* ret = 0;
  for (it->reset(); !it->isDone(); it->next()) {
    ABItem* item = *it->currentItem();
    if (item && item->getName()==name) { ret=item; break; }
  }
  delete it;
  return ret;
}


