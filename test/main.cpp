#include <iostream>
#include "LinkedList.h"

using namespace std;

struct Foo: public Linked<Foo>, public Linked<Foo,1>, public DblLinked<Foo>, public DblLinked<Foo,1>
{
public:
    Foo(const char *s) : s(s) {}
    const char * const s;
};

int main (int argc, char * const argv[]) {
    Foo a("a"), b("b"), c("c"), d("d");
    Linked<Foo>::List list1;
    Linked<Foo,1>::List list2;
    DblLinked<Foo>::List list3;
    DblLinked<Foo,1>::List list4;
    
    list1.addFront(&a).addFront(&b).addFront(&c).addFront(&d);
    list2.addFront(&a).addFront(&c).addFront(&b).addFront(&d);
    list3.addFront(&a).addBack(&b).addFront(&c).addBack(&d);
    list4.addFront(&a).addBack(&c).addFront(&b).addBack(&d);
    
    cout << "list1:";
    for (Linked<Foo>::List::Range r(list1); !r.empty(); r.popFront())
        cout << " " << r.front()->s;
    cout << endl;
    
    cout << "removing \"c\"" << endl;
    list1.remove(&c);
    
    cout << "removing list1:";
    while (Foo* item = list1.removeFront())
        cout << " " << item->s;
    cout << endl;
    
    cout << "list2:";
    for (Linked<Foo,1>::List::Range r(list2); !r.empty(); r.popFront())
        cout << " " << r.front()->s;
    cout << endl;
    
    cout << "removing \"c\"" << endl;
    list2.remove(&c);
    cout << "removing list2:";
    while (Foo* item = list2.removeFront())
        cout << " " << item->s;
    cout << endl;
    
    cout << "list3:";
    for (DblLinked<Foo>::List::Range r(list3); !r.empty(); r.popFront())
        cout << " " << r.front()->s;
    cout << endl;
    
    cout << "list3 backward:";
    for (DblLinked<Foo>::List::Range r(list3); !r.empty(); r.popBack())
        cout << " " << r.back()->s;
    cout << endl;
    
    cout << "removing \"c\"" << endl;
    list3.remove(&c);
    
    cout << "removing list3:";
    while (Foo* item = list3.removeFront())
        cout << " " << item->s;
    cout << endl;
    
    cout << "list4:";
    for (DblLinked<Foo,1>::List::Range r(list4); !r.empty(); r.popFront())
        cout << " " << r.front()->s;
    cout << endl;
    
    cout << "list4 backward:";
    for (DblLinked<Foo,1>::List::Range r(list4); !r.empty(); r.popBack())
        cout << " " << r.back()->s;
    cout << endl;
    
    cout << "removing \"c\"" << endl;
    list4.remove(&c);
    
    cout << "removing list4 backward:";
    while (Foo* item = list4.removeBack())
        cout << " " << item->s;
    cout << endl;
    
    return 0;
}
