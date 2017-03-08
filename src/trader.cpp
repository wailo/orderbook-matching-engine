#include <iostream>

#include "trader.hpp"
#include "matchingEngine.hpp"
#include "orderBook.hpp"
#include "order.hpp"

using namespace market;


unsigned int trader::m_IDGenerator = 0;

trader::trader(matchingEngine& p_market) noexcept
    :m_ID(m_IDGenerator++),
     m_market(p_market)
{}

void trader::onOrderBook(const orderBook& p_orderBook )
{
  if (onOrderBookCallBack)
  {
    onOrderBookCallBack(p_orderBook);
  }
  
  /*
    const auto& buys  = p_orderBook.getBuyOrdersSorted();
    const auto& sells  = p_orderBook.getSellOrdersSorted();
    
    std::cout << "onOrderBook, Buys:"  << std::endl;
    for (const auto& it : buys)
    {
    std::cout << it << std::endl;
    }
    std::cout << "onOrderBook, Sells:"  << std::endl;
    for (const auto& it : sells)
    {
    std::cout << it << std::endl;
    }
  */
}

void trader::onPublicTrade(const tradeData& p_tradeData) 
{
  if (onPublicTradeCallBack)
  {
    onPublicTradeCallBack(p_tradeData);
  }
  
  // std::cout << "onPublicTrade: "  <<
  //     "ID:" << p_tradeData.m_ID << " " <<
  //     "State:"   << p_tradeData.orderExecutionStateToString() << " " <<
  //     "Active Volume:" << p_tradeData.m_activeVolume << std::endl; 
}

bool trader::sendOrder(unsigned int p_contractID, int p_volume, double p_price, orderSide p_side)
{
  return m_market.addOrder(std::make_shared<trader>(*this), p_contractID, p_volume, p_price, p_side);   
}


void trader::onOrderExecution(const tradeData& p_tradeData)
{
  if (onOrderExecutionCallBack)
  {
    onOrderExecutionCallBack(p_tradeData);
  }
  // std::cout << "onOrderExecution: "  <<
  //     "ID:" << p_tradeData.m_ID << " " <<
  //     "State:"   << p_tradeData.orderExecutionStateToString() << " " <<
  //     "Active Volume:" << p_tradeData.m_activeVolume << std::endl;
}


void trader::setOnOrderExecutionCallBack (std::function<void(const tradeData&)> p_func)
{
  onOrderExecutionCallBack = p_func;
}

void trader::setOnPublicTradeCallBack (std::function<void(const tradeData&)> p_func)
{
  onPublicTradeCallBack = p_func;
}

void trader::setOnOrderBookCallBack (std::function<void(const orderBook&)> p_func)
{
  onOrderBookCallBack = p_func;
}
