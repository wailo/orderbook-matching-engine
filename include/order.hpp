#ifndef ORDER_H
#define ORDER_H

#include <iostream>

namespace market
{

//! orderSide BUY/SELL
enum class orderSide {BUY, SELL};

// Forward Declarations
class orderDelegate;

class order
{
 public:

  //! Default constructor
  order() = default;

  //! Constructor
  order(unsigned int p_contractID, unsigned int p_ID, int p_volume, double p_price, orderSide p_side, const std::shared_ptr<orderDelegate>& p_owner) noexcept;

  //! Destructor
  ~order() = default;

  //! Order ID get function
  inline unsigned int ID() const
  {
    return m_ID;
  }

  //! Order contract ID get function
  inline unsigned int contractID() const
  {
    return m_contractID;
  }
  
  //! Order price get function
  inline int price() const
  {
    return m_price;
  }

  //! Order side  get function
  inline orderSide side() const
  {
    return m_side;
  }
        
  //! Order side as string get function
  inline std::string sideStr() const
  {
    return orderSideToSting(m_side);
  }
        
  //! Order volume get function
  inline int volume() const
  {
    return m_volume;
  }

  //! Order owner get function
  inline const std::shared_ptr<orderDelegate>& owner() const
  {
    return m_owner;
  }

  //! Order volume set function
  inline void setVolume(int p_volume)
  {
    m_volume = p_volume; 
  }
  
  //! Order less-than operator overload, compare by price
  inline bool operator<( const order& other) const
  {
    return m_price < other.m_price;
  }
        
  //! Order greater-than operator overload, compare by price
  inline bool operator>( const order& other) const
  {
    return !operator<(other);
  }

  // helper function to convert orderSide to string
  inline std::string orderSideToSting(const orderSide p_side) const
  {
    switch (p_side)
    {

      case orderSide::BUY:
        return "BUY";
        break;

      case orderSide::SELL:
        return "SELL";
        break;

      default:
        return "UNKNOWN ORDER SIDE";
        break ;
    }
  }

  //! Order << operator overload, for use with cout
  friend std::ostream& operator<<(std::ostream &os, const order& p)
  {
    os << "Order ID: " << p.m_ID << " Volume: " << p.m_volume << " Price: " << p.m_price/100.0 << " Side: " << p.sideStr();
    return os;
  }

 private:

  //! order ID
  unsigned int m_ID{0};

  //! order contract ID
  unsigned int m_contractID{0};

  //! order volume
  int m_volume{0};

  //! order price
  int m_price{0};

  //! order side (Buy/Sell)
  orderSide m_side{orderSide::BUY};

  //! order owner
  std::shared_ptr<orderDelegate> m_owner{nullptr};

  //! helper function to convert price to cents
  constexpr int price_to_cents(const double price)
  {
    return 100 * price;
  }
};


}  // market

#endif // ORDER_H
