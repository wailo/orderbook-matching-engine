#include <iostream>
#include <algorithm>
#include <functional> 

#include "orderManagement.hpp"
#include "trader.hpp"
#include "orderDelegate.hpp"

using namespace webbtraders;

orderManagement::orderManagement(orderDelegate& p_delegate) noexcept
    :m_delegate(p_delegate)
{
}

unsigned int orderManagement::createOrder(unsigned int p_trader_ID, unsigned int volume, double price, orderSide side )
{
    // Check if the order is valid
    // 
    if (!price)
    {
        std::cout << "invalid order" << std::endl;
        return 0;
    }
    
    // Order are stored in heap    
    if ( side == orderSide::BUY )
    {
        m_buyOrders.emplace_back(m_UUID, volume, price, side ); 
        std::push_heap(m_buyOrders.begin(), m_buyOrders.end(), std::less<order>());
    }
    if ( side == orderSide::SELL )
    {
        m_sellOrders.emplace_back(m_UUID, volume, price, side); 
        std::push_heap(m_sellOrders.begin(), m_sellOrders.end(), std::greater<order>());
    }

    // time_stamp? 
    return m_UUID++;
}


void orderManagement::matchOrders()
{
    std::cout << "test" << std::endl;

    // While there are BUY and SELL orders in the queue
    while ( (!m_buyOrders.empty()) && (!m_sellOrders.empty()) )
    {

        for ( auto b : m_buyOrders )
        {
            std::cout << "BUY: " <<b.volume() << " " <<  b.price() << std::endl;
        }
        std::cout << std::endl;

        for ( auto b : m_sellOrders )
        {
            std::cout << "SELL: " <<b.volume() << " " <<  b.price() << std::endl;
        }

        auto& _buy_order = m_buyOrders.front();
        auto& _sell_order = m_sellOrders.front();

        // If the if the first buy order (with the highest price) in the queue can't be matched 
        if ( _sell_order.price() > _buy_order.price() )
        {
            break;
        }
        
        auto trade_volume = std::min(_sell_order.volume(), _buy_order.volume() );
        _sell_order.setVolume(_sell_order.volume() - trade_volume);
        _buy_order.setVolume(_buy_order.volume() - trade_volume);
        
        m_delegate.onOrderExecution(_sell_order);
        m_delegate.onOrderExecution(_buy_order);

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

    // send order book
}
