#ifndef TRADER_H
#define TRADER_H

#include "marketDataDelegate.hpp"
#include "orderDelegate.hpp"


namespace webbtraders
{
class matchingEngine;
// class orderManagement;
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
        
  //   template<typename... Args>
  // bool sendOrder(Args... args);
  bool sendOrder(unsigned int p_contractID, int p_volume, double p_price, orderSide p_side);

  //! Copy constructorx
  //  trader(const trader &other);

  //! Move constructor
  // trader(trader &&other);

  //! Destructor
  ~trader() = default;

  //! Copy assignment operator
  // trader& operator=(const trader &other);

  //! Move assignment operator
  // trader& operator=(trader &&other) noexcept;

  void setOnOrderExecutionCallBack (std::function<void(const tradeData&)>);
  void setOnPublicTradeCallBack (std::function<void(const tradeData&)>);
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


  std::function<void(const tradeData&)> onOrderExecutionCallBack;
  std::function<void(const tradeData&)> onPublicTradeCallBack;
  std::function<void(const orderBook&)> onOrderBookCallBack;

};

}  // webbtraders

#endif /* TRADER_H */
