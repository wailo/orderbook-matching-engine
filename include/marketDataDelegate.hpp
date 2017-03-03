#ifndef MARKET_DATA_DELEGATE_H
#define MARKET_DATA_DELEGATE_H


namespace webbtraders
{

class orderBook;
class tradeData;

class marketDataDelegate
{
 public:
        
  virtual void onOrderBook(const orderBook& p_orderBook) = 0;
  virtual void onPublicTrade(const tradeData& p_tradeData) = 0;
  // virtual void onTrade() = 0;
  virtual ~marketDataDelegate() = default;
};
    
    
}  // webbtraders

#endif // MARKET_DATA_DELEGATE_H
