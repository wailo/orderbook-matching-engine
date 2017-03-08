#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <vector>
#include <algorithm>
#include "order.hpp"

namespace market
{

class order;
    
class orderBook
{
 public:

  friend class orderManagement;

  //! Default constructor
  orderBook() = default;

  //! Destructor
  ~orderBook() = default;

  //! Copy constructor
  orderBook(const orderBook &other) = default;

  //! Move copy constructor
  orderBook(orderBook &&other) = default;

  //! Copy assignment operator
  orderBook& operator=(const orderBook &other) = default;

  //! Move assignment operator
  orderBook& operator=(orderBook &&other) = default;

  //! Add order
  bool addOrder( order p_order );

  //! Get list of buy orders
  inline const std::vector<order>& getBuyOrders() const
  {
    return m_buyOrders;
  }

  //! Get list of sell orders
  inline const std::vector<order> getSellOrders() const
  {
    return m_sellOrders;
  }

  //! Get sorted list of buy orders
  inline std::vector<order> getBuyOrdersSorted() const
  {
    auto sorted = m_buyOrders;
    std::sort_heap(sorted.begin(), sorted.end(), std::less<order>() );
    return sorted;
  }

  //! Get sorted list of sell orders
  inline std::vector<order> getSellOrdersSorted() const
  {
    auto sorted = m_sellOrders;
    std::sort_heap(sorted.begin(), sorted.end(), std::greater<order>() );
    return sorted;
  }


 private:

  //! Buys orders list in heap data structure
  std::vector<order> m_buyOrders;

  //! Buys orders list in heap data structure
  std::vector<order> m_sellOrders;

};

}  // market

#endif /* ORDERBOOK_H */
