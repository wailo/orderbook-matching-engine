#ifndef TRADER_H
#define TRADER_H

#include "marketDataDelegate.hpp"
#include "orderDelegate.hpp"


namespace market
{

class matchingEngine;
class orderBook;
enum class orderSide;

class trader :
      public std::enable_shared_from_this<trader>,
      public marketDataDelegate,
      public orderDelegate
{
 public:

  //! Default constructor
  trader(matchingEngine& p_market) noexcept;

  //! Send Order,  return true if order request succeed, false otherwise
  bool sendOrder(unsigned int p_contractID, int p_volume, double p_price, orderSide p_side);

  //! Destructor
  ~trader() = default;

  //! Set a function to be invoked when order execution update is received.
  void setOnOrderExecutionCallBack (std::function<void(const tradeData&)>);

  //! Set a function to be invoked when public trade update is received.
  void setOnPublicTradeCallBack (std::function<void(const tradeData&)>);

  //! Set a function to be invoked when order book update is received.
  void setOnOrderBookCallBack (std::function<void(const orderBook&)>);

 private:

  //! Trader unique ID
  unsigned int m_ID{0};

  //! Unique ID generate
  static unsigned int m_IDGenerator;

  //! handle to the
  matchingEngine& m_market;

  //! Function called when an order owned by this trader is sent
  virtual void onOrderExecution( const tradeData& p_orderExcution ) override;

  //! Function called when public trade is received
  virtual void onPublicTrade(const tradeData& p_tradeData) override;

  //! Function called when orderBook update is received
  virtual void onOrderBook( const orderBook& p_orderBook ) override;

  //! Function callback for order execution updates
  std::function<void(const tradeData&)> onOrderExecutionCallBack;

  //! Function callback for public trade updates
  std::function<void(const tradeData&)> onPublicTradeCallBack;

  //! Function callback for order book updates
  std::function<void(const orderBook&)> onOrderBookCallBack;

};

}  // market

#endif /* TRADER_H */
