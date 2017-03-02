#ifndef ORDER_MANAGEMENT_H
#define ORDER_MANAGEMENT_H

#include <vector>
#include <unordered_map>
#include <future>

#include "order.hpp"
#include <boost/lockfree/spsc_queue.hpp>
namespace webbtraders
{

class marketData;
class orderDelegate;
class orderBook;
    
class orderManagement
{
 public:
  //! Default constructor

  //! Constructor
  orderManagement(marketData& p_delegate) noexcept;

  //! Send Order
  //! return true if order request succeed, false otherwise
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


  // for unit tests
  inline unsigned int totalTradedVolume() const
  {
    return m_totalTradedVolume;
  }
        
  inline unsigned int totalVolume() const
  {
    return m_totalVolume;
  }
        
 private:

  // std::vector<order> m_buyOrders;
  //  std::vector<order> m_sellOrders;
  // std::unorder_set<order> m_orderbook;
  unsigned int m_UUID{1};
  marketData& m_delegate;

  // <Order_Id, trader>;

  std::unordered_map<unsigned int, orderBook > m_orderBooks;

  // for unit tests
  unsigned int m_totalTradedVolume{0};
  unsigned int m_totalVolume{0};
  //LockFreeQueue<order> m_queue;
  boost::lockfree::spsc_queue<order, boost::lockfree::capacity<1024>> m_queue;
};
}  // webbtraders


#endif // ORDER_MANAGEMENT_H
