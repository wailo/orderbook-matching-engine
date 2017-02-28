#ifndef MARKET_DATA_DELEGATE_H
#define MARKET_DATA_DELEGATE_H

#include <vector>

namespace webbtraders
{
    class order;
    
    class marketDataDelegate
    {
    public:

        virtual void onOrderBook( const std::vector<order>& p_orderBook ) = 0;
        virtual void onPublicTrade() = 0;
        // virtual void onTrade() = 0;
        virtual ~marketDataDelegate() = default;
    };
    

}  // webbtraders

#endif // MARKET_DATA_DELEGATE_H
