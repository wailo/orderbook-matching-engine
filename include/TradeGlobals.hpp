#ifndef TRADEGLOBALS_H
#define TRADEGLOBALS_H
#include <chrono>

namespace market
{

//! Order execution state
enum class orderExecutionState {FILLED, PARTIAL};


class tradeData
{
 public:
  tradeData(unsigned int p_contractID, unsigned int p_orderID, int p_tradedVolume, int p_price):
      m_timeStamp(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())),
      m_contractID(p_contractID),
      m_orderID(p_orderID), 
      m_tradedVolume(p_tradedVolume),
      m_price(p_price),
      m_state(p_tradedVolume? orderExecutionState::PARTIAL : orderExecutionState::FILLED)
  {}

  //! Helper function. Converts order execution state to string
  std::string orderExecutionStateToString() const
  {
    switch (m_state)
    {
      case orderExecutionState::FILLED:
        return "FILLED";
        break;

      case orderExecutionState::PARTIAL:
        return "PARTIAL";
        break;

      default:
        return "UNKNOWN ORDER EXECUTION STATE";
        break ;
    }
  }


  //! Helper function to print trade data
  inline std::string toString()
  {
    return std::string(timeStamp() + " " + orderExecutionStateToString() + " " +std::to_string(m_tradedVolume) + "@" + std::to_string(m_price/100.0));
  }

  //! Trade time Stamp
  const std::time_t m_timeStamp;

  //! Trade contract ID
  const unsigned int m_contractID{0};

  //! Trade order ID
  const unsigned int m_orderID{0};

  //! Trade volume
  const int m_tradedVolume{0};

  //! Trade price
  const int m_price{0};

  //! Trade volume state
  const orderExecutionState m_state;

 private:

  // Get time stamp as string
  inline std::string timeStamp() const
  {
    return std::ctime(&m_timeStamp);
  }
  
}; 

}  // market

#endif /* TRADEGLOBALS_H */
