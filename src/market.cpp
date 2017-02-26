#include <iostream>

#include "market.hpp"
#include "trader.hpp"
using namespace webbtraders;


market::market() noexcept
    : m_orderManagement(m_marketData)
{
}


bool market::createOrder(unsigned int p_trader_ID ,unsigned int p_volume, double p_price, orderSide p_side)
{
    auto orderID = m_orderManagement.createOrder(p_trader_ID, p_volume, p_price, p_side );

    if ( orderID )
    {
        // m_traders[orderID] = p_trader;
        // m_marketData.logOrder(m_traders[orderID], );
        m_orderManagement.matchOrders(); 
        return true;
    }

    else
    {
        return false;
    }
}

std::shared_ptr<trader> market::addTrader()
{
    auto _trader = std::make_shared<trader>(trader(*this));

    
    // m_traders[_trader->m_ID] = _trader;
    return _trader;
}

orderManagement& market::getOrderManagement()
{
    return m_orderManagement;
}

