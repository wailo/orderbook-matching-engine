#ifndef ORDERDELEGATE_H
#define ORDERDELEGATE_H

#include "TradeGlobals.hpp"

namespace market
{

class order;

class orderDelegate
{
 public:

  //! Delegate function. Called when execution is generated
  virtual void onOrderExecution(const tradeData& p_orderExcution ) = 0;

  //! Destructor
  virtual ~orderDelegate() = default;
         
};

}  // market

#endif /* ORDERDELEGATE_H */
