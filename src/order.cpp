
#include "order.hpp"
#include "orderDelegate.hpp"
using namespace market;


order::order(unsigned int p_contractID, unsigned int p_ID, int p_volume, double p_price, orderSide p_side, const std::shared_ptr<orderDelegate>& p_owner) noexcept
    :m_ID(p_ID),
     m_contractID(p_contractID), 
     m_volume(p_volume),
     m_price(price_to_cents(p_price)),
     m_side(p_side),
     m_owner(p_owner)
{}



