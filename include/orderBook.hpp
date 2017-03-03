#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <vector>
#include <algorithm>
#include "order.hpp"

namespace webbtraders
{

class order;
    
class orderBook
{
 public:

  friend class orderManagement;

  //! Default constructor
  orderBook() = default;

  //! Default constructor
  // explicit orderBook(unsigned int p_contract);

  //! Copy constructor
  orderBook(const orderBook &other) = default;
  
  bool addOrder( order p_order );
  
  inline const std::vector<order>& getBuyOrders() const
  {
    return m_buyOrders;
  }
        
  inline const std::vector<order> getSellOrders() const
  {
    return m_sellOrders;
  }

  inline std::vector<order> getBuyOrdersSorted() const
  {
    auto sorted = m_buyOrders;
    std::sort_heap(sorted.begin(), sorted.end(), std::less<order>() );
    return sorted;
  }
         
  inline std::vector<order> getSellOrdersSorted() const
  {
    auto sorted = m_sellOrders;
    std::sort_heap(sorted.begin(), sorted.end(), std::greater<order>() );
    return sorted;
  }

  //! Move constructor
  // orderBook(orderBook &&other) noexcept;

  //! Destructor
  // ~orderBook() noexcept;

  //! Copy assignment operator
  // orderBook& operator=(const orderBook &other);

  //! Move assignment operator
  // orderBook& operator=(orderBook &&other) noexcept;

 private:
  std::vector<order> m_buyOrders;
  std::vector<order> m_sellOrders;

};

}  // webbtraders

#endif /* ORDERBOOK_H */
