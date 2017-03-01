#ifndef ORDER_H
#define ORDER_H

#include <iostream>

namespace webbtraders {

    enum class orderSide {BUY, SELL};
    class order
    {
    public:

        //! Default constructor
        order(unsigned int p_ID, int p_volume, double p_price, orderSide p_side) noexcept;

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
                orderSideToSting(m_side);
            }
        
        inline int volume() const
            {
                return m_volume;
            }
        
        inline void setVolume(int p_volume)
            {
                m_volume = p_volume;
            }

        bool operator<( const order& other) const
            {
                return m_price < other.m_price;
            }
        
        bool operator>( const order& other) const
            {
                return !operator<(other);
            }
        
        std::string orderSideToSting(const orderSide p_side) const
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
        int m_volume{0};
        int m_price{0};
        orderSide m_side{orderSide::BUY};

        constexpr int price_to_int(const double price)
            {
                return 100 * price;
            }
    };


}  // webbtraders

#endif // ORDER_H
