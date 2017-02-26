
#include <iostream>

#include "trader.hpp"
#include "market.hpp"

using namespace webbtraders;


unsigned int trader::m_counter = 0;

trader::trader(market& p_market) noexcept
    :m_ID(m_counter++),
     m_makret(p_market)
{
}

void trader::onPublicTrade() 
{
    std::cout << "onPublicTrade, ID:" << m_ID << std::endl;
}

void trader::onTrade()
{
    std::cout << "onTrade, ID:" << m_ID << std::endl;
}

bool trader::sendOrder(unsigned int p_volume, double p_price, orderSide p_side )
{
    return m_makret.sendOrder(m_ID, p_volume, p_price, p_side);   
}
