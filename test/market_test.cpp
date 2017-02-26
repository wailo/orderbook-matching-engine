

//Link to Boost
#define BOOST_TEST_DYN_LINK

#include "market.hpp"
// #include "orderManagement.hpp"
#include "order.hpp"
#include "trader.hpp"


//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "BaseClassModule"
#include <boost/test/unit_test.hpp>


// ------------- Tests Follow --------------
BOOST_AUTO_TEST_CASE( orders )
{

    /*Order 1 Buy 100@12.30
      Order 2 Buy 25@12:15
      Order 3 Buy 10@12.20
    */

    
    BOOST_TEST_MESSAGE("test_message------------------WAIL");
    using namespace webbtraders;
    market _market;
    auto _trader = _market.addTrader();
    
    _trader->sendOrder(100, 12.30, orderSide::BUY );
    _trader->sendOrder(25, 12.15, orderSide::BUY );
    _trader->sendOrder(10, 12.20, orderSide::BUY );
    _trader->sendOrder(115, 12.17, orderSide::SELL );
    // market.matchOrders(); 
    
    //Check default constructor
    BOOST_TEST_MESSAGE("test_message------------------");
    BOOST_CHECK_EQUAL(2, 2);

}

//Name your test cases for what they test
BOOST_AUTO_TEST_CASE( assignment )
{
    int i = 0;
    int j = 1;
  
    j = i;
//Use BOOST_CHECK_EQUAL if you want the values to be 
//printed out if they mismatch
    BOOST_CHECK_EQUAL(j, i);
}

