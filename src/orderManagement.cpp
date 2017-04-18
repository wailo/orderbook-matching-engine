#include <iostream>
#include <algorithm>
#include <functional> 
#include <unordered_set>

#include "orderManagement.hpp"
#include "trader.hpp"
#include "orderDelegate.hpp"
#include "marketData.hpp"
#include "orderBook.hpp"

using namespace market;

orderManagement::orderManagement(marketData& p_delegate) noexcept
    :m_delegate(p_delegate)
{
}

bool orderManagement::addOrder(std::shared_ptr<orderDelegate> p_trader, unsigned int p_contractID, int p_volume, double price, orderSide side )
{
  // Check if the order is valid
  if (p_volume < 1 )
  {
    return false;
  }


  // If queue is full, wait for an arbitrary time.
  uint64_t wait_time = 1000000; 
  uint64_t start = 0;
  while ( !m_queue.write_available() )
  {
    if (start++ > wait_time)
    {
      // std::cout << "failed to add order" << std::endl;
      return false;
    }
  }
  
  m_queue.push(order(p_contractID, m_orderID++, p_volume, price, side, p_trader));
  m_totalVolume += p_volume;

  return true;
}


bool orderManagement::matchOrders()
{

  // If there are no data, return
  if (!m_queue.read_available())
  {
    return false;
  }
  
  order _order;
  std::unordered_set<unsigned int> contractIDs;
  while (m_queue.pop(_order))
  {
    // Add order to the order book
    contractIDs.insert(_order.contractID());
    m_orderBooks[_order.contractID()].addOrder(_order);
  }

  for(auto& _contractID : contractIDs )
  {        

    auto orderBookItr = m_orderBooks.find(_contractID);
    if ( orderBookItr == m_orderBooks.end() )
    {
      // Integrity check: If no order book available with the given contract number
      // then there is something wrong here
      return false;
    } 
        
    auto& m_buyOrders = orderBookItr->second.m_buyOrders;
    auto& m_sellOrders = orderBookItr->second.m_sellOrders;
        
    // While there are BUY and SELL orders in the queue
    // And the highest price of buy order can be matched 
    while ((!m_buyOrders.empty()) && (!m_sellOrders.empty()) &&
           m_buyOrders.front().price() >= m_sellOrders.front().price())
    {

      auto& _buy_order = m_buyOrders.front();
      auto& _sell_order = m_sellOrders.front();
      
      // Calculate and update trade volumes
      auto trade_volume = std::min(_sell_order.volume(), _buy_order.volume());
      _sell_order.setVolume(_sell_order.volume() - trade_volume);
      _buy_order.setVolume(_buy_order.volume() - trade_volume);
      
      // Notify the order owners
      // Not sure which price should be published. So putting buy price for now.
      _sell_order.owner()->onOrderExecution({_contractID, _sell_order.ID(), trade_volume, _buy_order.price()});
      _buy_order.owner()->onOrderExecution({_contractID, _buy_order.ID(), trade_volume, _buy_order.price()});

      // Increment internal counter (for testing purposes)
      m_totalTradedVolume += trade_volume;

      // Publish public trades
      m_delegate.publishPublicTrade({_contractID, _buy_order.ID(), trade_volume, _buy_order.price()});

      // Remove filled orders
      if ( _buy_order.volume() == 0 )
      {
        std::pop_heap(m_buyOrders.begin(), m_buyOrders.end(), std::less<order>());
        m_buyOrders.pop_back();
      }

      if ( _sell_order.volume() == 0 )
      {
        std::pop_heap(m_sellOrders.begin(), m_sellOrders.end(), std::greater<order>());
        m_sellOrders.pop_back();
      }
    }

    // Publish order book
    m_delegate.publishOrderBook(orderBookItr->second);

  }

  return true;
}
