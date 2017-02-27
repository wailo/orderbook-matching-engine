#include <memory>
#include <unordered_map>


#include "orderManagement.hpp"
#include "marketData.hpp"

namespace webbtraders
{
    class trader;    
    class market// : public orderDelegate
    {
    public:

        //! Default constructor
        market() noexcept;

        //! Destructor
        ~market() = default;

        //! Copy assignment operator
        market& operator=(const market &other) = delete;

        //! Move assignment operator
        market& operator=(market &&other) = delete;

        //! create and Add trader to this market
        std::shared_ptr<trader> addTrader();

        //! Add trader to this market
        // bool addTrader( const std::shared_ptr<trader>& p_trader );

        //! orderManagement getter function
        orderManagement& getOrderManagement();


        /*
          template<typename... Args>
          bool sendOrder(Args... args)
            {
                auto orderID = m_orderManagement.createOrder(std::forward<Args>(args)...);

                if ( orderID )
                {
                    // m_traders[orderID] = p_trader;

                    m_marketData;logOrder(
                        m_orderManagement.matchOrders(); 
                    return true;
                }

                else
                {
                    return false;
                }
                }*/
        // bool createOrder(unsigned int p_trader_ID ,unsigned int volume, double price, orderSide side);
    private:

        //! Copy constructor
        market(const market &other) = delete;

        //! Move constructor
        market(market &&other) = delete;

        // void onOrderExecution(const order& p_order) override;

        //! Order Management API
        orderManagement m_orderManagement;

        //! Market Data API
        marketData m_marketData;

        std::unordered_map< int, std::shared_ptr<marketDataDelegate> > m_traders;

        // std::unordered_set<unsigned int> m_traders;
    };
    
}  // webbtraders
