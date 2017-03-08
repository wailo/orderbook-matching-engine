#include <iostream>

#include "marketData.hpp"
#include "marketDataDelegate.hpp"

using namespace market;

void marketData::subscribe(std::shared_ptr<marketDataDelegate> p_subscriber)
{    m_traders.insert(p_subscriber);
}


void marketData::publishPublicTrade(const tradeData& p_tradeData)
{
  for ( auto& tr : m_traders )
  {
    tr->onPublicTrade(p_tradeData);
  }  
}


void marketData::publishOrderBook(const orderBook& p_orderBook)
{
  for ( auto& tr : m_traders )
  {
    tr->onOrderBook(p_orderBook);
  }  
}
