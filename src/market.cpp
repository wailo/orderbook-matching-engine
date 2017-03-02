#include <iostream>

#include "market.hpp"
#include "trader.hpp"
#include "orderBook.hpp"

using namespace webbtraders;

market::market() noexcept
    : m_orderManagement(m_marketData)
{}

market::~market()
{
     waitForAllExecutions();
}


bool market::addOrder(const std::shared_ptr<orderDelegate>& p_trader, unsigned int p_contractID, int p_volume, double p_price, orderSide p_side )
{
    
    auto res = m_orderManagement.addOrder(p_trader, p_contractID, p_volume, p_price, p_side );

    if ( res )
    {
        //   std::cout << "market added order" << std::endl;

        m_orderMatchingTasks.emplace_back(std::async(std::launch::async, [&](){ return m_orderManagement.matchOrders(0);}) );
    }

    return res;
}

std::shared_ptr<trader> market::addTrader()
{
    auto _trader = std::make_shared<trader>(trader(*this));
    m_marketData.subscribe(_trader);
    return _trader;
}

orderManagement& market::getOrderManagement()
{
    return m_orderManagement;
}

void market::waitForAllExecutions()
{
    while (!m_orderMatchingTasks.empty())
    {
        m_orderMatchingTasks.back().wait();
        m_orderMatchingTasks.pop_back();
    }
    
    // m_orderMatchingTask.get();
}
