#ifndef MARKET_DATA_DELEGATE_H
#define MARKET_DATA_DELEGATE_H


namespace webbtraders
{
    class marketDataDelegate
    {
    public:

        virtual void onPublicTrade() = 0;
        virtual void onTrade() = 0;
    };
    

}  // webbtraders

#endif // MARKET_DATA_DELEGATE_H
