#ifndef ORDER_MANAGEMENT_H
#define ORDER_MANAGEMENT_H

#include <vector>
#include <unordered_map>
#include <future>

#include "order.hpp"
#include <boost/lockfree/spsc_queue.hpp>

namespace market
{

class marketData;
class orderDelegate;
class orderBook;
    
class orderManagement
{
 public:

  //! Constructor
  orderManagement(marketData& p_delegate) noexcept;

  //! Send Order,  return true if order request succeed, false otherwise
  bool addOrder(std::shared_ptr<orderDelegate> p_trader, unsigned int p_contractID, int volume, double price, orderSide side);

  //! Match Orders
  bool matchOrders();
    
  //! Copy constructor
  orderManagement(const orderManagement &other) = delete;

  //! Move constructor
  orderManagement(orderManagement &&other) = delete;

  //! Destructor
  ~orderManagement() = default;
        
  //! Copy assignment operator
  orderManagement& operator=(const orderManagement &other) = delete;

  //! Move assignment operator
  orderManagement& operator=(orderManagement &&other) = delete;


  //! For unit tests: total traded volume get functions
  inline unsigned int totalTradedVolume() const
  {
    return m_totalTradedVolume;
  }

  //! For unit tests: total received orders volume get functions
  inline unsigned int totalVolume() const
  {
    return m_totalVolume;
  }

  
 private:
  
  //! order unique ID
  unsigned int m_orderID{1};

  // Handle to Market Data API
  marketData& m_delegate;

  // Order Book list
  std::unordered_map<unsigned int, orderBook > m_orderBooks;

  //! For unit tests:  Accumulative count of traded volume
  unsigned int m_totalTradedVolume{0};

  //! For unit tests:  Accumulative count of received order volume
  unsigned int m_totalVolume{0};

  //! Single Producer Single Consumer orders storage
  boost::lockfree::spsc_queue<order, boost::lockfree::capacity<4096>> m_queue;

};

}  // market


#endif // ORDER_MANAGEMENT_H
