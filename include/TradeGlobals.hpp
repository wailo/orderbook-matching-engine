#ifndef TRADEGLOBALS_H
#define TRADEGLOBALS_H

namespace webbtraders
{

    enum class orderExecutionState { FILLED, PARTIAL };

    class tradeData
    {
    public:
        tradeData( unsigned int p_ID, int p_activeVolume ):
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

}  // webbtraders

#endif /* TRADEGLOBALS_H */
