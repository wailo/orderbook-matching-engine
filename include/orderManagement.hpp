#ifndef ORDER_MANAGEMENT_H
#define ORDER_MANAGEMENT_H

#include <vector>

#include "order.hpp"


namespace webbtraders
{

    class orderDelegate; 
    // class trader;
    
    class orderManagement
    {
    public:
        //! Default constructor
        orderManagement(orderDelegate& p_delegate) noexcept;

        //! Send Order
        //! return true if order request succeed, false otherwise
        unsigned int createOrder(unsigned int p_trader_ID ,unsigned int volume, double price, orderSide side);

        //! Match Orders
        void matchOrders();
    
        //! Copy constructor
        orderManagement(const orderManagement &other) = delete;

        //! Move constructor
        orderManagement(orderManagement &&other) = delete;

        //! Destructor
        ~orderManagement() = default;
        
        //! Copy assignment operator
        orderManagement& operator=(const orderManagement &other) = delete;

        //! Move assignment operator
        orderManagement& operator=(orderManagement &&other) = delete;

    private:

        std::vector<order> m_buyOrders;
        std::vector<order> m_sellOrders;
        unsigned int m_UUID{1};
        orderDelegate& m_delegate;

    };
}  // webbtraders


#endif // ORDER_MANAGEMENT_H
