

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
BOOST_AUTO_TEST_CASE( orders_from_the_tesk )
{

    /*Order 1 Buy 100@12.30
      Order 2 Buy 25@12:15
      Order 3 Buy 10@12.20
    */
    
    using namespace webbtraders;
    market _market;
    auto _traderA = _market.addTrader();
    auto _traderB = _market.addTrader();

    
    _traderA->sendOrder(100, 12.30, orderSide::BUY );
    _traderA->sendOrder(25, 12.15, orderSide::BUY );
    _traderA->sendOrder(10, 12.20, orderSide::BUY );
    _traderB->sendOrder(115, 12.17, orderSide::SELL );
    // market.matchOrders(); 
    //Check default constructor
    BOOST_TEST_MESSAGE(_market.getOrderManagement().totalTradedVolume()); 
    BOOST_CHECK_EQUAL(_market.getOrderManagement().totalTradedVolume(), 110);

}


// BOOST_AUTO_TEST_CASE( test1 )
// {

//     /*Order 1 Buy 100@12.30
//       Order 2 Buy 25@12:15
//       Order 3 Buy 10@12.20
//     */
    
//     using namespace webbtraders;
//     market _market;
//     auto _traderA = _market.addTrader();
//     auto _traderB = _market.addTrader();

    
//     _traderA->sendOrder(100, 12.30, orderSide::BUY );
//     _traderA->sendOrder(25, 12.15, orderSide::BUY );
//     _traderA->sendOrder(10, 12.20, orderSide::BUY );
//     //    _traderB->sendOrder(115, 12.17, orderSide::SELL );
//     // market.matchOrders(); 
//     //Check default constructor
//     // BOOST_TEST_MESSAGE("test_message------------------");
//     BOOST_CHECK_EQUAL(_market.getOrderManagement().totalTradedVolume(), 0);

// }


