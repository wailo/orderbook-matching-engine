#ifndef ORDERDELEGATE_H
#define ORDERDELEGATE_H

namespace webbtraders
{
    class order;
    
    class orderDelegate
    {
    public:

        enum class orderExecutionState { FILLED, PARTIAL };

        class orderExecution
        {
        public:
            orderExecution( unsigned int p_activeVolume ):
                m_activeVolume(p_activeVolume),
                m_state(p_activeVolume? orderExecutionState::PARTIAL : orderExecutionState::FILLED) {}
            
            unsigned int m_activeVolume{0};
            orderExecutionState m_state;
        };

        virtual void onOrderExecution(const orderExecution& p_orderExcution ) = 0;
        virtual ~orderDelegate() = default;
         
    };

}  // webbtraders

#endif /* ORDERDELEGATE_H */
