
#include <iostream.h>
#include "ABook.h"
#include "Contact.h"
#include "CGroup.h"


typedef IteratorCollection<ABItem*> Iterator;


AddressBook::~AddressBook () {
  Iterator* it = myItems.createIterator();
  for (it->reset(); !it->isDone(); it->next()) {
    ABItem* item = *it->currentItem();
    delete item;
  }
  delete it;
  myItems.clear();
}


void AddressBook::removeItem (ABItem* i) {
  Iterator* it = myItems.createIterator();
  for (it->reset(); !it->isDone(); it->next()) {
    ABItem* item = *it->currentItem();
    item->removeItem(i);
  }
  delete it;
  myItems.remove(i);
}


AddressBook* AddressBook::create(string name) {
  return new AddressBook(name);
}


void AddressBook::read(istream& is) {
  while (!is.eof()) {
    is.ignore(1000,'#');
    if (is.eof()) break;
    ABItem* c = 0;
    const int ch = is.peek();
    if (ch=='{')
      // ContactGroup
      c = ContactGroup::create(this);
    else
      // Contact
      c = Contact::create();
    if (c==0) break;
    is>> *c;
    addItem(c);
  }
}


void AddressBook::write(ostream& os) const {
  Iterator* it = myItems.createIterator();
  for (it->reset(); !it->isDone(); it->next()) {
    ABItem* item = *it->currentItem();
    os<< "#" << *item << "\n";
  }
  delete it;
}


ABItem* AddressBook::getItem (string name) const {
  Iterator* it = myItems.createIterator();
  ABItem* ret = 0;
  for (it->reset(); !it->isDone(); it->next()) {
    ABItem* item = *it->currentItem();
    if (item && item->getName()==name) { ret=item; break; }
  }
  delete it;
  return ret;
}


