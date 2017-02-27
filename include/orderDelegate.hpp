#ifndef ORDERDELEGATE_H
#define ORDERDELEGATE_H

namespace webbtraders
{
    class order;
    
    class orderDelegate
    {
        public:
        virtual void onOrderExecution(const order& p_order) = 0;

        virtual ~orderDelegate() = default;
    };

}  // webbtraders

#endif /* ORDERDELEGATE_H */
