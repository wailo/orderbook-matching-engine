#include "orderBook.hpp"

using namespace webbtraders;

bool orderBook::addOrder( order p_order )
{
    
  // Orders are stored in heap    
  if ( p_order.side() == orderSide::BUY )
  {
    m_buyOrders.push_back(p_order); 
    std::push_heap(m_buyOrders.begin(), m_buyOrders.end(), std::less<order>());
  }
  else if ( p_order.side() == orderSide::SELL )
  {
    m_sellOrders.push_back(p_order); 
    std::push_heap(m_sellOrders.begin(), m_sellOrders.end(), std::greater<order>());
  }
  else
  {
    std::cout << "invalid order type" << std::endl;
    return 0;
  }
    
  return true;
}
