
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

void trader::onOrderBook( const std::vector<order>& p_orderBook )
{

    // std::cout << "onOrderBook, ID:" << m_ID << std::endl;
    // for ( const auto& it : p_orderBook )
    // {
    //     std::cout << it << std::endl;
    // }

}
void trader::onPublicTrade() 
{
    // std::cout << "onPublicTrade, ID:" << m_ID << std::endl;
}

/*
  void trader::onTrade()
  {
  std::cout << "onTrade, ID:" << m_ID << std::endl;
  }
*/

bool trader::sendOrder( int p_volume, double p_price, orderSide p_side )
{
    return m_orderManagement.addOrder(std::make_shared<trader>(*this), p_volume, p_price, p_side);   
}


void trader::onOrderExecution(const orderExecution& p_orderExecution)
{
    std::cout << "onOrderExecution: "  <<
        "ID:" << p_orderExecution.m_ID << " " <<
        "State:"   << p_orderExecution.orderExecutionStateToString() << " " <<
        "Active Volume:" << p_orderExecution.m_activeVolume << std::endl;
}
