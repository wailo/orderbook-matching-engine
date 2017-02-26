#ifndef MARKETDATA_H
#define MARKETDATA_H
#include <unordered_map>

#include "orderDelegate.hpp"
/*
 * A market data API, used by a client (the unit test) to receive the order book as well as public trades
 (report of execution where client identification has been removed)
*/
namespace webbtraders
{

    class marketDataDelegate;
    // enum class OrderRequestStatus
    class marketData
        : public orderDelegate
    {
    public:
        //! Default constructor
        marketData() = default;

        // void logOrder( unsgined int p_order_ID,  );
        void subscribe( std::shared_ptr<marketDataDelegate>& p_subscriber );
        virtual void onOrderExecution(const unsigned int p_trader_ID, const order& p_order) override;
        
        
        //! Copy constructor
        // marketData(const marketData &other);
        
        //! Move constructor
        // marketData(marketData &&other) noexcept;
        
        //! Destructor
        // virtual ~marketData() noexcept;

        //! Copy assignment operator
        // marketData& operator=(const marketData &other);

        //! Move assignment operator
        // marketData& operator=(marketData &&other) noexcept;

    private:
        
        std::unordered_map< int, std::shared_ptr<marketDataDelegate> > m_traders;


    };
}  // webbbraders

#endif // MARKETDATA_H
