#ifndef _COLLECTION
#define _COLLECTION


template <class T>
class Collection {
public:

  Collection ();
  Collection (const Collection<T>&);
 ~Collection ();

  Collection<T>& operator= (const Collection<T>&);

  void append (const T&);
  void insert (const T&, int at=0);
  void remove (const T&);
  void remove (int at=0);
  void clear  ();

  int      isEmpty  () const;
  int      isFull   () const;
  int      length   () const;
  const T& first    () const;
  const T& last     () const;
  const T& itemAt   (int at) const;
  T&       itemAt   (int at);
  int      location (const T&) const;
  void copy (const Collection<T>&);

private:

  friend class  IteratorCollection
  friend struct Element

  void remove (Element<T>*);

  Element<T>* head;
  int size;

};




 template <class T>
struct Element {
  T t;
  Element<T> *prev, *next;
  Element (const T&);
  Element (const T&, Element<T>* next);
  Element (const T&, Element<T>* prev, Element<T>* next);
};




template<class T>
Element<T>::Element (const T& e) : t(e), prev(0), next(0) {}


template<class T>
Element<T>::Element (const T& e, Element<T> *n)
    : t(e), prev(0), next(n) {
  if (n!=0) n->prev=this;
}


template<class T>
Element<T>::Element (const T& e, Element<T> *p, Element<T> *n)
    : t(e), prev(p), next(n) {
  if (n!=0) n->prev=this;
  if (p!=0) p->next=this;
}


template<class T>
void Collection<T>::remove (Element<T>* e) {
  if (e==0) return;
  if (e->next!=0) e->next->prev=e->prev;
  if (e->prev!=0) e->prev->next=e->next;
  else head=e->next;
  delete e;
  size--;
}



template<class T>
void Collection<T>::copy (const Collection<T>& r) {
  size=0;
  for (Element<T>* cur=r.head; cur!=0; cur=cur->next) append(cur->t);
}


template<class T>
void Collection<T>::clear () {
  for (Element<T> *cur=head, *temp=0; cur!=0; cur=temp) {
    temp=cur->next;
    delete cur;
  }
  head=0;
  size=0;
}


 template<class T>
int Collection<T>::isEmpty () const { return size==0; }


template<class T>
int Collection<T>::isFull () const { return 0; }



template<class T>
int Collection<T>::length () const { return size; }


template<class T>
const T& Collection<T>::first () const { return itemAt(0); }


template<class T>
const T& Collection<T>::last () const { return itemAt(length()-1); }


template<class T>
const T& Collection<T>::itemAt (int at) const {
  static T except;
  if (isEmpty()) return except;  // Exception!
  if (at>=length()) at=length()-1;
  if (at<0) at=0;
  int i=0;
  for (Element<T> *cur=head; i<at; cur=cur->next, i++);
  return cur->t;
}


template<class T>
T& Collection<T>::itemAt (int at) {
  static T except;
  if (isEmpty()) return except;  // Exception!
  if (at>=length()) at=length()-1;
  if (at<0) at=0;
  int i=0;
  for (Element<T> *cur=head; i<at; cur=cur->next, i++);
  return cur->t;
}


template<class T>
int Collection<T>::location (const T& e) const {
  int i=0;
  for (Element<T> *cur=head; cur!=0; cur=cur->next, i++)
    if (cur->t==e) return i;
  return -1;
}


template<class T>
void Collection<T>::append (const T& t) {
  if (head==0) head=new Element<T>(t);
  else {
    for (Element<T> *cur=head; cur->next!=0; cur=cur->next);
    new Element<T>(t,cur,0);
  }
  size++;
}


template<class T>
void Collection<T>::insert (const T& t, int at) {
  if ((at>size)||(at<0)) return;
  if (at==0) head=new Element<T>(t,head);
  else if (at==size) { append(t); return; }
  else {
    int i=0;
    for (Element<T> *cur=head; i<at; cur=cur->next, i++);
    new Element<T>(t,cur->prev,cur);
  }
  size++;
}


template<class T>
void Collection<T>::remove (int at) {
  if ((at>=size)||(at<0)) return;
  int i=0;
  for (Element<T> *cur=head; i<at; cur=cur->next, i++);
  remove(cur);
}


template<class T>
void Collection<T>::remove (const T& t) {
  remove(location(t));
}


template<class T>
Collection<T>::Collection () : size(0), head(0) {}


template<class T>
Collection<T>::Collection (const Collection<T>& r) : size(0), head(0) {
  copy(r);
}


template<class T>
Collection<T>& Collection<T>::operator= (const Collection<T>& r) {
  clear();
  copy(r);
  return *this;
}


template<class T>
Collection<T>::~Collection () { clear(); }




 /////////////////////////////////////////////////////////////////////
// class template IteratorCollection
/////////////////////////////////////////////////////////////////////

template <class T>
class IteratorCollection {
public:

  IteratorCollection (const Collection<T>*);
  IteratorCollection (const IteratorCollection<T>&);
 ~IteratorCollection ();

  IteratorCollection<T>& operator= (const IteratorCollection<T>&);
  int operator== (const IteratorCollection<T>&);
  int operator!= (const IteratorCollection<T>&);

  void reset();
  int  next ();

  int      isDone() const;
  const T* currentItem() const;

private:

  const Collection<T>* theSupplier;
  Element<T>* cur;

};



template <class T>
IteratorCollection<T>::IteratorCollection (const Collection<T>* ub)
  : theSupplier(ub), cur(theSupplier->head) {}


template <class T>
IteratorCollection<T>::IteratorCollection (const IteratorCollection<T>& r)
  : theSupplier(r.theSupplier), cur(r.cur) {}


template <class T>
IteratorCollection<T>& IteratorCollection<T>::operator= (const IteratorCollection<T>& r) {
  theSupplier=r.theSupplier;
  cur=r.cur;
  return *this;
}


template <class T>
IteratorCollection<T>::~IteratorCollection () {}


template <class T>
int IteratorCollection<T>::operator== (const IteratorCollection<T>& r) {
  return (theSupplier==r.theSupplier)&&(cur==r.cur);
}


template <class T>
int IteratorCollection<T>::operator!= (const IteratorCollection<T>& r) {
  return !(*this==r);
}


template <class T>
void IteratorCollection<T>::reset () {
  cur=theSupplier->head;
}


template <class T>
int IteratorCollection<T>::next () {
  if (cur!=0) cur=cur->next;
  return !isDone();
}


template <class T>
int IteratorCollection<T>::isDone () const {
  return (cur==0);
}


template <class T>
const T* IteratorCollection<T>::currentItem () const {
  if (isDone()) return 0;
  else return &(cur->t);
}


#endif
