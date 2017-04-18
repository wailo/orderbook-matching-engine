#include <iostream>

#include "matchingEngine.hpp"
#include "trader.hpp"
#include "orderBook.hpp"

using namespace market;

matchingEngine::matchingEngine()
    : m_orderManagement(m_marketData), 
      m_thread([&](){
          while ( m_live ) {
            if ( m_newOrder )
            {
              m_newOrder = false;
              // std::cout << "new order" << std::endl;
              m_orderManagement.matchOrders();}}})      
{}

matchingEngine::~matchingEngine()
{
  if (m_live)
  {
    close();
  }
}


bool matchingEngine::addOrder(const std::shared_ptr<orderDelegate>& p_trader, unsigned int p_contractID, int p_volume, double p_price, orderSide p_side )
{

  m_newOrder = m_orderManagement.addOrder(p_trader, p_contractID, p_volume, p_price, p_side );
  return m_newOrder;
}

std::shared_ptr<trader> matchingEngine::addTrader()
{
  auto _trader = std::make_shared<trader>(trader(*this));
  m_marketData.subscribe(_trader);
  return _trader;
}

orderManagement& matchingEngine::getOrderManagement()
{
  return m_orderManagement;
}

void matchingEngine::close()
{
  // while (!m_orderMatchingTasks.empty())
  // {
  //     m_orderMatchingTasks.back().wait();
  //     m_orderMatchingTasks.pop_back();
  // }
  m_live = false;
  m_thread.join();
  m_orderManagement.matchOrders();

}
