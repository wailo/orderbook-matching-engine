#ifndef ORDER_H
#define ORDER_H

#include <iostream>

namespace webbtraders {

    // class orderDelegate;
    
    enum class orderSide {BUY, SELL};
    class orderDelegate;
    class order
    {
    public:

        //! Default constructor
        order(unsigned int p_contractID, unsigned int p_ID, int p_volume, double p_price, orderSide p_side, const std::shared_ptr<orderDelegate>& p_owner) noexcept;

        //! Copy constructor
        // order(const order &other);

        //! Move constructor
        // order(order &&other) noexcept;

        //! Destructor
        //  ~order() noexcept;

        //! Copy assignment operator
        // order& operator=(const order &other);

        //! Move assignment operator
        // order& operator=(order &&other) noexcept;

        inline unsigned int ID() const
            {
                return m_ID;
            }

        inline unsigned int contractID() const
            {
                return m_contractID;
            }
        
        inline int price() const
            {
                return m_price;
            }
        inline orderSide side() const
            {
                return m_side;
            }
        
        inline std::string sideStr() const
            {
                return orderSideToSting(m_side);
            }
        
        inline int volume() const
            {
                return m_volume;
            }

        inline const std::shared_ptr<orderDelegate>& owner() const
            {
                return m_owner;
            }

        inline void setVolume(int p_volume)
            {
                m_volume = p_volume; 
            }

        inline bool operator<( const order& other) const
            {
                return m_price < other.m_price;
            }
        
        inline bool operator>( const order& other) const
            {
                return !operator<(other);
            }
        
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

        // friend std::ostream& operator<<(std::ostream &os, const order& p);
        friend std::ostream& operator<<(std::ostream &os, const order& p)
            {
                os << "Order ID: " << p.m_ID << " Volume: " << p.m_volume << " Price: " << p.m_price << " Side: " << p.sideStr();
                return os;
            }

    private:

        unsigned int m_ID{0};
        unsigned int m_contractID{0};
        int m_volume{0};
        int m_price{0};
        orderSide m_side{orderSide::BUY};
        std::shared_ptr<orderDelegate> m_owner{nullptr};
        constexpr int price_to_cents(const double price)
            {
                return 100 * price;
            }
    };


}  // webbtraders

#endif // ORDER_H
