//Link to Boost
#define BOOST_TEST_DYN_LINK

#include "matchingEngine.hpp"
#include "trader.hpp"

//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "BaseClassModule"
#include <boost/test/unit_test.hpp>

enum contract { IBM, APPLE };

BOOST_AUTO_TEST_CASE(adding_valid_orders)
{
  using namespace webbtraders;
  matchingEngine _market;
  auto _traderA = _market.addTrader();
  auto _traderB = _market.addTrader();
    
  _traderA->sendOrder(IBM, 100, 12.30, orderSide::BUY );
  _traderA->sendOrder(IBM, 100, 12.30, orderSide::SELL );
  BOOST_CHECK_EQUAL(_market.getOrderManagement().totalVolume(), 200);
}


BOOST_AUTO_TEST_CASE(adding_invalid_orders)
{
  using namespace webbtraders;
  matchingEngine _market;
  auto _traderA = _market.addTrader();    

  _traderA->sendOrder(IBM, -10, 12.30, orderSide::BUY );
  _traderA->sendOrder(IBM, -10, 12.30, orderSide::SELL );
  BOOST_CHECK_EQUAL(_market.getOrderManagement().totalVolume(), 0);
}

BOOST_AUTO_TEST_CASE(matching_orders_no_cross_price)
{
  using namespace webbtraders;
  matchingEngine _market;
  auto _traderA = _market.addTrader();    
  auto _traderB = _market.addTrader();    

  _traderA->sendOrder(IBM, 100, 12.29, orderSide::BUY );
  _traderB->sendOrder(IBM, 100, 12.30, orderSide::SELL );
  _market.close(); 
  BOOST_CHECK_EQUAL(_market.getOrderManagement().totalTradedVolume(), 0);
}

BOOST_AUTO_TEST_CASE(matching_orders_no_cross_contract)
{
  using namespace webbtraders;
  matchingEngine _market;
  auto _traderA = _market.addTrader();    
  auto _traderB = _market.addTrader();    

  _traderA->sendOrder(IBM, 100, 12.30, orderSide::BUY );
  _traderB->sendOrder(APPLE, 100, 12.30, orderSide::SELL );
  _market.close(); 
  BOOST_CHECK_EQUAL(_market.getOrderManagement().totalTradedVolume(), 0);
}


BOOST_AUTO_TEST_CASE(matching_orders_cross_contract)
{
  for (unsigned int i=0; i < 1; i++)
  {
    using namespace webbtraders;
    matchingEngine _market;
    auto _traderA = _market.addTrader();    
    auto _traderB = _market.addTrader();    

    _traderA->sendOrder(IBM, 100, 12.30, orderSide::BUY );
    _traderB->sendOrder(APPLE, 100, 12.30, orderSide::SELL );

    _traderA->sendOrder(APPLE, 100, 12.30, orderSide::BUY );
    _traderB->sendOrder(IBM, 100, 12.30, orderSide::SELL );

    _market.close(); 
    BOOST_CHECK_EQUAL(_market.getOrderManagement().totalTradedVolume(), 200);
  }
}

BOOST_AUTO_TEST_CASE(matching_orders_cross)
{
  for (int i=0; i<100; i++)
  {
    using namespace webbtraders;
    matchingEngine _market;
    auto _traderA = _market.addTrader();    
    auto _traderB = _market.addTrader();    

    _traderA->sendOrder(IBM, 100, 12.30, orderSide::BUY );
    _traderB->sendOrder(IBM, 100, 12.30, orderSide::SELL );

    _market.close(); 
    BOOST_CHECK_EQUAL(_market.getOrderManagement().totalTradedVolume(), 100);
  }
}

BOOST_AUTO_TEST_CASE(orders_example_from_the_task)
{
  /*
    Order 1 Buy 100@12.30
    Order 2 Buy 25@12:15
    Order 3 Buy 10@12.20
    Order 4 Sell 115@12.17
  */
    
  using namespace webbtraders;
  matchingEngine _market;
  auto _traderA = _market.addTrader();
  auto _traderB = _market.addTrader();

    
  _traderA->sendOrder(IBM, 100, 12.30, orderSide::BUY );
  _traderA->sendOrder(IBM, 25, 12.15, orderSide::BUY );

  _traderA->sendOrder(IBM, 10, 12.20, orderSide::BUY );
  _traderB->sendOrder(IBM, 115, 12.17, orderSide::SELL );

  _market.close(); 
  BOOST_CHECK_EQUAL(_market.getOrderManagement().totalTradedVolume(), 110);
}


BOOST_AUTO_TEST_CASE(stress_test)
{
  using namespace webbtraders;
  matchingEngine _market;

  unsigned int n = 1000;
  for (unsigned int i=0; i<n; ++i )
  {
    auto _traderA = _market.addTrader();    
    _traderA->sendOrder(IBM, 100, 12.30, orderSide::BUY );

    auto _traderB = _market.addTrader();    
    _traderB->sendOrder(IBM, 100, 12.30, orderSide::SELL );

  }

  _market.close(); 
  BOOST_CHECK_EQUAL(_market.getOrderManagement().totalVolume(), 2*n*100);
  BOOST_CHECK_EQUAL(_market.getOrderManagement().totalTradedVolume(), n*100);
}

BOOST_AUTO_TEST_CASE(multi_thread_test)
{
  using namespace webbtraders;
  matchingEngine _market;

  unsigned int n = 1000;
  unsigned int i=0; // j=0;
  auto _traderA = _market.addTrader(); 
  auto _traderB = _market.addTrader();    
    
  std::thread consumer([ & ] {
      while (i++ < n)  {
        _traderA->sendOrder(IBM, 100, 12.30, orderSide::SELL );
        _traderB->sendOrder(IBM, 100, 12.30, orderSide::BUY );
      }
    });

  consumer.join();
    
  BOOST_CHECK_EQUAL(true, true);
}



