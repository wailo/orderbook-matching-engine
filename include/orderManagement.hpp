#ifndef ORDER_MANAGEMENT_H
#define ORDER_MANAGEMENT_H

#include <vector>
#include <unordered_map>
#include <thread>
#include "order.hpp"


namespace webbtraders
{

    class marketData;
    class orderDelegate;
    // class marketDataDelegate;
    
    class orderManagement
    {
    public:
        //! Default constructor
        orderManagement(marketData& p_delegate) noexcept;

        //! Send Order
        //! return true if order request succeed, false otherwise
        unsigned int createOrder(std::shared_ptr<orderDelegate> p_trader ,unsigned int volume, double price, orderSide side);

        //! Match Orders
        void matchOrders();
    
        //! Copy constructor
        orderManagement(const orderManagement &other) = delete;

        //! Move constructor
        orderManagement(orderManagement &&other) = delete;

        //! Destructor
        ~orderManagement() noexcept;
        
        //! Copy assignment operator
        orderManagement& operator=(const orderManagement &other) = delete;

        //! Move assignment operator
        orderManagement& operator=(orderManagement &&other) = delete;

    private:

        std::vector<order> m_buyOrders;
        std::vector<order> m_sellOrders;
        unsigned int m_UUID{1};
        marketData& m_delegate;

        // <Order_Id, trader>;
        std::unordered_map< int, std::shared_ptr<orderDelegate> > m_traders;

        std::atomic<bool> m_order_changed{false};
        std::thread m_orderMatchingThread;



    };
}  // webbtraders


#endif // ORDER_MANAGEMENT_H
