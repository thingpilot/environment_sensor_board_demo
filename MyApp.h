
#include "node_flow.h"

class MyApp: public NodeFlow {

public:
    void setup();
    void HandleInterrupt();
    uint8_t* MetricGroupA(uint16_t &length);
    uint8_t* MetricGroupB(uint16_t &length);
    uint8_t* MetricGroupC(uint16_t &length);
    uint8_t* MetricGroupD(uint16_t &length);
    

};