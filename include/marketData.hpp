#ifndef MARKETDATA_H
#define MARKETDATA_H

#include <unordered_set>

namespace market
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

  //! Add subscriber 
  void subscribe(std::shared_ptr<marketDataDelegate> p_subscriber);

  //! Publish public trade
  void publishPublicTrade(const tradeData& p_tradeData);

  //! Publish order book
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
  //! Subscriber list
  std::unordered_set< std::shared_ptr<marketDataDelegate> > m_traders;

};

}  // webbbraders

#endif // MARKETDATA_H
