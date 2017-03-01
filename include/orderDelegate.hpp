#ifndef ORDERDELEGATE_H
#define ORDERDELEGATE_H


//chage onPublic order to pass two vectors
//add trader to order object
// implement MT properly
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
            orderExecution( unsigned int p_ID, int p_activeVolume ):
                m_ID(p_ID),
                m_activeVolume(p_activeVolume),
                m_state(p_activeVolume? orderExecutionState::PARTIAL : orderExecutionState::FILLED) {}

            std::string orderExecutionStateToString() const
                {
                    switch (m_state)
                    {
                    case orderExecutionState::FILLED:
                        return "FILLED";
                        break;

                    case orderExecutionState::PARTIAL:
                        return "PARTIAL";
                        break;

                    default:
                        return "UNKNOWN ORDER EXECUTION STATE";
                        break ;
                    }
                }

            unsigned int m_ID{0};
            int m_activeVolume{0};
            orderExecutionState m_state;
        };

        virtual void onOrderExecution(const orderExecution& p_orderExcution ) = 0;
        virtual ~orderDelegate() = default;
         
    };

}  // webbtraders

#endif /* ORDERDELEGATE_H */
