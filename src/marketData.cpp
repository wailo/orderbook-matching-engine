#include <iostream>

#include "marketData.hpp"
#include "marketDataDelegate.hpp"
#include "order.hpp"


using namespace webbtraders;


void marketData::subscribe( std::shared_ptr<marketDataDelegate>& p_subscriber )
{
    
}

void marketData::onOrderExecution(const unsigned int p_trader_ID, const order& p_order)
{
    // this has to go through Market Data API
    m_traders[p_order.ID()]->onTrade();
    std::cout << "Order Executed" << std::endl;
}
