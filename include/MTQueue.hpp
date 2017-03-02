#ifndef MTQUEUE_H
#define MTQUEUE_H

#include <atomic>
#include "order.hpp"
namespace webbtraders
{

    template <typename T>
    class LockFreeQueue {
    private:
        struct Node
        {
            Node( T val ) : value(val), next(nullptr) { }
            T value;
            Node* next;
        };
        Node* first;             // for producer only
        std::atomic<Node*> divider, last;  // shared
        // const order _order;
        

    public:
        LockFreeQueue()
        //  _order( 0,0,0,0, orderSide::BUY,nullptr)
            {
                first = divider = last =
                    new Node( T() );           // add dummy separator
            }
        ~LockFreeQueue()
            {
                while( first != nullptr )
                {   // release the list
                    Node* tmp = first;
                    first = tmp->next;
                    delete tmp;
                }
            }

        void Produce( const T& t )
            {
                // std::cout << "produces successfully" << std::endl;
                (*last).next = new Node(t);    // add the new item
                last = (*last).next;      // publish it
                while( first != divider )
                { // trim unused nodes
                    Node* tmp = first;
                    first = first->next;
                    delete tmp;
                }
            }
        
        bool Consume( T& result )
            {
                if( divider != last )
                {         // if queue is nonempty
                    result = (*divider).next->value;  // C: copy it back
                    divider = (*divider).next;   // D: publish that we took it
                    //   std::cout << "consumed successfully" << std::endl;
                    return true;              // and report success
                }
                // std::cout << "consumed failed" << std::endl;

                return false;               // else report empty
            }
    };
}  // webbtraders



#endif /* MTQUEUE_H */
