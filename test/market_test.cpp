//Link to Boost
#define BOOST_TEST_DYN_LINK
//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "BaseClassModule"

#include "matchingEngine.hpp"
#include "trader.hpp"
#include "orderBook.hpp"
#include <boost/test/unit_test.hpp>

// dummy representation of order contracts
enum contract { IBM, APPLE };

BOOST_AUTO_TEST_CASE(adding_valid_orders)
{
  using namespace market;
  matchingEngine _market;
  auto _traderA = _market.addTrader();
  auto _traderB = _market.addTrader();
    
  _traderA->sendOrder(IBM, 100, 12.30, orderSide::BUY );
  _traderA->sendOrder(IBM, 100, 12.30, orderSide::SELL );
  BOOST_CHECK_EQUAL(_market.getOrderManagement().totalVolume(), 200);
}


BOOST_AUTO_TEST_CASE(adding_invalid_orders)
{
  using namespace market;
  matchingEngine _market;
  auto _traderA = _market.addTrader();    

  _traderA->sendOrder(IBM, -10, 12.30, orderSide::BUY );
  _traderA->sendOrder(IBM, -10, 12.30, orderSide::SELL );
  BOOST_CHECK_EQUAL(_market.getOrderManagement().totalVolume(), 0);
}

BOOST_AUTO_TEST_CASE(matching_orders_no_cross_price)
{
  using namespace market;
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
  using namespace market;
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
    using namespace market;
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
    using namespace market;
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
    
  using namespace market;
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

BOOST_AUTO_TEST_CASE(order_updates_test)
{

  /*
    Order 1 Buy 100@12.30
    Order 2 Buy 25@12:15
    Order 3 Buy 10@12.20
    Order 4 Sell 115@12.17
  */
    
  using namespace market;
  matchingEngine _market;
  auto _traderA = _market.addTrader();
  auto _traderB = _market.addTrader();

  auto _executedOrdersVolume = 0;
  _traderA->setOnOrderExecutionCallBack([&](const tradeData& p_tradeData) {

      _executedOrdersVolume += p_tradeData.m_tradedVolume;
    });
  
  _traderA->sendOrder(IBM, 100, 12.30, orderSide::BUY );
  _traderA->sendOrder(IBM, 25, 12.15, orderSide::BUY );

  _traderA->sendOrder(IBM, 10, 12.20, orderSide::BUY );
  _traderB->sendOrder(IBM, 115, 12.17, orderSide::SELL );

  _market.close();
  
  BOOST_CHECK_EQUAL(_executedOrdersVolume, 110); 
  BOOST_CHECK_EQUAL(_market.getOrderManagement().totalTradedVolume(), 110); 
}

BOOST_AUTO_TEST_CASE(public_trades_test)
{

  /*
    Order 1 Buy 100@12.30
    Order 2 Buy 25@12:15
    Order 3 Buy 10@12.20
    Order 4 Sell 115@12.17
  */
    
  using namespace market;
  matchingEngine _market;
  auto _traderA = _market.addTrader();
  auto _traderB = _market.addTrader();
  auto _traderC = _market.addTrader();

  auto _executedOrdersVolume = 0;
  _traderC->setOnPublicTradeCallBack([&](const tradeData& p_tradeData) {

      _executedOrdersVolume += p_tradeData.m_tradedVolume;
    });
  
  _traderA->sendOrder(IBM, 100, 12.30, orderSide::BUY );
  _traderA->sendOrder(IBM, 25, 12.15, orderSide::BUY );

  _traderA->sendOrder(IBM, 10, 12.20, orderSide::BUY );
  _traderB->sendOrder(IBM, 115, 12.17, orderSide::SELL );

  _market.close();
  
  BOOST_CHECK_EQUAL(_executedOrdersVolume, 110); 
  BOOST_CHECK_EQUAL(_market.getOrderManagement().totalTradedVolume(), 110); 
}


BOOST_AUTO_TEST_CASE(order_book_test)
{

  /*
    Order 1 Buy 100@12.30
    Order 2 Buy 25@12:15
    Order 3 Buy 10@12.20
    Order 4 Sell 115@12.17
  */
    
  using namespace market;
  matchingEngine _market;
  auto _traderA = _market.addTrader();
  auto _traderB = _market.addTrader();

  auto _orderBookTotalBuyPrice = 0;
  auto _orderBookTotalSellPrice = 0;
  auto _orderBookTotalBuyVolume = 25;
  auto _orderBookTotalSellVolume = 5;

  _traderA->setOnOrderBookCallBack([&](const orderBook& p_orderBook) {
      auto buys = p_orderBook.getBuyOrders();
      auto sells = p_orderBook.getSellOrders();

      _orderBookTotalBuyVolume = 0;
      _orderBookTotalBuyPrice = 0;
      _orderBookTotalSellVolume = 0;
      _orderBookTotalSellPrice = 0;


      for ( const auto& b : buys )
      {
        // std::cout << b << std::endl;
        _orderBookTotalBuyPrice += b.price();
        _orderBookTotalBuyVolume += b.volume();
      }

      for ( const auto& s : sells )
      {
        // std::cout << s << std::endl;
        _orderBookTotalSellPrice += s.price();
        _orderBookTotalSellVolume += s.volume();
      }
      
    });
  
  _traderA->sendOrder(IBM, 100, 12.30, orderSide::BUY );
  _traderA->sendOrder(IBM, 25, 12.15, orderSide::BUY );

  _traderA->sendOrder(IBM, 10, 12.20, orderSide::BUY );
  _traderB->sendOrder(IBM, 115, 12.17, orderSide::SELL );

  _market.close();
  
  BOOST_CHECK_EQUAL(_orderBookTotalBuyVolume, 25); 
  BOOST_CHECK_EQUAL(_orderBookTotalBuyPrice, 1215); 
  BOOST_CHECK_EQUAL(_orderBookTotalSellVolume, 5); 
  BOOST_CHECK_EQUAL(_orderBookTotalSellPrice, 1217); 
}


BOOST_AUTO_TEST_CASE(stress_test)
{
  using namespace market;
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
  using namespace market;
  matchingEngine _market;

  unsigned int n = 1000;
  unsigned int i=0; // j=0;
  auto _traderA = _market.addTrader(); 
  auto _traderB = _market.addTrader();    
    
  std::thread producer([ & ] {
      while (i++ < n)  {
        _traderA->sendOrder(IBM, 100, 12.30, orderSide::SELL );
        _traderB->sendOrder(IBM, 100, 12.30, orderSide::BUY );
      }
    });

  producer.join();

  // wait for the order Management to finish matching orders
  auto w = 5000000; 
  while (w--) {}

  BOOST_CHECK_EQUAL(_market.getOrderManagement().totalVolume(), 2*n*100);
  BOOST_CHECK_EQUAL(_market.getOrderManagement().totalTradedVolume(), n*100);
}
