
#include "node_flow.h"
class MyApp: public NodeFlow {

public:
    int setup();
    int HandleInterrupt();
    uint8_t* HandlePeriodic(uint16_t &length); //uint8_t payload[], uint16_t &length

};