#include <iostream.h>
#include "Contact.h"


Contact::Contact( string fn,  string ln,  string e,  string phNum) {
  setFirstName(fn); 
  setLastName(ln);  
  setEmail(e);
  setPhoneNum(phNum);
}


Contact* Contact::create( string fn, string ln, string em, string phn) {
  return new Contact(fn,ln,em,phn);
}


void Contact::read(istream& is) {
  static const int MAXLEN=100;
  char buff[MAXLEN];
  string s;
  is.getline(buff,MAXLEN);
  s=buff;
  setFirstName(s);
  is.getline(buff,MAXLEN);
  s=buff;
  setLastName(s);
  is.getline(buff,MAXLEN);
  s=buff;
  setEmail(s);
  is.getline(buff,MAXLEN);
  s=buff;
  setPhoneNum(s);
}


void Contact::write(ostream& os) const {
  os<<firstName<<'\n';
  os<<lastName<<'\n';
  os<<email<<'\n';
  os<<phoneNum<<'\n';
}

