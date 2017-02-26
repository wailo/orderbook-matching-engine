#ifndef ORDERDELEGATE_H
#define ORDERDELEGATE_H

namespace webbtraders
{
    class order;
    
    class orderDelegate
    {
        public:
        virtual void onOrderExecution(const unsigned int p_trader_ID, const order& p_order) = 0;
    };

}  // webbtraders

#endif /* ORDERDELEGATE_H */
