
#ifndef _ABItem
#define _ABItem

#include <string>
class ostream;
class istream;
class ABItem;

istream& operator>> (istream&, ABItem&);
ostream& operator<< (ostream&, const ABItem&);


class ABItem {
public:

	virtual ~ABItem () {}

	virtual string getName () const  = 0;

	virtual void read  (istream& is) = 0;
	virtual void write (ostream& os) const = 0;
        virtual void writeEmail (ostream& os) const = 0;

        virtual void removeItem (ABItem*) {}

protected:

        ABItem () {}

};


inline istream& operator>> (istream& is, ABItem& c) {
  c.read(is);
  return is;
}


inline ostream& operator<< (ostream& os, const ABItem& c) {
  c.write(os);
  return os;
}


#endif

