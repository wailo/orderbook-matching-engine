#ifndef TRADER_H
#define TRADER_H

#include "marketDataDelegate.hpp"
#include "orderDelegate.hpp"
#include "order.hpp"


namespace webbtraders
{
class matchingEngine;
// class orderManagement;
class orderBook;

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

 private:

  // Trader unique ID
  unsigned int m_ID{0};

  // Unique ID generate
  static unsigned int m_IDGenerator;

  // handle to the
  matchingEngine& m_market;


  virtual void onOrderExecution( const tradeData& p_orderExcution ) override;
  virtual void onPublicTrade(const tradeData& p_tradeData) override;
  virtual void onOrderBook( const orderBook& p_orderBook ) override;

};

}  // webbtraders

#endif /* TRADER_H */
