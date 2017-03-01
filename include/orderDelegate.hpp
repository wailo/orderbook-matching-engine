#ifndef ORDERDELEGATE_H
#define ORDERDELEGATE_H

#include "TradeGlobals.hpp"

//chage onPublic order to pass two vectors
//add trader to order object
// implement MT properly
namespace webbtraders
{
    class order;
    
    class orderDelegate
    {
    public:
        virtual void onOrderExecution(const tradeData& p_orderExcution ) = 0;
        virtual ~orderDelegate() = default;
         
    };

}  // webbtraders

#endif /* ORDERDELEGATE_H */
