
#include <iostream.h>
#include <fstream.h>
#include "ABook.h"
#include "Contact.h"
#include "CGroup.h"


class UserInterface {
public:

  static UserInterface* Instance ();
  ~UserInterface () { delete myABook; }

  void run ();

  enum Status { ERR, OK, RET };

protected:

  UserInterface () : myABook(AddressBook::create()), myIs(cin), myOs(cout) {}


  Status mainMenu ();

  // Options of the main menu:
  Status optEnterContact ();
  Status optEnterCGroup  ();
  Status optPrintEntries ();
  Status optSearchEntry  ();
  Status optRemoveEntry  ();
  Status optPrintEmails  ();
  Status optLoad         ();
  Status optSave         ();

  // Helper functions:
  void writeMainMenu ();
  ABItem* inputEntry ();
  string  inputFileName ();

private:

  istream& myIs;
  ostream& myOs;

  AddressBook* myABook;

};




UserInterface* UserInterface::Instance () {
  static UserInterface instance;
  return &instance;
}


void UserInterface::run () {
  Status ret = OK;
  while (ret!=RET) {
    ret = mainMenu();
    if (ret==ERR) myOs<< "\nError!\n\n";
  }
}


void UserInterface::writeMainMenu () {
  myOs<< "\n\nAddress Book Example\n\n";
  myOs<< "Main menu:\n\n";
  myOs<< "[1] Exit\n";
  myOs<< "[2] Print Entries\n";
  myOs<< "[3] Search Entry\n";
  myOs<< "[4] Remove Entry\n";
  myOs<< "[5] Add Contact\n";
  myOs<< "[6] Add Contact Group\n";
  myOs<< "[7] Print Email(s)\n";
  myOs<< "[8] Save address book to a file\n";
  myOs<< "[9] Load address book from a file\n";
  myOs<< "\nSelect an option 1-9: ";
}


UserInterface::Status UserInterface::mainMenu () {
  int opt = 0;
  do {
    writeMainMenu();
    myIs>>opt;
    myIs.ignore(1000,'\n'); // Clear the '\n' character from cin
  } while (opt<1 || opt>9);

  switch (opt) {
    case 1: return RET;
    case 2: return optPrintEntries();
    case 3: return optSearchEntry();
    case 4: return optRemoveEntry();
    case 5: return optEnterContact();
    case 6: return optEnterCGroup();
    case 7: return optPrintEmails();
    case 8: return optSave();
    case 9: return optLoad();
    default: return ERR;
  }
}


UserInterface::Status UserInterface::optEnterContact () {
  myOs<< "Option Enter Contact:\n";

  Contact* newCont = Contact::create();
  if (newCont==0 || myABook==0) return ERR;
  myABook->addItem(newCont);

  myOs<< "Enter Contact data in the following format:\n  firstName\n  lastName\n  email\n  phoneNumber\n>\n";
  myIs>> *newCont;
  return OK;
}


UserInterface::Status UserInterface::optEnterCGroup () {
  myOs<< "Option Enter Contact Group:\n";

  if (myABook==0) return ERR;
  ContactGroup* newCont = ContactGroup::create(myABook);
  if (newCont==0) return ERR;
  myABook->addItem(newCont);

  myOs<< "Enter Contact Group data in the following format:";
  myOs<< "\n  {\n  groupName\n  elementName\n  elementName\n  ...\n  }\n>\n";
  myIs>> *newCont;
  return OK;
}


UserInterface::Status UserInterface::optPrintEntries () {
  myOs<< "Option Print Entries:\n";

  if (myABook==0) return ERR;

  myABook->write(myOs);
  return OK;
}


ABItem* UserInterface::inputEntry () {
  myOs<< "Enter entry name: ";
  static const int MAXLEN=100;
  char buff[MAXLEN];
  myIs.getline(buff,MAXLEN);
  string name=buff;

  if (myABook==0) return 0;
  ABItem* item = myABook->getItem(name);
  if (item==0) myOs<< "Entry \"" << name << "\" not found.\n";
  return item;
}


UserInterface::Status UserInterface::optSearchEntry () {
  myOs<< "Option Search Entry:\n";
  ABItem* item = inputEntry();
  if (item!=0) myOs<< *item;
  return OK;
}


UserInterface::Status UserInterface::optRemoveEntry () {
  myOs<< "Option Remove Entry:\n";
  ABItem* item = inputEntry();
  if (item && myABook) myABook->removeItem(item);
  return OK;
}


UserInterface::Status UserInterface::optPrintEmails () {
  myOs<< "Option Print Email(s):\n";
  ABItem* item = inputEntry();
  if (item!=0) item->writeEmail(myOs);
  myOs<<"\n";
  return OK;
}


string UserInterface::inputFileName () {
  myOs<< "Enter filename: ";
  static const int MAXLEN=100;
  char buff[MAXLEN];
  myIs.getline(buff,MAXLEN);
  return buff;
}


UserInterface::Status UserInterface::optSave () {
  myOs<< "Option Save current address book to a file:\n";
  string fname = inputFileName();
  ofstream file(fname);
  if (file.bad()) return ERR;
  if (myABook) myABook->write(file);
  if (file.bad()) return ERR;
  return OK;
}


UserInterface::Status UserInterface::optLoad () {
  myOs<< "Option Load current address book from a file:\n";
  string fname = inputFileName();
  ifstream file(fname);
  if (file.bad()) return ERR;
  delete myABook;
  myABook = AddressBook::create();
  if (myABook==0) return ERR;
  myABook->read(file);
  if (file.bad()) return ERR;
  return OK;
}




void main () {
  UserInterface::Instance()->run();
}

