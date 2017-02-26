#include "order.hpp"

using namespace webbtraders;

order::order(unsigned int p_ID, int p_volume, double p_price, orderSide p_side) noexcept
    :m_ID(p_ID),
     m_volume(p_volume),
     m_price(p_price),
     m_side(p_side)
{
}


