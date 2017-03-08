#ifndef MARKET_DATA_DELEGATE_H
#define MARKET_DATA_DELEGATE_H


namespace market
{

class orderBook;
class tradeData;

class marketDataDelegate
{
 public:

  //! Delegate function. Called when order book is changed
  virtual void onOrderBook(const orderBook& p_orderBook) = 0;

  //! Delegate function. Called when public trade is exchanged
  virtual void onPublicTrade(const tradeData& p_tradeData) = 0;

  //! Destructor
  virtual ~marketDataDelegate() = default;
};
    
    
}  // market

#endif // MARKET_DATA_DELEGATE_H
