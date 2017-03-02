#ifndef MARKETDATA_H
#define MARKETDATA_H

#include <unordered_set>


/*
 * A market data API, used by a client (the unit test) to receive the order book as well as public trades
 (report of execution where client identification has been removed)
*/

namespace webbtraders
{

class tradeData;
class marketDataDelegate;
class tradeData;
class orderBook;
class marketData
{
 public:
  //! Default constructor
  marketData() = default;

  // void logOrder( unsgined int p_order_ID,  );
  void subscribe(std::shared_ptr<marketDataDelegate> p_subscriber);
  // virtual void onOrderExecution(const order& p_order) override;
  //virtual void onPublicTrade() override;
  //  virtual void onTrade() override;
  void publishPublicTrade(const tradeData& p_tradeData);
  void publishOrderBook(const orderBook& p_orderBook);
        
  //! Copy constructor
  marketData(const marketData &other) = delete;
        
  //! Move constructor
  marketData(marketData &&other) = delete;
        
  //! Destructor
  ~marketData() = default;
  
  //! Copy assignment operator
  marketData& operator=(const marketData &other) = delete;

  //! Move assignment operator
  marketData& operator=(marketData &&other) = delete;

 private:
        
  std::unordered_set< std::shared_ptr<marketDataDelegate> > m_traders;


};
}  // webbbraders

#endif // MARKETDATA_H
