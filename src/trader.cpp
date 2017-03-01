
#include <iostream>

#include "trader.hpp"
#include "market.hpp"
#include "orderBook.hpp"

using namespace webbtraders;


unsigned int trader::m_counter = 0;

trader::trader(market& p_market) noexcept
    :m_ID(m_counter++),
     m_orderManagement(p_market.getOrderManagement())
{
}

void trader::onOrderBook(const orderBook& p_orderBook )
{
    
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
    std::cout << "onPublicTrade: "  <<
        "ID:" << p_tradeData.m_ID << " " <<
        "State:"   << p_tradeData.orderExecutionStateToString() << " " <<
        "Active Volume:" << p_tradeData.m_activeVolume << std::endl; 

    // std::cout << "onPublicTrade, ID:" << m_ID << std::endl;
}

/*
  void trader::onTrade()
  {
  std::cout << "onTrade, ID:" << m_ID << std::endl;
  }
*/

bool trader::sendOrder(unsigned int p_contractID, int p_volume, double p_price, orderSide p_side)
{
    return m_orderManagement.addOrder(std::make_shared<trader>(*this), p_contractID, p_volume, p_price, p_side);   
}


void trader::onOrderExecution(const tradeData& p_tradeData)
{
    std::cout << "onOrderExecution: "  <<
        "ID:" << p_tradeData.m_ID << " " <<
        "State:"   << p_tradeData.orderExecutionStateToString() << " " <<
        "Active Volume:" << p_tradeData.m_activeVolume << std::endl;
}
