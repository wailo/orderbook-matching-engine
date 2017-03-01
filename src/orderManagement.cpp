#include <iostream>
#include <algorithm>
#include <functional> 

#include "orderManagement.hpp"
#include "trader.hpp"
#include "orderDelegate.hpp"
#include "marketData.hpp"


using namespace webbtraders;

orderManagement::orderManagement(marketData& p_delegate) noexcept
    :m_delegate(p_delegate)
{
}

orderManagement::~orderManagement() noexcept 
{
    // std::cout << "orderManagement destructor" <<std::endl;
}

unsigned int orderManagement::addOrder(std::shared_ptr<orderDelegate> p_trader_ID, int p_volume, double price, orderSide side )
{
    // Check if the order is valid
    //    
    if (p_volume < 1 )
    {
        return 0;
    }

    // waiting time-out 
    int counter = 0;
    while (m_order_changed)
    {
        if (counter++ > 1000 )
        {
            std::cout << "Queue is too busy, can't process orders" << std::endl;
            return 0;
        }
    }
    
    // Orders are stored in heap    
    if ( side == orderSide::BUY )
    {
        m_buyOrders.emplace_back(m_UUID, p_volume, price, side ); 
        std::push_heap(m_buyOrders.begin(), m_buyOrders.end(), std::less<order>());
    }
    else if ( side == orderSide::SELL )
    {
        m_sellOrders.emplace_back(m_UUID, p_volume, price, side); 
        std::push_heap(m_sellOrders.begin(), m_sellOrders.end(), std::greater<order>());
    }
    else
    {
        std::cout << "invalid order type" << std::endl;
        return 0;
    }

    m_traders[m_UUID] = p_trader_ID;
    // time_stamp?

    m_totalVolume += p_volume;
    
    m_order_changed = true;
    // m_orderMatchingTask  = std::async( [&](){ this->matchOrders();});
    matchOrders();
    return m_UUID++;
}


bool orderManagement::matchOrders()
{

    // no changes in orders
    if (!m_order_changed)
    {
        return false;
    }
    
    // While there are BUY and SELL orders in the queue
    while ( (!m_buyOrders.empty()) && (!m_sellOrders.empty()) )
    {

        // for ( auto b : m_buyOrders )
        // {
        //     std::cout << "BUY: " <<b.volume() << " " <<  b.price() << std::endl;
        // }
        // std::cout << std::endl;

        // for ( auto b : m_sellOrders )
        // {
        //     std::cout << "SELL: " <<b.volume() << " " <<  b.price() << std::endl;
        // }

        auto& _buy_order = m_buyOrders.front();
        auto& _sell_order = m_sellOrders.front();

        // If the if the highest price buy order  in the queue can't be matched 
        if ( _sell_order.price() > _buy_order.price() )
        {
            break;
        }
        
        auto trade_volume = std::min(_sell_order.volume(), _buy_order.volume());
        _sell_order.setVolume(_sell_order.volume() - trade_volume);
        _buy_order.setVolume(_buy_order.volume() - trade_volume);

        m_traders[_sell_order.ID()]->onOrderExecution({_sell_order.ID(), _sell_order.volume()});
        m_traders[_buy_order.ID()]->onOrderExecution({_buy_order.ID(), _buy_order.volume()});

        m_totalTradedVolume += trade_volume;
        m_delegate.publishPublicTrades();

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

    std::vector<order> _orderbook;
    _orderbook.reserve(m_sellOrders.size() + m_buyOrders.size() );
    _orderbook.insert(_orderbook.end(), m_sellOrders.begin(), m_sellOrders.end());
    _orderbook.insert(_orderbook.end(), m_buyOrders.begin(), m_buyOrders.end());
    m_delegate.publishOrderBook(_orderbook);
    m_order_changed = false; 
    return true;
}
