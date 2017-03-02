#include <iostream>
#include <algorithm>
#include <functional> 
#include <unordered_set>

#include "orderManagement.hpp"
#include "trader.hpp"
#include "orderDelegate.hpp"
#include "marketData.hpp"
#include "orderBook.hpp"

using namespace webbtraders;


orderManagement::orderManagement(marketData& p_delegate) noexcept
    :m_delegate(p_delegate)
{
}

// orderManagement::~orderManagement() noexcept 
// {
//     std::cout << "orderManagement destructor" <<std::endl;
// }

unsigned int orderManagement::addOrder(std::shared_ptr<orderDelegate> p_trader, unsigned int p_contractID, int p_volume, double price, orderSide side )
{
    // Check if the order is valid
    if (p_volume < 1 )
    {
        return 0;
    }

    // std::cout << " order added " << std::endl;
    const order _order(p_contractID, m_UUID, p_volume, price, side, p_trader);
    m_queue.Produce(_order);
    m_totalVolume += p_volume;

    //  matchOrders(p_contractID);
    
    //     m_orderMatchingTask  = std::async( [&](){ return this->matchOrders(0);});
    
    return m_UUID++;
}


bool orderManagement::matchOrders(unsigned int _p_contractID)
{
    order _order;
    bool new_orders_flag{false};
    std::unordered_set<unsigned int> contractIDs;
    while (m_queue.Consume(_order))
    {
        // Add order to the order book
        contractIDs.insert(_order.contractID());
        m_orderBooks[_order.contractID()].addOrder(_order);
        new_orders_flag = true;
    }

    if (!new_orders_flag)
    {
        return false;
    }


    for(auto& p_contractID : contractIDs )
    {
        // std::cout << "Matching orders: " << p_contractID <<  std::endl;
        
        // If no order book available with the given contract number
        auto orderBookItr = m_orderBooks.find(p_contractID);
        if ( orderBookItr == m_orderBooks.end() )
        {
            return false;
        } 
        
        auto& m_buyOrders = orderBookItr->second.m_buyOrders;
        auto& m_sellOrders = orderBookItr->second.m_sellOrders;
        
        // While there are BUY and SELL orders in the queue
        while ( (!m_buyOrders.empty()) && (!m_sellOrders.empty()) )
        {
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

            _sell_order.owner()->onOrderExecution({_sell_order.ID(), _sell_order.volume()});
            _buy_order.owner()->onOrderExecution({_buy_order.ID(), _buy_order.volume()});

            m_totalTradedVolume += trade_volume;
            //  m_delegate.publishPublicTrade({_buy_order.ID(), _buy_order.volume()});

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

        m_delegate.publishOrderBook(orderBookItr->second);

    }

    return true;
}
