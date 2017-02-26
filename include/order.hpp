#ifndef ORDER_H
#define ORDER_H

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

        int ID() const
            {
                return m_ID;
            }

        double price() const
            {
                return m_price;
            }
        orderSide side() const
            {
                return m_side;
            }
        
        int volume() const
            {
                return m_volume;
            }
        
        void setVolume(int p_volume)
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
    private:

        unsigned int m_ID{0};
        int m_volume{0};
        double m_price{0};
        orderSide m_side{orderSide::BUY};
    };
}  // webbtraders

#endif // ORDER_H
