#include <memory>

#include "orderManagement.hpp"
#include "marketData.hpp"

namespace market
{

class trader;

class matchingEngine
{
 public:

  //! Default constructor
  matchingEngine();

  //! Destructor
  ~matchingEngine();

  //! Copy assignment operator
  matchingEngine& operator=(const matchingEngine &other) = delete;

  //! Move assignment operator
  matchingEngine& operator=(matchingEngine &&other) = delete;

  //! Copy constructor
  matchingEngine(const matchingEngine &other) = delete;

  //! Move constructor
  matchingEngine(matchingEngine &&other) = delete;
  
  //! create and Add trader to this market
  std::shared_ptr<trader> addTrader();

  //! orderManagement getter function
  orderManagement& getOrderManagement();

  //! Add order to the market
  bool addOrder(const std::shared_ptr<orderDelegate>& p_trader, unsigned int p_contractID, int p_volume, double p_price, orderSide p_side );

  //! Open market and start order executions
  void open();

  //! Close market and stop order executions
  void close();

 private:

  //! Market Data API
  marketData m_marketData;

  //! Order Management API
  orderManagement m_orderManagement;

  //std::vector<std::future<bool>> m_orderMatchingTasks; 
  std::future<bool> m_orderMatchingTask;

  //! Flag to open the market
  std::atomic<bool> m_live{true};

  //! flag to indicate when new order arrives 
  std::atomic<bool> m_newOrder{false};

  // Order matching thread
  std::thread m_thread;
};
    
}  // market
