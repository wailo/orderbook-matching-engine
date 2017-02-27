
#include <iostream>

#include "trader.hpp"
#include "market.hpp"

using namespace webbtraders;


unsigned int trader::m_counter = 0;

trader::trader(market& p_market) noexcept
    :m_ID(m_counter++),
     m_orderManagement(p_market.getOrderManagement())
{
}

void trader::onPublicTrade() 
{
    std::cout << "onPublicTrade, ID:" << m_ID << std::endl;
}

/*void trader::onTrade()
  {
  std::cout << "onTrade, ID:" << m_ID << std::endl;
  }*/

bool trader::sendOrder(unsigned int p_volume, double p_price, orderSide p_side )
{
    return m_orderManagement.createOrder(std::make_shared<trader>(*this), p_volume, p_price, p_side);   
}


void trader::onOrderExecution(const order& p_order)
{
    std::cout << "onOrderExecution" << std::endl;
}
