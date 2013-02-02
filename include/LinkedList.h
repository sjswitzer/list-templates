/*
 * LinkedList.h
 *
 * Template mixins implementing intrusive lists.
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <assert.h>

/*
 * Singly-linked list.
 *
 * Inherit as a mixin in the class to be linked, as follows:
 *
 *    class MyClass: public Linked<MyClass>, public Linked<MyClass,1>
 *
 * A class can be in more that one list; you distinguish the lists using the optional second parameter.
 *
 * To declare a list instance, use the List member:
 *
 *    Linked<MyClass>::List aList;
 *    Linked<MyClass,1>::List anotherList;
 */
template <class C, int N=0>
class Linked
{
    Linked* m_next;
    
public:
    Linked() : m_next(0) {}
    
    class List
    {
        Linked* m_head;
        
    public:
        List() : m_head(0) {}
        class Range {
            Linked* m_item;
        public:
            Range(const List& list) : m_item(list.m_head) {}
            C* front() const { return static_cast<C*>(m_item); }
            bool empty() const { return m_item == 0; }
            void popFront() { m_item = m_item->m_next; }
        };
        
        List& addFront(C* item) {
            Linked *listItem = item;
            assert(listItem->m_next == 0);
            listItem->m_next = m_head;
            m_head = listItem;
            return *this;
        }
        
        C* removeFront() {
            if (m_head == 0)
                return 0;
            Linked *item = m_head;
            m_head = item->m_next;
            return static_cast<C*>(item);
        }
        
        void remove(C* item) {
            Linked* listItem = item;
            
            for (Linked** p = &m_head; *p; p = &((*p)->m_next)) {
                if (*p == listItem) {
                    *p = listItem->m_next;
                    listItem->m_next = 0;
                    return;
                }
            }
            assert(!"item not in list");
        }
    };
};

/*
 * Doubly-linked list.
 *
 * Inherit as a mixin in the class to be linked, as follows:
 *
 *    class MyClass: public DblLinked<MyClass>, public DblLinked<MyClass,1>
 *
 * A class can be in more that one list; you distinguish the lists using the optional second parameter.
 *
 * To declare a list instance, use the List member:
 *
 *    DblLinked<MyClass>::List aList;
 *    DblLinked<MyClass,1>::List anotherList;
 */
template <class C, int N=0>
class DblLinked
{
    DblLinked* m_next;
    DblLinked* m_prev;
    
public:
    DblLinked() : m_next(0), m_prev(0) {}
    
    class List
    {
        DblLinked* m_head;
        DblLinked* m_tail;
    public:
        List() : m_head(0), m_tail(0) {}

        class Range
        {
            DblLinked* m_front;
            DblLinked* m_back;
        public:
            Range(const List& list) : m_front(list.m_head), m_back(list.m_tail) {}
            bool empty() const { return m_front == 0; }
            C* front() const { return static_cast<C*>(m_front); }
            void popFront() { m_front = m_front->m_next; if (!m_front) m_back = 0; }
            C* back() const { return static_cast<C*>(m_back); }
            void popBack() { m_back = m_back->m_prev; if (!m_back) m_front = 0; }
        };
        
        List& addFront(C *item) {
            DblLinked *listItem = item;
            assert(listItem->m_next == 0 && listItem->m_prev == 0);
            listItem->m_next = m_head;
            if (m_head)
                m_head->m_prev = listItem;
            else
                m_tail = listItem;
            m_head = listItem;
            return *this;
        }
        
        C* removeFront() {
            if (m_head == 0)
                return 0;
            DblLinked *listItem = m_head;
            m_head = listItem->m_next;
            if (m_head)
                m_head->m_prev = 0;
            else 
                m_tail = 0;
            return static_cast<C*>(listItem);
        }
        
        List& addBack(C *item) {
            DblLinked *listItem = item;
            assert(listItem->m_next == 0 && listItem->m_prev == 0);
            listItem->m_prev = m_tail;
            if (m_tail)
                m_tail->m_next = listItem;
            else
                m_head = listItem;
            m_tail = listItem;
            return *this;
        }
        
        C* removeBack() {
            if (m_tail == 0)
                return 0;
            DblLinked *listItem = m_tail;
            m_tail = listItem->m_prev;
            if (m_tail)
                m_tail->m_next = 0;
            else 
                m_head = 0;
            return static_cast<C*>(listItem);
        }
        
        void remove(C *item) {
            DblLinked *listItem = item;
            assert((listItem->m_prev == 0) == (m_head == listItem));
            assert((listItem->m_next == 0) == (m_tail == listItem));
            if (listItem == m_head) {
                m_head = listItem->m_next;
                if (m_head)
                    m_head->m_prev = 0;
                else 
                    m_tail = 0;
            }
            else if (listItem == m_tail) {
                m_tail = listItem->m_prev;
                if (m_tail)
                    m_tail->m_next = 0;
                else 
                    m_head = 0;
            }
            else {
                listItem->m_next->m_prev = listItem->m_prev;
                listItem->m_prev->m_next = listItem->m_next;
            }
            listItem->m_next = listItem->m_prev = 0;
        }
    };
};

#endif


