#ifndef ORDERDELEGATE_H
#define ORDERDELEGATE_H

#include "TradeGlobals.hpp"

namespace webbtraders
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

}  // webbtraders

#endif /* ORDERDELEGATE_H */
