#ifndef __STC32G144K246_DEF_H__
#define __STC32G144K246_DEF_H__

/////////////////////////////////////////////////

#include "stc32g144k246.h"
#include "def.h"

/////////////////////////////////////////////////

#define PORT_SetInitLevelLow(p, b)      CLR_REG_BIT(P##p, (b))
#define PORT_SetInitLevelHigh(p, b)     SET_REG_BIT(P##p, (b))

#define PORT_SetInitLevelLowX(p, b)     CLR_REG_BIT(P##p##OUT, (b))
#define PORT_SetInitLevelHighX(p, b)    SET_REG_BIT(P##p##OUT, (b))

#define PORT_SetQuasiMode(p, b)         CLR_REG_BIT(P##p##M0, (b)); \
                                        CLR_REG_BIT(P##p##M1, (b))

#define PORT_SetPushPullMode(p, b)      SET_REG_BIT(P##p##M0, (b)); \
                                        CLR_REG_BIT(P##p##M1, (b))

#define PORT_SetHighZInputMode(p, b)    CLR_REG_BIT(P##p##M0, (b)); \
                                        SET_REG_BIT(P##p##M1, (b))

#define PORT_SetOpenDrainMode(p, b)     SET_REG_BIT(P##p##M0, (b)); \
                                        SET_REG_BIT(P##p##M1, (b))

#define PORT_SetAutoMode(p, b)          CLR_REG_BIT(P##p##BP, (b))
#define PORT_SetManualMode(p, b)        SET_REG_BIT(P##p##BP, (b))

#define PORT_EnablePullUp(p, b)         SET_REG_BIT(P##p##PU, (b))
#define PORT_DisablePullUp(p, b)        CLR_REG_BIT(P##p##PU, (b))

#define PORT_EnablePullDown(p, b)       SET_REG_BIT(P##p##PD, (b))
#define PORT_DisablePullDown(p, b)      CLR_REG_BIT(P##p##PD, (b))

#define PORT_EnableSchmitt(p, b)        CLR_REG_BIT(P##p##NCS, (b))
#define PORT_DisableSchmitt(p, b)       SET_REG_BIT(P##p##NCS, (b))

#define PORT_SetSlewRateFast(p, b)      CLR_REG_BIT(P##p##SR, (b))
#define PORT_SetSlewRateNormal(p, b)    SET_REG_BIT(P##p##SR, (b))

#define PORT_SetDrivingStrong(p, b)     CLR_REG_BIT(P##p##DR, (b))
#define PORT_SetDrivingNormal(p, b)     SET_REG_BIT(P##p##DR, (b))

#define PORT_SetAnalogInput(p, b)       CLR_REG_BIT(P##p##IE, (b))
#define PORT_SetDigitalInput(p, b)      SET_REG_BIT(P##p##IE, (b))

#define SetP0nInitLevelLow(b)           PORT_SetInitLevelLow(0, (b))
#define SetP1nInitLevelLow(b)           PORT_SetInitLevelLow(1, (b))
#define SetP2nInitLevelLow(b)           PORT_SetInitLevelLow(2, (b))
#define SetP3nInitLevelLow(b)           PORT_SetInitLevelLow(3, (b))
#define SetP4nInitLevelLow(b)           PORT_SetInitLevelLow(4, (b))
#define SetP5nInitLevelLow(b)           PORT_SetInitLevelLow(5, (b))
#define SetP6nInitLevelLow(b)           PORT_SetInitLevelLow(6, (b))
#define SetP7nInitLevelLow(b)           PORT_SetInitLevelLow(7, (b))
#define SetP8nInitLevelLow(b)           PORT_SetInitLevelLowX(8, (b))
#define SetP9nInitLevelLow(b)           PORT_SetInitLevelLowX(9, (b))
#define SetPAnInitLevelLow(b)           PORT_SetInitLevelLowX(A, (b))
#define SetPBnInitLevelLow(b)           PORT_SetInitLevelLowX(B, (b))

#define SetP0nInitLevelHigh(b)          PORT_SetInitLevelHigh(0, (b))
#define SetP1nInitLevelHigh(b)          PORT_SetInitLevelHigh(1, (b))
#define SetP2nInitLevelHigh(b)          PORT_SetInitLevelHigh(2, (b))
#define SetP3nInitLevelHigh(b)          PORT_SetInitLevelHigh(3, (b))
#define SetP4nInitLevelHigh(b)          PORT_SetInitLevelHigh(4, (b))
#define SetP5nInitLevelHigh(b)          PORT_SetInitLevelHigh(5, (b))
#define SetP6nInitLevelHigh(b)          PORT_SetInitLevelHigh(6, (b))
#define SetP7nInitLevelHigh(b)          PORT_SetInitLevelHigh(7, (b))
#define SetP8nInitLevelHigh(b)          PORT_SetInitLevelHighX(8, (b))
#define SetP9nInitLevelHigh(b)          PORT_SetInitLevelHighX(9, (b))
#define SetPAnInitLevelHigh(b)          PORT_SetInitLevelHighX(A, (b))
#define SetPBnInitLevelHigh(b)          PORT_SetInitLevelHighX(B, (b))

#define SetP0nQuasiMode(b)              PORT_SetQuasiMode(0, (b))
#define SetP1nQuasiMode(b)              PORT_SetQuasiMode(1, (b))
#define SetP2nQuasiMode(b)              PORT_SetQuasiMode(2, (b))
#define SetP3nQuasiMode(b)              PORT_SetQuasiMode(3, (b))
#define SetP4nQuasiMode(b)              PORT_SetQuasiMode(4, (b))
#define SetP5nQuasiMode(b)              PORT_SetQuasiMode(5, (b))
#define SetP6nQuasiMode(b)              PORT_SetQuasiMode(6, (b))
#define SetP7nQuasiMode(b)              PORT_SetQuasiMode(7, (b))
#define SetP8nQuasiMode(b)              PORT_SetQuasiMode(8, (b))
#define SetP9nQuasiMode(b)              PORT_SetQuasiMode(9, (b))
#define SetPAnQuasiMode(b)              PORT_SetQuasiMode(A, (b))
#define SetPBnQuasiMode(b)              PORT_SetQuasiMode(B, (b))

#define SetP0nPushPullMode(b)           PORT_SetPushPullMode(0, (b))
#define SetP1nPushPullMode(b)           PORT_SetPushPullMode(1, (b))
#define SetP2nPushPullMode(b)           PORT_SetPushPullMode(2, (b))
#define SetP3nPushPullMode(b)           PORT_SetPushPullMode(3, (b))
#define SetP4nPushPullMode(b)           PORT_SetPushPullMode(4, (b))
#define SetP5nPushPullMode(b)           PORT_SetPushPullMode(5, (b))
#define SetP6nPushPullMode(b)           PORT_SetPushPullMode(6, (b))
#define SetP7nPushPullMode(b)           PORT_SetPushPullMode(7, (b))
#define SetP8nPushPullMode(b)           PORT_SetPushPullMode(8, (b))
#define SetP9nPushPullMode(b)           PORT_SetPushPullMode(9, (b))
#define SetPAnPushPullMode(b)           PORT_SetPushPullMode(A, (b))
#define SetPBnPushPullMode(b)           PORT_SetPushPullMode(B, (b))

#define SetP0nHighZInputMode(b)         PORT_SetHighZInputMode(0, (b))
#define SetP1nHighZInputMode(b)         PORT_SetHighZInputMode(1, (b))
#define SetP2nHighZInputMode(b)         PORT_SetHighZInputMode(2, (b))
#define SetP3nHighZInputMode(b)         PORT_SetHighZInputMode(3, (b))
#define SetP4nHighZInputMode(b)         PORT_SetHighZInputMode(4, (b))
#define SetP5nHighZInputMode(b)         PORT_SetHighZInputMode(5, (b))
#define SetP6nHighZInputMode(b)         PORT_SetHighZInputMode(6, (b))
#define SetP7nHighZInputMode(b)         PORT_SetHighZInputMode(7, (b))
#define SetP8nHighZInputMode(b)         PORT_SetHighZInputMode(8, (b))
#define SetP9nHighZInputMode(b)         PORT_SetHighZInputMode(9, (b))
#define SetPAnHighZInputMode(b)         PORT_SetHighZInputMode(A, (b))
#define SetPBnHighZInputMode(b)         PORT_SetHighZInputMode(B, (b))

#define SetP0nOpenDrainMode(b)          PORT_SetOpenDrainMode(0, (b))
#define SetP1nOpenDrainMode(b)          PORT_SetOpenDrainMode(1, (b))
#define SetP2nOpenDrainMode(b)          PORT_SetOpenDrainMode(2, (b))
#define SetP3nOpenDrainMode(b)          PORT_SetOpenDrainMode(3, (b))
#define SetP4nOpenDrainMode(b)          PORT_SetOpenDrainMode(4, (b))
#define SetP5nOpenDrainMode(b)          PORT_SetOpenDrainMode(5, (b))
#define SetP6nOpenDrainMode(b)          PORT_SetOpenDrainMode(6, (b))
#define SetP7nOpenDrainMode(b)          PORT_SetOpenDrainMode(7, (b))
#define SetP8nOpenDrainMode(b)          PORT_SetOpenDrainMode(8, (b))
#define SetP9nOpenDrainMode(b)          PORT_SetOpenDrainMode(9, (b))
#define SetPAnOpenDrainMode(b)          PORT_SetOpenDrainMode(A, (b))
#define SetPBnOpenDrainMode(b)          PORT_SetOpenDrainMode(B, (b))

#define SetP0nAutoMode(b)               PORT_SetAutoMode(0, (b))
#define SetP1nAutoMode(b)               PORT_SetAutoMode(1, (b))
#define SetP2nAutoMode(b)               PORT_SetAutoMode(2, (b))
#define SetP3nAutoMode(b)               PORT_SetAutoMode(3, (b))
#define SetP4nAutoMode(b)               PORT_SetAutoMode(4, (b))
#define SetP5nAutoMode(b)               PORT_SetAutoMode(5, (b))
#define SetP6nAutoMode(b)               PORT_SetAutoMode(6, (b))
#define SetP7nAutoMode(b)               PORT_SetAutoMode(7, (b))
#define SetP8nAutoMode(b)               PORT_SetAutoMode(8, (b))
#define SetP9nAutoMode(b)               PORT_SetAutoMode(9, (b))
#define SetPAnAutoMode(b)               PORT_SetAutoMode(A, (b))
#define SetPBnAutoMode(b)               PORT_SetAutoMode(B, (b))

#define SetP0nManualMode(b)             PORT_SetManualMode(0, (b))
#define SetP1nManualMode(b)             PORT_SetManualMode(1, (b))
#define SetP2nManualMode(b)             PORT_SetManualMode(2, (b))
#define SetP3nManualMode(b)             PORT_SetManualMode(3, (b))
#define SetP4nManualMode(b)             PORT_SetManualMode(4, (b))
#define SetP5nManualMode(b)             PORT_SetManualMode(5, (b))
#define SetP6nManualMode(b)             PORT_SetManualMode(6, (b))
#define SetP7nManualMode(b)             PORT_SetManualMode(7, (b))
#define SetP8nManualMode(b)             PORT_SetManualMode(8, (b))
#define SetP9nManualMode(b)             PORT_SetManualMode(9, (b))
#define SetPAnManualMode(b)             PORT_SetManualMode(A, (b))
#define SetPBnManualMode(b)             PORT_SetManualMode(B, (b))

#define EnableP0nPullUp(b)              PORT_EnablePullUp(0, (b))
#define EnableP1nPullUp(b)              PORT_EnablePullUp(1, (b))
#define EnableP2nPullUp(b)              PORT_EnablePullUp(2, (b))
#define EnableP3nPullUp(b)              PORT_EnablePullUp(3, (b))
#define EnableP4nPullUp(b)              PORT_EnablePullUp(4, (b))
#define EnableP5nPullUp(b)              PORT_EnablePullUp(5, (b))
#define EnableP6nPullUp(b)              PORT_EnablePullUp(6, (b))
#define EnableP7nPullUp(b)              PORT_EnablePullUp(7, (b))
#define EnableP8nPullUp(b)              PORT_EnablePullUp(8, (b))
#define EnableP9nPullUp(b)              PORT_EnablePullUp(9, (b))
#define EnablePAnPullUp(b)              PORT_EnablePullUp(A, (b))
#define EnablePBnPullUp(b)              PORT_EnablePullUp(B, (b))

#define DisableP0nPullUp(b)             PORT_DisablePullUp(0, (b))
#define DisableP1nPullUp(b)             PORT_DisablePullUp(1, (b))
#define DisableP2nPullUp(b)             PORT_DisablePullUp(2, (b))
#define DisableP3nPullUp(b)             PORT_DisablePullUp(3, (b))
#define DisableP4nPullUp(b)             PORT_DisablePullUp(4, (b))
#define DisableP5nPullUp(b)             PORT_DisablePullUp(5, (b))
#define DisableP6nPullUp(b)             PORT_DisablePullUp(6, (b))
#define DisableP7nPullUp(b)             PORT_DisablePullUp(7, (b))
#define DisableP8nPullUp(b)             PORT_DisablePullUp(8, (b))
#define DisableP9nPullUp(b)             PORT_DisablePullUp(9, (b))
#define DisablePAnPullUp(b)             PORT_DisablePullUp(A, (b))
#define DisablePBnPullUp(b)             PORT_DisablePullUp(B, (b))

#define EnableP0nPullDown(b)            PORT_EnablePullDown(0, (b))
#define EnableP1nPullDown(b)            PORT_EnablePullDown(1, (b))
#define EnableP2nPullDown(b)            PORT_EnablePullDown(2, (b))
#define EnableP3nPullDown(b)            PORT_EnablePullDown(3, (b))
#define EnableP4nPullDown(b)            PORT_EnablePullDown(4, (b))
#define EnableP5nPullDown(b)            PORT_EnablePullDown(5, (b))
#define EnableP6nPullDown(b)            PORT_EnablePullDown(6, (b))
#define EnableP7nPullDown(b)            PORT_EnablePullDown(7, (b))
#define EnableP8nPullDown(b)            PORT_EnablePullDown(8, (b))
#define EnableP9nPullDown(b)            PORT_EnablePullDown(9, (b))
#define EnablePAnPullDown(b)            PORT_EnablePullDown(A, (b))
#define EnablePBnPullDown(b)            PORT_EnablePullDown(B, (b))

#define DisableP0nPullDown(b)           PORT_DisablePullDown(0, (b))
#define DisableP1nPullDown(b)           PORT_DisablePullDown(1, (b))
#define DisableP2nPullDown(b)           PORT_DisablePullDown(2, (b))
#define DisableP3nPullDown(b)           PORT_DisablePullDown(3, (b))
#define DisableP4nPullDown(b)           PORT_DisablePullDown(4, (b))
#define DisableP5nPullDown(b)           PORT_DisablePullDown(5, (b))
#define DisableP6nPullDown(b)           PORT_DisablePullDown(6, (b))
#define DisableP7nPullDown(b)           PORT_DisablePullDown(7, (b))
#define DisableP8nPullDown(b)           PORT_DisablePullDown(8, (b))
#define DisableP9nPullDown(b)           PORT_DisablePullDown(9, (b))
#define DisablePAnPullDown(b)           PORT_DisablePullDown(A, (b))
#define DisablePBnPullDown(b)           PORT_DisablePullDown(B, (b))

#define EnableP0nSchmitt(b)             PORT_EnableSchmitt(0, (b))
#define EnableP1nSchmitt(b)             PORT_EnableSchmitt(1, (b))
#define EnableP2nSchmitt(b)             PORT_EnableSchmitt(2, (b))
#define EnableP3nSchmitt(b)             PORT_EnableSchmitt(3, (b))
#define EnableP4nSchmitt(b)             PORT_EnableSchmitt(4, (b))
#define EnableP5nSchmitt(b)             PORT_EnableSchmitt(5, (b))
#define EnableP6nSchmitt(b)             PORT_EnableSchmitt(6, (b))
#define EnableP7nSchmitt(b)             PORT_EnableSchmitt(7, (b))
#define EnableP8nSchmitt(b)             PORT_EnableSchmitt(8, (b))
#define EnableP9nSchmitt(b)             PORT_EnableSchmitt(9, (b))
#define EnablePAnSchmitt(b)             PORT_EnableSchmitt(A, (b))
#define EnablePBnSchmitt(b)             PORT_EnableSchmitt(B, (b))

#define DisableP0nSchmitt(b)            PORT_DisableSchmitt(0, (b))
#define DisableP1nSchmitt(b)            PORT_DisableSchmitt(1, (b))
#define DisableP2nSchmitt(b)            PORT_DisableSchmitt(2, (b))
#define DisableP3nSchmitt(b)            PORT_DisableSchmitt(3, (b))
#define DisableP4nSchmitt(b)            PORT_DisableSchmitt(4, (b))
#define DisableP5nSchmitt(b)            PORT_DisableSchmitt(5, (b))
#define DisableP6nSchmitt(b)            PORT_DisableSchmitt(6, (b))
#define DisableP7nSchmitt(b)            PORT_DisableSchmitt(7, (b))
#define DisableP8nSchmitt(b)            PORT_DisableSchmitt(8, (b))
#define DisableP9nSchmitt(b)            PORT_DisableSchmitt(9, (b))
#define DisablePAnSchmitt(b)            PORT_DisableSchmitt(A, (b))
#define DisablePBnSchmitt(b)            PORT_DisableSchmitt(B, (b))

#define SetP0nSlewRateFast(b)           PORT_SetSlewRateFast(0, (b))
#define SetP1nSlewRateFast(b)           PORT_SetSlewRateFast(1, (b))
#define SetP2nSlewRateFast(b)           PORT_SetSlewRateFast(2, (b))
#define SetP3nSlewRateFast(b)           PORT_SetSlewRateFast(3, (b))
#define SetP4nSlewRateFast(b)           PORT_SetSlewRateFast(4, (b))
#define SetP5nSlewRateFast(b)           PORT_SetSlewRateFast(5, (b))
#define SetP6nSlewRateFast(b)           PORT_SetSlewRateFast(6, (b))
#define SetP7nSlewRateFast(b)           PORT_SetSlewRateFast(7, (b))
#define SetP8nSlewRateFast(b)           PORT_SetSlewRateFast(8, (b))
#define SetP9nSlewRateFast(b)           PORT_SetSlewRateFast(9, (b))
#define SetPAnSlewRateFast(b)           PORT_SetSlewRateFast(A, (b))
#define SetPBnSlewRateFast(b)           PORT_SetSlewRateFast(B, (b))

#define SetP0nSlewRateNormal(b)         PORT_SetSlewRateNormal(0, (b))
#define SetP1nSlewRateNormal(b)         PORT_SetSlewRateNormal(1, (b))
#define SetP2nSlewRateNormal(b)         PORT_SetSlewRateNormal(2, (b))
#define SetP3nSlewRateNormal(b)         PORT_SetSlewRateNormal(3, (b))
#define SetP4nSlewRateNormal(b)         PORT_SetSlewRateNormal(4, (b))
#define SetP5nSlewRateNormal(b)         PORT_SetSlewRateNormal(5, (b))
#define SetP6nSlewRateNormal(b)         PORT_SetSlewRateNormal(6, (b))
#define SetP7nSlewRateNormal(b)         PORT_SetSlewRateNormal(7, (b))
#define SetP8nSlewRateNormal(b)         PORT_SetSlewRateNormal(8, (b))
#define SetP9nSlewRateNormal(b)         PORT_SetSlewRateNormal(9, (b))
#define SetPAnSlewRateNormal(b)         PORT_SetSlewRateNormal(A, (b))
#define SetPBnSlewRateNormal(b)         PORT_SetSlewRateNormal(B, (b))

#define SetP0nDrivingStrong(b)          PORT_SetDrivingStrong(0, (b))
#define SetP1nDrivingStrong(b)          PORT_SetDrivingStrong(1, (b))
#define SetP2nDrivingStrong(b)          PORT_SetDrivingStrong(2, (b))
#define SetP3nDrivingStrong(b)          PORT_SetDrivingStrong(3, (b))
#define SetP4nDrivingStrong(b)          PORT_SetDrivingStrong(4, (b))
#define SetP5nDrivingStrong(b)          PORT_SetDrivingStrong(5, (b))
#define SetP6nDrivingStrong(b)          PORT_SetDrivingStrong(6, (b))
#define SetP7nDrivingStrong(b)          PORT_SetDrivingStrong(7, (b))
#define SetP8nDrivingStrong(b)          PORT_SetDrivingStrong(8, (b))
#define SetP9nDrivingStrong(b)          PORT_SetDrivingStrong(9, (b))
#define SetPAnDrivingStrong(b)          PORT_SetDrivingStrong(A, (b))
#define SetPBnDrivingStrong(b)          PORT_SetDrivingStrong(B, (b))

#define SetP0nDrivingNormal(b)          PORT_SetDrivingNormal(0, (b))
#define SetP1nDrivingNormal(b)          PORT_SetDrivingNormal(1, (b))
#define SetP2nDrivingNormal(b)          PORT_SetDrivingNormal(2, (b))
#define SetP3nDrivingNormal(b)          PORT_SetDrivingNormal(3, (b))
#define SetP4nDrivingNormal(b)          PORT_SetDrivingNormal(4, (b))
#define SetP5nDrivingNormal(b)          PORT_SetDrivingNormal(5, (b))
#define SetP6nDrivingNormal(b)          PORT_SetDrivingNormal(6, (b))
#define SetP7nDrivingNormal(b)          PORT_SetDrivingNormal(7, (b))
#define SetP8nDrivingNormal(b)          PORT_SetDrivingNormal(8, (b))
#define SetP9nDrivingNormal(b)          PORT_SetDrivingNormal(9, (b))
#define SetPAnDrivingNormal(b)          PORT_SetDrivingNormal(A, (b))
#define SetPBnDrivingNormal(b)          PORT_SetDrivingNormal(B, (b))

#define SetP0nAnalogInput(b)            PORT_SetAnalogInput(0, (b))
#define SetP1nAnalogInput(b)            PORT_SetAnalogInput(1, (b))
#define SetP2nAnalogInput(b)            PORT_SetAnalogInput(2, (b))
#define SetP3nAnalogInput(b)            PORT_SetAnalogInput(3, (b))
#define SetP4nAnalogInput(b)            PORT_SetAnalogInput(4, (b))
#define SetP5nAnalogInput(b)            PORT_SetAnalogInput(5, (b))
#define SetP6nAnalogInput(b)            PORT_SetAnalogInput(6, (b))
#define SetP7nAnalogInput(b)            PORT_SetAnalogInput(7, (b))
#define SetP8nAnalogInput(b)            PORT_SetAnalogInput(8, (b))
#define SetP9nAnalogInput(b)            PORT_SetAnalogInput(9, (b))
#define SetPAnAnalogInput(b)            PORT_SetAnalogInput(A, (b))
#define SetPBnAnalogInput(b)            PORT_SetAnalogInput(B, (b))

#define SetP0nDigitalInput(b)           PORT_SetDigitalInput(0, (b))
#define SetP1nDigitalInput(b)           PORT_SetDigitalInput(1, (b))
#define SetP2nDigitalInput(b)           PORT_SetDigitalInput(2, (b))
#define SetP3nDigitalInput(b)           PORT_SetDigitalInput(3, (b))
#define SetP4nDigitalInput(b)           PORT_SetDigitalInput(4, (b))
#define SetP5nDigitalInput(b)           PORT_SetDigitalInput(5, (b))
#define SetP6nDigitalInput(b)           PORT_SetDigitalInput(6, (b))
#define SetP7nDigitalInput(b)           PORT_SetDigitalInput(7, (b))
#define SetP8nDigitalInput(b)           PORT_SetDigitalInput(8, (b))
#define SetP9nDigitalInput(b)           PORT_SetDigitalInput(9, (b))
#define SetPAnDigitalInput(b)           PORT_SetDigitalInput(A, (b))
#define SetPBnDigitalInput(b)           PORT_SetDigitalInput(B, (b))

/////////////////////////////////////////////////

#define EnableGlobalInt()               (EA = 1)
#define DisableGlobalInt()              (EA = 0)

#define INT0_EnableInt()                (EX0 = 1)
#define INT0_DisableInt()               (EX0 = 0)

#define INT1_EnableInt()                (EX1 = 1)
#define INT1_DisableInt()               (EX1 = 0)

#define INTCLKO_EX2_MSK                 BIT4
#define INT2_EnableInt()                SET_REG_BIT(INTCLKO, INTCLKO_EX2_MSK)
#define INT2_DisableInt()               CLR_REG_BIT(INTCLKO, INTCLKO_EX2_MSK)

#define INTCLKO_EX3_MSK                 BIT5
#define INT3_EnableInt()                SET_REG_BIT(INTCLKO, INTCLKO_EX3_MSK)
#define INT3_DisableInt()               CLR_REG_BIT(INTCLKO, INTCLKO_EX3_MSK)

#define INTCLKO_EX4_MSK                 BIT6
#define INT4_EnableInt()                SET_REG_BIT(INTCLKO, INTCLKO_EX4_MSK)
#define INT4_DisableInt()               CLR_REG_BIT(INTCLKO, INTCLKO_EX4_MSK)

#define TIMER0_EnableInt()              (ET0 = 1)
#define TIMER0_DisableInt()             (ET0 = 0)

#define TIMER1_EnableInt()              (ET1 = 1)
#define TIMER1_DisableInt()             (ET1 = 0)

#define IE2_ET2_MSK                     BIT2
#define TIMER2_EnableInt()              SET_REG_BIT(IE2, IE2_ET2_MSK)
#define TIMER2_DisableInt()             CLR_REG_BIT(IE2, IE2_ET2_MSK)

#define IE2_ET3_MSK                     BIT5
#define TIMER3_EnableInt()              SET_REG_BIT(IE2, IE2_ET3_MSK)
#define TIMER3_DisableInt()             CLR_REG_BIT(IE2, IE2_ET3_MSK)

#define IE2_ET4_MSK                     BIT6
#define TIMER4_EnableInt()              SET_REG_BIT(IE2, IE2_ET4_MSK)
#define TIMER4_DisableInt()             CLR_REG_BIT(IE2, IE2_ET4_MSK)

#define T6T5CFG_ET5_MSK                 BIT0
#define TIMER5_EnableInt()              SET_REG_BIT(T6T5CFG, T6T5CFG_ET5_MSK)
#define TIMER5_DisableInt()             CLR_REG_BIT(T6T5CFG, T6T5CFG_ET5_MSK)

#define T6T5CFG_ET6_MSK                 BIT4
#define TIMER6_EnableInt()              SET_REG_BIT(T6T5CFG, T6T5CFG_ET6_MSK)
#define TIMER6_DisableInt()             CLR_REG_BIT(T6T5CFG, T6T5CFG_ET6_MSK)

#define T8T7CFG_ET7_MSK                 BIT0
#define TIMER7_EnableInt()              SET_REG_BIT(T8T7CFG, T8T7CFG_ET7_MSK)
#define TIMER7_DisableInt()             CLR_REG_BIT(T8T7CFG, T8T7CFG_ET7_MSK)

#define T8T7CFG_ET8_MSK                 BIT4
#define TIMER8_EnableInt()              SET_REG_BIT(T8T7CFG, T8T7CFG_ET8_MSK)
#define TIMER8_DisableInt()             CLR_REG_BIT(T8T7CFG, T8T7CFG_ET8_MSK)

#define T10T9CFG_ET9_MSK                BIT0
#define TIMER9_EnableInt()              SET_REG_BIT(T10T9CFG, T10T9CFG_ET9_MSK)
#define TIMER9_DisableInt()             CLR_REG_BIT(T10T9CFG, T10T9CFG_ET9_MSK)

#define T10T9CFG_ET10_MSK               BIT4
#define TIMER10_EnableInt()             SET_REG_BIT(T10T9CFG, T10T9CFG_ET10_MSK)
#define TIMER10_DisableInt()            CLR_REG_BIT(T10T9CFG, T10T9CFG_ET10_MSK)

#define T11CR_ET11I_MSK                 BIT1
#define TIMER11_EnableInt()             SET_REG_BIT(T11CR, T11CR_ET11I_MSK)
#define TIMER11_DisableInt()            CLR_REG_BIT(T11CR, T11CR_ET11I_MSK)

#define T18T17CFG_ET17_MSK              BIT0
#define TIMER17_EnableInt()             SET_REG_BIT(T18T17CFG, T18T17CFG_ET17_MSK)
#define TIMER17_DisableInt()            CLR_REG_BIT(T18T17CFG, T18T17CFG_ET17_MSK)

#define T18T17CFG_ET18_MSK              BIT4
#define TIMER18_EnableInt()             SET_REG_BIT(T18T17CFG, T18T17CFG_ET18_MSK)
#define TIMER18_DisableInt()            CLR_REG_BIT(T18T17CFG, T18T17CFG_ET18_MSK)

#define UART1_EnableInt()               (ES = 1)
#define UART1_DisableInt()              (ES = 0)

#define IE2_ES2_MSK                     BIT0
#define UART2_EnableInt()               SET_REG_BIT(IE2, IE2_ES2_MSK)
#define UART2_DisableInt()              CLR_REG_BIT(IE2, IE2_ES2_MSK)

#define IE2_ES3_MSK                     BIT3
#define UART3_EnableInt()               SET_REG_BIT(IE2, IE2_ES3_MSK)
#define UART3_DisableInt()              CLR_REG_BIT(IE2, IE2_ES3_MSK)

#define IE2_ES4_MSK                     BIT4
#define UART4_EnableInt()               SET_REG_BIT(IE2, IE2_ES4_MSK)
#define UART4_DisableInt()              CLR_REG_BIT(IE2, IE2_ES4_MSK)

#define S5INTR_ES5_MSK                  BIT4
#define UART5_EnableInt()               SET_REG_BIT(S5INTR, S5INTR_ES5_MSK)
#define UART5_DisableInt()              CLR_REG_BIT(S5INTR, S5INTR_ES5_MSK)

#define S6INTR_ES6_MSK                  BIT4
#define UART6_EnableInt()               SET_REG_BIT(S6INTR, S6INTR_ES6_MSK)
#define UART6_DisableInt()              CLR_REG_BIT(S6INTR, S6INTR_ES6_MSK)

#define S7INTR_ES7_MSK                  BIT4
#define UART7_EnableInt()               SET_REG_BIT(S7INTR, S7INTR_ES7_MSK)
#define UART7_DisableInt()              CLR_REG_BIT(S7INTR, S7INTR_ES7_MSK)

#define S8INTR_ES8_MSK                  BIT4
#define UART8_EnableInt()               SET_REG_BIT(S8INTR, S8INTR_ES8_MSK)
#define UART8_DisableInt()              CLR_REG_BIT(S8INTR, S8INTR_ES8_MSK)

#define LVD_EnableInt()                 (ELVD = 1)
#define LVD_DisableInt()                (ELVD = 0)

#define ADC1_EnableInt()                (EADC = 1)
#define ADC1_DisableInt()               (EADC = 0)

#define ADC2INTR_EADC2_MSK              BIT0
#define ADC2_EnableInt()                SET_REG_BIT(ADC2INTR, ADC2INTR_EADC2_MSK)
#define ADC2_DisableInt()               CLR_REG_BIT(ADC2INTR, ADC2INTR_EADC2_MSK)

#define DAC1CR_EDAC_MSK                 BIT1
#define DAC1_EnableInt()                SET_REG_BIT(DAC1_CR, DAC1CR_EDAC_MSK)
#define DAC1_DisableInt()               CLR_REG_BIT(DAC1_CR, DAC1CR_EDAC_MSK)

#define DAC2CR_EDAC_MSK                 BIT1
#define DAC2_EnableInt()                SET_REG_BIT(DAC2_CR, DAC2CR_EDAC_MSK)
#define DAC2_DisableInt()               CLR_REG_BIT(DAC2_CR, DAC2CR_EDAC_MSK)

#define IE2_ESPI_MSK                    BIT1
#define SPI1_EnableInt()                SET_REG_BIT(IE2, IE2_ESPI_MSK)
#define SPI1_DisableInt()               CLR_REG_BIT(IE2, IE2_ESPI_MSK)

#define SPI2INTR_ESPI2_MSK              BIT0
#define SPI2_EnableInt()                SET_REG_BIT(SPI2INTR, SPI2INTR_ESPI2_MSK)
#define SPI2_DisableInt()               CLR_REG_BIT(SPI2INTR, SPI2INTR_ESPI2_MSK)

#define SPI3INTR_ESPI3_MSK              BIT0
#define SPI3_EnableInt()                SET_REG_BIT(SPI3INTR, SPI3INTR_ESPI3_MSK)
#define SPI3_DisableInt()               CLR_REG_BIT(SPI3INTR, SPI3INTR_ESPI3_MSK)

#define IE2_EUSB_MSK                    BIT7
#define USB_EnableInt()                 SET_REG_BIT(IE2, IE2_EUSB_MSK)
#define USB_DisableInt()                CLR_REG_BIT(IE2, IE2_EUSB_MSK)

#define CMP1CR1_PIE_MSK                 BIT5
#define CMP1CR1_NIE_MSK                 BIT4
#define CMP1_EnablePosedgeInt()         SET_REG_BIT(CMP1_6P6N_CR1, CMP1CR1_PIE_MSK)
#define CMP1_EnableNegedgeInt()         SET_REG_BIT(CMP1_6P6N_CR1, CMP1CR1_NIE_MSK)
#define CMP1_EnableEdgeInt()            SET_REG_BIT(CMP1_6P6N_CR1, (CMP1CR1_PIE_MSK | CMP1CR1_NIE_MSK))
#define CMP1_DisableInt()               CLR_REG_BIT(CMP1_6P6N_CR1, (CMP1CR1_PIE_MSK | CMP1CR1_NIE_MSK))

#define CMP2CR1_PIE_MSK                 BIT5
#define CMP2CR1_NIE_MSK                 BIT4
#define CMP2_EnablePosedgeInt()         SET_REG_BIT(CMP2_6P6N_CR1, CMP2CR1_PIE_MSK)
#define CMP2_EnableNegedgeInt()         SET_REG_BIT(CMP2_6P6N_CR1, CMP2CR1_NIE_MSK)
#define CMP2_EnableEdgeInt()            SET_REG_BIT(CMP2_6P6N_CR1, (CMP2CR1_PIE_MSK | CMP2CR1_NIE_MSK))
#define CMP2_DisableInt()               CLR_REG_BIT(CMP2_6P6N_CR1, (CMP2CR1_PIE_MSK | CMP2CR1_NIE_MSK))

#define CMP3CR1_PIE_MSK                 BIT5
#define CMP3CR1_NIE_MSK                 BIT4
#define CMP3_EnablePosedgeInt()         SET_REG_BIT(CMP3_6P6N_CR1, CMP3CR1_PIE_MSK)
#define CMP3_EnableNegedgeInt()         SET_REG_BIT(CMP3_6P6N_CR1, CMP3CR1_NIE_MSK)
#define CMP3_EnableEdgeInt()            SET_REG_BIT(CMP3_6P6N_CR1, (CMP3CR1_PIE_MSK | CMP3CR1_NIE_MSK))
#define CMP3_DisableInt()               CLR_REG_BIT(CMP3_6P6N_CR1, (CMP3CR1_PIE_MSK | CMP3CR1_NIE_MSK))

#define CMP4CR1_PIE_MSK                 BIT5
#define CMP4CR1_NIE_MSK                 BIT4
#define CMP4_EnablePosedgeInt()         SET_REG_BIT(CMP4_6P6N_CR1, CMP4CR1_PIE_MSK)
#define CMP4_EnableNegedgeInt()         SET_REG_BIT(CMP4_6P6N_CR1, CMP4CR1_NIE_MSK)
#define CMP4_EnableEdgeInt()            SET_REG_BIT(CMP4_6P6N_CR1, (CMP4CR1_PIE_MSK | CMP4CR1_NIE_MSK))
#define CMP4_DisableInt()               CLR_REG_BIT(CMP4_6P6N_CR1, (CMP4CR1_PIE_MSK | CMP4CR1_NIE_MSK))

#define RTCIEN_ALARM_MSK                BIT7
#define RTCIEN_DAY_MSK                  BIT6
#define RTCIEN_HOUR_MSK                 BIT5
#define RTCIEN_MIN_MSK                  BIT4
#define RTCIEN_SEC_MSK                  BIT3
#define RTCIEN_SEC2_MSK                 BIT2
#define RTCIEN_SEC8_MSK                 BIT1
#define RTCIEN_SEC32_MSK                BIT0
#define RTC_EnableAlarmInt()            SET_REG_BIT(RTCIEN, RTCIEN_ALARM_MSK)
#define RTC_EnableDayInt()              SET_REG_BIT(RTCIEN, RTCIEN_DAY_MSK)
#define RTC_EnableHourInt()             SET_REG_BIT(RTCIEN, RTCIEN_HOUR_MSK)
#define RTC_EnableMinuteInt()           SET_REG_BIT(RTCIEN, RTCIEN_MIN_MSK)
#define RTC_EnableSecondInt()           SET_REG_BIT(RTCIEN, RTCIEN_SEC_MSK)
#define RTC_EnableSecondD2Int()         SET_REG_BIT(RTCIEN, RTCIEN_SEC2_MSK)
#define RTC_EnableSecondD8Int()         SET_REG_BIT(RTCIEN, RTCIEN_SEC8_MSK)
#define RTC_EnableSecondD32Int()        SET_REG_BIT(RTCIEN, RTCIEN_SEC32_MSK)
#define RTC_DisableAlarmInt()           CLR_REG_BIT(RTCIEN, RTCIEN_ALARM_MSK)
#define RTC_DisableDayInt()             CLR_REG_BIT(RTCIEN, RTCIEN_DAY_MSK)
#define RTC_DisableHourInt()            CLR_REG_BIT(RTCIEN, RTCIEN_HOUR_MSK)
#define RTC_DisableMinuteInt()          CLR_REG_BIT(RTCIEN, RTCIEN_MIN_MSK)
#define RTC_DisableSecondInt()          CLR_REG_BIT(RTCIEN, RTCIEN_SEC_MSK)
#define RTC_DisableSecondD2Int()        CLR_REG_BIT(RTCIEN, RTCIEN_SEC2_MSK)
#define RTC_DisableSecondD8Int()        CLR_REG_BIT(RTCIEN, RTCIEN_SEC8_MSK)
#define RTC_DisableSecondD32Int()       CLR_REG_BIT(RTCIEN, RTCIEN_SEC32_MSK)

#define LCMIFIE_MSK                     BIT7
#define LCM_EnableInt()                 SET_REG_BIT(LCMIFCFG, LCMIFIE_MSK)
#define LCM_DisableInt()                CLR_REG_BIT(LCMIFCFG, LCMIFIE_MSK)

#define I2CMSCR_EMSI_MSK                BIT7
#define I2C1_EnableMasterInt()          SET_REG_BIT(I2CMSCR, I2CMSCR_EMSI_MSK)
#define I2C1_DisableMasterInt()         CLR_REG_BIT(I2CMSCR, I2CMSCR_EMSI_MSK)

#define I2CSLCR_ESTAI_MSK               BIT6
#define I2CSLCR_ERXI_MSK                BIT5
#define I2CSLCR_ETXI_MSK                BIT4
#define I2CSLCR_ESTOI_MSK               BIT3
#define I2C1_EnableSlaveSTAInt()        SET_REG_BIT(I2CSLCR, I2CSLCR_ESTAI_MSK)
#define I2C1_EnableSlaveSTOInt()        SET_REG_BIT(I2CSLCR, I2CSLCR_ESTOI_MSK)
#define I2C1_EnableSlaveRXInt()         SET_REG_BIT(I2CSLCR, I2CSLCR_ERXI_MSK)
#define I2C1_EnableSlaveTXInt()         SET_REG_BIT(I2CSLCR, I2CSLCR_ETXI_MSK)
#define I2C1_EnableSlaveAllInt()        SET_REG_BIT(I2CSLCR, I2CSLCR_ESTAI_MSK | I2CSLCR_ESTOI_MSK | I2CSLCR_ERXI_MSK | I2CSLCR_ETXI_MSK)
#define I2C1_DisableSlaveSTAInt()       CLR_REG_BIT(I2CSLCR, I2CSLCR_ESTAI_MSK)
#define I2C1_DisableSlaveSTOInt()       CLR_REG_BIT(I2CSLCR, I2CSLCR_ESTOI_MSK)
#define I2C1_DisableSlaveRXInt()        CLR_REG_BIT(I2CSLCR, I2CSLCR_ERXI_MSK)
#define I2C1_DisableSlaveTXInt()        CLR_REG_BIT(I2CSLCR, I2CSLCR_ETXI_MSK)
#define I2C1_DisableSlaveAllInt()       CLR_REG_BIT(I2CSLCR, I2CSLCR_ESTAI_MSK | I2CSLCR_ESTOI_MSK | I2CSLCR_ERXI_MSK | I2CSLCR_ETXI_MSK)

#define I2C2MSCR_EMSI_MSK               BIT7
#define I2C2_EnableMasterInt()          SET_REG_BIT(I2C2MSCR, I2C2MSCR_EMSI_MSK)
#define I2C2_DisableMasterInt()         CLR_REG_BIT(I2C2MSCR, I2C2MSCR_EMSI_MSK)

#define I2C2SLCR_ESTAI_MSK              BIT6
#define I2C2SLCR_ERXI_MSK               BIT5
#define I2C2SLCR_ETXI_MSK               BIT4
#define I2C2SLCR_ESTOI_MSK              BIT3
#define I2C2_EnableSlaveSTAInt()        SET_REG_BIT(I2C2SLCR, I2C2SLCR_ESTAI_MSK)
#define I2C2_EnableSlaveSTOInt()        SET_REG_BIT(I2C2SLCR, I2C2SLCR_ESTOI_MSK)
#define I2C2_EnableSlaveRXInt()         SET_REG_BIT(I2C2SLCR, I2C2SLCR_ERXI_MSK)
#define I2C2_EnableSlaveTXInt()         SET_REG_BIT(I2C2SLCR, I2C2SLCR_ETXI_MSK)
#define I2C2_EnableSlaveAllInt()        SET_REG_BIT(I2C2SLCR, I2C2SLCR_ESTAI_MSK | I2C2SLCR_ESTOI_MSK | I2C2SLCR_ERXI_MSK | I2C2SLCR_ETXI_MSK)
#define I2C2_DisableSlaveSTAInt()       CLR_REG_BIT(I2C2SLCR, I2C2SLCR_ESTAI_MSK)
#define I2C2_DisableSlaveSTOInt()       CLR_REG_BIT(I2C2SLCR, I2C2SLCR_ESTOI_MSK)
#define I2C2_DisableSlaveRXInt()        CLR_REG_BIT(I2C2SLCR, I2C2SLCR_ERXI_MSK)
#define I2C2_DisableSlaveTXInt()        CLR_REG_BIT(I2C2SLCR, I2C2SLCR_ETXI_MSK)
#define I2C2_DisableSlaveAllInt()       CLR_REG_BIT(I2C2SLCR, I2C2SLCR_ESTAI_MSK | I2C2SLCR_ESTOI_MSK | I2C2SLCR_ERXI_MSK | I2C2SLCR_ETXI_MSK)

#define PWMAIER_BIE_MSK                 BIT7
#define PWMAIER_TIE_MSK                 BIT6
#define PWMAIER_COMIE_MSK               BIT5
#define PWMAIER_CC4IE_MSK               BIT4
#define PWMAIER_CC3IE_MSK               BIT3
#define PWMAIER_CC2IE_MSK               BIT2
#define PWMAIER_CC1IE_MSK               BIT1
#define PWMAIER_UIE_MSK                 BIT0
#define PWMA_EnableBreakInt()           SET_REG_BIT(PWMA_IER, PWMAIER_BIE_MSK)
#define PWMA_EnableTriggerInt()         SET_REG_BIT(PWMA_IER, PWMAIER_TIE_MSK)
#define PWMA_EnableCOMInt()             SET_REG_BIT(PWMA_IER, PWMAIER_COMIE_MSK)
#define PWMA_EnableCC4Int()             SET_REG_BIT(PWMA_IER, PWMAIER_CC4IE_MSK)
#define PWMA_EnableCC3Int()             SET_REG_BIT(PWMA_IER, PWMAIER_CC3IE_MSK)
#define PWMA_EnableCC2Int()             SET_REG_BIT(PWMA_IER, PWMAIER_CC2IE_MSK)
#define PWMA_EnableCC1Int()             SET_REG_BIT(PWMA_IER, PWMAIER_CC1IE_MSK)
#define PWMA_EnableUpdateInt()          SET_REG_BIT(PWMA_IER, PWMAIER_UIE_MSK)
#define PWMA_DisableBreakInt()          CLR_REG_BIT(PWMA_IER, PWMAIER_BIE_MSK)
#define PWMA_DisableTriggerInt()        CLR_REG_BIT(PWMA_IER, PWMAIER_TIE_MSK)
#define PWMA_DisableCOMInt()            CLR_REG_BIT(PWMA_IER, PWMAIER_COMIE_MSK)
#define PWMA_DisableCC4Int()            CLR_REG_BIT(PWMA_IER, PWMAIER_CC4IE_MSK)
#define PWMA_DisableCC3Int()            CLR_REG_BIT(PWMA_IER, PWMAIER_CC3IE_MSK)
#define PWMA_DisableCC2Int()            CLR_REG_BIT(PWMA_IER, PWMAIER_CC2IE_MSK)
#define PWMA_DisableCC1Int()            CLR_REG_BIT(PWMA_IER, PWMAIER_CC1IE_MSK)
#define PWMA_DisableUpdateInt()         CLR_REG_BIT(PWMA_IER, PWMAIER_UIE_MSK)

#define HSPWMA_EnableBreakInt()         SET_HSPWMA_BIT(PWMA_IER, PWMAIER_BIE_MSK)
#define HSPWMA_EnableTriggerInt()       SET_HSPWMA_BIT(PWMA_IER, PWMAIER_TIE_MSK)
#define HSPWMA_EnableCOMInt()           SET_HSPWMA_BIT(PWMA_IER, PWMAIER_COMIE_MSK)
#define HSPWMA_EnableCC4Int()           SET_HSPWMA_BIT(PWMA_IER, PWMAIER_CC4IE_MSK)
#define HSPWMA_EnableCC3Int()           SET_HSPWMA_BIT(PWMA_IER, PWMAIER_CC3IE_MSK)
#define HSPWMA_EnableCC2Int()           SET_HSPWMA_BIT(PWMA_IER, PWMAIER_CC2IE_MSK)
#define HSPWMA_EnableCC1Int()           SET_HSPWMA_BIT(PWMA_IER, PWMAIER_CC1IE_MSK)
#define HSPWMA_EnableUpdateInt()        SET_HSPWMA_BIT(PWMA_IER, PWMAIER_UIE_MSK)
#define HSPWMA_DisableBreakInt()        CLR_HSPWMA_BIT(PWMA_IER, PWMAIER_BIE_MSK)
#define HSPWMA_DisableTriggerInt()      CLR_HSPWMA_BIT(PWMA_IER, PWMAIER_TIE_MSK)
#define HSPWMA_DisableCOMInt()          CLR_HSPWMA_BIT(PWMA_IER, PWMAIER_COMIE_MSK)
#define HSPWMA_DisableCC4Int()          CLR_HSPWMA_BIT(PWMA_IER, PWMAIER_CC4IE_MSK)
#define HSPWMA_DisableCC3Int()          CLR_HSPWMA_BIT(PWMA_IER, PWMAIER_CC3IE_MSK)
#define HSPWMA_DisableCC2Int()          CLR_HSPWMA_BIT(PWMA_IER, PWMAIER_CC2IE_MSK)
#define HSPWMA_DisableCC1Int()          CLR_HSPWMA_BIT(PWMA_IER, PWMAIER_CC1IE_MSK)
#define HSPWMA_DisableUpdateInt()       CLR_HSPWMA_BIT(PWMA_IER, PWMAIER_UIE_MSK)

#define PWMBIER_BIE_MSK                 BIT7
#define PWMBIER_TIE_MSK                 BIT6
#define PWMBIER_COMIE_MSK               BIT5
#define PWMBIER_CC8IE_MSK               BIT4
#define PWMBIER_CC7IE_MSK               BIT3
#define PWMBIER_CC6IE_MSK               BIT2
#define PWMBIER_CC5IE_MSK               BIT1
#define PWMBIER_UIE_MSK                 BIT0
#define PWMB_EnableBreakInt()           SET_REG_BIT(PWMB_IER, PWMBIER_BIE_MSK)
#define PWMB_EnableTriggerInt()         SET_REG_BIT(PWMB_IER, PWMBIER_TIE_MSK)
#define PWMB_EnableCOMInt()             SET_REG_BIT(PWMB_IER, PWMBIER_COMIE_MSK)
#define PWMB_EnableCC8Int()             SET_REG_BIT(PWMB_IER, PWMBIER_CC8IE_MSK)
#define PWMB_EnableCC7Int()             SET_REG_BIT(PWMB_IER, PWMBIER_CC7IE_MSK)
#define PWMB_EnableCC6Int()             SET_REG_BIT(PWMB_IER, PWMBIER_CC6IE_MSK)
#define PWMB_EnableCC5Int()             SET_REG_BIT(PWMB_IER, PWMBIER_CC5IE_MSK)
#define PWMB_EnableUpdateInt()          SET_REG_BIT(PWMB_IER, PWMBIER_UIE_MSK)
#define PWMB_DisableBreakInt()          CLR_REG_BIT(PWMB_IER, PWMBIER_BIE_MSK)
#define PWMB_DisableTriggerInt()        CLR_REG_BIT(PWMB_IER, PWMBIER_TIE_MSK)
#define PWMB_DisableCOMInt()            CLR_REG_BIT(PWMB_IER, PWMBIER_COMIE_MSK)
#define PWMB_DisableCC8Int()            CLR_REG_BIT(PWMB_IER, PWMBIER_CC8IE_MSK)
#define PWMB_DisableCC7Int()            CLR_REG_BIT(PWMB_IER, PWMBIER_CC7IE_MSK)
#define PWMB_DisableCC6Int()            CLR_REG_BIT(PWMB_IER, PWMBIER_CC6IE_MSK)
#define PWMB_DisableCC5Int()            CLR_REG_BIT(PWMB_IER, PWMBIER_CC5IE_MSK)
#define PWMB_DisableUpdateInt()         CLR_REG_BIT(PWMB_IER, PWMBIER_UIE_MSK)

#define HSPWMB_EnableBreakInt()         SET_HSPWMB_BIT(PWMB_IER, PWMBIER_BIE_MSK)
#define HSPWMB_EnableTriggerInt()       SET_HSPWMB_BIT(PWMB_IER, PWMBIER_TIE_MSK)
#define HSPWMB_EnableCOMInt()           SET_HSPWMB_BIT(PWMB_IER, PWMBIER_COMIE_MSK)
#define HSPWMB_EnableCC8Int()           SET_HSPWMB_BIT(PWMB_IER, PWMBIER_CC8IE_MSK)
#define HSPWMB_EnableCC7Int()           SET_HSPWMB_BIT(PWMB_IER, PWMBIER_CC7IE_MSK)
#define HSPWMB_EnableCC6Int()           SET_HSPWMB_BIT(PWMB_IER, PWMBIER_CC6IE_MSK)
#define HSPWMB_EnableCC5Int()           SET_HSPWMB_BIT(PWMB_IER, PWMBIER_CC5IE_MSK)
#define HSPWMB_EnableUpdateInt()        SET_HSPWMB_BIT(PWMB_IER, PWMBIER_UIE_MSK)
#define HSPWMB_DisableBreakInt()        CLR_HSPWMB_BIT(PWMB_IER, PWMBIER_BIE_MSK)
#define HSPWMB_DisableTriggerInt()      CLR_HSPWMB_BIT(PWMB_IER, PWMBIER_TIE_MSK)
#define HSPWMB_DisableCOMInt()          CLR_HSPWMB_BIT(PWMB_IER, PWMBIER_COMIE_MSK)
#define HSPWMB_DisableCC8Int()          CLR_HSPWMB_BIT(PWMB_IER, PWMBIER_CC8IE_MSK)
#define HSPWMB_DisableCC7Int()          CLR_HSPWMB_BIT(PWMB_IER, PWMBIER_CC7IE_MSK)
#define HSPWMB_DisableCC6Int()          CLR_HSPWMB_BIT(PWMB_IER, PWMBIER_CC6IE_MSK)
#define HSPWMB_DisableCC5Int()          CLR_HSPWMB_BIT(PWMB_IER, PWMBIER_CC5IE_MSK)
#define HSPWMB_DisableUpdateInt()       CLR_HSPWMB_BIT(PWMB_IER, PWMBIER_UIE_MSK)

#define PWMCIER_BIE_MSK                 BIT7
#define PWMCIER_TIE_MSK                 BIT6
#define PWMCIER_COMIE_MSK               BIT5
#define PWMCIER_CC4IE_MSK               BIT4
#define PWMCIER_CC3IE_MSK               BIT3
#define PWMCIER_CC2IE_MSK               BIT2
#define PWMCIER_CC1IE_MSK               BIT1
#define PWMCIER_UIE_MSK                 BIT0
#define PWMC_EnableBreakInt()           SET_REG_BIT(PWMC_IER, PWMCIER_BIE_MSK)
#define PWMC_EnableTriggerInt()         SET_REG_BIT(PWMC_IER, PWMCIER_TIE_MSK)
#define PWMC_EnableCOMInt()             SET_REG_BIT(PWMC_IER, PWMCIER_COMIE_MSK)
#define PWMC_EnableCC4Int()             SET_REG_BIT(PWMC_IER, PWMCIER_CC4IE_MSK)
#define PWMC_EnableCC3Int()             SET_REG_BIT(PWMC_IER, PWMCIER_CC3IE_MSK)
#define PWMC_EnableCC2Int()             SET_REG_BIT(PWMC_IER, PWMCIER_CC2IE_MSK)
#define PWMC_EnableCC1Int()             SET_REG_BIT(PWMC_IER, PWMCIER_CC1IE_MSK)
#define PWMC_EnableUpdateInt()          SET_REG_BIT(PWMC_IER, PWMCIER_UIE_MSK)
#define PWMC_DisableBreakInt()          CLR_REG_BIT(PWMC_IER, PWMCIER_BIE_MSK)
#define PWMC_DisableTriggerInt()        CLR_REG_BIT(PWMC_IER, PWMCIER_TIE_MSK)
#define PWMC_DisableCOMInt()            CLR_REG_BIT(PWMC_IER, PWMCIER_COMIE_MSK)
#define PWMC_DisableCC4Int()            CLR_REG_BIT(PWMC_IER, PWMCIER_CC4IE_MSK)
#define PWMC_DisableCC3Int()            CLR_REG_BIT(PWMC_IER, PWMCIER_CC3IE_MSK)
#define PWMC_DisableCC2Int()            CLR_REG_BIT(PWMC_IER, PWMCIER_CC2IE_MSK)
#define PWMC_DisableCC1Int()            CLR_REG_BIT(PWMC_IER, PWMCIER_CC1IE_MSK)
#define PWMC_DisableUpdateInt()         CLR_REG_BIT(PWMC_IER, PWMCIER_UIE_MSK)

#define HSPWMC_EnableBreakInt()         SET_HSPWMC_BIT(PWMC_IER, PWMCIER_BIE_MSK)
#define HSPWMC_EnableTriggerInt()       SET_HSPWMC_BIT(PWMC_IER, PWMCIER_TIE_MSK)
#define HSPWMC_EnableCOMInt()           SET_HSPWMC_BIT(PWMC_IER, PWMCIER_COMIE_MSK)
#define HSPWMC_EnableCC4Int()           SET_HSPWMC_BIT(PWMC_IER, PWMCIER_CC4IE_MSK)
#define HSPWMC_EnableCC3Int()           SET_HSPWMC_BIT(PWMC_IER, PWMCIER_CC3IE_MSK)
#define HSPWMC_EnableCC2Int()           SET_HSPWMC_BIT(PWMC_IER, PWMCIER_CC2IE_MSK)
#define HSPWMC_EnableCC1Int()           SET_HSPWMC_BIT(PWMC_IER, PWMCIER_CC1IE_MSK)
#define HSPWMC_EnableUpdateInt()        SET_HSPWMC_BIT(PWMC_IER, PWMCIER_UIE_MSK)
#define HSPWMC_DisableBreakInt()        CLR_HSPWMC_BIT(PWMC_IER, PWMCIER_BIE_MSK)
#define HSPWMC_DisableTriggerInt()      CLR_HSPWMC_BIT(PWMC_IER, PWMCIER_TIE_MSK)
#define HSPWMC_DisableCOMInt()          CLR_HSPWMC_BIT(PWMC_IER, PWMCIER_COMIE_MSK)
#define HSPWMC_DisableCC4Int()          CLR_HSPWMC_BIT(PWMC_IER, PWMCIER_CC4IE_MSK)
#define HSPWMC_DisableCC3Int()          CLR_HSPWMC_BIT(PWMC_IER, PWMCIER_CC3IE_MSK)
#define HSPWMC_DisableCC2Int()          CLR_HSPWMC_BIT(PWMC_IER, PWMCIER_CC2IE_MSK)
#define HSPWMC_DisableCC1Int()          CLR_HSPWMC_BIT(PWMC_IER, PWMCIER_CC1IE_MSK)
#define HSPWMC_DisableUpdateInt()       CLR_HSPWMC_BIT(PWMC_IER, PWMCIER_UIE_MSK)

#define PWMDIER_BIE_MSK                 BIT7
#define PWMDIER_TIE_MSK                 BIT6
#define PWMDIER_COMIE_MSK               BIT5
#define PWMDIER_CC8IE_MSK               BIT4
#define PWMDIER_CC7IE_MSK               BIT3
#define PWMDIER_CC6IE_MSK               BIT2
#define PWMDIER_CC5IE_MSK               BIT1
#define PWMDIER_UIE_MSK                 BIT0
#define PWMD_EnableBreakInt()           SET_REG_BIT(PWMD_IER, PWMDIER_BIE_MSK)
#define PWMD_EnableTriggerInt()         SET_REG_BIT(PWMD_IER, PWMDIER_TIE_MSK)
#define PWMD_EnableCOMInt()             SET_REG_BIT(PWMD_IER, PWMDIER_COMIE_MSK)
#define PWMD_EnableCC8Int()             SET_REG_BIT(PWMD_IER, PWMDIER_CC8IE_MSK)
#define PWMD_EnableCC7Int()             SET_REG_BIT(PWMD_IER, PWMDIER_CC7IE_MSK)
#define PWMD_EnableCC6Int()             SET_REG_BIT(PWMD_IER, PWMDIER_CC6IE_MSK)
#define PWMD_EnableCC5Int()             SET_REG_BIT(PWMD_IER, PWMDIER_CC5IE_MSK)
#define PWMD_EnableUpdateInt()          SET_REG_BIT(PWMD_IER, PWMDIER_UIE_MSK)
#define PWMD_DisableBreakInt()          CLR_REG_BIT(PWMD_IER, PWMDIER_BIE_MSK)
#define PWMD_DisableTriggerInt()        CLR_REG_BIT(PWMD_IER, PWMDIER_TIE_MSK)
#define PWMD_DisableCOMInt()            CLR_REG_BIT(PWMD_IER, PWMDIER_COMIE_MSK)
#define PWMD_DisableCC8Int()            CLR_REG_BIT(PWMD_IER, PWMDIER_CC8IE_MSK)
#define PWMD_DisableCC7Int()            CLR_REG_BIT(PWMD_IER, PWMDIER_CC7IE_MSK)
#define PWMD_DisableCC6Int()            CLR_REG_BIT(PWMD_IER, PWMDIER_CC6IE_MSK)
#define PWMD_DisableCC5Int()            CLR_REG_BIT(PWMD_IER, PWMDIER_CC5IE_MSK)
#define PWMD_DisableUpdateInt()         CLR_REG_BIT(PWMD_IER, PWMDIER_UIE_MSK)

#define HSPWMD_EnableBreakInt()         SET_HSPWMD_BIT(PWMD_IER, PWMDIER_BIE_MSK)
#define HSPWMD_EnableTriggerInt()       SET_HSPWMD_BIT(PWMD_IER, PWMDIER_TIE_MSK)
#define HSPWMD_EnableCOMInt()           SET_HSPWMD_BIT(PWMD_IER, PWMDIER_COMIE_MSK)
#define HSPWMD_EnableCC8Int()           SET_HSPWMD_BIT(PWMD_IER, PWMDIER_CC8IE_MSK)
#define HSPWMD_EnableCC7Int()           SET_HSPWMD_BIT(PWMD_IER, PWMDIER_CC7IE_MSK)
#define HSPWMD_EnableCC6Int()           SET_HSPWMD_BIT(PWMD_IER, PWMDIER_CC6IE_MSK)
#define HSPWMD_EnableCC5Int()           SET_HSPWMD_BIT(PWMD_IER, PWMDIER_CC5IE_MSK)
#define HSPWMD_EnableUpdateInt()        SET_HSPWMD_BIT(PWMD_IER, PWMDIER_UIE_MSK)
#define HSPWMD_DisableBreakInt()        CLR_HSPWMD_BIT(PWMD_IER, PWMDIER_BIE_MSK)
#define HSPWMD_DisableTriggerInt()      CLR_HSPWMD_BIT(PWMD_IER, PWMDIER_TIE_MSK)
#define HSPWMD_DisableCOMInt()          CLR_HSPWMD_BIT(PWMD_IER, PWMDIER_COMIE_MSK)
#define HSPWMD_DisableCC8Int()          CLR_HSPWMD_BIT(PWMD_IER, PWMDIER_CC8IE_MSK)
#define HSPWMD_DisableCC7Int()          CLR_HSPWMD_BIT(PWMD_IER, PWMDIER_CC7IE_MSK)
#define HSPWMD_DisableCC6Int()          CLR_HSPWMD_BIT(PWMD_IER, PWMDIER_CC6IE_MSK)
#define HSPWMD_DisableCC5Int()          CLR_HSPWMD_BIT(PWMD_IER, PWMDIER_CC5IE_MSK)
#define HSPWMD_DisableUpdateInt()       CLR_HSPWMD_BIT(PWMD_IER, PWMDIER_UIE_MSK)

#define PWMEIER_BIE_MSK                 BIT7
#define PWMEIER_TIE_MSK                 BIT6
#define PWMEIER_COMIE_MSK               BIT5
#define PWMEIER_CC4IE_MSK               BIT4
#define PWMEIER_CC3IE_MSK               BIT3
#define PWMEIER_CC2IE_MSK               BIT2
#define PWMEIER_CC1IE_MSK               BIT1
#define PWMEIER_UIE_MSK                 BIT0
#define PWME_EnableBreakInt()           SET_REG_BIT(PWME_IER, PWMEIER_BIE_MSK)
#define PWME_EnableTriggerInt()         SET_REG_BIT(PWME_IER, PWMEIER_TIE_MSK)
#define PWME_EnableCOMInt()             SET_REG_BIT(PWME_IER, PWMEIER_COMIE_MSK)
#define PWME_EnableCC4Int()             SET_REG_BIT(PWME_IER, PWMEIER_CC4IE_MSK)
#define PWME_EnableCC3Int()             SET_REG_BIT(PWME_IER, PWMEIER_CC3IE_MSK)
#define PWME_EnableCC2Int()             SET_REG_BIT(PWME_IER, PWMEIER_CC2IE_MSK)
#define PWME_EnableCC1Int()             SET_REG_BIT(PWME_IER, PWMEIER_CC1IE_MSK)
#define PWME_EnableUpdateInt()          SET_REG_BIT(PWME_IER, PWMEIER_UIE_MSK)
#define PWME_DisableBreakInt()          CLR_REG_BIT(PWME_IER, PWMEIER_BIE_MSK)
#define PWME_DisableTriggerInt()        CLR_REG_BIT(PWME_IER, PWMEIER_TIE_MSK)
#define PWME_DisableCOMInt()            CLR_REG_BIT(PWME_IER, PWMEIER_COMIE_MSK)
#define PWME_DisableCC4Int()            CLR_REG_BIT(PWME_IER, PWMEIER_CC4IE_MSK)
#define PWME_DisableCC3Int()            CLR_REG_BIT(PWME_IER, PWMEIER_CC3IE_MSK)
#define PWME_DisableCC2Int()            CLR_REG_BIT(PWME_IER, PWMEIER_CC2IE_MSK)
#define PWME_DisableCC1Int()            CLR_REG_BIT(PWME_IER, PWMEIER_CC1IE_MSK)
#define PWME_DisableUpdateInt()         CLR_REG_BIT(PWME_IER, PWMEIER_UIE_MSK)

#define HSPWME_EnableBreakInt()         SET_HSPWME_BIT(PWME_IER, PWMEIER_BIE_MSK)
#define HSPWME_EnableTriggerInt()       SET_HSPWME_BIT(PWME_IER, PWMEIER_TIE_MSK)
#define HSPWME_EnableCOMInt()           SET_HSPWME_BIT(PWME_IER, PWMEIER_COMIE_MSK)
#define HSPWME_EnableCC4Int()           SET_HSPWME_BIT(PWME_IER, PWMEIER_CC4IE_MSK)
#define HSPWME_EnableCC3Int()           SET_HSPWME_BIT(PWME_IER, PWMEIER_CC3IE_MSK)
#define HSPWME_EnableCC2Int()           SET_HSPWME_BIT(PWME_IER, PWMEIER_CC2IE_MSK)
#define HSPWME_EnableCC1Int()           SET_HSPWME_BIT(PWME_IER, PWMEIER_CC1IE_MSK)
#define HSPWME_EnableUpdateInt()        SET_HSPWME_BIT(PWME_IER, PWMEIER_UIE_MSK)
#define HSPWME_DisableBreakInt()        CLR_HSPWME_BIT(PWME_IER, PWMEIER_BIE_MSK)
#define HSPWME_DisableTriggerInt()      CLR_HSPWME_BIT(PWME_IER, PWMEIER_TIE_MSK)
#define HSPWME_DisableCOMInt()          CLR_HSPWME_BIT(PWME_IER, PWMEIER_COMIE_MSK)
#define HSPWME_DisableCC4Int()          CLR_HSPWME_BIT(PWME_IER, PWMEIER_CC4IE_MSK)
#define HSPWME_DisableCC3Int()          CLR_HSPWME_BIT(PWME_IER, PWMEIER_CC3IE_MSK)
#define HSPWME_DisableCC2Int()          CLR_HSPWME_BIT(PWME_IER, PWMEIER_CC2IE_MSK)
#define HSPWME_DisableCC1Int()          CLR_HSPWME_BIT(PWME_IER, PWMEIER_CC1IE_MSK)
#define HSPWME_DisableUpdateInt()       CLR_HSPWME_BIT(PWME_IER, PWMEIER_UIE_MSK)

#define PWMFIER_BIE_MSK                 BIT7
#define PWMFIER_TIE_MSK                 BIT6
#define PWMFIER_COMIE_MSK               BIT5
#define PWMFIER_CC8IE_MSK               BIT4
#define PWMFIER_CC7IE_MSK               BIT3
#define PWMFIER_CC6IE_MSK               BIT2
#define PWMFIER_CC5IE_MSK               BIT1
#define PWMFIER_UIE_MSK                 BIT0
#define PWMF_EnableBreakInt()           SET_REG_BIT(PWMF_IER, PWMFIER_BIE_MSK)
#define PWMF_EnableTriggerInt()         SET_REG_BIT(PWMF_IER, PWMFIER_TIE_MSK)
#define PWMF_EnableCOMInt()             SET_REG_BIT(PWMF_IER, PWMFIER_COMIE_MSK)
#define PWMF_EnableCC8Int()             SET_REG_BIT(PWMF_IER, PWMFIER_CC8IE_MSK)
#define PWMF_EnableCC7Int()             SET_REG_BIT(PWMF_IER, PWMFIER_CC7IE_MSK)
#define PWMF_EnableCC6Int()             SET_REG_BIT(PWMF_IER, PWMFIER_CC6IE_MSK)
#define PWMF_EnableCC5Int()             SET_REG_BIT(PWMF_IER, PWMFIER_CC5IE_MSK)
#define PWMF_EnableUpdateInt()          SET_REG_BIT(PWMF_IER, PWMFIER_UIE_MSK)
#define PWMF_DisableBreakInt()          CLR_REG_BIT(PWMF_IER, PWMFIER_BIE_MSK)
#define PWMF_DisableTriggerInt()        CLR_REG_BIT(PWMF_IER, PWMFIER_TIE_MSK)
#define PWMF_DisableCOMInt()            CLR_REG_BIT(PWMF_IER, PWMFIER_COMIE_MSK)
#define PWMF_DisableCC8Int()            CLR_REG_BIT(PWMF_IER, PWMFIER_CC8IE_MSK)
#define PWMF_DisableCC7Int()            CLR_REG_BIT(PWMF_IER, PWMFIER_CC7IE_MSK)
#define PWMF_DisableCC6Int()            CLR_REG_BIT(PWMF_IER, PWMFIER_CC6IE_MSK)
#define PWMF_DisableCC5Int()            CLR_REG_BIT(PWMF_IER, PWMFIER_CC5IE_MSK)
#define PWMF_DisableUpdateInt()         CLR_REG_BIT(PWMF_IER, PWMFIER_UIE_MSK)

#define HSPWMF_EnableBreakInt()         SET_HSPWMF_BIT(PWMF_IER, PWMFIER_BIE_MSK)
#define HSPWMF_EnableTriggerInt()       SET_HSPWMF_BIT(PWMF_IER, PWMFIER_TIE_MSK)
#define HSPWMF_EnableCOMInt()           SET_HSPWMF_BIT(PWMF_IER, PWMFIER_COMIE_MSK)
#define HSPWMF_EnableCC8Int()           SET_HSPWMF_BIT(PWMF_IER, PWMFIER_CC8IE_MSK)
#define HSPWMF_EnableCC7Int()           SET_HSPWMF_BIT(PWMF_IER, PWMFIER_CC7IE_MSK)
#define HSPWMF_EnableCC6Int()           SET_HSPWMF_BIT(PWMF_IER, PWMFIER_CC6IE_MSK)
#define HSPWMF_EnableCC5Int()           SET_HSPWMF_BIT(PWMF_IER, PWMFIER_CC5IE_MSK)
#define HSPWMF_EnableUpdateInt()        SET_HSPWMF_BIT(PWMF_IER, PWMFIER_UIE_MSK)
#define HSPWMF_DisableBreakInt()        CLR_HSPWMF_BIT(PWMF_IER, PWMFIER_BIE_MSK)
#define HSPWMF_DisableTriggerInt()      CLR_HSPWMF_BIT(PWMF_IER, PWMFIER_TIE_MSK)
#define HSPWMF_DisableCOMInt()          CLR_HSPWMF_BIT(PWMF_IER, PWMFIER_COMIE_MSK)
#define HSPWMF_DisableCC8Int()          CLR_HSPWMF_BIT(PWMF_IER, PWMFIER_CC8IE_MSK)
#define HSPWMF_DisableCC7Int()          CLR_HSPWMF_BIT(PWMF_IER, PWMFIER_CC7IE_MSK)
#define HSPWMF_DisableCC6Int()          CLR_HSPWMF_BIT(PWMF_IER, PWMFIER_CC6IE_MSK)
#define HSPWMF_DisableCC5Int()          CLR_HSPWMF_BIT(PWMF_IER, PWMFIER_CC5IE_MSK)
#define HSPWMF_DisableUpdateInt()       CLR_HSPWMF_BIT(PWMF_IER, PWMFIER_UIE_MSK)

#define PORT_EnableInt(p, b)            SET_REG_BIT(P##p##INTE, (b))
#define PORT_DisableInt(p, b)           CLR_REG_BIT(P##p##INTE, (b))

#define EnableP0nInt(b)                 PORT_EnableInt(0, (b))
#define EnableP1nInt(b)                 PORT_EnableInt(1, (b))
#define EnableP2nInt(b)                 PORT_EnableInt(2, (b))
#define EnableP3nInt(b)                 PORT_EnableInt(3, (b))
#define EnableP4nInt(b)                 PORT_EnableInt(4, (b))
#define EnableP5nInt(b)                 PORT_EnableInt(5, (b))
#define EnableP6nInt(b)                 PORT_EnableInt(6, (b))
#define EnableP7nInt(b)                 PORT_EnableInt(7, (b))
#define EnableP8nInt(b)                 PORT_EnableInt(8, (b))
#define EnableP9nInt(b)                 PORT_EnableInt(9, (b))
#define EnablePAnInt(b)                 PORT_EnableInt(A, (b))
#define EnablePBnInt(b)                 PORT_EnableInt(B, (b))

#define DisableP0nInt(b)                PORT_DisableInt(0, (b))
#define DisableP1nInt(b)                PORT_DisableInt(1, (b))
#define DisableP2nInt(b)                PORT_DisableInt(2, (b))
#define DisableP3nInt(b)                PORT_DisableInt(3, (b))
#define DisableP4nInt(b)                PORT_DisableInt(4, (b))
#define DisableP5nInt(b)                PORT_DisableInt(5, (b))
#define DisableP6nInt(b)                PORT_DisableInt(6, (b))
#define DisableP7nInt(b)                PORT_DisableInt(7, (b))
#define DisableP8nInt(b)                PORT_DisableInt(8, (b))
#define DisableP9nInt(b)                PORT_DisableInt(9, (b))
#define DisablePAnInt(b)                PORT_DisableInt(A, (b))
#define DisablePBnInt(b)                PORT_DisableInt(B, (b))

#define UR1TOCR_ENTOI_MSK               BIT6
#define UART1_EnableTimeoutInt()        SET_REG_BIT(UR1TOCR, UR1TOCR_ENTOI_MSK)
#define UART1_DisableTimeoutInt()       CLR_REG_BIT(UR1TOCR, UR1TOCR_ENTOI_MSK)

#define UR2TOCR_ENTOI_MSK               BIT6
#define UART2_EnableTimeoutInt()        SET_REG_BIT(UR2TOCR, UR2TOCR_ENTOI_MSK)
#define UART2_DisableTimeoutInt()       CLR_REG_BIT(UR2TOCR, UR2TOCR_ENTOI_MSK)

#define UR3TOCR_ENTOI_MSK               BIT6
#define UART3_EnableTimeoutInt()        SET_REG_BIT(UR3TOCR, UR3TOCR_ENTOI_MSK)
#define UART3_DisableTimeoutInt()       CLR_REG_BIT(UR3TOCR, UR3TOCR_ENTOI_MSK)

#define UR4TOCR_ENTOI_MSK               BIT6
#define UART4_EnableTimeoutInt()        SET_REG_BIT(UR4TOCR, UR4TOCR_ENTOI_MSK)
#define UART4_DisableTimeoutInt()       CLR_REG_BIT(UR4TOCR, UR4TOCR_ENTOI_MSK)

#define UR5TOCR_ENTOI_MSK               BIT6
#define UART5_EnableTimeoutInt()        SET_REG_BIT(UR5TOCR, UR5TOCR_ENTOI_MSK)
#define UART5_DisableTimeoutInt()       CLR_REG_BIT(UR5TOCR, UR5TOCR_ENTOI_MSK)

#define UR6TOCR_ENTOI_MSK               BIT6
#define UART6_EnableTimeoutInt()        SET_REG_BIT(UR6TOCR, UR6TOCR_ENTOI_MSK)
#define UART6_DisableTimeoutInt()       CLR_REG_BIT(UR6TOCR, UR6TOCR_ENTOI_MSK)

#define UR7TOCR_ENTOI_MSK               BIT6
#define UART7_EnableTimeoutInt()        SET_REG_BIT(UR7TOCR, UR7TOCR_ENTOI_MSK)
#define UART7_DisableTimeoutInt()       CLR_REG_BIT(UR7TOCR, UR7TOCR_ENTOI_MSK)

#define UR8TOCR_ENTOI_MSK               BIT6
#define UART8_EnableTimeoutInt()        SET_REG_BIT(UR8TOCR, UR8TOCR_ENTOI_MSK)
#define UART8_DisableTimeoutInt()       CLR_REG_BIT(UR8TOCR, UR8TOCR_ENTOI_MSK)

#define SPITOCR_ENTOI_MSK               BIT6
#define SPI1_EnableTimeoutInt()         SET_REG_BIT(SPITOCR, SPITOCR_ENTOI_MSK)
#define SPI1_DisableTimeoutInt()        CLR_REG_BIT(SPITOCR, SPITOCR_ENTOI_MSK)

#define SPI2TOCR_ENTOI_MSK              BIT6
#define SPI2_EnableTimeoutInt()         SET_REG_BIT(SPI2TOCR, SPI2TOCR_ENTOI_MSK)
#define SPI2_DisableTimeoutInt()        CLR_REG_BIT(SPI2TOCR, SPI2TOCR_ENTOI_MSK)

#define SPI3TOCR_ENTOI_MSK              BIT6
#define SPI3_EnableTimeoutInt()         SET_REG_BIT(SPI3TOCR, SPI3TOCR_ENTOI_MSK)
#define SPI3_DisableTimeoutInt()        CLR_REG_BIT(SPI3TOCR, SPI3TOCR_ENTOI_MSK)

#define I2CTOCR_ENTOI_MSK               BIT6
#define I2C1_EnableTimeoutInt()         SET_REG_BIT(I2CTOCR, I2CTOCR_ENTOI_MSK)
#define I2C1_DisableTimeoutInt()        CLR_REG_BIT(I2CTOCR, I2CTOCR_ENTOI_MSK)

#define I2C2TOCR_ENTOI_MSK              BIT6
#define I2C2_EnableTimeoutInt()         SET_REG_BIT(I2C2TOCR, I2C2TOCR_ENTOI_MSK)
#define I2C2_DisableTimeoutInt()        CLR_REG_BIT(I2C2TOCR, I2C2TOCR_ENTOI_MSK)

#define I2SCR_TXEIE_MSK                 BIT7
#define I2SCR_RXNEIE_MSK                BIT6
#define I2SCR_ERRIE_MSK                 BIT5
#define I2S1_EnableTXEInt()             SET_REG_BIT(I2SCR, I2SCR_TXEIE_MSK)
#define I2S1_EnableRXNEInt()            SET_REG_BIT(I2SCR, I2SCR_RXNEIE_MSK)
#define I2S1_EnableErrorInt()           SET_REG_BIT(I2SCR, I2SCR_ERRIE_MSK)
#define I2S1_DisableTXEInt()            CLR_REG_BIT(I2SCR, I2SCR_TXEIE_MSK)
#define I2S1_DisableRXNEInt()           CLR_REG_BIT(I2SCR, I2SCR_RXNEIE_MSK)
#define I2S1_DisableErrorInt()          CLR_REG_BIT(I2SCR, I2SCR_ERRIE_MSK)

#define I2S2CR_TXEIE_MSK                BIT7
#define I2S2CR_RXNEIE_MSK               BIT6
#define I2S2CR_ERRIE_MSK                BIT5
#define I2S2_EnableTXEInt()             SET_REG_BIT(I2S2CR, I2S2CR_TXEIE_MSK)
#define I2S2_EnableRXNEInt()            SET_REG_BIT(I2S2CR, I2S2CR_RXNEIE_MSK)
#define I2S2_EnableErrorInt()           SET_REG_BIT(I2S2CR, I2S2CR_ERRIE_MSK)
#define I2S2_DisableTXEInt()            CLR_REG_BIT(I2S2CR, I2S2CR_TXEIE_MSK)
#define I2S2_DisableRXNEInt()           CLR_REG_BIT(I2S2CR, I2S2CR_RXNEIE_MSK)
#define I2S2_DisableErrorInt()          CLR_REG_BIT(I2S2CR, I2S2CR_ERRIE_MSK)

#define QSPICR3_SMIE_MSK                BIT3
#define QSPICR3_FTIE_MSK                BIT2
#define QSPICR3_TCIE_MSK                BIT1
#define QSPICR3_TEIE_MSK                BIT0
#define QSPI_EnableMatchInt()           SET_REG_BIT(QSPI_CR3, QSPICR3_SMIE_MSK)
#define QSPI_EnableFIFOInt()            SET_REG_BIT(QSPI_CR3, QSPICR3_FTIE_MSK)
#define QSPI_EnableTransferInt()        SET_REG_BIT(QSPI_CR3, QSPICR3_TCIE_MSK)
#define QSPI_EnableErrorInt()           SET_REG_BIT(QSPI_CR3, QSPICR3_TEIE_MSK)
#define QSPI_DisableMatchInt()          CLR_REG_BIT(QSPI_CR3, QSPICR3_SMIE_MSK)
#define QSPI_DisableFIFOInt()           CLR_REG_BIT(QSPI_CR3, QSPICR3_FTIE_MSK)
#define QSPI_DisableTransferInt()       CLR_REG_BIT(QSPI_CR3, QSPICR3_TCIE_MSK)
#define QSPI_DisableErrorInt()          CLR_REG_BIT(QSPI_CR3, QSPICR3_TEIE_MSK)

#define DMAM2MCFG_M2MIE_MSK             BIT7
#define DMAADCCFG_ADCIE_MSK             BIT7
#define DMAADC2CFG_ADC2IE_MSK           BIT7
#define DMADAC1CFG_DAC1IE_MSK           BIT7
#define DMADAC2CFG_DAC2IE_MSK           BIT7
#define DMASPICFG_SPIIE_MSK             BIT7
#define DMASPI2CFG_SPI2IE_MSK           BIT7
#define DMASPI3CFG_SPI3IE_MSK           BIT7
#define DMAQSPICFG_QSPIIE_MSK           BIT7
#define DMALCMCFG_LCMIE_MSK             BIT7
#define DMAUR1TCFG_UR1TIE_MSK           BIT7
#define DMAUR1RCFG_UR1RIE_MSK           BIT7
#define DMAUR2TCFG_UR2TIE_MSK           BIT7
#define DMAUR2RCFG_UR2RIE_MSK           BIT7
#define DMAUR3TCFG_UR3TIE_MSK           BIT7
#define DMAUR3RCFG_UR3RIE_MSK           BIT7
#define DMAUR4TCFG_UR4TIE_MSK           BIT7
#define DMAUR4RCFG_UR4RIE_MSK           BIT7
#define DMAUR5TCFG_UR5TIE_MSK           BIT7
#define DMAUR5RCFG_UR5RIE_MSK           BIT7
#define DMAUR6TCFG_UR6TIE_MSK           BIT7
#define DMAUR6RCFG_UR6RIE_MSK           BIT7
#define DMAUR7TCFG_UR7TIE_MSK           BIT7
#define DMAUR7RCFG_UR7RIE_MSK           BIT7
#define DMAUR8TCFG_UR8TIE_MSK           BIT7
#define DMAUR8RCFG_UR8RIE_MSK           BIT7
#define DMAI2CTCFG_I2CTIE_MSK           BIT7
#define DMAI2CRCFG_I2CRIE_MSK           BIT7
#define DMAI2C2TCFG_I2C2TIE_MSK         BIT7
#define DMAI2C2RCFG_I2C2RIE_MSK         BIT7
#define DMAI2STCFG_I2STIE_MSK           BIT7
#define DMAI2SRCFG_I2SRIE_MSK           BIT7
#define DMAI2S2TCFG_I2S2TIE_MSK         BIT7
#define DMAI2S2RCFG_I2S2RIE_MSK         BIT7
#define DMAPWMATCFG_PWMATIE_MSK         BIT7
#define DMAPWMARCFG_PWMARIE_MSK         BIT7
#define DMAPWMCTCFG_PWMCTIE_MSK         BIT7
#define DMAPWMCRCFG_PWMCRIE_MSK         BIT7
#define DMAPWMETCFG_PWMETIE_MSK         BIT7
#define DMAPWMERCFG_PWMERIE_MSK         BIT7
#define DMACAN1TCFG_CAN1TIE_MSK         BIT7
#define DMACAN1RCFG_CAN1RIE_MSK         BIT7
#define DMACAN2TCFG_CAN2TIE_MSK         BIT7
#define DMACAN2RCFG_CAN2RIE_MSK         BIT7
#define DMA_M2M_EnableInt()             SET_REG_BIT(DMA_M2M_CFG,   DMAM2MCFG_M2MIE_MSK)
#define DMA_ADC1_EnableInt()            SET_REG_BIT(DMA_ADC_CFG,   DMAADCCFG_ADCIE_MSK)
#define DMA_ADC2_EnableInt()            SET_REG_BIT(DMA_ADC2_CFG,  DMAADC2CFG_ADC2IE_MSK)
#define DMA_DAC1_EnableInt()            SET_REG_BIT(DMA_DAC1_CFG,  DMADAC1CFG_DAC1IE_MSK)
#define DMA_DAC2_EnableInt()            SET_REG_BIT(DMA_DAC2_CFG,  DMADAC2CFG_DAC2IE_MSK)
#define DMA_SPI1_EnableInt()            SET_REG_BIT(DMA_SPI_CFG,   DMASPICFG_SPIIE_MSK)
#define DMA_SPI2_EnableInt()            SET_REG_BIT(DMA_SPI2_CFG,  DMASPI2CFG_SPI2IE_MSK)
#define DMA_SPI3_EnableInt()            SET_REG_BIT(DMA_SPI3_CFG,  DMASPI3CFG_SPI3IE_MSK)
#define DMA_QSPI_EnableInt()            SET_REG_BIT(DMA_QSPI_CFG,  DMAQSPICFG_QSPIIE_MSK)
#define DMA_LCM_EnableInt()             SET_REG_BIT(DMA_LCM_CFG,   DMALCMCFG_LCMIE_MSK)
#define DMA_UART1_EnableTxInt()         SET_REG_BIT(DMA_UR1T_CFG,  DMAUR1TCFG_UR1TIE_MSK)
#define DMA_UART1_EnableRxInt()         SET_REG_BIT(DMA_UR1R_CFG,  DMAUR1RCFG_UR1RIE_MSK)
#define DMA_UART2_EnableTxInt()         SET_REG_BIT(DMA_UR2T_CFG,  DMAUR2TCFG_UR2TIE_MSK)
#define DMA_UART2_EnableRxInt()         SET_REG_BIT(DMA_UR2R_CFG,  DMAUR2RCFG_UR2RIE_MSK)
#define DMA_UART3_EnableTxInt()         SET_REG_BIT(DMA_UR3T_CFG,  DMAUR3TCFG_UR3TIE_MSK)
#define DMA_UART3_EnableRxInt()         SET_REG_BIT(DMA_UR3R_CFG,  DMAUR3RCFG_UR3RIE_MSK)
#define DMA_UART4_EnableTxInt()         SET_REG_BIT(DMA_UR4T_CFG,  DMAUR4TCFG_UR4TIE_MSK)
#define DMA_UART4_EnableRxInt()         SET_REG_BIT(DMA_UR4R_CFG,  DMAUR4RCFG_UR4RIE_MSK)
#define DMA_UART5_EnableTxInt()         SET_REG_BIT(DMA_UR5T_CFG,  DMAUR5TCFG_UR5TIE_MSK)
#define DMA_UART5_EnableRxInt()         SET_REG_BIT(DMA_UR5R_CFG,  DMAUR5RCFG_UR5RIE_MSK)
#define DMA_UART6_EnableTxInt()         SET_REG_BIT(DMA_UR6T_CFG,  DMAUR6TCFG_UR6TIE_MSK)
#define DMA_UART6_EnableRxInt()         SET_REG_BIT(DMA_UR6R_CFG,  DMAUR6RCFG_UR6RIE_MSK)
#define DMA_UART7_EnableTxInt()         SET_REG_BIT(DMA_UR7T_CFG,  DMAUR7TCFG_UR7TIE_MSK)
#define DMA_UART7_EnableRxInt()         SET_REG_BIT(DMA_UR7R_CFG,  DMAUR7RCFG_UR7RIE_MSK)
#define DMA_UART8_EnableTxInt()         SET_REG_BIT(DMA_UR8T_CFG,  DMAUR8TCFG_UR8TIE_MSK)
#define DMA_UART8_EnableRxInt()         SET_REG_BIT(DMA_UR8R_CFG,  DMAUR8RCFG_UR8RIE_MSK)
#define DMA_I2C1_EnableTxInt()          SET_REG_BIT(DMA_I2CT_CFG,  DMAI2CTCFG_I2CTIE_MSK)
#define DMA_I2C1_EnableRxInt()          SET_REG_BIT(DMA_I2CR_CFG,  DMAI2CRCFG_I2CRIE_MSK)
#define DMA_I2C2_EnableTxInt()          SET_REG_BIT(DMA_I2C2T_CFG, DMAI2C2TCFG_I2C2TIE_MSK)
#define DMA_I2C2_EnableRxInt()          SET_REG_BIT(DMA_I2C2R_CFG, DMAI2C2RCFG_I2C2RIE_MSK)
#define DMA_I2S1_EnableTxInt()          SET_REG_BIT(DMA_I2ST_CFG,  DMAI2STCFG_I2STIE_MSK)
#define DMA_I2S1_EnableRxInt()          SET_REG_BIT(DMA_I2SR_CFG,  DMAI2SRCFG_I2SRIE_MSK)
#define DMA_I2S2_EnableTxInt()          SET_REG_BIT(DMA_I2S2T_CFG, DMAI2S2TCFG_I2S2TIE_MSK)
#define DMA_I2S2_EnableRxInt()          SET_REG_BIT(DMA_I2S2R_CFG, DMAI2S2RCFG_I2S2RIE_MSK)
#define DMA_PWMA_EnableTxInt()          SET_REG_BIT(DMA_PWMAT_CFG, DMAPWMATCFG_PWMATIE_MSK)
#define DMA_PWMA_EnableRxInt()          SET_REG_BIT(DMA_PWMAR_CFG, DMAPWMARCFG_PWMARIE_MSK)
#define DMA_PWMC_EnableTxInt()          SET_REG_BIT(DMA_PWMCT_CFG, DMAPWMCTCFG_PWMCTIE_MSK)
#define DMA_PWMC_EnableRxInt()          SET_REG_BIT(DMA_PWMCR_CFG, DMAPWMCRCFG_PWMCRIE_MSK)
#define DMA_PWME_EnableTxInt()          SET_REG_BIT(DMA_PWMET_CFG, DMAPWMETCFG_PWMETIE_MSK)
#define DMA_PWME_EnableRxInt()          SET_REG_BIT(DMA_PWMER_CFG, DMAPWMERCFG_PWMERIE_MSK)
#define DMA_CAN1_EnableTxInt()          SET_REG_BIT(DMA_CAN1T_CFG, DMACAN1TCFG_CAN1TIE_MSK)
#define DMA_CAN1_EnableRxInt()          SET_REG_BIT(DMA_CAN1R_CFG, DMACAN1RCFG_CAN1RIE_MSK)
#define DMA_CAN2_EnableTxInt()          SET_REG_BIT(DMA_CAN2T_CFG, DMACAN2TCFG_CAN2TIE_MSK)
#define DMA_CAN2_EnableRxInt()          SET_REG_BIT(DMA_CAN2R_CFG, DMACAN2RCFG_CAN2RIE_MSK)
#define DMA_M2M_DisableInt()            CLR_REG_BIT(DMA_M2M_CFG,   DMAM2MCFG_M2MIE_MSK)
#define DMA_ADC1_DisableInt()           CLR_REG_BIT(DMA_ADC_CFG,   DMAADCCFG_ADCIE_MSK)
#define DMA_ADC2_DisableInt()           CLR_REG_BIT(DMA_ADC2_CFG,  DMAADC2CFG_ADC2IE_MSK)
#define DMA_DAC1_DisableInt()           CLR_REG_BIT(DMA_DAC1_CFG,  DMADAC1CFG_DAC1IE_MSK)
#define DMA_DAC2_DisableInt()           CLR_REG_BIT(DMA_DAC2_CFG,  DMADAC2CFG_DAC2IE_MSK)
#define DMA_SPI1_DisableInt()           CLR_REG_BIT(DMA_SPI_CFG,   DMASPICFG_SPIIE_MSK)
#define DMA_SPI2_DisableInt()           CLR_REG_BIT(DMA_SPI2_CFG,  DMASPI2CFG_SPI2IE_MSK)
#define DMA_SPI3_DisableInt()           CLR_REG_BIT(DMA_SPI3_CFG,  DMASPI3CFG_SPI3IE_MSK)
#define DMA_QSPI_DisableInt()           CLR_REG_BIT(DMA_QSPI_CFG,  DMAQSPICFG_QSPIIE_MSK)
#define DMA_LCM_DisableInt()            CLR_REG_BIT(DMA_LCM_CFG,   DMALCMCFG_LCMIE_MSK)
#define DMA_UART1_DisableTxInt()        CLR_REG_BIT(DMA_UR1T_CFG,  DMAUR1TCFG_UR1TIE_MSK)
#define DMA_UART1_DisableRxInt()        CLR_REG_BIT(DMA_UR1R_CFG,  DMAUR1RCFG_UR1RIE_MSK)
#define DMA_UART2_DisableTxInt()        CLR_REG_BIT(DMA_UR2T_CFG,  DMAUR2TCFG_UR2TIE_MSK)
#define DMA_UART2_DisableRxInt()        CLR_REG_BIT(DMA_UR2R_CFG,  DMAUR2RCFG_UR2RIE_MSK)
#define DMA_UART3_DisableTxInt()        CLR_REG_BIT(DMA_UR3T_CFG,  DMAUR3TCFG_UR3TIE_MSK)
#define DMA_UART3_DisableRxInt()        CLR_REG_BIT(DMA_UR3R_CFG,  DMAUR3RCFG_UR3RIE_MSK)
#define DMA_UART4_DisableTxInt()        CLR_REG_BIT(DMA_UR4T_CFG,  DMAUR4TCFG_UR4TIE_MSK)
#define DMA_UART4_DisableRxInt()        CLR_REG_BIT(DMA_UR4R_CFG,  DMAUR4RCFG_UR4RIE_MSK)
#define DMA_UART5_DisableTxInt()        CLR_REG_BIT(DMA_UR5T_CFG,  DMAUR5TCFG_UR5TIE_MSK)
#define DMA_UART5_DisableRxInt()        CLR_REG_BIT(DMA_UR5R_CFG,  DMAUR5RCFG_UR5RIE_MSK)
#define DMA_UART6_DisableTxInt()        CLR_REG_BIT(DMA_UR6T_CFG,  DMAUR6TCFG_UR6TIE_MSK)
#define DMA_UART6_DisableRxInt()        CLR_REG_BIT(DMA_UR6R_CFG,  DMAUR6RCFG_UR6RIE_MSK)
#define DMA_UART7_DisableTxInt()        CLR_REG_BIT(DMA_UR7T_CFG,  DMAUR7TCFG_UR7TIE_MSK)
#define DMA_UART7_DisableRxInt()        CLR_REG_BIT(DMA_UR7R_CFG,  DMAUR7RCFG_UR7RIE_MSK)
#define DMA_UART8_DisableTxInt()        CLR_REG_BIT(DMA_UR8T_CFG,  DMAUR8TCFG_UR8TIE_MSK)
#define DMA_UART8_DisableRxInt()        CLR_REG_BIT(DMA_UR8R_CFG,  DMAUR8RCFG_UR8RIE_MSK)
#define DMA_I2C1_DisableTxInt()         CLR_REG_BIT(DMA_I2CT_CFG,  DMAI2CTCFG_I2CTIE_MSK)
#define DMA_I2C1_DisableRxInt()         CLR_REG_BIT(DMA_I2CR_CFG,  DMAI2CRCFG_I2CRIE_MSK)
#define DMA_I2C2_DisableTxInt()         CLR_REG_BIT(DMA_I2C2T_CFG, DMAI2C2TCFG_I2C2TIE_MSK)
#define DMA_I2C2_DisableRxInt()         CLR_REG_BIT(DMA_I2C2R_CFG, DMAI2C2RCFG_I2C2RIE_MSK)
#define DMA_I2S1_DisableTxInt()         CLR_REG_BIT(DMA_I2ST_CFG,  DMAI2STCFG_I2STIE_MSK)
#define DMA_I2S1_DisableRxInt()         CLR_REG_BIT(DMA_I2SR_CFG,  DMAI2SRCFG_I2SRIE_MSK)
#define DMA_I2S2_DisableTxInt()         CLR_REG_BIT(DMA_I2S2T_CFG, DMAI2S2TCFG_I2S2TIE_MSK)
#define DMA_I2S2_DisableRxInt()         CLR_REG_BIT(DMA_I2S2R_CFG, DMAI2S2RCFG_I2S2RIE_MSK)
#define DMA_PWMA_DisableTxInt()         CLR_REG_BIT(DMA_PWMAT_CFG, DMAPWMATCFG_PWMATIE_MSK)
#define DMA_PWMA_DisableRxInt()         CLR_REG_BIT(DMA_PWMAR_CFG, DMAPWMARCFG_PWMARIE_MSK)
#define DMA_PWMC_DisableTxInt()         CLR_REG_BIT(DMA_PWMCT_CFG, DMAPWMCTCFG_PWMCTIE_MSK)
#define DMA_PWMC_DisableRxInt()         CLR_REG_BIT(DMA_PWMCR_CFG, DMAPWMCRCFG_PWMCRIE_MSK)
#define DMA_PWME_DisableTxInt()         CLR_REG_BIT(DMA_PWMET_CFG, DMAPWMETCFG_PWMETIE_MSK)
#define DMA_PWME_DisableRxInt()         CLR_REG_BIT(DMA_PWMER_CFG, DMAPWMERCFG_PWMERIE_MSK)
#define DMA_CAN1_DisableTxInt()         CLR_REG_BIT(DMA_CAN1T_CFG, DMACAN1TCFG_CAN1TIE_MSK)
#define DMA_CAN1_DisableRxInt()         CLR_REG_BIT(DMA_CAN1R_CFG, DMACAN1RCFG_CAN1RIE_MSK)
#define DMA_CAN2_DisableTxInt()         CLR_REG_BIT(DMA_CAN2T_CFG, DMACAN2TCFG_CAN2TIE_MSK)
#define DMA_CAN2_DisableRxInt()         CLR_REG_BIT(DMA_CAN2R_CFG, DMACAN2RCFG_CAN2RIE_MSK)

#define INT0_FallingRisingInt()         (IT0 = 0)
#define INT0_FallingInt()               (IT0 = 1)

#define INT0_CheckFlag()                (IE0)
#define INT0_ClearFlag()                (IE0 = 0)

#define INT1_FallingRisingInt()         (IT1 = 0)
#define INT1_FallingInt()               (IT1 = 1)

#define INT1_CheckFlag()                (IE1)
#define INT1_ClearFlag()                (IE1 = 0)

#define AUXINTIF_INT2IF_MSK             BIT4
#define INT2_CheckFlag()                READ_REG_BIT(AUXINTIF, AUXINTIF_INT2IF_MSK)
#define INT2_ClearFlag()                CLR_REG_BIT(AUXINTIF, AUXINTIF_INT2IF_MSK)

#define AUXINTIF_INT3IF_MSK             BIT5
#define INT3_CheckFlag()                READ_REG_BIT(AUXINTIF, AUXINTIF_INT3IF_MSK)
#define INT3_ClearFlag()                CLR_REG_BIT(AUXINTIF, AUXINTIF_INT3IF_MSK)

#define AUXINTIF_INT4IF_MSK             BIT6
#define INT4_CheckFlag()                READ_REG_BIT(AUXINTIF, AUXINTIF_INT4IF_MSK)
#define INT4_ClearFlag()                CLR_REG_BIT(AUXINTIF, AUXINTIF_INT4IF_MSK)

#define TIMER0_CheckFlag()              (TF0)
#define TIMER0_ClearFlag()              (TF0 = 0)

#define TIMER1_CheckFlag()              (TF1)
#define TIMER1_ClearFlag()              (TF1 = 0)

#define AUXINTIF_T2IF_MSK               BIT0
#define TIMER2_CheckFlag()              READ_REG_BIT(AUXINTIF, AUXINTIF_T2IF_MSK)
#define TIMER2_ClearFlag()              CLR_REG_BIT(AUXINTIF, AUXINTIF_T2IF_MSK)

#define AUXINTIF_T3IF_MSK               BIT1
#define TIMER3_CheckFlag()              READ_REG_BIT(AUXINTIF, AUXINTIF_T3IF_MSK)
#define TIMER3_ClearFlag()              CLR_REG_BIT(AUXINTIF, AUXINTIF_T3IF_MSK)

#define AUXINTIF_T4IF_MSK               BIT2
#define TIMER4_CheckFlag()              READ_REG_BIT(AUXINTIF, AUXINTIF_T4IF_MSK)
#define TIMER4_ClearFlag()              CLR_REG_BIT(AUXINTIF, AUXINTIF_T4IF_MSK)

#define T6T5CFG_T5IF_MSK                BIT3
#define TIMER5_CheckFlag()              READ_REG_BIT(T6T5CFG, T6T5CFG_T5IF_MSK)
#define TIMER5_ClearFlag()              CLR_REG_BIT(T6T5CFG, T6T5CFG_T5IF_MSK)

#define T6T5CFG_T6IF_MSK                BIT7
#define TIMER6_CheckFlag()              READ_REG_BIT(T6T5CFG, T6T5CFG_T6IF_MSK)
#define TIMER6_ClearFlag()              CLR_REG_BIT(T6T5CFG, T6T5CFG_T6IF_MSK)

#define T8T7CFG_T7IF_MSK                BIT3
#define TIMER7_CheckFlag()              READ_REG_BIT(T8T7CFG, T8T7CFG_T7IF_MSK)
#define TIMER7_ClearFlag()              CLR_REG_BIT(T8T7CFG, T8T7CFG_T7IF_MSK)

#define T8T7CFG_T8IF_MSK                BIT7
#define TIMER8_CheckFlag()              READ_REG_BIT(T8T7CFG, T8T7CFG_T8IF_MSK)
#define TIMER8_ClearFlag()              CLR_REG_BIT(T8T7CFG, T8T7CFG_T8IF_MSK)

#define T10T9CFG_T9IF_MSK               BIT3
#define TIMER9_CheckFlag()              READ_REG_BIT(T10T9CFG, T10T9CFG_T9IF_MSK)
#define TIMER9_ClearFlag()              CLR_REG_BIT(T10T9CFG, T10T9CFG_T9IF_MSK)

#define T10T9CFG_T10IF_MSK              BIT7
#define TIMER10_CheckFlag()             READ_REG_BIT(T10T9CFG, T10T9CFG_T10IF_MSK)
#define TIMER10_ClearFlag()             CLR_REG_BIT(T10T9CFG, T10T9CFG_T10IF_MSK)

#define T11CR_T11IF_MSK                 BIT0
#define TIMER11_CheckFlag()             READ_REG_BIT(T11CR, T11CR_T11IF_MSK)
#define TIMER11_ClearFlag()             CLR_REG_BIT(T11CR, T11CR_T11IF_MSK)

#define T18T17CFG_T17IF_MSK             BIT3
#define TIMER17_CheckFlag()             READ_REG_BIT(T18T17CFG, T18T17CFG_T17IF_MSK)
#define TIMER17_ClearFlag()             CLR_REG_BIT(T18T17CFG, T18T17CFG_T17IF_MSK)

#define T18T17CFG_T18IF_MSK             BIT7
#define TIMER18_CheckFlag()             READ_REG_BIT(T18T17CFG, T18T17CFG_T18IF_MSK)
#define TIMER18_ClearFlag()             CLR_REG_BIT(T18T17CFG, T18T17CFG_T18IF_MSK)

#define UART1_CheckRxFlag()             (RI)
#define UART1_CheckTxFlag()             (TI)
#define UART1_ClearRxFlag()             (RI = 0)
#define UART1_ClearTxFlag()             (TI = 0)
#define UART1_SetRxFlag()               (RI = 1)
#define UART1_SetTxFlag()               (TI = 1)

#define S2CON_S2TI_MSK                  BIT1
#define S2CON_S2RI_MSK                  BIT0
#define UART2_CheckRxFlag()             READ_REG_BIT(S2CON, S2CON_S2RI_MSK)
#define UART2_CheckTxFlag()             READ_REG_BIT(S2CON, S2CON_S2TI_MSK)
#define UART2_ClearRxFlag()             CLR_REG_BIT(S2CON, S2CON_S2RI_MSK)
#define UART2_ClearTxFlag()             CLR_REG_BIT(S2CON, S2CON_S2TI_MSK)
#define UART2_SetRxFlag()               SET_REG_BIT(S2CON, S2CON_S2RI_MSK)
#define UART2_SetTxFlag()               SET_REG_BIT(S2CON, S2CON_S2TI_MSK)

#define S3CON_S3TI_MSK                  BIT1
#define S3CON_S3RI_MSK                  BIT0
#define UART3_CheckRxFlag()             READ_REG_BIT(S3CON, S3CON_S3RI_MSK)
#define UART3_CheckTxFlag()             READ_REG_BIT(S3CON, S3CON_S3TI_MSK)
#define UART3_ClearRxFlag()             CLR_REG_BIT(S3CON, S3CON_S3RI_MSK)
#define UART3_ClearTxFlag()             CLR_REG_BIT(S3CON, S3CON_S3TI_MSK)
#define UART3_SetRxFlag()               SET_REG_BIT(S3CON, S3CON_S3RI_MSK)
#define UART3_SetTxFlag()               SET_REG_BIT(S3CON, S3CON_S3TI_MSK)

#define S4CON_S4TI_MSK                  BIT1
#define S4CON_S4RI_MSK                  BIT0
#define UART4_CheckRxFlag()             READ_REG_BIT(S4CON, S4CON_S4RI_MSK)
#define UART4_CheckTxFlag()             READ_REG_BIT(S4CON, S4CON_S4TI_MSK)
#define UART4_ClearRxFlag()             CLR_REG_BIT(S4CON, S4CON_S4RI_MSK)
#define UART4_ClearTxFlag()             CLR_REG_BIT(S4CON, S4CON_S4TI_MSK)
#define UART4_SetRxFlag()               SET_REG_BIT(S4CON, S4CON_S4RI_MSK)
#define UART4_SetTxFlag()               SET_REG_BIT(S4CON, S4CON_S4TI_MSK)

#define S5CON_S5TI_MSK                  BIT1
#define S5CON_S5RI_MSK                  BIT0
#define UART5_CheckRxFlag()             READ_REG_BIT(S5CON, S5CON_S5RI_MSK)
#define UART5_CheckTxFlag()             READ_REG_BIT(S5CON, S5CON_S5TI_MSK)
#define UART5_ClearRxFlag()             CLR_REG_BIT(S5CON, S5CON_S5RI_MSK)
#define UART5_ClearTxFlag()             CLR_REG_BIT(S5CON, S5CON_S5TI_MSK)
#define UART5_SetRxFlag()               SET_REG_BIT(S5CON, S5CON_S5RI_MSK)
#define UART5_SetTxFlag()               SET_REG_BIT(S5CON, S5CON_S5TI_MSK)

#define S6CON_S6TI_MSK                  BIT1
#define S6CON_S6RI_MSK                  BIT0
#define UART6_CheckRxFlag()             READ_REG_BIT(S6CON, S6CON_S6RI_MSK)
#define UART6_CheckTxFlag()             READ_REG_BIT(S6CON, S6CON_S6TI_MSK)
#define UART6_ClearRxFlag()             CLR_REG_BIT(S6CON, S6CON_S6RI_MSK)
#define UART6_ClearTxFlag()             CLR_REG_BIT(S6CON, S6CON_S6TI_MSK)
#define UART6_SetRxFlag()               SET_REG_BIT(S6CON, S6CON_S6RI_MSK)
#define UART6_SetTxFlag()               SET_REG_BIT(S6CON, S6CON_S6TI_MSK)

#define S7CON_S7TI_MSK                  BIT1
#define S7CON_S7RI_MSK                  BIT0
#define UART7_CheckRxFlag()             READ_REG_BIT(S7CON, S7CON_S7RI_MSK)
#define UART7_CheckTxFlag()             READ_REG_BIT(S7CON, S7CON_S7TI_MSK)
#define UART7_ClearRxFlag()             CLR_REG_BIT(S7CON, S7CON_S7RI_MSK)
#define UART7_ClearTxFlag()             CLR_REG_BIT(S7CON, S7CON_S7TI_MSK)
#define UART7_SetRxFlag()               SET_REG_BIT(S7CON, S7CON_S7RI_MSK)
#define UART7_SetTxFlag()               SET_REG_BIT(S7CON, S7CON_S7TI_MSK)

#define S8CON_S8TI_MSK                  BIT1
#define S8CON_S8RI_MSK                  BIT0
#define UART8_CheckRxFlag()             READ_REG_BIT(S8CON, S8CON_S8RI_MSK)
#define UART8_CheckTxFlag()             READ_REG_BIT(S8CON, S8CON_S8TI_MSK)
#define UART8_ClearRxFlag()             CLR_REG_BIT(S8CON, S8CON_S8RI_MSK)
#define UART8_ClearTxFlag()             CLR_REG_BIT(S8CON, S8CON_S8TI_MSK)
#define UART8_SetRxFlag()               SET_REG_BIT(S8CON, S8CON_S8RI_MSK)
#define UART8_SetTxFlag()               SET_REG_BIT(S8CON, S8CON_S8TI_MSK)

#define PCON_LVDF_MSK                   BIT5
#define LVD_CheckFlag()                 READ_REG_BIT(PCON, PCON_LVDF_MSK)
#define LVD_ClearFlag()                 CLR_REG_BIT(PCON, PCON_LVDF_MSK)

#define ADCCONTR_ADCFLAG_MSK            BIT5
#define ADC1_CheckFlag()                READ_REG_BIT(ADC_CONTR, ADCCONTR_ADCFLAG_MSK)
#define ADC1_ClearFlag()                CLR_REG_BIT(ADC_CONTR, ADCCONTR_ADCFLAG_MSK)

#define ADC2CONTR_ADC2FLAG_MSK          BIT5
#define ADC2_CheckFlag()                READ_REG_BIT(ADC2_CONTR, ADC2CONTR_ADC2FLAG_MSK)
#define ADC2_ClearFlag()                CLR_REG_BIT(ADC2_CONTR, ADC2CONTR_ADC2FLAG_MSK)

#define DAC1STA_DAC1IF_MSK              BIT0
#define DAC1_CheckFlag()                READ_REG_BIT(DAC1_STA, DAC1STA_DAC1IF_MSK)
#define DAC1_ClearFlag()                CLR_REG_BIT(DAC1_STA, DAC1STA_DAC1IF_MSK)

#define DAC2STA_DAC2IF_MSK              BIT0
#define DAC2_CheckFlag()                READ_REG_BIT(DAC2_STA, DAC2STA_DAC2IF_MSK)
#define DAC2_ClearFlag()                CLR_REG_BIT(DAC2_STA, DAC2STA_DAC2IF_MSK)

#define SPSTAT_SPIF_MSK                 BIT7
#define SPSTAT_WCOL_MSK                 BIT6
#define SPI1_CheckFlag()                READ_REG_BIT(SPSTAT, SPSTAT_SPIF_MSK)
#define SPI1_ClearFlag()                SET_REG_BIT(SPSTAT, SPSTAT_SPIF_MSK | SPSTAT_WCOL_MSK)

#define SPI2STAT_SP2IF_MSK              BIT7
#define SPI2STAT_WCOL2_MSK              BIT6
#define SPI2_CheckFlag()                READ_REG_BIT(SPI2STAT, SPI2STAT_SP2IF_MSK)
#define SPI2_ClearFlag()                SET_REG_BIT(SPI2STAT, SPI2STAT_SP2IF_MSK | SPI2STAT_WCOL2_MSK)

#define SPI3STAT_SP3IF_MSK              BIT7
#define SPI3STAT_WCOL3_MSK              BIT6
#define SPI3_CheckFlag()                READ_REG_BIT(SPI3STAT, SPI3STAT_SP3IF_MSK)
#define SPI3_ClearFlag()                SET_REG_BIT(SPI3STAT, SPI3STAT_SP3IF_MSK | SPI3STAT_WCOL3_MSK)

#define CMP1CR1_CMPIF_MSK               BIT6
#define CMP1_CheckFlag()                READ_REG_BIT(CMP1_6P6N_CR1, CMP1CR1_CMPIF_MSK)
#define CMP1_ClearFlag()                CLR_REG_BIT(CMP1_6P6N_CR1, CMP1CR1_CMPIF_MSK)

#define CMP2CR1_CMPIF_MSK               BIT6
#define CMP2_CheckFlag()                READ_REG_BIT(CMP2_6P6N_CR1, CMP2CR1_CMPIF_MSK)
#define CMP2_ClearFlag()                CLR_REG_BIT(CMP2_6P6N_CR1, CMP2CR1_CMPIF_MSK)

#define CMP3CR1_CMPIF_MSK               BIT6
#define CMP3_CheckFlag()                READ_REG_BIT(CMP3_6P6N_CR1, CMP3CR1_CMPIF_MSK)
#define CMP3_ClearFlag()                CLR_REG_BIT(CMP3_6P6N_CR1, CMP3CR1_CMPIF_MSK)

#define CMP4CR1_CMPIF_MSK               BIT6
#define CMP4_CheckFlag()                READ_REG_BIT(CMP4_6P6N_CR1, CMP4CR1_CMPIF_MSK)
#define CMP4_ClearFlag()                CLR_REG_BIT(CMP4_6P6N_CR1, CMP4CR1_CMPIF_MSK)

#define RTCIF_ALARM_MSK                 BIT7
#define RTCIF_DAY_MSK                   BIT6
#define RTCIF_HOUR_MSK                  BIT5
#define RTCIF_MIN_MSK                   BIT4
#define RTCIF_SEC_MSK                   BIT3
#define RTCIF_SEC2_MSK                  BIT2
#define RTCIF_SEC8_MSK                  BIT1
#define RTCIF_SEC32_MSK                 BIT0
#define RTC_CheckAlarmFlag()            READ_REG_BIT(RTCIF, RTCIF_ALARM_MSK)
#define RTC_CheckDayFlag()              READ_REG_BIT(RTCIF, RTCIF_DAY_MSK)
#define RTC_CheckHourFlag()             READ_REG_BIT(RTCIF, RTCIF_HOUR_MSK)
#define RTC_CheckMinuteFlag()           READ_REG_BIT(RTCIF, RTCIF_MIN_MSK)
#define RTC_CheckSecondFlag()           READ_REG_BIT(RTCIF, RTCIF_SEC_MSK)
#define RTC_CheckSecondD2Flag()         READ_REG_BIT(RTCIF, RTCIF_SEC2_MSK)
#define RTC_CheckSecondD8Flag()         READ_REG_BIT(RTCIF, RTCIF_SEC8_MSK)
#define RTC_CheckSecondD32Flag()        READ_REG_BIT(RTCIF, RTCIF_SEC32_MSK)
#define RTC_ClearAlarmFlag()            CLR_REG_BIT(RTCIF, RTCIF_ALARM_MSK)
#define RTC_ClearDayFlag()              CLR_REG_BIT(RTCIF, RTCIF_DAY_MSK)
#define RTC_ClearHourFlag()             CLR_REG_BIT(RTCIF, RTCIF_HOUR_MSK)
#define RTC_ClearMinuteFlag()           CLR_REG_BIT(RTCIF, RTCIF_MIN_MSK)
#define RTC_ClearSecondFlag()           CLR_REG_BIT(RTCIF, RTCIF_SEC_MSK)
#define RTC_ClearSecondD2Flag()         CLR_REG_BIT(RTCIF, RTCIF_SEC2_MSK)
#define RTC_ClearSecondD8Flag()         CLR_REG_BIT(RTCIF, RTCIF_SEC8_MSK)
#define RTC_ClearSecondD32Flag()        CLR_REG_BIT(RTCIF, RTCIF_SEC32_MSK)

#define LCMIFIF_MSK                     BIT0
#define LCM_CheckFlag()                 READ_REG_BIT(LCMIFSTA, LCMIFIF_MSK)
#define LCM_ClearFlag()                 CLR_REG_BIT(LCMIFSTA, LCMIFIF_MSK)

#define I2CMSST_MSIF_MSK                BIT6
#define I2C1_CheckMasterFlag()          READ_REG_BIT(I2CMSST, I2CMSST_MSIF_MSK)
#define I2C1_ClearMasterFlag()          CLR_REG_BIT(I2CMSST, I2CMSST_MSIF_MSK)

#define I2C2MSST_MSIF_MSK               BIT6
#define I2C2_CheckMasterFlag()          READ_REG_BIT(I2C2MSST, I2C2MSST_MSIF_MSK)
#define I2C2_ClearMasterFlag()          CLR_REG_BIT(I2C2MSST, I2C2MSST_MSIF_MSK)

#define I2CSLST_STAIF_MSK               BIT6
#define I2CSLST_RXIF_MSK                BIT5
#define I2CSLST_TXIF_MSK                BIT4
#define I2CSLST_STOIF_MSK               BIT3
#define I2C1_CheckSlaveSTAFlag()        READ_REG_BIT(I2CSLST, I2CSLST_STAIF_MSK)
#define I2C1_CheckSlaveSTOFlag()        READ_REG_BIT(I2CSLST, I2CSLST_STOIF_MSK)
#define I2C1_CheckSlaveRXFlag()         READ_REG_BIT(I2CSLST, I2CSLST_RXIF_MSK)
#define I2C1_CheckSlaveTXFlag()         READ_REG_BIT(I2CSLST, I2CSLST_TXIF_MSK)
#define I2C1_CheckSlaveAllFlag()        READ_REG_BIT(I2CSLST, I2CSLST_STAIF_MSK | I2CSLST_STOIF_MSK | I2CSLST_RXIF_MSK | I2CSLST_TXIF_MSK)
#define I2C1_ClearSlaveSTAFlag()        CLR_REG_BIT(I2CSLST, I2CSLST_STAIF_MSK)
#define I2C1_ClearSlaveSTOFlag()        CLR_REG_BIT(I2CSLST, I2CSLST_STOIF_MSK)
#define I2C1_ClearSlaveRXFlag()         CLR_REG_BIT(I2CSLST, I2CSLST_RXIF_MSK)
#define I2C1_ClearSlaveTXFlag()         CLR_REG_BIT(I2CSLST, I2CSLST_TXIF_MSK)
#define I2C1_ClearSlaveAllFlag()        CLR_REG_BIT(I2CSLST, I2CSLST_STAIF_MSK | I2CSLST_STOIF_MSK | I2CSLST_RXIF_MSK | I2CSLST_TXIF_MSK)

#define I2C2SLST_STAIF_MSK              BIT6
#define I2C2SLST_RXIF_MSK               BIT5
#define I2C2SLST_TXIF_MSK               BIT4
#define I2C2SLST_STOIF_MSK              BIT3
#define I2C2_CheckSlaveSTAFlag()        READ_REG_BIT(I2C2SLST, I2C2SLST_STAIF_MSK)
#define I2C2_CheckSlaveSTOFlag()        READ_REG_BIT(I2C2SLST, I2C2SLST_STOIF_MSK)
#define I2C2_CheckSlaveRXFlag()         READ_REG_BIT(I2C2SLST, I2C2SLST_RXIF_MSK)
#define I2C2_CheckSlaveTXFlag()         READ_REG_BIT(I2C2SLST, I2C2SLST_TXIF_MSK)
#define I2C2_CheckSlaveAllFlag()        READ_REG_BIT(I2C2SLST, I2C2SLST_STAIF_MSK | I2C2SLST_STOIF_MSK | I2C2SLST_RXIF_MSK | I2C2SLST_TXIF_MSK)
#define I2C2_ClearSlaveSTAFlag()        CLR_REG_BIT(I2C2SLST, I2C2SLST_STAIF_MSK)
#define I2C2_ClearSlaveSTOFlag()        CLR_REG_BIT(I2C2SLST, I2C2SLST_STOIF_MSK)
#define I2C2_ClearSlaveRXFlag()         CLR_REG_BIT(I2C2SLST, I2C2SLST_RXIF_MSK)
#define I2C2_ClearSlaveTXFlag()         CLR_REG_BIT(I2C2SLST, I2C2SLST_TXIF_MSK)
#define I2C2_ClearSlaveAllFlag()        CLR_REG_BIT(I2C2SLST, I2C2SLST_STAIF_MSK | I2C2SLST_STOIF_MSK | I2C2SLST_RXIF_MSK | I2C2SLST_TXIF_MSK)

#define PWMASR1_BIF_MSK                 BIT7
#define PWMASR1_TIF_MSK                 BIT6
#define PWMASR1_COMIF_MSK               BIT5
#define PWMASR3_CC6IF_MSK               BIT1
#define PWMASR3_CC5IF_MSK               BIT0
#define PWMASR1_CC4IF_MSK               BIT4
#define PWMASR1_CC3IF_MSK               BIT3
#define PWMASR1_CC2IF_MSK               BIT2
#define PWMASR1_CC1IF_MSK               BIT1
#define PWMASR1_UIF_MSK                 BIT0
#define PWMA_CheckBreakFlag()           READ_REG_BIT(PWMA_SR1, PWMASR1_BIF_MSK)
#define PWMA_CheckTriggerFlag()         READ_REG_BIT(PWMA_SR1, PWMASR1_TIF_MSK)
#define PWMA_CheckCOMFlag()             READ_REG_BIT(PWMA_SR1, PWMASR1_COMIF_MSK)
#define PWMA_CheckCC6Flag()             READ_REG_BIT(PWMA_SR3, PWMASR3_CC6IF_MSK)
#define PWMA_CheckCC5Flag()             READ_REG_BIT(PWMA_SR3, PWMASR3_CC5IF_MSK)
#define PWMA_CheckCC4Flag()             READ_REG_BIT(PWMA_SR1, PWMASR1_CC4IF_MSK)
#define PWMA_CheckCC3Flag()             READ_REG_BIT(PWMA_SR1, PWMASR1_CC3IF_MSK)
#define PWMA_CheckCC2Flag()             READ_REG_BIT(PWMA_SR1, PWMASR1_CC2IF_MSK)
#define PWMA_CheckCC1Flag()             READ_REG_BIT(PWMA_SR1, PWMASR1_CC1IF_MSK)
#define PWMA_CheckUpdateFlag()          READ_REG_BIT(PWMA_SR1, PWMASR1_UIF_MSK)
#define PWMA_ClearBreakFlag()           CLR_REG_BIT(PWMA_SR1, PWMASR1_BIF_MSK)
#define PWMA_ClearTriggerFlag()         CLR_REG_BIT(PWMA_SR1, PWMASR1_TIF_MSK)
#define PWMA_ClearCOMFlag()             CLR_REG_BIT(PWMA_SR1, PWMASR1_COMIF_MSK)
#define PWMA_ClearCC6Flag()             CLR_REG_BIT(PWMA_SR3, PWMASR3_CC6IF_MSK)
#define PWMA_ClearCC5Flag()             CLR_REG_BIT(PWMA_SR3, PWMASR3_CC5IF_MSK)
#define PWMA_ClearCC4Flag()             CLR_REG_BIT(PWMA_SR1, PWMASR1_CC4IF_MSK)
#define PWMA_ClearCC3Flag()             CLR_REG_BIT(PWMA_SR1, PWMASR1_CC3IF_MSK)
#define PWMA_ClearCC2Flag()             CLR_REG_BIT(PWMA_SR1, PWMASR1_CC2IF_MSK)
#define PWMA_ClearCC1Flag()             CLR_REG_BIT(PWMA_SR1, PWMASR1_CC1IF_MSK)
#define PWMA_ClearUpdateFlag()          CLR_REG_BIT(PWMA_SR1, PWMASR1_UIF_MSK)

#define HSPWMA_CheckBreakFlag()         READ_HSPWMA_BIT(PWMA_SR1, PWMASR1_BIF_MSK)
#define HSPWMA_CheckTriggerFlag()       READ_HSPWMA_BIT(PWMA_SR1, PWMASR1_TIF_MSK)
#define HSPWMA_CheckCOMFlag()           READ_HSPWMA_BIT(PWMA_SR1, PWMASR1_COMIF_MSK)
#define HSPWMA_CheckCC6Flag()           READ_HSPWMA_BIT(PWMA_SR3, PWMASR3_CC6IF_MSK)
#define HSPWMA_CheckCC5Flag()           READ_HSPWMA_BIT(PWMA_SR3, PWMASR3_CC5IF_MSK)
#define HSPWMA_CheckCC4Flag()           READ_HSPWMA_BIT(PWMA_SR1, PWMASR1_CC4IF_MSK)
#define HSPWMA_CheckCC3Flag()           READ_HSPWMA_BIT(PWMA_SR1, PWMASR1_CC3IF_MSK)
#define HSPWMA_CheckCC2Flag()           READ_HSPWMA_BIT(PWMA_SR1, PWMASR1_CC2IF_MSK)
#define HSPWMA_CheckCC1Flag()           READ_HSPWMA_BIT(PWMA_SR1, PWMASR1_CC1IF_MSK)
#define HSPWMA_CheckUpdateFlag()        READ_HSPWMA_BIT(PWMA_SR1, PWMASR1_UIF_MSK)
#define HSPWMA_ClearBreakFlag()         CLR_HSPWMA_BIT(PWMA_SR1, PWMASR1_BIF_MSK)
#define HSPWMA_ClearTriggerFlag()       CLR_HSPWMA_BIT(PWMA_SR1, PWMASR1_TIF_MSK)
#define HSPWMA_ClearCOMFlag()           CLR_HSPWMA_BIT(PWMA_SR1, PWMASR1_COMIF_MSK)
#define HSPWMA_ClearCC6Flag()           CLR_HSPWMA_BIT(PWMA_SR3, PWMASR3_CC6IF_MSK)
#define HSPWMA_ClearCC5Flag()           CLR_HSPWMA_BIT(PWMA_SR3, PWMASR3_CC5IF_MSK)
#define HSPWMA_ClearCC4Flag()           CLR_HSPWMA_BIT(PWMA_SR1, PWMASR1_CC4IF_MSK)
#define HSPWMA_ClearCC3Flag()           CLR_HSPWMA_BIT(PWMA_SR1, PWMASR1_CC3IF_MSK)
#define HSPWMA_ClearCC2Flag()           CLR_HSPWMA_BIT(PWMA_SR1, PWMASR1_CC2IF_MSK)
#define HSPWMA_ClearCC1Flag()           CLR_HSPWMA_BIT(PWMA_SR1, PWMASR1_CC1IF_MSK)
#define HSPWMA_ClearUpdateFlag()        CLR_HSPWMA_BIT(PWMA_SR1, PWMASR1_UIF_MSK)

#define PWMBSR1_BIF_MSK                 BIT7
#define PWMBSR1_TIF_MSK                 BIT6
#define PWMBSR1_COMIF_MSK               BIT5
#define PWMBSR1_CC8IF_MSK               BIT4
#define PWMBSR1_CC7IF_MSK               BIT3
#define PWMBSR1_CC6IF_MSK               BIT2
#define PWMBSR1_CC5IF_MSK               BIT1
#define PWMBSR1_UIF_MSK                 BIT0
#define PWMB_CheckBreakFlag()           READ_REG_BIT(PWMB_SR1, PWMBSR1_BIF_MSK)
#define PWMB_CheckTriggerFlag()         READ_REG_BIT(PWMB_SR1, PWMBSR1_TIF_MSK)
#define PWMB_CheckCOMFlag()             READ_REG_BIT(PWMB_SR1, PWMBSR1_COMIF_MSK)
#define PWMB_CheckCC8Flag()             READ_REG_BIT(PWMB_SR1, PWMBSR1_CC8IF_MSK)
#define PWMB_CheckCC7Flag()             READ_REG_BIT(PWMB_SR1, PWMBSR1_CC7IF_MSK)
#define PWMB_CheckCC6Flag()             READ_REG_BIT(PWMB_SR1, PWMBSR1_CC6IF_MSK)
#define PWMB_CheckCC5Flag()             READ_REG_BIT(PWMB_SR1, PWMBSR1_CC5IF_MSK)
#define PWMB_CheckUpdateFlag()          READ_REG_BIT(PWMB_SR1, PWMBSR1_UIF_MSK)
#define PWMB_ClearBreakFlag()           CLR_REG_BIT(PWMB_SR1, PWMBSR1_BIF_MSK)
#define PWMB_ClearTriggerFlag()         CLR_REG_BIT(PWMB_SR1, PWMBSR1_TIF_MSK)
#define PWMB_ClearCOMFlag()             CLR_REG_BIT(PWMB_SR1, PWMBSR1_COMIF_MSK)
#define PWMB_ClearCC8Flag()             CLR_REG_BIT(PWMB_SR1, PWMBSR1_CC8IF_MSK)
#define PWMB_ClearCC7Flag()             CLR_REG_BIT(PWMB_SR1, PWMBSR1_CC7IF_MSK)
#define PWMB_ClearCC6Flag()             CLR_REG_BIT(PWMB_SR1, PWMBSR1_CC6IF_MSK)
#define PWMB_ClearCC5Flag()             CLR_REG_BIT(PWMB_SR1, PWMBSR1_CC5IF_MSK)
#define PWMB_ClearUpdateFlag()          CLR_REG_BIT(PWMB_SR1, PWMBSR1_UIF_MSK)

#define HSPWMB_CheckBreakFlag()         READ_HSPWMB_BIT(PWMB_SR1, PWMBSR1_BIF_MSK)
#define HSPWMB_CheckTriggerFlag()       READ_HSPWMB_BIT(PWMB_SR1, PWMBSR1_TIF_MSK)
#define HSPWMB_CheckCOMFlag()           READ_HSPWMB_BIT(PWMB_SR1, PWMBSR1_COMIF_MSK)
#define HSPWMB_CheckCC8Flag()           READ_HSPWMB_BIT(PWMB_SR1, PWMBSR1_CC8IF_MSK)
#define HSPWMB_CheckCC7Flag()           READ_HSPWMB_BIT(PWMB_SR1, PWMBSR1_CC7IF_MSK)
#define HSPWMB_CheckCC6Flag()           READ_HSPWMB_BIT(PWMB_SR1, PWMBSR1_CC6IF_MSK)
#define HSPWMB_CheckCC5Flag()           READ_HSPWMB_BIT(PWMB_SR1, PWMBSR1_CC5IF_MSK)
#define HSPWMB_CheckUpdateFlag()        READ_HSPWMB_BIT(PWMB_SR1, PWMBSR1_UIF_MSK)
#define HSPWMB_ClearBreakFlag()         CLR_HSPWMB_BIT(PWMB_SR1, PWMBSR1_BIF_MSK)
#define HSPWMB_ClearTriggerFlag()       CLR_HSPWMB_BIT(PWMB_SR1, PWMBSR1_TIF_MSK)
#define HSPWMB_ClearCOMFlag()           CLR_HSPWMB_BIT(PWMB_SR1, PWMBSR1_COMIF_MSK)
#define HSPWMB_ClearCC8Flag()           CLR_HSPWMB_BIT(PWMB_SR1, PWMBSR1_CC8IF_MSK)
#define HSPWMB_ClearCC7Flag()           CLR_HSPWMB_BIT(PWMB_SR1, PWMBSR1_CC7IF_MSK)
#define HSPWMB_ClearCC6Flag()           CLR_HSPWMB_BIT(PWMB_SR1, PWMBSR1_CC6IF_MSK)
#define HSPWMB_ClearCC5Flag()           CLR_HSPWMB_BIT(PWMB_SR1, PWMBSR1_CC5IF_MSK)
#define HSPWMB_ClearUpdateFlag()        CLR_HSPWMB_BIT(PWMB_SR1, PWMBSR1_UIF_MSK)

#define PWMCSR1_BIF_MSK                 BIT7
#define PWMCSR1_TIF_MSK                 BIT6
#define PWMCSR1_COMIF_MSK               BIT5
#define PWMCSR3_CC6IF_MSK               BIT1
#define PWMCSR3_CC5IF_MSK               BIT0
#define PWMCSR1_CC4IF_MSK               BIT4
#define PWMCSR1_CC3IF_MSK               BIT3
#define PWMCSR1_CC2IF_MSK               BIT2
#define PWMCSR1_CC1IF_MSK               BIT1
#define PWMCSR1_UIF_MSK                 BIT0
#define PWMC_CheckBreakFlag()           READ_REG_BIT(PWMC_SR1, PWMCSR1_BIF_MSK)
#define PWMC_CheckTriggerFlag()         READ_REG_BIT(PWMC_SR1, PWMCSR1_TIF_MSK)
#define PWMC_CheckCOMFlag()             READ_REG_BIT(PWMC_SR1, PWMCSR1_COMIF_MSK)
#define PWMC_CheckCC6Flag()             READ_REG_BIT(PWMC_SR3, PWMCSR3_CC6IF_MSK)
#define PWMC_CheckCC5Flag()             READ_REG_BIT(PWMC_SR3, PWMCSR3_CC5IF_MSK)
#define PWMC_CheckCC4Flag()             READ_REG_BIT(PWMC_SR1, PWMCSR1_CC4IF_MSK)
#define PWMC_CheckCC3Flag()             READ_REG_BIT(PWMC_SR1, PWMCSR1_CC3IF_MSK)
#define PWMC_CheckCC2Flag()             READ_REG_BIT(PWMC_SR1, PWMCSR1_CC2IF_MSK)
#define PWMC_CheckCC1Flag()             READ_REG_BIT(PWMC_SR1, PWMCSR1_CC1IF_MSK)
#define PWMC_CheckUpdateFlag()          READ_REG_BIT(PWMC_SR1, PWMCSR1_UIF_MSK)
#define PWMC_ClearBreakFlag()           CLR_REG_BIT(PWMC_SR1, PWMCSR1_BIF_MSK)
#define PWMC_ClearTriggerFlag()         CLR_REG_BIT(PWMC_SR1, PWMCSR1_TIF_MSK)
#define PWMC_ClearCOMFlag()             CLR_REG_BIT(PWMC_SR1, PWMCSR1_COMIF_MSK)
#define PWMC_ClearCC6Flag()             CLR_REG_BIT(PWMC_SR3, PWMCSR3_CC6IF_MSK)
#define PWMC_ClearCC5Flag()             CLR_REG_BIT(PWMC_SR3, PWMCSR3_CC5IF_MSK)
#define PWMC_ClearCC4Flag()             CLR_REG_BIT(PWMC_SR1, PWMCSR1_CC4IF_MSK)
#define PWMC_ClearCC3Flag()             CLR_REG_BIT(PWMC_SR1, PWMCSR1_CC3IF_MSK)
#define PWMC_ClearCC2Flag()             CLR_REG_BIT(PWMC_SR1, PWMCSR1_CC2IF_MSK)
#define PWMC_ClearCC1Flag()             CLR_REG_BIT(PWMC_SR1, PWMCSR1_CC1IF_MSK)
#define PWMC_ClearUpdateFlag()          CLR_REG_BIT(PWMC_SR1, PWMCSR1_UIF_MSK)

#define HSPWMC_CheckBreakFlag()         READ_HSPWMC_BIT(PWMC_SR1, PWMCSR1_BIF_MSK)
#define HSPWMC_CheckTriggerFlag()       READ_HSPWMC_BIT(PWMC_SR1, PWMCSR1_TIF_MSK)
#define HSPWMC_CheckCOMFlag()           READ_HSPWMC_BIT(PWMC_SR1, PWMCSR1_COMIF_MSK)
#define HSPWMC_CheckCC6Flag()           READ_HSPWMC_BIT(PWMC_SR3, PWMCSR3_CC6IF_MSK)
#define HSPWMC_CheckCC5Flag()           READ_HSPWMC_BIT(PWMC_SR3, PWMCSR3_CC5IF_MSK)
#define HSPWMC_CheckCC4Flag()           READ_HSPWMC_BIT(PWMC_SR1, PWMCSR1_CC4IF_MSK)
#define HSPWMC_CheckCC3Flag()           READ_HSPWMC_BIT(PWMC_SR1, PWMCSR1_CC3IF_MSK)
#define HSPWMC_CheckCC2Flag()           READ_HSPWMC_BIT(PWMC_SR1, PWMCSR1_CC2IF_MSK)
#define HSPWMC_CheckCC1Flag()           READ_HSPWMC_BIT(PWMC_SR1, PWMCSR1_CC1IF_MSK)
#define HSPWMC_CheckUpdateFlag()        READ_HSPWMC_BIT(PWMC_SR1, PWMCSR1_UIF_MSK)
#define HSPWMC_ClearBreakFlag()         CLR_HSPWMC_BIT(PWMC_SR1, PWMCSR1_BIF_MSK)
#define HSPWMC_ClearTriggerFlag()       CLR_HSPWMC_BIT(PWMC_SR1, PWMCSR1_TIF_MSK)
#define HSPWMC_ClearCOMFlag()           CLR_HSPWMC_BIT(PWMC_SR1, PWMCSR1_COMIF_MSK)
#define HSPWMC_ClearCC6Flag()           CLR_HSPWMC_BIT(PWMC_SR3, PWMCSR3_CC6IF_MSK)
#define HSPWMC_ClearCC5Flag()           CLR_HSPWMC_BIT(PWMC_SR3, PWMCSR3_CC5IF_MSK)
#define HSPWMC_ClearCC4Flag()           CLR_HSPWMC_BIT(PWMC_SR1, PWMCSR1_CC4IF_MSK)
#define HSPWMC_ClearCC3Flag()           CLR_HSPWMC_BIT(PWMC_SR1, PWMCSR1_CC3IF_MSK)
#define HSPWMC_ClearCC2Flag()           CLR_HSPWMC_BIT(PWMC_SR1, PWMCSR1_CC2IF_MSK)
#define HSPWMC_ClearCC1Flag()           CLR_HSPWMC_BIT(PWMC_SR1, PWMCSR1_CC1IF_MSK)
#define HSPWMC_ClearUpdateFlag()        CLR_HSPWMC_BIT(PWMC_SR1, PWMCSR1_UIF_MSK)

#define PWMDSR1_BIF_MSK                 BIT7
#define PWMDSR1_TIF_MSK                 BIT6
#define PWMDSR1_COMIF_MSK               BIT5
#define PWMDSR1_CC8IF_MSK               BIT4
#define PWMDSR1_CC7IF_MSK               BIT3
#define PWMDSR1_CC6IF_MSK               BIT2
#define PWMDSR1_CC5IF_MSK               BIT1
#define PWMDSR1_UIF_MSK                 BIT0
#define PWMD_CheckBreakFlag()           READ_REG_BIT(PWMD_SR1, PWMDSR1_BIF_MSK)
#define PWMD_CheckTriggerFlag()         READ_REG_BIT(PWMD_SR1, PWMDSR1_TIF_MSK)
#define PWMD_CheckCOMFlag()             READ_REG_BIT(PWMD_SR1, PWMDSR1_COMIF_MSK)
#define PWMD_CheckCC8Flag()             READ_REG_BIT(PWMD_SR1, PWMDSR1_CC8IF_MSK)
#define PWMD_CheckCC7Flag()             READ_REG_BIT(PWMD_SR1, PWMDSR1_CC7IF_MSK)
#define PWMD_CheckCC6Flag()             READ_REG_BIT(PWMD_SR1, PWMDSR1_CC6IF_MSK)
#define PWMD_CheckCC5Flag()             READ_REG_BIT(PWMD_SR1, PWMDSR1_CC5IF_MSK)
#define PWMD_CheckUpdateFlag()          READ_REG_BIT(PWMD_SR1, PWMDSR1_UIF_MSK)
#define PWMD_ClearBreakFlag()           CLR_REG_BIT(PWMD_SR1, PWMDSR1_BIF_MSK)
#define PWMD_ClearTriggerFlag()         CLR_REG_BIT(PWMD_SR1, PWMDSR1_TIF_MSK)
#define PWMD_ClearCOMFlag()             CLR_REG_BIT(PWMD_SR1, PWMDSR1_COMIF_MSK)
#define PWMD_ClearCC8Flag()             CLR_REG_BIT(PWMD_SR1, PWMDSR1_CC8IF_MSK)
#define PWMD_ClearCC7Flag()             CLR_REG_BIT(PWMD_SR1, PWMDSR1_CC7IF_MSK)
#define PWMD_ClearCC6Flag()             CLR_REG_BIT(PWMD_SR1, PWMDSR1_CC6IF_MSK)
#define PWMD_ClearCC5Flag()             CLR_REG_BIT(PWMD_SR1, PWMDSR1_CC5IF_MSK)
#define PWMD_ClearUpdateFlag()          CLR_REG_BIT(PWMD_SR1, PWMDSR1_UIF_MSK)

#define HSPWMD_CheckBreakFlag()         READ_HSPWMD_BIT(PWMD_SR1, PWMDSR1_BIF_MSK)
#define HSPWMD_CheckTriggerFlag()       READ_HSPWMD_BIT(PWMD_SR1, PWMDSR1_TIF_MSK)
#define HSPWMD_CheckCOMFlag()           READ_HSPWMD_BIT(PWMD_SR1, PWMDSR1_COMIF_MSK)
#define HSPWMD_CheckCC8Flag()           READ_HSPWMD_BIT(PWMD_SR1, PWMDSR1_CC8IF_MSK)
#define HSPWMD_CheckCC7Flag()           READ_HSPWMD_BIT(PWMD_SR1, PWMDSR1_CC7IF_MSK)
#define HSPWMD_CheckCC6Flag()           READ_HSPWMD_BIT(PWMD_SR1, PWMDSR1_CC6IF_MSK)
#define HSPWMD_CheckCC5Flag()           READ_HSPWMD_BIT(PWMD_SR1, PWMDSR1_CC5IF_MSK)
#define HSPWMD_CheckUpdateFlag()        READ_HSPWMD_BIT(PWMD_SR1, PWMDSR1_UIF_MSK)
#define HSPWMD_ClearBreakFlag()         CLR_HSPWMD_BIT(PWMD_SR1, PWMDSR1_BIF_MSK)
#define HSPWMD_ClearTriggerFlag()       CLR_HSPWMD_BIT(PWMD_SR1, PWMDSR1_TIF_MSK)
#define HSPWMD_ClearCOMFlag()           CLR_HSPWMD_BIT(PWMD_SR1, PWMDSR1_COMIF_MSK)
#define HSPWMD_ClearCC8Flag()           CLR_HSPWMD_BIT(PWMD_SR1, PWMDSR1_CC8IF_MSK)
#define HSPWMD_ClearCC7Flag()           CLR_HSPWMD_BIT(PWMD_SR1, PWMDSR1_CC7IF_MSK)
#define HSPWMD_ClearCC6Flag()           CLR_HSPWMD_BIT(PWMD_SR1, PWMDSR1_CC6IF_MSK)
#define HSPWMD_ClearCC5Flag()           CLR_HSPWMD_BIT(PWMD_SR1, PWMDSR1_CC5IF_MSK)
#define HSPWMD_ClearUpdateFlag()        CLR_HSPWMD_BIT(PWMD_SR1, PWMDSR1_UIF_MSK)

#define PWMESR1_BIF_MSK                 BIT7
#define PWMESR1_TIF_MSK                 BIT6
#define PWMESR1_COMIF_MSK               BIT5
#define PWMESR3_CC6IF_MSK               BIT1
#define PWMESR3_CC5IF_MSK               BIT0
#define PWMESR1_CC4IF_MSK               BIT4
#define PWMESR1_CC3IF_MSK               BIT3
#define PWMESR1_CC2IF_MSK               BIT2
#define PWMESR1_CC1IF_MSK               BIT1
#define PWMESR1_UIF_MSK                 BIT0
#define PWME_CheckBreakFlag()           READ_REG_BIT(PWME_SR1, PWMESR1_BIF_MSK)
#define PWME_CheckTriggerFlag()         READ_REG_BIT(PWME_SR1, PWMESR1_TIF_MSK)
#define PWME_CheckCOMFlag()             READ_REG_BIT(PWME_SR1, PWMESR1_COMIF_MSK)
#define PWME_CheckCC6Flag()             READ_REG_BIT(PWME_SR3, PWMESR3_CC6IF_MSK)
#define PWME_CheckCC5Flag()             READ_REG_BIT(PWME_SR3, PWMESR3_CC5IF_MSK)
#define PWME_CheckCC4Flag()             READ_REG_BIT(PWME_SR1, PWMESR1_CC4IF_MSK)
#define PWME_CheckCC3Flag()             READ_REG_BIT(PWME_SR1, PWMESR1_CC3IF_MSK)
#define PWME_CheckCC2Flag()             READ_REG_BIT(PWME_SR1, PWMESR1_CC2IF_MSK)
#define PWME_CheckCC1Flag()             READ_REG_BIT(PWME_SR1, PWMESR1_CC1IF_MSK)
#define PWME_CheckUpdateFlag()          READ_REG_BIT(PWME_SR1, PWMESR1_UIF_MSK)
#define PWME_ClearBreakFlag()           CLR_REG_BIT(PWME_SR1, PWMESR1_BIF_MSK)
#define PWME_ClearTriggerFlag()         CLR_REG_BIT(PWME_SR1, PWMESR1_TIF_MSK)
#define PWME_ClearCOMFlag()             CLR_REG_BIT(PWME_SR1, PWMESR1_COMIF_MSK)
#define PWME_ClearCC6Flag()             CLR_REG_BIT(PWME_SR3, PWMESR3_CC6IF_MSK)
#define PWME_ClearCC5Flag()             CLR_REG_BIT(PWME_SR3, PWMESR3_CC5IF_MSK)
#define PWME_ClearCC4Flag()             CLR_REG_BIT(PWME_SR1, PWMESR1_CC4IF_MSK)
#define PWME_ClearCC3Flag()             CLR_REG_BIT(PWME_SR1, PWMESR1_CC3IF_MSK)
#define PWME_ClearCC2Flag()             CLR_REG_BIT(PWME_SR1, PWMESR1_CC2IF_MSK)
#define PWME_ClearCC1Flag()             CLR_REG_BIT(PWME_SR1, PWMESR1_CC1IF_MSK)
#define PWME_ClearUpdateFlag()          CLR_REG_BIT(PWME_SR1, PWMESR1_UIF_MSK)

#define HSPWME_CheckBreakFlag()         READ_HSPWME_BIT(PWME_SR1, PWMESR1_BIF_MSK)
#define HSPWME_CheckTriggerFlag()       READ_HSPWME_BIT(PWME_SR1, PWMESR1_TIF_MSK)
#define HSPWME_CheckCOMFlag()           READ_HSPWME_BIT(PWME_SR1, PWMESR1_COMIF_MSK)
#define HSPWME_CheckCC6Flag()           READ_HSPWME_BIT(PWME_SR3, PWMESR3_CC6IF_MSK)
#define HSPWME_CheckCC5Flag()           READ_HSPWME_BIT(PWME_SR3, PWMESR3_CC5IF_MSK)
#define HSPWME_CheckCC4Flag()           READ_HSPWME_BIT(PWME_SR1, PWMESR1_CC4IF_MSK)
#define HSPWME_CheckCC3Flag()           READ_HSPWME_BIT(PWME_SR1, PWMESR1_CC3IF_MSK)
#define HSPWME_CheckCC2Flag()           READ_HSPWME_BIT(PWME_SR1, PWMESR1_CC2IF_MSK)
#define HSPWME_CheckCC1Flag()           READ_HSPWME_BIT(PWME_SR1, PWMESR1_CC1IF_MSK)
#define HSPWME_CheckUpdateFlag()        READ_HSPWME_BIT(PWME_SR1, PWMESR1_UIF_MSK)
#define HSPWME_ClearBreakFlag()         CLR_HSPWME_BIT(PWME_SR1, PWMESR1_BIF_MSK)
#define HSPWME_ClearTriggerFlag()       CLR_HSPWME_BIT(PWME_SR1, PWMESR1_TIF_MSK)
#define HSPWME_ClearCOMFlag()           CLR_HSPWME_BIT(PWME_SR1, PWMESR1_COMIF_MSK)
#define HSPWME_ClearCC6Flag()           CLR_HSPWME_BIT(PWME_SR3, PWMESR3_CC6IF_MSK)
#define HSPWME_ClearCC5Flag()           CLR_HSPWME_BIT(PWME_SR3, PWMESR3_CC5IF_MSK)
#define HSPWME_ClearCC4Flag()           CLR_HSPWME_BIT(PWME_SR1, PWMESR1_CC4IF_MSK)
#define HSPWME_ClearCC3Flag()           CLR_HSPWME_BIT(PWME_SR1, PWMESR1_CC3IF_MSK)
#define HSPWME_ClearCC2Flag()           CLR_HSPWME_BIT(PWME_SR1, PWMESR1_CC2IF_MSK)
#define HSPWME_ClearCC1Flag()           CLR_HSPWME_BIT(PWME_SR1, PWMESR1_CC1IF_MSK)
#define HSPWME_ClearUpdateFlag()        CLR_HSPWME_BIT(PWME_SR1, PWMESR1_UIF_MSK)

#define PWMFSR1_BIF_MSK                 BIT7
#define PWMFSR1_TIF_MSK                 BIT6
#define PWMFSR1_COMIF_MSK               BIT5
#define PWMFSR1_CC8IF_MSK               BIT4
#define PWMFSR1_CC7IF_MSK               BIT3
#define PWMFSR1_CC6IF_MSK               BIT2
#define PWMFSR1_CC5IF_MSK               BIT1
#define PWMFSR1_UIF_MSK                 BIT0
#define PWMF_CheckBreakFlag()           READ_REG_BIT(PWMF_SR1, PWMFSR1_BIF_MSK)
#define PWMF_CheckTriggerFlag()         READ_REG_BIT(PWMF_SR1, PWMFSR1_TIF_MSK)
#define PWMF_CheckCOMFlag()             READ_REG_BIT(PWMF_SR1, PWMFSR1_COMIF_MSK)
#define PWMF_CheckCC8Flag()             READ_REG_BIT(PWMF_SR1, PWMFSR1_CC8IF_MSK)
#define PWMF_CheckCC7Flag()             READ_REG_BIT(PWMF_SR1, PWMFSR1_CC7IF_MSK)
#define PWMF_CheckCC6Flag()             READ_REG_BIT(PWMF_SR1, PWMFSR1_CC6IF_MSK)
#define PWMF_CheckCC5Flag()             READ_REG_BIT(PWMF_SR1, PWMFSR1_CC5IF_MSK)
#define PWMF_CheckUpdateFlag()          READ_REG_BIT(PWMF_SR1, PWMFSR1_UIF_MSK)
#define PWMF_ClearBreakFlag()           CLR_REG_BIT(PWMF_SR1, PWMFSR1_BIF_MSK)
#define PWMF_ClearTriggerFlag()         CLR_REG_BIT(PWMF_SR1, PWMFSR1_TIF_MSK)
#define PWMF_ClearCOMFlag()             CLR_REG_BIT(PWMF_SR1, PWMFSR1_COMIF_MSK)
#define PWMF_ClearCC8Flag()             CLR_REG_BIT(PWMF_SR1, PWMFSR1_CC8IF_MSK)
#define PWMF_ClearCC7Flag()             CLR_REG_BIT(PWMF_SR1, PWMFSR1_CC7IF_MSK)
#define PWMF_ClearCC6Flag()             CLR_REG_BIT(PWMF_SR1, PWMFSR1_CC6IF_MSK)
#define PWMF_ClearCC5Flag()             CLR_REG_BIT(PWMF_SR1, PWMFSR1_CC5IF_MSK)
#define PWMF_ClearUpdateFlag()          CLR_REG_BIT(PWMF_SR1, PWMFSR1_UIF_MSK)

#define HSPWMF_CheckBreakFlag()         READ_HSPWMF_BIT(PWMF_SR1, PWMFSR1_BIF_MSK)
#define HSPWMF_CheckTriggerFlag()       READ_HSPWMF_BIT(PWMF_SR1, PWMFSR1_TIF_MSK)
#define HSPWMF_CheckCOMFlag()           READ_HSPWMF_BIT(PWMF_SR1, PWMFSR1_COMIF_MSK)
#define HSPWMF_CheckCC8Flag()           READ_HSPWMF_BIT(PWMF_SR1, PWMFSR1_CC8IF_MSK)
#define HSPWMF_CheckCC7Flag()           READ_HSPWMF_BIT(PWMF_SR1, PWMFSR1_CC7IF_MSK)
#define HSPWMF_CheckCC6Flag()           READ_HSPWMF_BIT(PWMF_SR1, PWMFSR1_CC6IF_MSK)
#define HSPWMF_CheckCC5Flag()           READ_HSPWMF_BIT(PWMF_SR1, PWMFSR1_CC5IF_MSK)
#define HSPWMF_CheckUpdateFlag()        READ_HSPWMF_BIT(PWMF_SR1, PWMFSR1_UIF_MSK)
#define HSPWMF_ClearBreakFlag()         CLR_HSPWMF_BIT(PWMF_SR1, PWMFSR1_BIF_MSK)
#define HSPWMF_ClearTriggerFlag()       CLR_HSPWMF_BIT(PWMF_SR1, PWMFSR1_TIF_MSK)
#define HSPWMF_ClearCOMFlag()           CLR_HSPWMF_BIT(PWMF_SR1, PWMFSR1_COMIF_MSK)
#define HSPWMF_ClearCC8Flag()           CLR_HSPWMF_BIT(PWMF_SR1, PWMFSR1_CC8IF_MSK)
#define HSPWMF_ClearCC7Flag()           CLR_HSPWMF_BIT(PWMF_SR1, PWMFSR1_CC7IF_MSK)
#define HSPWMF_ClearCC6Flag()           CLR_HSPWMF_BIT(PWMF_SR1, PWMFSR1_CC6IF_MSK)
#define HSPWMF_ClearCC5Flag()           CLR_HSPWMF_BIT(PWMF_SR1, PWMFSR1_CC5IF_MSK)
#define HSPWMF_ClearUpdateFlag()        CLR_HSPWMF_BIT(PWMF_SR1, PWMFSR1_UIF_MSK)

#define PWMASR2_CC4OF_MSK               BIT4
#define PWMASR2_CC3OF_MSK               BIT3
#define PWMASR2_CC2OF_MSK               BIT2
#define PWMASR2_CC1OF_MSK               BIT1
#define PWMA_CheckCC4OverFlag()         READ_REG_BIT(PWMA_SR2, PWMASR2_CC4OF_MSK)
#define PWMA_CheckCC3OverFlag()         READ_REG_BIT(PWMA_SR2, PWMASR2_CC3OF_MSK)
#define PWMA_CheckCC2OverFlag()         READ_REG_BIT(PWMA_SR2, PWMASR2_CC2OF_MSK)
#define PWMA_CheckCC1OverFlag()         READ_REG_BIT(PWMA_SR2, PWMASR2_CC1OF_MSK)
#define PWMA_ClearCC4OverFlag()         CLR_REG_BIT(PWMA_SR2, PWMASR2_CC4OF_MSK)
#define PWMA_ClearCC3OverFlag()         CLR_REG_BIT(PWMA_SR2, PWMASR2_CC3OF_MSK)
#define PWMA_ClearCC2OverFlag()         CLR_REG_BIT(PWMA_SR2, PWMASR2_CC2OF_MSK)
#define PWMA_ClearCC1OverFlag()         CLR_REG_BIT(PWMA_SR2, PWMASR2_CC1OF_MSK)

#define HSPWMA_CheckCC4OverFlag()       READ_HSPWMA_BIT(PWMA_SR2, PWMASR2_CC4OF_MSK)
#define HSPWMA_CheckCC3OverFlag()       READ_HSPWMA_BIT(PWMA_SR2, PWMASR2_CC3OF_MSK)
#define HSPWMA_CheckCC2OverFlag()       READ_HSPWMA_BIT(PWMA_SR2, PWMASR2_CC2OF_MSK)
#define HSPWMA_CheckCC1OverFlag()       READ_HSPWMA_BIT(PWMA_SR2, PWMASR2_CC1OF_MSK)
#define HSPWMA_ClearCC4OverFlag()       CLR_HSPWMA_BIT(PWMA_SR2, PWMASR2_CC4OF_MSK)
#define HSPWMA_ClearCC3OverFlag()       CLR_HSPWMA_BIT(PWMA_SR2, PWMASR2_CC3OF_MSK)
#define HSPWMA_ClearCC2OverFlag()       CLR_HSPWMA_BIT(PWMA_SR2, PWMASR2_CC2OF_MSK)
#define HSPWMA_ClearCC1OverFlag()       CLR_HSPWMA_BIT(PWMA_SR2, PWMASR2_CC1OF_MSK)

#define PWMBSR2_CC8OF_MSK               BIT4
#define PWMBSR2_CC7OF_MSK               BIT3
#define PWMBSR2_CC6OF_MSK               BIT2
#define PWMBSR2_CC5OF_MSK               BIT1
#define PWMB_CheckCC8OverFlag()         READ_REG_BIT(PWMB_SR2, PWMBSR2_CC8OF_MSK)
#define PWMB_CheckCC7OverFlag()         READ_REG_BIT(PWMB_SR2, PWMBSR2_CC7OF_MSK)
#define PWMB_CheckCC6OverFlag()         READ_REG_BIT(PWMB_SR2, PWMBSR2_CC6OF_MSK)
#define PWMB_CheckCC5OverFlag()         READ_REG_BIT(PWMB_SR2, PWMBSR2_CC5OF_MSK)
#define PWMB_ClearCC8OverFlag()         CLR_REG_BIT(PWMB_SR2, PWMBSR2_CC8OF_MSK)
#define PWMB_ClearCC7OverFlag()         CLR_REG_BIT(PWMB_SR2, PWMBSR2_CC7OF_MSK)
#define PWMB_ClearCC6OverFlag()         CLR_REG_BIT(PWMB_SR2, PWMBSR2_CC6OF_MSK)
#define PWMB_ClearCC5OverFlag()         CLR_REG_BIT(PWMB_SR2, PWMBSR2_CC5OF_MSK)

#define HSPWMB_CheckCC8OverFlag()       READ_HSPWMB_BIT(PWMB_SR2, PWMBSR2_CC8OF_MSK)
#define HSPWMB_CheckCC7OverFlag()       READ_HSPWMB_BIT(PWMB_SR2, PWMBSR2_CC7OF_MSK)
#define HSPWMB_CheckCC6OverFlag()       READ_HSPWMB_BIT(PWMB_SR2, PWMBSR2_CC6OF_MSK)
#define HSPWMB_CheckCC5OverFlag()       READ_HSPWMB_BIT(PWMB_SR2, PWMBSR2_CC5OF_MSK)
#define HSPWMB_ClearCC8OverFlag()       CLR_HSPWMB_BIT(PWMB_SR2, PWMBSR2_CC8OF_MSK)
#define HSPWMB_ClearCC7OverFlag()       CLR_HSPWMB_BIT(PWMB_SR2, PWMBSR2_CC7OF_MSK)
#define HSPWMB_ClearCC6OverFlag()       CLR_HSPWMB_BIT(PWMB_SR2, PWMBSR2_CC6OF_MSK)
#define HSPWMB_ClearCC5OverFlag()       CLR_HSPWMB_BIT(PWMB_SR2, PWMBSR2_CC5OF_MSK)

#define PWMCSR2_CC4OF_MSK               BIT4
#define PWMCSR2_CC3OF_MSK               BIT3
#define PWMCSR2_CC2OF_MSK               BIT2
#define PWMCSR2_CC1OF_MSK               BIT1
#define PWMC_CheckCC4OverFlag()         READ_REG_BIT(PWMC_SR2, PWMCSR2_CC4OF_MSK)
#define PWMC_CheckCC3OverFlag()         READ_REG_BIT(PWMC_SR2, PWMCSR2_CC3OF_MSK)
#define PWMC_CheckCC2OverFlag()         READ_REG_BIT(PWMC_SR2, PWMCSR2_CC2OF_MSK)
#define PWMC_CheckCC1OverFlag()         READ_REG_BIT(PWMC_SR2, PWMCSR2_CC1OF_MSK)
#define PWMC_ClearCC4OverFlag()         CLR_REG_BIT(PWMC_SR2, PWMCSR2_CC4OF_MSK)
#define PWMC_ClearCC3OverFlag()         CLR_REG_BIT(PWMC_SR2, PWMCSR2_CC3OF_MSK)
#define PWMC_ClearCC2OverFlag()         CLR_REG_BIT(PWMC_SR2, PWMCSR2_CC2OF_MSK)
#define PWMC_ClearCC1OverFlag()         CLR_REG_BIT(PWMC_SR2, PWMCSR2_CC1OF_MSK)

#define HSPWMC_CheckCC4OverFlag()       READ_HSPWMC_BIT(PWMC_SR2, PWMCSR2_CC4OF_MSK)
#define HSPWMC_CheckCC3OverFlag()       READ_HSPWMC_BIT(PWMC_SR2, PWMCSR2_CC3OF_MSK)
#define HSPWMC_CheckCC2OverFlag()       READ_HSPWMC_BIT(PWMC_SR2, PWMCSR2_CC2OF_MSK)
#define HSPWMC_CheckCC1OverFlag()       READ_HSPWMC_BIT(PWMC_SR2, PWMCSR2_CC1OF_MSK)
#define HSPWMC_ClearCC4OverFlag()       CLR_HSPWMC_BIT(PWMC_SR2, PWMCSR2_CC4OF_MSK)
#define HSPWMC_ClearCC3OverFlag()       CLR_HSPWMC_BIT(PWMC_SR2, PWMCSR2_CC3OF_MSK)
#define HSPWMC_ClearCC2OverFlag()       CLR_HSPWMC_BIT(PWMC_SR2, PWMCSR2_CC2OF_MSK)
#define HSPWMC_ClearCC1OverFlag()       CLR_HSPWMC_BIT(PWMC_SR2, PWMCSR2_CC1OF_MSK)

#define PWMDSR2_CC8OF_MSK               BIT4
#define PWMDSR2_CC7OF_MSK               BIT3
#define PWMDSR2_CC6OF_MSK               BIT2
#define PWMDSR2_CC5OF_MSK               BIT1
#define PWMD_CheckCC8OverFlag()         READ_REG_BIT(PWMD_SR2, PWMDSR2_CC8OF_MSK)
#define PWMD_CheckCC7OverFlag()         READ_REG_BIT(PWMD_SR2, PWMDSR2_CC7OF_MSK)
#define PWMD_CheckCC6OverFlag()         READ_REG_BIT(PWMD_SR2, PWMDSR2_CC6OF_MSK)
#define PWMD_CheckCC5OverFlag()         READ_REG_BIT(PWMD_SR2, PWMDSR2_CC5OF_MSK)
#define PWMD_ClearCC8OverFlag()         CLR_REG_BIT(PWMD_SR2, PWMDSR2_CC8OF_MSK)
#define PWMD_ClearCC7OverFlag()         CLR_REG_BIT(PWMD_SR2, PWMDSR2_CC7OF_MSK)
#define PWMD_ClearCC6OverFlag()         CLR_REG_BIT(PWMD_SR2, PWMDSR2_CC6OF_MSK)
#define PWMD_ClearCC5OverFlag()         CLR_REG_BIT(PWMD_SR2, PWMDSR2_CC5OF_MSK)

#define HSPWMD_CheckCC8OverFlag()       READ_HSPWMD_BIT(PWMD_SR2, PWMDSR2_CC8OF_MSK)
#define HSPWMD_CheckCC7OverFlag()       READ_HSPWMD_BIT(PWMD_SR2, PWMDSR2_CC7OF_MSK)
#define HSPWMD_CheckCC6OverFlag()       READ_HSPWMD_BIT(PWMD_SR2, PWMDSR2_CC6OF_MSK)
#define HSPWMD_CheckCC5OverFlag()       READ_HSPWMD_BIT(PWMD_SR2, PWMDSR2_CC5OF_MSK)
#define HSPWMD_ClearCC8OverFlag()       CLR_HSPWMD_BIT(PWMD_SR2, PWMDSR2_CC8OF_MSK)
#define HSPWMD_ClearCC7OverFlag()       CLR_HSPWMD_BIT(PWMD_SR2, PWMDSR2_CC7OF_MSK)
#define HSPWMD_ClearCC6OverFlag()       CLR_HSPWMD_BIT(PWMD_SR2, PWMDSR2_CC6OF_MSK)
#define HSPWMD_ClearCC5OverFlag()       CLR_HSPWMD_BIT(PWMD_SR2, PWMDSR2_CC5OF_MSK)

#define PWMESR2_CC4OF_MSK               BIT4
#define PWMESR2_CC3OF_MSK               BIT3
#define PWMESR2_CC2OF_MSK               BIT2
#define PWMESR2_CC1OF_MSK               BIT1
#define PWME_CheckCC4OverFlag()         READ_REG_BIT(PWME_SR2, PWMESR2_CC4OF_MSK)
#define PWME_CheckCC3OverFlag()         READ_REG_BIT(PWME_SR2, PWMESR2_CC3OF_MSK)
#define PWME_CheckCC2OverFlag()         READ_REG_BIT(PWME_SR2, PWMESR2_CC2OF_MSK)
#define PWME_CheckCC1OverFlag()         READ_REG_BIT(PWME_SR2, PWMESR2_CC1OF_MSK)
#define PWME_ClearCC4OverFlag()         CLR_REG_BIT(PWME_SR2, PWMESR2_CC4OF_MSK)
#define PWME_ClearCC3OverFlag()         CLR_REG_BIT(PWME_SR2, PWMESR2_CC3OF_MSK)
#define PWME_ClearCC2OverFlag()         CLR_REG_BIT(PWME_SR2, PWMESR2_CC2OF_MSK)
#define PWME_ClearCC1OverFlag()         CLR_REG_BIT(PWME_SR2, PWMESR2_CC1OF_MSK)

#define HSPWME_CheckCC4OverFlag()       READ_HSPWME_BIT(PWME_SR2, PWMESR2_CC4OF_MSK)
#define HSPWME_CheckCC3OverFlag()       READ_HSPWME_BIT(PWME_SR2, PWMESR2_CC3OF_MSK)
#define HSPWME_CheckCC2OverFlag()       READ_HSPWME_BIT(PWME_SR2, PWMESR2_CC2OF_MSK)
#define HSPWME_CheckCC1OverFlag()       READ_HSPWME_BIT(PWME_SR2, PWMESR2_CC1OF_MSK)
#define HSPWME_ClearCC4OverFlag()       CLR_HSPWME_BIT(PWME_SR2, PWMESR2_CC4OF_MSK)
#define HSPWME_ClearCC3OverFlag()       CLR_HSPWME_BIT(PWME_SR2, PWMESR2_CC3OF_MSK)
#define HSPWME_ClearCC2OverFlag()       CLR_HSPWME_BIT(PWME_SR2, PWMESR2_CC2OF_MSK)
#define HSPWME_ClearCC1OverFlag()       CLR_HSPWME_BIT(PWME_SR2, PWMESR2_CC1OF_MSK)

#define PWMFSR2_CC8OF_MSK               BIT4
#define PWMFSR2_CC7OF_MSK               BIT3
#define PWMFSR2_CC6OF_MSK               BIT2
#define PWMFSR2_CC5OF_MSK               BIT1
#define PWMF_CheckCC8OverFlag()         READ_REG_BIT(PWMF_SR2, PWMFSR2_CC8OF_MSK)
#define PWMF_CheckCC7OverFlag()         READ_REG_BIT(PWMF_SR2, PWMFSR2_CC7OF_MSK)
#define PWMF_CheckCC6OverFlag()         READ_REG_BIT(PWMF_SR2, PWMFSR2_CC6OF_MSK)
#define PWMF_CheckCC5OverFlag()         READ_REG_BIT(PWMF_SR2, PWMFSR2_CC5OF_MSK)
#define PWMF_ClearCC8OverFlag()         CLR_REG_BIT(PWMF_SR2, PWMFSR2_CC8OF_MSK)
#define PWMF_ClearCC7OverFlag()         CLR_REG_BIT(PWMF_SR2, PWMFSR2_CC7OF_MSK)
#define PWMF_ClearCC6OverFlag()         CLR_REG_BIT(PWMF_SR2, PWMFSR2_CC6OF_MSK)
#define PWMF_ClearCC5OverFlag()         CLR_REG_BIT(PWMF_SR2, PWMFSR2_CC5OF_MSK)

#define HSPWMF_CheckCC8OverFlag()       READ_HSPWMF_BIT(PWMF_SR2, PWMFSR2_CC8OF_MSK)
#define HSPWMF_CheckCC7OverFlag()       READ_HSPWMF_BIT(PWMF_SR2, PWMFSR2_CC7OF_MSK)
#define HSPWMF_CheckCC6OverFlag()       READ_HSPWMF_BIT(PWMF_SR2, PWMFSR2_CC6OF_MSK)
#define HSPWMF_CheckCC5OverFlag()       READ_HSPWMF_BIT(PWMF_SR2, PWMFSR2_CC5OF_MSK)
#define HSPWMF_ClearCC8OverFlag()       CLR_HSPWMF_BIT(PWMF_SR2, PWMFSR2_CC8OF_MSK)
#define HSPWMF_ClearCC7OverFlag()       CLR_HSPWMF_BIT(PWMF_SR2, PWMFSR2_CC7OF_MSK)
#define HSPWMF_ClearCC6OverFlag()       CLR_HSPWMF_BIT(PWMF_SR2, PWMFSR2_CC6OF_MSK)
#define HSPWMF_ClearCC5OverFlag()       CLR_HSPWMF_BIT(PWMF_SR2, PWMFSR2_CC5OF_MSK)

#define PORT_CheckFlag(p, b)            READ_REG_BIT(P##p##INTF, (b))
#define PORT_ClearFlag(p, b)            CLR_REG_BIT(P##p##INTF, (b))

#define CheckP0nFlag(b)                 PORT_CheckFlag(0, (b))
#define CheckP1nFlag(b)                 PORT_CheckFlag(1, (b))
#define CheckP2nFlag(b)                 PORT_CheckFlag(2, (b))
#define CheckP3nFlag(b)                 PORT_CheckFlag(3, (b))
#define CheckP4nFlag(b)                 PORT_CheckFlag(4, (b))
#define CheckP5nFlag(b)                 PORT_CheckFlag(5, (b))
#define CheckP6nFlag(b)                 PORT_CheckFlag(6, (b))
#define CheckP7nFlag(b)                 PORT_CheckFlag(7, (b))
#define CheckP8nFlag(b)                 PORT_CheckFlag(8, (b))
#define CheckP9nFlag(b)                 PORT_CheckFlag(9, (b))
#define CheckPAnFlag(b)                 PORT_CheckFlag(A, (b))
#define CheckPBnFlag(b)                 PORT_CheckFlag(B, (b))
#define ClearP0nFlag(b)                 PORT_ClearFlag(0, (b))
#define ClearP1nFlag(b)                 PORT_ClearFlag(1, (b))
#define ClearP2nFlag(b)                 PORT_ClearFlag(2, (b))
#define ClearP3nFlag(b)                 PORT_ClearFlag(3, (b))
#define ClearP4nFlag(b)                 PORT_ClearFlag(4, (b))
#define ClearP5nFlag(b)                 PORT_ClearFlag(5, (b))
#define ClearP6nFlag(b)                 PORT_ClearFlag(6, (b))
#define ClearP7nFlag(b)                 PORT_ClearFlag(7, (b))
#define ClearP8nFlag(b)                 PORT_ClearFlag(8, (b))
#define ClearP9nFlag(b)                 PORT_ClearFlag(9, (b))
#define ClearPAnFlag(b)                 PORT_ClearFlag(A, (b))
#define ClearPBnFlag(b)                 PORT_ClearFlag(B, (b))

#define UR1TOSR_TOIF_MSK                BIT0
#define UR2TOSR_TOIF_MSK                BIT0
#define UR3TOSR_TOIF_MSK                BIT0
#define UR4TOSR_TOIF_MSK                BIT0
#define UR5TOSR_TOIF_MSK                BIT0
#define UR6TOSR_TOIF_MSK                BIT0
#define UR7TOSR_TOIF_MSK                BIT0
#define UR8TOSR_TOIF_MSK                BIT0
#define SPITOSR_TOIF_MSK                BIT0
#define SPI2TOSR_TOIF_MSK               BIT0
#define SPI3TOSR_TOIF_MSK               BIT0
#define I2CTOSR_TOIF_MSK                BIT0
#define I2C2TOSR_TOIF_MSK               BIT0
#define UART1_CheckTimeoutFlag()        READ_REG_BIT(UR1TOSR, UR1TOSR_TOIF_MSK)
#define UART2_CheckTimeoutFlag()        READ_REG_BIT(UR2TOSR, UR2TOSR_TOIF_MSK)
#define UART3_CheckTimeoutFlag()        READ_REG_BIT(UR3TOSR, UR3TOSR_TOIF_MSK)
#define UART4_CheckTimeoutFlag()        READ_REG_BIT(UR4TOSR, UR4TOSR_TOIF_MSK)
#define UART5_CheckTimeoutFlag()        READ_REG_BIT(UR5TOSR, UR5TOSR_TOIF_MSK)
#define UART6_CheckTimeoutFlag()        READ_REG_BIT(UR6TOSR, UR6TOSR_TOIF_MSK)
#define UART7_CheckTimeoutFlag()        READ_REG_BIT(UR7TOSR, UR7TOSR_TOIF_MSK)
#define UART8_CheckTimeoutFlag()        READ_REG_BIT(UR8TOSR, UR8TOSR_TOIF_MSK)
#define SPI1_CheckTimeoutFlag()         READ_REG_BIT(SPITOSR, SPITOSR_TOIF_MSK)
#define SPI2_CheckTimeoutFlag()         READ_REG_BIT(SPI2TOSR, SPI2TOSR_TOIF_MSK)
#define SPI3_CheckTimeoutFlag()         READ_REG_BIT(SPI3TOSR, SPI3TOSR_TOIF_MSK)
#define I2C1_CheckTimeoutFlag()         READ_REG_BIT(I2CTOSR, I2CTOSR_TOIF_MSK)
#define I2C2_CheckTimeoutFlag()         READ_REG_BIT(I2C2TOSR, I2C2TOSR_TOIF_MSK)

#define UR1TOSR_CTOIF_MSK               BIT7
#define UR2TOSR_CTOIF_MSK               BIT7
#define UR3TOSR_CTOIF_MSK               BIT7
#define UR4TOSR_CTOIF_MSK               BIT7
#define UR5TOSR_CTOIF_MSK               BIT7
#define UR6TOSR_CTOIF_MSK               BIT7
#define UR7TOSR_CTOIF_MSK               BIT7
#define UR8TOSR_CTOIF_MSK               BIT7
#define SPITOSR_CTOIF_MSK               BIT7
#define SPI2TOSR_CTOIF_MSK              BIT7
#define SPI3TOSR_CTOIF_MSK              BIT7
#define I2CTOSR_CTOIF_MSK               BIT7
#define I2C2TOSR_CTOIF_MSK              BIT7
#define UART1_ClearTimeoutFlag()        SET_REG_BIT(UR1TOSR, UR1TOSR_CTOIF_MSK)
#define UART2_ClearTimeoutFlag()        SET_REG_BIT(UR2TOSR, UR2TOSR_CTOIF_MSK)
#define UART3_ClearTimeoutFlag()        SET_REG_BIT(UR3TOSR, UR3TOSR_CTOIF_MSK)
#define UART4_ClearTimeoutFlag()        SET_REG_BIT(UR4TOSR, UR4TOSR_CTOIF_MSK)
#define UART5_ClearTimeoutFlag()        SET_REG_BIT(UR5TOSR, UR5TOSR_CTOIF_MSK)
#define UART6_ClearTimeoutFlag()        SET_REG_BIT(UR6TOSR, UR6TOSR_CTOIF_MSK)
#define UART7_ClearTimeoutFlag()        SET_REG_BIT(UR7TOSR, UR7TOSR_CTOIF_MSK)
#define UART8_ClearTimeoutFlag()        SET_REG_BIT(UR8TOSR, UR8TOSR_CTOIF_MSK)
#define SPI1_ClearTimeoutFlag()         SET_REG_BIT(SPITOSR, SPITOSR_CTOIF_MSK)
#define SPI2_ClearTimeoutFlag()         SET_REG_BIT(SPI2TOSR, SPI2TOSR_CTOIF_MSK)
#define SPI3_ClearTimeoutFlag()         SET_REG_BIT(SPI3TOSR, SPI3TOSR_CTOIF_MSK)
#define I2C1_ClearTimeoutFlag()         SET_REG_BIT(I2CTOSR, I2CTOSR_CTOIF_MSK)
#define I2C2_ClearTimeoutFlag()         SET_REG_BIT(I2C2TOSR, I2C2TOSR_CTOIF_MSK)

#define I2SSR_TXE_MSK                   BIT1
#define I2SSR_RXNE_MSK                  BIT0
#define I2S1_CheckTXEFlag()             READ_REG_BIT(I2SSR, I2SSR_TXE_MSK)
#define I2S1_CheckRXNEFlag()            READ_REG_BIT(I2SSR, I2SSR_RXNE_MSK)
#define I2S1_ClearTXEFlag()             CLR_REG_BIT(I2SSR, I2SSR_TXE_MSK)
#define I2S1_ClearRXNEFlag()            CLR_REG_BIT(I2SSR, I2SSR_RXNE_MSK)

#define I2S2SR_TXE_MSK                  BIT1
#define I2S2SR_RXNE_MSK                 BIT0
#define I2S2_CheckTXEFlag()             READ_REG_BIT(I2S2SR, I2S2SR_TXE_MSK)
#define I2S2_CheckRXNEFlag()            READ_REG_BIT(I2S2SR, I2S2SR_RXNE_MSK)
#define I2S2_ClearTXEFlag()             CLR_REG_BIT(I2S2SR, I2S2SR_TXE_MSK)
#define I2S2_ClearRXNEFlag()            CLR_REG_BIT(I2S2SR, I2S2SR_RXNE_MSK)

#define QSPISR1_TOF_MSK                 BIT4
#define QSPISR1_SMF_MSK                 BIT3
#define QSPISR1_FTF_MSK                 BIT2
#define QSPISR1_TCF_MSK                 BIT1
#define QSPISR1_TEF_MSK                 BIT0
#define QSPI_CheckTimeout()             READ_REG_BIT(QSPI_SR1, QSPISR1_TOF_MSK)
#define QSPI_CheckMatch()               READ_REG_BIT(QSPI_SR1, QSPISR1_SMF_MSK)
#define QSPI_CheckFIFO()                READ_REG_BIT(QSPI_SR1, QSPISR1_FTF_MSK)
#define QSPI_CheckTransfer()            READ_REG_BIT(QSPI_SR1, QSPISR1_TCF_MSK)
#define QSPI_CheckError()               READ_REG_BIT(QSPI_SR1, QSPISR1_TEF_MSK)

#define QSPIFCR_CTOF_MSK                BIT4
#define QSPIFCR_CSMF_MSK                BIT3
#define QSPIFCR_CTCF_MSK                BIT1
#define QSPIFCR_CTEF_MSK                BIT0
#define QSPI_ClearTimeout()             SET_REG_BIT(QSPI_FCR, QSPIFCR_CTOF_MSK)
#define QSPI_ClearMatch()               SET_REG_BIT(QSPI_FCR, QSPIFCR_CSMF_MSK)
#define QSPI_ClearTransfer()            SET_REG_BIT(QSPI_FCR, QSPIFCR_CTCF_MSK)
#define QSPI_ClearError()               SET_REG_BIT(QSPI_FCR, QSPIFCR_CTEF_MSK)

#define DMAM2MSTA_M2MIF_MSK             BIT0
#define DMAADCSTA_ADCIF_MSK             BIT0
#define DMAADC2STA_ADC2IF_MSK           BIT0
#define DMADAC1STA_DAC1IF_MSK           BIT0
#define DMADAC2STA_DAC2IF_MSK           BIT0
#define DMASPISTA_SPIIF_MSK             BIT0
#define DMASPI2STA_SPI2IF_MSK           BIT0
#define DMASPI3STA_SPI3IF_MSK           BIT0
#define DMAQSPISTA_QSPIIF_MSK           BIT0
#define DMALCMSTA_LCMIF_MSK             BIT0
#define DMAUR1TSTA_UR1TIF_MSK           BIT0
#define DMAUR1RSTA_UR1RIF_MSK           BIT0
#define DMAUR2TSTA_UR2TIF_MSK           BIT0
#define DMAUR2RSTA_UR2RIF_MSK           BIT0
#define DMAUR3TSTA_UR3TIF_MSK           BIT0
#define DMAUR3RSTA_UR3RIF_MSK           BIT0
#define DMAUR4TSTA_UR4TIF_MSK           BIT0
#define DMAUR4RSTA_UR4RIF_MSK           BIT0
#define DMAUR5TSTA_UR5TIF_MSK           BIT0
#define DMAUR5RSTA_UR5RIF_MSK           BIT0
#define DMAUR6TSTA_UR6TIF_MSK           BIT0
#define DMAUR6RSTA_UR6RIF_MSK           BIT0
#define DMAUR7TSTA_UR7TIF_MSK           BIT0
#define DMAUR7RSTA_UR7RIF_MSK           BIT0
#define DMAUR8TSTA_UR8TIF_MSK           BIT0
#define DMAUR8RSTA_UR8RIF_MSK           BIT0
#define DMAI2CTSTA_I2CTIF_MSK           BIT0
#define DMAI2CRSTA_I2CRIF_MSK           BIT0
#define DMAI2C2TSTA_I2C2TIF_MSK         BIT0
#define DMAI2C2RSTA_I2C2RIF_MSK         BIT0
#define DMAI2STSTA_I2STIF_MSK           BIT0
#define DMAI2SRSTA_I2SRIF_MSK           BIT0
#define DMAI2S2TSTA_I2S2TIF_MSK         BIT0
#define DMAI2S2RSTA_I2S2RIF_MSK         BIT0
#define DMAPWMATSTA_PWMATIF_MSK         BIT0
#define DMAPWMARSTA_PWMARIF_MSK         BIT0
#define DMAPWMCTSTA_PWMCTIF_MSK         BIT0
#define DMAPWMCRSTA_PWMCRIF_MSK         BIT0
#define DMAPWMETSTA_PWMETIF_MSK         BIT0
#define DMAPWMERSTA_PWMERIF_MSK         BIT0
#define DMACAN1TSTA_CAN1TIF_MSK         BIT0
#define DMACAN1RSTA_CAN1RIF_MSK         BIT0
#define DMACAN2TSTA_CAN2TIF_MSK         BIT0
#define DMACAN2RSTA_CAN2RIF_MSK         BIT0
#define DMA_M2M_CheckFlag()             READ_REG_BIT(DMA_M2M_STA,   DMAM2MSTA_M2MIF_MSK)
#define DMA_ADC1_CheckFlag()            READ_REG_BIT(DMA_ADC_STA,   DMAADCSTA_ADCIF_MSK)
#define DMA_ADC2_CheckFlag()            READ_REG_BIT(DMA_ADC2_STA,  DMAADC2STA_ADC2IF_MSK)
#define DMA_DAC1_CheckFlag()            READ_REG_BIT(DMA_DAC1_STA,  DMADAC1STA_DAC1IF_MSK)
#define DMA_DAC2_CheckFlag()            READ_REG_BIT(DMA_DAC2_STA,  DMADAC2STA_DAC2IF_MSK)
#define DMA_SPI1_CheckFlag()            READ_REG_BIT(DMA_SPI_STA,   DMASPISTA_SPIIF_MSK)
#define DMA_SPI2_CheckFlag()            READ_REG_BIT(DMA_SPI2_STA,  DMASPI2STA_SPI2IF_MSK)
#define DMA_SPI3_CheckFlag()            READ_REG_BIT(DMA_SPI3_STA,  DMASPI3STA_SPI3IF_MSK)
#define DMA_QSPI_CheckFlag()            READ_REG_BIT(DMA_QSPI_STA,  DMAQSPISTA_QSPIIF_MSK)
#define DMA_LCM_CheckFlag()             READ_REG_BIT(DMA_LCM_STA,   DMALCMSTA_LCMIF_MSK)
#define DMA_UART1_CheckTxFlag()         READ_REG_BIT(DMA_UR1T_STA,  DMAUR1TSTA_UR1TIF_MSK)
#define DMA_UART1_CheckRxFlag()         READ_REG_BIT(DMA_UR1R_STA,  DMAUR1RSTA_UR1RIF_MSK)
#define DMA_UART2_CheckTxFlag()         READ_REG_BIT(DMA_UR2T_STA,  DMAUR2TSTA_UR2TIF_MSK)
#define DMA_UART2_CheckRxFlag()         READ_REG_BIT(DMA_UR2R_STA,  DMAUR2RSTA_UR2RIF_MSK)
#define DMA_UART3_CheckTxFlag()         READ_REG_BIT(DMA_UR3T_STA,  DMAUR3TSTA_UR3TIF_MSK)
#define DMA_UART3_CheckRxFlag()         READ_REG_BIT(DMA_UR3R_STA,  DMAUR3RSTA_UR3RIF_MSK)
#define DMA_UART4_CheckTxFlag()         READ_REG_BIT(DMA_UR4T_STA,  DMAUR4TSTA_UR4TIF_MSK)
#define DMA_UART4_CheckRxFlag()         READ_REG_BIT(DMA_UR4R_STA,  DMAUR4RSTA_UR4RIF_MSK)
#define DMA_UART5_CheckTxFlag()         READ_REG_BIT(DMA_UR5T_STA,  DMAUR5TSTA_UR5TIF_MSK)
#define DMA_UART5_CheckRxFlag()         READ_REG_BIT(DMA_UR5R_STA,  DMAUR5RSTA_UR5RIF_MSK)
#define DMA_UART6_CheckTxFlag()         READ_REG_BIT(DMA_UR6T_STA,  DMAUR6TSTA_UR6TIF_MSK)
#define DMA_UART6_CheckRxFlag()         READ_REG_BIT(DMA_UR6R_STA,  DMAUR6RSTA_UR6RIF_MSK)
#define DMA_UART7_CheckTxFlag()         READ_REG_BIT(DMA_UR7T_STA,  DMAUR7TSTA_UR7TIF_MSK)
#define DMA_UART7_CheckRxFlag()         READ_REG_BIT(DMA_UR7R_STA,  DMAUR7RSTA_UR7RIF_MSK)
#define DMA_UART8_CheckTxFlag()         READ_REG_BIT(DMA_UR8T_STA,  DMAUR8TSTA_UR8TIF_MSK)
#define DMA_UART8_CheckRxFlag()         READ_REG_BIT(DMA_UR8R_STA,  DMAUR8RSTA_UR8RIF_MSK)
#define DMA_I2C1_CheckTxFlag()          READ_REG_BIT(DMA_I2CT_STA,  DMAI2CTSTA_I2CTIF_MSK)
#define DMA_I2C1_CheckRxFlag()          READ_REG_BIT(DMA_I2CR_STA,  DMAI2CRSTA_I2CRIF_MSK)
#define DMA_I2C2_CheckTxFlag()          READ_REG_BIT(DMA_I2C2T_STA, DMAI2C2TSTA_I2C2TIF_MSK)
#define DMA_I2C2_CheckRxFlag()          READ_REG_BIT(DMA_I2C2R_STA, DMAI2C2RSTA_I2C2RIF_MSK)
#define DMA_I2S1_CheckTxFlag()          READ_REG_BIT(DMA_I2ST_STA,  DMAI2STSTA_I2STIF_MSK)
#define DMA_I2S1_CheckRxFlag()          READ_REG_BIT(DMA_I2SR_STA,  DMAI2SRSTA_I2SRIF_MSK)
#define DMA_I2S2_CheckTxFlag()          READ_REG_BIT(DMA_I2S2T_STA, DMAI2S2TSTA_I2S2TIF_MSK)
#define DMA_I2S2_CheckRxFlag()          READ_REG_BIT(DMA_I2S2R_STA, DMAI2S2RSTA_I2S2RIF_MSK)
#define DMA_PWMA_CheckTxFlag()          READ_REG_BIT(DMA_PWMAT_STA, DMAPWMATSTA_PWMATIF_MSK)
#define DMA_PWMA_CheckRxFlag()          READ_REG_BIT(DMA_PWMAR_STA, DMAPWMARSTA_PWMARIF_MSK)
#define DMA_PWMC_CheckTxFlag()          READ_REG_BIT(DMA_PWMCT_STA, DMAPWMCTSTA_PWMCTIF_MSK)
#define DMA_PWMC_CheckRxFlag()          READ_REG_BIT(DMA_PWMCR_STA, DMAPWMCRSTA_PWMCRIF_MSK)
#define DMA_PWME_CheckTxFlag()          READ_REG_BIT(DMA_PWMET_STA, DMAPWMETSTA_PWMETIF_MSK)
#define DMA_PWME_CheckRxFlag()          READ_REG_BIT(DMA_PWMER_STA, DMAPWMERSTA_PWMERIF_MSK)
#define DMA_CAN1_CheckTxFlag()          READ_REG_BIT(DMA_CAN1T_STA,  DMACAN1TSTA_CAN1TIF_MSK)
#define DMA_CAN1_CheckRxFlag()          READ_REG_BIT(DMA_CAN1R_STA,  DMACAN1RSTA_CAN1RIF_MSK)
#define DMA_CAN2_CheckTxFlag()          READ_REG_BIT(DMA_CAN2T_STA,  DMACAN2TSTA_CAN2TIF_MSK)
#define DMA_CAN2_CheckRxFlag()          READ_REG_BIT(DMA_CAN2R_STA,  DMACAN2RSTA_CAN2RIF_MSK)
#define DMA_M2M_ClearFlag()             CLR_REG_BIT(DMA_M2M_STA,   DMAM2MSTA_M2MIF_MSK)
#define DMA_ADC1_ClearFlag()            CLR_REG_BIT(DMA_ADC_STA,   DMAADCSTA_ADCIF_MSK)
#define DMA_ADC2_ClearFlag()            CLR_REG_BIT(DMA_ADC2_STA,  DMAADC2STA_ADC2IF_MSK)
#define DMA_DAC1_ClearFlag()            CLR_REG_BIT(DMA_DAC1_STA,  DMADAC1STA_DAC1IF_MSK)
#define DMA_DAC2_ClearFlag()            CLR_REG_BIT(DMA_DAC2_STA,  DMADAC2STA_DAC2IF_MSK)
#define DMA_SPI1_ClearFlag()            CLR_REG_BIT(DMA_SPI_STA,   DMASPISTA_SPIIF_MSK)
#define DMA_SPI2_ClearFlag()            CLR_REG_BIT(DMA_SPI2_STA,  DMASPI2STA_SPI2IF_MSK)
#define DMA_SPI3_ClearFlag()            CLR_REG_BIT(DMA_SPI3_STA,  DMASPI3STA_SPI3IF_MSK)
#define DMA_QSPI_ClearFlag()            CLR_REG_BIT(DMA_QSPI_STA,  DMAQSPISTA_QSPIIF_MSK)
#define DMA_LCM_ClearFlag()             CLR_REG_BIT(DMA_LCM_STA,   DMALCMSTA_LCMIF_MSK)
#define DMA_UART1_ClearTxFlag()         CLR_REG_BIT(DMA_UR1T_STA,  DMAUR1TSTA_UR1TIF_MSK)
#define DMA_UART1_ClearRxFlag()         CLR_REG_BIT(DMA_UR1R_STA,  DMAUR1RSTA_UR1RIF_MSK)
#define DMA_UART2_ClearTxFlag()         CLR_REG_BIT(DMA_UR2T_STA,  DMAUR2TSTA_UR2TIF_MSK)
#define DMA_UART2_ClearRxFlag()         CLR_REG_BIT(DMA_UR2R_STA,  DMAUR2RSTA_UR2RIF_MSK)
#define DMA_UART3_ClearTxFlag()         CLR_REG_BIT(DMA_UR3T_STA,  DMAUR3TSTA_UR3TIF_MSK)
#define DMA_UART3_ClearRxFlag()         CLR_REG_BIT(DMA_UR3R_STA,  DMAUR3RSTA_UR3RIF_MSK)
#define DMA_UART4_ClearTxFlag()         CLR_REG_BIT(DMA_UR4T_STA,  DMAUR4TSTA_UR4TIF_MSK)
#define DMA_UART4_ClearRxFlag()         CLR_REG_BIT(DMA_UR4R_STA,  DMAUR4RSTA_UR4RIF_MSK)
#define DMA_UART5_ClearTxFlag()         CLR_REG_BIT(DMA_UR5T_STA,  DMAUR5TSTA_UR5TIF_MSK)
#define DMA_UART5_ClearRxFlag()         CLR_REG_BIT(DMA_UR5R_STA,  DMAUR5RSTA_UR5RIF_MSK)
#define DMA_UART6_ClearTxFlag()         CLR_REG_BIT(DMA_UR6T_STA,  DMAUR6TSTA_UR6TIF_MSK)
#define DMA_UART6_ClearRxFlag()         CLR_REG_BIT(DMA_UR6R_STA,  DMAUR6RSTA_UR6RIF_MSK)
#define DMA_UART7_ClearTxFlag()         CLR_REG_BIT(DMA_UR7T_STA,  DMAUR7TSTA_UR7TIF_MSK)
#define DMA_UART7_ClearRxFlag()         CLR_REG_BIT(DMA_UR7R_STA,  DMAUR7RSTA_UR7RIF_MSK)
#define DMA_UART8_ClearTxFlag()         CLR_REG_BIT(DMA_UR8T_STA,  DMAUR8TSTA_UR8TIF_MSK)
#define DMA_UART8_ClearRxFlag()         CLR_REG_BIT(DMA_UR8R_STA,  DMAUR8RSTA_UR8RIF_MSK)
#define DMA_I2C1_ClearTxFlag()          CLR_REG_BIT(DMA_I2CT_STA,  DMAI2CTSTA_I2CTIF_MSK)
#define DMA_I2C1_ClearRxFlag()          CLR_REG_BIT(DMA_I2CR_STA,  DMAI2CRSTA_I2CRIF_MSK)
#define DMA_I2C2_ClearTxFlag()          CLR_REG_BIT(DMA_I2C2T_STA, DMAI2C2TSTA_I2C2TIF_MSK)
#define DMA_I2C2_ClearRxFlag()          CLR_REG_BIT(DMA_I2C2R_STA, DMAI2C2RSTA_I2C2RIF_MSK)
#define DMA_I2S1_ClearTxFlag()          CLR_REG_BIT(DMA_I2ST_STA,  DMAI2STSTA_I2STIF_MSK)
#define DMA_I2S1_ClearRxFlag()          CLR_REG_BIT(DMA_I2SR_STA,  DMAI2SRSTA_I2SRIF_MSK)
#define DMA_I2S2_ClearTxFlag()          CLR_REG_BIT(DMA_I2S2T_STA, DMAI2S2TSTA_I2S2TIF_MSK)
#define DMA_I2S2_ClearRxFlag()          CLR_REG_BIT(DMA_I2S2R_STA, DMAI2S2RSTA_I2S2RIF_MSK)
#define DMA_PWMA_ClearTxFlag()          CLR_REG_BIT(DMA_PWMAT_STA, DMAPWMATSTA_PWMATIF_MSK)
#define DMA_PWMA_ClearRxFlag()          CLR_REG_BIT(DMA_PWMAR_STA, DMAPWMARSTA_PWMARIF_MSK)
#define DMA_PWMC_ClearTxFlag()          CLR_REG_BIT(DMA_PWMCT_STA, DMAPWMCTSTA_PWMCTIF_MSK)
#define DMA_PWMC_ClearRxFlag()          CLR_REG_BIT(DMA_PWMCR_STA, DMAPWMCRSTA_PWMCRIF_MSK)
#define DMA_PWME_ClearTxFlag()          CLR_REG_BIT(DMA_PWMET_STA, DMAPWMETSTA_PWMETIF_MSK)
#define DMA_PWME_ClearRxFlag()          CLR_REG_BIT(DMA_PWMER_STA, DMAPWMERSTA_PWMERIF_MSK)
#define DMA_CAN1_ClearTxFlag()          CLR_REG_BIT(DMA_CAN1T_STA, DMACAN1TSTA_CAN1TIF_MSK)
#define DMA_CAN1_ClearRxFlag()          CLR_REG_BIT(DMA_CAN1R_STA, DMACAN1RSTA_CAN1RIF_MSK)
#define DMA_CAN2_ClearTxFlag()          CLR_REG_BIT(DMA_CAN2T_STA, DMACAN2TSTA_CAN2TIF_MSK)
#define DMA_CAN2_ClearRxFlag()          CLR_REG_BIT(DMA_CAN2R_STA, DMACAN2RSTA_CAN2RIF_MSK)

#define IPH_PX0H_MSK                    BIT0
#define INT0_SetIntPriority(n)          PX0 = ((n) & 1); \
                                        MODIFY_REG(IPH, IPH_PX0H_MSK, ((((n) >> 1) & 1) << 0))

#define IPH_PX1H_MSK                    BIT2
#define INT1_SetIntPriority(n)          PX1 = ((n) & 1); \
                                        MODIFY_REG(IPH, IPH_PX1H_MSK, ((((n) >> 1) & 1) << 2))

#define IP2_PX4_MSK                     BIT4
#define IP2H_PX4H_MSK                   BIT4
#define INT4_SetIntPriority(n)          MODIFY_REG(IP2, IP2_PX4_MSK, (((n) & 1) << 4)); \
                                        MODIFY_REG(IP2H, IP2H_PX4H_MSK, ((((n) >> 1) & 1) << 4))

#define IPH_PT0H_MSK                    BIT1
#define TIMER0_SetIntPriority(n)        PT0 = ((n) & 1); \
                                        MODIFY_REG(IPH, IPH_PT0H_MSK, ((((n) >> 1) & 1) << 1))

#define IPH_PT1H_MSK                    BIT3
#define TIMER1_SetIntPriority(n)        PT1 = ((n) & 1); \
                                        MODIFY_REG(IPH, IPH_PT1H_MSK, ((((n) >> 1) & 1) << 3))

#define T6T5CFG_PT5_MSK                 (BIT2 | BIT1)
#define TIMER5_SetIntPriority(n)        MODIFY_REG(T6T5CFG, T6T5CFG_PT5_MSK, ((n) << 1))

#define T6T5CFG_PT6_MSK                 (BIT6 | BIT5)
#define TIMER6_SetIntPriority(n)        MODIFY_REG(T6T5CFG, T6T5CFG_PT6_MSK, ((n) << 5))

#define T8T7CFG_PT7_MSK                 (BIT2 | BIT1)
#define TIMER7_SetIntPriority(n)        MODIFY_REG(T8T7CFG, T8T7CFG_PT7_MSK, ((n) << 1))

#define T8T7CFG_PT8_MSK                 (BIT6 | BIT5)
#define TIMER8_SetIntPriority(n)        MODIFY_REG(T8T7CFG, T8T7CFG_PT8_MSK, ((n) << 5))

#define T10T9CFG_PT9_MSK                (BIT2 | BIT1)
#define TIMER9_SetIntPriority(n)        MODIFY_REG(T10T9CFG, T10T9CFG_PT9_MSK, ((n) << 1))

#define T10T9CFG_PT10_MSK               (BIT6 | BIT5)
#define TIMER10_SetIntPriority(n)       MODIFY_REG(T10T9CFG, T10T9CFG_PT10_MSK, ((n) << 5))

#define T18T17CFG_PT17_MSK              (BIT2 | BIT1)
#define TIMER17_SetIntPriority(n)       MODIFY_REG(T18T17CFG, T18T17CFG_PT17_MSK, ((n) << 1))

#define T18T17CFG_PT18_MSK              (BIT6 | BIT5)
#define TIMER18_SetIntPriority(n)       MODIFY_REG(T18T17CFG, T18T17CFG_PT18_MSK, ((n) << 5))

#define IPH_PSH_MSK                     BIT4
#define UART1_SetIntPriority(n)         PS = ((n) & 1); \
                                        MODIFY_REG(IPH, IPH_PSH_MSK, ((((n) >> 1) & 1) << 4))

#define IP2_PS2_MSK                     BIT0
#define IP2H_PS2H_MSK                   BIT0
#define UART2_SetIntPriority(n)         MODIFY_REG(IP2, IP2_PS2_MSK, (((n) & 1) << 0)); \
                                        MODIFY_REG(IP2H, IP2H_PS2H_MSK, ((((n) >> 1) & 1) << 0))

#define IP3_PS3_MSK                     BIT0
#define IP3H_PS3H_MSK                   BIT0
#define UART3_SetIntPriority(n)         MODIFY_REG(IP3, IP3_PS3_MSK, (((n) & 1) << 0)); \
                                        MODIFY_REG(IP3H, IP3H_PS3H_MSK, ((((n) >> 1) & 1) << 0))

#define IP3_PS4_MSK                     BIT1
#define IP3H_PS4H_MSK                   BIT1
#define UART4_SetIntPriority(n)         MODIFY_REG(IP3, IP3_PS4_MSK, (((n) & 1) << 1)); \
                                        MODIFY_REG(IP3H, IP3H_PS4H_MSK, ((((n) >> 1) & 1) << 1))

#define S5INTR_PS5_MSK                  (BIT5 | BIT4)
#define UART5_SetIntPriority(n)         MODIFY_REG(S5INTR, S5INTR_PS5_MSK, ((n) << 4))

#define S6INTR_PS6_MSK                  (BIT5 | BIT4)
#define UART6_SetIntPriority(n)         MODIFY_REG(S6INTR, S6INTR_PS6_MSK, ((n) << 4))

#define S7INTR_PS7_MSK                  (BIT5 | BIT4)
#define UART7_SetIntPriority(n)         MODIFY_REG(S7INTR, S7INTR_PS7_MSK, ((n) << 4))

#define S8INTR_PS8_MSK                  (BIT5 | BIT4)
#define UART8_SetIntPriority(n)         MODIFY_REG(S8INTR, S8INTR_PS8_MSK, ((n) << 4))

#define IPH_PLVDH_MSK                   BIT6
#define LVD_SetIntPriority(n)           PLVD = ((n) & 1); \
                                        MODIFY_REG(IPH, IPH_PLVDH_MSK, ((((n) >> 1) & 1) << 6))

#define IPH_PADCH_MSK                   BIT5
#define ADC1_SetIntPriority(n)          PADC = ((n) & 1); \
                                        MODIFY_REG(IPH, IPH_PADCH_MSK, ((((n) >> 1) & 1) << 5))

#define ADC2INTR_PADC2_MSK              (BIT2 | BIT1)
#define ADC2_SetIntPriority(n)          MODIFY_REG(ADC2INTR, ADC2INTR_PADC2_MSK, ((n) << 1))

#define DAC1CR1_PDAC1_MSK               (BIT3 | BIT2)
#define DAC1_SetIntPriority(n)          MODIFY_REG(DAC1_CR, DAC1CR1_PDAC1_MSK, ((n) << 2))

#define DAC2CR1_PDAC2_MSK               (BIT3 | BIT2)
#define DAC2_SetIntPriority(n)          MODIFY_REG(DAC2_CR, DAC2CR1_PDAC2_MSK, ((n) << 2))

#define IP2_PSPI_MSK                    BIT1
#define IP2H_PSPIH_MSK                  BIT1
#define SPI1_SetIntPriority(n)          MODIFY_REG(IP2, IP2_PSPI_MSK, (((n) & 1) << 1)); \
                                        MODIFY_REG(IP2H, IP2H_PSPIH_MSK, ((((n) >> 1) & 1) << 1))

#define SPI2INTR_PSPI2_MSK              (BIT5 | BIT4)
#define SPI2_SetIntPriority(n)          MODIFY_REG(SPI2INTR, SPI2INTR_PSPI2_MSK, ((n) << 4))

#define SPI3INTR_PSPI3_MSK              (BIT5 | BIT4)
#define SPI3_SetIntPriority(n)          MODIFY_REG(SPI3INTR, SPI3INTR_PSPI3_MSK, ((n) << 4))

#define IP2_PCMP_MSK                    BIT5
#define IP2H_PCMPH_MSK                  BIT5
#define CMP1_SetIntPriority(n)          MODIFY_REG(IP2, IP2_PCMP_MSK, (((n) & 1) << 5)); \
                                        MODIFY_REG(IP2H, IP2H_PCMPH_MSK, ((((n) >> 1) & 1) << 5))

#define CMP2CR1_PCMP2_MSK               (BIT3 | BIT2)
#define CMP2_SetIntPriority(n)          MODIFY_REG(CMP2_6P6N_CR1, CMP2CR1_PCMP2_MSK, ((n) << 2))

#define CMP3CR1_PCMP3_MSK               (BIT3 | BIT2)
#define CMP3_SetIntPriority(n)          MODIFY_REG(CMP3_6P6N_CR1, CMP3CR1_PCMP3_MSK, ((n) << 2))

#define CMP4CR1_PCMP4_MSK               (BIT3 | BIT2)
#define CMP4_SetIntPriority(n)          MODIFY_REG(CMP4_6P6N_CR1, CMP4CR1_PCMP4_MSK, ((n) << 2))

#define IP3_PRTC_MSK                    BIT2
#define IP3H_PRTCH_MSK                  BIT2
#define RTC_SetIntPriority(n)           MODIFY_REG(IP3, IP3_PRTC_MSK, (((n) & 1) << 2)); \
                                        MODIFY_REG(IP3H, IP3H_PRTCH_MSK, ((((n) >> 1) & 1) << 2))

#define IP2_PI2C_MSK                    BIT6
#define IP2H_PI2CH_MSK                  BIT6
#define I2C1_SetIntPriority(n)          MODIFY_REG(IP2, IP2_PI2C_MSK, (((n) & 1) << 6)); \
                                        MODIFY_REG(IP2H, IP2H_PI2CH_MSK, ((((n) >> 1) & 1) << 6))

#define IP3_PI2C2_MSK                   BIT5
#define IP3H_PI2C2H_MSK                 BIT5
#define I2C2_SetIntPriority(n)          MODIFY_REG(IP3, IP3_PI2C2_MSK, (((n) & 1) << 5)); \
                                        MODIFY_REG(IP3H, IP3H_PI2C2H_MSK, ((((n) >> 1) & 1) << 5))

#define IP3_PI2S_MSK                    BIT3
#define IP3H_PI2SH_MSK                  BIT3
#define I2S1_SetIntPriority(n)          MODIFY_REG(IP3, IP3_PI2S_MSK, (((n) & 1) << 3)); \
                                        MODIFY_REG(IP3H, IP3H_PI2SH_MSK, ((((n) >> 1) & 1) << 3))

#define IP3_PI2S2_MSK                   BIT4
#define IP3H_PI2S2H_MSK                 BIT4
#define I2S2_SetIntPriority(n)          MODIFY_REG(IP3, IP3_PI2S2_MSK, (((n) & 1) << 4)); \
                                        MODIFY_REG(IP3H, IP3H_PI2S2H_MSK, ((((n) >> 1) & 1) << 4))

#define IP2_PUSB_MSK                    BIT7
#define IP2H_PUSBH_MSK                  BIT7
#define USB_SetIntPriority(n)           MODIFY_REG(IP2, IP2_PUSB_MSK, (((n) & 1) << 7)); \
                                        MODIFY_REG(IP2H, IP2H_PUSBH_MSK, ((((n) >> 1) & 1) << 7))

#define IP2_PPWMA_MSK                   BIT2
#define IP2H_PPWMAH_MSK                 BIT2
#define PWMA_SetIntPriority(n)          MODIFY_REG(IP2, IP2_PPWMA_MSK, (((n) & 1) << 2)); \
                                        MODIFY_REG(IP2H, IP2H_PPWMAH_MSK, ((((n) >> 1) & 1) << 2))
#define HSPWMA_SetIntPriority(n)        PWMA_SetIntPriority(n)

#define IP2_PPWMB_MSK                   BIT3
#define IP2H_PPWMBH_MSK                 BIT3
#define PWMB_SetIntPriority(n)          MODIFY_REG(IP2, IP2_PPWMB_MSK, (((n) & 1) << 3)); \
                                        MODIFY_REG(IP2H, IP2H_PPWMBH_MSK, ((((n) >> 1) & 1) << 3))
#define HSPWMB_SetIntPriority(n)        PWMB_SetIntPriority(n)

#define IP3_PPWMC_MSK                   BIT6
#define IP3H_PPWMCH_MSK                 BIT6
#define PWMC_SetIntPriority(n)          MODIFY_REG(IP3, IP3_PPWMC_MSK, (((n) & 1) << 6)); \
                                        MODIFY_REG(IP3H, IP3H_PPWMCH_MSK, ((((n) >> 1) & 1) << 6))
#define HSPWMC_SetIntPriority(n)        PWMC_SetIntPriority(n)

#define IP3_PPWMD_MSK                   BIT7
#define IP3H_PPWMDH_MSK                 BIT7
#define PWMD_SetIntPriority(n)          MODIFY_REG(IP3, IP3_PPWMD_MSK, (((n) & 1) << 7)); \
                                        MODIFY_REG(IP3H, IP3H_PPWMDH_MSK, ((((n) >> 1) & 1) << 7))
#define HSPWMD_SetIntPriority(n)        PWMD_SetIntPriority(n)

#define IP4_PPWME_MSK                   BIT0
#define IP4H_PPWMEH_MSK                 BIT0
#define PWME_SetIntPriority(n)          MODIFY_REG(IP4, IP4_PPWME_MSK, (((n) & 1) << 0)); \
                                        MODIFY_REG(IP4H, IP4H_PPWMEH_MSK, ((((n) >> 1) & 1) << 0))
#define HSPWME_SetIntPriority(n)        PWME_SetIntPriority(n)

#define IP4_PPWMF_MSK                   BIT1
#define IP4H_PPWMFH_MSK                 BIT1
#define PWMF_SetIntPriority(n)          MODIFY_REG(IP4, IP4_PPWMF_MSK, (((n) & 1) << 1)); \
                                        MODIFY_REG(IP4H, IP4H_PPWMFH_MSK, ((((n) >> 1) & 1) << 1))
#define HSPWMF_SetIntPriority(n)        PWMF_SetIntPriority(n)

#define LCMIFIP_MSK                     (BIT5 | BIT4)
#define LCM_SetIntPriority(n)           MODIFY_REG(LCMIFCFG, LCMIFIP_MSK, ((n) << 4))

#define PORT_SetIntPriority(p, n)       MODIFY_REG(PINIPL, BIT(p), (((n) & 0x01) << (p))); \
                                        MODIFY_REG(PINIPH, BIT(p), ((((n) >> 1) & 0x01) << (p)))

#define PORT_SetIntPriority2(p, n)      MODIFY_REG(PIN2IPL, BIT(p), (((n) & 0x01) << (p))); \
                                        MODIFY_REG(PIN2IPH, BIT(p), ((((n) >> 1) & 0x01) << (p)))

#define SetP0IntPriority(n)             PORT_SetIntPriority(0, (n))
#define SetP1IntPriority(n)             PORT_SetIntPriority(1, (n))
#define SetP2IntPriority(n)             PORT_SetIntPriority(2, (n))
#define SetP3IntPriority(n)             PORT_SetIntPriority(3, (n))
#define SetP4IntPriority(n)             PORT_SetIntPriority(4, (n))
#define SetP5IntPriority(n)             PORT_SetIntPriority(5, (n))
#define SetP6IntPriority(n)             PORT_SetIntPriority(6, (n))
#define SetP7IntPriority(n)             PORT_SetIntPriority(7, (n))
#define SetP8IntPriority(n)             PORT_SetIntPriority2(0, (n))
#define SetP9IntPriority(n)             PORT_SetIntPriority2(1, (n))
#define SetPAIntPriority(n)             PORT_SetIntPriority2(2, (n))
#define SetPBIntPriority(n)             PORT_SetIntPriority2(3, (n))

#define QSPIIP_MSK                      (BIT3 | BIT2)
#define QSPI_SetIntPriority(n)          MODIFY_REG(QSPI_DCR1, QSPIIP_MSK, ((n) << 2))

#define DMAM2MCFG_M2MIP_MSK             (BIT3 | BIT2)
#define DMAADCCFG_ADCIP_MSK             (BIT3 | BIT2)
#define DMAADC2CFG_ADC2IP_MSK           (BIT3 | BIT2)
#define DMADAC1CFG_DAC1IP_MSK           (BIT3 | BIT2)
#define DMADAC2CFG_DAC2IP_MSK           (BIT3 | BIT2)
#define DMASPICFG_SPIIP_MSK             (BIT3 | BIT2)
#define DMASPI2CFG_SPI2IP_MSK           (BIT3 | BIT2)
#define DMASPI3CFG_SPI3IP_MSK           (BIT3 | BIT2)
#define DMAQSPICFG_QSPIIP_MSK           (BIT3 | BIT2)
#define DMALCMCFG_LCMIP_MSK             (BIT3 | BIT2)
#define DMAUR1TCFG_UR1TIP_MSK           (BIT3 | BIT2)
#define DMAUR1RCFG_UR1RIP_MSK           (BIT3 | BIT2)
#define DMAUR2TCFG_UR2TIP_MSK           (BIT3 | BIT2)
#define DMAUR2RCFG_UR2RIP_MSK           (BIT3 | BIT2)
#define DMAUR3TCFG_UR3TIP_MSK           (BIT3 | BIT2)
#define DMAUR3RCFG_UR3RIP_MSK           (BIT3 | BIT2)
#define DMAUR4TCFG_UR4TIP_MSK           (BIT3 | BIT2)
#define DMAUR4RCFG_UR4RIP_MSK           (BIT3 | BIT2)
#define DMAUR5TCFG_UR5TIP_MSK           (BIT3 | BIT2)
#define DMAUR5RCFG_UR5RIP_MSK           (BIT3 | BIT2)
#define DMAUR6TCFG_UR6TIP_MSK           (BIT3 | BIT2)
#define DMAUR6RCFG_UR6RIP_MSK           (BIT3 | BIT2)
#define DMAUR7TCFG_UR7TIP_MSK           (BIT3 | BIT2)
#define DMAUR7RCFG_UR7RIP_MSK           (BIT3 | BIT2)
#define DMAUR8TCFG_UR8TIP_MSK           (BIT3 | BIT2)
#define DMAUR8RCFG_UR8RIP_MSK           (BIT3 | BIT2)
#define DMAI2CTCFG_I2CTIP_MSK           (BIT3 | BIT2)
#define DMAI2CRCFG_I2CRIP_MSK           (BIT3 | BIT2)
#define DMAI2C2TCFG_I2C2TIP_MSK         (BIT3 | BIT2)
#define DMAI2C2RCFG_I2C2RIP_MSK         (BIT3 | BIT2)
#define DMAI2STCFG_I2STIP_MSK           (BIT3 | BIT2)
#define DMAI2S2RCFG_I2S2RIP_MSK         (BIT3 | BIT2)
#define DMAI2S2TCFG_I2S2TIP_MSK         (BIT3 | BIT2)
#define DMAI2SRCFG_I2SRIP_MSK           (BIT3 | BIT2)
#define DMAPWMATCFG_PWMATIP_MSK         (BIT3 | BIT2)
#define DMAPWMARCFG_PWMARIP_MSK         (BIT3 | BIT2)
#define DMAPWMCTCFG_PWMCTIP_MSK         (BIT3 | BIT2)
#define DMAPWMCRCFG_PWMCRIP_MSK         (BIT3 | BIT2)
#define DMAPWMETCFG_PWMETIP_MSK         (BIT3 | BIT2)
#define DMAPWMERCFG_PWMERIP_MSK         (BIT3 | BIT2)
#define DMACAN1TCFG_CAN1TIP_MSK         (BIT3 | BIT2)
#define DMACAN1RCFG_CAN1RIP_MSK         (BIT3 | BIT2)
#define DMACAN2TCFG_CAN2TIP_MSK         (BIT3 | BIT2)
#define DMACAN2RCFG_CAN2RIP_MSK         (BIT3 | BIT2)
#define DMA_M2M_SetIntPriority(n)       MODIFY_REG(DMA_M2M_CFG,   DMAM2MCFG_M2MIP_MSK, ((n) << 2))
#define DMA_ADC1_SetIntPriority(n)      MODIFY_REG(DMA_ADC_CFG,   DMAADCCFG_ADCIP_MSK, ((n) << 2))
#define DMA_ADC2_SetIntPriority(n)      MODIFY_REG(DMA_ADC2_CFG,  DMAADC2CFG_ADC2IP_MSK, ((n) << 2))
#define DMA_DAC1_SetIntPriority(n)      MODIFY_REG(DMA_DAC1_CFG,  DMADAC1CFG_DAC1IP_MSK, ((n) << 2))
#define DMA_DAC2_SetIntPriority(n)      MODIFY_REG(DMA_DAC2_CFG,  DMADAC2CFG_DAC2IP_MSK, ((n) << 2))
#define DMA_SPI1_SetIntPriority(n)      MODIFY_REG(DMA_SPI_CFG,   DMASPICFG_SPIIP_MSK, ((n) << 2))
#define DMA_SPI2_SetIntPriority(n)      MODIFY_REG(DMA_SPI2_CFG,  DMASPI2CFG_SPI2IP_MSK, ((n) << 2))
#define DMA_SPI3_SetIntPriority(n)      MODIFY_REG(DMA_SPI3_CFG,  DMASPI3CFG_SPI3IP_MSK, ((n) << 2))
#define DMA_QSPI_SetIntPriority(n)      MODIFY_REG(DMA_QSPI_CFG,  DMAQSPICFG_QSPIIP_MSK, ((n) << 2))
#define DMA_LCM_SetIntPriority(n)       MODIFY_REG(DMA_LCM_CFG,   DMALCMCFG_LCMIP_MSK, ((n) << 2))
#define DMA_UART1_SetTxIntPriority(n)   MODIFY_REG(DMA_UR1T_CFG,  DMAUR1TCFG_UR1TIP_MSK, ((n) << 2))
#define DMA_UART1_SetRxIntPriority(n)   MODIFY_REG(DMA_UR1R_CFG,  DMAUR1RCFG_UR1RIP_MSK, ((n) << 2))
#define DMA_UART2_SetTxIntPriority(n)   MODIFY_REG(DMA_UR2T_CFG,  DMAUR2TCFG_UR2TIP_MSK, ((n) << 2))
#define DMA_UART2_SetRxIntPriority(n)   MODIFY_REG(DMA_UR2R_CFG,  DMAUR2RCFG_UR2RIP_MSK, ((n) << 2))
#define DMA_UART3_SetTxIntPriority(n)   MODIFY_REG(DMA_UR3T_CFG,  DMAUR3TCFG_UR3TIP_MSK, ((n) << 2))
#define DMA_UART3_SetRxIntPriority(n)   MODIFY_REG(DMA_UR3R_CFG,  DMAUR3RCFG_UR3RIP_MSK, ((n) << 2))
#define DMA_UART4_SetTxIntPriority(n)   MODIFY_REG(DMA_UR4T_CFG,  DMAUR4TCFG_UR4TIP_MSK, ((n) << 2))
#define DMA_UART4_SetRxIntPriority(n)   MODIFY_REG(DMA_UR4R_CFG,  DMAUR4RCFG_UR4RIP_MSK, ((n) << 2))
#define DMA_UART5_SetTxIntPriority(n)   MODIFY_REG(DMA_UR5T_CFG,  DMAUR5TCFG_UR5TIP_MSK, ((n) << 2))
#define DMA_UART5_SetRxIntPriority(n)   MODIFY_REG(DMA_UR5R_CFG,  DMAUR5RCFG_UR5RIP_MSK, ((n) << 2))
#define DMA_UART6_SetTxIntPriority(n)   MODIFY_REG(DMA_UR6T_CFG,  DMAUR6TCFG_UR6TIP_MSK, ((n) << 2))
#define DMA_UART6_SetRxIntPriority(n)   MODIFY_REG(DMA_UR6R_CFG,  DMAUR6RCFG_UR6RIP_MSK, ((n) << 2))
#define DMA_UART7_SetTxIntPriority(n)   MODIFY_REG(DMA_UR7T_CFG,  DMAUR7TCFG_UR7TIP_MSK, ((n) << 2))
#define DMA_UART7_SetRxIntPriority(n)   MODIFY_REG(DMA_UR7R_CFG,  DMAUR7RCFG_UR7RIP_MSK, ((n) << 2))
#define DMA_UART8_SetTxIntPriority(n)   MODIFY_REG(DMA_UR8T_CFG,  DMAUR8TCFG_UR8TIP_MSK, ((n) << 2))
#define DMA_UART8_SetRxIntPriority(n)   MODIFY_REG(DMA_UR8R_CFG,  DMAUR8RCFG_UR8RIP_MSK, ((n) << 2))
#define DMA_I2C1_SetTxIntPriority(n)    MODIFY_REG(DMA_I2CT_CFG,  DMAI2CTCFG_I2CTIP_MSK, ((n) << 2))
#define DMA_I2C1_SetRxIntPriority(n)    MODIFY_REG(DMA_I2CR_CFG,  DMAI2CRCFG_I2CRIP_MSK, ((n) << 2))
#define DMA_I2C2_SetTxIntPriority(n)    MODIFY_REG(DMA_I2C2T_CFG, DMAI2C2TCFG_I2C2TIP_MSK, ((n) << 2))
#define DMA_I2C2_SetRxIntPriority(n)    MODIFY_REG(DMA_I2C2R_CFG, DMAI2C2RCFG_I2C2RIP_MSK, ((n) << 2))
#define DMA_I2S1_SetTxIntPriority(n)    MODIFY_REG(DMA_I2ST_CFG,  DMAI2STCFG_I2STIP_MSK, ((n) << 2))
#define DMA_I2S1_SetRxIntPriority(n)    MODIFY_REG(DMA_I2SR_CFG,  DMAI2SRCFG_I2SRIP_MSK, ((n) << 2))
#define DMA_I2S2_SetTxIntPriority(n)    MODIFY_REG(DMA_I2S2T_CFG, DMAI2S2TCFG_I2S2TIP_MSK, ((n) << 2))
#define DMA_I2S2_SetRxIntPriority(n)    MODIFY_REG(DMA_I2S2R_CFG, DMAI2S2RCFG_I2S2RIP_MSK, ((n) << 2))
#define DMA_PWMA_SetTxIntPriority(n)    MODIFY_REG(DMA_PWMAT_CFG, DMAPWMATCFG_PWMATIP_MSK, ((n) << 2))
#define DMA_PWMA_SetRxIntPriority(n)    MODIFY_REG(DMA_PWMAR_CFG, DMAPWMARCFG_PWMARIP_MSK, ((n) << 2))
#define DMA_CAN1_SetTxIntPriority(n)    MODIFY_REG(DMA_CAN1T_CFG, DMACAN1TCFG_CAN1TIP_MSK, ((n) << 2))
#define DMA_CAN1_SetRxIntPriority(n)    MODIFY_REG(DMA_CAN1R_CFG, DMACAN1RCFG_CAN1RIP_MSK, ((n) << 2))
#define DMA_CAN2_SetTxIntPriority(n)    MODIFY_REG(DMA_CAN2T_CFG, DMACAN2TCFG_CAN2TIP_MSK, ((n) << 2))
#define DMA_CAN2_SetRxIntPriority(n)    MODIFY_REG(DMA_CAN2R_CFG, DMACAN2RCFG_CAN2RIP_MSK, ((n) << 2))

/////////////////////////////////////////////////

#define EAXFR_MSK                       BIT7
#define EnableAccessXFR()               SET_REG_BIT(P_SW2, EAXFR_MSK)

#define AccessCodeSpeed(n)              WRITE_REG(WTST, (n))
#define AccessCodeFastest()             AccessCodeSpeed((SYSCLK) <=  32000000 ? 0 : \
                                                        (SYSCLK) <=  64000000 ? 1 : \
                                                        (SYSCLK) <=  90000000 ? 2 : \
                                                        (SYSCLK) <= 120000000 ? 3 : 4)

#define ACCIXRAM_MSK                    (BIT2 | BIT1 | BIT0)
#define AccessIXramSpeed(n)             MODIFY_REG(CKCON, ACCIXRAM_MSK, ((n) << 0))
#define AccessIXramFastest()            AccessIXramSpeed(0)

#define ACCEXRAM_MSK                    (BIT2 | BIT1 | BIT0)
#define AccessEXramSpeed(n)             MODIFY_REG(BUS_SPEED, ACCEXRAM_MSK, ((n) << 0))
#define AccessEXramFastest()            AccessEXramSpeed(0)

#define UART1_PS_MSK                    (BIT7 | BIT6)
#define UART1_SwitchP3031()             MODIFY_REG(P_SW1, UART1_PS_MSK, ((0) << 6))
#define UART1_SwitchP3637()             MODIFY_REG(P_SW1, UART1_PS_MSK, ((1) << 6))
#define UART1_SwitchP1617()             MODIFY_REG(P_SW1, UART1_PS_MSK, ((2) << 6))
#define UART1_SwitchP4344()             MODIFY_REG(P_SW1, UART1_PS_MSK, ((3) << 6))

#define UART2_PS_MSK                    (BIT0)
#define UART2_PS2_MSK                   (BIT5)
#define UART2_SwitchP1011()             CLR_REG_BIT(P_SW2, UART2_PS_MSK); CLR_REG_BIT(P_SWX1, UART2_PS2_MSK)
#define UART2_SwitchP4647()             SET_REG_BIT(P_SW2, UART2_PS_MSK); CLR_REG_BIT(P_SWX1, UART2_PS2_MSK)
#define UART2_SwitchP8485()             CLR_REG_BIT(P_SW2, UART2_PS_MSK); SET_REG_BIT(P_SWX1, UART2_PS2_MSK)
#define UART2_SwitchPA0A1()             SET_REG_BIT(P_SW2, UART2_PS_MSK); SET_REG_BIT(P_SWX1, UART2_PS2_MSK)

#define UART3_PS_MSK                    (BIT1)
#define UART3_PS2_MSK                   (BIT6)
#define UART3_SwitchP0001()             CLR_REG_BIT(P_SW2, UART3_PS_MSK); CLR_REG_BIT(P_SWX1, UART3_PS2_MSK)
#define UART3_SwitchP5051()             SET_REG_BIT(P_SW2, UART3_PS_MSK); CLR_REG_BIT(P_SWX1, UART3_PS2_MSK)
#define UART3_SwitchP8687()             CLR_REG_BIT(P_SW2, UART3_PS_MSK); SET_REG_BIT(P_SWX1, UART3_PS2_MSK)
#define UART3_SwitchPB6B7()             SET_REG_BIT(P_SW2, UART3_PS_MSK); SET_REG_BIT(P_SWX1, UART3_PS2_MSK)

#define UART4_PS_MSK                    (BIT2)
#define UART4_PS2_MSK                   (BIT7)
#define UART4_SwitchP0203()             CLR_REG_BIT(P_SW2, UART4_PS_MSK); CLR_REG_BIT(P_SWX1, UART4_PS2_MSK)
#define UART4_SwitchP5253()             SET_REG_BIT(P_SW2, UART4_PS_MSK); CLR_REG_BIT(P_SWX1, UART4_PS2_MSK)
#define UART4_SwitchPA2A3()             CLR_REG_BIT(P_SW2, UART4_PS_MSK); SET_REG_BIT(P_SWX1, UART4_PS2_MSK)
#define UART4_SwitchPC0C1()             SET_REG_BIT(P_SW2, UART4_PS_MSK); SET_REG_BIT(P_SWX1, UART4_PS2_MSK)

#define UART5_PS_MSK                    (BIT1 | BIT0)
#define UART5_SwitchP0405()             MODIFY_REG(P_SWX2, UART5_PS_MSK, ((0) << 0))
#define UART5_SwitchP4041()             MODIFY_REG(P_SWX2, UART5_PS_MSK, ((1) << 0))
#define UART5_SwitchP1415()             MODIFY_REG(P_SWX2, UART5_PS_MSK, ((2) << 0))
#define UART5_SwitchP2021()             MODIFY_REG(P_SWX2, UART5_PS_MSK, ((3) << 0))

#define UART6_PS_MSK                    (BIT3 | BIT2)
#define UART6_SwitchP0607()             MODIFY_REG(P_SWX2, UART6_PS_MSK, ((0) << 2))
#define UART6_SwitchP6263()             MODIFY_REG(P_SWX2, UART6_PS_MSK, ((1) << 2))
#define UART6_SwitchP3233()             MODIFY_REG(P_SWX2, UART6_PS_MSK, ((2) << 2))
#define UART6_SwitchP2627()             MODIFY_REG(P_SWX2, UART6_PS_MSK, ((3) << 2))

#define UART7_PS_MSK                    (BIT5 | BIT4)
#define UART7_SwitchP5051()             MODIFY_REG(P_SWX5, UART7_PS_MSK, ((0) << 4))
#define UART7_SwitchPA4A5()             MODIFY_REG(P_SWX5, UART7_PS_MSK, ((1) << 4))
#define UART7_SwitchP9091()             MODIFY_REG(P_SWX5, UART7_PS_MSK, ((2) << 4))
#define UART7_SwitchP1213()             MODIFY_REG(P_SWX5, UART7_PS_MSK, ((3) << 4))

#define UART8_PS_MSK                    (BIT7 | BIT6)
#define UART8_SwitchP5253()             MODIFY_REG(P_SWX5, UART8_PS_MSK, ((0) << 6))
#define UART8_SwitchPA6A7()             MODIFY_REG(P_SWX5, UART8_PS_MSK, ((1) << 6))
#define UART8_SwitchP9293()             MODIFY_REG(P_SWX5, UART8_PS_MSK, ((2) << 6))
#define UART8_SwitchP6061()             MODIFY_REG(P_SWX5, UART8_PS_MSK, ((3) << 6))

#define I2C_PS_MSK                      (BIT5 | BIT4)
#define I2C1_SwitchP1415()              MODIFY_REG(P_SW2, I2C_PS_MSK, ((0) << 4))
#define I2C1_SwitchP2425()              MODIFY_REG(P_SW2, I2C_PS_MSK, ((1) << 4))
#define I2C1_SwitchP7677()              MODIFY_REG(P_SW2, I2C_PS_MSK, ((2) << 4))
#define I2C1_SwitchP3332()              MODIFY_REG(P_SW2, I2C_PS_MSK, ((3) << 4))

#define I2C2_PS_MSK                     (BIT7 | BIT6)
#define I2C2_SwitchP2627()              MODIFY_REG(P_SWX4, I2C2_PS_MSK, ((0) << 6))
#define I2C2_SwitchP3637()              MODIFY_REG(P_SWX4, I2C2_PS_MSK, ((1) << 6))
#define I2C2_SwitchP1617()              MODIFY_REG(P_SWX4, I2C2_PS_MSK, ((2) << 6))
#define I2C2_SwitchP6061()              MODIFY_REG(P_SWX4, I2C2_PS_MSK, ((3) << 6))

#define SPI_PS_MSK                      (BIT3 | BIT2)
#define SPI1_SwitchP1n()                MODIFY_REG(P_SW1, SPI_PS_MSK, ((0) << 2))
#define SPI1_SwitchP2n()                MODIFY_REG(P_SW1, SPI_PS_MSK, ((1) << 2))
#define SPI1_SwitchP4n()                MODIFY_REG(P_SW1, SPI_PS_MSK, ((2) << 2))
#define SPI1_SwitchP3n()                MODIFY_REG(P_SW1, SPI_PS_MSK, ((3) << 2))

#define SPI2_PS_MSK                      (BIT1 | BIT0)
#define SPI2_SwitchP6n()                MODIFY_REG(P_SWX4, SPI2_PS_MSK, ((0) << 0))
#define SPI2_SwitchP0n()                MODIFY_REG(P_SWX4, SPI2_PS_MSK, ((1) << 0))
#define SPI2_SwitchPBn()                MODIFY_REG(P_SWX4, SPI2_PS_MSK, ((2) << 0))
#define SPI2_SwitchP8n()                MODIFY_REG(P_SWX4, SPI2_PS_MSK, ((3) << 0))

#define SPI3_PS_MSK                      (BIT3 | BIT2)
#define SPI3_SwitchP2n()                MODIFY_REG(P_SWX4, SPI3_PS_MSK, ((0) << 2))
#define SPI3_SwitchP7n()                MODIFY_REG(P_SWX4, SPI3_PS_MSK, ((1) << 2))
#define SPI3_SwitchP8n()                MODIFY_REG(P_SWX4, SPI3_PS_MSK, ((2) << 2))
#define SPI3_SwitchP9n()                MODIFY_REG(P_SWX4, SPI3_PS_MSK, ((3) << 2))

#define USART1_PS_MSK                   (BIT3 | BIT2)
#define USART1_SwitchP1n()              MODIFY_REG(P_SW3, USART1_PS_MSK, ((0) << 2))
#define USART1_SwitchP2n()              MODIFY_REG(P_SW3, USART1_PS_MSK, ((1) << 2))
#define USART1_SwitchP4n()              MODIFY_REG(P_SW3, USART1_PS_MSK, ((2) << 2))
#define USART1_SwitchP6n()              MODIFY_REG(P_SW3, USART1_PS_MSK, ((3) << 2))

#define USART2_PS_MSK                   (BIT5 | BIT4)
#define USART2_SwitchP1n()              MODIFY_REG(P_SW3, USART2_PS_MSK, ((0) << 4))
#define USART2_SwitchP2n()              MODIFY_REG(P_SW3, USART2_PS_MSK, ((1) << 4))
#define USART2_SwitchP4n()              MODIFY_REG(P_SW3, USART2_PS_MSK, ((2) << 4))
#define USART2_SwitchP7n()              MODIFY_REG(P_SW3, USART2_PS_MSK, ((3) << 4))

#define USART3_PS_MSK                   (BIT1 | BIT0)
#define USART3_SwitchP6n()              MODIFY_REG(P_SWX3, USART3_PS_MSK, ((0) << 0))
#define USART3_SwitchP0n()              MODIFY_REG(P_SWX3, USART3_PS_MSK, ((1) << 0))
#define USART3_SwitchPBn()              MODIFY_REG(P_SWX3, USART3_PS_MSK, ((2) << 0))
#define USART3_SwitchP9n()              MODIFY_REG(P_SWX3, USART3_PS_MSK, ((3) << 0))

#define USART4_PS_MSK                   (BIT3 | BIT2)
#define USART4_SwitchP6n()              MODIFY_REG(P_SWX3, USART4_PS_MSK, ((0) << 2))
#define USART4_SwitchP0n()              MODIFY_REG(P_SWX3, USART4_PS_MSK, ((1) << 2))
#define USART4_SwitchPBn()              MODIFY_REG(P_SWX3, USART4_PS_MSK, ((2) << 2))
#define USART4_SwitchP7n()              MODIFY_REG(P_SWX3, USART4_PS_MSK, ((3) << 2))

#define USART5_PS_MSK                   (BIT5 | BIT4)
#define USART5_SwitchP2n()              MODIFY_REG(P_SWX3, USART5_PS_MSK, ((0) << 4))
#define USART5_SwitchP7n()              MODIFY_REG(P_SWX3, USART5_PS_MSK, ((1) << 4))
#define USART5_SwitchP8n()              MODIFY_REG(P_SWX3, USART5_PS_MSK, ((2) << 4))
#define USART5_SwitchP9n()              MODIFY_REG(P_SWX3, USART5_PS_MSK, ((3) << 4))

#define USART6_PS_MSK                   (BIT7 | BIT6)
#define USART6_SwitchP2n()              MODIFY_REG(P_SWX3, USART6_PS_MSK, ((0) << 6))
#define USART6_SwitchP7n()              MODIFY_REG(P_SWX3, USART6_PS_MSK, ((1) << 6))
#define USART6_SwitchP8n()              MODIFY_REG(P_SWX3, USART6_PS_MSK, ((2) << 6))
#define USART6_SwitchP9n()              MODIFY_REG(P_SWX3, USART6_PS_MSK, ((3) << 6))

#define USART7_PS_MSK                   (BIT1 | BIT0)
#define USART7_SwitchP5n()              MODIFY_REG(P_SWX6, USART7_PS_MSK, ((0) << 0))
#define USART7_SwitchPAn()              MODIFY_REG(P_SWX6, USART7_PS_MSK, ((1) << 0))
#define USART7_SwitchP7n()              MODIFY_REG(P_SWX6, USART7_PS_MSK, ((2) << 0))

#define USART8_PS_MSK                   (BIT3 | BIT2)
#define USART8_SwitchP5n()              MODIFY_REG(P_SWX6, USART8_PS_MSK, ((0) << 2))
#define USART8_SwitchPAn()              MODIFY_REG(P_SWX6, USART8_PS_MSK, ((1) << 2))
#define USART8_SwitchP7n()              MODIFY_REG(P_SWX6, USART8_PS_MSK, ((2) << 2))
#define USART8_SwitchP6n()              MODIFY_REG(P_SWX6, USART8_PS_MSK, ((3) << 2))

#define I2S_PS_MSK                      (BIT7 | BIT6)
#define I2S1_SwitchP3n()                MODIFY_REG(P_SW3, I2S_PS_MSK, ((0) << 6))
#define I2S1_SwitchP6n()                MODIFY_REG(P_SW3, I2S_PS_MSK, ((1) << 6))
#define I2S1_SwitchP2n()                MODIFY_REG(P_SW3, I2S_PS_MSK, ((2) << 6))
#define I2S1_SwitchP4n()                MODIFY_REG(P_SW3, I2S_PS_MSK, ((3) << 6))

#define I2S2_PS_MSK                     (BIT3 | BIT2)
#define I2S2_SwitchP5n()                MODIFY_REG(P_SWX5, I2S2_PS_MSK, ((0) << 2))
#define I2S2_SwitchP6n()                MODIFY_REG(P_SWX5, I2S2_PS_MSK, ((1) << 2))
#define I2S2_SwitchP8n()                MODIFY_REG(P_SWX5, I2S2_PS_MSK, ((2) << 2))
#define I2S2_SwitchPBn()                MODIFY_REG(P_SWX5, I2S2_PS_MSK, ((3) << 2))

#define QSPI_PS_MSK                     (BIT1 | BIT0)
#define QSPI_SwitchP1n()                MODIFY_REG(P_SW4, QSPI_PS_MSK, ((0) << 0))
#define QSPI_SwitchP4n()                MODIFY_REG(P_SW4, QSPI_PS_MSK, ((1) << 0))
#define QSPI_SwitchP7n()                MODIFY_REG(P_SW4, QSPI_PS_MSK, ((2) << 0))

#define CMP1O_PS_MSK                    (BIT1 | BIT0)
#define CMP1O_SwitchP34()               MODIFY_REG(CMP1_6P6N_CR4, CMP1O_PS_MSK, ((0) << 0))
#define CMP1O_SwitchP41()               MODIFY_REG(CMP1_6P6N_CR4, CMP1O_PS_MSK, ((1) << 0))

#define CMP1NS_MSK                      (BIT5 | BIT4 | BIT3)
#define CMP1N_SwitchP36()               MODIFY_REG(CMP1_6P6N_CR3, CMP1NS_MSK, ((0) << 3))
#define CMP1N_SwitchP51()               MODIFY_REG(CMP1_6P6N_CR3, CMP1NS_MSK, ((1) << 3))
#define CMP1N_SwitchOP2O()              MODIFY_REG(CMP1_6P6N_CR3, CMP1NS_MSK, ((2) << 3))
#define CMP1N_SwitchREFV()              MODIFY_REG(CMP1_6P6N_CR3, CMP1NS_MSK, ((3) << 3))
#define CMP1N_SwitchDAC1O()             MODIFY_REG(CMP1_6P6N_CR3, CMP1NS_MSK, ((4) << 3))
#define CMP1N_SwitchDAC2O()             MODIFY_REG(CMP1_6P6N_CR3, CMP1NS_MSK, ((5) << 3))

#define CMP1PS_MSK                      (BIT2 | BIT1 | BIT0)
#define CMP1P_SwitchP37()               MODIFY_REG(CMP1_6P6N_CR3, CMP1PS_MSK, ((0) << 0))
#define CMP1P_SwitchP50()               MODIFY_REG(CMP1_6P6N_CR3, CMP1PS_MSK, ((1) << 0))
#define CMP1P_SwitchOP1O()              MODIFY_REG(CMP1_6P6N_CR3, CMP1PS_MSK, ((2) << 0))
#define CMP1P_SwitchADC1IN()            MODIFY_REG(CMP1_6P6N_CR3, CMP1PS_MSK, ((3) << 0))
#define CMP1P_SwitchDAC1O()             MODIFY_REG(CMP1_6P6N_CR3, CMP1PS_MSK, ((4) << 0))
#define CMP1P_SwitchDAC2O()             MODIFY_REG(CMP1_6P6N_CR3, CMP1PS_MSK, ((5) << 0))

#define CMP2O_PS_MSK                    (BIT1 | BIT0)
#define CMP2O_SwitchP47()               MODIFY_REG(CMP2_6P6N_CR4, CMP2O_PS_MSK, ((0) << 0))
#define CMP2O_SwitchP40()               MODIFY_REG(CMP2_6P6N_CR4, CMP2O_PS_MSK, ((1) << 0))

#define CMP2NS_MSK                      (BIT5 | BIT4 | BIT3)
#define CMP2N_SwitchP66()               MODIFY_REG(CMP2_6P6N_CR3, CMP2NS_MSK, ((0) << 3))
#define CMP2N_SwitchP11()               MODIFY_REG(CMP2_6P6N_CR3, CMP2NS_MSK, ((1) << 3))
#define CMP2N_SwitchOP3O()              MODIFY_REG(CMP2_6P6N_CR3, CMP2NS_MSK, ((2) << 3))
#define CMP2N_SwitchREFV()              MODIFY_REG(CMP2_6P6N_CR3, CMP2NS_MSK, ((3) << 3))
#define CMP2N_SwitchDAC1O()             MODIFY_REG(CMP2_6P6N_CR3, CMP2NS_MSK, ((4) << 3))
#define CMP2N_SwitchDAC2O()             MODIFY_REG(CMP2_6P6N_CR3, CMP2NS_MSK, ((5) << 3))

#define CMP2PS_MSK                      (BIT2 | BIT1 | BIT0)
#define CMP2P_SwitchP67()               MODIFY_REG(CMP2_6P6N_CR3, CMP2PS_MSK, ((0) << 0))
#define CMP2P_SwitchP10()               MODIFY_REG(CMP2_6P6N_CR3, CMP2PS_MSK, ((1) << 0))
#define CMP2P_SwitchOP2O()              MODIFY_REG(CMP2_6P6N_CR3, CMP2PS_MSK, ((2) << 0))
#define CMP2P_SwitchADC1IN()            MODIFY_REG(CMP2_6P6N_CR3, CMP2PS_MSK, ((3) << 0))
#define CMP2P_SwitchDAC1O()             MODIFY_REG(CMP2_6P6N_CR3, CMP2PS_MSK, ((4) << 0))
#define CMP2P_SwitchDAC2O()             MODIFY_REG(CMP2_6P6N_CR3, CMP2PS_MSK, ((5) << 0))

#define CMP3O_PS_MSK                    (BIT1 | BIT0)
#define CMP3O_SwitchP24()               MODIFY_REG(CMP3_6P6N_CR4, CMP3O_PS_MSK, ((0) << 0))
#define CMP3O_SwitchP45()               MODIFY_REG(CMP3_6P6N_CR4, CMP3O_PS_MSK, ((1) << 0))

#define CMP3NS_MSK                      (BIT5 | BIT4 | BIT3)
#define CMP3N_SwitchP76()               MODIFY_REG(CMP3_6P6N_CR3, CMP3NS_MSK, ((0) << 3))
#define CMP3N_SwitchP52()               MODIFY_REG(CMP3_6P6N_CR3, CMP3NS_MSK, ((1) << 3))
#define CMP3N_SwitchOP4O()              MODIFY_REG(CMP3_6P6N_CR3, CMP3NS_MSK, ((2) << 3))
#define CMP3N_SwitchREFV()              MODIFY_REG(CMP3_6P6N_CR3, CMP3NS_MSK, ((3) << 3))
#define CMP3N_SwitchDAC1O()             MODIFY_REG(CMP3_6P6N_CR3, CMP3NS_MSK, ((4) << 3))
#define CMP3N_SwitchDAC2O()             MODIFY_REG(CMP3_6P6N_CR3, CMP3NS_MSK, ((5) << 3))

#define CMP3PS_MSK                      (BIT2 | BIT1 | BIT0)
#define CMP3P_SwitchP77()               MODIFY_REG(CMP3_6P6N_CR3, CMP3PS_MSK, ((0) << 0))
#define CMP3P_SwitchP53()               MODIFY_REG(CMP3_6P6N_CR3, CMP3PS_MSK, ((1) << 0))
#define CMP3P_SwitchOP3O()              MODIFY_REG(CMP3_6P6N_CR3, CMP3PS_MSK, ((2) << 0))
#define CMP3P_SwitchADC2IN()            MODIFY_REG(CMP3_6P6N_CR3, CMP3PS_MSK, ((3) << 0))
#define CMP3P_SwitchDAC1O()             MODIFY_REG(CMP3_6P6N_CR3, CMP3PS_MSK, ((4) << 0))
#define CMP3P_SwitchDAC2O()             MODIFY_REG(CMP3_6P6N_CR3, CMP3PS_MSK, ((5) << 0))

#define CMP4O_PS_MSK                    (BIT1 | BIT0)
#define CMP4O_SwitchP25()               MODIFY_REG(CMP4_6P6N_CR4, CMP4O_PS_MSK, ((0) << 0))
#define CMP4O_SwitchP46()               MODIFY_REG(CMP4_6P6N_CR4, CMP4O_PS_MSK, ((1) << 0))

#define CMP4NS_MSK                      (BIT5 | BIT4 | BIT3)
#define CMP4N_SwitchP26()               MODIFY_REG(CMP4_6P6N_CR3, CMP4NS_MSK, ((0) << 3))
#define CMP4N_SwitchP44()               MODIFY_REG(CMP4_6P6N_CR3, CMP4NS_MSK, ((1) << 3))
#define CMP4N_SwitchOP1O()              MODIFY_REG(CMP4_6P6N_CR3, CMP4NS_MSK, ((2) << 3))
#define CMP4N_SwitchREFV()              MODIFY_REG(CMP4_6P6N_CR3, CMP4NS_MSK, ((3) << 3))
#define CMP4N_SwitchDAC1O()             MODIFY_REG(CMP4_6P6N_CR3, CMP4NS_MSK, ((4) << 3))
#define CMP4N_SwitchDAC2O()             MODIFY_REG(CMP4_6P6N_CR3, CMP4NS_MSK, ((5) << 3))

#define CMP4PS_MSK                      (BIT2 | BIT1 | BIT0)
#define CMP4P_SwitchP27()               MODIFY_REG(CMP4_6P6N_CR3, CMP4PS_MSK, ((0) << 0))
#define CMP4P_SwitchP43()               MODIFY_REG(CMP4_6P6N_CR3, CMP4PS_MSK, ((1) << 0))
#define CMP4P_SwitchOP4O()              MODIFY_REG(CMP4_6P6N_CR3, CMP4PS_MSK, ((2) << 0))
#define CMP4P_SwitchADC2IN()            MODIFY_REG(CMP4_6P6N_CR3, CMP4PS_MSK, ((3) << 0))
#define CMP4P_SwitchDAC1O()             MODIFY_REG(CMP4_6P6N_CR3, CMP4PS_MSK, ((4) << 0))
#define CMP4P_SwitchDAC2O()             MODIFY_REG(CMP4_6P6N_CR3, CMP4PS_MSK, ((5) << 0))

#define PGA1O_PS_MSK                    (BIT5 | BIT4)
#define PGA1O_SwitchP07()               MODIFY_REG(PGA1_CR1, PGA1O_PS_MSK, ((0) << 4))
#define PGA1O_SwitchP00()               MODIFY_REG(PGA1_CR1, PGA1O_PS_MSK, ((1) << 4))
#define PGA1O_SwitchP74()               MODIFY_REG(PGA1_CR1, PGA1O_PS_MSK, ((2) << 4))
#define PGA1O_SwitchP63()               MODIFY_REG(PGA1_CR1, PGA1O_PS_MSK, ((3) << 4))

#define PGA1NS_MSK                      (BIT3 | BIT2)
#define PGA1N_SwitchP05()               MODIFY_REG(PGA1_CR1, PGA1NS_MSK, ((0) << 2))
#define PGA1N_SwitchP04()               MODIFY_REG(PGA1_CR1, PGA1NS_MSK, ((1) << 2))
#define PGA1N_SwitchP61()               MODIFY_REG(PGA1_CR1, PGA1NS_MSK, ((2) << 2))
#define PGA1N_SwitchDAC1O()             MODIFY_REG(PGA1_CR1, PGA1NS_MSK, ((3) << 2))

#define PGA1PS_MSK                      (BIT1 | BIT0)
#define PGA1P_SwitchP04()               MODIFY_REG(PGA1_CR1, PGA1PS_MSK, ((0) << 0))
#define PGA1P_SwitchP05()               MODIFY_REG(PGA1_CR1, PGA1PS_MSK, ((1) << 0))
#define PGA1P_SwitchP60()               MODIFY_REG(PGA1_CR1, PGA1PS_MSK, ((2) << 0))
#define PGA1P_SwitchDAC1O()             MODIFY_REG(PGA1_CR1, PGA1PS_MSK, ((3) << 0))

#define PGA2O_PS_MSK                    (BIT5 | BIT4)
#define PGA2O_SwitchP42()               MODIFY_REG(PGA2_CR1, PGA2O_PS_MSK, ((0) << 4))
#define PGA2O_SwitchP00()               MODIFY_REG(PGA2_CR1, PGA2O_PS_MSK, ((1) << 4))
#define PGA2O_SwitchP74()               MODIFY_REG(PGA2_CR1, PGA2O_PS_MSK, ((2) << 4))
#define PGA2O_SwitchP62()               MODIFY_REG(PGA2_CR1, PGA2O_PS_MSK, ((3) << 4))

#define PGA2NS_MSK                      (BIT3 | BIT2)
#define PGA2N_SwitchP27()               MODIFY_REG(PGA2_CR1, PGA2NS_MSK, ((0) << 2))
#define PGA2N_SwitchP81()               MODIFY_REG(PGA2_CR1, PGA2NS_MSK, ((1) << 2))
#define PGA2N_SwitchP76()               MODIFY_REG(PGA2_CR1, PGA2NS_MSK, ((2) << 2))
#define PGA2N_SwitchDAC2O()             MODIFY_REG(PGA2_CR1, PGA2NS_MSK, ((3) << 2))

#define PGA2PS_MSK                      (BIT1 | BIT0)
#define PGA2P_SwitchP26()               MODIFY_REG(PGA2_CR1, PGA2PS_MSK, ((0) << 0))
#define PGA2P_SwitchP80()               MODIFY_REG(PGA2_CR1, PGA2PS_MSK, ((1) << 0))
#define PGA2P_SwitchP75()               MODIFY_REG(PGA2_CR1, PGA2PS_MSK, ((2) << 0))
#define PGA2P_SwitchP77()               MODIFY_REG(PGA2_CR1, PGA2PS_MSK, ((3) << 0))

#define PGA3O_PS_MSK                    (BIT5 | BIT4)
#define PGA3O_SwitchP32()               MODIFY_REG(PGA3_CR1, PGA3O_PS_MSK, ((0) << 4))
#define PGA3O_SwitchP21()               MODIFY_REG(PGA3_CR1, PGA3O_PS_MSK, ((1) << 4))
#define PGA3O_SwitchP74()               MODIFY_REG(PGA3_CR1, PGA3O_PS_MSK, ((2) << 4))
#define PGA3O_SwitchP50()               MODIFY_REG(PGA3_CR1, PGA3O_PS_MSK, ((3) << 4))

#define PGA3NS_MSK                      (BIT3 | BIT2)
#define PGA3N_SwitchP51()               MODIFY_REG(PGA3_CR1, PGA3NS_MSK, ((0) << 2))
#define PGA3N_SwitchP42()               MODIFY_REG(PGA3_CR1, PGA3NS_MSK, ((1) << 2))
#define PGA3N_SwitchP71()               MODIFY_REG(PGA3_CR1, PGA3NS_MSK, ((2) << 2))
#define PGA3N_SwitchDAC2O()             MODIFY_REG(PGA3_CR1, PGA3NS_MSK, ((3) << 2))

#define PGA3PS_MSK                      (BIT1 | BIT0)
#define PGA3P_SwitchP35()               MODIFY_REG(PGA3_CR1, PGA3PS_MSK, ((0) << 0))
#define PGA3P_SwitchP20()               MODIFY_REG(PGA3_CR1, PGA3PS_MSK, ((1) << 0))
#define PGA3P_SwitchP70()               MODIFY_REG(PGA3_CR1, PGA3PS_MSK, ((2) << 0))
#define PGA3P_SwitchDAC2O()             MODIFY_REG(PGA3_CR1, PGA3PS_MSK, ((3) << 0))

#define PGA4O_PS_MSK                    (BIT5 | BIT4)
#define PGA4O_SwitchP13()               MODIFY_REG(PGA4_CR1, PGA4O_PS_MSK, ((0) << 4))
#define PGA4O_SwitchP40()               MODIFY_REG(PGA4_CR1, PGA4O_PS_MSK, ((1) << 4))
#define PGA4O_SwitchP74()               MODIFY_REG(PGA4_CR1, PGA4O_PS_MSK, ((2) << 4))
#define PGA4O_SwitchP63()               MODIFY_REG(PGA4_CR1, PGA4O_PS_MSK, ((3) << 4))

#define PGA4NS_MSK                      (BIT3 | BIT2)
#define PGA4N_SwitchP17()               MODIFY_REG(PGA4_CR1, PGA4NS_MSK, ((0) << 2))
#define PGA4N_SwitchP65()               MODIFY_REG(PGA4_CR1, PGA4NS_MSK, ((1) << 2))
#define PGA4N_SwitchP33()               MODIFY_REG(PGA4_CR1, PGA4NS_MSK, ((2) << 2))
#define PGA4N_SwitchDAC1O()             MODIFY_REG(PGA4_CR1, PGA4NS_MSK, ((3) << 2))

#define PGA4PS_MSK                      (BIT1 | BIT0)
#define PGA4P_SwitchP16()               MODIFY_REG(PGA4_CR1, PGA4PS_MSK, ((0) << 0))
#define PGA4P_SwitchP63()               MODIFY_REG(PGA4_CR1, PGA4PS_MSK, ((1) << 0))
#define PGA4P_SwitchP64()               MODIFY_REG(PGA4_CR1, PGA4PS_MSK, ((2) << 0))
#define PGA4P_SwitchDAC2O()             MODIFY_REG(PGA4_CR1, PGA4PS_MSK, ((3) << 0))

#define MCLKO_PS_MSK                    (BIT7)
#define CLK_MCLKO_SwitchP54()           CLR_REG_BIT(MCLKOCR, MCLKO_PS_MSK)
#define CLK_MCLKO_SwitchP16()           SET_REG_BIT(MCLKOCR, MCLKO_PS_MSK)

#define PWMA_C1PS_MSK                   (BIT1 | BIT0)
#define PWMA_C1SwitchP1011()            MODIFY_REG(PWMA_PS, PWMA_C1PS_MSK, ((0) << 0))
#define PWMA_C1SwitchP2021()            MODIFY_REG(PWMA_PS, PWMA_C1PS_MSK, ((1) << 0))
#define PWMA_C1SwitchP6061()            MODIFY_REG(PWMA_PS, PWMA_C1PS_MSK, ((2) << 0))

#define HSPWMA_C1SwitchP1011()          PWMA_C1SwitchP1011()
#define HSPWMA_C1SwitchP2021()          PWMA_C1SwitchP2021()
#define HSPWMA_C1SwitchP6061()          PWMA_C1SwitchP6061()

#define PWMA_C2PS_MSK                   (BIT3 | BIT2)
#define PWMA_C2SwitchP1213()            MODIFY_REG(PWMA_PS, PWMA_C2PS_MSK, ((0) << 2))
#define PWMA_C2SwitchP2223()            MODIFY_REG(PWMA_PS, PWMA_C2PS_MSK, ((1) << 2))
#define PWMA_C2SwitchP6263()            MODIFY_REG(PWMA_PS, PWMA_C2PS_MSK, ((2) << 2))

#define HSPWMA_C2SwitchP1213()          PWMA_C2SwitchP1213()
#define HSPWMA_C2SwitchP2223()          PWMA_C2SwitchP2223()
#define HSPWMA_C2SwitchP6263()          PWMA_C2SwitchP6263()

#define PWMA_C3PS_MSK                   (BIT5 | BIT4)
#define PWMA_C3SwitchP1415()            MODIFY_REG(PWMA_PS, PWMA_C3PS_MSK, ((0) << 4))
#define PWMA_C3SwitchP2425()            MODIFY_REG(PWMA_PS, PWMA_C3PS_MSK, ((1) << 4))
#define PWMA_C3SwitchP6465()            MODIFY_REG(PWMA_PS, PWMA_C3PS_MSK, ((2) << 4))

#define HSPWMA_C3SwitchP1415()          PWMA_C3SwitchP1415()
#define HSPWMA_C3SwitchP2425()          PWMA_C3SwitchP2425()
#define HSPWMA_C3SwitchP6465()          PWMA_C3SwitchP6465()

#define PWMA_C4PS_MSK                   (BIT7 | BIT6)
#define PWMA_C4SwitchP1617()            MODIFY_REG(PWMA_PS, PWMA_C4PS_MSK, ((0) << 6))
#define PWMA_C4SwitchP2627()            MODIFY_REG(PWMA_PS, PWMA_C4PS_MSK, ((1) << 6))
#define PWMA_C4SwitchP6667()            MODIFY_REG(PWMA_PS, PWMA_C4PS_MSK, ((2) << 6))
#define PWMA_C4SwitchP3433()            MODIFY_REG(PWMA_PS, PWMA_C4PS_MSK, ((3) << 6))

#define HSPWMA_C4SwitchP1617()          PWMA_C4SwitchP1617()
#define HSPWMA_C4SwitchP2627()          PWMA_C4SwitchP2627()
#define HSPWMA_C4SwitchP6667()          PWMA_C4SwitchP6667()
#define HSPWMA_C4SwitchP3433()          PWMA_C4SwitchP3433()

#define PWMA_C5PS_MSK                   (BIT1 | BIT0)
#define PWMA_C5SwitchP46()              MODIFY_REG(PWMA_PS2, PWMA_C5PS_MSK, ((0) << 0))
#define PWMA_C5SwitchP04()              MODIFY_REG(PWMA_PS2, PWMA_C5PS_MSK, ((1) << 0))
#define PWMA_C5SwitchP72()              MODIFY_REG(PWMA_PS2, PWMA_C5PS_MSK, ((2) << 0))
#define PWMA_C5SwitchP13()              MODIFY_REG(PWMA_PS2, PWMA_C5PS_MSK, ((3) << 0))

#define HSPWMA_C5SwitchP46()            PWMA_C5SwitchP46()
#define HSPWMA_C5SwitchP04()            PWMA_C5SwitchP04()
#define HSPWMA_C5SwitchP72()            PWMA_C5SwitchP72()
#define HSPWMA_C5SwitchP13()            PWMA_C5SwitchP13()

#define PWMA_C6PS_MSK                   (BIT3 | BIT2)
#define PWMA_C6SwitchP47()              MODIFY_REG(PWMA_PS2, PWMA_C6PS_MSK, ((0) << 2))
#define PWMA_C6SwitchP05()              MODIFY_REG(PWMA_PS2, PWMA_C6PS_MSK, ((1) << 2))
#define PWMA_C6SwitchP73()              MODIFY_REG(PWMA_PS2, PWMA_C6PS_MSK, ((2) << 2))
#define PWMA_C6SwitchP15()              MODIFY_REG(PWMA_PS2, PWMA_C6PS_MSK, ((3) << 2))

#define HSPWMA_C6SwitchP47()            PWMA_C6SwitchP47()
#define HSPWMA_C6SwitchP05()            PWMA_C6SwitchP05()
#define HSPWMA_C6SwitchP73()            PWMA_C6SwitchP73()
#define HSPWMA_C6SwitchP15()            PWMA_C6SwitchP15()

#define PWMB_C5PS_MSK                   (BIT1 | BIT0)
#define PWMB_C5SwitchP20()              MODIFY_REG(PWMB_PS, PWMB_C5PS_MSK, ((0) << 0))
#define PWMB_C5SwitchP17()              MODIFY_REG(PWMB_PS, PWMB_C5PS_MSK, ((1) << 0))
#define PWMB_C5SwitchP00()              MODIFY_REG(PWMB_PS, PWMB_C5PS_MSK, ((2) << 0))
#define PWMB_C5SwitchP74()              MODIFY_REG(PWMB_PS, PWMB_C5PS_MSK, ((3) << 0))

#define HSPWMB_C5SwitchP20()            PWMB_C5SwitchP20()
#define HSPWMB_C5SwitchP17()            PWMB_C5SwitchP17()
#define HSPWMB_C5SwitchP00()            PWMB_C5SwitchP00()
#define HSPWMB_C5SwitchP74()            PWMB_C5SwitchP74()

#define PWMB_C6PS_MSK                   (BIT3 | BIT2)
#define PWMB_C6SwitchP21()              MODIFY_REG(PWMB_PS, PWMB_C6PS_MSK, ((0) << 2))
#define PWMB_C6SwitchP54()              MODIFY_REG(PWMB_PS, PWMB_C6PS_MSK, ((1) << 2))
#define PWMB_C6SwitchP01()              MODIFY_REG(PWMB_PS, PWMB_C6PS_MSK, ((2) << 2))
#define PWMB_C6SwitchP75()              MODIFY_REG(PWMB_PS, PWMB_C6PS_MSK, ((3) << 2))

#define HSPWMB_C6SwitchP21()            PWMB_C6SwitchP21()
#define HSPWMB_C6SwitchP54()            PWMB_C6SwitchP54()
#define HSPWMB_C6SwitchP01()            PWMB_C6SwitchP01()
#define HSPWMB_C6SwitchP75()            PWMB_C6SwitchP75()

#define PWMB_C7PS_MSK                   (BIT5 | BIT4)
#define PWMB_C7SwitchP22()              MODIFY_REG(PWMB_PS, PWMB_C7PS_MSK, ((0) << 4))
#define PWMB_C7SwitchP33()              MODIFY_REG(PWMB_PS, PWMB_C7PS_MSK, ((1) << 4))
#define PWMB_C7SwitchP02()              MODIFY_REG(PWMB_PS, PWMB_C7PS_MSK, ((2) << 4))
#define PWMB_C7SwitchP76()              MODIFY_REG(PWMB_PS, PWMB_C7PS_MSK, ((3) << 4))

#define HSPWMB_C7SwitchP22()            PWMB_C7SwitchP22()
#define HSPWMB_C7SwitchP33()            PWMB_C7SwitchP33()
#define HSPWMB_C7SwitchP02()            PWMB_C7SwitchP02()
#define HSPWMB_C7SwitchP76()            PWMB_C7SwitchP76()

#define PWMB_C8PS_MSK                   (BIT7 | BIT6)
#define PWMB_C8SwitchP23()              MODIFY_REG(PWMB_PS, PWMB_C8PS_MSK, ((0) << 6))
#define PWMB_C8SwitchP34()              MODIFY_REG(PWMB_PS, PWMB_C8PS_MSK, ((1) << 6))
#define PWMB_C8SwitchP03()              MODIFY_REG(PWMB_PS, PWMB_C8PS_MSK, ((2) << 6))
#define PWMB_C8SwitchP77()              MODIFY_REG(PWMB_PS, PWMB_C8PS_MSK, ((3) << 6))

#define HSPWMB_C8SwitchP23()            PWMB_C8SwitchP23()
#define HSPWMB_C8SwitchP34()            PWMB_C8SwitchP34()
#define HSPWMB_C8SwitchP03()            PWMB_C8SwitchP03()
#define HSPWMB_C8SwitchP77()            PWMB_C8SwitchP77()

#define PWMC_C1PS_MSK                   (BIT1 | BIT0)
#define PWMC_C1SwitchP6061()            MODIFY_REG(PWMC_PS, PWMC_C1PS_MSK, ((0) << 0))
#define PWMC_C1SwitchP8081()            MODIFY_REG(PWMC_PS, PWMC_C1PS_MSK, ((1) << 0))
#define PWMC_C1SwitchP4041()            MODIFY_REG(PWMC_PS, PWMC_C1PS_MSK, ((2) << 0))
#define PWMC_C1SwitchPB0B1()            MODIFY_REG(PWMC_PS, PWMC_C1PS_MSK, ((3) << 0))

#define HSPWMC_C1SwitchP6061()          PWMC_C1SwitchP6061()
#define HSPWMC_C1SwitchP8081()          PWMC_C1SwitchP8081()
#define HSPWMC_C1SwitchP4041()          PWMC_C1SwitchP4041()
#define HSPWMC_C1SwitchPB0B1()          PWMC_C1SwitchPB0B1()

#define PWMC_C2PS_MSK                   (BIT3 | BIT2)
#define PWMC_C2SwitchP6263()            MODIFY_REG(PWMC_PS, PWMC_C2PS_MSK, ((0) << 2))
#define PWMC_C2SwitchP8283()            MODIFY_REG(PWMC_PS, PWMC_C2PS_MSK, ((1) << 2))
#define PWMC_C2SwitchP4243()            MODIFY_REG(PWMC_PS, PWMC_C2PS_MSK, ((2) << 2))
#define PWMC_C2SwitchPB2B3()            MODIFY_REG(PWMC_PS, PWMC_C2PS_MSK, ((3) << 2))

#define HSPWMC_C2SwitchP6263()          PWMC_C2SwitchP6263()
#define HSPWMC_C2SwitchP8283()          PWMC_C2SwitchP8283()
#define HSPWMC_C2SwitchP4243()          PWMC_C2SwitchP4243()
#define HSPWMC_C2SwitchPB2B3()          PWMC_C2SwitchPB2B3()

#define PWMC_C3PS_MSK                   (BIT5 | BIT4)
#define PWMC_C3SwitchP6465()            MODIFY_REG(PWMC_PS, PWMC_C3PS_MSK, ((0) << 4))
#define PWMC_C3SwitchP8485()            MODIFY_REG(PWMC_PS, PWMC_C3PS_MSK, ((1) << 4))
#define PWMC_C3SwitchP4445()            MODIFY_REG(PWMC_PS, PWMC_C3PS_MSK, ((2) << 4))
#define PWMC_C3SwitchPB4B5()            MODIFY_REG(PWMC_PS, PWMC_C3PS_MSK, ((3) << 4))

#define HSPWMC_C3SwitchP6465()          PWMC_C3SwitchP6465()
#define HSPWMC_C3SwitchP8485()          PWMC_C3SwitchP8485()
#define HSPWMC_C3SwitchP4445()          PWMC_C3SwitchP4445()
#define HSPWMC_C3SwitchPB4B5()          PWMC_C3SwitchPB4B5()

#define PWMC_C4PS_MSK                   (BIT7 | BIT6)
#define PWMC_C4SwitchP6667()            MODIFY_REG(PWMC_PS, PWMC_C4PS_MSK, ((0) << 6))
#define PWMC_C4SwitchP8687()            MODIFY_REG(PWMC_PS, PWMC_C4PS_MSK, ((1) << 6))
#define PWMC_C4SwitchP4647()            MODIFY_REG(PWMC_PS, PWMC_C4PS_MSK, ((2) << 6))
#define PWMC_C4SwitchPB6B7()            MODIFY_REG(PWMC_PS, PWMC_C4PS_MSK, ((3) << 6))

#define HSPWMC_C4SwitchP6667()          PWMC_C4SwitchP6667()
#define HSPWMC_C4SwitchP8687()          PWMC_C4SwitchP8687()
#define HSPWMC_C4SwitchP4647()          PWMC_C4SwitchP4647()
#define HSPWMC_C4SwitchPB6B7()          PWMC_C4SwitchPB6B7()

#define PWMC_C5PS_MSK                   (BIT1 | BIT0)
#define PWMC_C5SwitchP11()              MODIFY_REG(PWMC_PS2, PWMC_C5PS_MSK, ((0) << 0))
#define PWMC_C5SwitchP36()              MODIFY_REG(PWMC_PS2, PWMC_C5PS_MSK, ((1) << 0))
#define PWMC_C5SwitchP96()              MODIFY_REG(PWMC_PS2, PWMC_C5PS_MSK, ((2) << 0))
#define PWMC_C5SwitchP63()              MODIFY_REG(PWMC_PS2, PWMC_C5PS_MSK, ((3) << 0))

#define HSPWMC_C5SwitchP11()            PWMC_C5SwitchP11()
#define HSPWMC_C5SwitchP36()            PWMC_C5SwitchP36()
#define HSPWMC_C5SwitchP96()            PWMC_C5SwitchP96()
#define HSPWMC_C5SwitchP63()            PWMC_C5SwitchP63()

#define PWMC_C6PS_MSK                   (BIT3 | BIT2)
#define PWMC_C6SwitchP17()              MODIFY_REG(PWMC_PS2, PWMC_C6PS_MSK, ((0) << 2))
#define PWMC_C6SwitchP37()              MODIFY_REG(PWMC_PS2, PWMC_C6PS_MSK, ((1) << 2))
#define PWMC_C6SwitchP97()              MODIFY_REG(PWMC_PS2, PWMC_C6PS_MSK, ((2) << 2))
#define PWMC_C6SwitchP65()              MODIFY_REG(PWMC_PS2, PWMC_C6PS_MSK, ((3) << 2))

#define HSPWMC_C6SwitchP17()            PWMC_C6SwitchP17()
#define HSPWMC_C6SwitchP37()            PWMC_C6SwitchP37()
#define HSPWMC_C6SwitchP97()            PWMC_C6SwitchP97()
#define HSPWMC_C6SwitchP65()            PWMC_C6SwitchP65()

#define PWMD_C5PS_MSK                   (BIT1 | BIT0)
#define PWMD_C5SwitchP24()              MODIFY_REG(PWMD_PS, PWMD_C5PS_MSK, ((0) << 0))
#define PWMD_C5SwitchP81()              MODIFY_REG(PWMD_PS, PWMD_C5PS_MSK, ((1) << 0))
#define PWMD_C5SwitchP50()              MODIFY_REG(PWMD_PS, PWMD_C5PS_MSK, ((2) << 0))
#define PWMD_C5SwitchPB4()              MODIFY_REG(PWMD_PS, PWMD_C5PS_MSK, ((3) << 0))

#define HSPWMD_C5SwitchP24()            PWMD_C5SwitchP24()
#define HSPWMD_C5SwitchP81()            PWMD_C5SwitchP81()
#define HSPWMD_C5SwitchP50()            PWMD_C5SwitchP50()
#define HSPWMD_C5SwitchPB4()            PWMD_C5SwitchPB4()

#define PWMD_C6PS_MSK                   (BIT3 | BIT2)
#define PWMD_C6SwitchP25()              MODIFY_REG(PWMD_PS, PWMD_C6PS_MSK, ((0) << 2))
#define PWMD_C6SwitchP83()              MODIFY_REG(PWMD_PS, PWMD_C6PS_MSK, ((1) << 2))
#define PWMD_C6SwitchP51()              MODIFY_REG(PWMD_PS, PWMD_C6PS_MSK, ((2) << 2))
#define PWMD_C6SwitchPB5()              MODIFY_REG(PWMD_PS, PWMD_C6PS_MSK, ((3) << 2))

#define HSPWMD_C6SwitchP25()            PWMD_C6SwitchP25()
#define HSPWMD_C6SwitchP83()            PWMD_C6SwitchP83()
#define HSPWMD_C6SwitchP51()            PWMD_C6SwitchP51()
#define HSPWMD_C6SwitchPB5()            PWMD_C6SwitchPB5()

#define PWMD_C7PS_MSK                   (BIT5 | BIT4)
#define PWMD_C7SwitchP26()              MODIFY_REG(PWMD_PS, PWMD_C7PS_MSK, ((0) << 4))
#define PWMD_C7SwitchP85()              MODIFY_REG(PWMD_PS, PWMD_C7PS_MSK, ((1) << 4))
#define PWMD_C7SwitchP52()              MODIFY_REG(PWMD_PS, PWMD_C7PS_MSK, ((2) << 4))
#define PWMD_C7SwitchPB6()              MODIFY_REG(PWMD_PS, PWMD_C7PS_MSK, ((3) << 4))

#define HSPWMD_C7SwitchP26()            PWMD_C7SwitchP26()
#define HSPWMD_C7SwitchP85()            PWMD_C7SwitchP85()
#define HSPWMD_C7SwitchP52()            PWMD_C7SwitchP52()
#define HSPWMD_C7SwitchPB6()            PWMD_C7SwitchPB6()

#define PWMD_C8PS_MSK                   (BIT7 | BIT6)
#define PWMD_C8SwitchP27()              MODIFY_REG(PWMD_PS, PWMD_C8PS_MSK, ((0) << 6))
#define PWMD_C8SwitchP87()              MODIFY_REG(PWMD_PS, PWMD_C8PS_MSK, ((1) << 6))
#define PWMD_C8SwitchP53()              MODIFY_REG(PWMD_PS, PWMD_C8PS_MSK, ((2) << 6))
#define PWMD_C8SwitchPB7()              MODIFY_REG(PWMD_PS, PWMD_C8PS_MSK, ((3) << 6))

#define HSPWMD_C8SwitchP27()            PWMD_C8SwitchP27()
#define HSPWMD_C8SwitchP87()            PWMD_C8SwitchP87()
#define HSPWMD_C8SwitchP53()            PWMD_C8SwitchP53()
#define HSPWMD_C8SwitchPB7()            PWMD_C8SwitchPB7()

#define PWME_C1PS_MSK                   (BIT1 | BIT0)
#define PWME_C1SwitchP7071()            MODIFY_REG(PWME_PS, PWME_C1PS_MSK, ((0) << 0))
#define PWME_C1SwitchP9091()            MODIFY_REG(PWME_PS, PWME_C1PS_MSK, ((1) << 0))
#define PWME_C1SwitchPA0A1()            MODIFY_REG(PWME_PS, PWME_C1PS_MSK, ((2) << 0))

#define HSPWME_C1SwitchP7071()          PWME_C1SwitchP7071()
#define HSPWME_C1SwitchP9091()          PWME_C1SwitchP9091()
#define HSPWME_C1SwitchPA0A1()          PWME_C1SwitchPA0A1()

#define PWME_C2PS_MSK                   (BIT3 | BIT2)
#define PWME_C2SwitchP7273()            MODIFY_REG(PWME_PS, PWME_C2PS_MSK, ((0) << 2))
#define PWME_C2SwitchP9293()            MODIFY_REG(PWME_PS, PWME_C2PS_MSK, ((1) << 2))
#define PWME_C2SwitchPA2A3()            MODIFY_REG(PWME_PS, PWME_C2PS_MSK, ((2) << 2))

#define HSPWME_C2SwitchP7273()          PWME_C2SwitchP7273()
#define HSPWME_C2SwitchP9293()          PWME_C2SwitchP9293()
#define HSPWME_C2SwitchPA2A3()          PWME_C2SwitchPA2A3()

#define PWME_C3PS_MSK                   (BIT5 | BIT4)
#define PWME_C3SwitchP7475()            MODIFY_REG(PWME_PS, PWME_C3PS_MSK, ((0) << 4))
#define PWME_C3SwitchP9495()            MODIFY_REG(PWME_PS, PWME_C3PS_MSK, ((1) << 4))
#define PWME_C3SwitchPA4A5()            MODIFY_REG(PWME_PS, PWME_C3PS_MSK, ((2) << 4))

#define HSPWME_C3SwitchP7475()          PWME_C3SwitchP7475()
#define HSPWME_C3SwitchP9495()          PWME_C3SwitchP9495()
#define HSPWME_C3SwitchPA4A5()          PWME_C3SwitchPA4A5()

#define PWME_C4PS_MSK                   (BIT7 | BIT6)
#define PWME_C4SwitchP7677()            MODIFY_REG(PWME_PS, PWME_C4PS_MSK, ((0) << 6))
#define PWME_C4SwitchP9697()            MODIFY_REG(PWME_PS, PWME_C4PS_MSK, ((1) << 6))
#define PWME_C4SwitchPA6A7()            MODIFY_REG(PWME_PS, PWME_C4PS_MSK, ((2) << 6))

#define HSPWME_C4SwitchP7677()          PWME_C4SwitchP7677()
#define HSPWME_C4SwitchP9697()          PWME_C4SwitchP9697()
#define HSPWME_C4SwitchPA6A7()          PWME_C4SwitchPA6A7()

#define PWME_C5PS_MSK                   (BIT1 | BIT0)
#define PWME_C5SwitchP50()              MODIFY_REG(PWME_PS2, PWME_C5PS_MSK, ((0) << 0))
#define PWME_C5SwitchP43()              MODIFY_REG(PWME_PS2, PWME_C5PS_MSK, ((1) << 0))
#define PWME_C5SwitchPB4()              MODIFY_REG(PWME_PS2, PWME_C5PS_MSK, ((2) << 0))
#define PWME_C5SwitchP95()              MODIFY_REG(PWME_PS2, PWME_C5PS_MSK, ((3) << 0))

#define HSPWME_C5SwitchP50()            PWME_C5SwitchP50()
#define HSPWME_C5SwitchP43()            PWME_C5SwitchP43()
#define HSPWME_C5SwitchPB4()            PWME_C5SwitchPB4()
#define HSPWME_C5SwitchP95()            PWME_C5SwitchP95()

#define PWME_C6PS_MSK                   (BIT3 | BIT2)
#define PWME_C6SwitchP51()              MODIFY_REG(PWME_PS2, PWME_C6PS_MSK, ((0) << 2))
#define PWME_C6SwitchP44()              MODIFY_REG(PWME_PS2, PWME_C6PS_MSK, ((1) << 2))
#define PWME_C6SwitchPB5()              MODIFY_REG(PWME_PS2, PWME_C6PS_MSK, ((2) << 2))
#define PWME_C6SwitchP97()              MODIFY_REG(PWME_PS2, PWME_C6PS_MSK, ((3) << 2))

#define HSPWME_C6SwitchP51()            PWME_C6SwitchP51()
#define HSPWME_C6SwitchP44()            PWME_C6SwitchP44()
#define HSPWME_C6SwitchPB5()            PWME_C6SwitchPB5()
#define HSPWME_C6SwitchP97()            PWME_C6SwitchP97()

#define PWMF_C5PS_MSK                   (BIT1 | BIT0)
#define PWMF_C5SwitchP70()              MODIFY_REG(PWMF_PS, PWMF_C5PS_MSK, ((0) << 0))
#define PWMF_C5SwitchPA1()              MODIFY_REG(PWMF_PS, PWMF_C5PS_MSK, ((1) << 0))
#define PWMF_C5SwitchP90()              MODIFY_REG(PWMF_PS, PWMF_C5PS_MSK, ((2) << 0))

#define HSPWMF_C5SwitchP70()            PWMF_C5SwitchP70()
#define HSPWMF_C5SwitchPA1()            PWMF_C5SwitchPA1()
#define HSPWMF_C5SwitchP90()            PWMF_C5SwitchP90()

#define PWMF_C6PS_MSK                   (BIT3 | BIT2)
#define PWMF_C6SwitchP71()              MODIFY_REG(PWMF_PS, PWMF_C6PS_MSK, ((0) << 2))
#define PWMF_C6SwitchPA3()              MODIFY_REG(PWMF_PS, PWMF_C6PS_MSK, ((1) << 2))
#define PWMF_C6SwitchP91()              MODIFY_REG(PWMF_PS, PWMF_C6PS_MSK, ((2) << 2))

#define HSPWMF_C6SwitchP71()            PWMF_C6SwitchP71()
#define HSPWMF_C6SwitchPA3()            PWMF_C6SwitchPA3()
#define HSPWMF_C6SwitchP91()            PWMF_C6SwitchP91()

#define PWMF_C7PS_MSK                   (BIT5 | BIT4)
#define PWMF_C7SwitchP72()              MODIFY_REG(PWMF_PS, PWMF_C7PS_MSK, ((0) << 4))
#define PWMF_C7SwitchPA5()              MODIFY_REG(PWMF_PS, PWMF_C7PS_MSK, ((1) << 4))
#define PWMF_C7SwitchP92()              MODIFY_REG(PWMF_PS, PWMF_C7PS_MSK, ((2) << 4))

#define HSPWMF_C7SwitchP72()            PWMF_C7SwitchP72()
#define HSPWMF_C7SwitchPA5()            PWMF_C7SwitchPA5()
#define HSPWMF_C7SwitchP92()            PWMF_C7SwitchP92()

#define PWMF_C8PS_MSK                   (BIT7 | BIT6)
#define PWMF_C8SwitchP73()              MODIFY_REG(PWMF_PS, PWMF_C8PS_MSK, ((0) << 6))
#define PWMF_C8SwitchPA7()              MODIFY_REG(PWMF_PS, PWMF_C8PS_MSK, ((1) << 6))
#define PWMF_C8SwitchP93()              MODIFY_REG(PWMF_PS, PWMF_C8PS_MSK, ((2) << 6))

#define HSPWMF_C8SwitchP73()            PWMF_C8SwitchP73()
#define HSPWMF_C8SwitchPA7()            PWMF_C8SwitchPA7()
#define HSPWMF_C8SwitchP93()            PWMF_C8SwitchP93()

#define PWMA_ETRPS_MSK                  (BIT1 | BIT0)
#define PWMA_ETRSwitchP32()             MODIFY_REG(PWMA_ETRPS, PWMA_ETRPS_MSK, ((0) << 0))
#define PWMA_ETRSwitchP41()             MODIFY_REG(PWMA_ETRPS, PWMA_ETRPS_MSK, ((1) << 0))
#define PWMA_ETRSwitchP73()             MODIFY_REG(PWMA_ETRPS, PWMA_ETRPS_MSK, ((2) << 0))

#define HSPWMA_ETRSwitchP32()           PWMA_ETRSwitchP32()
#define HSPWMA_ETRSwitchP41()           PWMA_ETRSwitchP41()
#define HSPWMA_ETRSwitchP73()           PWMA_ETRSwitchP73()

#define PWMB_ETRPS_MSK                  (BIT1 | BIT0)
#define PWMB_ETRSwitchP32()             MODIFY_REG(PWMB_ETRPS, PWMB_ETRPS_MSK, ((0) << 0))
#define PWMB_ETRSwitchP06()             MODIFY_REG(PWMB_ETRPS, PWMB_ETRPS_MSK, ((1) << 0))

#define HSPWMB_ETRSwitchP32()           PWMB_ETRSwitchP32()
#define HSPWMB_ETRSwitchP06()           PWMB_ETRSwitchP06()

#define PWMC_ETRPS_MSK                  (BIT1 | BIT0)
#define PWMC_ETRSwitchP32()             MODIFY_REG(PWMC_ETRPS, PWMC_ETRPS_MSK, ((0) << 0))
#define PWMC_ETRSwitchP70()             MODIFY_REG(PWMC_ETRPS, PWMC_ETRPS_MSK, ((1) << 0))
#define PWMC_ETRSwitchP94()             MODIFY_REG(PWMC_ETRPS, PWMC_ETRPS_MSK, ((2) << 0))

#define HSPWMC_ETRSwitchP32()           PWMC_ETRSwitchP32()
#define HSPWMC_ETRSwitchP70()           PWMC_ETRSwitchP70()
#define HSPWMC_ETRSwitchP94()           PWMC_ETRSwitchP94()

#define PWMD_ETRPS_MSK                  (BIT1 | BIT0)
#define PWMD_ETRSwitchP32()             MODIFY_REG(PWMD_ETRPS, PWMD_ETRPS_MSK, ((0) << 0))
#define PWMD_ETRSwitchP70()             MODIFY_REG(PWMD_ETRPS, PWMD_ETRPS_MSK, ((1) << 0))

#define HSPWMD_ETRSwitchP32()           PWMD_ETRSwitchP32()
#define HSPWMD_ETRSwitchP70()           PWMD_ETRSwitchP70()

#define PWME_ETRPS_MSK                  (BIT1 | BIT0)
#define PWME_ETRSwitchP32()             MODIFY_REG(PWME_ETRPS, PWME_ETRPS_MSK, ((0) << 0))
#define PWME_ETRSwitchP02()             MODIFY_REG(PWME_ETRPS, PWME_ETRPS_MSK, ((2) << 0))

#define HSPWME_ETRSwitchP32()           PWME_ETRSwitchP32()
#define HSPWME_ETRSwitchP02()           PWME_ETRSwitchP02()

#define PWMF_ETRPS_MSK                  (BIT1 | BIT0)
#define PWMF_ETRSwitchP32()             MODIFY_REG(PWMF_ETRPS, PWMF_ETRPS_MSK, ((0) << 0))
#define PWMF_ETRSwitchPB1()             MODIFY_REG(PWMF_ETRPS, PWMF_ETRPS_MSK, ((1) << 0))
#define PWMF_ETRSwitchP00()             MODIFY_REG(PWMF_ETRPS, PWMF_ETRPS_MSK, ((2) << 0))

#define HSPWMF_ETRSwitchP32()           PWMF_ETRSwitchP32()
#define HSPWMF_ETRSwitchPB1()           PWMF_ETRSwitchPB1()
#define HSPWMF_ETRSwitchP00()           PWMF_ETRSwitchP00()

#define PWMA_BRKPS_MSK                  (BIT3 | BIT2)
#define PWMA_BRKSwitchP35()             MODIFY_REG(PWMA_ETRPS, PWMA_BRKPS_MSK, ((0) << 2))
#define PWMA_BRKSwitchCMPAO()           MODIFY_REG(PWMA_ETRPS, PWMA_BRKPS_MSK, ((1) << 2))
#define PWMA_BRKSwitchP45()             MODIFY_REG(PWMA_ETRPS, PWMA_BRKPS_MSK, ((2) << 2))

#define HSPWMA_BRKSwitchP35()           PWMA_BRKSwitchP35()
#define HSPWMA_BRKSwitchCMPAO()         PWMA_BRKSwitchCMPAO()
#define HSPWMA_BRKSwitchP45()           PWMA_BRKSwitchP45()

#define PWMB_BRKPS_MSK                  (BIT3 | BIT2)
#define PWMB_BRKSwitchP35()             MODIFY_REG(PWMB_ETRPS, PWMB_BRKPS_MSK, ((0) << 2))
#define PWMB_BRKSwitchCMPBO()           MODIFY_REG(PWMB_ETRPS, PWMB_BRKPS_MSK, ((1) << 2))
#define PWMB_BRKSwitchP07()             MODIFY_REG(PWMB_ETRPS, PWMB_BRKPS_MSK, ((2) << 2))

#define HSPWMB_BRKSwitchP35()           PWMB_BRKSwitchP35()
#define HSPWMB_BRKSwitchCMPBO()         PWMB_BRKSwitchCMPBO()
#define HSPWMB_BRKSwitchP07()           PWMB_BRKSwitchP07()

#define PWMC_BRKPS_MSK                  (BIT3 | BIT2)
#define PWMC_BRKSwitchP35()             MODIFY_REG(PWMC_ETRPS, PWMC_BRKPS_MSK, ((0) << 2))
#define PWMC_BRKSwitchCMPCO()           MODIFY_REG(PWMC_ETRPS, PWMC_BRKPS_MSK, ((1) << 2))
#define PWMC_BRKSwitchP71()             MODIFY_REG(PWMC_ETRPS, PWMC_BRKPS_MSK, ((2) << 2))
#define PWMC_BRKSwitchP95()             MODIFY_REG(PWMC_ETRPS, PWMC_BRKPS_MSK, ((2) << 2))

#define HSPWMC_BRKSwitchP35()           PWMC_BRKSwitchP35()
#define HSPWMC_BRKSwitchCMPCO()         PWMC_BRKSwitchCMPCO()
#define HSPWMC_BRKSwitchP71()           PWMC_BRKSwitchP71()
#define HSPWMC_BRKSwitchP95()           PWMC_BRKSwitchP95()

#define PWMD_BRKPS_MSK                  (BIT3 | BIT2)
#define PWMD_BRKSwitchP35()             MODIFY_REG(PWMD_ETRPS, PWMD_BRKPS_MSK, ((0) << 2))
#define PWMD_BRKSwitchCMPDO()           MODIFY_REG(PWMD_ETRPS, PWMD_BRKPS_MSK, ((1) << 2))
#define PWMD_BRKSwitchP71()             MODIFY_REG(PWMD_ETRPS, PWMD_BRKPS_MSK, ((2) << 2))

#define HSPWMD_BRKSwitchP35()           PWMD_BRKSwitchP35()
#define HSPWMD_BRKSwitchCMPDO()         PWMD_BRKSwitchCMPDO()
#define HSPWMD_BRKSwitchP71()           PWMD_BRKSwitchP71()

#define PWME_BRKPS_MSK                  (BIT3 | BIT2)
#define PWME_BRKSwitchP35()             MODIFY_REG(PWME_ETRPS, PWME_BRKPS_MSK, ((0) << 2))
#define PWME_BRKSwitchCMPEO()           MODIFY_REG(PWME_ETRPS, PWME_BRKPS_MSK, ((1) << 2))
#define PWME_BRKSwitchP03()             MODIFY_REG(PWME_ETRPS, PWME_BRKPS_MSK, ((3) << 2))

#define HSPWME_BRKSwitchP35()           PWME_BRKSwitchP35()
#define HSPWME_BRKSwitchCMPEO()         PWME_BRKSwitchCMPEO()
#define HSPWME_BRKSwitchP03()           PWME_BRKSwitchP03()

#define PWMF_BRKPS_MSK                  (BIT3 | BIT2)
#define PWMF_BRKSwitchP35()             MODIFY_REG(PWMF_ETRPS, PWMF_BRKPS_MSK, ((0) << 2))
#define PWMF_BRKSwitchCMPFO()           MODIFY_REG(PWMF_ETRPS, PWMF_BRKPS_MSK, ((1) << 2))
#define PWMF_BRKSwitchPB3()             MODIFY_REG(PWMF_ETRPS, PWMF_BRKPS_MSK, ((2) << 2))
#define PWMF_BRKSwitchP01()             MODIFY_REG(PWMF_ETRPS, PWMF_BRKPS_MSK, ((3) << 2))

#define HSPWMF_BRKSwitchP35()           PWMF_BRKSwitchP35()
#define HSPWMF_BRKSwitchCMPFO()         PWMF_BRKSwitchCMPFO()
#define HSPWMF_BRKSwitchPB3()           PWMF_BRKSwitchPB3()
#define HSPWMF_BRKSwitchP01()           PWMF_BRKSwitchP01()

#define PWMA_CMPAPS_MSK                 (BIT5 | BIT4)
#define PWMA_CMPASwitchCMP1()           MODIFY_REG(PWMA_ETRPS, PWMA_CMPAPS_MSK, ((0) << 4))
#define PWMA_CMPASwitchCMP2()           MODIFY_REG(PWMA_ETRPS, PWMA_CMPAPS_MSK, ((1) << 4))
#define PWMA_CMPASwitchCMP3()           MODIFY_REG(PWMA_ETRPS, PWMA_CMPAPS_MSK, ((2) << 4))
#define PWMA_CMPASwitchCMP4()           MODIFY_REG(PWMA_ETRPS, PWMA_CMPAPS_MSK, ((3) << 4))

#define HSPWMA_CMPASwitchCMP1()         PWMA_CMPASwitchCMP1()
#define HSPWMA_CMPASwitchCMP2()         PWMA_CMPASwitchCMP2()
#define HSPWMA_CMPASwitchCMP3()         PWMA_CMPASwitchCMP3()
#define HSPWMA_CMPASwitchCMP4()         PWMA_CMPASwitchCMP4()

#define PWMB_CMPBPS_MSK                 (BIT5 | BIT4)
#define PWMB_CMPBSwitchCMP1()           MODIFY_REG(PWMB_ETRPS, PWMB_CMPBPS_MSK, ((0) << 4))
#define PWMB_CMPBSwitchCMP2()           MODIFY_REG(PWMB_ETRPS, PWMB_CMPBPS_MSK, ((1) << 4))
#define PWMB_CMPBSwitchCMP3()           MODIFY_REG(PWMB_ETRPS, PWMB_CMPBPS_MSK, ((2) << 4))
#define PWMB_CMPBSwitchCMP4()           MODIFY_REG(PWMB_ETRPS, PWMB_CMPBPS_MSK, ((3) << 4))

#define HSPWMB_CMPBSwitchCMP1()         PWMB_CMPBSwitchCMP1()
#define HSPWMB_CMPBSwitchCMP2()         PWMB_CMPBSwitchCMP2()
#define HSPWMB_CMPBSwitchCMP3()         PWMB_CMPBSwitchCMP3()
#define HSPWMB_CMPBSwitchCMP4()         PWMB_CMPBSwitchCMP4()

#define PWMC_CMPCPS_MSK                 (BIT5 | BIT4)
#define PWMC_CMPCSwitchCMP1()           MODIFY_REG(PWMC_ETRPS, PWMC_CMPCPS_MSK, ((0) << 4))
#define PWMC_CMPCSwitchCMP2()           MODIFY_REG(PWMC_ETRPS, PWMC_CMPCPS_MSK, ((1) << 4))
#define PWMC_CMPCSwitchCMP3()           MODIFY_REG(PWMC_ETRPS, PWMC_CMPCPS_MSK, ((2) << 4))
#define PWMC_CMPCSwitchCMP4()           MODIFY_REG(PWMC_ETRPS, PWMC_CMPCPS_MSK, ((3) << 4))

#define HSPWMC_CMPCSwitchCMP1()         PWMC_CMPCSwitchCMP1()
#define HSPWMC_CMPCSwitchCMP2()         PWMC_CMPCSwitchCMP2()
#define HSPWMC_CMPCSwitchCMP3()         PWMC_CMPCSwitchCMP3()
#define HSPWMC_CMPCSwitchCMP4()         PWMC_CMPCSwitchCMP4()

#define PWMD_CMPDPS_MSK                 (BIT5 | BIT4)
#define PWMD_CMPDSwitchCMP1()           MODIFY_REG(PWMD_ETRPS, PWMD_CMPDPS_MSK, ((0) << 4))
#define PWMD_CMPDSwitchCMP2()           MODIFY_REG(PWMD_ETRPS, PWMD_CMPDPS_MSK, ((1) << 4))
#define PWMD_CMPDSwitchCMP3()           MODIFY_REG(PWMD_ETRPS, PWMD_CMPDPS_MSK, ((2) << 4))
#define PWMD_CMPDSwitchCMP4()           MODIFY_REG(PWMD_ETRPS, PWMD_CMPDPS_MSK, ((3) << 4))

#define HSPWMD_CMPDSwitchCMP1()         PWMD_CMPDSwitchCMP1()
#define HSPWMD_CMPDSwitchCMP2()         PWMD_CMPDSwitchCMP2()
#define HSPWMD_CMPDSwitchCMP3()         PWMD_CMPDSwitchCMP3()
#define HSPWMD_CMPDSwitchCMP4()         PWMD_CMPDSwitchCMP4()

#define PWME_CMPEPS_MSK                 (BIT5 | BIT4)
#define PWME_CMPESwitchCMP1()           MODIFY_REG(PWME_ETRPS, PWME_CMPEPS_MSK, ((0) << 4))
#define PWME_CMPESwitchCMP2()           MODIFY_REG(PWME_ETRPS, PWME_CMPEPS_MSK, ((1) << 4))
#define PWME_CMPESwitchCMP3()           MODIFY_REG(PWME_ETRPS, PWME_CMPEPS_MSK, ((2) << 4))
#define PWME_CMPESwitchCMP4()           MODIFY_REG(PWME_ETRPS, PWME_CMPEPS_MSK, ((3) << 4))

#define HSPWME_CMPESwitchCMP1()         PWME_CMPESwitchCMP1()
#define HSPWME_CMPESwitchCMP2()         PWME_CMPESwitchCMP2()
#define HSPWME_CMPESwitchCMP3()         PWME_CMPESwitchCMP3()
#define HSPWME_CMPESwitchCMP4()         PWME_CMPESwitchCMP4()

#define PWMF_CMPFPS_MSK                 (BIT5 | BIT4)
#define PWMF_CMPFSwitchCMP1()           MODIFY_REG(PWMF_ETRPS, PWMF_CMPFPS_MSK, ((0) << 4))
#define PWMF_CMPFSwitchCMP2()           MODIFY_REG(PWMF_ETRPS, PWMF_CMPFPS_MSK, ((1) << 4))
#define PWMF_CMPFSwitchCMP3()           MODIFY_REG(PWMF_ETRPS, PWMF_CMPFPS_MSK, ((2) << 4))
#define PWMF_CMPFSwitchCMP4()           MODIFY_REG(PWMF_ETRPS, PWMF_CMPFPS_MSK, ((3) << 4))

#define HSPWMF_CMPFSwitchCMP1()         PWMF_CMPFSwitchCMP1()
#define HSPWMF_CMPFSwitchCMP2()         PWMF_CMPFSwitchCMP2()
#define HSPWMF_CMPFSwitchCMP3()         PWMF_CMPFSwitchCMP3()
#define HSPWMF_CMPFSwitchCMP4()         PWMF_CMPFSwitchCMP4()

#define ADC_ETRPS_MSK                   (BIT7 | BIT6)
#define ADC1_ETRSwitchP12()             MODIFY_REG(ADCEXCFG, ADC_ETRPS_MSK, ((0) << 6))
#define ADC1_ETRSwitchP43()             MODIFY_REG(ADCEXCFG, ADC_ETRPS_MSK, ((1) << 6))

#define ADC2_ETRPS_MSK                  (BIT7 | BIT6)
#define ADC2_ETRSwitchP12()             MODIFY_REG(ADC2EXCFG, ADC2_ETRPS_MSK, ((0) << 6))
#define ADC2_ETRSwitchP43()             MODIFY_REG(ADC2EXCFG, ADC2_ETRPS_MSK, ((1) << 6))

#define LCM_DPS_MSK                     (BIT3 | BIT2)
#define LCM_DATA8BSwitchP2()            MODIFY_REG(LCMIFCFG, LCM_DPS_MSK, ((0) << 2))
#define LCM_DATA8BSwitchP6()            MODIFY_REG(LCMIFCFG, LCM_DPS_MSK, ((1) << 2))
#define LCM_DATA16BSwitchP2P0()         MODIFY_REG(LCMIFCFG, LCM_DPS_MSK, ((0) << 2))
#define LCM_DATA16BSwitchP6P2()         MODIFY_REG(LCMIFCFG, LCM_DPS_MSK, ((1) << 2))
#define LCM_DATA16BSwitchP2P4()         MODIFY_REG(LCMIFCFG, LCM_DPS_MSK, ((2) << 2))
#define LCM_DATA16BSwitchP6P7()         MODIFY_REG(LCMIFCFG, LCM_DPS_MSK, ((3) << 2))

#define LCM_RSPS_MSK                    (BIT6)
#define LCM_RSSwitchP45()               CLR_REG_BIT(LCMIFCFG2, LCM_RSPS_MSK)
#define LCM_RSSwitchP40()               SET_REG_BIT(LCMIFCFG2, LCM_RSPS_MSK)

#define LCM_RWPS_MSK                    (BIT5)
#define LCM_CTRLSwitchP4442()           CLR_REG_BIT(LCMIFCFG2, LCM_RWPS_MSK)
#define LCM_CTRLSwitchP3736()           SET_REG_BIT(LCMIFCFG2, LCM_RWPS_MSK)

#define LIN_PS_MSK                      (BIT1 | BIT0)
#define LIN1_SwitchP0203()              MODIFY_REG(P_SW1, LIN_PS_MSK, ((0) << 0))
#define LIN1_SwitchP5253()              MODIFY_REG(P_SW1, LIN_PS_MSK, ((1) << 0))
#define LIN1_SwitchP4647()              MODIFY_REG(P_SW1, LIN_PS_MSK, ((2) << 0))
#define LIN1_SwitchP7273()              MODIFY_REG(P_SW1, LIN_PS_MSK, ((3) << 0))

#define LIN2_PS_MSK                     (BIT5 | BIT4)
#define LIN2_SwitchP0607()              MODIFY_REG(P_SWX2, LIN2_PS_MSK, ((0) << 4))
#define LIN2_SwitchP2627()              MODIFY_REG(P_SWX2, LIN2_PS_MSK, ((1) << 4))
#define LIN2_SwitchP6263()              MODIFY_REG(P_SWX2, LIN2_PS_MSK, ((2) << 4))
#define LIN2_SwitchP8485()              MODIFY_REG(P_SWX2, LIN2_PS_MSK, ((3) << 4))

#define CAN1_PS_MSK                     (BIT5 | BIT4)
#define CAN1_PS2_MSK                    BIT2
#define CAN1_SwitchP000106()            MODIFY_REG(P_SW1, CAN1_PS_MSK, ((0) << 4)); CLR_REG_BIT(P_SWX1, CAN1_PS2_MSK)
#define CAN1_SwitchP505122()            MODIFY_REG(P_SW1, CAN1_PS_MSK, ((1) << 4)); CLR_REG_BIT(P_SWX1, CAN1_PS2_MSK)
#define CAN1_SwitchP424551()            MODIFY_REG(P_SW1, CAN1_PS_MSK, ((2) << 4)); CLR_REG_BIT(P_SWX1, CAN1_PS2_MSK)
#define CAN1_SwitchP707145()            MODIFY_REG(P_SW1, CAN1_PS_MSK, ((3) << 4)); CLR_REG_BIT(P_SWX1, CAN1_PS2_MSK)
#define CAN1_SwitchP303133()            MODIFY_REG(P_SW1, CAN1_PS_MSK, ((0) << 4)); SET_REG_BIT(P_SWX1, CAN1_PS2_MSK)
#define CAN1_SwitchP363712()            MODIFY_REG(P_SW1, CAN1_PS_MSK, ((1) << 4)); SET_REG_BIT(P_SWX1, CAN1_PS2_MSK)
#define CAN1_SwitchP141533()            MODIFY_REG(P_SW1, CAN1_PS_MSK, ((2) << 4)); SET_REG_BIT(P_SWX1, CAN1_PS2_MSK)
#define CAN1_SwitchP434474()            MODIFY_REG(P_SW1, CAN1_PS_MSK, ((3) << 4)); SET_REG_BIT(P_SWX1, CAN1_PS2_MSK)

#define CAN2_PS_MSK                     (BIT1 | BIT0)
#define CAN2_PS2_MSK                    BIT3
#define CAN2_SwitchP020307()            MODIFY_REG(P_SW3, CAN2_PS_MSK, ((0) << 0)); CLR_REG_BIT(P_SWX1, CAN2_PS2_MSK)
#define CAN2_SwitchP525323()            MODIFY_REG(P_SW3, CAN2_PS_MSK, ((1) << 0)); CLR_REG_BIT(P_SWX1, CAN2_PS2_MSK)
#define CAN2_SwitchP464753()            MODIFY_REG(P_SW3, CAN2_PS_MSK, ((2) << 0)); CLR_REG_BIT(P_SWX1, CAN2_PS2_MSK)
#define CAN2_SwitchP727347()            MODIFY_REG(P_SW3, CAN2_PS_MSK, ((3) << 0)); CLR_REG_BIT(P_SWX1, CAN2_PS2_MSK)
#define CAN2_SwitchP101107()            MODIFY_REG(P_SW3, CAN2_PS_MSK, ((0) << 0)); SET_REG_BIT(P_SWX1, CAN2_PS2_MSK)
#define CAN2_SwitchP848583()            MODIFY_REG(P_SW3, CAN2_PS_MSK, ((1) << 0)); SET_REG_BIT(P_SWX1, CAN2_PS2_MSK)
#define CAN2_SwitchPA0A123()            MODIFY_REG(P_SW3, CAN2_PS_MSK, ((2) << 0)); SET_REG_BIT(P_SWX1, CAN2_PS2_MSK)

/////////////////////////////////////////////////

#define CLKSEL_MCKSEL_MSK               (BIT1 | BIT0)
#define CLK_MCLK_HIRC()                 MODIFY_REG(CLKSEL, CLKSEL_MCKSEL_MSK, ((0x00) << 0))
#define CLK_MCLK_XTAL()                 MODIFY_REG(CLKSEL, CLKSEL_MCKSEL_MSK, ((0x01) << 0))
#define CLK_MCLK_X32K()                 MODIFY_REG(CLKSEL, CLKSEL_MCKSEL_MSK, ((0x02) << 0))
#define CLK_MCLK_LIRC()                 MODIFY_REG(CLKSEL, CLKSEL_MCKSEL_MSK, ((0x03) << 0))

#define CLKSEL_MCK2SEL_MSK              (BIT3 | BIT2)
#define CLK_MCLK2_BYPASS()              MODIFY_REG(CLKSEL, CLKSEL_MCK2SEL_MSK, ((0x00) << 2))
#define CLK_MCLK2_HPLL1D2()             MODIFY_REG(CLKSEL, CLKSEL_MCK2SEL_MSK, ((0x01) << 2))
#define CLK_MCLK2_HPLL2D2()             MODIFY_REG(CLKSEL, CLKSEL_MCK2SEL_MSK, ((0x02) << 2))
#define CLK_MCLK2_IRC48M()              MODIFY_REG(CLKSEL, CLKSEL_MCK2SEL_MSK, ((0x03) << 2))

//#define CKSEL_HSIOCK_MSK                (BIT6)
//#define CLK_HSIOCK_MCLK()               CLR_REG_BIT(CLKSEL, CKSEL_HSIOCK_MSK)
//#define CLK_HSIOCK_PLL()                SET_REG_BIT(CLKSEL, CKSEL_HSIOCK_MSK)
//
//#define CLK_HSIOCK_Divider(n)           WRITE_REG(HSCLKDIV, (n))

#define CLK_SYSCLK_Divider(n)           WRITE_REG(CLKDIV, (n))

#define MCLKODIV_MSK                    (~(BIT7))
#define CLK_MCLKO_Divider(n)            MODIFY_REG(MCLKOCR, MCLKODIV_MSK, (n))

#define HIRCCR_EN_MSK                   (BIT7)
#define HIRCCR_ST_MSK                   (BIT0)
#define CLK_HIRC_Enable()               SET_REG_BIT(HIRCCR, HIRCCR_EN_MSK)
#define CLK_HIRC_WaitStable()           while (READ_REG_BIT(HIRCCR, HIRCCR_ST_MSK) == 0)

#define IRCBAND_SEL_MSK                 (BIT1 | BIT0)
#define CLK_HIRC_16MHzBand()            MODIFY_REG(IRCBAND, IRCBAND_SEL_MSK, ((0) << 0))
#define CLK_HIRC_27MHzBand()            MODIFY_REG(IRCBAND, IRCBAND_SEL_MSK, ((1) << 0))
#define CLK_HIRC_44MHzBand()            MODIFY_REG(IRCBAND, IRCBAND_SEL_MSK, ((2) << 0))
#define CLK_HIRC_72MHzBand()            MODIFY_REG(IRCBAND, IRCBAND_SEL_MSK, ((3) << 0))

#define IRC48MCR_EN_MSK                 (BIT7)
#define IRC48MCR_ST_MSK                 (BIT0)
#define CLK_IRC48M_Enable()             SET_REG_BIT(IRC48MCR, IRC48MCR_EN_MSK)
#define CLK_IRC48M_WaitStable()         while (READ_REG_BIT(IRC48MCR, IRC48MCR_ST_MSK) == 0)

#define LIRCCR_EN_MSK                   (BIT7)
#define LIRCCR_ST_MSK                   (BIT0)
#define CLK_LIRC_Enable()               SET_REG_BIT(IRC32KCR, LIRCCR_EN_MSK)
#define CLK_LIRC_WaitStable()           while (READ_REG_BIT(IRC32KCR, LIRCCR_ST_MSK) == 0)

#define XOSCCR_EN_MSK                   (BIT7)
#define XOSCCR_XITYPE_MSK               (BIT6)
#define XOSCCR_GAIN_MSK                 (BIT5)
#define XOSCCR_FILTER_MSK               (BIT3 | BIT2)
#define XOSCCR_ST_MSK                   (BIT0)

#define CLK_XTAL_Enable()               SET_REG_BIT(XOSCCR, XOSCCR_EN_MSK | XOSCCR_XITYPE_MSK)
#define CLK_XOSC_Enable()               SET_REG_BIT(XOSCCR, XOSCCR_EN_MSK)
#define CLK_XOSC_WaitStable()           while (READ_REG_BIT(XOSCCR, XOSCCR_ST_MSK) == 0)

#define CLK_XOSC_LowGain()              CLR_REG_BIT(XOSCCR, XOSCCR_GAIN_MSK)
#define CLK_XOSC_FullGain()             SET_REG_BIT(XOSCCR, XOSCCR_GAIN_MSK)

#define CLK_XOSC_HighFilter()           MODIFY_REG(CLKSEL, XOSCCR_FILTER_MSK, ((0) << 2))
#define CLK_XOSC_MiddleFilter()         MODIFY_REG(CLKSEL, XOSCCR_FILTER_MSK, ((1) << 2))
#define CLK_XOSC_LowFilter()            MODIFY_REG(CLKSEL, XOSCCR_FILTER_MSK, ((2) << 2))

#define X32KCR_EN_MSK                   (BIT7)
#define X32KCR_GAIN_MSK                 (BIT6)
#define X32KCR_ST_MSK                   (BIT0)

#define CLK_X32K_Enable()               SET_REG_BIT(X32KCR, X32KCR_EN_MSK)
#define CLK_X32K_WaitStable()           while (READ_REG_BIT(X32KCR, X32KCR_ST_MSK) == 0)

#define CLK_X32K_LowGain()              CLR_REG_BIT(X32KCR, X32KCR_GAIN_MSK)
#define CLK_X32K_FullGain()             SET_REG_BIT(X32KCR, X32KCR_GAIN_MSK)

#define CLK_SPI1CLK_Divider(n)          WRITE_REG(SPI_CLKDIV, (n))
#define CLK_SPI2CLK_Divider(n)          WRITE_REG(SPI2_CLKDIV, (n))
#define CLK_SPI3CLK_Divider(n)          WRITE_REG(SPI3_CLKDIV, (n))
#define CLK_I2S1CLK_Divider(n)          WRITE_REG(I2S_CLKDIV, (n))
#define CLK_I2S2CLK_Divider(n)          WRITE_REG(I2S2_CLKDIV, (n))
#define CLK_PWMACLK_Divider(n)          WRITE_REG(PWMA_CLKDIV, (n))
#define CLK_PWMBCLK_Divider(n)          WRITE_REG(PWMB_CLKDIV, (n))
#define CLK_PWMCCLK_Divider(n)          WRITE_REG(PWMC_CLKDIV, (n))
#define CLK_PWMDCLK_Divider(n)          WRITE_REG(PWMD_CLKDIV, (n))
#define CLK_PWMECLK_Divider(n)          WRITE_REG(PWME_CLKDIV, (n))
#define CLK_PWMFCLK_Divider(n)          WRITE_REG(PWMF_CLKDIV, (n))
#define CLK_TFPUCLK_Divider(n)          WRITE_REG(TFPU_CLKDIV, (n))

#define HPLL1CR_ENHPLL1_MSK             BIT7
#define CLK_HPLL1_Enable()              SET_REG_BIT(HPLLCR, HPLL1CR_ENHPLL1_MSK)
#define CLK_HPLL1_Disable()             CLR_REG_BIT(HPLLCR, HPLL1CR_ENHPLL1_MSK)

#define HPLL1CR_HPLL1CKS_MSK            BIT4
#define CLK_HPLL1_BASECLK()             CLR_REG_BIT(HPLLCR, HPLL1CR_HPLL1CKS_MSK)
#define CLK_HPLL1_IRC48M()              SET_REG_BIT(HPLLCR, HPLL1CR_HPLL1CKS_MSK)

#define HPLL1CR_LOCK_MSK                (BIT_LN)
#define CLK_HPLL1_LockFreq(n)           MODIFY_REG(HPLLCR, HPLL1CR_LOCK_MSK, ((n) << 0))
#define CLK_HPLL1_Lock312MHz()          CLK_HPLL1_LockFreq(0)
#define CLK_HPLL1_Lock324MHz()          CLK_HPLL1_LockFreq(1)
#define CLK_HPLL1_Lock336MHz()          CLK_HPLL1_LockFreq(2)
#define CLK_HPLL1_Lock348MHz()          CLK_HPLL1_LockFreq(3)
#define CLK_HPLL1_Lock360MHz()          CLK_HPLL1_LockFreq(4)
#define CLK_HPLL1_Lock372MHz()          CLK_HPLL1_LockFreq(5)
#define CLK_HPLL1_Lock384MHz()          CLK_HPLL1_LockFreq(6)
#define CLK_HPLL1_Lock396MHz()          CLK_HPLL1_LockFreq(7)
#define CLK_HPLL1_Lock408MHz()          CLK_HPLL1_LockFreq(8)
#define CLK_HPLL1_Lock420MHz()          CLK_HPLL1_LockFreq(9)
#define CLK_HPLL1_Lock432MHz()          CLK_HPLL1_LockFreq(10)
#define CLK_HPLL1_Lock444MHz()          CLK_HPLL1_LockFreq(11)
#define CLK_HPLL1_Lock456MHz()          CLK_HPLL1_LockFreq(12)
#define CLK_HPLL1_Lock468MHz()          CLK_HPLL1_LockFreq(13)
#define CLK_HPLL1_Lock480MHz()          CLK_HPLL1_LockFreq(14)
#define CLK_HPLL1_Lock492MHz()          CLK_HPLL1_LockFreq(15)

#define CLK_HPLL1_PreDivider(n)         WRITE_REG(HPLLPDIV, (n))

#define HPLL2CR_ENHPLL2_MSK             BIT7
#define CLK_HPLL2_Enable()              SET_REG_BIT(HPLL2CR, HPLL2CR_ENHPLL2_MSK)
#define CLK_HPLL2_Disable()             CLR_REG_BIT(HPLL2CR, HPLL2CR_ENHPLL2_MSK)

#define HPLL2CR_HPLL2CKS_MSK            BIT4
#define CLK_HPLL2_BASECLK()             CLR_REG_BIT(HPLL2CR, HPLL2CR_HPLL2CKS_MSK)
#define CLK_HPLL2_IRC48M()              SET_REG_BIT(HPLL2CR, HPLL2CR_HPLL2CKS_MSK)

#define HPLL2CR_LOCK_MSK                (BIT_LN)
#define CLK_HPLL2_LockFreq(n)           MODIFY_REG(HPLL2CR, HPLL2CR_LOCK_MSK, ((n) << 0))
#define CLK_HPLL2_Lock312MHz()          CLK_HPLL2_LockFreq(0)
#define CLK_HPLL2_Lock324MHz()          CLK_HPLL2_LockFreq(1)
#define CLK_HPLL2_Lock336MHz()          CLK_HPLL2_LockFreq(2)
#define CLK_HPLL2_Lock348MHz()          CLK_HPLL2_LockFreq(3)
#define CLK_HPLL2_Lock360MHz()          CLK_HPLL2_LockFreq(4)
#define CLK_HPLL2_Lock372MHz()          CLK_HPLL2_LockFreq(5)
#define CLK_HPLL2_Lock384MHz()          CLK_HPLL2_LockFreq(6)
#define CLK_HPLL2_Lock396MHz()          CLK_HPLL2_LockFreq(7)
#define CLK_HPLL2_Lock408MHz()          CLK_HPLL2_LockFreq(8)
#define CLK_HPLL2_Lock420MHz()          CLK_HPLL2_LockFreq(9)
#define CLK_HPLL2_Lock432MHz()          CLK_HPLL2_LockFreq(10)
#define CLK_HPLL2_Lock444MHz()          CLK_HPLL2_LockFreq(11)
#define CLK_HPLL2_Lock456MHz()          CLK_HPLL2_LockFreq(12)
#define CLK_HPLL2_Lock468MHz()          CLK_HPLL2_LockFreq(13)
#define CLK_HPLL2_Lock480MHz()          CLK_HPLL2_LockFreq(14)
#define CLK_HPLL2_Lock492MHz()          CLK_HPLL2_LockFreq(15)

#define CLK_HPLL2_PreDivider(n)         WRITE_REG(HPLL2PDIV, (n))

#define HPLL1CR_HSI2SCK_MSK             (BIT6 | BIT5)
#define CLK_HSI2SCK_HPLL1D2()           MODIFY_REG(HPLLCR, HPLL1CR_HSI2SCK_MSK, ((0) << 5))
#define CLK_HSI2SCK_HPLL2D2()           MODIFY_REG(HPLLCR, HPLL1CR_HSI2SCK_MSK, ((1) << 5))
#define CLK_HSI2SCK_HPLL1()             MODIFY_REG(HPLLCR, HPLL1CR_HSI2SCK_MSK, ((2) << 5))
#define CLK_HSI2SCK_HPLL2()             MODIFY_REG(HPLLCR, HPLL1CR_HSI2SCK_MSK, ((3) << 5))

#define HPLL2CR_HSIOCK_MSK              (BIT6 | BIT5)
#define CLK_HSIOCK_HPLL1D2()            MODIFY_REG(HPLL2CR, HPLL2CR_HSIOCK_MSK, ((0) << 5))
#define CLK_HSIOCK_HPLL2D2()            MODIFY_REG(HPLL2CR, HPLL2CR_HSIOCK_MSK, ((1) << 5))
#define CLK_HSIOCK_HPLL1()              MODIFY_REG(HPLL2CR, HPLL2CR_HSIOCK_MSK, ((2) << 5))
#define CLK_HSIOCK_HPLL2()              MODIFY_REG(HPLL2CR, HPLL2CR_HSIOCK_MSK, ((3) << 5))

#define MCLKOCK_SEL_MSK                 (BIT5 | BIT4)
#define CLK_MCLKO_NONE()                MODIFY_REG(HIRCCR, MCLKOCK_SEL_MSK, ((0) << 4))
#define CLK_MCLKO_SYSCLK()              MODIFY_REG(HIRCCR, MCLKOCK_SEL_MSK, ((1) << 4))
#define CLK_MCLKO_HIRC()                MODIFY_REG(HIRCCR, MCLKOCK_SEL_MSK, ((2) << 4))
#define CLK_MCLKO_HIRCF()               MODIFY_REG(HIRCCR, MCLKOCK_SEL_MSK, ((3) << 4))

/////////////////////////////////////////////////

#define CRECR_ENCRE_MSK                 (BIT7)
#define CRECR_MONO_MSK                  (BIT6)
#define CRECR_UPT_MSK                   (BIT5 | BIT4)
#define CRECR_CREHF_MSK                 (BIT3)
#define CRECR_CREINC_MSK                (BIT2)
#define CRECR_CREDEC_MSK                (BIT1)
#define CRECR_CRERDY_MSK                (BIT0)

#define CRE_Enable()                    SET_REG_BIT(CRECR, CRECR_ENCRE_MSK)
#define CRE_Disable()                   CLR_REG_BIT(CRECR, CRECR_ENCRE_MSK)

#define CRE_OneStepMode()               CLR_REG_BIT(CRECR, CRECR_MONO_MSK)
#define CRE_TwoStepsMode()              SET_REG_BIT(CRECR, CRECR_MONO_MSK)

#define CRE_CalibCycle_1ms()            MODIFY_REG(CRECR, CRECR_UPT_MSK, ((0) << 4))
#define CRE_CalibCycle_4ms()            MODIFY_REG(CRECR, CRECR_UPT_MSK, ((1) << 4))
#define CRE_CalibCycle_32ms()           MODIFY_REG(CRECR, CRECR_UPT_MSK, ((2) << 4))
#define CRE_CalibCycle_64ms()           MODIFY_REG(CRECR, CRECR_UPT_MSK, ((3) << 4))

#define CRE_LowFrequency()              CLR_REG_BIT(CRECR, CRECR_CREHF_MSK)
#define CRE_HighFrequency()             SET_REG_BIT(CRECR, CRECR_CREHF_MSK)

#define CRE_CalibReady()                READ_REG_BIT(CRECR, CRECR_CRERDY_MSK)

#define CRE_LFCNT(freq)                 ((16UL * (freq)) / 32768)
#define CRE_HFCNT(freq)                 ((8UL * (freq)) / 32768)

#define CRE_SetCalibCounter(n)          WRITE_REG(CRECNTH, HIBYTE(n)); \
                                        WRITE_REG(CRECNTL, LOBYTE(n))

#define CRE_LFERROR(freq, err)          ((BYTE)(CRE_LFCNT(freq) * (err) / 1000))
#define CRE_HFERROR(freq, err)          ((BYTE)(CRE_HFCNT(freq) * (err) / 1000))

#define CRE_SetCalibError(n)            WRITE_REG(CRERES, (n))

/////////////////////////////////////////////////

#define WDTCONTR_FLAG_MSK               BIT7
#define WDTCONTR_EN_MSK                 BIT5
#define WDTCONTR_CLR_MSK                BIT4
#define WDTCONTR_IDL_MSK                BIT3
#define WDTCONTR_PS_MSK                 (BIT2 | BIT1 | BIT0)

#define WDT_Enable()                    SET_REG_BIT(WDT_CONTR, WDTCONTR_EN_MSK)
#define WDT_Clear()                     SET_REG_BIT(WDT_CONTR, WDTCONTR_CLR_MSK)
#define WDT_CheckWDTReset()             READ_REG_BIT(WDT_CONTR, WDTCONTR_FLAG_MSK)
#define WDT_IdlePause()                 CLR_REG_BIT(WDT_CONTR, WDTCONTR_IDL_MSK)
#define WDT_IdleContinue()              SET_REG_BIT(WDT_CONTR, WDTCONTR_IDL_MSK)

#define WDT_SetPrescale(n)              MODIFY_REG(WDT_CONTR, WDTCONTR_PS_MSK, ((n) << 0))
#define WDT_SetPrescale2()              WDT_SetPrescale(0)
#define WDT_SetPrescale4()              WDT_SetPrescale(1)
#define WDT_SetPrescale8()              WDT_SetPrescale(2)
#define WDT_SetPrescale16()             WDT_SetPrescale(3)
#define WDT_SetPrescale32()             WDT_SetPrescale(4)
#define WDT_SetPrescale64()             WDT_SetPrescale(5)
#define WDT_SetPrescale128()            WDT_SetPrescale(6)
#define WDT_SetPrescale256()            WDT_SetPrescale(7)

/////////////////////////////////////////////////

#define CHIPID_ReadID0()                CHIPID0
#define CHIPID_ReadID1()                CHIPID1
#define CHIPID_ReadID2()                CHIPID2
#define CHIPID_ReadID3()                CHIPID3
#define CHIPID_ReadID4()                CHIPID4
#define CHIPID_ReadID5()                CHIPID5
#define CHIPID_ReadID6()                CHIPID6
#define CHIPID_ReadREFVoltage()         MAKEWORD(CHIPID8, CHIPID7)
#define CHIPID_ReadLIRCFrequency()      MAKEWORD(CHIPID10, CHIPID9)
#define CHIPID_Read22MIRCTrim()         CHIPID11
#define CHIPID_Read24MIRCTrim()         CHIPID12
#define CHIPID_Read40MIRCTrim()         CHIPID13
#define CHIPID_Read45MIRCTrim()         CHIPID14
#define CHIPID_Read48MIRCTrim()         CHIPID15
#define CHIPID_Read49MIRCTrim()         CHIPID16
#define CHIPID_Read50MIRCTrim()         CHIPID17
#define CHIPID_Read55MIRCTrim()         CHIPID18
#define CHIPID_Read60MIRCTrim()         CHIPID19
#define CHIPID_Read64MIRCTrim()         CHIPID20
#define CHIPID_Read16MVRTrim()          CHIPID21
#define CHIPID_Read27MVRTrim()          CHIPID22
#define CHIPID_Read44MVRTrim()          CHIPID23
#define CHIPID_Read72MVRTrim()          CHIPID24
#define CHIPID_ReadTag()                CHIPID31

#define HIRC_22M1184()                          \
{                                               \
    IRTRIM = CHIPID_Read22MIRCTrim();           \
    VRTRIM = CHIPID_Read27MVRTrim();            \
    CLK_HIRC_27MHzBand();                       \
}

#define HIRC_24M()                              \
{                                               \
    IRTRIM = CHIPID_Read24MIRCTrim();           \
    VRTRIM = CHIPID_Read27MVRTrim();            \
    CLK_HIRC_27MHzBand();                       \
}

#define HIRC_40M()                              \
{                                               \
    IRTRIM = CHIPID_Read40MIRCTrim();           \
    VRTRIM = CHIPID_Read44MVRTrim();            \
    CLK_HIRC_44MHzBand();                       \
}

#define HIRC_45M1584()                          \
{                                               \
    IRTRIM = CHIPID_Read45MIRCTrim();           \
    VRTRIM = CHIPID_Read44MVRTrim();            \
    CLK_HIRC_44MHzBand();                       \
}

#define HIRC_48M()                              \
{                                               \
    IRTRIM = CHIPID_Read48MIRCTrim();           \
    VRTRIM = CHIPID_Read44MVRTrim();            \
    CLK_HIRC_44MHzBand();                       \
}

#define HIRC_49M152()                           \
{                                               \
    IRTRIM = CHIPID_Read49MIRCTrim();           \
    VRTRIM = CHIPID_Read44MVRTrim();            \
    CLK_HIRC_44MHzBand();                       \
}

#define HIRC_50M8032()                          \
{                                               \
    IRTRIM = CHIPID_Read50MIRCTrim();           \
    VRTRIM = CHIPID_Read44MVRTrim();            \
    CLK_HIRC_44MHzBand();                       \
}

#define HIRC_55M296()                           \
{                                               \
    IRTRIM = CHIPID_Read55MIRCTrim();           \
    VRTRIM = CHIPID_Read44MVRTrim();            \
    CLK_HIRC_44MHzBand();                       \
}

#define HIRC_60M()                              \
{                                               \
    IRTRIM = CHIPID_Read60MIRCTrim();           \
    VRTRIM = CHIPID_Read44MVRTrim();            \
    CLK_HIRC_44MHzBand();                       \
}

#define HIRC_64M()                              \
{                                               \
    IRTRIM = CHIPID_Read64MIRCTrim();           \
    VRTRIM = CHIPID_Read44MVRTrim();            \
    CLK_HIRC_44MHzBand();                       \
}

/////////////////////////////////////////////////

#define PORT_SetFallingInt(p, b)        CLR_REG_BIT(P##p##IM0, (b)); \
                                        CLR_REG_BIT(P##p##IM1, (b)); \
                                        CLR_REG_BIT(P##p##IM2, (b))

#define PORT_SetRisingInt(p, b)         SET_REG_BIT(P##p##IM0, (b)); \
                                        CLR_REG_BIT(P##p##IM1, (b)); \
                                        CLR_REG_BIT(P##p##IM2, (b))

#define PORT_SetLowLevelInt(p, b)       CLR_REG_BIT(P##p##IM0, (b)); \
                                        SET_REG_BIT(P##p##IM1, (b)); \
                                        CLR_REG_BIT(P##p##IM2, (b))

#define PORT_SetHighLevelInt(p, b)      SET_REG_BIT(P##p##IM0, (b)); \
                                        SET_REG_BIT(P##p##IM1, (b)); \
                                        CLR_REG_BIT(P##p##IM2, (b))

#define PORT_SetEdgeInt(p, b)           CLR_REG_BIT(P##p##IM0, (b)); \
                                        CLR_REG_BIT(P##p##IM1, (b)); \
                                        SET_REG_BIT(P##p##IM2, (b))

#define SetP0nFallingInt(b)             PORT_SetFallingInt(0, (b))
#define SetP1nFallingInt(b)             PORT_SetFallingInt(1, (b))
#define SetP2nFallingInt(b)             PORT_SetFallingInt(2, (b))
#define SetP3nFallingInt(b)             PORT_SetFallingInt(3, (b))
#define SetP4nFallingInt(b)             PORT_SetFallingInt(4, (b))
#define SetP5nFallingInt(b)             PORT_SetFallingInt(5, (b))
#define SetP6nFallingInt(b)             PORT_SetFallingInt(6, (b))
#define SetP7nFallingInt(b)             PORT_SetFallingInt(7, (b))
#define SetP8nFallingInt(b)             PORT_SetFallingInt(8, (b))
#define SetP9nFallingInt(b)             PORT_SetFallingInt(9, (b))
#define SetPAnFallingInt(b)             PORT_SetFallingInt(A, (b))
#define SetPBnFallingInt(b)             PORT_SetFallingInt(B, (b))

#define SetP0nRisingInt(b)              PORT_SetRisingInt(0, (b))
#define SetP1nRisingInt(b)              PORT_SetRisingInt(1, (b))
#define SetP2nRisingInt(b)              PORT_SetRisingInt(2, (b))
#define SetP3nRisingInt(b)              PORT_SetRisingInt(3, (b))
#define SetP4nRisingInt(b)              PORT_SetRisingInt(4, (b))
#define SetP5nRisingInt(b)              PORT_SetRisingInt(5, (b))
#define SetP6nRisingInt(b)              PORT_SetRisingInt(6, (b))
#define SetP7nRisingInt(b)              PORT_SetRisingInt(7, (b))
#define SetP8nRisingInt(b)              PORT_SetRisingInt(8, (b))
#define SetP9nRisingInt(b)              PORT_SetRisingInt(9, (b))
#define SetPAnRisingInt(b)              PORT_SetRisingInt(A, (b))
#define SetPBnRisingInt(b)              PORT_SetRisingInt(B, (b))

#define SetP0nLowLevelInt(b)            PORT_SetLowLevelInt(0, (b))
#define SetP1nLowLevelInt(b)            PORT_SetLowLevelInt(1, (b))
#define SetP2nLowLevelInt(b)            PORT_SetLowLevelInt(2, (b))
#define SetP3nLowLevelInt(b)            PORT_SetLowLevelInt(3, (b))
#define SetP4nLowLevelInt(b)            PORT_SetLowLevelInt(4, (b))
#define SetP5nLowLevelInt(b)            PORT_SetLowLevelInt(5, (b))
#define SetP6nLowLevelInt(b)            PORT_SetLowLevelInt(6, (b))
#define SetP7nLowLevelInt(b)            PORT_SetLowLevelInt(7, (b))
#define SetP8nLowLevelInt(b)            PORT_SetLowLevelInt(8, (b))
#define SetP9nLowLevelInt(b)            PORT_SetLowLevelInt(9, (b))
#define SetPAnLowLevelInt(b)            PORT_SetLowLevelInt(A, (b))
#define SetPBnLowLevelInt(b)            PORT_SetLowLevelInt(B, (b))

#define SetP0nHighLevelInt(b)           PORT_SetHighLevelInt(0, (b))
#define SetP1nHighLevelInt(b)           PORT_SetHighLevelInt(1, (b))
#define SetP2nHighLevelInt(b)           PORT_SetHighLevelInt(2, (b))
#define SetP3nHighLevelInt(b)           PORT_SetHighLevelInt(3, (b))
#define SetP4nHighLevelInt(b)           PORT_SetHighLevelInt(4, (b))
#define SetP5nHighLevelInt(b)           PORT_SetHighLevelInt(5, (b))
#define SetP6nHighLevelInt(b)           PORT_SetHighLevelInt(6, (b))
#define SetP7nHighLevelInt(b)           PORT_SetHighLevelInt(7, (b))
#define SetP8nHighLevelInt(b)           PORT_SetHighLevelInt(8, (b))
#define SetP9nHighLevelInt(b)           PORT_SetHighLevelInt(9, (b))
#define SetPAnHighLevelInt(b)           PORT_SetHighLevelInt(A, (b))
#define SetPBnHighLevelInt(b)           PORT_SetHighLevelInt(B, (b))

#define SetP0nEdgeInt(b)                PORT_SetEdgeInt(0, (b))
#define SetP1nEdgeInt(b)                PORT_SetEdgeInt(1, (b))
#define SetP2nEdgeInt(b)                PORT_SetEdgeInt(2, (b))
#define SetP3nEdgeInt(b)                PORT_SetEdgeInt(3, (b))
#define SetP4nEdgeInt(b)                PORT_SetEdgeInt(4, (b))
#define SetP5nEdgeInt(b)                PORT_SetEdgeInt(5, (b))
#define SetP6nEdgeInt(b)                PORT_SetEdgeInt(6, (b))
#define SetP7nEdgeInt(b)                PORT_SetEdgeInt(7, (b))
#define SetP8nEdgeInt(b)                PORT_SetEdgeInt(8, (b))
#define SetP9nEdgeInt(b)                PORT_SetEdgeInt(9, (b))
#define SetPAnEdgeInt(b)                PORT_SetEdgeInt(A, (b))
#define SetPBnEdgeInt(b)                PORT_SetEdgeInt(B, (b))

#define PORT_EnableIntWaieup(p, b)      SET_REG_BIT(P##p##WKUE, (b))

#define SetP0nIntWaieup(b)              PORT_EnableIntWaieup(0, (b))
#define SetP1nIntWaieup(b)              PORT_EnableIntWaieup(1, (b))
#define SetP2nIntWaieup(b)              PORT_EnableIntWaieup(2, (b))
#define SetP3nIntWaieup(b)              PORT_EnableIntWaieup(3, (b))
#define SetP4nIntWaieup(b)              PORT_EnableIntWaieup(4, (b))
#define SetP5nIntWaieup(b)              PORT_EnableIntWaieup(5, (b))
#define SetP6nIntWaieup(b)              PORT_EnableIntWaieup(6, (b))
#define SetP7nIntWaieup(b)              PORT_EnableIntWaieup(7, (b))
#define SetP8nIntWaieup(b)              PORT_EnableIntWaieup(8, (b))
#define SetP9nIntWaieup(b)              PORT_EnableIntWaieup(9, (b))
#define SetPAnIntWaieup(b)              PORT_EnableIntWaieup(A, (b))
#define SetPBnIntWaieup(b)              PORT_EnableIntWaieup(B, (b))

/////////////////////////////////////////////////

#define TIMER0_Run()                    (TR0 = 1)
#define TIMER0_Stop()                   (TR0 = 0)

#define TIMER0_SetReload8(n)            (TH0 = LOBYTE(n), TL0 = LOBYTE(n))
#define TIMER0_SetReload16(n)           (TH0 = HIBYTE(n), TL0 = LOBYTE(n))
#define TIMER0_SetPrescale(n)           (TM0PS = (n))

#define TMOD_T0M_MSK                    (BIT1 | BIT0)
#define TIMER0_Mode0()                  MODIFY_REG(TMOD, TMOD_T0M_MSK, ((0) << 0))
#define TIMER0_Mode1()                  MODIFY_REG(TMOD, TMOD_T0M_MSK, ((1) << 0))
#define TIMER0_Mode2()                  MODIFY_REG(TMOD, TMOD_T0M_MSK, ((2) << 0))
#define TIMER0_Mode3()                  MODIFY_REG(TMOD, TMOD_T0M_MSK, ((3) << 0))

#define AUXR_T0X12_MSK                  BIT7
#define TIMER0_1TMode()                 SET_REG_BIT(AUXR, AUXR_T0X12_MSK)
#define TIMER0_12TMode()                CLR_REG_BIT(AUXR, AUXR_T0X12_MSK)

#define TMOD_T0CT_MSK                   BIT2
#define TIMER0_TimerMode()              CLR_REG_BIT(TMOD, TMOD_T0CT_MSK)
#define TIMER0_CounterMode()            SET_REG_BIT(TMOD, TMOD_T0CT_MSK)

#define TMOD_T0GATE_MSK                 BIT3
#define TIMER0_EnableGateINT0()         SET_REG_BIT(TMOD, TMOD_T0GATE_MSK)
#define TIMER0_DisableGateINT0()        CLR_REG_BIT(TMOD, TMOD_T0GATE_MSK)

#define INTCLKO_T0CLKO_MSK              BIT0
#define TIMER0_EnableCLKO()             SET_REG_BIT(INTCLKO, INTCLKO_T0CLKO_MSK)
#define TIMER0_DisableCLKO()            CLR_REG_BIT(INTCLKO, INTCLKO_T0CLKO_MSK)

////////////////////////

#define TIMER1_Run()                    (TR1 = 1)
#define TIMER1_Stop()                   (TR1 = 0)

#define TIMER1_SetReload8(n)            (TH1 = LOBYTE(n), TL1 = LOBYTE(n))
#define TIMER1_SetReload16(n)           (TH1 = HIBYTE(n), TL1 = LOBYTE(n))
#define TIMER1_SetPrescale(n)           (TM1PS = (n))

#define TMOD_T1M_MSK                    (BIT5 | BIT4)
#define TIMER1_Mode0()                  MODIFY_REG(TMOD, TMOD_T1M_MSK, ((0) << 4))
#define TIMER1_Mode1()                  MODIFY_REG(TMOD, TMOD_T1M_MSK, ((1) << 4))
#define TIMER1_Mode2()                  MODIFY_REG(TMOD, TMOD_T1M_MSK, ((2) << 4))

#define AUXR_T1X12_MSK                  BIT6
#define TIMER1_1TMode()                 SET_REG_BIT(AUXR, AUXR_T1X12_MSK)
#define TIMER1_12TMode()                CLR_REG_BIT(AUXR, AUXR_T1X12_MSK)

#define TMOD_T1CT_MSK                   BIT6
#define TIMER1_TimerMode()              CLR_REG_BIT(TMOD, TMOD_T1CT_MSK)
#define TIMER1_CounterMode()            SET_REG_BIT(TMOD, TMOD_T1CT_MSK)

#define TMOD_T1GATE_MSK                 BIT7
#define TIMER1_EnableGateINT1()         SET_REG_BIT(TMOD, TMOD_T1GATE_MSK)
#define TIMER1_DisableGateINT1()        CLR_REG_BIT(TMOD, TMOD_T1GATE_MSK)

#define INTCLKO_T1CLKO_MSK              BIT1
#define TIMER1_EnableCLKO()             SET_REG_BIT(INTCLKO, INTCLKO_T1CLKO_MSK)
#define TIMER1_DisableCLKO()            CLR_REG_BIT(INTCLKO, INTCLKO_T1CLKO_MSK)

////////////////////////

#define AUXR_T2R_MSK                    BIT4
#define TIMER2_Run()                    SET_REG_BIT(AUXR, AUXR_T2R_MSK)
#define TIMER2_Stop()                   CLR_REG_BIT(AUXR, AUXR_T2R_MSK)

#define TIMER2_SetReload16(n)           (T2H = HIBYTE(n), T2L = LOBYTE(n))
#define TIMER2_SetPrescale(n)           (TM2PS = (n))

#define AUXR_T2X12_MSK                  BIT2
#define TIMER2_1TMode()                 SET_REG_BIT(AUXR, AUXR_T2X12_MSK)
#define TIMER2_12TMode()                CLR_REG_BIT(AUXR, AUXR_T2X12_MSK)

#define AUXR_T2CT_MSK                   BIT3
#define TIMER2_TimerMode()              CLR_REG_BIT(AUXR, AUXR_T2CT_MSK)
#define TIMER2_CounterMode()            SET_REG_BIT(AUXR, AUXR_T2CT_MSK)

#define INTCLKO_T2CLKO_MSK              BIT2
#define TIMER2_EnableCLKO()             SET_REG_BIT(INTCLKO, INTCLKO_T2CLKO_MSK)
#define TIMER2_DisableCLKO()            CLR_REG_BIT(INTCLKO, INTCLKO_T2CLKO_MSK)

////////////////////////

#define T4T3M_T3R_MSK                   BIT3
#define TIMER3_Run()                    SET_REG_BIT(T4T3M, T4T3M_T3R_MSK)
#define TIMER3_Stop()                   CLR_REG_BIT(T4T3M, T4T3M_T3R_MSK)

#define TIMER3_SetReload16(n)           (T3H = HIBYTE(n), T3L = LOBYTE(n))
#define TIMER3_SetPrescale(n)           (TM3PS = (n))

#define T4T3M_T3X12_MSK                 BIT1
#define TIMER3_1TMode()                 SET_REG_BIT(T4T3M, T4T3M_T3X12_MSK)
#define TIMER3_12TMode()                CLR_REG_BIT(T4T3M, T4T3M_T3X12_MSK)

#define T4T3M_T3CT_MSK                  BIT2
#define TIMER3_TimerMode()              CLR_REG_BIT(T4T3M, T4T3M_T3CT_MSK)
#define TIMER3_CounterMode()            SET_REG_BIT(T4T3M, T4T3M_T3CT_MSK)

#define T4T3M_T3CLKO_MSK                BIT0
#define TIMER3_EnableCLKO()             SET_REG_BIT(T4T3M, T4T3M_T3CLKO_MSK)
#define TIMER3_DisableCLKO()            CLR_REG_BIT(T4T3M, T4T3M_T3CLKO_MSK)

#define TIMERPS_T3T4SEL_MSK             BIT0
#define T3T4_CLKO_SwitchP0507()         CLR_REG_BIT(TIMER_PS, TIMERPS_T3T4SEL_MSK)
#define T3T4_CLKO_SwitchP0103()         SET_REG_BIT(TIMER_PS, TIMERPS_T3T4SEL_MSK)

////////////////////////

#define T4T3M_T4R_MSK                   BIT7
#define TIMER4_Run()                    SET_REG_BIT(T4T3M, T4T3M_T4R_MSK)
#define TIMER4_Stop()                   CLR_REG_BIT(T4T3M, T4T3M_T4R_MSK)

#define TIMER4_SetReload16(n)           (T4H = HIBYTE(n), T4L = LOBYTE(n))
#define TIMER4_SetPrescale(n)           (TM4PS = (n))

#define T4T3M_T4X12_MSK                 BIT5
#define TIMER4_1TMode()                 SET_REG_BIT(T4T3M, T4T3M_T4X12_MSK)
#define TIMER4_12TMode()                CLR_REG_BIT(T4T3M, T4T3M_T4X12_MSK)

#define T4T3M_T4CT_MSK                  BIT6
#define TIMER4_TimerMode()              CLR_REG_BIT(T4T3M, T4T3M_T4CT_MSK)
#define TIMER4_CounterMode()            SET_REG_BIT(T4T3M, T4T3M_T4CT_MSK)

#define T4T3M_T4CLKO_MSK                BIT4
#define TIMER4_EnableCLKO()             SET_REG_BIT(T4T3M, T4T3M_T4CLKO_MSK)
#define TIMER4_DisableCLKO()            CLR_REG_BIT(T4T3M, T4T3M_T4CLKO_MSK)

////////////////////////

#define T6T5M_T5R_MSK                   BIT3
#define TIMER5_Run()                    SET_REG_BIT(T6T5M, T6T5M_T5R_MSK)
#define TIMER5_Stop()                   CLR_REG_BIT(T6T5M, T6T5M_T5R_MSK)

#define TIMER5_SetReload16(n)           (T5H = HIBYTE(n), T5L = LOBYTE(n))
#define TIMER5_SetPrescale(n)           (TM5PS = (n))

#define T6T5M_T5X12_MSK                 BIT1
#define TIMER5_1TMode()                 SET_REG_BIT(T6T5M, T6T5M_T5X12_MSK)
#define TIMER5_12TMode()                CLR_REG_BIT(T6T5M, T6T5M_T5X12_MSK)

#define T6T5M_T5CT_MSK                  BIT2
#define TIMER5_TimerMode()              CLR_REG_BIT(T6T5M, T6T5M_T5CT_MSK)
#define TIMER5_CounterMode()            SET_REG_BIT(T6T5M, T6T5M_T5CT_MSK)

#define T6T5M_T5CLKO_MSK                BIT0
#define TIMER5_EnableCLKO()             SET_REG_BIT(T6T5M, T6T5M_T5CLKO_MSK)
#define TIMER5_DisableCLKO()            CLR_REG_BIT(T6T5M, T6T5M_T5CLKO_MSK)

////////////////////////

#define T6T5M_T6R_MSK                   BIT7
#define TIMER6_Run()                    SET_REG_BIT(T6T5M, T6T5M_T6R_MSK)
#define TIMER6_Stop()                   CLR_REG_BIT(T6T5M, T6T5M_T6R_MSK)

#define TIMER6_SetReload16(n)           (T6H = HIBYTE(n), T6L = LOBYTE(n))
#define TIMER6_SetPrescale(n)           (TM6PS = (n))

#define T6T5M_T6X12_MSK                 BIT5
#define TIMER6_1TMode()                 SET_REG_BIT(T6T5M, T6T5M_T6X12_MSK)
#define TIMER6_12TMode()                CLR_REG_BIT(T6T5M, T6T5M_T6X12_MSK)

#define T6T5M_T6CT_MSK                  BIT6
#define TIMER6_TimerMode()              CLR_REG_BIT(T6T5M, T6T5M_T6CT_MSK)
#define TIMER6_CounterMode()            SET_REG_BIT(T6T5M, T6T5M_T6CT_MSK)

#define T6T5M_T6CLKO_MSK                BIT4
#define TIMER6_EnableCLKO()             SET_REG_BIT(T6T5M, T6T5M_T6CLKO_MSK)
#define TIMER6_DisableCLKO()            CLR_REG_BIT(T6T5M, T6T5M_T6CLKO_MSK)

////////////////////////

#define T8T7M_T7R_MSK                   BIT3
#define TIMER7_Run()                    SET_REG_BIT(T8T7M, T8T7M_T7R_MSK)
#define TIMER7_Stop()                   CLR_REG_BIT(T8T7M, T8T7M_T7R_MSK)

#define TIMER7_SetReload16(n)           (T7H = HIBYTE(n), T7L = LOBYTE(n))
#define TIMER7_SetPrescale(n)           (TM7PS = (n))

#define T8T7M_T7X12_MSK                 BIT1
#define TIMER7_1TMode()                 SET_REG_BIT(T8T7M, T8T7M_T7X12_MSK)
#define TIMER7_12TMode()                CLR_REG_BIT(T8T7M, T8T7M_T7X12_MSK)

#define T8T7M_T7CT_MSK                  BIT2
#define TIMER7_TimerMode()              CLR_REG_BIT(T8T7M, T8T7M_T7CT_MSK)
#define TIMER7_CounterMode()            SET_REG_BIT(T8T7M, T8T7M_T7CT_MSK)

#define T8T7M_T7CLKO_MSK                BIT0
#define TIMER7_EnableCLKO()             SET_REG_BIT(T8T7M, T8T7M_T7CLKO_MSK)
#define TIMER7_DisableCLKO()            CLR_REG_BIT(T8T7M, T8T7M_T7CLKO_MSK)

////////////////////////

#define T8T7M_T8R_MSK                   BIT7
#define TIMER8_Run()                    SET_REG_BIT(T8T7M, T8T7M_T8R_MSK)
#define TIMER8_Stop()                   CLR_REG_BIT(T8T7M, T8T7M_T8R_MSK)

#define TIMER8_SetReload16(n)           (T8H = HIBYTE(n), T8L = LOBYTE(n))
#define TIMER8_SetPrescale(n)           (TM8PS = (n))

#define T8T7M_T8X12_MSK                 BIT5
#define TIMER8_1TMode()                 SET_REG_BIT(T8T7M, T8T7M_T8X12_MSK)
#define TIMER8_12TMode()                CLR_REG_BIT(T8T7M, T8T7M_T8X12_MSK)

#define T8T7M_T8CT_MSK                  BIT6
#define TIMER8_TimerMode()              CLR_REG_BIT(T8T7M, T8T7M_T8CT_MSK)
#define TIMER8_CounterMode()            SET_REG_BIT(T8T7M, T8T7M_T8CT_MSK)

#define T8T7M_T8CLKO_MSK                BIT4
#define TIMER8_EnableCLKO()             SET_REG_BIT(T8T7M, T8T7M_T8CLKO_MSK)
#define TIMER8_DisableCLKO()            CLR_REG_BIT(T8T7M, T8T7M_T8CLKO_MSK)

////////////////////////

#define T10T9M_T9R_MSK                  BIT3
#define TIMER9_Run()                    SET_REG_BIT(T10T9M, T10T9M_T9R_MSK)
#define TIMER9_Stop()                   CLR_REG_BIT(T10T9M, T10T9M_T9R_MSK)

#define TIMER9_SetReload16(n)           (T9H = HIBYTE(n), T9L = LOBYTE(n))
#define TIMER9_SetPrescale(n)           (TM9PS = (n))

#define T10T9M_T9X12_MSK                BIT1
#define TIMER9_1TMode()                 SET_REG_BIT(T10T9M, T10T9M_T9X12_MSK)
#define TIMER9_12TMode()                CLR_REG_BIT(T10T9M, T10T9M_T9X12_MSK)

#define T10T9M_T9CT_MSK                 BIT2
#define TIMER9_TimerMode()              CLR_REG_BIT(T10T9M, T10T9M_T9CT_MSK)
#define TIMER9_CounterMode()            SET_REG_BIT(T10T9M, T10T9M_T9CT_MSK)

#define T10T9M_T9CLKO_MSK               BIT0
#define TIMER9_EnableCLKO()             SET_REG_BIT(T10T9M, T10T9M_T9CLKO_MSK)
#define TIMER9_DisableCLKO()            CLR_REG_BIT(T10T9M, T10T9M_T9CLKO_MSK)

#define TIMERPS_T9T10SEL_MSK            BIT3
#define T9T10_CLKO_SwitchP7161()        CLR_REG_BIT(TIMER_PS, TIMERPS_T9T10SEL_MSK)
#define T9T10_CLKO_SwitchPB1B7()        SET_REG_BIT(TIMER_PS, TIMERPS_T9T10SEL_MSK)

////////////////////////

#define T10T9M_T10R_MSK                 BIT7
#define TIMER10_Run()                   SET_REG_BIT(T10T9M, T10T9M_T10R_MSK)
#define TIMER10_Stop()                  CLR_REG_BIT(T10T9M, T10T9M_T10R_MSK)

#define TIMER10_SetReload16(n)          (T10H = HIBYTE(n), T10L = LOBYTE(n))
#define TIMER10_SetPrescale(n)          (TM8PS = (n))

#define T10T9M_T10X12_MSK               BIT5
#define TIMER10_1TMode()                SET_REG_BIT(T10T9M, T10T9M_T10X12_MSK)
#define TIMER10_12TMode()               CLR_REG_BIT(T10T9M, T10T9M_T10X12_MSK)

#define T10T9M_T10CT_MSK                BIT6
#define TIMER10_TimerMode()             CLR_REG_BIT(T10T9M, T10T9M_T10CT_MSK)
#define TIMER10_CounterMode()           SET_REG_BIT(T10T9M, T10T9M_T10CT_MSK)

#define T10T9M_T10CLKO_MSK              BIT4
#define TIMER10_EnableCLKO()            SET_REG_BIT(T10T9M, T10T9M_T10CLKO_MSK)
#define TIMER10_DisableCLKO()           CLR_REG_BIT(T10T9M, T10T9M_T10CLKO_MSK)

////////////////////////

#define T11CR_T11R_MSK                  BIT7
#define TIMER11_Run()                   SET_REG_BIT(T11CR, T11CR_T11R_MSK)
#define TIMER11_Stop()                  CLR_REG_BIT(T11CR, T11CR_T11R_MSK)

#define TIMER11_CheckFlag()             READ_REG_BIT(T11CR, T11CR_T11IF_MSK)
#define TIMER11_ClearFlag()             CLR_REG_BIT(T11CR, T11CR_T11IF_MSK)

#define TIMER11_SetReload16(n)          (T11H = HIBYTE(n), T11L = LOBYTE(n))
#define TIMER11_SetPrescale(n)          (T11PS = (n))

#define T11CR_T11X12_MSK                BIT4
#define TIMER11_1TMode()                SET_REG_BIT(T11CR, T11CR_T11X12_MSK)
#define TIMER11_12TMode()               CLR_REG_BIT(T11CR, T11CR_T11X12_MSK)

#define T11CR_T11CT_MSK                 BIT6
#define TIMER11_TimerMode()             CLR_REG_BIT(T11CR, T11CR_T11CT_MSK)
#define TIMER11_CounterMode()           SET_REG_BIT(T11CR, T11CR_T11CT_MSK)

#define T11CR_T11CLKO_MSK               BIT5
#define TIMER11_EnableCLKO()            SET_REG_BIT(T11CR, T11CR_T11CLKO_MSK)
#define TIMER11_DisableCLKO()           CLR_REG_BIT(T11CR, T11CR_T11CLKO_MSK)

#define TIMERPS_T11SEL_MSK              (BIT5 | BIT4)
#define T11_CLKO_SwitchP77()            MODIFY_REG(TIMER_PS, TIMERPS_T11SEL_MSK, ((0) << 4))
#define T11_CLKO_SwitchP15()            MODIFY_REG(TIMER_PS, TIMERPS_T11SEL_MSK, ((1) << 4))
#define T11_CLKO_SwitchPA7()            MODIFY_REG(TIMER_PS, TIMERPS_T11SEL_MSK, ((2) << 4))
#define T11_CLKO_SwitchP45()            MODIFY_REG(TIMER_PS, TIMERPS_T11SEL_MSK, ((3) << 4))

#define T11CR_T11CS_MSK                 (BIT3 | BIT2)
#define TIMER11_ClockSource(n)          MODIFY_REG(T11CR, T11CR_T11CS_MSK, ((n) << 2))
#define TIMER11_CLK_SYSCLK()            TIMER11_ClockSource(0)
#define TIMER11_CLK_HIRC()              TIMER11_ClockSource(1)
#define TIMER11_CLK_X32K()              TIMER11_ClockSource(2)
#define TIMER11_CLK_LIRC()              TIMER11_ClockSource(3)

////////////////////////

#define T18T17M_T17R_MSK                BIT3
#define TIMER17_Run()                   SET_REG_BIT(T18T17M, T18T17M_T17R_MSK)
#define TIMER17_Stop()                  CLR_REG_BIT(T18T17M, T18T17M_T17R_MSK)

#define TIMER17_SetReload16(n)          (T17H = HIBYTE(n), T17L = LOBYTE(n))
#define TIMER17_SetPrescale(n)          (TM17PS = (n))

#define T18T17M_T17X12_MSK              BIT1
#define TIMER17_1TMode()                SET_REG_BIT(T18T17M, T18T17M_T17X12_MSK)
#define TIMER17_12TMode()               CLR_REG_BIT(T18T17M, T18T17M_T17X12_MSK)

#define T18T17M_T17CT_MSK               BIT2
#define TIMER17_TimerMode()             CLR_REG_BIT(T18T17M, T18T17M_T17CT_MSK)
#define TIMER17_CounterMode()           SET_REG_BIT(T18T17M, T18T17M_T17CT_MSK)

#define T18T17M_T17CLKO_MSK             BIT0
#define TIMER17_EnableCLKO()            SET_REG_BIT(T18T17M, T18T17M_T17CLKO_MSK)
#define TIMER17_DisableCLKO()           CLR_REG_BIT(T18T17M, T18T17M_T17CLKO_MSK)

////////////////////////

#define T18T17M_T18R_MSK                BIT7
#define TIMER18_Run()                   SET_REG_BIT(T18T17M, T18T17M_T18R_MSK)
#define TIMER18_Stop()                  CLR_REG_BIT(T18T17M, T18T17M_T18R_MSK)

#define TIMER18_SetReload16(n)          (T18H = HIBYTE(n), T18L = LOBYTE(n))
#define TIMER18_SetPrescale(n)          (TM18PS = (n))

#define T18T17M_T18X12_MSK              BIT5
#define TIMER18_1TMode()                SET_REG_BIT(T18T17M, T18T17M_T18X12_MSK)
#define TIMER18_12TMode()               CLR_REG_BIT(T18T17M, T18T17M_T18X12_MSK)

#define T18T17M_T18CT_MSK               BIT6
#define TIMER18_TimerMode()             CLR_REG_BIT(T18T17M, T18T17M_T18CT_MSK)
#define TIMER18_CounterMode()           SET_REG_BIT(T18T17M, T18T17M_T18CT_MSK)

#define T18T17M_T18CLKO_MSK             BIT4
#define TIMER18_EnableCLKO()            SET_REG_BIT(T18T17M, T18T17M_T18CLKO_MSK)
#define TIMER18_DisableCLKO()           CLR_REG_BIT(T18T17M, T18T17M_T18CLKO_MSK)

/////////////////////////////////////////////////

#define SCON_SM_MSK                     (BIT7 | BIT6)
#define UART1_SetMode(n)                MODIFY_REG(SCON, SCON_SM_MSK, ((n) << 6))
#define UART1_Mode0()                   UART1_SetMode(0)
#define UART1_Mode1()                   UART1_SetMode(1)
#define UART1_Mode2()                   UART1_SetMode(2)
#define UART1_Mode3()                   UART1_SetMode(3)

#define UART1_EnableRx()                (REN = 1)
#define UART1_DisableRx()               (REN = 0)
#define UART1_SetTB8(b)                 (TB8 = (b))
#define UART1_ReadRB8()                 (RB8)

#define UART1_SendData(d)               (SBUF = (d))
#define UART1_ReadData()                (SBUF)

#define PCON_SMOD_MSK                   BIT7
#define UART1_BaudrateX2()              SET_REG_BIT(PCON, PCON_SMOD_MSK)

#define AUXR_M0X6_MSK                   BIT5
#define UART1_Mode0BaudrateX6()         SET_REG_BIT(AUXR, AUXR_M0X6_MSK)

#define USARTCR2_PCEN_MSK               BIT2
#define USARTCR2_PS_MSK                 BIT1
#define UART1_NoneParity()              CLR_REG_BIT(USARTCR2, USARTCR2_PCEN_MSK)
#define UART1_OddParity()               SET_REG_BIT(USARTCR2, USARTCR2_PCEN_MSK); \
                                        SET_REG_BIT(USARTCR2, USARTCR2_PS_MSK)
#define UART1_EvenParity()              SET_REG_BIT(USARTCR2, USARTCR2_PCEN_MSK); \
                                        CLR_REG_BIT(USARTCR2, USARTCR2_PS_MSK)
#define UART1_MarkParity()              CLR_REG_BIT(USARTCR2, USARTCR2_PCEN_MSK); \
                                        UART1_SetTB8(1)
#define UART1_SpaceParity()             CLR_REG_BIT(USARTCR2, USARTCR2_PCEN_MSK); \
                                        UART1_SetTB8(0)

#define UR1TOCR_ENTO_MSK                BIT7
#define UART1_EnableTimeout()           SET_REG_BIT(UR1TOCR, UR1TOCR_ENTO_MSK)
#define UART1_DisableTimeout()          CLR_REG_BIT(UR1TOCR, UR1TOCR_ENTO_MSK)

#define UR1TOCR_SCALE_MSK               BIT5
#define UART1_TimeoutScale_SYSCLK()     SET_REG_BIT(UR1TOCR, UR1TOCR_SCALE_MSK)
#define UART1_TimeoutScale_BRT()        CLR_REG_BIT(UR1TOCR, UR1TOCR_SCALE_MSK)

#define UART1_SetTimeoutInterval(n)     UR1TOTL = BYTE0(n); \
                                        UR1TOTH = BYTE1(n); \
                                        UR1TOTE = BYTE2(n)

#define AUXR_S1BRT_MSK                  BIT0
#define UART1_Timer1BRT()               CLR_REG_BIT(AUXR, AUXR_S1BRT_MSK)
#define UART1_Timer2BRT()               SET_REG_BIT(AUXR, AUXR_S1BRT_MSK)

////////////////////////

#define S2CON_S2SM_MSK                  (BIT7 | BIT6)
#define UART2_SetMode(n)                MODIFY_REG(S2CON, S2CON_S2SM_MSK, ((n) << 6))
#define UART2_Mode0()                   UART2_SetMode(0)
#define UART2_Mode1()                   UART2_SetMode(1)
#define UART2_Mode2()                   UART2_SetMode(2)
#define UART2_Mode3()                   UART2_SetMode(3)

#define S2CON_S2REN_MSK                 BIT4
#define UART2_EnableRx()                SET_REG_BIT(S2CON, S2CON_S2REN_MSK)
#define UART2_DisableRx()               CLR_REG_BIT(S2CON, S2CON_S2REN_MSK)

#define S2CON_S2TB8_MSK                 BIT3
#define UART2_SetTB8(b)                 MODIFY_REG(S2CON, S2CON_S2TB8_MSK, ((b) << 3))

#define S2CON_S2RB8_MSK                 BIT2
#define UART2_ReadRB8()                 READ_REG_BIT(S2CON, S2CON_S2RB8_MSK)

#define UART2_SendData(d)               (S2BUF = (d))
#define UART2_ReadData()                (S2BUF)

#define S2CFG_S2M0X6_MSK                BIT5
#define UART2_Mode0BaudrateX6()         SET_REG_BIT(S2CFG, S2CFG_S2M0X6_MSK)

#define S2CFG_W1_MSK                    BIT1
#define UART2_Timer2BRT()               SET_REG_BIT(S2CFG, S2CFG_W1_MSK)

#define USART2CR2_PCEN_MSK              BIT2
#define USART2CR2_PS_MSK                BIT1
#define UART2_NoneParity()              CLR_REG_BIT(USART2CR2, USART2CR2_PCEN_MSK)
#define UART2_OddParity()               SET_REG_BIT(USART2CR2, USART2CR2_PCEN_MSK); \
                                        SET_REG_BIT(USART2CR2, USART2CR2_PS_MSK)
#define UART2_EvenParity()              SET_REG_BIT(USART2CR2, USART2CR2_PCEN_MSK); \
                                        CLR_REG_BIT(USART2CR2, USART2CR2_PS_MSK)
#define UART2_MarkParity()              CLR_REG_BIT(USART2CR2, USART2CR2_PCEN_MSK); \
                                        UART2_SetTB8(1)
#define UART2_SpaceParity()             CLR_REG_BIT(USART2CR2, USART2CR2_PCEN_MSK); \
                                        UART2_SetTB8(0)

#define UR2TOCR_ENTO_MSK                BIT7
#define UART2_EnableTimeout()           SET_REG_BIT(UR2TOCR, UR2TOCR_ENTO_MSK)
#define UART2_DisableTimeout()          CLR_REG_BIT(UR2TOCR, UR2TOCR_ENTO_MSK)

#define UR2TOCR_SCALE_MSK               BIT5
#define UART2_TimeoutScale_SYSCLK()     SET_REG_BIT(UR2TOCR, UR2TOCR_SCALE_MSK)
#define UART2_TimeoutScale_BRT()        CLR_REG_BIT(UR2TOCR, UR2TOCR_SCALE_MSK)

#define UART2_SetTimeoutInterval(n)     UR2TOTL = BYTE0(n); \
                                        UR2TOTH = BYTE1(n); \
                                        UR2TOTE = BYTE2(n)

////////////////////////

#define S3CON_S3SM_MSK                  (BIT7 | BIT6)
#define UART3_SetMode(n)                MODIFY_REG(S3CON, S3CON_S3SM_MSK, ((n) << 6))
#define UART3_Mode0()                   UART3_SetMode(0)
#define UART3_Mode1()                   UART3_SetMode(1)
#define UART3_Mode2()                   UART3_SetMode(2)
#define UART3_Mode3()                   UART3_SetMode(3)

#define S3CON_S3REN_MSK                 BIT4
#define UART3_EnableRx()                SET_REG_BIT(S3CON, S3CON_S3REN_MSK)
#define UART3_DisableRx()               CLR_REG_BIT(S3CON, S3CON_S3REN_MSK)

#define S3CON_S3TB8_MSK                 BIT3
#define UART3_SetTB8(b)                 MODIFY_REG(S3CON, S3CON_S3TB8_MSK, ((b) << 3))

#define S3CON_S3RB8_MSK                 BIT2
#define UART3_ReadRB8()                 READ_REG_BIT(S3CON, S3CON_S3RB8_MSK)

#define UART3_SendData(d)               (S3BUF = (d))
#define UART3_ReadData()                (S3BUF)

#define S3CFG_S3M0X6_MSK                BIT5
#define UART3_Mode0BaudrateX6()         SET_REG_BIT(S3CFG, S3CFG_S3M0X6_MSK)

#define USART3CR2_PCEN_MSK              BIT2
#define USART3CR2_PS_MSK                BIT1
#define UART3_NoneParity()              CLR_REG_BIT(USART3CR2, USART3CR2_PCEN_MSK)
#define UART3_OddParity()               SET_REG_BIT(USART3CR2, USART3CR2_PCEN_MSK); \
                                        SET_REG_BIT(USART3CR2, USART3CR2_PS_MSK)
#define UART3_EvenParity()              SET_REG_BIT(USART3CR2, USART3CR2_PCEN_MSK); \
                                        CLR_REG_BIT(USART3CR2, USART3CR2_PS_MSK)
#define UART3_MarkParity()              CLR_REG_BIT(USART3CR2, USART3CR2_PCEN_MSK); \
                                        UART3_SetTB8(1)
#define UART3_SpaceParity()             CLR_REG_BIT(USART3CR2, USART3CR2_PCEN_MSK); \
                                        UART3_SetTB8(0)

#define UR3TOCR_ENTO_MSK                BIT7
#define UART3_EnableTimeout()           SET_REG_BIT(UR3TOCR, UR3TOCR_ENTO_MSK)
#define UART3_DisableTimeout()          CLR_REG_BIT(UR3TOCR, UR3TOCR_ENTO_MSK)

#define UR3TOCR_SCALE_MSK               BIT5
#define UART3_TimeoutScale_SYSCLK()     SET_REG_BIT(UR3TOCR, UR3TOCR_SCALE_MSK)
#define UART3_TimeoutScale_BRT()        CLR_REG_BIT(UR3TOCR, UR3TOCR_SCALE_MSK)

#define UART3_SetTimeoutInterval(n)     UR3TOTL = BYTE0(n); \
                                        UR3TOTH = BYTE1(n); \
                                        UR3TOTE = BYTE2(n)

#define S3CFG_S3BRT_MSK                 BIT0
#define UART3_Timer2BRT()               CLR_REG_BIT(S3CFG, S3CFG_S3BRT_MSK)
#define UART3_Timer3BRT()               SET_REG_BIT(S3CFG, S3CFG_S3BRT_MSK)

////////////////////////

#define S4CON_S4SM_MSK                  (BIT7 | BIT6)
#define UART4_SetMode(n)                MODIFY_REG(S4CON, S4CON_S4SM_MSK, ((n) << 6))
#define UART4_Mode0()                   UART4_SetMode(0)
#define UART4_Mode1()                   UART4_SetMode(1)
#define UART4_Mode2()                   UART4_SetMode(2)
#define UART4_Mode3()                   UART4_SetMode(3)

#define S4CON_S4REN_MSK                 BIT4
#define UART4_EnableRx()                SET_REG_BIT(S4CON, S4CON_S4REN_MSK)
#define UART4_DisableRx()               CLR_REG_BIT(S4CON, S4CON_S4REN_MSK)

#define S4CON_S4TB8_MSK                 BIT3
#define UART4_SetTB8(b)                 MODIFY_REG(S4CON, S4CON_S4TB8_MSK, ((b) << 3))

#define S4CON_S4RB8_MSK                 BIT2
#define UART4_ReadRB8()                 READ_REG_BIT(S4CON, S4CON_S4RB8_MSK)

#define UART4_SendData(d)               (S4BUF = (d))
#define UART4_ReadData()                (S4BUF)

#define S4CFG_S4M0X6_MSK                BIT5
#define UART4_Mode0BaudrateX6()         SET_REG_BIT(S4CFG, S4CFG_S4M0X6_MSK)

#define USART4CR2_PCEN_MSK              BIT2
#define USART4CR2_PS_MSK                BIT1
#define UART4_NoneParity()              CLR_REG_BIT(USART4CR2, USART4CR2_PCEN_MSK)
#define UART4_OddParity()               SET_REG_BIT(USART4CR2, USART4CR2_PCEN_MSK); \
                                        SET_REG_BIT(USART4CR2, USART4CR2_PS_MSK)
#define UART4_EvenParity()              SET_REG_BIT(USART4CR2, USART4CR2_PCEN_MSK); \
                                        CLR_REG_BIT(USART4CR2, USART4CR2_PS_MSK)
#define UART4_MarkParity()              CLR_REG_BIT(USART4CR2, USART4CR2_PCEN_MSK); \
                                        UART4_SetTB8(1)
#define UART4_SpaceParity()             CLR_REG_BIT(USART4CR2, USART4CR2_PCEN_MSK); \
                                        UART4_SetTB8(0)

#define UR4TOCR_ENTO_MSK                BIT7
#define UART4_EnableTimeout()           SET_REG_BIT(UR4TOCR, UR4TOCR_ENTO_MSK)
#define UART4_DisableTimeout()          CLR_REG_BIT(UR4TOCR, UR4TOCR_ENTO_MSK)

#define UR4TOCR_SCALE_MSK               BIT5
#define UART4_TimeoutScale_SYSCLK()     SET_REG_BIT(UR4TOCR, UR4TOCR_SCALE_MSK)
#define UART4_TimeoutScale_BRT()        CLR_REG_BIT(UR4TOCR, UR4TOCR_SCALE_MSK)

#define UART4_SetTimeoutInterval(n)     UR4TOTL = BYTE0(n); \
                                        UR4TOTH = BYTE1(n); \
                                        UR4TOTE = BYTE2(n)

#define S4CFG_S4BRT_MSK                 BIT0
#define UART4_Timer2BRT()               CLR_REG_BIT(S4CFG, S4CFG_S4BRT_MSK)
#define UART4_Timer4BRT()               SET_REG_BIT(S4CFG, S4CFG_S4BRT_MSK)

////////////////////////

#define S5CON_S5SM_MSK                  (BIT7 | BIT6)
#define UART5_SetMode(n)                MODIFY_REG(S5CON, S5CON_S5SM_MSK, ((n) << 6))
#define UART5_Mode0()                   UART5_SetMode(0)
#define UART5_Mode1()                   UART5_SetMode(1)
#define UART5_Mode2()                   UART5_SetMode(2)
#define UART5_Mode3()                   UART5_SetMode(3)

#define S5CON_S5REN_MSK                 BIT4
#define UART5_EnableRx()                SET_REG_BIT(S5CON, S5CON_S5REN_MSK)
#define UART5_DisableRx()               CLR_REG_BIT(S5CON, S5CON_S5REN_MSK)

#define S5CON_S5TB8_MSK                 BIT3
#define UART5_SetTB8(b)                 MODIFY_REG(S5CON, S5CON_S5TB8_MSK, ((b) << 3))

#define S5CON_S5RB8_MSK                 BIT2
#define UART5_ReadRB8()                 READ_REG_BIT(S5CON, S5CON_S5RB8_MSK)

#define UART5_SendData(d)               (S5BUF = (d))
#define UART5_ReadData()                (S5BUF)

#define S5CFG_S5M0X6_MSK                BIT5
#define UART5_Mode0BaudrateX6()         SET_REG_BIT(S5CFG, S5CFG_S5M0X6_MSK)

#define USART5CR2_PCEN_MSK              BIT2
#define USART5CR2_PS_MSK                BIT1
#define UART5_NoneParity()              CLR_REG_BIT(USART5CR2, USART5CR2_PCEN_MSK)
#define UART5_OddParity()               SET_REG_BIT(USART5CR2, USART5CR2_PCEN_MSK); \
                                        SET_REG_BIT(USART5CR2, USART5CR2_PS_MSK)
#define UART5_EvenParity()              SET_REG_BIT(USART5CR2, USART5CR2_PCEN_MSK); \
                                        CLR_REG_BIT(USART5CR2, USART5CR2_PS_MSK)
#define UART5_MarkParity()              CLR_REG_BIT(USART5CR2, USART5CR2_PCEN_MSK); \
                                        UART5_SetTB8(1)
#define UART5_SpaceParity()             CLR_REG_BIT(USART5CR2, USART5CR2_PCEN_MSK); \
                                        UART5_SetTB8(0)

#define UR5TOCR_ENTO_MSK                BIT7
#define UART5_EnableTimeout()           SET_REG_BIT(UR5TOCR, UR5TOCR_ENTO_MSK)
#define UART5_DisableTimeout()          CLR_REG_BIT(UR5TOCR, UR5TOCR_ENTO_MSK)

#define UR5TOCR_SCALE_MSK               BIT5
#define UART5_TimeoutScale_SYSCLK()     SET_REG_BIT(UR5TOCR, UR5TOCR_SCALE_MSK)
#define UART5_TimeoutScale_BRT()        CLR_REG_BIT(UR5TOCR, UR5TOCR_SCALE_MSK)

#define UART5_SetTimeoutInterval(n)     UR5TOTL = BYTE0(n); \
                                        UR5TOTH = BYTE1(n); \
                                        UR5TOTE = BYTE2(n)

#define S5CFG_S5BRT_MSK                 BIT0
#define UART5_Timer2BRT()               CLR_REG_BIT(S5CFG, S5CFG_S5BRT_MSK)
#define UART5_Timer5BRT()               SET_REG_BIT(S5CFG, S5CFG_S5BRT_MSK)

////////////////////////

#define S6CON_S6SM_MSK                  (BIT7 | BIT6)
#define UART6_SetMode(n)                MODIFY_REG(S6CON, S6CON_S6SM_MSK, ((n) << 6))
#define UART6_Mode0()                   UART6_SetMode(0)
#define UART6_Mode1()                   UART6_SetMode(1)
#define UART6_Mode2()                   UART6_SetMode(2)
#define UART6_Mode3()                   UART6_SetMode(3)

#define S6CON_S6REN_MSK                 BIT4
#define UART6_EnableRx()                SET_REG_BIT(S6CON, S6CON_S6REN_MSK)
#define UART6_DisableRx()               CLR_REG_BIT(S6CON, S6CON_S6REN_MSK)

#define S6CON_S6TB8_MSK                 BIT3
#define UART6_SetTB8(b)                 MODIFY_REG(S6CON, S6CON_S6TB8_MSK, ((b) << 3))

#define S6CON_S6RB8_MSK                 BIT2
#define UART6_ReadRB8()                 READ_REG_BIT(S6CON, S6CON_S6RB8_MSK)

#define UART6_SendData(d)               (S6BUF = (d))
#define UART6_ReadData()                (S6BUF)

#define S6CFG_S6M0X6_MSK                BIT5
#define UART6_Mode0BaudrateX6()         SET_REG_BIT(S6CFG, S6CFG_S6M0X6_MSK)

#define USART6CR2_PCEN_MSK              BIT2
#define USART6CR2_PS_MSK                BIT1
#define UART6_NoneParity()              CLR_REG_BIT(USART6CR2, USART6CR2_PCEN_MSK)
#define UART6_OddParity()               SET_REG_BIT(USART6CR2, USART6CR2_PCEN_MSK); \
                                        SET_REG_BIT(USART6CR2, USART6CR2_PS_MSK)
#define UART6_EvenParity()              SET_REG_BIT(USART6CR2, USART6CR2_PCEN_MSK); \
                                        CLR_REG_BIT(USART6CR2, USART6CR2_PS_MSK)
#define UART6_MarkParity()              CLR_REG_BIT(USART6CR2, USART6CR2_PCEN_MSK); \
                                        UART6_SetTB8(1)
#define UART6_SpaceParity()             CLR_REG_BIT(USART6CR2, USART6CR2_PCEN_MSK); \
                                        UART6_SetTB8(0)

#define UR6TOCR_ENTO_MSK                BIT7
#define UART6_EnableTimeout()           SET_REG_BIT(UR6TOCR, UR6TOCR_ENTO_MSK)
#define UART6_DisableTimeout()          CLR_REG_BIT(UR6TOCR, UR6TOCR_ENTO_MSK)

#define UR6TOCR_SCALE_MSK               BIT5
#define UART6_TimeoutScale_SYSCLK()     SET_REG_BIT(UR6TOCR, UR6TOCR_SCALE_MSK)
#define UART6_TimeoutScale_BRT()        CLR_REG_BIT(UR6TOCR, UR6TOCR_SCALE_MSK)

#define UART6_SetTimeoutInterval(n)     UR6TOTL = BYTE0(n); \
                                        UR6TOTH = BYTE1(n); \
                                        UR6TOTE = BYTE2(n)

#define S6CFG_S6BRT_MSK                 BIT0
#define UART6_Timer2BRT()               CLR_REG_BIT(S6CFG, S6CFG_S6BRT_MSK)
#define UART6_Timer6BRT()               SET_REG_BIT(S6CFG, S6CFG_S6BRT_MSK)

////////////////////////

#define S7CON_S7SM_MSK                  (BIT7 | BIT6)
#define UART7_SetMode(n)                MODIFY_REG(S7CON, S7CON_S7SM_MSK, ((n) << 6))
#define UART7_Mode0()                   UART7_SetMode(0)
#define UART7_Mode1()                   UART7_SetMode(1)
#define UART7_Mode2()                   UART7_SetMode(2)
#define UART7_Mode3()                   UART7_SetMode(3)

#define S7CON_S7REN_MSK                 BIT4
#define UART7_EnableRx()                SET_REG_BIT(S7CON, S7CON_S7REN_MSK)
#define UART7_DisableRx()               CLR_REG_BIT(S7CON, S7CON_S7REN_MSK)

#define S7CON_S7TB8_MSK                 BIT3
#define UART7_SetTB8(b)                 MODIFY_REG(S7CON, S7CON_S7TB8_MSK, ((b) << 3))

#define S7CON_S7RB8_MSK                 BIT2
#define UART7_ReadRB8()                 READ_REG_BIT(S7CON, S7CON_S7RB8_MSK)

#define UART7_SendData(d)               (S7BUF = (d))
#define UART7_ReadData()                (S7BUF)

#define S7CFG_S7M0X6_MSK                BIT5
#define UART7_Mode0BaudrateX6()         SET_REG_BIT(S7CFG, S7CFG_S7M0X6_MSK)

#define USART7CR2_PCEN_MSK              BIT2
#define USART7CR2_PS_MSK                BIT1
#define UART7_NoneParity()              CLR_REG_BIT(USART7CR2, USART7CR2_PCEN_MSK)
#define UART7_OddParity()               SET_REG_BIT(USART7CR2, USART7CR2_PCEN_MSK); \
                                        SET_REG_BIT(USART7CR2, USART7CR2_PS_MSK)
#define UART7_EvenParity()              SET_REG_BIT(USART7CR2, USART7CR2_PCEN_MSK); \
                                        CLR_REG_BIT(USART7CR2, USART7CR2_PS_MSK)
#define UART7_MarkParity()              CLR_REG_BIT(USART7CR2, USART7CR2_PCEN_MSK); \
                                        UART7_SetTB8(1)
#define UART7_SpaceParity()             CLR_REG_BIT(USART7CR2, USART7CR2_PCEN_MSK); \
                                        UART7_SetTB8(0)

#define UR7TOCR_ENTO_MSK                BIT7
#define UART7_EnableTimeout()           SET_REG_BIT(UR7TOCR, UR7TOCR_ENTO_MSK)
#define UART7_DisableTimeout()          CLR_REG_BIT(UR7TOCR, UR7TOCR_ENTO_MSK)

#define UR7TOCR_SCALE_MSK               BIT5
#define UART7_TimeoutScale_SYSCLK()     SET_REG_BIT(UR7TOCR, UR7TOCR_SCALE_MSK)
#define UART7_TimeoutScale_BRT()        CLR_REG_BIT(UR7TOCR, UR7TOCR_SCALE_MSK)

#define UART7_SetTimeoutInterval(n)     UR7TOTL = BYTE0(n); \
                                        UR7TOTH = BYTE1(n); \
                                        UR7TOTE = BYTE2(n)

#define S7CFG_S7BRT_MSK                 BIT0
#define UART7_Timer2BRT()               CLR_REG_BIT(S7CFG, S7CFG_S7BRT_MSK)
#define UART7_Timer7BRT()               SET_REG_BIT(S7CFG, S7CFG_S7BRT_MSK)

////////////////////////

#define S8CON_S8SM_MSK                  (BIT7 | BIT6)
#define UART8_SetMode(n)                MODIFY_REG(S8CON, S8CON_S8SM_MSK, ((n) << 6))
#define UART8_Mode0()                   UART8_SetMode(0)
#define UART8_Mode1()                   UART8_SetMode(1)
#define UART8_Mode2()                   UART8_SetMode(2)
#define UART8_Mode3()                   UART8_SetMode(3)

#define S8CON_S8REN_MSK                 BIT4
#define UART8_EnableRx()                SET_REG_BIT(S8CON, S8CON_S8REN_MSK)
#define UART8_DisableRx()               CLR_REG_BIT(S8CON, S8CON_S8REN_MSK)

#define S8CON_S8TB8_MSK                 BIT3
#define UART8_SetTB8(b)                 MODIFY_REG(S8CON, S8CON_S8TB8_MSK, ((b) << 3))

#define S8CON_S8RB8_MSK                 BIT2
#define UART8_ReadRB8()                 READ_REG_BIT(S8CON, S8CON_S8RB8_MSK)

#define UART8_SendData(d)               (S8BUF = (d))
#define UART8_ReadData()                (S8BUF)

#define S8CFG_S8M0X6_MSK                BIT5
#define UART8_Mode0BaudrateX6()         SET_REG_BIT(S8CFG, S8CFG_S8M0X6_MSK)

#define USART8CR2_PCEN_MSK              BIT2
#define USART8CR2_PS_MSK                BIT1
#define UART8_NoneParity()              CLR_REG_BIT(USART8CR2, USART8CR2_PCEN_MSK)
#define UART8_OddParity()               SET_REG_BIT(USART8CR2, USART8CR2_PCEN_MSK); \
                                        SET_REG_BIT(USART8CR2, USART8CR2_PS_MSK)
#define UART8_EvenParity()              SET_REG_BIT(USART8CR2, USART8CR2_PCEN_MSK); \
                                        CLR_REG_BIT(USART8CR2, USART8CR2_PS_MSK)
#define UART8_MarkParity()              CLR_REG_BIT(USART8CR2, USART8CR2_PCEN_MSK); \
                                        UART8_SetTB8(1)
#define UART8_SpaceParity()             CLR_REG_BIT(USART8CR2, USART8CR2_PCEN_MSK); \
                                        UART8_SetTB8(0)

#define UR8TOCR_ENTO_MSK                BIT7
#define UART8_EnableTimeout()           SET_REG_BIT(UR8TOCR, UR8TOCR_ENTO_MSK)
#define UART8_DisableTimeout()          CLR_REG_BIT(UR8TOCR, UR8TOCR_ENTO_MSK)

#define UR8TOCR_SCALE_MSK               BIT5
#define UART8_TimeoutScale_SYSCLK()     SET_REG_BIT(UR8TOCR, UR8TOCR_SCALE_MSK)
#define UART8_TimeoutScale_BRT()        CLR_REG_BIT(UR8TOCR, UR8TOCR_SCALE_MSK)

#define UART8_SetTimeoutInterval(n)     UR8TOTL = BYTE0(n); \
                                        UR8TOTH = BYTE1(n); \
                                        UR8TOTE = BYTE2(n)

#define S8CFG_S8BRT_MSK                 BIT0
#define UART8_Timer2BRT()               CLR_REG_BIT(S8CFG, S8CFG_S8BRT_MSK)
#define UART8_Timer8BRT()               SET_REG_BIT(S8CFG, S8CFG_S8BRT_MSK)

/////////////////////////////////////////////////

#define CMP1CR1_CMP1EN_MSK              BIT7
#define CMP1_Enable()                   SET_REG_BIT(CMP1_6P6N_CR1, CMP1CR1_CMP1EN_MSK)
#define CMP1_Disable()                  CLR_REG_BIT(CMP1_6P6N_CR1, CMP1CR1_CMP1EN_MSK)

#define CMP1CR1_CMP1OE_MSK              BIT1
#define CMP1_EnableOutput()             SET_REG_BIT(CMP1_6P6N_CR1, CMP1CR1_CMP1OE_MSK)
#define CMP1_DisableOutput()            CLR_REG_BIT(CMP1_6P6N_CR1, CMP1CR1_CMP1OE_MSK)

#define CMP1CR1_CMP1RES_MSK             BIT0
#define CMP1_ReadResult()               READ_REG_BIT(CMP1_6P6N_CR1, CMP1CR1_CMP1RES_MSK)

#define CMP1CR2_INVO_MSK                BIT7
#define CMP1_OutputInvert()             SET_REG_BIT(CMP1_6P6N_CR2, CMP1CR2_INVO_MSK)

#define CMP1CR2_DISFLT_MSK              BIT6
#define CMP1_EnableAnalogFilter()       CLR_REG_BIT(CMP1_6P6N_CR2, CMP1CR2_DISFLT_MSK)
#define CMP1_DisableAnalogFilter()      SET_REG_BIT(CMP1_6P6N_CR2, CMP1CR2_DISFLT_MSK)

#define CMP1CR2_LCDTY_MSK               (BIT5 | BIT4 | BIT_LN)
#define CMP1_SetDigitalFilter(n)        MODIFY_REG(CMP1_6P6N_CR2, CMP1CR2_LCDTY_MSK, ((n) << 0))

#define CMP1CR3_CHYS_MSK                (BIT7 | BIT6)
#define CMP1_SetHysteresis(n)           MODIFY_REG(CMP1_6P6N_CR3, CMP1CR3_CHYS_MSK, ((n) << 6))
#define CMP1_DisableHysteresis()        CMP1_SetHysteresis(0)
#define CMP1_SetHysteresis_10mV()       CMP1_SetHysteresis(1)
#define CMP1_SetHysteresis_20mV()       CMP1_SetHysteresis(2)
#define CMP1_SetHysteresis_30mV()       CMP1_SetHysteresis(3)

////////////////////////

#define CMP2CR1_CMP2EN_MSK              BIT7
#define CMP2_Enable()                   SET_REG_BIT(CMP2_6P6N_CR1, CMP2CR1_CMP2EN_MSK)
#define CMP2_Disable()                  CLR_REG_BIT(CMP2_6P6N_CR1, CMP2CR1_CMP2EN_MSK)

#define CMP2CR1_CMP2OE_MSK              BIT1
#define CMP2_EnableOutput()             SET_REG_BIT(CMP2_6P6N_CR1, CMP2CR1_CMP2OE_MSK)
#define CMP2_DisableOutput()            CLR_REG_BIT(CMP2_6P6N_CR1, CMP2CR1_CMP2OE_MSK)

#define CMP2CR1_CMP2RES_MSK             BIT0
#define CMP2_ReadResult()               READ_REG_BIT(CMP2_6P6N_CR1, CMP2CR1_CMP2RES_MSK)

#define CMP2CR2_INVO_MSK                BIT7
#define CMP2_OutputInvert()             SET_REG_BIT(CMP2_6P6N_CR2, CMP2CR2_INVO_MSK)

#define CMP2CR2_DISFLT_MSK              BIT6
#define CMP2_EnableAnalogFilter()       CLR_REG_BIT(CMP2_6P6N_CR2, CMP2CR2_DISFLT_MSK)
#define CMP2_DisableAnalogFilter()      SET_REG_BIT(CMP2_6P6N_CR2, CMP2CR2_DISFLT_MSK)

#define CMP2CR2_LCDTY_MSK               (BIT5 | BIT4 | BIT_LN)
#define CMP2_SetDigitalFilter(n)        MODIFY_REG(CMP2_6P6N_CR2, CMP2CR2_LCDTY_MSK, ((n) << 0))

#define CMP2CR3_CHYS_MSK                (BIT7 | BIT6)
#define CMP2_SetHysteresis(n)           MODIFY_REG(CMP2_6P6N_CR3, CMP2CR3_CHYS_MSK, ((n) << 6))
#define CMP2_DisableHysteresis()        CMP2_SetHysteresis(0)
#define CMP2_SetHysteresis_10mV()       CMP2_SetHysteresis(1)
#define CMP2_SetHysteresis_20mV()       CMP2_SetHysteresis(2)
#define CMP2_SetHysteresis_30mV()       CMP2_SetHysteresis(3)

////////////////////////

#define CMP3CR1_CMP3EN_MSK              BIT7
#define CMP3_Enable()                   SET_REG_BIT(CMP3_6P6N_CR1, CMP3CR1_CMP3EN_MSK)
#define CMP3_Disable()                  CLR_REG_BIT(CMP3_6P6N_CR1, CMP3CR1_CMP3EN_MSK)

#define CMP3CR1_CMP3OE_MSK              BIT1
#define CMP3_EnableOutput()             SET_REG_BIT(CMP3_6P6N_CR1, CMP3CR1_CMP3OE_MSK)
#define CMP3_DisableOutput()            CLR_REG_BIT(CMP3_6P6N_CR1, CMP3CR1_CMP3OE_MSK)

#define CMP3CR1_CMP3RES_MSK             BIT0
#define CMP3_ReadResult()               READ_REG_BIT(CMP3_6P6N_CR1, CMP3CR1_CMP3RES_MSK)

#define CMP3CR2_INVO_MSK                BIT7
#define CMP3_OutputInvert()             SET_REG_BIT(CMP3_6P6N_CR2, CMP3CR2_INVO_MSK)

#define CMP3CR2_DISFLT_MSK              BIT6
#define CMP3_EnableAnalogFilter()       CLR_REG_BIT(CMP3_6P6N_CR2, CMP3CR2_DISFLT_MSK)
#define CMP3_DisableAnalogFilter()      SET_REG_BIT(CMP3_6P6N_CR2, CMP3CR2_DISFLT_MSK)

#define CMP3CR2_LCDTY_MSK               (BIT5 | BIT4 | BIT_LN)
#define CMP3_SetDigitalFilter(n)        MODIFY_REG(CMP3_6P6N_CR2, CMP3CR2_LCDTY_MSK, ((n) << 0))

#define CMP3CR3_CHYS_MSK                (BIT7 | BIT6)
#define CMP3_SetHysteresis(n)           MODIFY_REG(CMP3_6P6N_CR3, CMP3CR3_CHYS_MSK, ((n) << 6))
#define CMP3_DisableHysteresis()        CMP3_SetHysteresis(0)
#define CMP3_SetHysteresis_10mV()       CMP3_SetHysteresis(1)
#define CMP3_SetHysteresis_20mV()       CMP3_SetHysteresis(2)
#define CMP3_SetHysteresis_30mV()       CMP3_SetHysteresis(3)

////////////////////////

#define CMP4CR1_CMP4EN_MSK              BIT7
#define CMP4_Enable()                   SET_REG_BIT(CMP4_6P6N_CR1, CMP4CR1_CMP4EN_MSK)
#define CMP4_Disable()                  CLR_REG_BIT(CMP4_6P6N_CR1, CMP4CR1_CMP4EN_MSK)

#define CMP4CR1_CMP4OE_MSK              BIT1
#define CMP4_EnableOutput()             SET_REG_BIT(CMP4_6P6N_CR1, CMP4CR1_CMP4OE_MSK)
#define CMP4_DisableOutput()            CLR_REG_BIT(CMP4_6P6N_CR1, CMP4CR1_CMP4OE_MSK)

#define CMP4CR1_CMP4RES_MSK             BIT0
#define CMP4_ReadResult()               READ_REG_BIT(CMP4_6P6N_CR1, CMP4CR1_CMP4RES_MSK)

#define CMP4CR2_INVO_MSK                BIT7
#define CMP4_OutputInvert()             SET_REG_BIT(CMP4_6P6N_CR2, CMP4CR2_INVO_MSK)

#define CMP4CR2_DISFLT_MSK              BIT6
#define CMP4_EnableAnalogFilter()       CLR_REG_BIT(CMP4_6P6N_CR2, CMP4CR2_DISFLT_MSK)
#define CMP4_DisableAnalogFilter()      SET_REG_BIT(CMP4_6P6N_CR2, CMP4CR2_DISFLT_MSK)

#define CMP4CR2_LCDTY_MSK               (BIT5 | BIT4 | BIT_LN)
#define CMP4_SetDigitalFilter(n)        MODIFY_REG(CMP4_6P6N_CR2, CMP4CR2_LCDTY_MSK, ((n) << 0))

#define CMP4CR3_CHYS_MSK                (BIT7 | BIT6)
#define CMP4_SetHysteresis(n)           MODIFY_REG(CMP4_6P6N_CR3, CMP4CR3_CHYS_MSK, ((n) << 6))
#define CMP4_DisableHysteresis()        CMP4_SetHysteresis(0)
#define CMP4_SetHysteresis_10mV()       CMP4_SetHysteresis(1)
#define CMP4_SetHysteresis_20mV()       CMP4_SetHysteresis(2)
#define CMP4_SetHysteresis_30mV()       CMP4_SetHysteresis(3)

/////////////////////////////////////////////////

#define IAPCON_IAPEN_MSK                BIT7
#define IAP_Enable()                    SET_REG_BIT(IAP_CONTR, IAPCON_IAPEN_MSK)
#define IAP_Disable()                   CLR_REG_BIT(IAP_CONTR, IAPCON_IAPEN_MSK)

#define IAP_SetData(d)                  (IAP_DATA = (d))
#define IAP_ReadData()                  (IAP_DATA)

#define IAP_SetDataX(n, d)              (IAP_XDATA[n] = (d))
#define IAP_ReadDataX(n)                (IAP_XDATA[n])

#define IAP_SetAddress(n)               IAP_ADDRL = BYTE0(n); \
                                        IAP_ADDRH = BYTE1(n); \
                                        IAP_ADDRE = BYTE2(n)

#define IAP_Trigger()                   IAP_TRIG = 0x5a; \
                                        IAP_TRIG = 0xa5; \
                                        _nop_();         \
                                        _nop_();         \
                                        _nop_();         \
                                        _nop_()

#define IAP_Idle()                      IAP_CMD = 0
#define IAP_TriggerRead()               IAP_CMD = 1; IAP_Trigger()
#define IAP_TriggerProgram()            IAP_CMD = 2; IAP_Trigger()
#define IAP_TriggerErase()              IAP_CMD = 3; IAP_Trigger()

#define IAP_TriggerRead4Bytes()         IAP_CMD = 5; IAP_Trigger()
#define IAP_TriggerRead8Bytes()         IAP_CMD = 6; IAP_Trigger()
#define IAP_TriggerRead16Bytes()        IAP_CMD = 7; IAP_Trigger()
#define IAP_TriggerProgram4Bytes()      IAP_CMD = 13; IAP_Trigger()
#define IAP_TriggerProgram8Bytes()      IAP_CMD = 14; IAP_Trigger()
#define IAP_TriggerProgram16Bytes()     IAP_CMD = 15; IAP_Trigger()

#define IAP_SetTimeBase()               IAP_TPS = ((SYSCLK) / 1000000)

#define IAPCON_FAIL_MSK                 BIT4
#define IAP_CheckErrorFlag()            READ_REG_BIT(IAP_CONTR, IAPCON_FAIL_MSK)
#define IAP_ClearErrorFlag()            CLR_REG_BIT(IAP_CONTR, IAPCON_FAIL_MSK)

/////////////////////////////////////////////////

#define ADCCONTR_ADCPOWER_MSK           BIT7
#define ADC1_Enable()                   SET_REG_BIT(ADC_CONTR, ADCCONTR_ADCPOWER_MSK)
#define ADC1_Disable()                  CLR_REG_BIT(ADC_CONTR, ADCCONTR_ADCPOWER_MSK)

#define ADC1_ReadResult()               MAKEWORD(ADC_RESL, ADC_RES)

#define ADCCONTR_ADCSTART_MSK           BIT6
#define ADC1_Start()                    SET_REG_BIT(ADC_CONTR, ADCCONTR_ADCSTART_MSK)

#define ADCCONTR_ADCCHS_MSK             (BIT_LN)
#define ADC1_ActiveChannel(n)           MODIFY_REG(ADC_CONTR, ADCCONTR_ADCCHS_MSK, ((n) << 0))

#define ADCCONTR_ADCEPWMT_MSK           BIT4
#define ADC1_EnablePWMTrig()            SET_REG_BIT(ADC_CONTR, ADCCONTR_ADCEPWMT_MSK)
#define ADC1_DisablePWMTrig()           CLR_REG_BIT(ADC_CONTR, ADCCONTR_ADCEPWMT_MSK)

#define ADCCFG_RESFMT_MSK               BIT5
#define ADC1_ResultLeftAlign()          CLR_REG_BIT(ADCCFG, ADCCFG_RESFMT_MSK)
#define ADC1_ResultRightAlign()         SET_REG_BIT(ADCCFG, ADCCFG_RESFMT_MSK)

#define ADCCFG_SPEED_MSK                (BIT_LN)
#define ADC1_SetClockDivider(n)         MODIFY_REG(ADCCFG, ADCCFG_SPEED_MSK, ((n) << 0))

#define ADCEXCFG_ETRE_MSK               BIT5
#define ADC1_EnableETR()                SET_REG_BIT(ADCEXCFG, ADCEXCFG_ETRE_MSK)
#define ADC1_DisableETR()               CLR_REG_BIT(ADCEXCFG, ADCEXCFG_ETRE_MSK)

#define ADCEXCFG_ETRP_MSK               BIT4
#define ADC1_ETRRising()                CLR_REG_BIT(ADCEXCFG, ADCEXCFG_ETRP_MSK)
#define ADC1_ETRFalling()               SET_REG_BIT(ADCEXCFG, ADCEXCFG_ETRP_MSK)

#define ADCEXCFG_CVT_MSK                (BIT2 | BIT1 | BIT0)
#define ADC1_SetRepeatTimes(n)          MODIFY_REG(ADCEXCFG, ADCEXCFG_CVT_MSK, ((n) << 0))

#define ADC1_DisableRepeatConv()        ADC1_SetRepeatTimes(0)
#define ADC1_SetRepeat2Times()          ADC1_SetRepeatTimes(4)
#define ADC1_SetRepeat4Times()          ADC1_SetRepeatTimes(5)
#define ADC1_SetRepeat8Times()          ADC1_SetRepeatTimes(6)
#define ADC1_SetRepeat16Times()         ADC1_SetRepeatTimes(7)

#define ADCTIM_CSSETUP_MSK              BIT7
#define ADCTIM_CSHOLD_MSK               (BIT6 | BIT5)
#define ADCTIM_SMPDUTY_MSK              (BIT4 | BIT_LN)
#define ADC1_SetCSSetupCycles(n)        MODIFY_REG(ADCTIM, ADCTIM_CSSETUP_MSK, (((n) - 1) << 7))
#define ADC1_SetCSHoldCycles(n)         MODIFY_REG(ADCTIM, ADCTIM_CSHOLD_MSK, (((n) - 1) << 5))
#define ADC1_SetSampleDutyCycles(n)     MODIFY_REG(ADCTIM, ADCTIM_SMPDUTY_MSK, (((n) - 1) << 0))

#define ADCEXCFG2_TRIGON_MSK            BIT7
#define ADC1_ADC2_IndependMode()        CLR_REG_BIT(ADCEXCFG2, ADCEXCFG2_TRIGON_MSK)
#define ADC1_ADC2_LinkageMode()         SET_REG_BIT(ADCEXCFG2, ADCEXCFG2_TRIGON_MSK)

#define ADCEXCFG2_PWMCFG_MSK            (BIT5 | BIT4)
#define ADC1_TriggerMode(n)             MODIFY_REG(ADCEXCFG2, ADCEXCFG2_PWMCFG_MSK, ((n) << 4))
#define ADC1_TriggerDisable()           ADC1_TriggerMode(0)
#define ADC1_RisingTrigger()            ADC1_TriggerMode(1)
#define ADC1_FallingTrigger()           ADC1_TriggerMode(2)
#define ADC1_EdgeTrigger()              ADC1_TriggerMode(3)

#define ADCEXCFG2_TRIGSEL_MSK           (BIT_LN)
#define ADC1_TriggerSel(n)              MODIFY_REG(ADCEXCFG2, ADCEXCFG2_TRIGSEL_MSK, ((n) << 0))
#define ADC1_PWMATrgoTrigger()          ADC1_TriggerSel(0)
#define ADC1_PWMCTrgoTrigger()          ADC1_TriggerSel(1)
#define ADC1_PWMETrgoTrigger()          ADC1_TriggerSel(2)
#define ADC1_PWMATrgo2Trigger()         ADC1_TriggerSel(3)
#define ADC1_PWMCTrgo2Trigger()         ADC1_TriggerSel(4)
#define ADC1_PWMETrgo2Trigger()         ADC1_TriggerSel(5)
#define ADC1_PWMBTrgoTrigger()          ADC1_TriggerSel(6)
#define ADC1_PWMDTrgoTrigger()          ADC1_TriggerSel(7)
#define ADC1_PWMFTrgoTrigger()          ADC1_TriggerSel(8)
#define ADC1_AlwaysTrigger()            ADC1_TriggerSel(9)
#define ADC1_NoneTrigger()              ADC1_TriggerSel(10)
#define ADC1_T17Trigger()               ADC1_TriggerSel(12)
#define ADC1_T18Trigger()               ADC1_TriggerSel(13)
#define ADC1_T17PhaseTrigger()          ADC1_TriggerSel(14)
#define ADC1_T18PhaseTrigger()          ADC1_TriggerSel(15)

////////////////////////

#define ADC2CONTR_ADC2POWER_MSK         BIT7
#define ADC2_Enable()                   SET_REG_BIT(ADC2_CONTR, ADC2CONTR_ADC2POWER_MSK)
#define ADC2_Disable()                  CLR_REG_BIT(ADC2_CONTR, ADC2CONTR_ADC2POWER_MSK)

#define ADC2_ReadResult()               MAKEWORD(ADC2_RESL, ADC2_RES)

#define ADC2CONTR_ADC2START_MSK         BIT6
#define ADC2_Start()                    SET_REG_BIT(ADC2_CONTR, ADC2CONTR_ADC2START_MSK)

#define ADC2CONTR_ADC2CHS_MSK           (BIT_LN)
#define ADC2_ActiveChannel(n)           MODIFY_REG(ADC2_CONTR, ADC2CONTR_ADC2CHS_MSK, ((n) << 0))

#define ADC2CONTR_ADC2EPWMT_MSK         BIT4
#define ADC2_EnablePWMTrig()            SET_REG_BIT(ADC2_CONTR, ADC2CONTR_ADC2EPWMT_MSK)
#define ADC2_DisablePWMTrig()           CLR_REG_BIT(ADC2_CONTR, ADC2CONTR_ADC2EPWMT_MSK)

#define ADC2CFG_RESFMT_MSK              BIT5
#define ADC2_ResultLeftAlign()          CLR_REG_BIT(ADC2CFG, ADC2CFG_RESFMT_MSK)
#define ADC2_ResultRightAlign()         SET_REG_BIT(ADC2CFG, ADC2CFG_RESFMT_MSK)

#define ADC2CFG_SPEED_MSK               (BIT_LN)
#define ADC2_SetClockDivider(n)         MODIFY_REG(ADC2CFG, ADC2CFG_SPEED_MSK, ((n) << 0))

#define ADC2EXCFG_ETRE_MSK              BIT5
#define ADC2_EnableETR()                SET_REG_BIT(ADC2EXCFG, ADC2EXCFG_ETRE_MSK)
#define ADC2_DisableETR()               CLR_REG_BIT(ADC2EXCFG, ADC2EXCFG_ETRE_MSK)

#define ADC2EXCFG_ETRP_MSK              BIT4
#define ADC2_ETRRising()                CLR_REG_BIT(ADC2EXCFG, ADC2EXCFG_ETRP_MSK)
#define ADC2_ETRFalling()               SET_REG_BIT(ADC2EXCFG, ADC2EXCFG_ETRP_MSK)

#define ADC2EXCFG_CVT_MSK               (BIT2 | BIT1 | BIT0)
#define ADC2_SetRepeatTimes(n)          MODIFY_REG(ADC2EXCFG, ADC2EXCFG_CVT_MSK, ((n) << 0))

#define ADC2_DisableRepeatConv()        ADC2_SetRepeatTimes(0)
#define ADC2_SetRepeat2Times()          ADC2_SetRepeatTimes(4)
#define ADC2_SetRepeat4Times()          ADC2_SetRepeatTimes(5)
#define ADC2_SetRepeat8Times()          ADC2_SetRepeatTimes(6)
#define ADC2_SetRepeat16Times()         ADC2_SetRepeatTimes(7)

#define ADC2TIM_CSSETUP_MSK             BIT7
#define ADC2TIM_CSHOLD_MSK              (BIT6 | BIT5)
#define ADC2TIM_SMPDUTY_MSK             (BIT4 | BIT_LN)
#define ADC2_SetCSSetupCycles(n)        MODIFY_REG(ADC2TIM, ADC2TIM_CSSETUP_MSK, (((n) - 1) << 7))
#define ADC2_SetCSHoldCycles(n)         MODIFY_REG(ADC2TIM, ADC2TIM_CSHOLD_MSK, (((n) - 1) << 5))
#define ADC2_SetSampleDutyCycles(n)     MODIFY_REG(ADC2TIM, ADC2TIM_SMPDUTY_MSK, (((n) - 1) << 0))

#define ADC2EXCFG2_PWMCFG_MSK           (BIT5 | BIT4)
#define ADC2_TriggerMode(n)             MODIFY_REG(ADC2EXCFG2, ADC2EXCFG2_PWMCFG_MSK, ((n) << 4))
#define ADC2_TriggerDisable()           ADC2_TriggerMode(0)
#define ADC2_RisingTrigger()            ADC2_TriggerMode(1)
#define ADC2_FallingTrigger()           ADC2_TriggerMode(2)
#define ADC2_EdgeTrigger()              ADC2_TriggerMode(3)

#define ADC2EXCFG2_TRIGSEL_MSK          (BIT_LN)
#define ADC2_TriggerSel(n)              MODIFY_REG(ADC2EXCFG2, ADC2EXCFG2_TRIGSEL_MSK, ((n) << 0))
#define ADC2_PWMATrgoTrigger()          ADC2_TriggerSel(0)
#define ADC2_PWMCTrgoTrigger()          ADC2_TriggerSel(1)
#define ADC2_PWMETrgoTrigger()          ADC2_TriggerSel(2)
#define ADC2_PWMATrgo2Trigger()         ADC2_TriggerSel(3)
#define ADC2_PWMCTrgo2Trigger()         ADC2_TriggerSel(4)
#define ADC2_PWMETrgo2Trigger()         ADC2_TriggerSel(5)
#define ADC2_PWMBTrgoTrigger()          ADC2_TriggerSel(6)
#define ADC2_PWMDTrgoTrigger()          ADC2_TriggerSel(7)
#define ADC2_PWMFTrgoTrigger()          ADC2_TriggerSel(8)
#define ADC2_AlwaysTrigger()            ADC2_TriggerSel(9)
#define ADC2_NoneTrigger()              ADC2_TriggerSel(10)
#define ADC2_T17Trigger()               ADC2_TriggerSel(12)
#define ADC2_T18Trigger()               ADC2_TriggerSel(13)
#define ADC2_T17PhaseTrigger()          ADC2_TriggerSel(14)
#define ADC2_T18PhaseTrigger()          ADC2_TriggerSel(15)

/////////////////////////////////////////////////

#define DAC1CR_DAC1EN_MSK               BIT0
#define DAC1_Enable()                   SET_REG_BIT(DAC1_CR, DAC1CR_DAC1EN_MSK)
#define DAC1_Disable()                  CLR_REG_BIT(DAC1_CR, DAC1CR_DAC1EN_MSK)

#define DAC1CR_TRIGSEL_MSK              (BIT5 | BIT4)
#define DAC1_TriggerSel(n)              MODIFY_REG(DAC1_CR, DAC1CR_TRIGSEL_MSK, ((n) << 4))
#define DAC1_SigngleTrigger()           DAC1_TriggerSel(0)
#define DAC1_T17Trigger()               DAC1_TriggerSel(1)
#define DAC1_T18Trigger()               DAC1_TriggerSel(2)
#define DAC1_AlwaysTrigger()            DAC1_TriggerSel(3)

#define DAC1CR_TRIGGER_MSK              BIT6
#define DAC1_Trigger()                  SET_REG_BIT(DAC1_CR, DAC1CR_TRIGGER_MSK)

#define DAC1CR_DMAEN_MSK                BIT7
#define DAC1_EnableDMA()                SET_REG_BIT(DAC1_CR, DAC1CR_DMAEN_MSK)
#define DAC1_DisableDMA()               CLR_REG_BIT(DAC1_CR, DAC1CR_DMAEN_MSK)

#define DAC1STA_BUSY_MSK                BIT7
#define DAC1_CheckBusy()                READ_REG_BIT(DAC1_STA, DAC1STA_BUSY_MSK)

#define DAC1_SetValue(n)                (DAC1_DATH = HIBYTE(n), DAC1_DATL = LOBYTE(n))
#define DAC1_SetClockDivider(n)         (DAC1_DIVH = HIBYTE(n), DAC1_DIVL = LOBYTE(n))

////////////////////////

#define DAC2CR_DAC2EN_MSK               BIT0
#define DAC2_Enable()                   SET_REG_BIT(DAC2_CR, DAC2CR_DAC2EN_MSK)
#define DAC2_Disable()                  CLR_REG_BIT(DAC2_CR, DAC2CR_DAC2EN_MSK)

#define DAC2CR_TRIGSEL_MSK              (BIT5 | BIT4)
#define DAC2_TriggerSel(n)              MODIFY_REG(DAC2_CR, DAC2CR_TRIGSEL_MSK, ((n) << 4))
#define DAC2_SigngleTrigger()           DAC2_TriggerSel(0)
#define DAC2_T17Trigger()               DAC2_TriggerSel(1)
#define DAC2_T18Trigger()               DAC2_TriggerSel(2)
#define DAC2_AlwaysTrigger()            DAC2_TriggerSel(3)

#define DAC2CR_TRIGGER_MSK              BIT6
#define DAC2_Trigger()                  SET_REG_BIT(DAC2_CR, DAC2CR_TRIGGER_MSK)

#define DAC2CR_DMAEN_MSK                BIT7
#define DAC2_EnableDMA()                SET_REG_BIT(DAC2_CR, DAC2CR_DMAEN_MSK)
#define DAC2_DisableDMA()               CLR_REG_BIT(DAC2_CR, DAC2CR_DMAEN_MSK)

#define DAC2STA_BUSY_MSK                BIT7
#define DAC2_CheckBusy()                READ_REG_BIT(DAC2_STA, DAC2STA_BUSY_MSK)

#define DAC2_SetValue(n)                (DAC2_DATH = HIBYTE(n), DAC2_DATL = LOBYTE(n))
#define DAC2_SetClockDivider(n)         (DAC2_DIVH = HIBYTE(n), DAC2_DIVL = LOBYTE(n))

/////////////////////////////////////////////////

#define PGA1CR2_PD_MSK                  BIT0
#define PGA1_Enable()                   CLR_REG_BIT(PGA1_CR2, PGA1CR2_PD_MSK)
#define PGA1_Disable()                  SET_REG_BIT(PGA1_CR2, PGA1CR2_PD_MSK)

#define PGA1CR1_MSEL_MSK                (BIT7 | BIT6)
#define PGA1_SetMode(n)                 MODIFY_REG(PGA1_CR1, PGA1CR1_MSEL_MSK, ((n) << 6))
#define PGA1_GeneralOPAMode()           PGA1_SetMode(0)
#define PGA1_BufferMode()               PGA1_SetMode(1)
#define PGA1_InvertPGAMode()            PGA1_SetMode(2)
#define PGA1_NonInvertPGAMode()         PGA1_SetMode(3)

#define PGA1CR2_OE_MSK                  BIT2
#define PGA1_EnableOutput()             SET_REG_BIT(PGA1_CR2, PGA1CR2_OE_MSK)
#define PGA1_DisableOutput()            CLR_REG_BIT(PGA1_CR2, PGA1CR2_OE_MSK)

#define PGA1CR2_IBS_MSK                 BIT1
#define PGA1_NormalBiasCurrent()        CLR_REG_BIT(PGA1_CR2, PGA1CR2_IBS_MSK)
#define PGA1_StrongBiasCurrent()        SET_REG_BIT(PGA1_CR2, PGA1CR2_IBS_MSK)

#define PGA1CR2_GSEL_MSK                (BIT6 | BIT5 | BIT4)
#define PGA1_SetGain(n)                 MODIFY_REG(PGA1_CR2, PGA1CR2_GSEL_MSK, ((n) << 4))

#define PGA1_DisableGain()              PGA1_SetGain(0)

#define PGA1_SetInvertGain1()           PGA1_SetGain(1)
#define PGA1_SetInvertGain2()           PGA1_SetGain(2)
#define PGA1_SetInvertGain4()           PGA1_SetGain(3)
#define PGA1_SetInvertGain8()           PGA1_SetGain(4)
#define PGA1_SetInvertGain16()          PGA1_SetGain(5)
#define PGA1_SetInvertGain32()          PGA1_SetGain(6)
#define PGA1_SetInvertGain48()          PGA1_SetGain(7)

#define PGA1_SetNonInvertGain2()        PGA1_SetGain(1)
#define PGA1_SetNonInvertGain3()        PGA1_SetGain(2)
#define PGA1_SetNonInvertGain5()        PGA1_SetGain(3)
#define PGA1_SetNonInvertGain9()        PGA1_SetGain(4)
#define PGA1_SetNonInvertGain17()       PGA1_SetGain(5)
#define PGA1_SetNonInvertGain33()       PGA1_SetGain(6)
#define PGA1_SetNonInvertGain49()       PGA1_SetGain(7)

////////////////////////

#define PGA2CR2_PD_MSK                  BIT0
#define PGA2_Enable()                   CLR_REG_BIT(PGA2_CR2, PGA2CR2_PD_MSK)
#define PGA2_Disable()                  SET_REG_BIT(PGA2_CR2, PGA2CR2_PD_MSK)

#define PGA2CR1_MSEL_MSK                (BIT7 | BIT6)
#define PGA2_SetMode(n)                 MODIFY_REG(PGA2_CR1, PGA2CR1_MSEL_MSK, ((n) << 6))
#define PGA2_GeneralOPAMode()           PGA2_SetMode(0)
#define PGA2_BufferMode()               PGA2_SetMode(1)
#define PGA2_InvertPGAMode()            PGA2_SetMode(2)
#define PGA2_NonInvertPGAMode()         PGA2_SetMode(3)

#define PGA2CR2_OE_MSK                  BIT2
#define PGA2_EnableOutput()             SET_REG_BIT(PGA2_CR2, PGA2CR2_OE_MSK)
#define PGA2_DisableOutput()            CLR_REG_BIT(PGA2_CR2, PGA2CR2_OE_MSK)

#define PGA2CR2_IBS_MSK                 BIT1
#define PGA2_NormalBiasCurrent()        CLR_REG_BIT(PGA2_CR2, PGA2CR2_IBS_MSK)
#define PGA2_StrongBiasCurrent()        SET_REG_BIT(PGA2_CR2, PGA2CR2_IBS_MSK)

#define PGA2CR2_GSEL_MSK                (BIT6 | BIT5 | BIT4)
#define PGA2_SetGain(n)                 MODIFY_REG(PGA2_CR2, PGA2CR2_GSEL_MSK, ((n) << 4))

#define PGA2_DisableGain()              PGA2_SetGain(0)

#define PGA2_SetInvertGain1()           PGA2_SetGain(1)
#define PGA2_SetInvertGain2()           PGA2_SetGain(2)
#define PGA2_SetInvertGain4()           PGA2_SetGain(3)
#define PGA2_SetInvertGain8()           PGA2_SetGain(4)
#define PGA2_SetInvertGain16()          PGA2_SetGain(5)
#define PGA2_SetInvertGain32()          PGA2_SetGain(6)
#define PGA2_SetInvertGain48()          PGA2_SetGain(7)

#define PGA2_SetNonInvertGain2()        PGA2_SetGain(1)
#define PGA2_SetNonInvertGain3()        PGA2_SetGain(2)
#define PGA2_SetNonInvertGain5()        PGA2_SetGain(3)
#define PGA2_SetNonInvertGain9()        PGA2_SetGain(4)
#define PGA2_SetNonInvertGain17()       PGA2_SetGain(5)
#define PGA2_SetNonInvertGain33()       PGA2_SetGain(6)
#define PGA2_SetNonInvertGain49()       PGA2_SetGain(7)

////////////////////////

#define PGA3CR2_PD_MSK                  BIT0
#define PGA3_Enable()                   CLR_REG_BIT(PGA3_CR2, PGA3CR2_PD_MSK)
#define PGA3_Disable()                  SET_REG_BIT(PGA3_CR2, PGA3CR2_PD_MSK)

#define PGA3CR1_MSEL_MSK                (BIT7 | BIT6)
#define PGA3_SetMode(n)                 MODIFY_REG(PGA3_CR1, PGA3CR1_MSEL_MSK, ((n) << 6))
#define PGA3_GeneralOPAMode()           PGA3_SetMode(0)
#define PGA3_BufferMode()               PGA3_SetMode(1)
#define PGA3_InvertPGAMode()            PGA3_SetMode(2)
#define PGA3_NonInvertPGAMode()         PGA3_SetMode(3)

#define PGA3CR2_OE_MSK                  BIT2
#define PGA3_EnableOutput()             SET_REG_BIT(PGA3_CR2, PGA3CR2_OE_MSK)
#define PGA3_DisableOutput()            CLR_REG_BIT(PGA3_CR2, PGA3CR2_OE_MSK)

#define PGA3CR2_IBS_MSK                 BIT1
#define PGA3_NormalBiasCurrent()        CLR_REG_BIT(PGA3_CR2, PGA3CR2_IBS_MSK)
#define PGA3_StrongBiasCurrent()        SET_REG_BIT(PGA3_CR2, PGA3CR2_IBS_MSK)

#define PGA3CR2_GSEL_MSK                (BIT6 | BIT5 | BIT4)
#define PGA3_SetGain(n)                 MODIFY_REG(PGA3_CR2, PGA3CR2_GSEL_MSK, ((n) << 4))

#define PGA3_DisableGain()              PGA3_SetGain(0)

#define PGA3_SetInvertGain1()           PGA3_SetGain(1)
#define PGA3_SetInvertGain2()           PGA3_SetGain(2)
#define PGA3_SetInvertGain4()           PGA3_SetGain(3)
#define PGA3_SetInvertGain8()           PGA3_SetGain(4)
#define PGA3_SetInvertGain16()          PGA3_SetGain(5)
#define PGA3_SetInvertGain32()          PGA3_SetGain(6)
#define PGA3_SetInvertGain48()          PGA3_SetGain(7)

#define PGA3_SetNonInvertGain2()        PGA3_SetGain(1)
#define PGA3_SetNonInvertGain3()        PGA3_SetGain(2)
#define PGA3_SetNonInvertGain5()        PGA3_SetGain(3)
#define PGA3_SetNonInvertGain9()        PGA3_SetGain(4)
#define PGA3_SetNonInvertGain17()       PGA3_SetGain(5)
#define PGA3_SetNonInvertGain33()       PGA3_SetGain(6)
#define PGA3_SetNonInvertGain49()       PGA3_SetGain(7)

////////////////////////

#define PGA4CR2_PD_MSK                  BIT0
#define PGA4_Enable()                   CLR_REG_BIT(PGA4_CR2, PGA4CR2_PD_MSK)
#define PGA4_Disable()                  SET_REG_BIT(PGA4_CR2, PGA4CR2_PD_MSK)

#define PGA4CR1_MSEL_MSK                (BIT7 | BIT6)
#define PGA4_SetMode(n)                 MODIFY_REG(PGA4_CR1, PGA4CR1_MSEL_MSK, ((n) << 6))
#define PGA4_GeneralOPAMode()           PGA4_SetMode(0)
#define PGA4_BufferMode()               PGA4_SetMode(1)
#define PGA4_InvertPGAMode()            PGA4_SetMode(2)
#define PGA4_NonInvertPGAMode()         PGA4_SetMode(3)

#define PGA4CR2_OE_MSK                  BIT2
#define PGA4_EnableOutput()             SET_REG_BIT(PGA4_CR2, PGA4CR2_OE_MSK)
#define PGA4_DisableOutput()            CLR_REG_BIT(PGA4_CR2, PGA4CR2_OE_MSK)

#define PGA4CR2_IBS_MSK                 BIT1
#define PGA4_NormalBiasCurrent()        CLR_REG_BIT(PGA4_CR2, PGA4CR2_IBS_MSK)
#define PGA4_StrongBiasCurrent()        SET_REG_BIT(PGA4_CR2, PGA4CR2_IBS_MSK)

#define PGA4CR2_GSEL_MSK                (BIT6 | BIT5 | BIT4)
#define PGA4_SetGain(n)                 MODIFY_REG(PGA4_CR2, PGA4CR2_GSEL_MSK, ((n) << 4))

#define PGA4_DisableGain()              PGA4_SetGain(0)

#define PGA4_SetInvertGain1()           PGA4_SetGain(1)
#define PGA4_SetInvertGain2()           PGA4_SetGain(2)
#define PGA4_SetInvertGain4()           PGA4_SetGain(3)
#define PGA4_SetInvertGain8()           PGA4_SetGain(4)
#define PGA4_SetInvertGain16()          PGA4_SetGain(5)
#define PGA4_SetInvertGain32()          PGA4_SetGain(6)
#define PGA4_SetInvertGain48()          PGA4_SetGain(7)

#define PGA4_SetNonInvertGain2()        PGA4_SetGain(1)
#define PGA4_SetNonInvertGain3()        PGA4_SetGain(2)
#define PGA4_SetNonInvertGain5()        PGA4_SetGain(3)
#define PGA4_SetNonInvertGain9()        PGA4_SetGain(4)
#define PGA4_SetNonInvertGain17()       PGA4_SetGain(5)
#define PGA4_SetNonInvertGain33()       PGA4_SetGain(6)
#define PGA4_SetNonInvertGain49()       PGA4_SetGain(7)

/////////////////////////////////////////////////

#define SPCTL_SPEN_MSK                  BIT6
#define SPI1_Enable()                   SET_REG_BIT(SPCTL, SPCTL_SPEN_MSK)
#define SPI1_Disable()                  CLR_REG_BIT(SPCTL, SPCTL_SPEN_MSK)

#define SPCTL_DORD_MSK                  BIT5
#define SPI1_DataLSB()                  SET_REG_BIT(SPCTL, SPCTL_DORD_MSK)
#define SPI1_DataMSB()                  CLR_REG_BIT(SPCTL, SPCTL_DORD_MSK)

#define SPCTL_MSTR_MSK                  BIT4
#define SPI1_MasterMode()               SET_REG_BIT(SPCTL, SPCTL_MSTR_MSK)
#define SPI1_SlaveMode()                CLR_REG_BIT(SPCTL, SPCTL_MSTR_MSK)

#define SPCTL_SSIG_MSK                  BIT7
#define SPI1_IgnoreSS()                 SET_REG_BIT(SPCTL, SPCTL_SSIG_MSK)
#define SPI1_UnignoreSS()               CLR_REG_BIT(SPCTL, SPCTL_SSIG_MSK)

#define SPCTL_CPOL_MSK                  BIT3
#define SPCTL_CPHA_MSK                  BIT2
#define SPIMODE                         (SPCTL_CPOL_MSK | SPCTL_CPHA_MSK)
#define SPI1_SetMode0()                 MODIFY_REG(SPCTL, SPIMODE, ((0) << 2))
#define SPI1_SetMode1()                 MODIFY_REG(SPCTL, SPIMODE, ((1) << 2))
#define SPI1_SetMode2()                 MODIFY_REG(SPCTL, SPIMODE, ((2) << 2))
#define SPI1_SetMode3()                 MODIFY_REG(SPCTL, SPIMODE, ((3) << 2))

#define SPCTL_SPR_MSK                   (BIT1 | BIT0)
#define SPI1_SetClockDivider(n)         MODIFY_REG(SPCTL, SPCTL_SPR_MSK, ((n) << 0))
#define SPI1_SetClockDivider2()         SPI1_SetClockDivider(3)
#define SPI1_SetClockDivider4()         SPI1_SetClockDivider(0)
#define SPI1_SetClockDivider8()         SPI1_SetClockDivider(1)
#define SPI1_SetClockDivider16()        SPI1_SetClockDivider(2)

#define SPI1_SendData(d)                (SPDAT = (d))
#define SPI1_ReadData()                 (SPDAT)

#define HSSPICFG2_IOSW_MSK              BIT6
#define SPI1_SwapMosiMiso()             SET_REG_BIT(HSSPI_CFG2, HSSPICFG2_IOSW_MSK)

#define HSSPICFG2_HSSPIEN_MSK           BIT5
#define HSSPI1_Enable()                 SET_REG_BIT(HSSPI_CFG2, HSSPICFG2_HSSPIEN_MSK)
#define HSSPI1_Disable()                CLR_REG_BIT(HSSPI_CFG2, HSSPICFG2_HSSPIEN_MSK)

#define HSSPICFG_SSHLD_MSK              BIT_HN
#define HSSPI1_SetSSHoldTime(n)         MODIFY_REG(HSSPI_CFG, HSSPICFG_SSHLD_MSK, ((n) << 4))

#define HSSPICFG_SSSETUP_MSK            BIT_LN
#define HSSPI1_SetSSSetupTime(n)        MODIFY_REG(HSSPI_CFG, HSSPICFG_SSSETUP_MSK, ((n) << 0))

#define HSSPICFG2_SSDACT_MSK            BIT_LN
#define HSSPI1_SetSSDeactTime(n)        MODIFY_REG(HSSPI_CFG2, HSSPICFG2_SSDACT_MSK, ((n) << 0))

#define HSSPICFG2_FIFOEN_MSK            BIT4
#define HSSPI1_EnableFIFO()             SET_REG_BIT(HSSPI_CFG2, HSSPICFG2_FIFOEN_MSK)
#define HSSPI1_DisableFIFO()            CLR_REG_BIT(HSSPI_CFG2, HSSPICFG2_FIFOEN_MSK)

#define HSSPI1_SetClockDivider(n)       WRITE_REG(HSSPI_PSCR, (n))

#define SPITOCR_ENTO_MSK                BIT7
#define SPI1_EnableTimeout()            SET_REG_BIT(SPITOCR, SPITOCR_ENTO_MSK)
#define SPI1_DisableTimeout()           CLR_REG_BIT(SPITOCR, SPITOCR_ENTO_MSK)

#define SPITOCR_SCALE_MSK               BIT5
#define SPI1_TimeoutScale_SYSCLK()      SET_REG_BIT(SPITOCR, SPITOCR_SCALE_MSK)
#define SPI1_TimeoutScale_1us()         CLR_REG_BIT(SPITOCR, SPITOCR_SCALE_MSK)

#define SPI1_SetTimeoutInterval(n)      SPITOTL = BYTE0(n); \
                                        SPITOTH = BYTE1(n); \
                                        SPITOTE = BYTE2(n)

////////////////////////

#define SPI2CTL_SPEN_MSK                BIT6
#define SPI2_Enable()                   SET_REG_BIT(SPI2CTL, SPI2CTL_SPEN_MSK)
#define SPI2_Disable()                  CLR_REG_BIT(SPI2CTL, SPI2CTL_SPEN_MSK)

#define SPI2CTL_DORD_MSK                BIT5
#define SPI2_DataLSB()                  SET_REG_BIT(SPI2CTL, SPI2CTL_DORD_MSK)
#define SPI2_DataMSB()                  CLR_REG_BIT(SPI2CTL, SPI2CTL_DORD_MSK)

#define SPI2CTL_MSTR_MSK                BIT4
#define SPI2_MasterMode()               SET_REG_BIT(SPI2CTL, SPI2CTL_MSTR_MSK)
#define SPI2_SlaveMode()                CLR_REG_BIT(SPI2CTL, SPI2CTL_MSTR_MSK)

#define SPI2CTL_SSIG_MSK                BIT7
#define SPI2_IgnoreSS()                 SET_REG_BIT(SPI2CTL, SPI2CTL_SSIG_MSK)
#define SPI2_UnignoreSS()               CLR_REG_BIT(SPI2CTL, SPI2CTL_SSIG_MSK)

#define SPI2CTL_CPOL_MSK                BIT3
#define SPI2CTL_CPHA_MSK                BIT2
#define SPI2MODE                        (SPI2CTL_CPOL_MSK | SPI2CTL_CPHA_MSK)
#define SPI2_SetMode0()                 MODIFY_REG(SPI2CTL, SPI2MODE, ((0) << 2))
#define SPI2_SetMode1()                 MODIFY_REG(SPI2CTL, SPI2MODE, ((1) << 2))
#define SPI2_SetMode2()                 MODIFY_REG(SPI2CTL, SPI2MODE, ((2) << 2))
#define SPI2_SetMode3()                 MODIFY_REG(SPI2CTL, SPI2MODE, ((3) << 2))

#define SPI2CTL_SPR_MSK                 (BIT1 | BIT0)
#define SPI2_SetClockDivider(n)         MODIFY_REG(SPI2CTL, SPI2CTL_SPR_MSK, ((n) << 0))
#define SPI2_SetClockDivider2()         SPI2_SetClockDivider(3)
#define SPI2_SetClockDivider4()         SPI2_SetClockDivider(0)
#define SPI2_SetClockDivider8()         SPI2_SetClockDivider(1)
#define SPI2_SetClockDivider16()        SPI2_SetClockDivider(2)

#define SPI2_SendData(d)                (SPI2DAT = (d))
#define SPI2_ReadData()                 (SPI2DAT)

#define HSSPI2CFG2_IOSW_MSK             BIT6
#define SPI2_SwapMosiMiso()             SET_REG_BIT(HSSPI2_CFG2, HSSPI2CFG2_IOSW_MSK)

#define HSSPI2CFG2_HSSPIEN_MSK          BIT5
#define HSSPI2_Enable()                 SET_REG_BIT(HSSPI2_CFG2, HSSPI2CFG2_HSSPIEN_MSK)
#define HSSPI2_Disable()                CLR_REG_BIT(HSSPI2_CFG2, HSSPI2CFG2_HSSPIEN_MSK)

#define HSSPI2CFG_SSHLD_MSK             BIT_HN
#define HSSPI2_SetSSHoldTime(n)         MODIFY_REG(HSSPI2_CFG, HSSPI2CFG_SSHLD_MSK, ((n) << 4))

#define HSSPI2CFG_SSSETUP_MSK           BIT_LN
#define HSSPI2_SetSSSetupTime(n)        MODIFY_REG(HSSPI2_CFG, HSSPI2CFG_SSSETUP_MSK, ((n) << 0))

#define HSSPI2CFG2_SSDACT_MSK           BIT_LN
#define HSSPI2_SetSSDeactTime(n)        MODIFY_REG(HSSPI2_CFG2, HSSPI2CFG2_SSDACT_MSK, ((n) << 0))

#define HSSPI2CFG2_FIFOEN_MSK            BIT4
#define HSSPI2_EnableFIFO()             SET_REG_BIT(HSSPI2_CFG2, HSSPI2CFG2_FIFOEN_MSK)
#define HSSPI2_DisableFIFO()            CLR_REG_BIT(HSSPI2_CFG2, HSSPI2CFG2_FIFOEN_MSK)

#define HSSPI2_SetClockDivider(n)       WRITE_REG(HSSPI2_PSCR, (n))

#define SPI2TOCR_ENTO_MSK               BIT7
#define SPI2_EnableTimeout()            SET_REG_BIT(SPI2TOCR, SPI2TOCR_ENTO_MSK)
#define SPI2_DisableTimeout()           CLR_REG_BIT(SPI2TOCR, SPI2TOCR_ENTO_MSK)

#define SPI2TOCR_SCALE_MSK              BIT5
#define SPI2_TimeoutScale_SYSCLK()      SET_REG_BIT(SPI2TOCR, SPI2TOCR_SCALE_MSK)
#define SPI2_TimeoutScale_1us()         CLR_REG_BIT(SPI2TOCR, SPI2TOCR_SCALE_MSK)

#define SPI2_SetTimeoutInterval(n)      SPI2TOTL = BYTE0(n); \
                                        SPI2TOTH = BYTE1(n); \
                                        SPI2TOTE = BYTE2(n)

////////////////////////

#define SPI3CTL_SPEN_MSK                BIT6
#define SPI3_Enable()                   SET_REG_BIT(SPI3CTL, SPI3CTL_SPEN_MSK)
#define SPI3_Disable()                  CLR_REG_BIT(SPI3CTL, SPI3CTL_SPEN_MSK)

#define SPI3CTL_DORD_MSK                BIT5
#define SPI3_DataLSB()                  SET_REG_BIT(SPI3CTL, SPI3CTL_DORD_MSK)
#define SPI3_DataMSB()                  CLR_REG_BIT(SPI3CTL, SPI3CTL_DORD_MSK)

#define SPI3CTL_MSTR_MSK                BIT4
#define SPI3_MasterMode()               SET_REG_BIT(SPI3CTL, SPI3CTL_MSTR_MSK)
#define SPI3_SlaveMode()                CLR_REG_BIT(SPI3CTL, SPI3CTL_MSTR_MSK)

#define SPI3CTL_SSIG_MSK                BIT7
#define SPI3_IgnoreSS()                 SET_REG_BIT(SPI3CTL, SPI3CTL_SSIG_MSK)
#define SPI3_UnignoreSS()               CLR_REG_BIT(SPI3CTL, SPI3CTL_SSIG_MSK)

#define SPI3CTL_CPOL_MSK                BIT3
#define SPI3CTL_CPHA_MSK                BIT2
#define SPI3MODE                        (SPI3CTL_CPOL_MSK | SPI3CTL_CPHA_MSK)
#define SPI3_SetMode0()                 MODIFY_REG(SPI3CTL, SPI3MODE, ((0) << 2))
#define SPI3_SetMode1()                 MODIFY_REG(SPI3CTL, SPI3MODE, ((1) << 2))
#define SPI3_SetMode2()                 MODIFY_REG(SPI3CTL, SPI3MODE, ((2) << 2))
#define SPI3_SetMode3()                 MODIFY_REG(SPI3CTL, SPI3MODE, ((3) << 2))

#define SPI3CTL_SPR_MSK                 (BIT1 | BIT0)
#define SPI3_SetClockDivider(n)         MODIFY_REG(SPI3CTL, SPI3CTL_SPR_MSK, ((n) << 0))
#define SPI3_SetClockDivider2()         SPI3_SetClockDivider(3)
#define SPI3_SetClockDivider4()         SPI3_SetClockDivider(0)
#define SPI3_SetClockDivider8()         SPI3_SetClockDivider(1)
#define SPI3_SetClockDivider16()        SPI3_SetClockDivider(2)

#define SPI3_SendData(d)                (SPI3DAT = (d))
#define SPI3_ReadData()                 (SPI3DAT)

#define HSSPI3CFG2_IOSW_MSK             BIT6
#define SPI3_SwapMosiMiso()             SET_REG_BIT(HSSPI3_CFG2, HSSPI3CFG2_IOSW_MSK)

#define HSSPI3CFG2_HSSPIEN_MSK          BIT5
#define HSSPI3_Enable()                 SET_REG_BIT(HSSPI3_CFG2, HSSPI3CFG2_HSSPIEN_MSK)
#define HSSPI3_Disable()                CLR_REG_BIT(HSSPI3_CFG2, HSSPI3CFG2_HSSPIEN_MSK)

#define HSSPI3CFG_SSHLD_MSK             BIT_HN
#define HSSPI3_SetSSHoldTime(n)         MODIFY_REG(HSSPI3_CFG, HSSPI3CFG_SSHLD_MSK, ((n) << 4))

#define HSSPI3CFG_SSSETUP_MSK           BIT_LN
#define HSSPI3_SetSSSetupTime(n)        MODIFY_REG(HSSPI3_CFG, HSSPI3CFG_SSSETUP_MSK, ((n) << 0))

#define HSSPI3CFG2_SSDACT_MSK           BIT_LN
#define HSSPI3_SetSSDeactTime(n)        MODIFY_REG(HSSPI3_CFG2, HSSPI3CFG2_SSDACT_MSK, ((n) << 0))

#define HSSPI3CFG2_FIFOEN_MSK            BIT4
#define HSSPI3_EnableFIFO()             SET_REG_BIT(HSSPI3_CFG2, HSSPI3CFG2_FIFOEN_MSK)
#define HSSPI3_DisableFIFO()            CLR_REG_BIT(HSSPI3_CFG2, HSSPI3CFG2_FIFOEN_MSK)

#define HSSPI3_SetClockDivider(n)       WRITE_REG(HSSPI3_PSCR, (n))

#define SPI3TOCR_ENTO_MSK               BIT7
#define SPI3_EnableTimeout()            SET_REG_BIT(SPI3TOCR, SPI3TOCR_ENTO_MSK)
#define SPI3_DisableTimeout()           CLR_REG_BIT(SPI3TOCR, SPI3TOCR_ENTO_MSK)

#define SPI3TOCR_SCALE_MSK              BIT5
#define SPI3_TimeoutScale_SYSCLK()      SET_REG_BIT(SPI3TOCR, SPI3TOCR_SCALE_MSK)
#define SPI3_TimeoutScale_1us()         CLR_REG_BIT(SPI3TOCR, SPI3TOCR_SCALE_MSK)

#define SPI3_SetTimeoutInterval(n)      SPI3TOTL = BYTE0(n); \
                                        SPI3TOTH = BYTE1(n); \
                                        SPI3TOTE = BYTE2(n)

/////////////////////////////////////////////////

#define QSPICR1_EN_MSK                  BIT0
#define QSPI_Enable()                   SET_REG_BIT(QSPI_CR1, QSPICR1_EN_MSK)
#define QSPI_Disable()                  CLR_REG_BIT(QSPI_CR1, QSPICR1_EN_MSK)

#define QSPICR1_ABORT_MSK               BIT1
#define QSPI_Abort()                    SET_REG_BIT(QSPI_CR1, QSPICR1_ABORT_MSK)

#define QSPICR1_SSHIFT_MSK              BIT4
#define QSPI_ReadNoDelay()              CLR_REG_BIT(QSPI_CR1, QSPICR1_SSHIFT_MSK)
#define QSPI_ReadDelayHalfCycle()       SET_REG_BIT(QSPI_CR1, QSPICR1_SSHIFT_MSK)

#define QSPICR2_FTHRES_MSK              (BIT4 | BIT_LN)
#define QSPI_SetFIFOLevel(n)            MODIFY_REG(QSPI_CR2, QSPICR2_FTHRES_MSK, ((n) << 0))

#define QSPICR3_PMM_MSK                 BIT7
#define QSPI_PollingMatchAND()          CLR_REG_BIT(QSPI_CR3, QSPICR3_PMM_MSK)
#define QSPI_PollingMatchOR()           SET_REG_BIT(QSPI_CR3, QSPICR3_PMM_MSK)

#define QSPICR3_APMS_MSK                BIT6
#define QSPI_PollingManualStop()        CLR_REG_BIT(QSPI_CR3, QSPICR3_APMS_MSK)
#define QSPI_PollingAutoStop()          SET_REG_BIT(QSPI_CR3, QSPICR3_APMS_MSK)

#define QSPICR3_TOIE_MSK                BIT4
#define QSPICR3_SMIE_MSK                BIT3
#define QSPICR3_FTIE_MSK                BIT2
#define QSPICR3_TCIE_MSK                BIT1
#define QSPICR3_TEIE_MSK                BIT0
#define QSPI_EnableTimeoutInt()         SET_REG_BIT(QSPI_CR3, QSPICR3_TOIE_MSK)
#define QSPI_EnableMatchInt()           SET_REG_BIT(QSPI_CR3, QSPICR3_SMIE_MSK)
#define QSPI_EnableFIFOInt()            SET_REG_BIT(QSPI_CR3, QSPICR3_FTIE_MSK)
#define QSPI_EnableTransferInt()        SET_REG_BIT(QSPI_CR3, QSPICR3_TCIE_MSK)
#define QSPI_EnableErrorInt()           SET_REG_BIT(QSPI_CR3, QSPICR3_TEIE_MSK)

#define QSPI_SetClockDivider(n)         (QSPI_CR4 = (n))

#define QSPIDCR1_CSHT_MSK               (BIT6 | BIT5 | BIT4)
#define QSPI_SetCSHold(n)               MODIFY_REG(QSPI_DCR1, QSPIDCR1_CSHT_MSK, ((n) << 4))

#define QSPIDCR1_CKMODE_MSK             (BIT0)
#define QSPI_SetSCKNormalHigh()         SET_REG_BIT(QSPI_DCR1, QSPIDCR1_CKMODE_MSK)
#define QSPI_SetSCKNormalLow()          CLR_REG_BIT(QSPI_DCR1, QSPIDCR1_CKMODE_MSK)

#define QSPIDCR2_FSIZE_MSK              (BIT4 | BIT_LN)
#define QSPI_SetFlashSize(n)            MODIFY_REG(QSPI_DCR2, QSPIDCR2_FSIZE_MSK, ((n) << 0))

#define QSPISR1_BUSY_MSK                BIT5
#define QSPI_CheckBusy()                READ_REG_BIT(QSPI_SR1, QSPISR1_BUSY_MSK)

#define QSPISR2_FLEVEL_MSK              (BIT5 | BIT4 | BIT_LN)
#define QSPI_CheckFIFOLevel()           READ_REG_BIT(QSPI_SR2, QSPISR2_FLEVEL_MSK)

/*
#define QSPI_SetDataLength(n)           QSPI_DLR4 = BYTE3(n);       \
                                        QSPI_DLR3 = BYTE2(n);       \
                                        QSPI_DLR2 = BYTE1(n);       \
                                        QSPI_DLR1 = BYTE0(n)
*/

#define QSPI_SetDataLength(n)           QSPI_DLR2 = BYTE1(n);       \
                                        QSPI_DLR1 = BYTE0(n)

#define QSPI_SetAddress(n)              QSPI_AR4 = BYTE3(n);        \
                                        QSPI_AR3 = BYTE2(n);        \
                                        QSPI_AR2 = BYTE1(n);        \
                                        QSPI_AR1 = BYTE0(n)

#define QSPI_SetAlternate(n)            QSPI_ABR4 = BYTE3(n);       \
                                        QSPI_ABR3 = BYTE2(n);       \
                                        QSPI_ABR2 = BYTE1(n);       \
                                        QSPI_ABR1 = BYTE0(n)

#define QSPI_SetInstruction(n)          (QSPI_CCR1 = (n))

#define QSPICCR2_ADSIZE_MSK             (BIT5 | BIT4)
#define QSPI_SetAddressSize(n)          MODIFY_REG(QSPI_CCR2, QSPICCR2_ADSIZE_MSK, ((n) << 4))
#define QSPI_SetAddressSize_8B()        QSPI_SetAddressSize(0)
#define QSPI_SetAddressSize_16B()       QSPI_SetAddressSize(1)
#define QSPI_SetAddressSize_24B()       QSPI_SetAddressSize(2)
#define QSPI_SetAddressSize_32B()       QSPI_SetAddressSize(3)

#define QSPICCR3_ABSIZE_MSK             (BIT1 | BIT0)
#define QSPI_SetAlternateSize(n)        MODIFY_REG(QSPI_CCR3, QSPICCR3_ABSIZE_MSK, ((n) << 0))
#define QSPI_SetAlternateSize_8B()      QSPI_SetAlternateSize(0)
#define QSPI_SetAlternateSize_16B()     QSPI_SetAlternateSize(1)
#define QSPI_SetAlternateSize_24B()     QSPI_SetAlternateSize(2)
#define QSPI_SetAlternateSize_32B()     QSPI_SetAlternateSize(3)

#define QSPICCR3_DCYC_MSK               (BIT6 | BIT5 | BIT4 | BIT3 | BIT2)
#define QSPI_SetDummyCycles(n)          MODIFY_REG(QSPI_CCR3, QSPICCR3_DCYC_MSK, ((n) << 2))

#define QSPICCR2_IMODE_MSK              (BIT1 | BIT0)
#define QSPI_SetInstructionMode(n)      MODIFY_REG(QSPI_CCR2, QSPICCR2_IMODE_MSK, ((n) << 0))
#define QSPI_NoInstruction()            QSPI_SetInstructionMode(0)
#define QSPI_InstructionSingMode()      QSPI_SetInstructionMode(1)
#define QSPI_InstructionDualMode()      QSPI_SetInstructionMode(2)
#define QSPI_InstructionQuadMode()      QSPI_SetInstructionMode(3)

#define QSPICCR2_ADMODE_MSK             (BIT3 | BIT2)
#define QSPI_SetAddressMode(n)          MODIFY_REG(QSPI_CCR2, QSPICCR2_ADMODE_MSK, ((n) << 2))
#define QSPI_NoAddress()                QSPI_SetAddressMode(0)
#define QSPI_AddressSingMode()          QSPI_SetAddressMode(1)
#define QSPI_AddressDualMode()          QSPI_SetAddressMode(2)
#define QSPI_AddressQuadMode()          QSPI_SetAddressMode(3)

#define QSPICCR2_ABMODE_MSK             (BIT7 | BIT6)
#define QSPI_SetAlternateMode(n)        MODIFY_REG(QSPI_CCR2, QSPICCR2_ABMODE_MSK, ((n) << 6))
#define QSPI_NoAlternate()              QSPI_SetAlternateMode(0)
#define QSPI_AlternateSingMode()        QSPI_SetAlternateMode(1)
#define QSPI_AlternateDualMode()        QSPI_SetAlternateMode(2)
#define QSPI_AlternateQuadMode()        QSPI_SetAlternateMode(3)

#define QSPICCR4_DMODE_MSK              (BIT1 | BIT0)
#define QSPI_SetDataMode(n)             MODIFY_REG(QSPI_CCR4, QSPICCR4_DMODE_MSK, ((n) << 0))
#define QSPI_NoData()                   QSPI_SetDataMode(0)
#define QSPI_DataSingMode()             QSPI_SetDataMode(1)
#define QSPI_DataDualMode()             QSPI_SetDataMode(2)
#define QSPI_DataQuadMode()             QSPI_SetDataMode(3)

#define QSPICCR4_FMODE_MSK              (BIT3 | BIT2)
#define QSPI_SetFunctionMode(n)         MODIFY_REG(QSPI_CCR4, QSPICCR4_FMODE_MSK, ((n) << 2))
#define QSPI_SetWriteMode()             QSPI_SetFunctionMode(0)
#define QSPI_SetReadMode()              QSPI_SetFunctionMode(1)
#define QSPI_SetPollingMode()           QSPI_SetFunctionMode(2)

#define QSPICCR4_SIOO_MSK               BIT4
#define QSPI_InstructionOnce()          SET_REG_BIT(QSPI_CCR4, QSPICCR4_SIOO_MSK)
#define QSPI_InstructionAlways()        CLR_REG_BIT(QSPI_CCR4, QSPICCR4_SIOO_MSK)

#define QSPI_ReadData()                 (ACC = QSPI_DR)
#define QSPI_WriteData(d)               (QSPI_DR = (d))

#define QSPI_SetPollingMask(n)          /* QSPI_PSMKR4 = BYTE3(n); */   \
                                        /* QSPI_PSMKR3 = BYTE2(n); */   \
                                        /* QSPI_PSMKR2 = BYTE1(n);  */  \
                                        QSPI_PSMKR1 = BYTE0(n)

#define QSPI_SetPollingMatch(n)         /* QSPI_PSMAR4 = BYTE3(n); */   \
                                        /* QSPI_PSMAR3 = BYTE2(n); */   \
                                        /* QSPI_PSMAR2 = BYTE1(n);  */  \
                                        QSPI_PSMAR1 = BYTE0(n)

#define QSPI_SetPollingInterval(n)      QSPI_PIR2 = BYTE1(n);           \
                                        QSPI_PIR1 = BYTE0(n)

/////////////////////////////////////////////////

#define I2CCFG_ENI2C_MSK                BIT7
#define I2C1_Enable()                   SET_REG_BIT(I2CCFG, I2CCFG_ENI2C_MSK)
#define I2C1_Disable()                  CLR_REG_BIT(I2CCFG, I2CCFG_ENI2C_MSK)

#define I2CCFG_MSSL_MSK                 BIT6
#define I2C1_MasterMode()               SET_REG_BIT(I2CCFG, I2CCFG_MSSL_MSK)
#define I2C1_SlaveMode()                CLR_REG_BIT(I2CCFG, I2CCFG_MSSL_MSK)

#define I2CCFG_SPEED_MSK                (BIT5 | BIT4 |BIT_LN)
#define I2C1_SetClockDivider(n)         MODIFY_REG(I2CCFG, I2CCFG_SPEED_MSK, ((n) << 0)); \
                                        I2CPSCR = ((n) >> 6)

#define I2CMSCR_MSCMD_MSK               (BIT_LN)
#define I2C1_SetMasterCommand(n)        MODIFY_REG(I2CMSCR, I2CMSCR_MSCMD_MSK, ((n) << 0))

#define I2CCMD_IDLE                     0
#define I2CCMD_START                    1
#define I2CCMD_SENDDATA                 2
#define I2CCMD_RECVACK                  3
#define I2CCMD_RECVDATA                 4
#define I2CCMD_SENDACK                  5
#define I2CCMD_STOP                     6
#define I2CCMD_START_SENDDATA_RECVACK   9
#define I2CCMD_SENDDATA_RECVACK         10
#define I2CCMD_RECVDATA_SENDACK         11
#define I2CCMD_RECVDATA_SENDNAK         12
#define I2C1_Idle()                     I2C1_SetMasterCommand(I2CCMD_IDLE)
#define I2C1_Start()                    I2C1_SetMasterCommand(I2CCMD_START)
#define I2C1_SendData()                 I2C1_SetMasterCommand(I2CCMD_SENDDATA)
#define I2C1_RecvACK()                  I2C1_SetMasterCommand(I2CCMD_RECVACK)
#define I2C1_RecvData()                 I2C1_SetMasterCommand(I2CCMD_RECVDATA)
#define I2C1_SendACK()                  I2C1_SetMasterCommand(I2CCMD_SENDACK)
#define I2C1_Stop()                     I2C1_SetMasterCommand(I2CCMD_STOP)
#define I2C1_StartSendDataRecvACK()     I2C1_SetMasterCommand(I2CCMD_START_SENDDATA_RECVACK)
#define I2C1_SendDataRecvACK()          I2C1_SetMasterCommand(I2CCMD_SENDDATA_RECVACK)
#define I2C1_RecvDataSendACK()          I2C1_SetMasterCommand(I2CCMD_RECVDATA_SENDACK)
#define I2C1_RecvDataSendNAK()          I2C1_SetMasterCommand(I2CCMD_RECVDATA_SENDNAK)

#define I2CMSST_BUSY_MSK                BIT7
#define I2C1_CheckMasterBusy()          READ_REG_BIT(I2CMSST, I2CMSST_BUSY_MSK)

#define I2CMSST_MSIF_MSK                BIT6
#define I2C1_CheckMasterFlag()          READ_REG_BIT(I2CMSST, I2CMSST_MSIF_MSK)
#define I2C1_ClearMasterFlag()          CLR_REG_BIT(I2CMSST, I2CMSST_MSIF_MSK)

#define I2C1_WriteData(d)               (I2CTXD = (d))
#define I2C1_ReadData()                 (I2CRXD)

#define I2CMSST_ACKI_MSK                BIT1
#define I2CMSST_ACKO_MSK                BIT0
#define I2C1_MasterSetACK()             CLR_REG_BIT(I2CMSST, I2CMSST_ACKO_MSK)
#define I2C1_MasterSetNAK()             SET_REG_BIT(I2CMSST, I2CMSST_ACKO_MSK)
#define I2C1_MasterReadACK()            READ_REG_BIT(I2CMSST, I2CMSST_ACKI_MSK)

#define I2CSLCR_SLRST_MSK               BIT0
#define I2C1_SlaveReset()               SET_REG_BIT(I2CSLCR, I2CSLCR_SLRST_MSK)

#define I2CSLST_BUSY_MSK                BIT7
#define I2C1_CheckSlaveBusy()           READ_REG_BIT(I2CSLST, I2CSLST_BUSY_MSK)

#define I2CSLST_ACKI_MSK                BIT1
#define I2CSLST_ACKO_MSK                BIT0
#define I2C1_SlaveSetACK()              CLR_REG_BIT(I2CSLST, I2CSLST_ACKO_MSK)
#define I2C1_SlaveSetNAK()              SET_REG_BIT(I2CSLST, I2CSLST_ACKO_MSK)
#define I2C1_SlaveReadACK()             READ_REG_BIT(I2CSLST, I2CSLST_ACKI_MSK)

#define I2CSLADR_SLADR_MSK              (BIT_HN | BIT3 | BIT2 | BIT1)
#define I2C1_SetSlaveAddress(n)         I2CSLADR = ((n) << 1)

#define I2CSLADR_MA_MSK                 (BIT0)
#define I2C1_SetSlaveBroadcast()        SET_REG_BIT(I2CSLADR, I2CSLADR_MA_MSK)

#define I2CTOCR_ENTO_MSK                BIT7
#define I2C1_EnableTimeout()            SET_REG_BIT(I2CTOCR, I2CTOCR_ENTO_MSK)
#define I2C1_DisableTimeout()           CLR_REG_BIT(I2CTOCR, I2CTOCR_ENTO_MSK)

#define I2CTOCR_SCALE_MSK               BIT5
#define I2C1_TimeoutScale_SYSCLK()      SET_REG_BIT(I2CTOCR, I2CTOCR_SCALE_MSK)
#define I2C1_TimeoutScale_1us()         CLR_REG_BIT(I2CTOCR, I2CTOCR_SCALE_MSK)

#define I2C1_SetTimeoutInterval(n)      I2CTOTL = BYTE0(n); \
                                        I2CTOTH = BYTE1(n); \
                                        I2CTOTE = BYTE2(n)

////////////////////////

#define I2C2CFG_ENI2C_MSK               BIT7
#define I2C2_Enable()                   SET_REG_BIT(I2C2CFG, I2C2CFG_ENI2C_MSK)
#define I2C2_Disable()                  CLR_REG_BIT(I2C2CFG, I2C2CFG_ENI2C_MSK)

#define I2C2CFG_MSSL_MSK                BIT6
#define I2C2_MasterMode()               SET_REG_BIT(I2C2CFG, I2C2CFG_MSSL_MSK)
#define I2C2_SlaveMode()                CLR_REG_BIT(I2C2CFG, I2C2CFG_MSSL_MSK)

#define I2C2CFG_SPEED_MSK               (BIT5 | BIT4 |BIT_LN)
#define I2C2_SetClockDivider(n)         MODIFY_REG(I2C2CFG, I2C2CFG_SPEED_MSK, ((n) << 0)); \
                                        I2C2PSCR = ((n) >> 6)

#define I2C2MSCR_MSCMD_MSK              (BIT_LN)
#define I2C2_SetMasterCommand(n)        MODIFY_REG(I2C2MSCR, I2C2MSCR_MSCMD_MSK, ((n) << 0))

#define I2C2CMD_IDLE                    0
#define I2C2CMD_START                   1
#define I2C2CMD_SENDDATA                2
#define I2C2CMD_RECVACK                 3
#define I2C2CMD_RECVDATA                4
#define I2C2CMD_SENDACK                 5
#define I2C2CMD_STOP                    6
#define I2C2CMD_START_SENDDATA_RECVACK  9
#define I2C2CMD_SENDDATA_RECVACK        10
#define I2C2CMD_RECVDATA_SENDACK        11
#define I2C2CMD_RECVDATA_SENDNAK        12
#define I2C2_Idle()                     I2C2_SetMasterCommand(I2C2CMD_IDLE)
#define I2C2_Start()                    I2C2_SetMasterCommand(I2C2CMD_START)
#define I2C2_SendData()                 I2C2_SetMasterCommand(I2C2CMD_SENDDATA)
#define I2C2_RecvACK()                  I2C2_SetMasterCommand(I2C2CMD_RECVACK)
#define I2C2_RecvData()                 I2C2_SetMasterCommand(I2C2CMD_RECVDATA)
#define I2C2_SendACK()                  I2C2_SetMasterCommand(I2C2CMD_SENDACK)
#define I2C2_Stop()                     I2C2_SetMasterCommand(I2C2CMD_STOP)
#define I2C2_StartSendDataRecvACK()     I2C2_SetMasterCommand(I2C2CMD_START_SENDDATA_RECVACK)
#define I2C2_SendDataRecvACK()          I2C2_SetMasterCommand(I2C2CMD_SENDDATA_RECVACK)
#define I2C2_RecvDataSendACK()          I2C2_SetMasterCommand(I2C2CMD_RECVDATA_SENDACK)
#define I2C2_RecvDataSendNAK()          I2C2_SetMasterCommand(I2C2CMD_RECVDATA_SENDNAK)

#define I2C2MSST_BUSY_MSK               BIT7
#define I2C2_CheckMasterBusy()          READ_REG_BIT(I2C2MSST, I2C2MSST_BUSY_MSK)

#define I2C2MSST_MSIF_MSK               BIT6
#define I2C2_CheckMasterFlag()          READ_REG_BIT(I2C2MSST, I2C2MSST_MSIF_MSK)
#define I2C2_ClearMasterFlag()          CLR_REG_BIT(I2C2MSST, I2C2MSST_MSIF_MSK)

#define I2C2_WriteData(d)               (I2C2TXD = (d))
#define I2C2_ReadData()                 (I2C2RXD)

#define I2C2MSST_ACKI_MSK               BIT1
#define I2C2MSST_ACKO_MSK               BIT0
#define I2C2_MasterSetACK()             CLR_REG_BIT(I2C2MSST, I2C2MSST_ACKO_MSK)
#define I2C2_MasterSetNAK()             SET_REG_BIT(I2C2MSST, I2C2MSST_ACKO_MSK)
#define I2C2_MasterReadACK()            READ_REG_BIT(I2C2MSST, I2C2MSST_ACKI_MSK)

#define I2C2SLCR_SLRST_MSK              BIT0
#define I2C2_SlaveReset()               SET_REG_BIT(I2C2SLCR, I2C2SLCR_SLRST_MSK)

#define I2C2SLST_BUSY_MSK               BIT7
#define I2C2_CheckSlaveBusy()           READ_REG_BIT(I2C2SLST, I2C2SLST_BUSY_MSK)

#define I2C2SLST_ACKI_MSK               BIT1
#define I2C2SLST_ACKO_MSK               BIT0
#define I2C2_SlaveSetACK()              CLR_REG_BIT(I2C2SLST, I2C2SLST_ACKO_MSK)
#define I2C2_SlaveSetNAK()              SET_REG_BIT(I2C2SLST, I2C2SLST_ACKO_MSK)
#define I2C2_SlaveReadACK()             READ_REG_BIT(I2C2SLST, I2C2SLST_ACKI_MSK)

#define I2C2SLADR_SLADR_MSK             (BIT_HN | BIT3 | BIT2 | BIT1)
#define I2C2_SetSlaveAddress(n)         I2C2SLADR = ((n) << 1)

#define I2C2SLADR_MA_MSK                (BIT0)
#define I2C2_SetSlaveBroadcast()        SET_REG_BIT(I2C2SLADR, I2C2SLADR_MA_MSK)

#define I2C2TOCR_ENTO_MSK               BIT7
#define I2C2_EnableTimeout()            SET_REG_BIT(I2C2TOCR, I2C2TOCR_ENTO_MSK)
#define I2C2_DisableTimeout()           CLR_REG_BIT(I2C2TOCR, I2C2TOCR_ENTO_MSK)

#define I2C2TOCR_SCALE_MSK              BIT5
#define I2C2_TimeoutScale_SYSCLK()      SET_REG_BIT(I2C2TOCR, I2C2TOCR_SCALE_MSK)
#define I2C2_TimeoutScale_1us()         CLR_REG_BIT(I2C2TOCR, I2C2TOCR_SCALE_MSK)

#define I2C2_SetTimeoutInterval(n)      I2C2TOTL = BYTE0(n); \
                                        I2C2TOTH = BYTE1(n); \
                                        I2C2TOTE = BYTE2(n)

/////////////////////////////////////////////////

#define RTCCR_RUNRTC_MSK                BIT0
#define RTC_Run()                       SET_REG_BIT(RTCCR, RTCCR_RUNRTC_MSK)
#define RTC_Stop()                      CLR_REG_BIT(RTCCR, RTCCR_RUNRTC_MSK)

#define RTCCFG_RTCCKS_MSK               BIT1
#define RTC_CLK_X32K()                  CLR_REG_BIT(RTCCFG, RTCCFG_RTCCKS_MSK)
#define RTC_CLK_LIRC()                  SET_REG_BIT(RTCCFG, RTCCFG_RTCCKS_MSK)

#define RTCCFG_SETRTC_MSK               BIT0
#define RTC_SyncInitial()               SET_REG_BIT(RTCCFG, RTCCFG_SETRTC_MSK)
#define RTC_IsSyncing()                 READ_REG_BIT(RTCCFG, RTCCFG_SETRTC_MSK)

#define RTC_SetAlarmHour(n)             (ALAHOUR = (n))
#define RTC_SetAlarmMinute(n)           (ALAMIN = (n))
#define RTC_SetAlarmSecond(n)           (ALASEC = (n))
#define RTC_SetAlarmSSecond(n)          (ALASSEC = (n))

#define RTC_SetYear(n)                  (INIYEAR = (n))
#define RTC_SetMonth(n)                 (INIMONTH = (n))
#define RTC_SetDay(n)                   (INIDAY = (n))
#define RTC_SetHour(n)                  (INIHOUR = (n))
#define RTC_SetMinute(n)                (INIMIN = (n))
#define RTC_SetSecond(n)                (INISEC = (n))
#define RTC_SetSSecond(n)               (INISSEC = (n))

#define RTC_ReadYear()                  (RTCYEAR)
#define RTC_ReadMonth()                 (RTCMONTH)
#define RTC_ReadDay()                   (RTCDAY)
#define RTC_ReadWeek()                  (RTCWEEK)
#define RTC_ReadHour()                  (RTCHOUR)
#define RTC_ReadMinute()                (RTCMIN)
#define RTC_ReadSecond()                (RTCSEC)
#define RTC_ReadSSecond()               (RTCSSEC)

/////////////////////////////////////////////////

#define LCMIFCR_EN_MSK                  BIT7
#define LCM_Enable()                    SET_REG_BIT(LCMIFCR, LCMIFCR_EN_MSK)
#define LCM_Disable()                   CLR_REG_BIT(LCMIFCR, LCMIFCR_EN_MSK)

#define LCMIFCFG_BW_MSK                 BIT1
#define LCM_SetBitWidth_8B()            CLR_REG_BIT(LCMIFCFG, LCMIFCFG_BW_MSK)
#define LCM_SetBitWidth_16B()           SET_REG_BIT(LCMIFCFG, LCMIFCFG_BW_MSK)

#define LCMIFCFG_MODE_MSK               BIT0
#define LCM_SetMode_i8080()             CLR_REG_BIT(LCMIFCFG, LCMIFCFG_MODE_MSK)
#define LCM_SetMode_M6800()             SET_REG_BIT(LCMIFCFG, LCMIFCFG_MODE_MSK)

#define LCMIFCFG2_SETUPT_MSK            (BIT4 | BIT3 | BIT2)
#define LCMIFCFG2_HOLDT_MSK             (BIT1 | BIT0)
#define LCM_SetSetupTime(n)             MODIFY_REG(LCMIFCFG2, LCMIFCFG2_SETUPT_MSK, ((n) << 2))
#define LCM_SetHoldTime(n)              MODIFY_REG(LCMIFCFG2, LCMIFCFG2_HOLDT_MSK, ((n) << 0))

#define LCMIFCR_ENDIAN_MSK              BIT4
#define LCM_SetDataBigEndian()          CLR_REG_BIT(LCMIFCR, LCMIFCR_ENDIAN_MSK)
#define LCM_SetDataLittleEndian()       SET_REG_BIT(LCMIFCR, LCMIFCR_ENDIAN_MSK)

#define LCMIFCR_CMD_MSK                 (BIT2 | BIT1 | BIT0)
#define LCM_SetCommand(n)               MODIFY_REG(LCMIFCR, LCMIFCR_CMD_MSK, ((n) << 0))

#define LCMCMD_IDLE                     0
#define LCMCMD_SENDCMD                  4
#define LCMCMD_SENDDATA                 5
#define LCMCMD_READSTAT                 6
#define LCMCMD_READDATA                 7
#define LCM_Idle()                      LCM_SetCommand(LCMCMD_IDLE)
#define LCM_TrigSendCommand()           LCM_SetCommand(LCMCMD_SENDCMD)
#define LCM_TrigSendData()              LCM_SetCommand(LCMCMD_SENDDATA)
#define LCM_TrigReadStatus()            LCM_SetCommand(LCMCMD_READSTAT)
#define LCM_TrigReadData()              LCM_SetCommand(LCMCMD_READDATA)

#define LCM_WriteData_8B(d)             WRITE_REG(LCMIFDATL, (d))
#define LCM_ReadData_8B()               (LCMIFDATL)

#define LCM_WriteData_16B(d)            (LCMIFDATH = HIBYTE(d), LCMIFDATL = LOBYTE(d))
#define LCM_ReadData_16B()              MAKEWORD(LCMIFDATL, LCMIFDATH)

#define LCM_SetClockDivider(n)          WRITE_REG(LCMIFPSCR, (n))

/////////////////////////////////////////////////

#define I2SCR_FRF_MSK                   BIT4
#define I2S1_SetMOTOROLAFrame()         CLR_REG_BIT(I2SCR, I2SCR_FRF_MSK)
#define I2S1_SetTIFrame()               SET_REG_BIT(I2SCR, I2SCR_FRF_MSK)

#define I2SCR_TXDMAEN_MSK               BIT1
#define I2SCR_RXDMAEN_MSK               BIT0
#define I2S1_EnableTxDMA()              SET_REG_BIT(I2SCR, I2SCR_TXDMAEN_MSK)
#define I2S1_DisableTxDMA()             CLR_REG_BIT(I2SCR, I2SCR_TXDMAEN_MSK)
#define I2S1_EnableRxDMA()              SET_REG_BIT(I2SCR, I2SCR_RXDMAEN_MSK)
#define I2S1_DisableRxDMA()             CLR_REG_BIT(I2SCR, I2SCR_RXDMAEN_MSK)

#define I2SSR_FRE_MSK                   BIT6
#define I2SSR_BUY_MSK                   BIT5
#define I2SSR_OVR_MSK                   BIT4
#define I2SSR_UDR_MSK                   BIT3
#define I2SSR_CHSID_MSK                 BIT2
#define I2S1_CheckFREFlag()             READ_REG_BIT(I2SSR, I2SSR_FRE_MSK)
#define I2S1_CheckBUYFlag()             READ_REG_BIT(I2SSR, I2SSR_BUY_MSK)
#define I2S1_CheckOVRFlag()             READ_REG_BIT(I2SSR, I2SSR_OVR_MSK)
#define I2S1_CheckUDRFlag()             READ_REG_BIT(I2SSR, I2SSR_UDR_MSK)
#define I2S1_CheckCHSIDFlag()           READ_REG_BIT(I2SSR, I2SSR_CHSID_MSK)

#define I2S1_WriteData_16B(d)           (I2SDRH = HIBYTE(d), I2SDRL = LOBYTE(d))
#define I2S1_ReadData_16B()             MAKEWORD(I2SDRL, I2SDRH)

#define I2SPRH_MCKOE_MSK                BIT1
#define I2S1_EnableMCKOutput()          SET_REG_BIT(I2SPRH, I2SPRH_MCKOE_MSK)
#define I2S1_DisableMCKOutput()         CLR_REG_BIT(I2SPRH, I2SPRH_MCKOE_MSK)

#define I2SPRH_ODD_MSK                  BIT0
#define I2S1_SetClockDivider(n)         MODIFY_REG(I2SPRH, I2SPRH_ODD_MSK, ((n) << 0)); \
                                        I2SPRL = ((n) >> 1)

#define I2SCFGH_I2SE_MSK                BIT2
#define I2S1_Enable()                   SET_REG_BIT(I2SCFGH, I2SCFGH_I2SE_MSK)
#define I2S1_Disable()                  CLR_REG_BIT(I2SCFGH, I2SCFGH_I2SE_MSK)

#define I2SCFGH_MODE_MSK                (BIT1 | BIT0)
#define I2S1_SetMode(n)                 MODIFY_REG(I2SCFGH, I2SCFGH_MODE_MSK, ((n) << 0))
#define I2S1_SlaveSendMode()            I2S1_SetMode(0)
#define I2S1_SlaveReceiveMode()         I2S1_SetMode(1)
#define I2S1_MasterSendMode()           I2S1_SetMode(2)
#define I2S1_MasterReceiveMode()        I2S1_SetMode(3)

#define I2SCFGL_PCMSYNC_MSK             BIT7
#define I2S1_ShortFrameSync()           CLR_REG_BIT(I2SCFGL, I2SCFGL_PCMSYNC_MSK)
#define I2S1_LongFrameSync()            SET_REG_BIT(I2SCFGL, I2SCFGL_PCMSYNC_MSK)

#define I2SCFGL_STD_MSK                 (BIT5 | BIT4)
#define I2S1_SetStandard(n)             MODIFY_REG(I2SCFGL, I2SCFGL_STD_MSK, ((n) << 4))
#define I2S1_PhilipsStandard()          I2S1_SetStandard(0)
#define I2S1_LeftAlignStandard()        I2S1_SetStandard(1)
#define I2S1_RightAlignStandard()       I2S1_SetStandard(2)
#define I2S1_PCMStandard()              I2S1_SetStandard(3)

#define I2SCFGL_CKPOL_MSK               BIT3
#define I2S1_ClkNormalLow()             CLR_REG_BIT(I2SCFGL, I2SCFGL_CKPOL_MSK)
#define I2S1_ClkNormalHigh()            SET_REG_BIT(I2SCFGL, I2SCFGL_CKPOL_MSK)

#define I2SCFGL_DATLEN_MSK              (BIT2 | BIT1)
#define I2S1_SetDataLength(n)           MODIFY_REG(I2SCFGL, I2SCFGL_DATLEN_MSK, ((n) << 1))
#define I2S1_SetData16Bit()             I2S1_SetDataLength(0)
#define I2S1_SetData24Bit()             I2S1_SetDataLength(1)
#define I2S1_SetData32Bit()             I2S1_SetDataLength(2)

#define I2SCFGL_CHLEN_MSK               BIT0
#define I2S1_SetChannel16Bit()          CLR_REG_BIT(I2SCFGL, I2SCFGL_CHLEN_MSK)
#define I2S1_SetChannel32Bit()          SET_REG_BIT(I2SCFGL, I2SCFGL_CHLEN_MSK)

#define I2S1_SetMCKDivider(n)           WRITE_REG(I2SMCKDIV, (n))

////////////////////////

#define I2S2CR_FRF_MSK                  BIT4
#define I2S2_SetMOTOROLAFrame()         CLR_REG_BIT(I2S2CR, I2S2CR_FRF_MSK)
#define I2S2_SetTIFrame()               SET_REG_BIT(I2S2CR, I2S2CR_FRF_MSK)

#define I2S2CR_TXDMAEN_MSK              BIT1
#define I2S2CR_RXDMAEN_MSK              BIT0
#define I2S2_EnableTxDMA()              SET_REG_BIT(I2S2CR, I2S2CR_TXDMAEN_MSK)
#define I2S2_DisableTxDMA()             CLR_REG_BIT(I2S2CR, I2S2CR_TXDMAEN_MSK)
#define I2S2_EnableRxDMA()              SET_REG_BIT(I2S2CR, I2S2CR_RXDMAEN_MSK)
#define I2S2_DisableRxDMA()             CLR_REG_BIT(I2S2CR, I2S2CR_RXDMAEN_MSK)

#define I2S2SR_FRE_MSK                  BIT6
#define I2S2SR_BUY_MSK                  BIT5
#define I2S2SR_OVR_MSK                  BIT4
#define I2S2SR_UDR_MSK                  BIT3
#define I2S2SR_CHSID_MSK                BIT2
#define I2S2_CheckFREFlag()             READ_REG_BIT(I2S2SR, I2S2SR_FRE_MSK)
#define I2S2_CheckBUYFlag()             READ_REG_BIT(I2S2SR, I2S2SR_BUY_MSK)
#define I2S2_CheckOVRFlag()             READ_REG_BIT(I2S2SR, I2S2SR_OVR_MSK)
#define I2S2_CheckUDRFlag()             READ_REG_BIT(I2S2SR, I2S2SR_UDR_MSK)
#define I2S2_CheckCHSIDFlag()           READ_REG_BIT(I2S2SR, I2S2SR_CHSID_MSK)

#define I2S2_WriteData_16B(d)           (I2S2DRH = HIBYTE(d), I2S2DRL = LOBYTE(d))
#define I2S2_ReadData_16B()             MAKEWORD(I2S2DRL, I2S2DRH)

#define I2S2PRH_MCKOE_MSK               BIT1
#define I2S2_EnableMCKOutput()          SET_REG_BIT(I2S2PRH, I2S2PRH_MCKOE_MSK)
#define I2S2_DisableMCKOutput()         CLR_REG_BIT(I2S2PRH, I2S2PRH_MCKOE_MSK)

#define I2S2PRH_ODD_MSK                 BIT0
#define I2S2_SetClockDivider(n)         MODIFY_REG(I2S2PRH, I2S2PRH_ODD_MSK, ((n) << 0)); \
                                        I2S2PRL = ((n) >> 1)

#define I2S2CFGH_I2S2E_MSK              BIT2
#define I2S2_Enable()                   SET_REG_BIT(I2S2CFGH, I2S2CFGH_I2S2E_MSK)
#define I2S2_Disable()                  CLR_REG_BIT(I2S2CFGH, I2S2CFGH_I2S2E_MSK)

#define I2S2CFGH_MODE_MSK               (BIT1 | BIT0)
#define I2S2_SetMode(n)                 MODIFY_REG(I2S2CFGH, I2S2CFGH_MODE_MSK, ((n) << 0))
#define I2S2_SlaveSendMode()            I2S2_SetMode(0)
#define I2S2_SlaveReceiveMode()         I2S2_SetMode(1)
#define I2S2_MasterSendMode()           I2S2_SetMode(2)
#define I2S2_MasterReceiveMode()        I2S2_SetMode(3)

#define I2S2CFGL_PCMSYNC_MSK            BIT7
#define I2S2_ShortFrameSync()           CLR_REG_BIT(I2S2CFGL, I2S2CFGL_PCMSYNC_MSK)
#define I2S2_LongFrameSync()            SET_REG_BIT(I2S2CFGL, I2S2CFGL_PCMSYNC_MSK)

#define I2S2CFGL_STD_MSK                (BIT5 | BIT4)
#define I2S2_SetStandard(n)             MODIFY_REG(I2S2CFGL, I2S2CFGL_STD_MSK, ((n) << 4))
#define I2S2_PhilipsStandard()          I2S2_SetStandard(0)
#define I2S2_LeftAlignStandard()        I2S2_SetStandard(1)
#define I2S2_RightAlignStandard()       I2S2_SetStandard(2)
#define I2S2_PCMStandard()              I2S2_SetStandard(3)

#define I2S2CFGL_CKPOL_MSK              BIT3
#define I2S2_ClkNormalLow()             CLR_REG_BIT(I2S2CFGL, I2S2CFGL_CKPOL_MSK)
#define I2S2_ClkNormalHigh()            SET_REG_BIT(I2S2CFGL, I2S2CFGL_CKPOL_MSK)

#define I2S2CFGL_DATLEN_MSK             (BIT2 | BIT1)
#define I2S2_SetDataLength(n)           MODIFY_REG(I2S2CFGL, I2S2CFGL_DATLEN_MSK, ((n) << 1))
#define I2S2_SetData16Bit()             I2S2_SetDataLength(0)
#define I2S2_SetData24Bit()             I2S2_SetDataLength(1)
#define I2S2_SetData32Bit()             I2S2_SetDataLength(2)

#define I2S2CFGL_CHLEN_MSK              BIT0
#define I2S2_SetChannel16Bit()          CLR_REG_BIT(I2S2CFGL, I2S2CFGL_CHLEN_MSK)
#define I2S2_SetChannel32Bit()          SET_REG_BIT(I2S2CFGL, I2S2CFGL_CHLEN_MSK)

#define I2S2_SetMCKDivider(n)           WRITE_REG(I2S2MCKDIV, (n))

/////////////////////////////////////////////////

#define TFPU_CLK_SYSCLK()               WRITE_REG(DMAIR, (0x3e))
#define TFPU_CLK_HSIOCK()               WRITE_REG(DMAIR, (0x3f))

/////////////////////////////////////////////////

#define DMAUR1TCFG_UR1TPTY_MSK          (BIT1 | BIT0)
#define DMAUR2TCFG_UR2TPTY_MSK          (BIT1 | BIT0)
#define DMAUR3TCFG_UR3TPTY_MSK          (BIT1 | BIT0)
#define DMAUR4TCFG_UR4TPTY_MSK          (BIT1 | BIT0)
#define DMAUR5TCFG_UR5TPTY_MSK          (BIT1 | BIT0)
#define DMAUR6TCFG_UR6TPTY_MSK          (BIT1 | BIT0)
#define DMAUR7TCFG_UR7TPTY_MSK          (BIT1 | BIT0)
#define DMAUR8TCFG_UR8TPTY_MSK          (BIT1 | BIT0)
#define DMA_UART1_SetTxBusPriority(n)   MODIFY_REG(DMA_UR1T_CFG,  DMAUR1TCFG_UR1TPTY_MSK, ((n) << 0))
#define DMA_UART2_SetTxBusPriority(n)   MODIFY_REG(DMA_UR2T_CFG,  DMAUR2TCFG_UR2TPTY_MSK, ((n) << 0))
#define DMA_UART3_SetTxBusPriority(n)   MODIFY_REG(DMA_UR3T_CFG,  DMAUR3TCFG_UR3TPTY_MSK, ((n) << 0))
#define DMA_UART4_SetTxBusPriority(n)   MODIFY_REG(DMA_UR4T_CFG,  DMAUR4TCFG_UR4TPTY_MSK, ((n) << 0))
#define DMA_UART5_SetTxBusPriority(n)   MODIFY_REG(DMA_UR5T_CFG,  DMAUR5TCFG_UR5TPTY_MSK, ((n) << 0))
#define DMA_UART6_SetTxBusPriority(n)   MODIFY_REG(DMA_UR6T_CFG,  DMAUR6TCFG_UR6TPTY_MSK, ((n) << 0))
#define DMA_UART7_SetTxBusPriority(n)   MODIFY_REG(DMA_UR7T_CFG,  DMAUR7TCFG_UR7TPTY_MSK, ((n) << 0))
#define DMA_UART8_SetTxBusPriority(n)   MODIFY_REG(DMA_UR8T_CFG,  DMAUR8TCFG_UR8TPTY_MSK, ((n) << 0))

#define DMAUR1RCFG_UR1RPTY_MSK          (BIT1 | BIT0)
#define DMAUR2RCFG_UR2RPTY_MSK          (BIT1 | BIT0)
#define DMAUR3RCFG_UR3RPTY_MSK          (BIT1 | BIT0)
#define DMAUR4RCFG_UR4RPTY_MSK          (BIT1 | BIT0)
#define DMAUR5RCFG_UR5RPTY_MSK          (BIT1 | BIT0)
#define DMAUR6RCFG_UR6RPTY_MSK          (BIT1 | BIT0)
#define DMAUR7RCFG_UR7RPTY_MSK          (BIT1 | BIT0)
#define DMAUR8RCFG_UR8RPTY_MSK          (BIT1 | BIT0)
#define DMA_UART1_SetRxBusPriority(n)   MODIFY_REG(DMA_UR1R_CFG,  DMAUR1RCFG_UR1RPTY_MSK, ((n) << 0))
#define DMA_UART2_SetRxBusPriority(n)   MODIFY_REG(DMA_UR2R_CFG,  DMAUR2RCFG_UR2RPTY_MSK, ((n) << 0))
#define DMA_UART3_SetRxBusPriority(n)   MODIFY_REG(DMA_UR3R_CFG,  DMAUR3RCFG_UR3RPTY_MSK, ((n) << 0))
#define DMA_UART4_SetRxBusPriority(n)   MODIFY_REG(DMA_UR4R_CFG,  DMAUR4RCFG_UR4RPTY_MSK, ((n) << 0))
#define DMA_UART5_SetRxBusPriority(n)   MODIFY_REG(DMA_UR5R_CFG,  DMAUR5RCFG_UR5RPTY_MSK, ((n) << 0))
#define DMA_UART6_SetRxBusPriority(n)   MODIFY_REG(DMA_UR6R_CFG,  DMAUR6RCFG_UR6RPTY_MSK, ((n) << 0))
#define DMA_UART7_SetRxBusPriority(n)   MODIFY_REG(DMA_UR7R_CFG,  DMAUR7RCFG_UR7RPTY_MSK, ((n) << 0))
#define DMA_UART8_SetRxBusPriority(n)   MODIFY_REG(DMA_UR8R_CFG,  DMAUR8RCFG_UR8RPTY_MSK, ((n) << 0))

#define DMAUR1TCR_ENUR1T_MSK            BIT7
#define DMAUR2TCR_ENUR2T_MSK            BIT7
#define DMAUR3TCR_ENUR3T_MSK            BIT7
#define DMAUR4TCR_ENUR4T_MSK            BIT7
#define DMAUR5TCR_ENUR5T_MSK            BIT7
#define DMAUR6TCR_ENUR6T_MSK            BIT7
#define DMAUR7TCR_ENUR7T_MSK            BIT7
#define DMAUR8TCR_ENUR8T_MSK            BIT7
#define DMA_UART1_EnableTx()            SET_REG_BIT(DMA_UR1T_CR, DMAUR1TCR_ENUR1T_MSK)
#define DMA_UART2_EnableTx()            SET_REG_BIT(DMA_UR2T_CR, DMAUR2TCR_ENUR2T_MSK)
#define DMA_UART3_EnableTx()            SET_REG_BIT(DMA_UR3T_CR, DMAUR3TCR_ENUR3T_MSK)
#define DMA_UART4_EnableTx()            SET_REG_BIT(DMA_UR4T_CR, DMAUR4TCR_ENUR4T_MSK)
#define DMA_UART5_EnableTx()            SET_REG_BIT(DMA_UR5T_CR, DMAUR5TCR_ENUR5T_MSK)
#define DMA_UART6_EnableTx()            SET_REG_BIT(DMA_UR6T_CR, DMAUR6TCR_ENUR6T_MSK)
#define DMA_UART7_EnableTx()            SET_REG_BIT(DMA_UR7T_CR, DMAUR7TCR_ENUR7T_MSK)
#define DMA_UART8_EnableTx()            SET_REG_BIT(DMA_UR8T_CR, DMAUR8TCR_ENUR8T_MSK)
#define DMA_UART1_DisableTx()           CLR_REG_BIT(DMA_UR1T_CR, DMAUR1TCR_ENUR1T_MSK)
#define DMA_UART2_DisableTx()           CLR_REG_BIT(DMA_UR2T_CR, DMAUR2TCR_ENUR2T_MSK)
#define DMA_UART3_DisableTx()           CLR_REG_BIT(DMA_UR3T_CR, DMAUR3TCR_ENUR3T_MSK)
#define DMA_UART4_DisableTx()           CLR_REG_BIT(DMA_UR4T_CR, DMAUR4TCR_ENUR4T_MSK)
#define DMA_UART5_DisableTx()           CLR_REG_BIT(DMA_UR5T_CR, DMAUR5TCR_ENUR5T_MSK)
#define DMA_UART6_DisableTx()           CLR_REG_BIT(DMA_UR6T_CR, DMAUR6TCR_ENUR6T_MSK)
#define DMA_UART7_DisableTx()           CLR_REG_BIT(DMA_UR7T_CR, DMAUR7TCR_ENUR7T_MSK)
#define DMA_UART8_DisableTx()           CLR_REG_BIT(DMA_UR8T_CR, DMAUR8TCR_ENUR8T_MSK)

#define DMAUR1RCR_ENUR1R_MSK            BIT7
#define DMAUR2RCR_ENUR2R_MSK            BIT7
#define DMAUR3RCR_ENUR3R_MSK            BIT7
#define DMAUR4RCR_ENUR4R_MSK            BIT7
#define DMAUR5RCR_ENUR5R_MSK            BIT7
#define DMAUR6RCR_ENUR6R_MSK            BIT7
#define DMAUR7RCR_ENUR7R_MSK            BIT7
#define DMAUR8RCR_ENUR8R_MSK            BIT7
#define DMA_UART1_EnableRx()            SET_REG_BIT(DMA_UR1R_CR, DMAUR1RCR_ENUR1R_MSK)
#define DMA_UART2_EnableRx()            SET_REG_BIT(DMA_UR2R_CR, DMAUR2RCR_ENUR2R_MSK)
#define DMA_UART3_EnableRx()            SET_REG_BIT(DMA_UR3R_CR, DMAUR3RCR_ENUR3R_MSK)
#define DMA_UART4_EnableRx()            SET_REG_BIT(DMA_UR4R_CR, DMAUR4RCR_ENUR4R_MSK)
#define DMA_UART5_EnableRx()            SET_REG_BIT(DMA_UR5R_CR, DMAUR5RCR_ENUR5R_MSK)
#define DMA_UART6_EnableRx()            SET_REG_BIT(DMA_UR6R_CR, DMAUR6RCR_ENUR6R_MSK)
#define DMA_UART7_EnableRx()            SET_REG_BIT(DMA_UR7R_CR, DMAUR7RCR_ENUR7R_MSK)
#define DMA_UART8_EnableRx()            SET_REG_BIT(DMA_UR8R_CR, DMAUR8RCR_ENUR8R_MSK)
#define DMA_UART1_DisableRx()           CLR_REG_BIT(DMA_UR1R_CR, DMAUR1RCR_ENUR1R_MSK)
#define DMA_UART2_DisableRx()           CLR_REG_BIT(DMA_UR2R_CR, DMAUR2RCR_ENUR2R_MSK)
#define DMA_UART3_DisableRx()           CLR_REG_BIT(DMA_UR3R_CR, DMAUR3RCR_ENUR3R_MSK)
#define DMA_UART4_DisableRx()           CLR_REG_BIT(DMA_UR4R_CR, DMAUR4RCR_ENUR4R_MSK)
#define DMA_UART5_DisableRx()           CLR_REG_BIT(DMA_UR5R_CR, DMAUR5RCR_ENUR5R_MSK)
#define DMA_UART6_DisableRx()           CLR_REG_BIT(DMA_UR6R_CR, DMAUR6RCR_ENUR6R_MSK)
#define DMA_UART7_DisableRx()           CLR_REG_BIT(DMA_UR7R_CR, DMAUR7RCR_ENUR7R_MSK)
#define DMA_UART8_DisableRx()           CLR_REG_BIT(DMA_UR8R_CR, DMAUR8RCR_ENUR8R_MSK)

#define DMAUR1TCR_TRIG_MSK              BIT6
#define DMAUR2TCR_TRIG_MSK              BIT6
#define DMAUR3TCR_TRIG_MSK              BIT6
#define DMAUR4TCR_TRIG_MSK              BIT6
#define DMAUR5TCR_TRIG_MSK              BIT6
#define DMAUR6TCR_TRIG_MSK              BIT6
#define DMAUR7TCR_TRIG_MSK              BIT6
#define DMAUR8TCR_TRIG_MSK              BIT6
#define DMA_UART1_TriggerTx()           SET_REG_BIT(DMA_UR1T_CR, DMAUR1TCR_TRIG_MSK)
#define DMA_UART2_TriggerTx()           SET_REG_BIT(DMA_UR2T_CR, DMAUR2TCR_TRIG_MSK)
#define DMA_UART3_TriggerTx()           SET_REG_BIT(DMA_UR3T_CR, DMAUR3TCR_TRIG_MSK)
#define DMA_UART4_TriggerTx()           SET_REG_BIT(DMA_UR4T_CR, DMAUR4TCR_TRIG_MSK)
#define DMA_UART5_TriggerTx()           SET_REG_BIT(DMA_UR5T_CR, DMAUR5TCR_TRIG_MSK)
#define DMA_UART6_TriggerTx()           SET_REG_BIT(DMA_UR6T_CR, DMAUR6TCR_TRIG_MSK)
#define DMA_UART7_TriggerTx()           SET_REG_BIT(DMA_UR7T_CR, DMAUR7TCR_TRIG_MSK)
#define DMA_UART8_TriggerTx()           SET_REG_BIT(DMA_UR8T_CR, DMAUR8TCR_TRIG_MSK)

#define DMAUR1RCR_TRIG_MSK              BIT5
#define DMAUR2RCR_TRIG_MSK              BIT5
#define DMAUR3RCR_TRIG_MSK              BIT5
#define DMAUR4RCR_TRIG_MSK              BIT5
#define DMAUR5RCR_TRIG_MSK              BIT5
#define DMAUR6RCR_TRIG_MSK              BIT5
#define DMAUR7RCR_TRIG_MSK              BIT5
#define DMAUR8RCR_TRIG_MSK              BIT5
#define DMA_UART1_TriggerRx()           SET_REG_BIT(DMA_UR1R_CR, DMAUR1RCR_TRIG_MSK)
#define DMA_UART2_TriggerRx()           SET_REG_BIT(DMA_UR2R_CR, DMAUR2RCR_TRIG_MSK)
#define DMA_UART3_TriggerRx()           SET_REG_BIT(DMA_UR3R_CR, DMAUR3RCR_TRIG_MSK)
#define DMA_UART4_TriggerRx()           SET_REG_BIT(DMA_UR4R_CR, DMAUR4RCR_TRIG_MSK)
#define DMA_UART5_TriggerRx()           SET_REG_BIT(DMA_UR5R_CR, DMAUR5RCR_TRIG_MSK)
#define DMA_UART6_TriggerRx()           SET_REG_BIT(DMA_UR6R_CR, DMAUR6RCR_TRIG_MSK)
#define DMA_UART7_TriggerRx()           SET_REG_BIT(DMA_UR7R_CR, DMAUR7RCR_TRIG_MSK)
#define DMA_UART8_TriggerRx()           SET_REG_BIT(DMA_UR8R_CR, DMAUR8RCR_TRIG_MSK)

#define DMAUR1RCR_CLRFIFO_MSK           BIT0
#define DMAUR2RCR_CLRFIFO_MSK           BIT0
#define DMAUR3RCR_CLRFIFO_MSK           BIT0
#define DMAUR4RCR_CLRFIFO_MSK           BIT0
#define DMAUR5RCR_CLRFIFO_MSK           BIT0
#define DMAUR6RCR_CLRFIFO_MSK           BIT0
#define DMAUR7RCR_CLRFIFO_MSK           BIT0
#define DMAUR8RCR_CLRFIFO_MSK           BIT0
#define DMA_UART1_ClearFIFO()           SET_REG_BIT(DMA_UR1R_CR, DMAUR1RCR_CLRFIFO_MSK)
#define DMA_UART2_ClearFIFO()           SET_REG_BIT(DMA_UR2R_CR, DMAUR2RCR_CLRFIFO_MSK)
#define DMA_UART3_ClearFIFO()           SET_REG_BIT(DMA_UR3R_CR, DMAUR3RCR_CLRFIFO_MSK)
#define DMA_UART4_ClearFIFO()           SET_REG_BIT(DMA_UR4R_CR, DMAUR4RCR_CLRFIFO_MSK)
#define DMA_UART5_ClearFIFO()           SET_REG_BIT(DMA_UR5R_CR, DMAUR5RCR_CLRFIFO_MSK)
#define DMA_UART6_ClearFIFO()           SET_REG_BIT(DMA_UR6R_CR, DMAUR6RCR_CLRFIFO_MSK)
#define DMA_UART7_ClearFIFO()           SET_REG_BIT(DMA_UR7R_CR, DMAUR7RCR_CLRFIFO_MSK)
#define DMA_UART8_ClearFIFO()           SET_REG_BIT(DMA_UR8R_CR, DMAUR8RCR_CLRFIFO_MSK)

#define DMAUR1TSTA_TXOVW_MSK            BIT2
#define DMAUR2TSTA_TXOVW_MSK            BIT2
#define DMAUR3TSTA_TXOVW_MSK            BIT2
#define DMAUR4TSTA_TXOVW_MSK            BIT2
#define DMAUR5TSTA_TXOVW_MSK            BIT2
#define DMAUR6TSTA_TXOVW_MSK            BIT2
#define DMAUR7TSTA_TXOVW_MSK            BIT2
#define DMAUR8TSTA_TXOVW_MSK            BIT2
#define DMA_UART1_CheckOverWriteFlag()  READ_REG_BIT(DMA_UR1T_STA,  DMAUR1TSTA_TXOVW_MSK)
#define DMA_UART2_CheckOverWriteFlag()  READ_REG_BIT(DMA_UR2T_STA,  DMAUR2TSTA_TXOVW_MSK)
#define DMA_UART3_CheckOverWriteFlag()  READ_REG_BIT(DMA_UR3T_STA,  DMAUR3TSTA_TXOVW_MSK)
#define DMA_UART4_CheckOverWriteFlag()  READ_REG_BIT(DMA_UR4T_STA,  DMAUR4TSTA_TXOVW_MSK)
#define DMA_UART5_CheckOverWriteFlag()  READ_REG_BIT(DMA_UR5T_STA,  DMAUR5TSTA_TXOVW_MSK)
#define DMA_UART6_CheckOverWriteFlag()  READ_REG_BIT(DMA_UR6T_STA,  DMAUR6TSTA_TXOVW_MSK)
#define DMA_UART7_CheckOverWriteFlag()  READ_REG_BIT(DMA_UR7T_STA,  DMAUR7TSTA_TXOVW_MSK)
#define DMA_UART8_CheckOverWriteFlag()  READ_REG_BIT(DMA_UR8T_STA,  DMAUR8TSTA_TXOVW_MSK)
#define DMA_UART1_ClearOverWriteFlag()  CLR_REG_BIT(DMA_UR1T_STA,   DMAUR1TSTA_TXOVW_MSK)
#define DMA_UART2_ClearOverWriteFlag()  CLR_REG_BIT(DMA_UR2T_STA,   DMAUR2TSTA_TXOVW_MSK)
#define DMA_UART3_ClearOverWriteFlag()  CLR_REG_BIT(DMA_UR3T_STA,   DMAUR3TSTA_TXOVW_MSK)
#define DMA_UART4_ClearOverWriteFlag()  CLR_REG_BIT(DMA_UR4T_STA,   DMAUR4TSTA_TXOVW_MSK)
#define DMA_UART5_ClearOverWriteFlag()  CLR_REG_BIT(DMA_UR5T_STA,   DMAUR5TSTA_TXOVW_MSK)
#define DMA_UART6_ClearOverWriteFlag()  CLR_REG_BIT(DMA_UR6T_STA,   DMAUR6TSTA_TXOVW_MSK)
#define DMA_UART7_ClearOverWriteFlag()  CLR_REG_BIT(DMA_UR7T_STA,   DMAUR7TSTA_TXOVW_MSK)
#define DMA_UART8_ClearOverWriteFlag()  CLR_REG_BIT(DMA_UR8T_STA,   DMAUR8TSTA_TXOVW_MSK)

#define DMAUR1RSTA_RXLOSS_MSK           BIT1
#define DMAUR2RSTA_RXLOSS_MSK           BIT1
#define DMAUR3RSTA_RXLOSS_MSK           BIT1
#define DMAUR4RSTA_RXLOSS_MSK           BIT1
#define DMAUR5RSTA_RXLOSS_MSK           BIT1
#define DMAUR6RSTA_RXLOSS_MSK           BIT1
#define DMAUR7RSTA_RXLOSS_MSK           BIT1
#define DMAUR8RSTA_RXLOSS_MSK           BIT1
#define DMA_UART1_CheckRxLossFlag()     READ_REG_BIT(DMA_UR1R_STA,  DMAUR1RSTA_RXLOSS_MSK)
#define DMA_UART2_CheckRxLossFlag()     READ_REG_BIT(DMA_UR2R_STA,  DMAUR2RSTA_RXLOSS_MSK)
#define DMA_UART3_CheckRxLossFlag()     READ_REG_BIT(DMA_UR3R_STA,  DMAUR3RSTA_RXLOSS_MSK)
#define DMA_UART4_CheckRxLossFlag()     READ_REG_BIT(DMA_UR4R_STA,  DMAUR4RSTA_RXLOSS_MSK)
#define DMA_UART5_CheckRxLossFlag()     READ_REG_BIT(DMA_UR5R_STA,  DMAUR5RSTA_RXLOSS_MSK)
#define DMA_UART6_CheckRxLossFlag()     READ_REG_BIT(DMA_UR6R_STA,  DMAUR6RSTA_RXLOSS_MSK)
#define DMA_UART7_CheckRxLossFlag()     READ_REG_BIT(DMA_UR7R_STA,  DMAUR7RSTA_RXLOSS_MSK)
#define DMA_UART8_CheckRxLossFlag()     READ_REG_BIT(DMA_UR8R_STA,  DMAUR8RSTA_RXLOSS_MSK)
#define DMA_UART1_ClearRxLossFlag()     CLR_REG_BIT(DMA_UR1R_STA,   DMAUR1RSTA_RXLOSS_MSK)
#define DMA_UART2_ClearRxLossFlag()     CLR_REG_BIT(DMA_UR2R_STA,   DMAUR2RSTA_RXLOSS_MSK)
#define DMA_UART3_ClearRxLossFlag()     CLR_REG_BIT(DMA_UR3R_STA,   DMAUR3RSTA_RXLOSS_MSK)
#define DMA_UART4_ClearRxLossFlag()     CLR_REG_BIT(DMA_UR4R_STA,   DMAUR4RSTA_RXLOSS_MSK)
#define DMA_UART5_ClearRxLossFlag()     CLR_REG_BIT(DMA_UR5R_STA,   DMAUR5RSTA_RXLOSS_MSK)
#define DMA_UART6_ClearRxLossFlag()     CLR_REG_BIT(DMA_UR6R_STA,   DMAUR6RSTA_RXLOSS_MSK)
#define DMA_UART7_ClearRxLossFlag()     CLR_REG_BIT(DMA_UR7R_STA,   DMAUR7RSTA_RXLOSS_MSK)
#define DMA_UART8_ClearRxLossFlag()     CLR_REG_BIT(DMA_UR8R_STA,   DMAUR8RSTA_RXLOSS_MSK)

#define DMA_UART1_SetTxAmount(d)        (DMA_UR1T_AMTH = HIBYTE(d), DMA_UR1T_AMT = LOBYTE(d))
#define DMA_UART2_SetTxAmount(d)        (DMA_UR2T_AMTH = HIBYTE(d), DMA_UR2T_AMT = LOBYTE(d))
#define DMA_UART3_SetTxAmount(d)        (DMA_UR3T_AMTH = HIBYTE(d), DMA_UR3T_AMT = LOBYTE(d))
#define DMA_UART4_SetTxAmount(d)        (DMA_UR4T_AMTH = HIBYTE(d), DMA_UR4T_AMT = LOBYTE(d))
#define DMA_UART5_SetTxAmount(d)        (DMA_UR5T_AMTH = HIBYTE(d), DMA_UR5T_AMT = LOBYTE(d))
#define DMA_UART6_SetTxAmount(d)        (DMA_UR6T_AMTH = HIBYTE(d), DMA_UR6T_AMT = LOBYTE(d))
#define DMA_UART7_SetTxAmount(d)        (DMA_UR7T_AMTH = HIBYTE(d), DMA_UR7T_AMT = LOBYTE(d))
#define DMA_UART8_SetTxAmount(d)        (DMA_UR8T_AMTH = HIBYTE(d), DMA_UR8T_AMT = LOBYTE(d))

#define DMA_UART1_SetRxAmount(d)        (DMA_UR1R_AMTH = HIBYTE(d), DMA_UR1R_AMT = LOBYTE(d))
#define DMA_UART2_SetRxAmount(d)        (DMA_UR2R_AMTH = HIBYTE(d), DMA_UR2R_AMT = LOBYTE(d))
#define DMA_UART3_SetRxAmount(d)        (DMA_UR3R_AMTH = HIBYTE(d), DMA_UR3R_AMT = LOBYTE(d))
#define DMA_UART4_SetRxAmount(d)        (DMA_UR4R_AMTH = HIBYTE(d), DMA_UR4R_AMT = LOBYTE(d))
#define DMA_UART5_SetRxAmount(d)        (DMA_UR5R_AMTH = HIBYTE(d), DMA_UR5R_AMT = LOBYTE(d))
#define DMA_UART6_SetRxAmount(d)        (DMA_UR6R_AMTH = HIBYTE(d), DMA_UR6R_AMT = LOBYTE(d))
#define DMA_UART7_SetRxAmount(d)        (DMA_UR7R_AMTH = HIBYTE(d), DMA_UR7R_AMT = LOBYTE(d))
#define DMA_UART8_SetRxAmount(d)        (DMA_UR8R_AMTH = HIBYTE(d), DMA_UR8R_AMT = LOBYTE(d))

#define DMA_UART1_ReadTxDone()          MAKEWORD(DMA_UR1T_DONE, DMA_UR1T_DONEH)
#define DMA_UART2_ReadTxDone()          MAKEWORD(DMA_UR2T_DONE, DMA_UR2T_DONEH)
#define DMA_UART3_ReadTxDone()          MAKEWORD(DMA_UR3T_DONE, DMA_UR3T_DONEH)
#define DMA_UART4_ReadTxDone()          MAKEWORD(DMA_UR4T_DONE, DMA_UR4T_DONEH)
#define DMA_UART5_ReadTxDone()          MAKEWORD(DMA_UR5T_DONE, DMA_UR5T_DONEH)
#define DMA_UART6_ReadTxDone()          MAKEWORD(DMA_UR6T_DONE, DMA_UR6T_DONEH)
#define DMA_UART7_ReadTxDone()          MAKEWORD(DMA_UR7T_DONE, DMA_UR7T_DONEH)
#define DMA_UART8_ReadTxDone()          MAKEWORD(DMA_UR8T_DONE, DMA_UR8T_DONEH)

#define DMA_UART1_ReadRxDone()          MAKEWORD(DMA_UR1R_DONE, DMA_UR1R_DONEH)
#define DMA_UART2_ReadRxDone()          MAKEWORD(DMA_UR2R_DONE, DMA_UR2R_DONEH)
#define DMA_UART3_ReadRxDone()          MAKEWORD(DMA_UR3R_DONE, DMA_UR3R_DONEH)
#define DMA_UART4_ReadRxDone()          MAKEWORD(DMA_UR4R_DONE, DMA_UR4R_DONEH)
#define DMA_UART5_ReadRxDone()          MAKEWORD(DMA_UR5R_DONE, DMA_UR5R_DONEH)
#define DMA_UART6_ReadRxDone()          MAKEWORD(DMA_UR6R_DONE, DMA_UR6R_DONEH)
#define DMA_UART7_ReadRxDone()          MAKEWORD(DMA_UR7R_DONE, DMA_UR7R_DONEH)
#define DMA_UART8_ReadRxDone()          MAKEWORD(DMA_UR8R_DONE, DMA_UR8R_DONEH)

#define DMA_UART1_SetTxAddress(d)       (DMA_UR1T_TXAH = HIBYTE(d), DMA_UR1T_TXAL = LOBYTE(d))
#define DMA_UART2_SetTxAddress(d)       (DMA_UR2T_TXAH = HIBYTE(d), DMA_UR2T_TXAL = LOBYTE(d))
#define DMA_UART3_SetTxAddress(d)       (DMA_UR3T_TXAH = HIBYTE(d), DMA_UR3T_TXAL = LOBYTE(d))
#define DMA_UART4_SetTxAddress(d)       (DMA_UR4T_TXAH = HIBYTE(d), DMA_UR4T_TXAL = LOBYTE(d))
#define DMA_UART5_SetTxAddress(d)       (DMA_UR5T_TXAH = HIBYTE(d), DMA_UR5T_TXAL = LOBYTE(d))
#define DMA_UART6_SetTxAddress(d)       (DMA_UR6T_TXAH = HIBYTE(d), DMA_UR6T_TXAL = LOBYTE(d))
#define DMA_UART7_SetTxAddress(d)       (DMA_UR7T_TXAH = HIBYTE(d), DMA_UR7T_TXAL = LOBYTE(d))
#define DMA_UART8_SetTxAddress(d)       (DMA_UR8T_TXAH = HIBYTE(d), DMA_UR8T_TXAL = LOBYTE(d))

#define DMA_UART1_SetRxAddress(d)       (DMA_UR1R_RXAH = HIBYTE(d), DMA_UR1R_RXAL = LOBYTE(d))
#define DMA_UART2_SetRxAddress(d)       (DMA_UR2R_RXAH = HIBYTE(d), DMA_UR2R_RXAL = LOBYTE(d))
#define DMA_UART3_SetRxAddress(d)       (DMA_UR3R_RXAH = HIBYTE(d), DMA_UR3R_RXAL = LOBYTE(d))
#define DMA_UART4_SetRxAddress(d)       (DMA_UR4R_RXAH = HIBYTE(d), DMA_UR4R_RXAL = LOBYTE(d))
#define DMA_UART5_SetRxAddress(d)       (DMA_UR5R_RXAH = HIBYTE(d), DMA_UR5R_RXAL = LOBYTE(d))
#define DMA_UART6_SetRxAddress(d)       (DMA_UR6R_RXAH = HIBYTE(d), DMA_UR6R_RXAL = LOBYTE(d))
#define DMA_UART7_SetRxAddress(d)       (DMA_UR7R_RXAH = HIBYTE(d), DMA_UR7R_RXAL = LOBYTE(d))
#define DMA_UART8_SetRxAddress(d)       (DMA_UR8R_RXAH = HIBYTE(d), DMA_UR8R_RXAL = LOBYTE(d))

#define DMA_UART1_SetInterval(d)        (DMA_UR1_ITVH = HIBYTE(d), DMA_UR1_ITVL = LOBYTE(d))
#define DMA_UART2_SetInterval(d)        (DMA_UR2_ITVH = HIBYTE(d), DMA_UR2_ITVL = LOBYTE(d))
#define DMA_UART3_SetInterval(d)        (DMA_UR3_ITVH = HIBYTE(d), DMA_UR3_ITVL = LOBYTE(d))
#define DMA_UART4_SetInterval(d)        (DMA_UR4_ITVH = HIBYTE(d), DMA_UR4_ITVL = LOBYTE(d))
#define DMA_UART5_SetInterval(d)        (DMA_UR5_ITVH = HIBYTE(d), DMA_UR5_ITVL = LOBYTE(d))
#define DMA_UART6_SetInterval(d)        (DMA_UR6_ITVH = HIBYTE(d), DMA_UR6_ITVL = LOBYTE(d))
#define DMA_UART7_SetInterval(d)        (DMA_UR7_ITVH = HIBYTE(d), DMA_UR7_ITVL = LOBYTE(d))
#define DMA_UART8_SetInterval(d)        (DMA_UR8_ITVH = HIBYTE(d), DMA_UR8_ITVL = LOBYTE(d))

/////////////////////////////////////////////////

#define DMAADCCFG_ADCPTY_MSK            (BIT1 | BIT0)
#define DMA_ADC1_SetBusPriority(n)      MODIFY_REG(DMA_ADC_CFG,  DMAADCCFG_ADCPTY_MSK, ((n) << 0))

#define DMAADCCR_ENADC_MSK              BIT7
#define DMA_ADC1_Enable()               SET_REG_BIT(DMA_ADC_CR, DMAADCCR_ENADC_MSK)
#define DMA_ADC1_Disable()              CLR_REG_BIT(DMA_ADC_CR, DMAADCCR_ENADC_MSK)

#define DMAADCCR_TRIG_MSK               BIT6
#define DMA_ADC1_Trigger()              SET_REG_BIT(DMA_ADC_CR, DMAADCCR_TRIG_MSK)

#define DMA_ADC1_SetAmount(d)           (DMA_ADC_AMTH = HIBYTE(d), DMA_ADC_AMT = LOBYTE(d))
#define DMA_ADC1_ReadDone()             MAKEWORD(DMA_ADC_DONE, DMA_ADC_DONEH)
#define DMA_ADC1_SetAddress(d)          (DMA_ADC_RXAH = HIBYTE(d), DMA_ADC_RXAL = LOBYTE(d))
#define DMA_ADC1_SetInterval(d)         (DMA_ADC_ITVH = HIBYTE(d), DMA_ADC_ITVL = LOBYTE(d))
#define DMA_ADC1_SetChannels(d)         (DMA_ADC_CHSW1 = HIBYTE(d), DMA_ADC_CHSW0 = LOBYTE(d))

#define DMAADCCFG2_CVTIMES_MSK          (BIT_LN)
#define DAM_ADC1_SetRepeatTimes(n)      MODIFY_REG(DMA_ADC_CFG2,  DMAADCCFG2_CVTIMES_MSK, ((n) << 0))
#define DMA_ADC1_DisableRepeatConv()    DAM_ADC1_SetRepeatTimes(0)
#define DMA_ADC1_SetRepeat2Times()      DAM_ADC1_SetRepeatTimes(8)
#define DMA_ADC1_SetRepeat4Times()      DAM_ADC1_SetRepeatTimes(9)
#define DMA_ADC1_SetRepeat8Times()      DAM_ADC1_SetRepeatTimes(10)
#define DMA_ADC1_SetRepeat16Times()     DAM_ADC1_SetRepeatTimes(11)
#define DMA_ADC1_SetRepeat32Times()     DAM_ADC1_SetRepeatTimes(12)
#define DMA_ADC1_SetRepeat64Times()     DAM_ADC1_SetRepeatTimes(13)
#define DMA_ADC1_SetRepeat128Times()    DAM_ADC1_SetRepeatTimes(14)
#define DMA_ADC1_SetRepeat256Times()    DAM_ADC1_SetRepeatTimes(15)

////////////////////////

#define DMAADC2CFG_ADCPTY_MSK           (BIT1 | BIT0)
#define DMA_ADC2_SetBusPriority(n)      MODIFY_REG(DMA_ADC2_CFG,  DMAADC2CFG_ADCPTY_MSK, ((n) << 0))

#define DMAADC2CR_ENADC_MSK             BIT7
#define DMA_ADC2_Enable()               SET_REG_BIT(DMA_ADC2_CR, DMAADC2CR_ENADC_MSK)
#define DMA_ADC2_Disable()              CLR_REG_BIT(DMA_ADC2_CR, DMAADC2CR_ENADC_MSK)

#define DMAADC2CR_TRIG_MSK              BIT6
#define DMA_ADC2_Trigger()              SET_REG_BIT(DMA_ADC2_CR, DMAADC2CR_TRIG_MSK)

#define DMA_ADC2_SetAmount(d)           (DMA_ADC2_AMTH = HIBYTE(d), DMA_ADC2_AMT = LOBYTE(d))
#define DMA_ADC2_ReadDone()             MAKEWORD(DMA_ADC2_DONE, DMA_ADC2_DONEH)
#define DMA_ADC2_SetAddress(d)          (DMA_ADC2_RXAH = HIBYTE(d), DMA_ADC2_RXAL = LOBYTE(d))
#define DMA_ADC2_SetInterval(d)         (DMA_ADC2_ITVH = HIBYTE(d), DMA_ADC2_ITVL = LOBYTE(d))
#define DMA_ADC2_SetChannels(d)         (DMA_ADC2_CHSW1 = HIBYTE(d), DMA_ADC2_CHSW0 = LOBYTE(d))

#define DMAADC2CFG2_CVTIMES_MSK         (BIT_LN)
#define DAM_ADC2_SetRepeatTimes(n)      MODIFY_REG(DMA_ADC2_CFG2,  DMAADC2CFG2_CVTIMES_MSK, ((n) << 0))
#define DMA_ADC2_DisableRepeatConv()    DAM_ADC2_SetRepeatTimes(0)
#define DMA_ADC2_SetRepeat2Times()      DAM_ADC2_SetRepeatTimes(8)
#define DMA_ADC2_SetRepeat4Times()      DAM_ADC2_SetRepeatTimes(9)
#define DMA_ADC2_SetRepeat8Times()      DAM_ADC2_SetRepeatTimes(10)
#define DMA_ADC2_SetRepeat16Times()     DAM_ADC2_SetRepeatTimes(11)
#define DMA_ADC2_SetRepeat32Times()     DAM_ADC2_SetRepeatTimes(12)
#define DMA_ADC2_SetRepeat64Times()     DAM_ADC2_SetRepeatTimes(13)
#define DMA_ADC2_SetRepeat128Times()    DAM_ADC2_SetRepeatTimes(14)
#define DMA_ADC2_SetRepeat256Times()    DAM_ADC2_SetRepeatTimes(15)

/////////////////////////////////////////////////

#define DMASPICFG_ACTTX_MSK             BIT6
#define DMASPICFG_ACTRX_MSK             BIT5
#define DMA_SPI1_EnableTx()             SET_REG_BIT(DMA_SPI_CFG, DMASPICFG_ACTTX_MSK)
#define DMA_SPI1_DisableTx()            CLR_REG_BIT(DMA_SPI_CFG, DMASPICFG_ACTTX_MSK)
#define DMA_SPI1_EnableRx()             SET_REG_BIT(DMA_SPI_CFG, DMASPICFG_ACTRX_MSK)
#define DMA_SPI1_DisableRx()            CLR_REG_BIT(DMA_SPI_CFG, DMASPICFG_ACTRX_MSK)

#define DMASPICFG_SPIPTY_MSK            (BIT1 | BIT0)
#define DMA_SPI1_SetBusPriority(n)      MODIFY_REG(DMA_SPI_CFG,  DMASPICFG_SPIPTY_MSK, ((n) << 0))

#define DMASPICFG2_WRPSS_MSK            BIT2
#define DMA_SPI1_AutoSS()               SET_REG_BIT(DMA_SPI_CFG2, DMASPICFG2_WRPSS_MSK)
#define DMA_SPI1_ManualSS()             CLR_REG_BIT(DMA_SPI_CFG2, DMASPICFG2_WRPSS_MSK)

#define DMASPICFG2_SSS_MSK              (BIT1 | BIT0)
#define DMA_SPI1_SetAutoSSPort(n)       MODIFY_REG(DMA_SPI_CFG2,  DMASPICFG2_SSS_MSK, ((n) << 0))
#define DMA_SPI1_SetAutoSSP12()         DMA_SPI1_SetAutoSSPort(0)
#define DMA_SPI1_SetAutoSSP22()         DMA_SPI1_SetAutoSSPort(1)
#define DMA_SPI1_SetAutoSSP54()         DMA_SPI1_SetAutoSSPort(2)
#define DMA_SPI1_SetAutoSSP35()         DMA_SPI1_SetAutoSSPort(3)

#define DMASPICR_ENSPI_MSK              BIT7
#define DMA_SPI1_Enable()               SET_REG_BIT(DMA_SPI_CR, DMASPICR_ENSPI_MSK)
#define DMA_SPI1_Disable()              CLR_REG_BIT(DMA_SPI_CR, DMASPICR_ENSPI_MSK)

#define DMASPICR_TRIGM_MSK              BIT6
#define DMASPICR_TRIGS_MSK              BIT5
#define DMA_SPI1_MasterTrigger()        SET_REG_BIT(DMA_SPI_CR, DMASPICR_TRIGM_MSK)
#define DMA_SPI1_SlaveTrigger()         SET_REG_BIT(DMA_SPI_CR, DMASPICR_TRIGS_MSK)

#define DMASPICR_CLRFIFO_MSK            BIT0
#define DMA_SPI1_ClearFIFO()            SET_REG_BIT(DMA_SPI_CR, DMASPICR_CLRFIFO_MSK)

#define DMASPISTA_TXOVW_MSK             BIT2
#define DMASPISTA_RXLOSS_MSK            BIT1
#define DMA_SPI1_CheckOverWriteFlag()   READ_REG_BIT(DMA_SPI_STA,  DMASPISTA_TXOVW_MSK)
#define DMA_SPI1_ClearOverWriteFlag()   CLR_REG_BIT(DMA_SPI_STA,   DMASPISTA_TXOVW_MSK)
#define DMA_SPI1_CheckRxLossFlag()      READ_REG_BIT(DMA_SPI_STA,  DMASPISTA_RXLOSS_MSK)
#define DMA_SPI1_ClearRxLossFlag()      CLR_REG_BIT(DMA_SPI_STA,   DMASPISTA_RXLOSS_MSK)

#define DMA_SPI1_SetAmount(d)           (DMA_SPI_AMTH = HIBYTE(d), DMA_SPI_AMT = LOBYTE(d))
#define DMA_SPI1_ReadDone()             MAKEWORD(DMA_SPI_DONE, DMA_SPI_DONEH)
#define DMA_SPI1_SetTxAddress(d)        (DMA_SPI_TXAH = HIBYTE(d), DMA_SPI_TXAL = LOBYTE(d))
#define DMA_SPI1_SetRxAddress(d)        (DMA_SPI_RXAH = HIBYTE(d), DMA_SPI_RXAL = LOBYTE(d))
#define DMA_SPI1_SetInterval(d)         (DMA_SPI_ITVH = HIBYTE(d), DMA_SPI_ITVL = LOBYTE(d))

////////////////////////

#define DMASPI2CFG_ACTTX_MSK            BIT6
#define DMASPI2CFG_ACTRX_MSK            BIT5
#define DMA_SPI2_EnableTx()             SET_REG_BIT(DMA_SPI2_CFG, DMASPI2CFG_ACTTX_MSK)
#define DMA_SPI2_DisableTx()            CLR_REG_BIT(DMA_SPI2_CFG, DMASPI2CFG_ACTTX_MSK)
#define DMA_SPI2_EnableRx()             SET_REG_BIT(DMA_SPI2_CFG, DMASPI2CFG_ACTRX_MSK)
#define DMA_SPI2_DisableRx()            CLR_REG_BIT(DMA_SPI2_CFG, DMASPI2CFG_ACTRX_MSK)

#define DMASPI2CFG_SPIPTY_MSK           (BIT1 | BIT0)
#define DMA_SPI2_SetBusPriority(n)      MODIFY_REG(DMA_SPI2_CFG,  DMASPI2CFG_SPIPTY_MSK, ((n) << 0))

#define DMASPI2CFG2_WRPSS_MSK           BIT2
#define DMA_SPI2_AutoSS()               SET_REG_BIT(DMA_SPI2_CFG2, DMASPI2CFG2_WRPSS_MSK)
#define DMA_SPI2_ManualSS()             CLR_REG_BIT(DMA_SPI2_CFG2, DMASPI2CFG2_WRPSS_MSK)

#define DMASPI2CFG2_SSS_MSK             (BIT1 | BIT0)
#define DMA_SPI2_SetAutoSSPort(n)       MODIFY_REG(DMA_SPI2_CFG2,  DMASPI2CFG2_SSS_MSK, ((n) << 0))
#define DMA_SPI2_SetAutoSSP64()         DMA_SPI2_SetAutoSSPort(0)
#define DMA_SPI2_SetAutoSSP02()         DMA_SPI2_SetAutoSSPort(1)
#define DMA_SPI2_SetAutoSSPB1()         DMA_SPI2_SetAutoSSPort(2)
#define DMA_SPI2_SetAutoSSP80()         DMA_SPI2_SetAutoSSPort(3)

#define DMASPI2CR_ENSPI_MSK             BIT7
#define DMA_SPI2_Enable()               SET_REG_BIT(DMA_SPI2_CR, DMASPI2CR_ENSPI_MSK)
#define DMA_SPI2_Disable()              CLR_REG_BIT(DMA_SPI2_CR, DMASPI2CR_ENSPI_MSK)

#define DMASPI2CR_TRIGM_MSK             BIT6
#define DMASPI2CR_TRIGS_MSK             BIT5
#define DMA_SPI2_MasterTrigger()        SET_REG_BIT(DMA_SPI2_CR, DMASPI2CR_TRIGM_MSK)
#define DMA_SPI2_SlaveTrigger()         SET_REG_BIT(DMA_SPI2_CR, DMASPI2CR_TRIGS_MSK)

#define DMASPI2CR_CLRFIFO_MSK           BIT0
#define DMA_SPI2_ClearFIFO()            SET_REG_BIT(DMA_SPI2_CR, DMASPI2CR_CLRFIFO_MSK)

#define DMASPI2STA_TXOVW_MSK            BIT2
#define DMASPI2STA_RXLOSS_MSK           BIT1
#define DMA_SPI2_CheckOverWriteFlag()   READ_REG_BIT(DMA_SPI2_STA,  DMASPI2STA_TXOVW_MSK)
#define DMA_SPI2_ClearOverWriteFlag()   CLR_REG_BIT(DMA_SPI2_STA,   DMASPI2STA_TXOVW_MSK)
#define DMA_SPI2_CheckRxLossFlag()      READ_REG_BIT(DMA_SPI2_STA,  DMASPI2STA_RXLOSS_MSK)
#define DMA_SPI2_ClearRxLossFlag()      CLR_REG_BIT(DMA_SPI2_STA,   DMASPI2STA_RXLOSS_MSK)

#define DMA_SPI2_SetAmount(d)           (DMA_SPI2_AMTH = HIBYTE(d), DMA_SPI2_AMT = LOBYTE(d))
#define DMA_SPI2_ReadDone()             MAKEWORD(DMA_SPI2_DONE, DMA_SPI2_DONEH)
#define DMA_SPI2_SetTxAddress(d)        (DMA_SPI2_TXAH = HIBYTE(d), DMA_SPI2_TXAL = LOBYTE(d))
#define DMA_SPI2_SetRxAddress(d)        (DMA_SPI2_RXAH = HIBYTE(d), DMA_SPI2_RXAL = LOBYTE(d))
#define DMA_SPI2_SetInterval(d)         (DMA_SPI2_ITVH = HIBYTE(d), DMA_SPI2_ITVL = LOBYTE(d))

////////////////////////

#define DMASPI3CFG_ACTTX_MSK            BIT6
#define DMASPI3CFG_ACTRX_MSK            BIT5
#define DMA_SPI3_EnableTx()             SET_REG_BIT(DMA_SPI3_CFG, DMASPI3CFG_ACTTX_MSK)
#define DMA_SPI3_DisableTx()            CLR_REG_BIT(DMA_SPI3_CFG, DMASPI3CFG_ACTTX_MSK)
#define DMA_SPI3_EnableRx()             SET_REG_BIT(DMA_SPI3_CFG, DMASPI3CFG_ACTRX_MSK)
#define DMA_SPI3_DisableRx()            CLR_REG_BIT(DMA_SPI3_CFG, DMASPI3CFG_ACTRX_MSK)

#define DMASPI3CFG_SPIPTY_MSK           (BIT1 | BIT0)
#define DMA_SPI3_SetBusPriority(n)      MODIFY_REG(DMA_SPI3_CFG,  DMASPI3CFG_SPIPTY_MSK, ((n) << 0))

#define DMASPI3CFG2_WRPSS_MSK           BIT2
#define DMA_SPI3_AutoSS()               SET_REG_BIT(DMA_SPI3_CFG2, DMASPI3CFG2_WRPSS_MSK)
#define DMA_SPI3_ManualSS()             CLR_REG_BIT(DMA_SPI3_CFG2, DMASPI3CFG2_WRPSS_MSK)

#define DMASPI3CFG2_SSS_MSK             (BIT1 | BIT0)
#define DMA_SPI3_SetAutoSSPort(n)       MODIFY_REG(DMA_SPI3_CFG2,  DMASPI3CFG2_SSS_MSK, ((n) << 0))
#define DMA_SPI3_SetAutoSSP22()         DMA_SPI3_SetAutoSSPort(0)
#define DMA_SPI3_SetAutoSSP70()         DMA_SPI3_SetAutoSSPort(1)
#define DMA_SPI3_SetAutoSSP84()         DMA_SPI3_SetAutoSSPort(2)
#define DMA_SPI3_SetAutoSSP90()         DMA_SPI3_SetAutoSSPort(3)

#define DMASPI3CR_ENSPI_MSK             BIT7
#define DMA_SPI3_Enable()               SET_REG_BIT(DMA_SPI3_CR, DMASPI3CR_ENSPI_MSK)
#define DMA_SPI3_Disable()              CLR_REG_BIT(DMA_SPI3_CR, DMASPI3CR_ENSPI_MSK)

#define DMASPI3CR_TRIGM_MSK             BIT6
#define DMASPI3CR_TRIGS_MSK             BIT5
#define DMA_SPI3_MasterTrigger()        SET_REG_BIT(DMA_SPI3_CR, DMASPI3CR_TRIGM_MSK)
#define DMA_SPI3_SlaveTrigger()         SET_REG_BIT(DMA_SPI3_CR, DMASPI3CR_TRIGS_MSK)

#define DMASPI3CR_CLRFIFO_MSK           BIT0
#define DMA_SPI3_ClearFIFO()            SET_REG_BIT(DMA_SPI3_CR, DMASPI3CR_CLRFIFO_MSK)

#define DMASPI3STA_TXOVW_MSK            BIT2
#define DMASPI3STA_RXLOSS_MSK           BIT1
#define DMA_SPI3_CheckOverWriteFlag()   READ_REG_BIT(DMA_SPI3_STA,  DMASPI3STA_TXOVW_MSK)
#define DMA_SPI3_ClearOverWriteFlag()   CLR_REG_BIT(DMA_SPI3_STA,   DMASPI3STA_TXOVW_MSK)
#define DMA_SPI3_CheckRxLossFlag()      READ_REG_BIT(DMA_SPI3_STA,  DMASPI3STA_RXLOSS_MSK)
#define DMA_SPI3_ClearRxLossFlag()      CLR_REG_BIT(DMA_SPI3_STA,   DMASPI3STA_RXLOSS_MSK)

#define DMA_SPI3_SetAmount(d)           (DMA_SPI3_AMTH = HIBYTE(d), DMA_SPI3_AMT = LOBYTE(d))
#define DMA_SPI3_ReadDone()             MAKEWORD(DMA_SPI3_DONE, DMA_SPI3_DONEH)
#define DMA_SPI3_SetTxAddress(d)        (DMA_SPI3_TXAH = HIBYTE(d), DMA_SPI3_TXAL = LOBYTE(d))
#define DMA_SPI3_SetRxAddress(d)        (DMA_SPI3_RXAH = HIBYTE(d), DMA_SPI3_RXAL = LOBYTE(d))
#define DMA_SPI3_SetInterval(d)         (DMA_SPI3_ITVH = HIBYTE(d), DMA_SPI3_ITVL = LOBYTE(d))

/////////////////////////////////////////////////

#define DMALCMCFG_LCMPTY_MSK            (BIT1 | BIT0)
#define DMA_LCM_SetBusPriority(n)       MODIFY_REG(DMA_LCM_CFG,  DMALCMCFG_LCMPTY_MSK, ((n) << 0))

#define DMALCMCR_ENLCM_MSK              BIT7
#define DMA_LCM_Enable()                SET_REG_BIT(DMA_LCM_CR, DMALCMCR_ENLCM_MSK)
#define DMA_LCM_Disable()               CLR_REG_BIT(DMA_LCM_CR, DMALCMCR_ENLCM_MSK)

#define DMALCMCR_TRIGWC_MSK             BIT6
#define DMALCMCR_TRIGWD_MSK             BIT5
#define DMALCMCR_TRIGRC_MSK             BIT4
#define DMALCMCR_TRIGRD_MSK             BIT3
#define DMA_LCM_TriggerWriteCommand()   SET_REG_BIT(DMA_LCM_CR, DMALCMCR_TRIGWC_MSK)
#define DMA_LCM_TriggerWriteData()      SET_REG_BIT(DMA_LCM_CR, DMALCMCR_TRIGWD_MSK)
#define DMA_LCM_TriggerReadStatus()     SET_REG_BIT(DMA_LCM_CR, DMALCMCR_TRIGRC_MSK)
#define DMA_LCM_TriggerReadData()       SET_REG_BIT(DMA_LCM_CR, DMALCMCR_TRIGRD_MSK)

#define DMALCMSTA_TXOVW_MSK             BIT1
#define DMA_LCM_CheckOverWriteFlag()    READ_REG_BIT(DMA_LCM_STA,  DMALCMSTA_TXOVW_MSK)
#define DMA_LCM_ClearOverWriteFlag()    CLR_REG_BIT(DMA_LCM_STA,   DMALCMSTA_TXOVW_MSK)

#define DMA_LCM_SetAmount(d)            (DMA_LCM_AMTH = HIBYTE(d), DMA_LCM_AMT = LOBYTE(d))
#define DMA_LCM_ReadDone()              MAKEWORD(DMA_LCM_DONE, DMA_LCM_DONEH)
#define DMA_LCM_SetTxAddress(d)         (DMA_LCM_TXAH = HIBYTE(d), DMA_LCM_TXAL = LOBYTE(d))
#define DMA_LCM_SetRxAddress(d)         (DMA_LCM_RXAH = HIBYTE(d), DMA_LCM_RXAL = LOBYTE(d))
#define DMA_LCM_SetInterval(d)          (DMA_LCM_ITVH = HIBYTE(d), DMA_LCM_ITVL = LOBYTE(d))

/////////////////////////////////////////////////

#define DMAI2CTCFG_I2CTPTY_MSK          (BIT1 | BIT0)
#define DMAI2CRCFG_I2CRPTY_MSK          (BIT1 | BIT0)
#define DMA_I2C1_SetTxBusPriority(n)    MODIFY_REG(DMA_I2CT_CFG,  DMAI2CTCFG_I2CTPTY_MSK, ((n) << 0))
#define DMA_I2C1_SetRxBusPriority(n)    MODIFY_REG(DMA_I2CR_CFG,  DMAI2CRCFG_I2CRPTY_MSK, ((n) << 0))

#define DMAI2CTCR_ENI2CT_MSK            BIT7
#define DMAI2CRCR_ENI2CR_MSK            BIT7
#define DMA_I2C1_EnableTx()             SET_REG_BIT(DMA_I2CT_CR, DMAI2CTCR_ENI2CT_MSK)
#define DMA_I2C1_DisableTx()            CLR_REG_BIT(DMA_I2CT_CR, DMAI2CTCR_ENI2CT_MSK)
#define DMA_I2C1_EnableRx()             SET_REG_BIT(DMA_I2CR_CR, DMAI2CRCR_ENI2CR_MSK)
#define DMA_I2C1_DisableRx()            CLR_REG_BIT(DMA_I2CR_CR, DMAI2CRCR_ENI2CR_MSK)

#define DMAI2CTCR_TRIG_MSK              BIT6
#define DMAI2CRCR_TRIG_MSK              BIT6
#define DMA_I2C1_TriggerTx()            SET_REG_BIT(DMA_I2CT_CR, DMAI2CTCR_TRIG_MSK)
#define DMA_I2C1_TriggerRx()            SET_REG_BIT(DMA_I2CR_CR, DMAI2CRCR_TRIG_MSK)

#define DMAI2CRCR_CLRFIFO_MSK           BIT0
#define DMA_I2C1_ClearFIFO()            SET_REG_BIT(DMA_I2CR_CR, DMAI2CRCR_CLRFIFO_MSK)

#define DMAI2CTSTA_TXOVW_MSK            BIT2
#define DMA_I2C1_CheckOverWriteFlag()   READ_REG_BIT(DMA_I2CT_STA,  DMAI2CTSTA_TXOVW_MSK)
#define DMA_I2C1_ClearOverWriteFlag()   CLR_REG_BIT(DMA_I2CT_STA,   DMAI2CTSTA_TXOVW_MSK)

#define DMAI2CRSTA_RXLOSS_MSK           BIT1
#define DMA_I2C1_CheckRxLossFlag()      READ_REG_BIT(DMA_I2CR_STA,  DMAI2CRSTA_RXLOSS_MSK)
#define DMA_I2C1_ClearRxLossFlag()      CLR_REG_BIT(DMA_I2CR_STA,   DMAI2CRSTA_RXLOSS_MSK)

#define DMA_I2C1_SetTxAmount(d)         (DMA_I2CT_AMTH = HIBYTE(d), DMA_I2CT_AMT = LOBYTE(d))
#define DMA_I2C1_SetRxAmount(d)         (DMA_I2CR_AMTH = HIBYTE(d), DMA_I2CR_AMT = LOBYTE(d))
#define DMA_I2C1_ReadTxDone()           MAKEWORD(DMA_I2CT_DONE, DMA_I2CT_DONEH)
#define DMA_I2C1_ReadRxDone()           MAKEWORD(DMA_I2CR_DONE, DMA_I2CR_DONEH)
#define DMA_I2C1_SetTxAddress(d)        (DMA_I2CT_TXAH = HIBYTE(d), DMA_I2CT_TXAL = LOBYTE(d))
#define DMA_I2C1_SetRxAddress(d)        (DMA_I2CR_RXAH = HIBYTE(d), DMA_I2CR_RXAL = LOBYTE(d))
#define DMA_I2C1_SetInterval(d)         (DMA_I2C_ITVH = HIBYTE(d), DMA_I2C_ITVL = LOBYTE(d))

#define DMAI2CCR_RDSEL_MSK              BIT7
#define DMA_I2C1_ReadAmount()           CLR_REG_BIT(DMA_I2C_CR, DMAI2CCR_RDSEL_MSK)
#define DMA_I2C1_ReadDone()             SET_REG_BIT(DMA_I2C_CR, DMAI2CCR_RDSEL_MSK)

#define DMAI2CCR_ACKERR_MSK             BIT2
#define DMA_I2C1_CheckACK()             READ_REG_BIT(DMA_I2C_CR,  DMAI2CCR_ACKERR_MSK)

#define DMAI2CCR_ERRIE_MSK              BIT1
#define DMA_I2C1_EnableACKErrorInt()    SET_REG_BIT(DMA_I2C_CR, DMAI2CCR_ERRIE_MSK)
#define DMA_I2C1_DisableACKErrorInt()   CLR_REG_BIT(DMA_I2C_CR, DMAI2CCR_ERRIE_MSK)

#define DMAI2CCR_DMAEN_MSK              BIT0
#define DMA_I2C1_EnableDMA()            SET_REG_BIT(DMA_I2C_CR, DMAI2CCR_DMAEN_MSK)
#define DMA_I2C1_DisableDMA()           CLR_REG_BIT(DMA_I2C_CR, DMAI2CCR_DMAEN_MSK)

#define DMA_I2C1_SetDMAAmount(d)        (DMA_I2C_ST2 = HIBYTE(d), DMA_I2C_ST1 = LOBYTE(d))
#define DMA_I2C1_ReadDMAAmount()        MAKEWORD(DMA_I2C_ST1, DMA_I2C_ST2)
#define DMA_I2C1_ReadDMADone()          MAKEWORD(DMA_I2C_ST1, DMA_I2C_ST2)

////////////////////////

#define DMAI2C2TCFG_I2CTPTY_MSK         (BIT1 | BIT0)
#define DMAI2C2RCFG_I2CRPTY_MSK         (BIT1 | BIT0)
#define DMA_I2C2_SetTxBusPriority(n)    MODIFY_REG(DMA_I2C2T_CFG,  DMAI2C2TCFG_I2CTPTY_MSK, ((n) << 0))
#define DMA_I2C2_SetRxBusPriority(n)    MODIFY_REG(DMA_I2C2R_CFG,  DMAI2C2RCFG_I2CRPTY_MSK, ((n) << 0))

#define DMAI2C2TCR_ENI2CT_MSK           BIT7
#define DMAI2C2RCR_ENI2CR_MSK           BIT7
#define DMA_I2C2_EnableTx()             SET_REG_BIT(DMA_I2C2T_CR, DMAI2C2TCR_ENI2CT_MSK)
#define DMA_I2C2_DisableTx()            CLR_REG_BIT(DMA_I2C2T_CR, DMAI2C2TCR_ENI2CT_MSK)
#define DMA_I2C2_EnableRx()             SET_REG_BIT(DMA_I2C2R_CR, DMAI2C2RCR_ENI2CR_MSK)
#define DMA_I2C2_DisableRx()            CLR_REG_BIT(DMA_I2C2R_CR, DMAI2C2RCR_ENI2CR_MSK)

#define DMAI2C2TCR_TRIG_MSK             BIT6
#define DMAI2C2RCR_TRIG_MSK             BIT6
#define DMA_I2C2_TriggerTx()            SET_REG_BIT(DMA_I2C2T_CR, DMAI2C2TCR_TRIG_MSK)
#define DMA_I2C2_TriggerRx()            SET_REG_BIT(DMA_I2C2R_CR, DMAI2C2RCR_TRIG_MSK)

#define DMAI2C2RCR_CLRFIFO_MSK          BIT0
#define DMA_I2C2_ClearFIFO()            SET_REG_BIT(DMA_I2C2R_CR, DMAI2C2RCR_CLRFIFO_MSK)

#define DMAI2C2TSTA_TXOVW_MSK           BIT2
#define DMA_I2C2_CheckOverWriteFlag()   READ_REG_BIT(DMA_I2C2T_STA,  DMAI2C2TSTA_TXOVW_MSK)
#define DMA_I2C2_ClearOverWriteFlag()   CLR_REG_BIT(DMA_I2C2T_STA,   DMAI2C2TSTA_TXOVW_MSK)

#define DMAI2C2RSTA_RXLOSS_MSK          BIT1
#define DMA_I2C2_CheckRxLossFlag()      READ_REG_BIT(DMA_I2C2R_STA,  DMAI2C2RSTA_RXLOSS_MSK)
#define DMA_I2C2_ClearRxLossFlag()      CLR_REG_BIT(DMA_I2C2R_STA,   DMAI2C2RSTA_RXLOSS_MSK)

#define DMA_I2C2_SetTxAmount(d)         (DMA_I2C2T_AMTH = HIBYTE(d), DMA_I2C2T_AMT = LOBYTE(d))
#define DMA_I2C2_SetRxAmount(d)         (DMA_I2C2R_AMTH = HIBYTE(d), DMA_I2C2R_AMT = LOBYTE(d))
#define DMA_I2C2_ReadTxDone()           MAKEWORD(DMA_I2C2T_DONE, DMA_I2C2T_DONEH)
#define DMA_I2C2_ReadRxDone()           MAKEWORD(DMA_I2C2R_DONE, DMA_I2C2R_DONEH)
#define DMA_I2C2_SetTxAddress(d)        (DMA_I2C2T_TXAH = HIBYTE(d), DMA_I2C2T_TXAL = LOBYTE(d))
#define DMA_I2C2_SetRxAddress(d)        (DMA_I2C2R_RXAH = HIBYTE(d), DMA_I2C2R_RXAL = LOBYTE(d))
#define DMA_I2C2_SetInterval(d)         (DMA_I2C2_ITVH = HIBYTE(d), DMA_I2C2_ITVL = LOBYTE(d))

#define DMAI2C2CR_RDSEL_MSK             BIT7
#define DMA_I2C2_ReadAmount()           CLR_REG_BIT(DMA_I2C2_CR, DMAI2C2CR_RDSEL_MSK)
#define DMA_I2C2_ReadDone()             SET_REG_BIT(DMA_I2C2_CR, DMAI2C2CR_RDSEL_MSK)

#define DMAI2C2CR_ACKERR_MSK            BIT2
#define DMA_I2C2_CheckACK()             READ_REG_BIT(DMA_I2C2_CR,  DMAI2C2CR_ACKERR_MSK)

#define DMAI2C2CR_ERRIE_MSK             BIT1
#define DMA_I2C2_EnableACKErrorInt()    SET_REG_BIT(DMA_I2C2_CR, DMAI2C2CR_ERRIE_MSK)
#define DMA_I2C2_DisableACKErrorInt()   CLR_REG_BIT(DMA_I2C2_CR, DMAI2C2CR_ERRIE_MSK)

#define DMAI2C2CR_DMAEN_MSK             BIT0
#define DMA_I2C2_EnableDMA()            SET_REG_BIT(DMA_I2C2_CR, DMAI2C2CR_DMAEN_MSK)
#define DMA_I2C2_DisableDMA()           CLR_REG_BIT(DMA_I2C2_CR, DMAI2C2CR_DMAEN_MSK)

#define DMA_I2C2_SetDMAAmount(d)        (DMA_I2C2_ST2 = HIBYTE(d), DMA_I2C2_ST1 = LOBYTE(d))
#define DMA_I2C2_ReadDMAAmount()        MAKEWORD(DMA_I2C2_ST1, DMA_I2C2_ST2)
#define DMA_I2C2_ReadDMADone()          MAKEWORD(DMA_I2C2_ST1, DMA_I2C2_ST2)

/////////////////////////////////////////////////

#define DMAI2STCFG_I2STPTY_MSK          (BIT1 | BIT0)
#define DMAI2SRCFG_I2SRPTY_MSK          (BIT1 | BIT0)
#define DMA_I2S1_SetTxBusPriority(n)    MODIFY_REG(DMA_I2ST_CFG,  DMAI2STCFG_I2STPTY_MSK, ((n) << 0))
#define DMA_I2S1_SetRxBusPriority(n)    MODIFY_REG(DMA_I2SR_CFG,  DMAI2SRCFG_I2SRPTY_MSK, ((n) << 0))

#define DMAI2STCR_ENI2ST_MSK            BIT7
#define DMAI2SRCR_ENI2SR_MSK            BIT7
#define DMA_I2S1_EnableTx()             SET_REG_BIT(DMA_I2ST_CR, DMAI2STCR_ENI2ST_MSK)
#define DMA_I2S1_DisableTx()            CLR_REG_BIT(DMA_I2ST_CR, DMAI2STCR_ENI2ST_MSK)
#define DMA_I2S1_EnableRx()             SET_REG_BIT(DMA_I2SR_CR, DMAI2SRCR_ENI2SR_MSK)
#define DMA_I2S1_DisableRx()            CLR_REG_BIT(DMA_I2SR_CR, DMAI2SRCR_ENI2SR_MSK)

#define DMAI2STCR_TRIG_MSK              BIT6
#define DMAI2SRCR_TRIG_MSK              BIT6
#define DMA_I2S1_TriggerTx()            SET_REG_BIT(DMA_I2ST_CR, DMAI2STCR_TRIG_MSK)
#define DMA_I2S1_TriggerRx()            SET_REG_BIT(DMA_I2SR_CR, DMAI2SRCR_TRIG_MSK)

#define DMAI2SRCR_CLRFIFO_MSK           BIT0
#define DMA_I2S1_ClearFIFO()            SET_REG_BIT(DMA_I2SR_CR, DMAI2SRCR_CLRFIFO_MSK)

#define DMAI2STSTA_TXOVW_MSK            BIT2
#define DMA_I2S1_CheckOverWriteFlag()   READ_REG_BIT(DMA_I2ST_STA,  DMAI2STSTA_TXOVW_MSK)
#define DMA_I2S1_ClearOverWriteFlag()   CLR_REG_BIT(DMA_I2ST_STA,   DMAI2STSTA_TXOVW_MSK)

#define DMAI2SRSTA_RXLOSS_MSK           BIT1
#define DMA_I2S1_CheckRxLossFlag()      READ_REG_BIT(DMA_I2SR_STA,  DMAI2SRSTA_RXLOSS_MSK)
#define DMA_I2S1_ClearRxLossFlag()      CLR_REG_BIT(DMA_I2SR_STA,   DMAI2SRSTA_RXLOSS_MSK)

#define DMA_I2S1_SetTxAmount(d)         (DMA_I2ST_AMTH = HIBYTE(d), DMA_I2ST_AMT = LOBYTE(d))
#define DMA_I2S1_SetRxAmount(d)         (DMA_I2SR_AMTH = HIBYTE(d), DMA_I2SR_AMT = LOBYTE(d))
#define DMA_I2S1_ReadTxDone()           MAKEWORD(DMA_I2ST_DONE, DMA_I2ST_DONEH)
#define DMA_I2S1_ReadRxDone()           MAKEWORD(DMA_I2SR_DONE, DMA_I2SR_DONEH)
#define DMA_I2S1_SetTxAddress(d)        (DMA_I2ST_TXAH = HIBYTE(d), DMA_I2ST_TXAL = LOBYTE(d))
#define DMA_I2S1_SetRxAddress(d)        (DMA_I2SR_RXAH = HIBYTE(d), DMA_I2SR_RXAL = LOBYTE(d))
#define DMA_I2S1_SetInterval(d)         (DMA_I2S_ITVH = HIBYTE(d), DMA_I2S_ITVL = LOBYTE(d))

////////////////////////

#define DMAI2S2TCFG_I2STPTY_MSK         (BIT1 | BIT0)
#define DMAI2S2RCFG_I2SRPTY_MSK         (BIT1 | BIT0)
#define DMA_I2S2_SetTxBusPriority(n)    MODIFY_REG(DMA_I2S2T_CFG,  DMAI2S2TCFG_I2STPTY_MSK, ((n) << 0))
#define DMA_I2S2_SetRxBusPriority(n)    MODIFY_REG(DMA_I2S2R_CFG,  DMAI2S2RCFG_I2SRPTY_MSK, ((n) << 0))

#define DMAI2S2TCR_ENI2ST_MSK           BIT7
#define DMAI2S2RCR_ENI2SR_MSK           BIT7
#define DMA_I2S2_EnableTx()             SET_REG_BIT(DMA_I2S2T_CR, DMAI2S2TCR_ENI2ST_MSK)
#define DMA_I2S2_DisableTx()            CLR_REG_BIT(DMA_I2S2T_CR, DMAI2S2TCR_ENI2ST_MSK)
#define DMA_I2S2_EnableRx()             SET_REG_BIT(DMA_I2S2R_CR, DMAI2S2RCR_ENI2SR_MSK)
#define DMA_I2S2_DisableRx()            CLR_REG_BIT(DMA_I2S2R_CR, DMAI2S2RCR_ENI2SR_MSK)

#define DMAI2S2TCR_TRIG_MSK             BIT6
#define DMAI2S2RCR_TRIG_MSK             BIT6
#define DMA_I2S2_TriggerTx()            SET_REG_BIT(DMA_I2S2T_CR, DMAI2S2TCR_TRIG_MSK)
#define DMA_I2S2_TriggerRx()            SET_REG_BIT(DMA_I2S2R_CR, DMAI2S2RCR_TRIG_MSK)

#define DMAI2S2RCR_CLRFIFO_MSK          BIT0
#define DMA_I2S2_ClearFIFO()            SET_REG_BIT(DMA_I2S2R_CR, DMAI2S2RCR_CLRFIFO_MSK)

#define DMAI2S2TSTA_TXOVW_MSK           BIT2
#define DMA_I2S2_CheckOverWriteFlag()   READ_REG_BIT(DMA_I2S2T_STA,  DMAI2S2TSTA_TXOVW_MSK)
#define DMA_I2S2_ClearOverWriteFlag()   CLR_REG_BIT(DMA_I2S2T_STA,   DMAI2S2TSTA_TXOVW_MSK)

#define DMAI2S2RSTA_RXLOSS_MSK          BIT1
#define DMA_I2S2_CheckRxLossFlag()      READ_REG_BIT(DMA_I2S2R_STA,  DMAI2S2RSTA_RXLOSS_MSK)
#define DMA_I2S2_ClearRxLossFlag()      CLR_REG_BIT(DMA_I2S2R_STA,   DMAI2S2RSTA_RXLOSS_MSK)

#define DMA_I2S2_SetTxAmount(d)         (DMA_I2S2T_AMTH = HIBYTE(d), DMA_I2S2T_AMT = LOBYTE(d))
#define DMA_I2S2_SetRxAmount(d)         (DMA_I2S2R_AMTH = HIBYTE(d), DMA_I2S2R_AMT = LOBYTE(d))
#define DMA_I2S2_ReadTxDone()           MAKEWORD(DMA_I2S2T_DONE, DMA_I2S2T_DONEH)
#define DMA_I2S2_ReadRxDone()           MAKEWORD(DMA_I2S2R_DONE, DMA_I2S2R_DONEH)
#define DMA_I2S2_SetTxAddress(d)        (DMA_I2S2T_TXAH = HIBYTE(d), DMA_I2S2T_TXAL = LOBYTE(d))
#define DMA_I2S2_SetRxAddress(d)        (DMA_I2S2R_RXAH = HIBYTE(d), DMA_I2S2R_RXAL = LOBYTE(d))
#define DMA_I2S2_SetInterval(d)         (DMA_I2S2_ITVH = HIBYTE(d), DMA_I2S2_ITVL = LOBYTE(d))

/////////////////////////////////////////////////

#define DMAQSPICFG_ACTWR_MSK            BIT6
#define DMAQSPICFG_ACTRD_MSK            BIT5
#define DMA_QSPI_EnableWrite()          SET_REG_BIT(DMA_QSPI_CFG, DMAQSPICFG_ACTWR_MSK)
#define DMA_QSPI_DisableWrite()         CLR_REG_BIT(DMA_QSPI_CFG, DMAQSPICFG_ACTWR_MSK)
#define DMA_QSPI_EnableRead()           SET_REG_BIT(DMA_QSPI_CFG, DMAQSPICFG_ACTRD_MSK)
#define DMA_QSPI_DisableRead()          CLR_REG_BIT(DMA_QSPI_CFG, DMAQSPICFG_ACTRD_MSK)

#define DMAQSPICFG_QSPIPTY_MSK          (BIT1 | BIT0)
#define DMA_QSPI_SetBusPriority(n)      MODIFY_REG(DMA_QSPI_CFG,  DMAQSPICFG_QSPIPTY_MSK, ((n) << 0))

#define DMAQSPICR_ENQSPI_MSK            BIT7
#define DMA_QSPI_Enable()               SET_REG_BIT(DMA_QSPI_CR, DMAQSPICR_ENQSPI_MSK)
#define DMA_QSPI_Disable()              CLR_REG_BIT(DMA_QSPI_CR, DMAQSPICR_ENQSPI_MSK)

#define DMAQSPICR_TRIGW_MSK             BIT6
#define DMAQSPICR_TRIGR_MSK             BIT5
#define DMA_QSPI_TriggerWrite()         SET_REG_BIT(DMA_QSPI_CR, DMAQSPICR_TRIGW_MSK)
#define DMA_QSPI_TriggerRead()          SET_REG_BIT(DMA_QSPI_CR, DMAQSPICR_TRIGR_MSK)

#define DMAQSPICR_CLRRFIFO_MSK          BIT0
#define DMAQSPICR_CLRWFIFO_MSK          BIT1
#define DMA_QSPI_ClearReadFIFO()        SET_REG_BIT(DMA_QSPI_CR, DMAQSPICR_CLRRFIFO_MSK)
#define DMA_QSPI_ClearWriteFIFO()       SET_REG_BIT(DMA_QSPI_CR, DMAQSPICR_CLRWFIFO_MSK)

#define DMA_QSPI_SetAmount(d)           (DMA_QSPI_AMTH = HIBYTE(d), DMA_QSPI_AMT = LOBYTE(d))
#define DMA_QSPI_ReadDone()             MAKEWORD(DMA_QSPI_DONE, DMA_QSPI_DONEH)
#define DMA_QSPI_SetTxAddress(d)        (DMA_QSPI_TXAH = HIBYTE(d), DMA_QSPI_TXAL = LOBYTE(d))
#define DMA_QSPI_SetRxAddress(d)        (DMA_QSPI_RXAH = HIBYTE(d), DMA_QSPI_RXAL = LOBYTE(d))
#define DMA_QSPI_SetInterval(d)         (DMA_QSPI_ITVH = HIBYTE(d), DMA_QSPI_ITVL = LOBYTE(d))

/////////////////////////////////////////////////

#define DMAPWMATCFG_PWMATPTY_MSK        (BIT1 | BIT0)
#define DMAPWMARCFG_PWMARPTY_MSK        (BIT1 | BIT0)
#define DMA_PWMA_SetTxBusPriority(n)    MODIFY_REG(DMA_PWMAT_CFG,  DMAPWMATCFG_PWMATPTY_MSK, ((n) << 0))
#define DMA_PWMA_SetRxBusPriority(n)    MODIFY_REG(DMA_PWMAR_CFG,  DMAPWMARCFG_PWMARPTY_MSK, ((n) << 0))

#define DMAPWMATCR_ENPWMAT_MSK          BIT7
#define DMAPWMARCR_ENPWMAR_MSK          BIT7
#define DMA_PWMA_EnableTx()             SET_REG_BIT(DMA_PWMAT_CR, DMAPWMATCR_ENPWMAT_MSK)
#define DMA_PWMA_DisableTx()            CLR_REG_BIT(DMA_PWMAT_CR, DMAPWMATCR_ENPWMAT_MSK)
#define DMA_PWMA_EnableRx()             SET_REG_BIT(DMA_PWMAR_CR, DMAPWMARCR_ENPWMAR_MSK)
#define DMA_PWMA_DisableRx()            CLR_REG_BIT(DMA_PWMAR_CR, DMAPWMARCR_ENPWMAR_MSK)

#define DMAPWMATCR_TRIG_MSK             BIT6
#define DMAPWMARCR_TRIG_MSK             BIT6
#define DMA_PWMA_TriggerTx()            SET_REG_BIT(DMA_PWMAT_CR, DMAPWMATCR_TRIG_MSK)
#define DMA_PWMA_TriggerRx()            SET_REG_BIT(DMA_PWMAR_CR, DMAPWMARCR_TRIG_MSK)

#define DMAPWMARCR_CLRFIFO_MSK          BIT0
#define DMA_PWMA_ClearFIFO()            SET_REG_BIT(DMA_PWMAR_CR, DMAPWMARCR_CLRFIFO_MSK)

#define DMAPWMATSTA_TXOVW_MSK           BIT2
#define DMA_PWMA_CheckOverWriteFlag()   READ_REG_BIT(DMA_PWMAT_STA,  DMAPWMATSTA_TXOVW_MSK)
#define DMA_PWMA_ClearOverWriteFlag()   CLR_REG_BIT(DMA_PWMAT_STA,   DMAPWMATSTA_TXOVW_MSK)

#define DMAPWMARSTA_RXLOSS_MSK          BIT1
#define DMA_PWMA_CheckRxLossFlag()      READ_REG_BIT(DMA_PWMAR_STA,  DMAPWMARSTA_RXLOSS_MSK)
#define DMA_PWMA_ClearRxLossFlag()      CLR_REG_BIT(DMA_PWMAR_STA,   DMAPWMARSTA_RXLOSS_MSK)

#define DMA_PWMA_SetTxAmount(d)         (DMA_PWMAT_AMTH = HIBYTE(d), DMA_PWMAT_AMT = LOBYTE(d))
#define DMA_PWMA_SetRxAmount(d)         (DMA_PWMAR_AMTH = HIBYTE(d), DMA_PWMAR_AMT = LOBYTE(d))
#define DMA_PWMA_ReadTxDone()           MAKEWORD(DMA_PWMAT_DONE, DMA_PWMAT_DONEH)
#define DMA_PWMA_ReadRxDone()           MAKEWORD(DMA_PWMAR_DONE, DMA_PWMAR_DONEH)
#define DMA_PWMA_SetTxAddress(d)        (DMA_PWMAT_TXAH = HIBYTE(d), DMA_PWMAT_TXAL = LOBYTE(d))
#define DMA_PWMA_SetRxAddress(d)        (DMA_PWMAR_RXAH = HIBYTE(d), DMA_PWMAR_RXAL = LOBYTE(d))
#define DMA_PWMA_SetInterval(d)         (DMA_PWMA_ITVH = HIBYTE(d), DMA_PWMA_ITVL = LOBYTE(d))

////////////////////////

#define DMAPWMCTCFG_PWMCTPTY_MSK        (BIT1 | BIT0)
#define DMAPWMCRCFG_PWMCRPTY_MSK        (BIT1 | BIT0)
#define DMA_PWMC_SetTxBusPriority(n)    MODIFY_REG(DMA_PWMCT_CFG,  DMAPWMCTCFG_PWMCTPTY_MSK, ((n) << 0))
#define DMA_PWMC_SetRxBusPriority(n)    MODIFY_REG(DMA_PWMCR_CFG,  DMAPWMCRCFG_PWMCRPTY_MSK, ((n) << 0))

#define DMAPWMCTCR_ENPWMCT_MSK          BIT7
#define DMAPWMCRCR_ENPWMCR_MSK          BIT7
#define DMA_PWMC_EnableTx()             SET_REG_BIT(DMA_PWMCT_CR, DMAPWMCTCR_ENPWMCT_MSK)
#define DMA_PWMC_DisableTx()            CLR_REG_BIT(DMA_PWMCT_CR, DMAPWMCTCR_ENPWMCT_MSK)
#define DMA_PWMC_EnableRx()             SET_REG_BIT(DMA_PWMCR_CR, DMAPWMCRCR_ENPWMCR_MSK)
#define DMA_PWMC_DisableRx()            CLR_REG_BIT(DMA_PWMCR_CR, DMAPWMCRCR_ENPWMCR_MSK)

#define DMAPWMCTCR_TRIG_MSK             BIT6
#define DMAPWMCRCR_TRIG_MSK             BIT6
#define DMA_PWMC_TriggerTx()            SET_REG_BIT(DMA_PWMCT_CR, DMAPWMCTCR_TRIG_MSK)
#define DMA_PWMC_TriggerRx()            SET_REG_BIT(DMA_PWMCR_CR, DMAPWMCRCR_TRIG_MSK)

#define DMAPWMCRCR_CLRFIFO_MSK          BIT0
#define DMA_PWMC_ClearFIFO()            SET_REG_BIT(DMA_PWMCR_CR, DMAPWMCRCR_CLRFIFO_MSK)

#define DMAPWMCTSTA_TXOVW_MSK           BIT2
#define DMA_PWMC_CheckOverWriteFlag()   READ_REG_BIT(DMA_PWMCT_STA,  DMAPWMCTSTA_TXOVW_MSK)
#define DMA_PWMC_ClearOverWriteFlag()   CLR_REG_BIT(DMA_PWMCT_STA,   DMAPWMCTSTA_TXOVW_MSK)

#define DMAPWMCRSTA_RXLOSS_MSK          BIT1
#define DMA_PWMC_CheckRxLossFlag()      READ_REG_BIT(DMA_PWMCR_STA,  DMAPWMCRSTA_RXLOSS_MSK)
#define DMA_PWMC_ClearRxLossFlag()      CLR_REG_BIT(DMA_PWMCR_STA,   DMAPWMCRSTA_RXLOSS_MSK)

#define DMA_PWMC_SetTxAmount(d)         (DMA_PWMCT_AMTH = HIBYTE(d), DMA_PWMCT_AMT = LOBYTE(d))
#define DMA_PWMC_SetRxAmount(d)         (DMA_PWMCR_AMTH = HIBYTE(d), DMA_PWMCR_AMT = LOBYTE(d))
#define DMA_PWMC_ReadTxDone()           MAKEWORD(DMA_PWMCT_DONE, DMA_PWMCT_DONEH)
#define DMA_PWMC_ReadRxDone()           MAKEWORD(DMA_PWMCR_DONE, DMA_PWMCR_DONEH)
#define DMA_PWMC_SetTxAddress(d)        (DMA_PWMCT_TXAH = HIBYTE(d), DMA_PWMCT_TXAL = LOBYTE(d))
#define DMA_PWMC_SetRxAddress(d)        (DMA_PWMCR_RXAH = HIBYTE(d), DMA_PWMCR_RXAL = LOBYTE(d))
#define DMA_PWMC_SetInterval(d)         (DMA_PWMC_ITVH = HIBYTE(d), DMA_PWMC_ITVL = LOBYTE(d))

////////////////////////

#define DMAPWMETCFG_PWMETPTY_MSK        (BIT1 | BIT0)
#define DMAPWMERCFG_PWMERPTY_MSK        (BIT1 | BIT0)
#define DMA_PWME_SetTxBusPriority(n)    MODIFY_REG(DMA_PWMET_CFG,  DMAPWMETCFG_PWMETPTY_MSK, ((n) << 0))
#define DMA_PWME_SetRxBusPriority(n)    MODIFY_REG(DMA_PWMER_CFG,  DMAPWMERCFG_PWMERPTY_MSK, ((n) << 0))

#define DMAPWMETCR_ENPWMET_MSK          BIT7
#define DMAPWMERCR_ENPWMER_MSK          BIT7
#define DMA_PWME_EnableTx()             SET_REG_BIT(DMA_PWMET_CR, DMAPWMETCR_ENPWMET_MSK)
#define DMA_PWME_DisableTx()            CLR_REG_BIT(DMA_PWMET_CR, DMAPWMETCR_ENPWMET_MSK)
#define DMA_PWME_EnableRx()             SET_REG_BIT(DMA_PWMER_CR, DMAPWMERCR_ENPWMER_MSK)
#define DMA_PWME_DisableRx()            CLR_REG_BIT(DMA_PWMER_CR, DMAPWMERCR_ENPWMER_MSK)

#define DMAPWMETCR_TRIG_MSK             BIT6
#define DMAPWMERCR_TRIG_MSK             BIT6
#define DMA_PWME_TriggerTx()            SET_REG_BIT(DMA_PWMET_CR, DMAPWMETCR_TRIG_MSK)
#define DMA_PWME_TriggerRx()            SET_REG_BIT(DMA_PWMER_CR, DMAPWMERCR_TRIG_MSK)

#define DMAPWMERCR_CLRFIFO_MSK          BIT0
#define DMA_PWME_ClearFIFO()            SET_REG_BIT(DMA_PWMER_CR, DMAPWMERCR_CLRFIFO_MSK)

#define DMAPWMETSTA_TXOVW_MSK           BIT2
#define DMA_PWME_CheckOverWriteFlag()   READ_REG_BIT(DMA_PWMET_STA,  DMAPWMETSTA_TXOVW_MSK)
#define DMA_PWME_ClearOverWriteFlag()   CLR_REG_BIT(DMA_PWMET_STA,   DMAPWMETSTA_TXOVW_MSK)

#define DMAPWMERSTA_RXLOSS_MSK          BIT1
#define DMA_PWME_CheckRxLossFlag()      READ_REG_BIT(DMA_PWMER_STA,  DMAPWMERSTA_RXLOSS_MSK)
#define DMA_PWME_ClearRxLossFlag()      CLR_REG_BIT(DMA_PWMER_STA,   DMAPWMERSTA_RXLOSS_MSK)

#define DMA_PWME_SetTxAmount(d)         (DMA_PWMET_AMTH = HIBYTE(d), DMA_PWMET_AMT = LOBYTE(d))
#define DMA_PWME_SetRxAmount(d)         (DMA_PWMER_AMTH = HIBYTE(d), DMA_PWMER_AMT = LOBYTE(d))
#define DMA_PWME_ReadTxDone()           MAKEWORD(DMA_PWMET_DONE, DMA_PWMET_DONEH)
#define DMA_PWME_ReadRxDone()           MAKEWORD(DMA_PWMER_DONE, DMA_PWMER_DONEH)
#define DMA_PWME_SetTxAddress(d)        (DMA_PWMET_TXAH = HIBYTE(d), DMA_PWMET_TXAL = LOBYTE(d))
#define DMA_PWME_SetRxAddress(d)        (DMA_PWMER_RXAH = HIBYTE(d), DMA_PWMER_RXAL = LOBYTE(d))
#define DMA_PWME_SetInterval(d)         (DMA_PWME_ITVH = HIBYTE(d), DMA_PWME_ITVL = LOBYTE(d))

/////////////////////////////////////////////////

#define DMADAC1CFG_DAC1PTY_MSK          (BIT1 | BIT0)
#define DMA_DAC1_SetBusPriority(n)      MODIFY_REG(DMA_DAC1_CFG,  DMADAC1CFG_DAC1PTY_MSK, ((n) << 0))

#define DMADAC1CR_ENDAC1_MSK            BIT7
#define DMA_DAC1_Enable()               SET_REG_BIT(DMA_DAC1_CR, DMADAC1CR_ENDAC1_MSK)
#define DMA_DAC1_Disable()              CLR_REG_BIT(DMA_DAC1_CR, DMADAC1CR_ENDAC1_MSK)

#define DMADAC1CR_TRIG_MSK              BIT6
#define DMA_DAC1_Trigger()              SET_REG_BIT(DMA_DAC1_CR, DMADAC1CR_TRIG_MSK)

#define DMA_DAC1_SetAmount(d)           (DMA_DAC1_AMTH = HIBYTE(d), DMA_DAC1_AMT = LOBYTE(d))
#define DMA_DAC1_ReadDone()             MAKEWORD(DMA_DAC1_DONE, DMA_DAC1_DONEH)
#define DMA_DAC1_SetAddress(d)          (DMA_DAC1_TXAH = HIBYTE(d), DMA_DAC1_TXAL = LOBYTE(d))
#define DMA_DAC1_SetInterval(d)         (DMA_DAC1_ITVH = HIBYTE(d), DMA_DAC1_ITVL = LOBYTE(d))

////////////////////////

#define DMADAC2CFG_DAC2PTY_MSK          (BIT1 | BIT0)
#define DMA_DAC2_SetBusPriority(n)      MODIFY_REG(DMA_DAC2_CFG,  DMADAC2CFG_DAC2PTY_MSK, ((n) << 0))

#define DMADAC2CR_ENDAC2_MSK            BIT7
#define DMA_DAC2_Enable()               SET_REG_BIT(DMA_DAC2_CR, DMADAC2CR_ENDAC2_MSK)
#define DMA_DAC2_Disable()              CLR_REG_BIT(DMA_DAC2_CR, DMADAC2CR_ENDAC2_MSK)

#define DMADAC2CR_TRIG_MSK              BIT6
#define DMA_DAC2_Trigger()              SET_REG_BIT(DMA_DAC2_CR, DMADAC2CR_TRIG_MSK)

#define DMA_DAC2_SetAmount(d)           (DMA_DAC2_AMTH = HIBYTE(d), DMA_DAC2_AMT = LOBYTE(d))
#define DMA_DAC2_ReadDone()             MAKEWORD(DMA_DAC2_DONE, DMA_DAC2_DONEH)
#define DMA_DAC2_SetAddress(d)          (DMA_DAC2_TXAH = HIBYTE(d), DMA_DAC2_TXAL = LOBYTE(d))
#define DMA_DAC2_SetInterval(d)         (DMA_DAC2_ITVH = HIBYTE(d), DMA_DAC2_ITVL = LOBYTE(d))

/////////////////////////////////////////////////

#define DMACAN1TCFG_CAN1TPTY_MSK        (BIT1 | BIT0)
#define DMACAN2TCFG_CAN2TPTY_MSK        (BIT1 | BIT0)
#define DMA_CAN1_SetTxBusPriority(n)    MODIFY_REG(DMA_CAN1T_CFG,  DMACAN1TCFG_CAN1TPTY_MSK, ((n) << 0))
#define DMA_CAN2_SetTxBusPriority(n)    MODIFY_REG(DMA_CAN2T_CFG,  DMACAN2TCFG_CAN2TPTY_MSK, ((n) << 0))

#define DMACAN1RCFG_CAN1RPTY_MSK        (BIT1 | BIT0)
#define DMACAN2RCFG_CAN2RPTY_MSK        (BIT1 | BIT0)
#define DMA_CAN1_SetRxBusPriority(n)    MODIFY_REG(DMA_CAN1R_CFG,  DMACAN1RCFG_CAN1RPTY_MSK, ((n) << 0))
#define DMA_CAN2_SetRxBusPriority(n)    MODIFY_REG(DMA_CAN2R_CFG,  DMACAN2RCFG_CAN2RPTY_MSK, ((n) << 0))

#define DMACAN1TCFG_TADRALIGN_MSK       BIT5
#define DMACAN2TCFG_TADRALIGN_MSK       BIT5
#define DMA_CAN1_TxDataAlign()          SET_REG_BIT(DMA_CAN1T_CFG, DMACAN1TCFG_TADRALIGN_MSK)
#define DMA_CAN2_TxDataAlign()          SET_REG_BIT(DMA_CAN2T_CFG, DMACAN2TCFG_TADRALIGN_MSK)
#define DMA_CAN1_TxDataContinue()       CLR_REG_BIT(DMA_CAN1T_CFG, DMACAN1TCFG_TADRALIGN_MSK)
#define DMA_CAN2_TxDataContinue()       CLR_REG_BIT(DMA_CAN2T_CFG, DMACAN2TCFG_TADRALIGN_MSK)

#define DMACAN1TCFG_TXBW_MSK            BIT4
#define DMACAN2TCFG_TXBW_MSK            BIT4
#define DMA_CAN1_Tx8BitWidth()          CLR_REG_BIT(DMA_CAN1T_CFG, DMACAN1TCFG_TXBW_MSK)
#define DMA_CAN2_Tx8BitWidth()          CLR_REG_BIT(DMA_CAN2T_CFG, DMACAN2TCFG_TXBW_MSK)
#define DMA_CAN1_Tx32BitWidth()         SET_REG_BIT(DMA_CAN1T_CFG, DMACAN1TCFG_TXBW_MSK)
#define DMA_CAN2_Tx32BitWidth()         SET_REG_BIT(DMA_CAN2T_CFG, DMACAN2TCFG_TXBW_MSK)

#define DMACAN1RCFG_RAMTALIGN_MSK       BIT6
#define DMACAN2RCFG_RAMTALIGN_MSK       BIT6
#define DMA_CAN1_RxAmountAlign()        CLR_REG_BIT(DMA_CAN1R_CFG, DMACAN1RCFG_RAMTALIGN_MSK)
#define DMA_CAN2_RxAmountAlign()        CLR_REG_BIT(DMA_CAN2R_CFG, DMACAN2RCFG_RAMTALIGN_MSK)
#define DMA_CAN1_RxDoneAlign()          SET_REG_BIT(DMA_CAN1R_CFG, DMACAN1RCFG_RAMTALIGN_MSK)
#define DMA_CAN2_RxDoneAlign()          SET_REG_BIT(DMA_CAN2R_CFG, DMACAN2RCFG_RAMTALIGN_MSK)

#define DMACAN1RCFG_RADRALIGN_MSK       BIT5
#define DMACAN2RCFG_RADRALIGN_MSK       BIT5
#define DMA_CAN1_RxDataAlign()          SET_REG_BIT(DMA_CAN1R_CFG, DMACAN1RCFG_RADRALIGN_MSK)
#define DMA_CAN2_RxDataAlign()          SET_REG_BIT(DMA_CAN2R_CFG, DMACAN2RCFG_RADRALIGN_MSK)
#define DMA_CAN1_RxDataContinue()       CLR_REG_BIT(DMA_CAN1R_CFG, DMACAN1RCFG_RADRALIGN_MSK)
#define DMA_CAN2_RxDataContinue()       CLR_REG_BIT(DMA_CAN2R_CFG, DMACAN2RCFG_RADRALIGN_MSK)

#define DMACAN1RCFG_RXBW_MSK            BIT4
#define DMACAN2RCFG_RXBW_MSK            BIT4
#define DMA_CAN1_Rx8BitWidth()          CLR_REG_BIT(DMA_CAN1R_CFG, DMACAN1RCFG_RXBW_MSK)
#define DMA_CAN2_Rx8BitWidth()          CLR_REG_BIT(DMA_CAN2R_CFG, DMACAN2RCFG_RXBW_MSK)
#define DMA_CAN1_Rx32BitWidth()         SET_REG_BIT(DMA_CAN1R_CFG, DMACAN1RCFG_RXBW_MSK)
#define DMA_CAN2_Rx32BitWidth()         SET_REG_BIT(DMA_CAN2R_CFG, DMACAN2RCFG_RXBW_MSK)

#define DMACAN1TCR_ENCAN1T_MSK          BIT7
#define DMACAN2TCR_ENCAN2T_MSK          BIT7
#define DMA_CAN1_EnableTx()             SET_REG_BIT(DMA_CAN1T_CR, DMACAN1TCR_ENCAN1T_MSK)
#define DMA_CAN2_EnableTx()             SET_REG_BIT(DMA_CAN2T_CR, DMACAN2TCR_ENCAN2T_MSK)
#define DMA_CAN1_DisableTx()            CLR_REG_BIT(DMA_CAN1T_CR, DMACAN1TCR_ENCAN1T_MSK)
#define DMA_CAN2_DisableTx()            CLR_REG_BIT(DMA_CAN2T_CR, DMACAN2TCR_ENCAN2T_MSK)

#define DMACAN1RCR_ENCAN1R_MSK          BIT7
#define DMACAN2RCR_ENCAN2R_MSK          BIT7
#define DMA_CAN1_EnableRx()             SET_REG_BIT(DMA_CAN1R_CR, DMACAN1RCR_ENCAN1R_MSK)
#define DMA_CAN2_EnableRx()             SET_REG_BIT(DMA_CAN2R_CR, DMACAN2RCR_ENCAN2R_MSK)
#define DMA_CAN1_DisableRx()            CLR_REG_BIT(DMA_CAN1R_CR, DMACAN1RCR_ENCAN1R_MSK)
#define DMA_CAN2_DisableRx()            CLR_REG_BIT(DMA_CAN2R_CR, DMACAN2RCR_ENCAN2R_MSK)

#define DMACAN1TCR_TRIG_MSK             BIT6
#define DMACAN2TCR_TRIG_MSK             BIT6
#define DMA_CAN1_TriggerTx()            SET_REG_BIT(DMA_CAN1T_CR, DMACAN1TCR_TRIG_MSK)
#define DMA_CAN2_TriggerTx()            SET_REG_BIT(DMA_CAN2T_CR, DMACAN2TCR_TRIG_MSK)

#define DMACAN1RCR_TRIG_MSK             BIT6
#define DMACAN2RCR_TRIG_MSK             BIT6
#define DMA_CAN1_TriggerRx()            SET_REG_BIT(DMA_CAN1R_CR, DMACAN1RCR_TRIG_MSK)
#define DMA_CAN2_TriggerRx()            SET_REG_BIT(DMA_CAN2R_CR, DMACAN2RCR_TRIG_MSK)

#define DMACAN1RCR_CLRFIFO_MSK          BIT0
#define DMACAN2RCR_CLRFIFO_MSK          BIT0
#define DMA_CAN1_ClearFIFO()            SET_REG_BIT(DMA_CAN1R_CR, DMACAN1RCR_CLRFIFO_MSK)
#define DMA_CAN2_ClearFIFO()            SET_REG_BIT(DMA_CAN2R_CR, DMACAN2RCR_CLRFIFO_MSK)

#define DMACAN1TSTA_TXOVW_MSK           BIT2
#define DMACAN2TSTA_TXOVW_MSK           BIT2
#define DMA_CAN1_CheckOverWriteFlag()   READ_REG_BIT(DMA_CAN1T_STA,  DMACAN1TSTA_TXOVW_MSK)
#define DMA_CAN2_CheckOverWriteFlag()   READ_REG_BIT(DMA_CAN2T_STA,  DMACAN2TSTA_TXOVW_MSK)
#define DMA_CAN1_ClearOverWriteFlag()   CLR_REG_BIT(DMA_CAN1T_STA,   DMACAN1TSTA_TXOVW_MSK)
#define DMA_CAN2_ClearOverWriteFlag()   CLR_REG_BIT(DMA_CAN2T_STA,   DMACAN2TSTA_TXOVW_MSK)

#define DMACAN1RSTA_RXLOSS_MSK          BIT1
#define DMACAN2RSTA_RXLOSS_MSK          BIT1
#define DMA_CAN1_CheckRxLossFlag()      READ_REG_BIT(DMA_CAN1R_STA,  DMACAN1RSTA_RXLOSS_MSK)
#define DMA_CAN2_CheckRxLossFlag()      READ_REG_BIT(DMA_CAN2R_STA,  DMACAN2RSTA_RXLOSS_MSK)
#define DMA_CAN1_ClearRxLossFlag()      CLR_REG_BIT(DMA_CAN1R_STA,   DMACAN1RSTA_RXLOSS_MSK)
#define DMA_CAN2_ClearRxLossFlag()      CLR_REG_BIT(DMA_CAN2R_STA,   DMACAN2RSTA_RXLOSS_MSK)

#define DMA_CAN1_SetTxAmount(d)         (DMA_CAN1T_AMTH = HIBYTE(d), DMA_CAN1T_AMT = LOBYTE(d))
#define DMA_CAN2_SetTxAmount(d)         (DMA_CAN2T_AMTH = HIBYTE(d), DMA_CAN2T_AMT = LOBYTE(d))

#define DMA_CAN1_SetRxAmount(d)         (DMA_CAN1R_AMTH = HIBYTE(d), DMA_CAN1R_AMT = LOBYTE(d))
#define DMA_CAN2_SetRxAmount(d)         (DMA_CAN2R_AMTH = HIBYTE(d), DMA_CAN2R_AMT = LOBYTE(d))

#define DMA_CAN1_ReadTxDone()           MAKEWORD(DMA_CAN1T_DONE, DMA_CAN1T_DONEH)
#define DMA_CAN2_ReadTxDone()           MAKEWORD(DMA_CAN2T_DONE, DMA_CAN2T_DONEH)

#define DMA_CAN1_ReadRxDone()           MAKEWORD(DMA_CAN1R_DONE, DMA_CAN1R_DONEH)
#define DMA_CAN2_ReadRxDone()           MAKEWORD(DMA_CAN2R_DONE, DMA_CAN2R_DONEH)

#define DMA_CAN1_SetTxAddress(d)        (DMA_CAN1T_TXAH = HIBYTE(d), DMA_CAN1T_TXAL = LOBYTE(d))
#define DMA_CAN2_SetTxAddress(d)        (DMA_CAN2T_TXAH = HIBYTE(d), DMA_CAN2T_TXAL = LOBYTE(d))

#define DMA_CAN1_SetRxAddress(d)        (DMA_CAN1R_RXAH = HIBYTE(d), DMA_CAN1R_RXAL = LOBYTE(d))
#define DMA_CAN2_SetRxAddress(d)        (DMA_CAN2R_RXAH = HIBYTE(d), DMA_CAN2R_RXAL = LOBYTE(d))

#define DMA_CAN1_SetInterval(d)         (DMA_CAN1_ITVH = HIBYTE(d), DMA_CAN1_ITVL = LOBYTE(d))
#define DMA_CAN2_SetInterval(d)         (DMA_CAN2_ITVH = HIBYTE(d), DMA_CAN2_ITVL = LOBYTE(d))

#define DMA_CAN1_SetTxFrameSize(d)      (DMA_CAN1T_FRM = BYTE(d))
#define DMA_CAN2_SetTxFrameSize(d)      (DMA_CAN2T_FRM = BYTE(d))

#define DMA_CAN1_SetRxFrameSize(d)      (DMA_CAN1R_FRM = BYTE(d))
#define DMA_CAN2_SetRxFrameSize(d)      (DMA_CAN2R_FRM = BYTE(d))

#define DMA_CAN1_SetRxAddress(d)        (DMA_CAN1R_RXAH = HIBYTE(d), DMA_CAN1R_RXAL = LOBYTE(d))
#define DMA_CAN2_SetRxAddress(d)        (DMA_CAN2R_RXAH = HIBYTE(d), DMA_CAN2R_RXAL = LOBYTE(d))

#define DMA_CAN1_ReadTxFrameCount()     MAKEWORD(DMA_CAN1T_FCNTL, DMA_CAN1T_FCNTH)
#define DMA_CAN2_ReadTxFrameCount()     MAKEWORD(DMA_CAN2T_FCNTL, DMA_CAN2T_FCNTH)

#define DMA_CAN1_ReadRxFrameCount()     MAKEWORD(DMA_CAN1R_FCNTL, DMA_CAN1R_FCNTH)
#define DMA_CAN2_ReadRxFrameCount()     MAKEWORD(DMA_CAN2R_FCNTL, DMA_CAN2R_FCNTH)

#define CAN1AUXCR_AUTOTRANS_MSK         BIT5
#define CAN2AUXCR_AUTOTRANS_MSK         BIT5
#define DMA_CAN1_AutoTransmit()         CLR_REG_BIT(CAN1_AUX_CR, CAN1AUXCR_AUTOTRANS_MSK)
#define DMA_CAN2_AutoTransmit()         CLR_REG_BIT(CAN2_AUX_CR, CAN2AUXCR_AUTOTRANS_MSK)
#define DMA_CAN1_ManualTransmit()       SET_REG_BIT(CAN1_AUX_CR, CAN1AUXCR_AUTOTRANS_MSK)
#define DMA_CAN2_ManualTransmit()       SET_REG_BIT(CAN2_AUX_CR, CAN2AUXCR_AUTOTRANS_MSK)

#define CAN1AUXCR_DMATXEN_MSK           BIT4
#define CAN2AUXCR_DMATXEN_MSK           BIT4
#define CAN1_EnableTxDMA()              SET_REG_BIT(CAN1_AUX_CR, CAN1AUXCR_DMATXEN_MSK)
#define CAN2_EnableTxDMA()              SET_REG_BIT(CAN2_AUX_CR, CAN2AUXCR_DMATXEN_MSK)
#define CAN1_DisableTxDMA()             CLR_REG_BIT(CAN1_AUX_CR, CAN1AUXCR_DMATXEN_MSK)
#define CAN2_DisableTxDMA()             CLR_REG_BIT(CAN2_AUX_CR, CAN2AUXCR_DMATXEN_MSK)

#define CAN1AUXCR_DMARXEN_MSK           BIT0
#define CAN2AUXCR_DMARXEN_MSK           BIT0
#define CAN1_EnableRxDMA()              SET_REG_BIT(CAN1_AUX_CR, CAN1AUXCR_DMARXEN_MSK)
#define CAN2_EnableRxDMA()              SET_REG_BIT(CAN2_AUX_CR, CAN2AUXCR_DMARXEN_MSK)
#define CAN1_DisableRxDMA()             CLR_REG_BIT(CAN1_AUX_CR, CAN1AUXCR_DMARXEN_MSK)
#define CAN2_DisableRxDMA()             CLR_REG_BIT(CAN2_AUX_CR, CAN2AUXCR_DMARXEN_MSK)

/////////////////////////////////////////////////

#define RSTCFG_P47RST_MSK               BIT4
#define RST_EnableResetPin()            SET_REG_BIT(RSTCFG, RSTCFG_P47RST_MSK)
#define RST_ResetPinAsGPIO()            CLR_REG_BIT(RSTCFG, RSTCFG_P47RST_MSK)

#define RSTCFG_ENLVR_MSK                BIT7
#define LVR_EnableLVR()                 SET_REG_BIT(RSTCFG, RSTCFG_ENLVR_MSK)
#define LVR_DisableLVR()                CLR_REG_BIT(RSTCFG, RSTCFG_ENLVR_MSK)

#define RSTCFG_LVDS_MSK                 (BIT1 | BIT0)
#define LVR_SetLVDS(n)                  MODIFY_REG(RSTCFG,  RSTCFG_LVDS_MSK, ((n) << 0))
#define LVR_SetLVDLevelV2p0()           LVR_SetLVDS(0)
#define LVR_SetLVDLevelV2p4()           LVR_SetLVDS(1)
#define LVR_SetLVDLevelV2p7()           LVR_SetLVDS(2)
#define LVR_SetLVDLevelV3p0()           LVR_SetLVDS(3)

/////////////////////////////////////////////////

#ifndef READ_LIN
#define READ_LIN(r)                     (LINAR = (r), READ_REG(LINDR))
#endif
#ifndef WRITE_LIN
#define WRITE_LIN(r, dat)               (LINAR = (r), WRITE_REG(LINDR, (dat)))
#endif
#ifndef MODIFY_LIN
#define MODIFY_LIN(r, clr, set)         (LINAR = (r), MODIFY_REG(LINDR, (clr), (set)))
#endif
#ifndef CLR_LIN_BIT
#define CLR_LIN_BIT(r, b)               (LINAR = (r), CLR_REG_BIT(LINDR, (b)))
#endif
#ifndef SET_LIN_BIT
#define SET_LIN_BIT(r, b)               (LINAR = (r), SET_REG_BIT(LINDR, (b)))
#endif

#define AUXR2_LIN1EN_MSK                BIT0
#define LIN1_Enable()                   SET_REG_BIT(AUXR2, AUXR2_LIN1EN_MSK)
#define LIN1_Disable()                  CLR_REG_BIT(AUXR2, AUXR2_LIN1EN_MSK)

#define AUXR2_LIN2EN_MSK                BIT4
#define LIN2_Enable()                   SET_REG_BIT(AUXR2, AUXR2_LIN2EN_MSK)
#define LIN2_Disable()                  CLR_REG_BIT(AUXR2, AUXR2_LIN2EN_MSK)

#define AUXR2_LINSEL_MSK                BIT5
#define LIN1_SEL()                      CLR_REG_BIT(AUXR2, AUXR2_LINSEL_MSK)
#define LIN2_SEL()                      SET_REG_BIT(AUXR2, AUXR2_LINSEL_MSK)
#define LIN1_ACTIVE()                   (READ_REG_BIT(AUXR2, AUXR2_LINSEL_MSK) == 0)
#define LIN2_ACTIVE()                   (READ_REG_BIT(AUXR2, AUXR2_LINSEL_MSK) != 0)

#define LINICR_LIN1IE_MSK               BIT1
#define LIN1_EnableInt()                SET_REG_BIT(LINICR, LINICR_LIN1IE_MSK)
#define LIN1_DisableInt()               CLR_REG_BIT(LINICR, LINICR_LIN1IE_MSK)

#define LINICR_PLIN1L_MSK               BIT0
#define LINICR_PLIN1H_MSK               BIT3
#define LIN1_SetIntPriority(n)          MODIFY_REG(LINICR, LINICR_PLIN1L_MSK, (((n) & 1) << 0)); \
                                        MODIFY_REG(LINICR, LINICR_PLIN1H_MSK, ((((n) >> 1) & 1) << 3))

#define LINICR_LIN2IE_MSK               BIT5
#define LIN2_EnableInt()                SET_REG_BIT(LINICR, LINICR_LIN2IE_MSK)
#define LIN2_DisableInt()               CLR_REG_BIT(LINICR, LINICR_LIN2IE_MSK)

#define LINICR_PLIN2L_MSK               BIT4
#define LINICR_PLIN2H_MSK               BIT7
#define LIN2_SetIntPriority(n)          MODIFY_REG(LINICR, LINICR_PLIN2L_MSK, (((n) & 1) << 4)); \
                                        MODIFY_REG(LINICR, LINICR_PLIN2H_MSK, ((((n) >> 1) & 1) << 7))

#define LIN_ReadData()                  READ_LIN(LBUF)
#define LIN_WriteData(d)                WRITE_LIN(LBUF, (d))

#define LSEL_AINC_MSK                   BIT7
#define LIN_EnableAutoIncIndex()        SET_LIN_BIT(LSEL, LSEL_AINC_MSK)
#define LIN_DisableAutoIncIndex()       CLR_LIN_BIT(LSEL, LSEL_AINC_MSK)

#define LSEL_INDEX_MSK                  (BIT_LN)
#define LIN_SetDataIndex(i)             MODIFY_LIN(LSEL, LSEL_INDEX_MSK, ((i) << 0))

#define LID_ID_MSK                      (BIT5 | BIT4 | BIT_LN)
#define LIN_SetFrameID(n)               WRITE_LIN(LID, ((n) & LID_ID_MSK))
#define LIN_ReadFrameID()               (READ_LIN(LID) & LID_ID_MSK)

#define LER_OV_MSK                      BIT6
#define LER_SYN_MSK                     BIT5
#define LER_TOV_MSK                     BIT4
#define LER_CHK_MSK                     BIT3
#define LER_PER_MSK                     BIT2
#define LER_BIT_MSK                     BIT1
#define LER_FER_MSK                     BIT0
#define LIN_ReadAndClearError()         READ_LIN(LER)
#define LIN_CheckOVError(f)             READ_REG_BIT((f), LER_OV_MSK)
#define LIN_CheckSYNError(f)            READ_REG_BIT((f), LER_SYN_MSK)
#define LIN_CheckTOVError(f)            READ_REG_BIT((f), LER_TOV_MSK)
#define LIN_CheckCHKError(f)            READ_REG_BIT((f), LER_CHK_MSK)
#define LIN_CheckPERError(f)            READ_REG_BIT((f), LER_PER_MSK)
#define LIN_CheckBITError(f)            READ_REG_BIT((f), LER_BIT_MSK)
#define LIN_CheckFERError(f)            READ_REG_BIT((f), LER_FER_MSK)

#define LIE_ABORTE_MSK                  BIT3
#define LIE_ERRE_MSK                    BIT2
#define LIE_RDYE_MSK                    BIT1
#define LIE_LIDE_MSK                    BIT0
#define LIN_EnableAbortInt()            SET_LIN_BIT(LIE, LIE_ABORTE_MSK)
#define LIN_EnableErrorInt()            SET_LIN_BIT(LIE, LIE_ERRE_MSK)
#define LIN_EnableReadyInt()            SET_LIN_BIT(LIE, LIE_RDYE_MSK)
#define LIN_EnableHeaderInt()           SET_LIN_BIT(LIE, LIE_LIDE_MSK)
#define LIN_DisableAbortInt()           CLR_LIN_BIT(LIE, LIE_ABORTE_MSK)
#define LIN_DisableErrorInt()           CLR_LIN_BIT(LIE, LIE_ERRE_MSK)
#define LIN_DisableReadyInt()           CLR_LIN_BIT(LIE, LIE_RDYE_MSK)
#define LIN_DisableHeaderInt()          CLR_LIN_BIT(LIE, LIE_LIDE_MSK)

#define LSR_LOGSIZE_MSK                 (BIT_HN)
#define LSR_ABORT_MSK                   BIT3
#define LSR_ERR_MSK                     BIT2
#define LSR_RDY_MSK                     BIT1
#define LSR_LID_MSK                     BIT0
#define LIN_ReadAndClearStatus()        READ_LIN(LSR)
#define LIN_CheckAbort(f)               READ_REG_BIT((f), LSR_ABORT_MSK)
#define LIN_CheckError(f)               READ_REG_BIT((f), LSR_ERR_MSK)
#define LIN_CheckReady(f)               READ_REG_BIT((f), LSR_RDY_MSK)
#define LIN_CheckHeader(f)              READ_REG_BIT((f), LSR_LID_MSK)
#define LIN_GetLogSize(f)               (READ_REG_BIT((f), LSR_LOGSIZE_MSK) >> 4)

#define LCR_MODE_MSK                    BIT7
#define LIN_MASTER_MODE                 ((1 << 7) & LCR_MODE_MSK)
#define LIN_SLAVE_MODE                  ((0 << 7) & LCR_MODE_MSK)

#define LCR_LIN13_MSK                   BIT6
#define LIN_R1p3POTOCOL                 ((1 << 6) & LCR_LIN13_MSK)
#define LIN_R2p1POTOCOL                 ((0 << 6) & LCR_LIN13_MSK)

#define LCR_SIZE_MSK                    (BIT5 | BIT4 | BIT3 | BIT2)
#define LIN_FRAMESIZE(n)                (((n) << 2) & LCR_SIZE_MSK)

#define LCR_CMD_MSK                     (BIT1 | BIT0)
#define LIN_ABORTCMD                    (0 & LCR_CMD_MSK)
#define LIN_SENDHEADERCMD               (1 & LCR_CMD_MSK)
#define LIN_TXRESPONSECMD               (2 & LCR_CMD_MSK)
#define LIN_RXRESPONSECMD               (3 & LCR_CMD_MSK)

#define LIN_SendCommand(n)              WRITE_LIN(LCR, (n))

#define DLH_SYNC_MSK                    BIT7
#define LIN_EnableBaudRateSync()        SET_LIN_BIT(DLH, DLH_SYNC_MSK)
#define LIN_DisableBaudRateSync()       CLR_LIN_BIT(DLH, DLH_SYNC_MSK)

#define LIN_SetBaudRate(n)              WRITE_LIN(DLL, BYTE0(n)) ; \
                                        MODIFY_LIN(DLH, BYTE0(~DLH_SYNC_MSK), BYTE1(n))

#define LIN_SetHeaderDelay(n)           WRITE_LIN(HDRL, BYTE0(n)) ; \
                                        WRITE_LIN(HDRH, BYTE1(n))

#define HDP_PSCR_MSK                    (BIT5 | BIT4 | BIT_LN)
#define LIN_SetHeaderPrescale(n)        MODIFY_LIN(HDP, HDP_PSCR_MSK, ((n) << 0))

/////////////////////////////////////////////////

#define READ_CAN(r)                     (ACC = READ_REG(r), READ_REG(r))
#define WRITE_CAN(r, dat)               (WRITE_REG((r), (dat)))
#define MODIFY_CAN(r, clr, set)         (ACC = READ_REG(r), MODIFY_REG((r), (clr), (set)))
#define CLR_CAN_BIT(r, b)               (ACC = READ_REG(r), CLR_REG_BIT((r), (b)))
#define SET_CAN_BIT(r, b)               (ACC = READ_REG(r), SET_REG_BIT((r), (b)))
#define READ_CAN_BIT(r, b)              (ACC = READ_REG(r), READ_REG_BIT((r), (b)))

#define AUXR2_CAN1EN_MSK                BIT1
#define CAN1_Enable()                   SET_REG_BIT(AUXR2, AUXR2_CAN1EN_MSK)
#define CAN1_Disable()                  CLR_REG_BIT(AUXR2, AUXR2_CAN1EN_MSK)

#define AUXR2_CAN2EN_MSK                BIT2
#define CAN2_Enable()                   SET_REG_BIT(AUXR2, AUXR2_CAN2EN_MSK)
#define CAN2_Disable()                  CLR_REG_BIT(AUXR2, AUXR2_CAN2EN_MSK)

#define AUXR2_CANEDIN_MSK               BIT3
#define CAN16_LittleEndian()            CLR_REG_BIT(AUXR2, AUXR2_CANEDIN_MSK)
#define CAN16_BigEndian()               SET_REG_BIT(AUXR2, AUXR2_CANEDIN_MSK)
#define CAN16_SetEndianMode(n)          MODIFY_REG(AUXR2, AUXR2_CANEDIN_MSK, (((n) & 1) << 3))

#define CANICR_CAN1IE_MSK               BIT1
#define CAN1_EnableInt()                SET_REG_BIT(CANICR, CANICR_CAN1IE_MSK)
#define CAN1_DisableInt()               CLR_REG_BIT(CANICR, CANICR_CAN1IE_MSK)

#define CANICR_PCAN1L_MSK               BIT0
#define CANICR_PCAN1H_MSK               BIT3
#define CAN1_SetIntPriority(n)          MODIFY_REG(CANICR, CANICR_PCAN1L_MSK, (((n) & 1) << 0)); \
                                        MODIFY_REG(CANICR, CANICR_PCAN1H_MSK, ((((n) >> 1) & 1) << 3))

#define CANICR_CAN2IE_MSK               BIT5
#define CAN2_EnableInt()                SET_REG_BIT(CANICR, CANICR_CAN2IE_MSK)
#define CAN2_DisableInt()               CLR_REG_BIT(CANICR, CANICR_CAN2IE_MSK)

#define CANICR_PCAN2L_MSK               BIT4
#define CANICR_PCAN2H_MSK               BIT7
#define CAN2_SetIntPriority(n)          MODIFY_REG(CANICR, CANICR_PCAN2L_MSK, (((n) & 1) << 4)); \
                                        MODIFY_REG(CANICR, CANICR_PCAN2H_MSK, ((((n) >> 1) & 1) << 7))

#define CAN1AUXCR_STBYEN_MSK            BIT6
#define CAN1_EnableStandbyPin()         SET_REG_BIT(CAN1_AUX_CR, CAN1AUXCR_STBYEN_MSK)
#define CAN1_DisableStandbyPin()        CLR_REG_BIT(CAN1_AUX_CR, CAN1AUXCR_STBYEN_MSK)

#define CAN2AUXCR_STBYEN_MSK            BIT6
#define CAN2_EnableStandbyPin()         SET_REG_BIT(CAN2_AUX_CR, CAN2AUXCR_STBYEN_MSK)
#define CAN2_DisableStandbyPin()        CLR_REG_BIT(CAN2_AUX_CR, CAN2AUXCR_STBYEN_MSK)

#define CAN1_WriteRBUF(n, d)            WRITE_CAN(CAN_RBUF[n], (d))
#define CAN1_ReadRBUF(n)                READ_CAN(CAN_RBUF[n])

#define CAN1_WriteTBUF(n, d)            WRITE_CAN(CAN_TBUF[n], (d))
#define CAN1_ReadTBUF(n)                READ_CAN(CAN_TBUF[n])

#define CAN1_WriteTTS(n, d)             WRITE_CAN(CAN_TTS[n], (d))
#define CAN1_ReadTTS(n)                 READ_CAN(CAN_TTS[n])

#define CANCFGSTAT_RESET_MSK            BIT7
#define CAN1_EnterResetMode()           SET_CAN_BIT(CAN_CFG_STAT, CANCFGSTAT_RESET_MSK)
#define CAN1_ExitResetMode()            CLR_CAN_BIT(CAN_CFG_STAT, CANCFGSTAT_RESET_MSK)

#define CANCFGSTAT_LBM_MSK              (BIT6 | BIT5)
#define CANTCMD_LOM_MSK                 BIT6
#define CAN1_ExternalLoopBackMode()     MODIFY_CAN(CAN_CFG_STAT, CANCFGSTAT_LBM_MSK, ((2) << 5)); \
                                        CLR_CAN_BIT(CAN_TCMD, CANTCMD_LOM_MSK)
#define CAN1_InternalLoopBackMode()     MODIFY_CAN(CAN_CFG_STAT, CANCFGSTAT_LBM_MSK, ((1) << 5)); \
                                        CLR_CAN_BIT(CAN_TCMD, CANTCMD_LOM_MSK)
#define CAN1_ListenOnlyMode()           MODIFY_CAN(CAN_CFG_STAT, CANCFGSTAT_LBM_MSK, ((0) << 5)); \
                                        SET_CAN_BIT(CAN_TCMD, CANTCMD_LOM_MSK)
#define CAN1_ExtLoopBackListenMode()    MODIFY_CAN(CAN_CFG_STAT, CANCFGSTAT_LBM_MSK, ((2) << 5)); \
                                        SET_CAN_BIT(CAN_TCMD, CANTCMD_LOM_MSK)
#define CAN1_NormalMode()               MODIFY_CAN(CAN_CFG_STAT, CANCFGSTAT_LBM_MSK, ((0) << 5)); \
                                        CLR_CAN_BIT(CAN_TCMD, CANTCMD_LOM_MSK)

#define CANCFGSTAT_TPSS_MSK             BIT4
#define CAN1_PTBSingleShotTransmit()    SET_CAN_BIT(CAN_CFG_STAT, CANCFGSTAT_TPSS_MSK)
#define CAN1_PTBAutoRetransmit()        CLR_CAN_BIT(CAN_CFG_STAT, CANCFGSTAT_TPSS_MSK)

#define CANCFGSTAT_TSSS_MSK             BIT3
#define CAN1_STBSingleShotTransmit()    SET_CAN_BIT(CAN_CFG_STAT, CANCFGSTAT_TSSS_MSK)
#define CAN1_STBAutoRetransmit()        CLR_CAN_BIT(CAN_CFG_STAT, CANCFGSTAT_TSSS_MSK)

#define CANCFGSTAT_RACTIVE_MSK          BIT2
#define CANCFGSTAT_TACTIVE_MSK          BIT1
#define CAN1_CheckReceiveStatus()       READ_CAN_BIT(CAN_CFG_STAT, CANCFGSTAT_RACTIVE_MSK)
#define CAN1_CheckTransmitStatus()      READ_CAN_BIT(CAN_CFG_STAT, CANCFGSTAT_TACTIVE_MSK)

#define CANCFGSTAT_BUSOFF_MSK           BIT0
#define CAN1_EnterBusOffStatus()        SET_CAN_BIT(CAN_CFG_STAT, CANCFGSTAT_BUSOFF_MSK)
#define CAN1_ExitBusOffStatus()         CLR_CAN_BIT(CAN_CFG_STAT, CANCFGSTAT_BUSOFF_MSK)
#define CAN1_CheckBusOffStatus()        READ_CAN_BIT(CAN_CFG_STAT, CANCFGSTAT_BUSOFF_MSK)

#define CANTCMD_TBSEL_MSK               BIT7
#define CAN1_SelectPTB()                CLR_CAN_BIT(CAN_TCMD, CANTCMD_TBSEL_MSK)
#define CAN1_SelectSTB()                SET_CAN_BIT(CAN_TCMD, CANTCMD_TBSEL_MSK)

#define CANTCMD_TPE_MSK                 BIT4
#define CAN1_TransmitPTB()              SET_CAN_BIT(CAN_TCMD, CANTCMD_TPE_MSK)

#define CANTCMD_TPA_MSK                 BIT3
#define CAN1_AbortTransmitPTB()         SET_CAN_BIT(CAN_TCMD, CANTCMD_TPA_MSK)

#define CANTCMD_TSONE_MSK               BIT2
#define CANTCMD_TSALL_MSK               BIT1
#define CAN1_TransmitOneSTB()           SET_CAN_BIT(CAN_TCMD, CANTCMD_TSONE_MSK)
#define CAN1_TransmitAllSTB()           SET_CAN_BIT(CAN_TCMD, CANTCMD_TSALL_MSK)

#define CANTCMD_TSA_MSK                 BIT0
#define CAN1_AbortTransmitSTB()         SET_CAN_BIT(CAN_TCMD, CANTCMD_TSA_MSK)

#define CANTCTRL_FDISO_MSK              BIT7
#define CAN1_FD_BoschMode()             CLR_CAN_BIT(CAN_TCTRL, CANTCTRL_FDISO_MSK)
#define CAN1_FD_ISO11898Mode()          SET_CAN_BIT(CAN_TCTRL, CANTCTRL_FDISO_MSK)

#define CANTCTRL_TSNEXT_MSK             BIT6
#define CAN1_SelectNextTBSlot()         SET_CAN_BIT(CAN_TCTRL, CANTCTRL_TSNEXT_MSK)

#define CANTCTRL_TSMODE_MSK             BIT5
#define CAN1_STBPriorityFIFO()          CLR_CAN_BIT(CAN_TCTRL, CANTCTRL_TSMODE_MSK)
#define CAN1_STBPriorityID()            SET_CAN_BIT(CAN_TCTRL, CANTCTRL_TSMODE_MSK)

#define CANTCTRL_TTTBM_MSK              BIT4
#define CAN1_TTCAN_NormalMode()         CLR_CAN_BIT(CAN_TCTRL, CANTCTRL_TTTBM_MSK)
#define CAN1_TTCAN_PtrMode()            SET_CAN_BIT(CAN_TCTRL, CANTCTRL_TTTBM_MSK)

#define CANTCTRL_TSSTAT_MSK             (BIT1 | BIT0)
#define CAN1_CheckSTBStatus()           READ_CAN_BIT(CAN_TCTRL, CANTCTRL_TSSTAT_MSK)

#define CANRCTRL_SACK_MSK               BIT7
#define CAN1_EnableSelfACK()            SET_CAN_BIT(CAN_RCTRL, CANRCTRL_SACK_MSK)
#define CAN1_DisableSelfACK()           CLR_CAN_BIT(CAN_RCTRL, CANRCTRL_SACK_MSK)

#define CANRCTRL_ROM_MSK                BIT6
#define CAN1_OVFSaveNewest()            CLR_CAN_BIT(CAN_RCTRL, CANRCTRL_ROM_MSK)
#define CAN1_OVFDiscardNewest()         SET_CAN_BIT(CAN_RCTRL, CANRCTRL_ROM_MSK)

#define CANRCTRL_ROV_MSK                BIT5
#define CAN1_CheckRBUFOverflow()        READ_CAN_BIT(CAN_RCTRL, CANRCTRL_ROV_MSK)

#define CANRCTRL_RREL_MSK               BIT4
#define CAN1_ReleaseRBUF()              SET_CAN_BIT(CAN_RCTRL, CANRCTRL_RREL_MSK)

#define CANRCTRL_RBALL_MSK              BIT3
#define CAN1_RBStoreCorrectData()       CLR_CAN_BIT(CAN_RCTRL, CANRCTRL_RBALL_MSK)
#define CAN1_RBStoreAllEvenError()      SET_CAN_BIT(CAN_RCTRL, CANRCTRL_RBALL_MSK)

#define CANRCTRL_RSTAT_MSK              (BIT1 | BIT0)
#define CANRCTRL_RSTAT_EMPTY            ((0) << 0)
#define CANRCTRL_RSTAT_LESSLIMIT        ((1) << 0)
#define CANRCTRL_RSTAT_MORELIMIT        ((2) << 0)
#define CANRCTRL_RSTAT_FULL             ((3) << 0)
#define CAN1_CheckRBStatus()            READ_CAN_BIT(CAN_RCTRL, CANRCTRL_RSTAT_MSK)

#define CANRTIE_RIE_MSK                 BIT7
#define CANRTIE_ROIE_MSK                BIT6
#define CANRTIE_RFIE_MSK                BIT5
#define CANRTIE_RAFIE_MSK               BIT4
#define CANRTIE_TPIE_MSK                BIT3
#define CANRTIE_TSIE_MSK                BIT2
#define CANRTIE_EIE_MSK                 BIT1
#define CANERRINT_EPIE_MSK              BIT5
#define CANERRINT_ALIE_MSK              BIT3
#define CANERRINT_BEIE_MSK              BIT1
#define CAN1_EnableReceiveInt()         SET_CAN_BIT(CAN_RTIE, CANRTIE_RIE_MSK)
#define CAN1_EnableRBOverrunInt()       SET_CAN_BIT(CAN_RTIE, CANRTIE_ROIE_MSK)
#define CAN1_EnableRBFIFOFullInt()      SET_CAN_BIT(CAN_RTIE, CANRTIE_RFIE_MSK)
#define CAN1_EnableRBAlmostFullInt()    SET_CAN_BIT(CAN_RTIE, CANRTIE_RAFIE_MSK)
#define CAN1_EnablePTBTransmitInt()     SET_CAN_BIT(CAN_RTIE, CANRTIE_TPIE_MSK)
#define CAN1_EnableSTBTransmitInt()     SET_CAN_BIT(CAN_RTIE, CANRTIE_TSIE_MSK)
#define CAN1_EnableErrorInt()           SET_CAN_BIT(CAN_RTIE, CANRTIE_EIE_MSK)
#define CAN1_EnableErrorPassiveInt()    SET_CAN_BIT(CAN_ERRINT, CANERRINT_EPIE_MSK)
#define CAN1_EnableArbitrateLostInt()   SET_CAN_BIT(CAN_ERRINT, CANERRINT_ALIE_MSK)
#define CAN1_EnableBusErrorInt()        SET_CAN_BIT(CAN_ERRINT, CANERRINT_BEIE_MSK)
#define CAN1_DisableReceiveInt()        CLR_CAN_BIT(CAN_RTIE, CANRTIE_RIE_MSK)
#define CAN1_DisableRBOverrunInt()      CLR_CAN_BIT(CAN_RTIE, CANRTIE_ROIE_MSK)
#define CAN1_DisableRBFIFOFullInt()     CLR_CAN_BIT(CAN_RTIE, CANRTIE_RFIE_MSK)
#define CAN1_DisableRBAlmostFullInt()   CLR_CAN_BIT(CAN_RTIE, CANRTIE_RAFIE_MSK)
#define CAN1_DisablePTBTransmitInt()    CLR_CAN_BIT(CAN_RTIE, CANRTIE_TPIE_MSK)
#define CAN1_DisableSTBTransmitInt()    CLR_CAN_BIT(CAN_RTIE, CANRTIE_TSIE_MSK)
#define CAN1_DisableErrorInt()          CLR_CAN_BIT(CAN_RTIE, CANRTIE_EIE_MSK)
#define CAN1_DisableErrorPassiveInt()   CLR_CAN_BIT(CAN_ERRINT, CANERRINT_EPIE_MSK)
#define CAN1_DisableArbitrateLostInt()  CLR_CAN_BIT(CAN_ERRINT, CANERRINT_ALIE_MSK)
#define CAN1_DisableBusErrorInt()       CLR_CAN_BIT(CAN_ERRINT, CANERRINT_BEIE_MSK)

#define CANRTIF_RIF_MSK                 BIT7
#define CANRTIF_ROIF_MSK                BIT6
#define CANRTIF_RFIF_MSK                BIT5
#define CANRTIF_RAFIF_MSK               BIT4
#define CANRTIF_TPIF_MSK                BIT3
#define CANRTIF_TSIF_MSK                BIT2
#define CANRTIF_EIF_MSK                 BIT1
#define CANRTIF_AIF_MSK                 BIT0
#define CANERRINT_EPIF_MSK              BIT4
#define CANERRINT_ALIF_MSK              BIT2
#define CANERRINT_BEIF_MSK              BIT0
#define CANRTIF_ALL_MSK                 (BIT_ALL)
#define CANERRINT_ALL_MSK               (BIT4 | BIT2 | BIT0)
#define CAN1_CheckReceive(f)            READ_REG_BIT((f), CANRTIF_RIF_MSK)
#define CAN1_CheckRBOverrun(f)          READ_REG_BIT((f), CANRTIF_ROIF_MSK)
#define CAN1_CheckRBFIFOFull(f)         READ_REG_BIT((f), CANRTIF_RFIF_MSK)
#define CAN1_CheckRBAlmostFull(f)       READ_REG_BIT((f), CANRTIF_RAFIF_MSK)
#define CAN1_CheckPTBTransmit(f)        READ_REG_BIT((f), CANRTIF_TPIF_MSK)
#define CAN1_CheckSTBTransmit(f)        READ_REG_BIT((f), CANRTIF_TSIF_MSK)
#define CAN1_CheckError(f)              READ_REG_BIT((f), CANRTIF_EIF_MSK)
#define CAN1_CheckAbort(f)              READ_REG_BIT((f), CANRTIF_AIF_MSK)
#define CAN1_CheckErrorPassive(f)       READ_REG_BIT((f), CANERRINT_EPIF_MSK)
#define CAN1_CheckArbitrateLost(f)      READ_REG_BIT((f), CANERRINT_ALIF_MSK)
#define CAN1_CheckBusError(f)           READ_REG_BIT((f), CANERRINT_BEIF_MSK)

#define CAN1_ReadIntStatus()            (READ_CAN(CAN_RTIF) & CANRTIF_ALL_MSK)
#define CAN1_ReadErrorStatus()          (READ_CAN(CAN_ERRINT) & CANERRINT_ALL_MSK)
#define CAN1_ClearFlags(n)              WRITE_CAN(CAN_RTIF, ((n) & CANRTIF_ALL_MSK))
#define CAN1_ClearErrorFlags(n)         WRITE_CAN(CAN_ERRINT, ((n) & CANERRINT_ALL_MSK))

#define CANRTIE_TSFF_MSK                BIT0
#define CAN1_CheckTBFullFlag()          READ_CAN_BIT(CAN_RTIE, CANRTIE_TSFF_MSK)

#define CANERRINT_EWARN_MSK             BIT7
#define CAN1_CheckErrorWarningLimit()   READ_CAN_BIT(CAN_ERRINT, CANERRINT_EWARN_MSK)

#define CANLIMIT_AFWL_MSK               (BIT_HN)
#define CANLIMIT_EWL_MSK                (BIT_LN)
#define CAN1_SetAFWLimit(n)             MODIFY_CAN(CAN_LIMIT, CANLIMIT_AFWL_MSK, ((n) << 4))
#define CAN1_SetEWLimit(n)              MODIFY_CAN(CAN_LIMIT, CANLIMIT_EWL_MSK, ((n) << 0))
#define CAN1_SetEWLimit_8()             CAN1_SetEWLimit(0)
#define CAN1_SetEWLimit_16()            CAN1_SetEWLimit(1)
#define CAN1_SetEWLimit_24()            CAN1_SetEWLimit(2)
#define CAN1_SetEWLimit_32()            CAN1_SetEWLimit(3)
#define CAN1_SetEWLimit_40()            CAN1_SetEWLimit(4)
#define CAN1_SetEWLimit_48()            CAN1_SetEWLimit(5)
#define CAN1_SetEWLimit_56()            CAN1_SetEWLimit(6)
#define CAN1_SetEWLimit_64()            CAN1_SetEWLimit(7)
#define CAN1_SetEWLimit_72()            CAN1_SetEWLimit(8)
#define CAN1_SetEWLimit_80()            CAN1_SetEWLimit(9)
#define CAN1_SetEWLimit_88()            CAN1_SetEWLimit(10)
#define CAN1_SetEWLimit_96()            CAN1_SetEWLimit(11)
#define CAN1_SetEWLimit_104()           CAN1_SetEWLimit(12)
#define CAN1_SetEWLimit_112()           CAN1_SetEWLimit(13)
#define CAN1_SetEWLimit_120()           CAN1_SetEWLimit(14)
#define CAN1_SetEWLimit_128()           CAN1_SetEWLimit(15)

#define CANSBT_SEG2_MSK                 (~(BIT7))
#define CANSBT_SJW_MSK                  (~(BIT7))
#define CAN1_SetSBT_SEG1(n)             WRITE_CAN(CAN_S_SEG1, (n))
#define CAN1_SetSBT_SEG2(n)             MODIFY_CAN(CAN_S_SEG2, CANSBT_SEG2_MSK, ((n) << 0))
#define CAN1_SetSBT_SJW(n)              MODIFY_CAN(CAN_S_SJW, CANSBT_SJW_MSK, ((n) << 0))
#define CAN1_SetSBT_PRESC(n)            WRITE_CAN(CAN_S_PRESC, (n))

#define CANFBT_SEG1_MSK                 (BIT4 | BIT_LN)
#define CANFBT_SEG2_MSK                 (BIT_LN)
#define CANFBT_SJW_MSK                  (BIT_LN)
#define CAN1_SetFBT_SEG1(n)             MODIFY_CAN(CAN_F_SEG1, CANFBT_SEG1_MSK, ((n) << 0))
#define CAN1_SetFBT_SEG2(n)             MODIFY_CAN(CAN_F_SEG2, CANFBT_SEG2_MSK, ((n) << 0))
#define CAN1_SetFBT_SJW(n)              MODIFY_CAN(CAN_F_SJW, CANFBT_SJW_MSK, ((n) << 0))
#define CAN1_SetFBT_PRESC(n)            WRITE_CAN(CAN_F_PRESC, (n))

#define CANEALCAP_KOER_MSK              (BIT7 | BIT6 | BIT5)
#define CANEALCAP_ALC_MSK               (BIT4 | BIT_LN)
#define CAN1_ReadErrorCode()            READ_CAN_BIT(CAN_EALCAP, CANEALCAP_KOER_MSK)
#define CAN1_ReadArbitrationLost()      READ_CAN_BIT(CAN_EALCAP, CANEALCAP_ALC_MSK)

#define CANTDC_TDCEN_MSK                BIT7
#define CAN1_EnableTDC()                SET_CAN_BIT(CAN_TDC, CANTDC_TDCEN_MSK)
#define CAN1_DisableTDC()               CLR_CAN_BIT(CAN_TDC, CANTDC_TDCEN_MSK)

#define CANTDC_SSPOFF_MSK               (~(BIT7))
#define CAN1_SetSSPOffset(n)            MODIFY_CAN(CAN_TDC, CANTDC_SSPOFF_MSK, ((n) << 0))

#define CAN1_GetRxErrorCouter()         READ_CAN(CAN_RECNT)
#define CAN1_GetTxErrorCouter()         READ_CAN(CAN_TECNT)

#define CANACFCTRL_SEL_MSK              BIT5
#define CAN1_SelectACFID()              CLR_CAN_BIT(CAN_ACFCTRL, CANACFCTRL_SEL_MSK)
#define CAN1_SelectACFMask()            SET_CAN_BIT(CAN_ACFCTRL, CANACFCTRL_SEL_MSK)

#define CANACFCTRL_ADR_MSK              (BIT_LN)
#define CAN1_SetACFAddress(n)           MODIFY_CAN(CAN_ACFCTRL, CANACFCTRL_ADR_MSK, ((n) << 0))

#define CANTIMECFG_TSPOS_MSK            BIT1
#define CAN1_TimeStampAtSOF()           CLR_CAN_BIT(CAN_TIMECFG, CANTIMECFG_TSPOS_MSK)
#define CAN1_TimeStampAtEOF()           SET_CAN_BIT(CAN_TIMECFG, CANTIMECFG_TSPOS_MSK)

#define CANTIMECFG_TSEN_MSK             BIT0
#define CAN1_DisableTimeStamp()         CLR_CAN_BIT(CAN_TIMECFG, CANTIMECFG_TSEN_MSK)
#define CAN1_EnableTimeStamp()          SET_CAN_BIT(CAN_TIMECFG, CANTIMECFG_TSEN_MSK)

#define CAN1_EnableACFL(n)              SET_CAN_BIT(CAN_ACF_EN0, BIT(n))
#define CAN1_EnableACFH(n)              SET_CAN_BIT(CAN_ACF_EN1, BIT(n))
#define CAN1_DisableACFL(n)             CLR_CAN_BIT(CAN_ACF_EN0, BIT(n))
#define CAN1_DisableACFH(n)             CLR_CAN_BIT(CAN_ACF_EN1, BIT(n))
#define CAN1_EnableACF(n)               SET_CAN_BIT(CAN_ACF_EN[(n) >> 3], (1 << ((n) & 0x07)))
#define CAN1_DisableACF(n)              CLR_CAN_BIT(CAN_ACF_EN[(n) >> 3], (1 << ((n) & 0x07)))

#define CANACF3_CODE_MSK                (BIT4 | BIT_LN)
#define CAN1_SetACF0(n)                 WRITE_CAN(CAN_ACF0, (n))
#define CAN1_SetACF1(n)                 WRITE_CAN(CAN_ACF1, (n))
#define CAN1_SetACF2(n)                 WRITE_CAN(CAN_ACF2, (n))
#define CAN1_SetACF3(n)                 MODIFY_CAN(CAN_ACF3, CANACF3_CODE_MSK, ((n) << 0))
#define CAN1_SetACF(n)                  CAN1_SetACF0(BYTE0(n)); \
                                        CAN1_SetACF1(BYTE1(n)); \
                                        CAN1_SetACF2(BYTE2(n)); \
                                        CAN1_SetACF3(BYTE3(n))

#define CANACF3_AIDE_MSK                BIT5
#define CANACF3_AIDEE_MSK               BIT6
#define CAN1_ACFAcceptStdFrame()        SET_CAN_BIT(CAN_ACF3, CANACF3_AIDEE_MSK); \
                                        CLR_CAN_BIT(CAN_ACF3, CANACF3_AIDE_MSK)
#define CAN1_ACFAcceptExtFrame()        SET_CAN_BIT(CAN_ACF3, CANACF3_AIDEE_MSK); \
                                        SET_CAN_BIT(CAN_ACF3, CANACF3_AIDE_MSK)
#define CAN1_ACFAcceptAllFrame()        CLR_CAN_BIT(CAN_ACF3, CANACF3_AIDEE_MSK)

#define CAN1_ReadVersion()              MAKEWORD(READ_CAN(CAN_VER0), READ_CAN(CAN_VER1))

#define CANTBSLOT_TBE_MSK               BIT7
#define CANTBSLOT_TBF_MSK               BIT6
#define CAN1_SetTBSlotToEmpty()         SET_CAN_BIT(CAN_TBSLOT, CANTBSLOT_TBE_MSK)
#define CAN1_SetTBSlotToFull()          SET_CAN_BIT(CAN_TBSLOT, CANTBSLOT_TBF_MSK)

#define CANTBSLOT_TBPTR_MSK             (BIT_LN)
#define CAN1_SetTBSlotPointer(n)        MODIFY_CAN(CAN_TBSLOT, CANTBSLOT_TBPTR_MSK, ((n) << 0))

#define CANTTCFG_WTIE_MSK               BIT7
#define CANTTCFG_WTIF_MSK               BIT6
#define CAN1_EnableWatchTriggerInt()    SET_CAN_BIT(CAN_TTCFG, CANTTCFG_WTIE_MSK)
#define CAN1_DisableWatchTriggerInt()   CLR_CAN_BIT(CAN_TTCFG, CANTTCFG_WTIE_MSK)
#define CAN1_CheckWatchTriggerFlag()    READ_CAN_BIT(CAN_TTCFG, CANTTCFG_WTIF_MSK)

#define CANTTCFG_TEIF_MSK               BIT5
#define CANTTCFG_TTIE_MSK               BIT4
#define CANTTCFG_TTIF_MSK               BIT3
#define CAN1_EnableTimeTriggerInt()     SET_CAN_BIT(CAN_TTCFG, CANTTCFG_TTIE_MSK)
#define CAN1_DisableTimeTriggerInt()    CLR_CAN_BIT(CAN_TTCFG, CANTTCFG_TTIE_MSK)
#define CAN1_CheckTimeTriggerFlag()     READ_CAN_BIT(CAN_TTCFG, CANTTCFG_TTIF_MSK)
#define CAN1_CheckTriggerErrorFlag()    READ_CAN_BIT(CAN_TTCFG, CANTTCFG_TEIF_MSK)

#define CANTTCFG_PRESC_MSK              (BIT2 | BIT1)
#define CAN1_SetTTTimerPrescale(n)      MODIFY_CAN(CAN_TTCFG, CANTTCFG_PRESC_MSK, ((n) << 1))
#define CAN1_SetTTTimerPrescale1()      CAN1_SetTTTimerPrescale(0)
#define CAN1_SetTTTimerPrescale2()      CAN1_SetTTTimerPrescale(1)
#define CAN1_SetTTTimerPrescale4()      CAN1_SetTTTimerPrescale(2)
#define CAN1_SetTTTimerPrescale8()      CAN1_SetTTTimerPrescale(3)

#define CANTTCFG_TTEN_MSK               BIT0
#define CAN1_EnableTimeTrigger()        SET_CAN_BIT(CAN_TTCFG, CANTTCFG_TTEN_MSK)
#define CAN1_DisableTimeTrigger()       CLR_CAN_BIT(CAN_TTCFG, CANTTCFG_TTEN_MSK)

#define CANREFMSG3_REFID_MSK            (BIT4 | BIT_LN)
#define CAN1_SetREFID0(n)               WRITE_CAN(CAN_REF_MSG0, (n))
#define CAN1_SetREFID1(n)               WRITE_CAN(CAN_REF_MSG1, (n))
#define CAN1_SetREFID2(n)               WRITE_CAN(CAN_REF_MSG2, (n))
#define CAN1_SetREFID3(n)               MODIFY_CAN(CAN_REF_MSG3, CANREFMSG3_REFID_MSK, ((n) << 0))
#define CAN1_SetREFID(n)                CAN1_SetREFID0(BYTE0(n)); \
                                        CAN1_SetREFID1(BYTE1(n)); \
                                        CAN1_SetREFID2(BYTE2(n)); \
                                        CAN1_SetREFID3(BYTE3(n))

#define CANREFMSG3_REFIDE_MSK           BIT7
#define CAN1_StandardREFID()            CLR_CAN_BIT(CAN_REF_MSG3, CANREFMSG3_REFIDE_MSK)
#define CAN1_ExtendedREFID()            SET_CAN_BIT(CAN_REF_MSG3, CANREFMSG3_REFIDE_MSK)

#define CANTRIGCFG0_TTPTR_MSK           (BIT5 | BIT4 | BIT_LN)
#define CAN1_SetTTBSlotPointer(n)       MODIFY_CAN(CAN_TRIG_CFG0, CANTRIGCFG0_TTPTR_MSK, ((n) << 0))

#define CANTRIGCFG1_TTYPE_MSK           (BIT2 | BIT1 | BIT0)
#define CAN1_SetTriggerType(n)          MODIFY_CAN(CAN_TRIG_CFG1, CANTRIGCFG1_TTYPE_MSK, ((n) << 0))

#define CANTRIGCFG1_TEWE_MSK            (BIT_HN)
#define CAN1_SetTransEnableWindow(n)    MODIFY_CAN(CAN_TRIG_CFG1, CANTRIGCFG1_TEWE_MSK, ((n) << 4))

#define CAN1_SetTriggerTime(n)          (WRITE_CAN(CAN_TT_CFG0, LOBYTE(n)), WRITE_CAN(CAN_TT_CFG1, HIBYTE(n)))
#define CAN1_SetWatchTriggerTime(n)     (WRITE_CAN(CAN_TT_WTRIG0, LOBYTE(n)), WRITE_CAN(CAN_TT_WTRIG1, HIBYTE(n)))

////////////////////////

#define CAN2_WriteRBUF(n, d)            WRITE_CAN(CAN2_RBUF[n], (d))
#define CAN2_ReadRBUF(n)                READ_CAN(CAN2_RBUF[n])

#define CAN2_WriteTBUF(n, d)            WRITE_CAN(CAN2_TBUF[n], (d))
#define CAN2_ReadTBUF(n)                READ_CAN(CAN2_TBUF[n])

#define CAN2_WriteTTS(n, d)             WRITE_CAN(CAN2_TTS[n], (d))
#define CAN2_ReadTTS(n)                 READ_CAN(CAN2_TTS[n])

#define CAN2CFGSTAT_RESET_MSK           BIT7
#define CAN2_EnterResetMode()           SET_CAN_BIT(CAN2_CFG_STAT, CAN2CFGSTAT_RESET_MSK)
#define CAN2_ExitResetMode()            CLR_CAN_BIT(CAN2_CFG_STAT, CAN2CFGSTAT_RESET_MSK)

#define CAN2CFGSTAT_LBM_MSK             (BIT6 | BIT5)
#define CAN2TCMD_LOM_MSK                BIT6
#define CAN2_ExternalLoopBackMode()     MODIFY_CAN(CAN2_CFG_STAT, CAN2CFGSTAT_LBM_MSK, ((2) << 5)); \
                                        CLR_CAN_BIT(CAN2_TCMD, CAN2TCMD_LOM_MSK)
#define CAN2_InternalLoopBackMode()     MODIFY_CAN(CAN2_CFG_STAT, CAN2CFGSTAT_LBM_MSK, ((1) << 5)); \
                                        CLR_CAN_BIT(CAN2_TCMD, CAN2TCMD_LOM_MSK)
#define CAN2_ListenOnlyMode()           MODIFY_CAN(CAN2_CFG_STAT, CAN2CFGSTAT_LBM_MSK, ((0) << 5)); \
                                        SET_CAN_BIT(CAN2_TCMD, CAN2TCMD_LOM_MSK)
#define CAN2_ExtLoopBackListenMode()    MODIFY_CAN(CAN2_CFG_STAT, CAN2CFGSTAT_LBM_MSK, ((2) << 5)); \
                                        SET_CAN_BIT(CAN2_TCMD, CAN2TCMD_LOM_MSK)
#define CAN2_NormalMode()               MODIFY_CAN(CAN2_CFG_STAT, CAN2CFGSTAT_LBM_MSK, ((0) << 5)); \
                                        CLR_CAN_BIT(CAN2_TCMD, CAN2TCMD_LOM_MSK)

#define CAN2CFGSTAT_TPSS_MSK            BIT4
#define CAN2_PTBSingleShotTransmit()    SET_CAN_BIT(CAN2_CFG_STAT, CAN2CFGSTAT_TPSS_MSK)
#define CAN2_PTBAutoRetransmit()        CLR_CAN_BIT(CAN2_CFG_STAT, CAN2CFGSTAT_TPSS_MSK)

#define CAN2CFGSTAT_TSSS_MSK            BIT3
#define CAN2_STBSingleShotTransmit()    SET_CAN_BIT(CAN2_CFG_STAT, CAN2CFGSTAT_TSSS_MSK)
#define CAN2_STBAutoRetransmit()        CLR_CAN_BIT(CAN2_CFG_STAT, CAN2CFGSTAT_TSSS_MSK)

#define CAN2CFGSTAT_RACTIVE_MSK         BIT2
#define CAN2CFGSTAT_TACTIVE_MSK         BIT1
#define CAN2_CheckReceiveStatus()       READ_CAN_BIT(CAN2_CFG_STAT, CAN2CFGSTAT_RACTIVE_MSK)
#define CAN2_CheckTransmitStatus()      READ_CAN_BIT(CAN2_CFG_STAT, CAN2CFGSTAT_TACTIVE_MSK)

#define CAN2CFGSTAT_BUSOFF_MSK          BIT0
#define CAN2_EnterBusOffStatus()        SET_CAN_BIT(CAN2_CFG_STAT, CAN2CFGSTAT_BUSOFF_MSK)
#define CAN2_ExitBusOffStatus()         CLR_CAN_BIT(CAN2_CFG_STAT, CAN2CFGSTAT_BUSOFF_MSK)
#define CAN2_CheckBusOffStatus()        READ_CAN_BIT(CAN2_CFG_STAT, CAN2CFGSTAT_BUSOFF_MSK)

#define CAN2TCMD_TBSEL_MSK              BIT7
#define CAN2_SelectPTB()                CLR_CAN_BIT(CAN2_TCMD, CAN2TCMD_TBSEL_MSK)
#define CAN2_SelectSTB()                SET_CAN_BIT(CAN2_TCMD, CAN2TCMD_TBSEL_MSK)

#define CAN2TCMD_TPE_MSK                BIT4
#define CAN2_TransmitPTB()              SET_CAN_BIT(CAN2_TCMD, CAN2TCMD_TPE_MSK)

#define CAN2TCMD_TPA_MSK                BIT3
#define CAN2_AbortTransmitPTB()         SET_CAN_BIT(CAN2_TCMD, CAN2TCMD_TPA_MSK)

#define CAN2TCMD_TSONE_MSK              BIT2
#define CAN2TCMD_TSALL_MSK              BIT1
#define CAN2_TransmitOneSTB()           SET_CAN_BIT(CAN2_TCMD, CAN2TCMD_TSONE_MSK)
#define CAN2_TransmitAllSTB()           SET_CAN_BIT(CAN2_TCMD, CAN2TCMD_TSALL_MSK)

#define CAN2TCMD_TSA_MSK                BIT0
#define CAN2_AbortTransmitSTB()         SET_CAN_BIT(CAN2_TCMD, CAN2TCMD_TSA_MSK)

#define CAN2TCTRL_FDISO_MSK             BIT7
#define CAN2_FD_BoschMode()             CLR_CAN_BIT(CAN2_TCTRL, CAN2TCTRL_FDISO_MSK)
#define CAN2_FD_ISO11898Mode()          SET_CAN_BIT(CAN2_TCTRL, CAN2TCTRL_FDISO_MSK)

#define CAN2TCTRL_TSNEXT_MSK            BIT6
#define CAN2_SelectNextTBSlot()         SET_CAN_BIT(CAN2_TCTRL, CAN2TCTRL_TSNEXT_MSK)

#define CAN2TCTRL_TSMODE_MSK            BIT5
#define CAN2_STBPriorityFIFO()          CLR_CAN_BIT(CAN2_TCTRL, CAN2TCTRL_TSMODE_MSK)
#define CAN2_STBPriorityID()            SET_CAN_BIT(CAN2_TCTRL, CAN2TCTRL_TSMODE_MSK)

#define CAN2TCTRL_TTTBM_MSK             BIT4
#define CAN2_TTCAN2_NormalMode()         CLR_CAN_BIT(CAN2_TCTRL, CAN2TCTRL_TTTBM_MSK)
#define CAN2_TTCAN2_PtrMode()            SET_CAN_BIT(CAN2_TCTRL, CAN2TCTRL_TTTBM_MSK)

#define CAN2TCTRL_TSSTAT_MSK            (BIT1 | BIT0)
#define CAN2_CheckSTBStatus()           READ_CAN_BIT(CAN2_TCTRL, CAN2TCTRL_TSSTAT_MSK)

#define CAN2RCTRL_SACK_MSK              BIT7
#define CAN2_EnableSelfACK()            SET_CAN_BIT(CAN2_RCTRL, CAN2RCTRL_SACK_MSK)
#define CAN2_DisableSelfACK()           CLR_CAN_BIT(CAN2_RCTRL, CAN2RCTRL_SACK_MSK)

#define CAN2RCTRL_ROM_MSK               BIT6
#define CAN2_OVFSaveNewest()            CLR_CAN_BIT(CAN2_RCTRL, CAN2RCTRL_ROM_MSK)
#define CAN2_OVFDiscardNewest()         SET_CAN_BIT(CAN2_RCTRL, CAN2RCTRL_ROM_MSK)

#define CAN2RCTRL_ROV_MSK               BIT5
#define CAN2_CheckRBUFOverflow()        READ_CAN_BIT(CAN2_RCTRL, CAN2RCTRL_ROV_MSK)

#define CAN2RCTRL_RREL_MSK              BIT4
#define CAN2_ReleaseRBUF()              SET_CAN_BIT(CAN2_RCTRL, CAN2RCTRL_RREL_MSK)

#define CAN2RCTRL_RBALL_MSK             BIT3
#define CAN2_RBStoreCorrectData()       CLR_CAN_BIT(CAN2_RCTRL, CAN2RCTRL_RBALL_MSK)
#define CAN2_RBStoreAllEvenError()      SET_CAN_BIT(CAN2_RCTRL, CAN2RCTRL_RBALL_MSK)

#define CAN2RCTRL_RSTAT_MSK             (BIT1 | BIT0)
#define CAN2RCTRL_RSTAT_EMPTY           ((0) << 0)
#define CAN2RCTRL_RSTAT_LESSLIMIT       ((1) << 0)
#define CAN2RCTRL_RSTAT_MORELIMIT       ((2) << 0)
#define CAN2RCTRL_RSTAT_FULL            ((3) << 0)
#define CAN2_CheckRBStatus()            READ_CAN_BIT(CAN2_RCTRL, CAN2RCTRL_RSTAT_MSK)

#define CAN2RTIE_RIE_MSK                BIT7
#define CAN2RTIE_ROIE_MSK               BIT6
#define CAN2RTIE_RFIE_MSK               BIT5
#define CAN2RTIE_RAFIE_MSK              BIT4
#define CAN2RTIE_TPIE_MSK               BIT3
#define CAN2RTIE_TSIE_MSK               BIT2
#define CAN2RTIE_EIE_MSK                BIT1
#define CAN2ERRINT_EPIE_MSK             BIT5
#define CAN2ERRINT_ALIE_MSK             BIT3
#define CAN2ERRINT_BEIE_MSK             BIT1
#define CAN2_EnableReceiveInt()         SET_CAN_BIT(CAN2_RTIE, CAN2RTIE_RIE_MSK)
#define CAN2_EnableRBOverrunInt()       SET_CAN_BIT(CAN2_RTIE, CAN2RTIE_ROIE_MSK)
#define CAN2_EnableRBFIFOFullInt()      SET_CAN_BIT(CAN2_RTIE, CAN2RTIE_RFIE_MSK)
#define CAN2_EnableRBAlmostFullInt()    SET_CAN_BIT(CAN2_RTIE, CAN2RTIE_RAFIE_MSK)
#define CAN2_EnablePTBTransmitInt()     SET_CAN_BIT(CAN2_RTIE, CAN2RTIE_TPIE_MSK)
#define CAN2_EnableSTBTransmitInt()     SET_CAN_BIT(CAN2_RTIE, CAN2RTIE_TSIE_MSK)
#define CAN2_EnableErrorInt()           SET_CAN_BIT(CAN2_RTIE, CAN2RTIE_EIE_MSK)
#define CAN2_EnableErrorPassiveInt()    SET_CAN_BIT(CAN2_ERRINT, CAN2ERRINT_EPIE_MSK)
#define CAN2_EnableArbitrateLostInt()   SET_CAN_BIT(CAN2_ERRINT, CAN2ERRINT_ALIE_MSK)
#define CAN2_EnableBusErrorInt()        SET_CAN_BIT(CAN2_ERRINT, CAN2ERRINT_BEIE_MSK)
#define CAN2_DisableReceiveInt()        CLR_CAN_BIT(CAN2_RTIE, CAN2RTIE_RIE_MSK)
#define CAN2_DisableRBOverrunInt()      CLR_CAN_BIT(CAN2_RTIE, CAN2RTIE_ROIE_MSK)
#define CAN2_DisableRBFIFOFullInt()     CLR_CAN_BIT(CAN2_RTIE, CAN2RTIE_RFIE_MSK)
#define CAN2_DisableRBAlmostFullInt()   CLR_CAN_BIT(CAN2_RTIE, CAN2RTIE_RAFIE_MSK)
#define CAN2_DisablePTBTransmitInt()    CLR_CAN_BIT(CAN2_RTIE, CAN2RTIE_TPIE_MSK)
#define CAN2_DisableSTBTransmitInt()    CLR_CAN_BIT(CAN2_RTIE, CAN2RTIE_TSIE_MSK)
#define CAN2_DisableErrorInt()          CLR_CAN_BIT(CAN2_RTIE, CAN2RTIE_EIE_MSK)
#define CAN2_DisableErrorPassiveInt()   CLR_CAN_BIT(CAN2_ERRINT, CAN2ERRINT_EPIE_MSK)
#define CAN2_DisableArbitrateLostInt()  CLR_CAN_BIT(CAN2_ERRINT, CAN2ERRINT_ALIE_MSK)
#define CAN2_DisableBusErrorInt()       CLR_CAN_BIT(CAN2_ERRINT, CAN2ERRINT_BEIE_MSK)

#define CAN2RTIF_RIF_MSK                BIT7
#define CAN2RTIF_ROIF_MSK               BIT6
#define CAN2RTIF_RFIF_MSK               BIT5
#define CAN2RTIF_RAFIF_MSK              BIT4
#define CAN2RTIF_TPIF_MSK               BIT3
#define CAN2RTIF_TSIF_MSK               BIT2
#define CAN2RTIF_EIF_MSK                BIT1
#define CAN2RTIF_AIF_MSK                BIT0
#define CAN2ERRINT_EPIF_MSK             BIT4
#define CAN2ERRINT_ALIF_MSK             BIT2
#define CAN2ERRINT_BEIF_MSK             BIT0
#define CAN2RTIF_ALL_MSK                (BIT_ALL)
#define CAN2ERRINT_ALL_MSK              (BIT4 | BIT2 | BIT0)
#define CAN2_CheckReceive(f)            READ_REG_BIT((f), CAN2RTIF_RIF_MSK)
#define CAN2_CheckRBOverrun(f)          READ_REG_BIT((f), CAN2RTIF_ROIF_MSK)
#define CAN2_CheckRBFIFOFull(f)         READ_REG_BIT((f), CAN2RTIF_RFIF_MSK)
#define CAN2_CheckRBAlmostFull(f)       READ_REG_BIT((f), CAN2RTIF_RAFIF_MSK)
#define CAN2_CheckPTBTransmit(f)        READ_REG_BIT((f), CAN2RTIF_TPIF_MSK)
#define CAN2_CheckSTBTransmit(f)        READ_REG_BIT((f), CAN2RTIF_TSIF_MSK)
#define CAN2_CheckError(f)              READ_REG_BIT((f), CAN2RTIF_EIF_MSK)
#define CAN2_CheckAbort(f)              READ_REG_BIT((f), CAN2RTIF_AIF_MSK)
#define CAN2_CheckErrorPassive(f)       READ_REG_BIT((f), CAN2ERRINT_EPIF_MSK)
#define CAN2_CheckArbitrateLost(f)      READ_REG_BIT((f), CAN2ERRINT_ALIF_MSK)
#define CAN2_CheckBusError(f)           READ_REG_BIT((f), CAN2ERRINT_BEIF_MSK)

#define CAN2_ReadIntStatus()            (READ_CAN(CAN2_RTIF) & CAN2RTIF_ALL_MSK)
#define CAN2_ReadErrorStatus()          (READ_CAN(CAN2_ERRINT) & CAN2ERRINT_ALL_MSK)
#define CAN2_ClearFlags(n)              WRITE_CAN(CAN2_RTIF, ((n) & CAN2RTIF_ALL_MSK))
#define CAN2_ClearErrorFlags(n)         WRITE_CAN(CAN2_ERRINT, ((n) & CAN2ERRINT_ALL_MSK))

#define CAN2RTIE_TSFF_MSK               BIT0
#define CAN2_CheckTBFullFlag()          READ_CAN_BIT(CAN2_RTIE, CAN2RTIE_TSFF_MSK)

#define CAN2ERRINT_EWARN_MSK            BIT7
#define CAN2_CheckErrorWarningLimit()   READ_CAN_BIT(CAN2_ERRINT, CAN2ERRINT_EWARN_MSK)

#define CAN2LIMIT_AFWL_MSK              (BIT_HN)
#define CAN2LIMIT_EWL_MSK               (BIT_LN)
#define CAN2_SetAFWLimit(n)             MODIFY_CAN(CAN2_LIMIT, CAN2LIMIT_AFWL_MSK, ((n) << 4))
#define CAN2_SetEWLimit(n)              MODIFY_CAN(CAN2_LIMIT, CAN2LIMIT_EWL_MSK, ((n) << 0))
#define CAN2_SetEWLimit_8()             CAN2_SetEWLimit(0)
#define CAN2_SetEWLimit_16()            CAN2_SetEWLimit(1)
#define CAN2_SetEWLimit_24()            CAN2_SetEWLimit(2)
#define CAN2_SetEWLimit_32()            CAN2_SetEWLimit(3)
#define CAN2_SetEWLimit_40()            CAN2_SetEWLimit(4)
#define CAN2_SetEWLimit_48()            CAN2_SetEWLimit(5)
#define CAN2_SetEWLimit_56()            CAN2_SetEWLimit(6)
#define CAN2_SetEWLimit_64()            CAN2_SetEWLimit(7)
#define CAN2_SetEWLimit_72()            CAN2_SetEWLimit(8)
#define CAN2_SetEWLimit_80()            CAN2_SetEWLimit(9)
#define CAN2_SetEWLimit_88()            CAN2_SetEWLimit(10)
#define CAN2_SetEWLimit_96()            CAN2_SetEWLimit(11)
#define CAN2_SetEWLimit_104()           CAN2_SetEWLimit(12)
#define CAN2_SetEWLimit_112()           CAN2_SetEWLimit(13)
#define CAN2_SetEWLimit_120()           CAN2_SetEWLimit(14)
#define CAN2_SetEWLimit_128()           CAN2_SetEWLimit(15)

#define CAN2SBT_SEG2_MSK                (~(BIT7))
#define CAN2SBT_SJW_MSK                 (~(BIT7))
#define CAN2_SetSBT_SEG1(n)             WRITE_CAN(CAN2_S_SEG1, (n))
#define CAN2_SetSBT_SEG2(n)             MODIFY_CAN(CAN2_S_SEG2, CAN2SBT_SEG2_MSK, ((n) << 0))
#define CAN2_SetSBT_SJW(n)              MODIFY_CAN(CAN2_S_SJW, CAN2SBT_SJW_MSK, ((n) << 0))
#define CAN2_SetSBT_PRESC(n)            WRITE_CAN(CAN2_S_PRESC, (n))

#define CAN2FBT_SEG1_MSK                (BIT4 | BIT_LN)
#define CAN2FBT_SEG2_MSK                (BIT_LN)
#define CAN2FBT_SJW_MSK                 (BIT_LN)
#define CAN2_SetFBT_SEG1(n)             MODIFY_CAN(CAN2_F_SEG1, CAN2FBT_SEG1_MSK, ((n) << 0))
#define CAN2_SetFBT_SEG2(n)             MODIFY_CAN(CAN2_F_SEG2, CAN2FBT_SEG2_MSK, ((n) << 0))
#define CAN2_SetFBT_SJW(n)              MODIFY_CAN(CAN2_F_SJW, CAN2FBT_SJW_MSK, ((n) << 0))
#define CAN2_SetFBT_PRESC(n)            WRITE_CAN(CAN2_F_PRESC, (n))

#define CAN2EALCAP_KOER_MSK             (BIT7 | BIT6 | BIT5)
#define CAN2EALCAP_ALC_MSK              (BIT4 | BIT_LN)
#define CAN2_ReadErrorCode()            READ_CAN_BIT(CAN2_EALCAP, CAN2EALCAP_KOER_MSK)
#define CAN2_ReadArbitrationLost()      READ_CAN_BIT(CAN2_EALCAP, CAN2EALCAP_ALC_MSK)

#define CAN2TDC_TDCEN_MSK               BIT7
#define CAN2_EnableTDC()                SET_CAN_BIT(CAN2_TDC, CAN2TDC_TDCEN_MSK)
#define CAN2_DisableTDC()               CLR_CAN_BIT(CAN2_TDC, CAN2TDC_TDCEN_MSK)

#define CAN2TDC_SSPOFF_MSK              (~(BIT7))
#define CAN2_SetSSPOffset(n)            MODIFY_CAN(CAN2_TDC, CAN2TDC_SSPOFF_MSK, ((n) << 0))

#define CAN2_GetRxErrorCouter()         READ_CAN(CAN2_RECNT)
#define CAN2_GetTxErrorCouter()         READ_CAN(CAN2_TECNT)

#define CAN2ACFCTRL_SEL_MSK             BIT5
#define CAN2_SelectACFID()              CLR_CAN_BIT(CAN2_ACFCTRL, CAN2ACFCTRL_SEL_MSK)
#define CAN2_SelectACFMask()            SET_CAN_BIT(CAN2_ACFCTRL, CAN2ACFCTRL_SEL_MSK)

#define CAN2ACFCTRL_ADR_MSK             (BIT_LN)
#define CAN2_SetACFAddress(n)           MODIFY_CAN(CAN2_ACFCTRL, CAN2ACFCTRL_ADR_MSK, ((n) << 0))

#define CAN2TIMECFG_TSPOS_MSK           BIT1
#define CAN2_TimeStampAtSOF()           CLR_CAN_BIT(CAN2_TIMECFG, CAN2TIMECFG_TSPOS_MSK)
#define CAN2_TimeStampAtEOF()           SET_CAN_BIT(CAN2_TIMECFG, CAN2TIMECFG_TSPOS_MSK)

#define CAN2TIMECFG_TSEN_MSK            BIT0
#define CAN2_DisableTimeStamp()         CLR_CAN_BIT(CAN2_TIMECFG, CAN2TIMECFG_TSEN_MSK)
#define CAN2_EnableTimeStamp()          SET_CAN_BIT(CAN2_TIMECFG, CAN2TIMECFG_TSEN_MSK)

#define CAN2_EnableACFL(n)              SET_CAN_BIT(CAN2_ACF_EN0, BIT(n))
#define CAN2_EnableACFH(n)              SET_CAN_BIT(CAN2_ACF_EN1, BIT(n))
#define CAN2_DisableACFL(n)             CLR_CAN_BIT(CAN2_ACF_EN0, BIT(n))
#define CAN2_DisableACFH(n)             CLR_CAN_BIT(CAN2_ACF_EN1, BIT(n))
#define CAN2_EnableACF(n)               SET_CAN_BIT(CAN2_ACF_EN[(n) >> 3], (1 << ((n) & 0x07)))
#define CAN2_DisableACF(n)              CLR_CAN_BIT(CAN2_ACF_EN[(n) >> 3], (1 << ((n) & 0x07)))

#define CAN2ACF3_CODE_MSK               (BIT4 | BIT_LN)
#define CAN2_SetACF0(n)                 WRITE_CAN(CAN2_ACF0, (n))
#define CAN2_SetACF1(n)                 WRITE_CAN(CAN2_ACF1, (n))
#define CAN2_SetACF2(n)                 WRITE_CAN(CAN2_ACF2, (n))
#define CAN2_SetACF3(n)                 MODIFY_CAN(CAN2_ACF3, CAN2ACF3_CODE_MSK, ((n) << 0))
#define CAN2_SetACF(n)                  CAN2_SetACF0(BYTE0(n)); \
                                        CAN2_SetACF1(BYTE1(n)); \
                                        CAN2_SetACF2(BYTE2(n)); \
                                        CAN2_SetACF3(BYTE3(n))

#define CAN2ACF3_AIDE_MSK               BIT5
#define CAN2ACF3_AIDEE_MSK              BIT6
#define CAN2_ACFAcceptStdFrame()        SET_CAN_BIT(CAN2_ACF3, CAN2ACF3_AIDEE_MSK); \
                                        CLR_CAN_BIT(CAN2_ACF3, CAN2ACF3_AIDE_MSK)
#define CAN2_ACFAcceptExtFrame()        SET_CAN_BIT(CAN2_ACF3, CAN2ACF3_AIDEE_MSK); \
                                        SET_CAN_BIT(CAN2_ACF3, CAN2ACF3_AIDE_MSK)
#define CAN2_ACFAcceptAllFrame()        CLR_CAN_BIT(CAN2_ACF3, CAN2ACF3_AIDEE_MSK)

#define CAN2_ReadVersion()              MAKEWORD(READ_CAN(CAN2_VER0), READ_CAN(CAN2_VER1))

#define CAN2TBSLOT_TBE_MSK              BIT7
#define CAN2TBSLOT_TBF_MSK              BIT6
#define CAN2_SetTBSlotToEmpty()         SET_CAN_BIT(CAN2_TBSLOT, CAN2TBSLOT_TBE_MSK)
#define CAN2_SetTBSlotToFull()          SET_CAN_BIT(CAN2_TBSLOT, CAN2TBSLOT_TBF_MSK)

#define CAN2TBSLOT_TBPTR_MSK            (BIT_LN)
#define CAN2_SetTBSlotPointer(n)        MODIFY_CAN(CAN2_TBSLOT, CAN2TBSLOT_TBPTR_MSK, ((n) << 0))

#define CAN2TTCFG_WTIE_MSK              BIT7
#define CAN2TTCFG_WTIF_MSK              BIT6
#define CAN2_EnableWatchTriggerInt()    SET_CAN_BIT(CAN2_TTCFG, CAN2TTCFG_WTIE_MSK)
#define CAN2_DisableWatchTriggerInt()   CLR_CAN_BIT(CAN2_TTCFG, CAN2TTCFG_WTIE_MSK)
#define CAN2_CheckWatchTriggerFlag()    READ_CAN_BIT(CAN2_TTCFG, CAN2TTCFG_WTIF_MSK)

#define CAN2TTCFG_TEIF_MSK              BIT5
#define CAN2TTCFG_TTIE_MSK              BIT4
#define CAN2TTCFG_TTIF_MSK              BIT3
#define CAN2_EnableTimeTriggerInt()     SET_CAN_BIT(CAN2_TTCFG, CAN2TTCFG_TTIE_MSK)
#define CAN2_DisableTimeTriggerInt()    CLR_CAN_BIT(CAN2_TTCFG, CAN2TTCFG_TTIE_MSK)
#define CAN2_CheckTimeTriggerFlag()     READ_CAN_BIT(CAN2_TTCFG, CAN2TTCFG_TTIF_MSK)
#define CAN2_CheckTriggerErrorFlag()    READ_CAN_BIT(CAN2_TTCFG, CAN2TTCFG_TEIF_MSK)

#define CAN2TTCFG_PRESC_MSK             (BIT2 | BIT1)
#define CAN2_SetTTTimerPrescale(n)      MODIFY_CAN(CAN2_TTCFG, CAN2TTCFG_PRESC_MSK, ((n) << 1))
#define CAN2_SetTTTimerPrescale1()      CAN2_SetTTTimerPrescale(0)
#define CAN2_SetTTTimerPrescale2()      CAN2_SetTTTimerPrescale(1)
#define CAN2_SetTTTimerPrescale4()      CAN2_SetTTTimerPrescale(2)
#define CAN2_SetTTTimerPrescale8()      CAN2_SetTTTimerPrescale(3)

#define CAN2TTCFG_TTEN_MSK              BIT0
#define CAN2_EnableTimeTrigger()        SET_CAN_BIT(CAN2_TTCFG, CAN2TTCFG_TTEN_MSK)
#define CAN2_DisableTimeTrigger()       CLR_CAN_BIT(CAN2_TTCFG, CAN2TTCFG_TTEN_MSK)

#define CAN2REFMSG3_REFID_MSK           (BIT4 | BIT_LN)
#define CAN2_SetREFID0(n)               WRITE_CAN(CAN2_REF_MSG0, (n))
#define CAN2_SetREFID1(n)               WRITE_CAN(CAN2_REF_MSG1, (n))
#define CAN2_SetREFID2(n)               WRITE_CAN(CAN2_REF_MSG2, (n))
#define CAN2_SetREFID3(n)               MODIFY_CAN(CAN2_REF_MSG3, CAN2REFMSG3_REFID_MSK, ((n) << 0))
#define CAN2_SetREFID(n)                CAN2_SetREFID0(BYTE0(n)); \
                                        CAN2_SetREFID1(BYTE1(n)); \
                                        CAN2_SetREFID2(BYTE2(n)); \
                                        CAN2_SetREFID3(BYTE3(n))

#define CAN2REFMSG3_REFIDE_MSK          BIT7
#define CAN2_StandardREFID()            CLR_CAN_BIT(CAN2_REF_MSG3, CAN2REFMSG3_REFIDE_MSK)
#define CAN2_ExtendedREFID()            SET_CAN_BIT(CAN2_REF_MSG3, CAN2REFMSG3_REFIDE_MSK)

#define CAN2TRIGCFG0_TTPTR_MSK          (BIT5 | BIT4 | BIT_LN)
#define CAN2_SetTTBSlotPointer(n)       MODIFY_CAN(CAN2_TRIG_CFG0, CAN2TRIGCFG0_TTPTR_MSK, ((n) << 0))

#define CAN2TRIGCFG1_TTYPE_MSK          (BIT2 | BIT1 | BIT0)
#define CAN2_SetTriggerType(n)          MODIFY_CAN(CAN2_TRIG_CFG1, CAN2TRIGCFG1_TTYPE_MSK, ((n) << 0))

#define CAN2TRIGCFG1_TEWE_MSK           (BIT_HN)
#define CAN2_SetTransEnableWindow(n)    MODIFY_CAN(CAN2_TRIG_CFG1, CAN2TRIGCFG1_TEWE_MSK, ((n) << 4))

#define CAN2_SetTriggerTime(n)          (WRITE_CAN(CAN2_TT_CFG0, LOBYTE(n)), WRITE_CAN(CAN2_TT_CFG1, HIBYTE(n)))
#define CAN2_SetWatchTriggerTime(n)     (WRITE_CAN(CAN2_TT_WTRIG0, LOBYTE(n)), WRITE_CAN(CAN2_TT_WTRIG1, HIBYTE(n)))

/////////////////////////////////////////////////

#define PWMAENO_ENO1P_MSK               BIT0
#define PWMAENO_ENO1N_MSK               BIT1
#define PWMAENO_ENO2P_MSK               BIT2
#define PWMAENO_ENO2N_MSK               BIT3
#define PWMAENO_ENO3P_MSK               BIT4
#define PWMAENO_ENO3N_MSK               BIT5
#define PWMAENO_ENO4P_MSK               BIT6
#define PWMAENO_ENO4N_MSK               BIT7
#define PWMAENO2_ENO5P_MSK              BIT0
#define PWMAENO2_ENO6P_MSK              BIT2
#define PWMA_EnablePWM1POutput()        SET_REG_BIT(PWMA_ENO, PWMAENO_ENO1P_MSK)
#define PWMA_DisablePWM1POutput()       CLR_REG_BIT(PWMA_ENO, PWMAENO_ENO1P_MSK)
#define PWMA_EnablePWM1NOutput()        SET_REG_BIT(PWMA_ENO, PWMAENO_ENO1N_MSK)
#define PWMA_DisablePWM1NOutput()       CLR_REG_BIT(PWMA_ENO, PWMAENO_ENO1N_MSK)
#define PWMA_EnablePWM2POutput()        SET_REG_BIT(PWMA_ENO, PWMAENO_ENO2P_MSK)
#define PWMA_DisablePWM2POutput()       CLR_REG_BIT(PWMA_ENO, PWMAENO_ENO2P_MSK)
#define PWMA_EnablePWM2NOutput()        SET_REG_BIT(PWMA_ENO, PWMAENO_ENO2N_MSK)
#define PWMA_DisablePWM2NOutput()       CLR_REG_BIT(PWMA_ENO, PWMAENO_ENO2N_MSK)
#define PWMA_EnablePWM3POutput()        SET_REG_BIT(PWMA_ENO, PWMAENO_ENO3P_MSK)
#define PWMA_DisablePWM3POutput()       CLR_REG_BIT(PWMA_ENO, PWMAENO_ENO3P_MSK)
#define PWMA_EnablePWM3NOutput()        SET_REG_BIT(PWMA_ENO, PWMAENO_ENO3N_MSK)
#define PWMA_DisablePWM3NOutput()       CLR_REG_BIT(PWMA_ENO, PWMAENO_ENO3N_MSK)
#define PWMA_EnablePWM4POutput()        SET_REG_BIT(PWMA_ENO, PWMAENO_ENO4P_MSK)
#define PWMA_DisablePWM4POutput()       CLR_REG_BIT(PWMA_ENO, PWMAENO_ENO4P_MSK)
#define PWMA_EnablePWM4NOutput()        SET_REG_BIT(PWMA_ENO, PWMAENO_ENO4N_MSK)
#define PWMA_DisablePWM4NOutput()       CLR_REG_BIT(PWMA_ENO, PWMAENO_ENO4N_MSK)
#define PWMA_EnablePWM5POutput()        SET_REG_BIT(PWMA_ENO2, PWMAENO2_ENO5P_MSK)
#define PWMA_DisablePWM5POutput()       CLR_REG_BIT(PWMA_ENO2, PWMAENO2_ENO5P_MSK)
#define PWMA_EnablePWM6POutput()        SET_REG_BIT(PWMA_ENO2, PWMAENO2_ENO6P_MSK)
#define PWMA_DisablePWM6POutput()       CLR_REG_BIT(PWMA_ENO2, PWMAENO2_ENO6P_MSK)

#define HSPWMA_EnablePWM1POutput()      SET_HSPWMA_BIT(PWMA_ENO, PWMAENO_ENO1P_MSK)
#define HSPWMA_DisablePWM1POutput()     CLR_HSPWMA_BIT(PWMA_ENO, PWMAENO_ENO1P_MSK)
#define HSPWMA_EnablePWM1NOutput()      SET_HSPWMA_BIT(PWMA_ENO, PWMAENO_ENO1N_MSK)
#define HSPWMA_DisablePWM1NOutput()     CLR_HSPWMA_BIT(PWMA_ENO, PWMAENO_ENO1N_MSK)
#define HSPWMA_EnablePWM2POutput()      SET_HSPWMA_BIT(PWMA_ENO, PWMAENO_ENO2P_MSK)
#define HSPWMA_DisablePWM2POutput()     CLR_HSPWMA_BIT(PWMA_ENO, PWMAENO_ENO2P_MSK)
#define HSPWMA_EnablePWM2NOutput()      SET_HSPWMA_BIT(PWMA_ENO, PWMAENO_ENO2N_MSK)
#define HSPWMA_DisablePWM2NOutput()     CLR_HSPWMA_BIT(PWMA_ENO, PWMAENO_ENO2N_MSK)
#define HSPWMA_EnablePWM3POutput()      SET_HSPWMA_BIT(PWMA_ENO, PWMAENO_ENO3P_MSK)
#define HSPWMA_DisablePWM3POutput()     CLR_HSPWMA_BIT(PWMA_ENO, PWMAENO_ENO3P_MSK)
#define HSPWMA_EnablePWM3NOutput()      SET_HSPWMA_BIT(PWMA_ENO, PWMAENO_ENO3N_MSK)
#define HSPWMA_DisablePWM3NOutput()     CLR_HSPWMA_BIT(PWMA_ENO, PWMAENO_ENO3N_MSK)
#define HSPWMA_EnablePWM4POutput()      SET_HSPWMA_BIT(PWMA_ENO, PWMAENO_ENO4P_MSK)
#define HSPWMA_DisablePWM4POutput()     CLR_HSPWMA_BIT(PWMA_ENO, PWMAENO_ENO4P_MSK)
#define HSPWMA_EnablePWM4NOutput()      SET_HSPWMA_BIT(PWMA_ENO, PWMAENO_ENO4N_MSK)
#define HSPWMA_DisablePWM4NOutput()     CLR_HSPWMA_BIT(PWMA_ENO, PWMAENO_ENO4N_MSK)
#define HSPWMA_EnablePWM5POutput()      SET_HSPWMA_BIT(PWMA_ENO2, PWMAENO2_ENO5P_MSK)
#define HSPWMA_DisablePWM5POutput()     CLR_HSPWMA_BIT(PWMA_ENO2, PWMAENO2_ENO5P_MSK)
#define HSPWMA_EnablePWM6POutput()      SET_HSPWMA_BIT(PWMA_ENO2, PWMAENO2_ENO6P_MSK)
#define HSPWMA_DisablePWM6POutput()     CLR_HSPWMA_BIT(PWMA_ENO2, PWMAENO2_ENO6P_MSK)

#define PWMAIOAUX_AUX1P_MSK             BIT0
#define PWMAIOAUX_AUX1N_MSK             BIT1
#define PWMAIOAUX_AUX2P_MSK             BIT2
#define PWMAIOAUX_AUX2N_MSK             BIT3
#define PWMAIOAUX_AUX3P_MSK             BIT4
#define PWMAIOAUX_AUX3N_MSK             BIT5
#define PWMAIOAUX_AUX4P_MSK             BIT6
#define PWMAIOAUX_AUX4N_MSK             BIT7
#define PWMAIOAUX2_AUX5P_MSK            BIT0
#define PWMAIOAUX2_AUX6P_MSK            BIT2
#define PWMA_EnoCtrlPWM1P()             CLR_REG_BIT(PWMA_IOAUX, PWMAIOAUX_AUX1P_MSK)
#define PWMA_EnoBrkCtrlPWM1P()          SET_REG_BIT(PWMA_IOAUX, PWMAIOAUX_AUX1P_MSK)
#define PWMA_EnoCtrlPWM1N()             CLR_REG_BIT(PWMA_IOAUX, PWMAIOAUX_AUX1N_MSK)
#define PWMA_EnoBrkCtrlPWM1N()          SET_REG_BIT(PWMA_IOAUX, PWMAIOAUX_AUX1N_MSK)
#define PWMA_EnoCtrlPWM2P()             CLR_REG_BIT(PWMA_IOAUX, PWMAIOAUX_AUX2P_MSK)
#define PWMA_EnoBrkCtrlPWM2P()          SET_REG_BIT(PWMA_IOAUX, PWMAIOAUX_AUX2P_MSK)
#define PWMA_EnoCtrlPWM2N()             CLR_REG_BIT(PWMA_IOAUX, PWMAIOAUX_AUX2N_MSK)
#define PWMA_EnoBrkCtrlPWM2N()          SET_REG_BIT(PWMA_IOAUX, PWMAIOAUX_AUX2N_MSK)
#define PWMA_EnoCtrlPWM3P()             CLR_REG_BIT(PWMA_IOAUX, PWMAIOAUX_AUX3P_MSK)
#define PWMA_EnoBrkCtrlPWM3P()          SET_REG_BIT(PWMA_IOAUX, PWMAIOAUX_AUX3P_MSK)
#define PWMA_EnoCtrlPWM3N()             CLR_REG_BIT(PWMA_IOAUX, PWMAIOAUX_AUX3N_MSK)
#define PWMA_EnoBrkCtrlPWM3N()          SET_REG_BIT(PWMA_IOAUX, PWMAIOAUX_AUX3N_MSK)
#define PWMA_EnoCtrlPWM4P()             CLR_REG_BIT(PWMA_IOAUX, PWMAIOAUX_AUX4P_MSK)
#define PWMA_EnoBrkCtrlPWM4P()          SET_REG_BIT(PWMA_IOAUX, PWMAIOAUX_AUX4P_MSK)
#define PWMA_EnoCtrlPWM4N()             CLR_REG_BIT(PWMA_IOAUX, PWMAIOAUX_AUX4N_MSK)
#define PWMA_EnoBrkCtrlPWM4N()          SET_REG_BIT(PWMA_IOAUX, PWMAIOAUX_AUX4N_MSK)
#define PWMA_EnoCtrlPWM5P()             CLR_REG_BIT(PWMA_IOAUX2, PWMAIOAUX2_AUX5P_MSK)
#define PWMA_EnoBrkCtrlPWM5P()          SET_REG_BIT(PWMA_IOAUX2, PWMAIOAUX2_AUX5P_MSK)
#define PWMA_EnoCtrlPWM6P()             CLR_REG_BIT(PWMA_IOAUX2, PWMAIOAUX2_AUX6P_MSK)
#define PWMA_EnoBrkCtrlPWM6P()          SET_REG_BIT(PWMA_IOAUX2, PWMAIOAUX2_AUX6P_MSK)

#define HSPWMA_EnoCtrlPWM1P()           CLR_HSPWMA_BIT(PWMA_IOAUX, PWMAIOAUX_AUX1P_MSK)
#define HSPWMA_EnoBrkCtrlPWM1P()        SET_HSPWMA_BIT(PWMA_IOAUX, PWMAIOAUX_AUX1P_MSK)
#define HSPWMA_EnoCtrlPWM1N()           CLR_HSPWMA_BIT(PWMA_IOAUX, PWMAIOAUX_AUX1N_MSK)
#define HSPWMA_EnoBrkCtrlPWM1N()        SET_HSPWMA_BIT(PWMA_IOAUX, PWMAIOAUX_AUX1N_MSK)
#define HSPWMA_EnoCtrlPWM2P()           CLR_HSPWMA_BIT(PWMA_IOAUX, PWMAIOAUX_AUX2P_MSK)
#define HSPWMA_EnoBrkCtrlPWM2P()        SET_HSPWMA_BIT(PWMA_IOAUX, PWMAIOAUX_AUX2P_MSK)
#define HSPWMA_EnoCtrlPWM2N()           CLR_HSPWMA_BIT(PWMA_IOAUX, PWMAIOAUX_AUX2N_MSK)
#define HSPWMA_EnoBrkCtrlPWM2N()        SET_HSPWMA_BIT(PWMA_IOAUX, PWMAIOAUX_AUX2N_MSK)
#define HSPWMA_EnoCtrlPWM3P()           CLR_HSPWMA_BIT(PWMA_IOAUX, PWMAIOAUX_AUX3P_MSK)
#define HSPWMA_EnoBrkCtrlPWM3P()        SET_HSPWMA_BIT(PWMA_IOAUX, PWMAIOAUX_AUX3P_MSK)
#define HSPWMA_EnoCtrlPWM3N()           CLR_HSPWMA_BIT(PWMA_IOAUX, PWMAIOAUX_AUX3N_MSK)
#define HSPWMA_EnoBrkCtrlPWM3N()        SET_HSPWMA_BIT(PWMA_IOAUX, PWMAIOAUX_AUX3N_MSK)
#define HSPWMA_EnoCtrlPWM4P()           CLR_HSPWMA_BIT(PWMA_IOAUX, PWMAIOAUX_AUX4P_MSK)
#define HSPWMA_EnoBrkCtrlPWM4P()        SET_HSPWMA_BIT(PWMA_IOAUX, PWMAIOAUX_AUX4P_MSK)
#define HSPWMA_EnoCtrlPWM4N()           CLR_HSPWMA_BIT(PWMA_IOAUX, PWMAIOAUX_AUX4N_MSK)
#define HSPWMA_EnoBrkCtrlPWM4N()        SET_HSPWMA_BIT(PWMA_IOAUX, PWMAIOAUX_AUX4N_MSK)
#define HSPWMA_EnoCtrlPWM5P()           CLR_HSPWMA_BIT(PWMA_IOAUX2, PWMAIOAUX2_AUX5P_MSK)
#define HSPWMA_EnoBrkCtrlPWM5P()        SET_HSPWMA_BIT(PWMA_IOAUX2, PWMAIOAUX2_AUX5P_MSK)
#define HSPWMA_EnoCtrlPWM6P()           CLR_HSPWMA_BIT(PWMA_IOAUX2, PWMAIOAUX2_AUX6P_MSK)
#define HSPWMA_EnoBrkCtrlPWM6P()        SET_HSPWMA_BIT(PWMA_IOAUX2, PWMAIOAUX2_AUX6P_MSK)

#define PWMACR1_ARPE_MSK                BIT7
#define PWMA_UnbufferARR()              CLR_REG_BIT(PWMA_CR1, PWMACR1_ARPE_MSK)
#define PWMA_BufferARR()                SET_REG_BIT(PWMA_CR1, PWMACR1_ARPE_MSK)

#define HSPWMA_UnbufferARR()            CLR_HSPWMA_BIT(PWMA_CR1, PWMACR1_ARPE_MSK)
#define HSPWMA_BufferARR()              SET_HSPWMA_BIT(PWMA_CR1, PWMACR1_ARPE_MSK)

#define PWMACR1_CMS_MSK                 (BIT6 | BIT5)
#define PWMA_SetAlignMode(n)            MODIFY_REG(PWMA_CR1,  PWMACR1_CMS_MSK, ((n) << 5))
#define PWMA_EdgeAlignMode()            PWMA_SetAlignMode(0)
#define PWMA_CenterAlignMode1()         PWMA_SetAlignMode(1)
#define PWMA_CenterAlignMode2()         PWMA_SetAlignMode(2)
#define PWMA_CenterAlignMode3()         PWMA_SetAlignMode(3)

#define HSPWMA_SetAlignMode(n)          MODIFY_HSPWMA(PWMA_CR1,  PWMACR1_CMS_MSK, ((n) << 5))
#define HSPWMA_EdgeAlignMode()          HSPWMA_SetAlignMode(0)
#define HSPWMA_CenterAlignMode1()       HSPWMA_SetAlignMode(1)
#define HSPWMA_CenterAlignMode2()       HSPWMA_SetAlignMode(2)
#define HSPWMA_CenterAlignMode3()       HSPWMA_SetAlignMode(3)

#define PWMACR1_DIR_MSK                 BIT4
#define PWMA_UpCounter()                CLR_REG_BIT(PWMA_CR1, PWMACR1_DIR_MSK)
#define PWMA_DownCounter()              SET_REG_BIT(PWMA_CR1, PWMACR1_DIR_MSK)

#define HSPWMA_UpCounter()              CLR_HSPWMA_BIT(PWMA_CR1, PWMACR1_DIR_MSK)
#define HSPWMA_DownCounter()            SET_HSPWMA_BIT(PWMA_CR1, PWMACR1_DIR_MSK)

#define PWMACR1_OPM_MSK                 BIT3
#define PWMA_ContinueMode()             CLR_REG_BIT(PWMA_CR1, PWMACR1_OPM_MSK)
#define PWMA_OnePulseMode()             SET_REG_BIT(PWMA_CR1, PWMACR1_OPM_MSK)

#define HSPWMA_ContinueMode()           CLR_HSPWMA_BIT(PWMA_CR1, PWMACR1_OPM_MSK)
#define HSPWMA_OnePulseMode()           SET_HSPWMA_BIT(PWMA_CR1, PWMACR1_OPM_MSK)

#define PWMACR1_URS_MSK                 BIT2
#define PWMA_UpdateRequestMode1()       SET_REG_BIT(PWMA_CR1, PWMACR1_URS_MSK)
#define PWMA_UpdateRequestMode2()       CLR_REG_BIT(PWMA_CR1, PWMACR1_URS_MSK)

#define HSPWMA_UpdateRequestMode1()     SET_HSPWMA_BIT(PWMA_CR1, PWMACR1_URS_MSK)
#define HSPWMA_UpdateRequestMode2()     CLR_HSPWMA_BIT(PWMA_CR1, PWMACR1_URS_MSK)

#define PWMACR1_UDIS_MSK                BIT1
#define PWMA_EnableUpdate()             CLR_REG_BIT(PWMA_CR1, PWMACR1_UDIS_MSK)
#define PWMA_DisableUpdate()            SET_REG_BIT(PWMA_CR1, PWMACR1_UDIS_MSK)

#define HSPWMA_EnableUpdate()           CLR_HSPWMA_BIT(PWMA_CR1, PWMACR1_UDIS_MSK)
#define HSPWMA_DisableUpdate()          SET_HSPWMA_BIT(PWMA_CR1, PWMACR1_UDIS_MSK)

#define PWMACR1_CEN_MSK                 BIT0
#define PWMA_Run()                      SET_REG_BIT(PWMA_CR1, PWMACR1_CEN_MSK)
#define PWMA_Stop()                     CLR_REG_BIT(PWMA_CR1, PWMACR1_CEN_MSK)

#define HSPWMA_Run()                    SET_HSPWMA_BIT(PWMA_CR1, PWMACR1_CEN_MSK)
#define HSPWMA_Stop()                   CLR_HSPWMA_BIT(PWMA_CR1, PWMACR1_CEN_MSK)

#define PWMACR2_TIS_MSK                 BIT7
#define PWMA_PWM1PToTI()                CLR_REG_BIT(PWMA_CR2, PWMACR2_TIS_MSK)
#define PWMA_Xor1P2P3PToTI()            SET_REG_BIT(PWMA_CR2, PWMACR2_TIS_MSK)

#define HSPWMA_PWM1PToTI()              CLR_HSPWMA_BIT(PWMA_CR2, PWMACR2_TIS_MSK)
#define HSPWMA_Xor1P2P3PToTI()          SET_HSPWMA_BIT(PWMA_CR2, PWMACR2_TIS_MSK)

#define PWMACR2_MMS_MSK                 (BIT6 | BIT5 | BIT4)
#define PWMA_SelectTRGO(n)              MODIFY_REG(PWMA_CR2,  PWMACR2_MMS_MSK, ((n) << 4))
#define PWMA_ResetAsTRGO()              PWMA_SelectTRGO(0)
#define PWMA_EnableAsTRGO()             PWMA_SelectTRGO(1)
#define PWMA_UpdateAsTRGO()             PWMA_SelectTRGO(2)
#define PWMA_MatchAsTRGO()              PWMA_SelectTRGO(3)
#define PWMA_OC1REFAsTRGO()             PWMA_SelectTRGO(4)
#define PWMA_OC2REFAsTRGO()             PWMA_SelectTRGO(5)
#define PWMA_OC3REFAsTRGO()             PWMA_SelectTRGO(6)
#define PWMA_OC4REFAsTRGO()             PWMA_SelectTRGO(7)

#define HSPWMA_SelectTRGO(n)            MODIFY_HSPWMA(PWMA_CR2,  PWMACR2_MMS_MSK, ((n) << 4))
#define HSPWMA_ResetAsTRGO()            HSPWMA_SelectTRGO(0)
#define HSPWMA_EnableAsTRGO()           HSPWMA_SelectTRGO(1)
#define HSPWMA_UpdateAsTRGO()           HSPWMA_SelectTRGO(2)
#define HSPWMA_MatchAsTRGO()            HSPWMA_SelectTRGO(3)
#define HSPWMA_OC1REFAsTRGO()           HSPWMA_SelectTRGO(4)
#define HSPWMA_OC2REFAsTRGO()           HSPWMA_SelectTRGO(5)
#define HSPWMA_OC3REFAsTRGO()           HSPWMA_SelectTRGO(6)
#define HSPWMA_OC4REFAsTRGO()           HSPWMA_SelectTRGO(7)

#define PWMACR2_COMS_MSK                BIT2
#define PWMA_CCOCUpdateMode0()          CLR_REG_BIT(PWMA_CR2, PWMACR2_COMS_MSK)
#define PWMA_CCOCUpdateMode1()          SET_REG_BIT(PWMA_CR2, PWMACR2_COMS_MSK)

#define HSPWMA_CCOCUpdateMode0()        CLR_HSPWMA_BIT(PWMA_CR2, PWMACR2_COMS_MSK)
#define HSPWMA_CCOCUpdateMode1()        SET_HSPWMA_BIT(PWMA_CR2, PWMACR2_COMS_MSK)

#define PWMACR2_CCPC_MSK                BIT0
#define PWMA_UnbufferCCOC()             CLR_REG_BIT(PWMA_CR2, PWMACR2_CCPC_MSK)
#define PWMA_BufferCCOC()               SET_REG_BIT(PWMA_CR2, PWMACR2_CCPC_MSK)

#define HSPWMA_UnbufferCCOC()           CLR_HSPWMA_BIT(PWMA_CR2, PWMACR2_CCPC_MSK)
#define HSPWMA_BufferCCOC()             SET_HSPWMA_BIT(PWMA_CR2, PWMACR2_CCPC_MSK)

#define PWMASMCR_MSM_MSK                BIT7
#define PWMA_StandaloneMode()           CLR_REG_BIT(PWMA_SMCR, PWMASMCR_MSM_MSK)
#define PWMA_MasterSlaveMode()          SET_REG_BIT(PWMA_SMCR, PWMASMCR_MSM_MSK)

#define HSPWMA_StandaloneMode()         CLR_HSPWMA_BIT(PWMA_SMCR, PWMASMCR_MSM_MSK)
#define HSPWMA_MasterSlaveMode()        SET_HSPWMA_BIT(PWMA_SMCR, PWMASMCR_MSM_MSK)

#define PWMASMCR_TS_MSK                 (BIT6 | BIT5 | BIT4)
#define PWMA_SelectTRGI(n)              MODIFY_REG(PWMA_SMCR,  PWMASMCR_TS_MSK, ((n) << 4))
#define PWMA_DisableTRGI()              PWMA_SelectTRGI(0)
#define PWMA_ITR2AsTRGI()               PWMA_SelectTRGI(2)
#define PWMA_TI1FEDAsTRGI()             PWMA_SelectTRGI(4)
#define PWMA_TI1FP1AsTRGI()             PWMA_SelectTRGI(5)
#define PWMA_TI2FP2AsTRGI()             PWMA_SelectTRGI(6)
#define PWMA_ETRFAsTRGI()               PWMA_SelectTRGI(7)

#define HSPWMA_SelectTRGI(n)            MODIFY_HSPWMA(PWMA_SMCR,  PWMASMCR_TS_MSK, ((n) << 4))
#define HSPWMA_DisableTRGI()            HSPWMA_SelectTRGI(0)
#define HSPWMA_ITR2AsTRGI()             HSPWMA_SelectTRGI(2)
#define HSPWMA_TI1FEDAsTRGI()           HSPWMA_SelectTRGI(4)
#define HSPWMA_TI1FP1AsTRGI()           HSPWMA_SelectTRGI(5)
#define HSPWMA_TI2FP2AsTRGI()           HSPWMA_SelectTRGI(6)
#define HSPWMA_ETRFAsTRGI()             HSPWMA_SelectTRGI(7)

#define PWMASMCR_SMS_MSK                (BIT2 | BIT1 | BIT0)
#define PWMA_SetClockMode(n)            MODIFY_REG(PWMA_SMCR,  PWMASMCR_SMS_MSK, ((n) << 0))
#define PWMA_InternalClockMode()        PWMA_SetClockMode(0)
#define PWMA_EncoderMode1()             PWMA_SetClockMode(1)
#define PWMA_EncoderMode2()             PWMA_SetClockMode(2)
#define PWMA_EncoderMode3()             PWMA_SetClockMode(3)
#define PWMA_TriggerResetMode()         PWMA_SetClockMode(4)
#define PWMA_TriggerGateMode()          PWMA_SetClockMode(5)
#define PWMA_TriggerStartMode()         PWMA_SetClockMode(6)
#define PWMA_ExternalClockMode()        PWMA_SetClockMode(7)

#define HSPWMA_SetClockMode(n)          MODIFY_HSPWMA(PWMA_SMCR,  PWMASMCR_SMS_MSK, ((n) << 0))
#define HSPWMA_InternalClockMode()      HSPWMA_SetClockMode(0)
#define HSPWMA_EncoderMode1()           HSPWMA_SetClockMode(1)
#define HSPWMA_EncoderMode2()           HSPWMA_SetClockMode(2)
#define HSPWMA_EncoderMode3()           HSPWMA_SetClockMode(3)
#define HSPWMA_TriggerResetMode()       HSPWMA_SetClockMode(4)
#define HSPWMA_TriggerGateMode()        HSPWMA_SetClockMode(5)
#define HSPWMA_TriggerStartMode()       HSPWMA_SetClockMode(6)
#define HSPWMA_ExternalClockMode()      HSPWMA_SetClockMode(7)

#define PWMAETR_ETP_MSK                 BIT7
#define PWMA_ETRNonInverted()           CLR_REG_BIT(PWMA_ETR, PWMAETR_ETP_MSK)
#define PWMA_ETRInverted()              SET_REG_BIT(PWMA_ETR, PWMAETR_ETP_MSK)

#define HSPWMA_ETRNonInverted()         CLR_HSPWMA_BIT(PWMA_ETR, PWMAETR_ETP_MSK)
#define HSPWMA_ETRInverted()            SET_HSPWMA_BIT(PWMA_ETR, PWMAETR_ETP_MSK)

#define PWMAETR_ECE_MSK                 BIT6
#define PWMA_DisableExternalClock2()    CLR_REG_BIT(PWMA_ETR, PWMAETR_ECE_MSK)
#define PWMA_EnableExternalClock2()     SET_REG_BIT(PWMA_ETR, PWMAETR_ECE_MSK)

#define HSPWMA_DisableExternalClock2()  CLR_HSPWMA_BIT(PWMA_ETR, PWMAETR_ECE_MSK)
#define HSPWMA_EnableExternalClock2()   SET_HSPWMA_BIT(PWMA_ETR, PWMAETR_ECE_MSK)

#define PWMAETR_ETPS_MSK                (BIT5 | BIT4)
#define PWMA_SetETRDivider(n)           MODIFY_REG(PWMA_ETR,  PWMAETR_ETPS_MSK, ((n) << 4))
#define PWMA_ETRDivider1()              PWMA_SetETRDivider(0)
#define PWMA_ETRDivider2()              PWMA_SetETRDivider(1)
#define PWMA_ETRDivider4()              PWMA_SetETRDivider(2)
#define PWMA_ETRDivider8()              PWMA_SetETRDivider(3)

#define HSPWMA_SetETRDivider(n)         MODIFY_HSPWMA(PWMA_ETR,  PWMAETR_ETPS_MSK, ((n) << 4))
#define HSPWMA_ETRDivider1()            HSPWMA_SetETRDivider(0)
#define HSPWMA_ETRDivider2()            HSPWMA_SetETRDivider(1)
#define HSPWMA_ETRDivider4()            HSPWMA_SetETRDivider(2)
#define HSPWMA_ETRDivider8()            HSPWMA_SetETRDivider(3)

#define PWMAETR_ETF_MSK                 (BIT_LN)
#define PWMA_SetETRFilter(n)            MODIFY_REG(PWMA_ETR,  PWMAETR_ETF_MSK, ((n) << 0))
#define PWMA_ETRFilter1()               PWMA_SetETRFilter(0)
#define PWMA_ETRFilter2()               PWMA_SetETRFilter(1)
#define PWMA_ETRFilter4()               PWMA_SetETRFilter(2)
#define PWMA_ETRFilter8()               PWMA_SetETRFilter(3)
#define PWMA_ETRFilter12()              PWMA_SetETRFilter(4)
#define PWMA_ETRFilter16()              PWMA_SetETRFilter(5)
#define PWMA_ETRFilter24()              PWMA_SetETRFilter(6)
#define PWMA_ETRFilter32()              PWMA_SetETRFilter(7)
#define PWMA_ETRFilter48()              PWMA_SetETRFilter(8)
#define PWMA_ETRFilter64()              PWMA_SetETRFilter(9)
#define PWMA_ETRFilter80()              PWMA_SetETRFilter(10)
#define PWMA_ETRFilter96()              PWMA_SetETRFilter(11)
#define PWMA_ETRFilter128()             PWMA_SetETRFilter(12)
#define PWMA_ETRFilter160()             PWMA_SetETRFilter(13)
#define PWMA_ETRFilter192()             PWMA_SetETRFilter(14)
#define PWMA_ETRFilter256()             PWMA_SetETRFilter(15)

#define HSPWMA_SetETRFilter(n)          MODIFY_HSPWMA(PWMA_ETR,  PWMAETR_ETF_MSK, ((n) << 0))
#define HSPWMA_ETRFilter1()             HSPWMA_SetETRFilter(0)
#define HSPWMA_ETRFilter2()             HSPWMA_SetETRFilter(1)
#define HSPWMA_ETRFilter4()             HSPWMA_SetETRFilter(2)
#define HSPWMA_ETRFilter8()             HSPWMA_SetETRFilter(3)
#define HSPWMA_ETRFilter12()            HSPWMA_SetETRFilter(4)
#define HSPWMA_ETRFilter16()            HSPWMA_SetETRFilter(5)
#define HSPWMA_ETRFilter24()            HSPWMA_SetETRFilter(6)
#define HSPWMA_ETRFilter32()            HSPWMA_SetETRFilter(7)
#define HSPWMA_ETRFilter48()            HSPWMA_SetETRFilter(8)
#define HSPWMA_ETRFilter64()            HSPWMA_SetETRFilter(9)
#define HSPWMA_ETRFilter80()            HSPWMA_SetETRFilter(10)
#define HSPWMA_ETRFilter96()            HSPWMA_SetETRFilter(11)
#define HSPWMA_ETRFilter128()           HSPWMA_SetETRFilter(12)
#define HSPWMA_ETRFilter160()           HSPWMA_SetETRFilter(13)
#define HSPWMA_ETRFilter192()           HSPWMA_SetETRFilter(14)
#define HSPWMA_ETRFilter256()           HSPWMA_SetETRFilter(15)

#define PWMAEGR_BG_MSK                  BIT7
#define PWMAEGR_TG_MSK                  BIT6
#define PWMAEGR_COMG_MSK                BIT5
#define PWMAEGR_CC4G_MSK                BIT4
#define PWMAEGR_CC3G_MSK                BIT3
#define PWMAEGR_CC2G_MSK                BIT2
#define PWMAEGR_CC1G_MSK                BIT1
#define PWMAEGR_UG_MSK                  BIT0
#define PWMA_GenerateBreakEvent()       SET_REG_BIT(PWMA_EGR, PWMAEGR_BG_MSK)
#define PWMA_GenerateTriggerEvent()     SET_REG_BIT(PWMA_EGR, PWMAEGR_TG_MSK)
#define PWMA_GenerateCOMEvent()         SET_REG_BIT(PWMA_EGR, PWMAEGR_COMG_MSK)
#define PWMA_GenerateCC4Event()         SET_REG_BIT(PWMA_EGR, PWMAEGR_CC4G_MSK)
#define PWMA_GenerateCC3Event()         SET_REG_BIT(PWMA_EGR, PWMAEGR_CC3G_MSK)
#define PWMA_GenerateCC2Event()         SET_REG_BIT(PWMA_EGR, PWMAEGR_CC2G_MSK)
#define PWMA_GenerateCC1Event()         SET_REG_BIT(PWMA_EGR, PWMAEGR_CC1G_MSK)
#define PWMA_GenerateUpdateEvent()      SET_REG_BIT(PWMA_EGR, PWMAEGR_UG_MSK)

#define HSPWMA_GenerateBreakEvent()     SET_HSPWMA_BIT(PWMA_EGR, PWMAEGR_BG_MSK)
#define HSPWMA_GenerateTriggerEvent()   SET_HSPWMA_BIT(PWMA_EGR, PWMAEGR_TG_MSK)
#define HSPWMA_GenerateCOMEvent()       SET_HSPWMA_BIT(PWMA_EGR, PWMAEGR_COMG_MSK)
#define HSPWMA_GenerateCC4Event()       SET_HSPWMA_BIT(PWMA_EGR, PWMAEGR_CC4G_MSK)
#define HSPWMA_GenerateCC3Event()       SET_HSPWMA_BIT(PWMA_EGR, PWMAEGR_CC3G_MSK)
#define HSPWMA_GenerateCC2Event()       SET_HSPWMA_BIT(PWMA_EGR, PWMAEGR_CC2G_MSK)
#define HSPWMA_GenerateCC1Event()       SET_HSPWMA_BIT(PWMA_EGR, PWMAEGR_CC1G_MSK)
#define HSPWMA_GenerateUpdateEvent()    SET_HSPWMA_BIT(PWMA_EGR, PWMAEGR_UG_MSK)

#define PWMACCMR1_OC1CE_MSK             BIT7
#define PWMA_EnableETRFClearOC1REF()    SET_REG_BIT(PWMA_CCMR1, PWMACCMR1_OC1CE_MSK)
#define PWMA_DisableETRFClearOC1REF()   CLR_REG_BIT(PWMA_CCMR1, PWMACCMR1_OC1CE_MSK)

#define HSPWMA_EnableETRFClearOC1REF()  SET_HSPWMA_BIT(PWMA_CCMR1, PWMACCMR1_OC1CE_MSK)
#define HSPWMA_DisableETRFClearOC1REF() CLR_HSPWMA_BIT(PWMA_CCMR1, PWMACCMR1_OC1CE_MSK)

#define PWMACCMR1_OC1M_MSK              (BIT6 | BIT5 | BIT4)
#define PWMACCMR1X_OC1M3_MSK            BIT0
#define PWMA_SetOC1OutputMode(n)        MODIFY_REG(PWMA_CCMR1,  PWMACCMR1_OC1M_MSK, ((n) << 4)); \
                                        MODIFY_REG(PWMA_CCMR1X, PWMACCMR1X_OC1M3_MSK, (((n) >> 3) << 0))
#define PWMA_OC1REFFrozen()             PWMA_SetOC1OutputMode(0)
#define PWMA_OC1REFHighIfMatch()        PWMA_SetOC1OutputMode(1)
#define PWMA_OC1REFLowIfMatch()         PWMA_SetOC1OutputMode(2)
#define PWMA_OC1REFToggleIfMatch()      PWMA_SetOC1OutputMode(3)
#define PWMA_OC1REFForceLow()           PWMA_SetOC1OutputMode(4)
#define PWMA_OC1REFForceHigh()          PWMA_SetOC1OutputMode(5)
#define PWMA_OC1REFPWMMode1()           PWMA_SetOC1OutputMode(6)
#define PWMA_OC1REFPWMMode2()           PWMA_SetOC1OutputMode(7)
#define PWMA_OC1REFReTrigOPMPWM1()      PWMA_SetOC1OutputMode(8)
#define PWMA_OC1REFReTrigOPMPWM2()      PWMA_SetOC1OutputMode(9)
#define PWMA_OC1REFCombinedPWM1()       PWMA_SetOC1OutputMode(12)
#define PWMA_OC1REFCombinedPWM2()       PWMA_SetOC1OutputMode(13)
#define PWMA_OC1REFAsymmetricPWM1()     PWMA_SetOC1OutputMode(14)
#define PWMA_OC1REFAsymmetricPWM2()     PWMA_SetOC1OutputMode(15)

#define HSPWMA_SetOC1OutputMode(n)      MODIFY_HSPWMA(PWMA_CCMR1,  PWMACCMR1_OC1M_MSK, ((n) << 4)); \
                                        MODIFY_HSPWMA(PWMA_CCMR1X, PWMACCMR1X_OC1M3_MSK, (((n) >> 3) << 0))
#define HSPWMA_OC1REFFrozen()           HSPWMA_SetOC1OutputMode(0)
#define HSPWMA_OC1REFHighIfMatch()      HSPWMA_SetOC1OutputMode(1)
#define HSPWMA_OC1REFLowIfMatch()       HSPWMA_SetOC1OutputMode(2)
#define HSPWMA_OC1REFToggleIfMatch()    HSPWMA_SetOC1OutputMode(3)
#define HSPWMA_OC1REFForceLow()         HSPWMA_SetOC1OutputMode(4)
#define HSPWMA_OC1REFForceHigh()        HSPWMA_SetOC1OutputMode(5)
#define HSPWMA_OC1REFPWMMode1()         HSPWMA_SetOC1OutputMode(6)
#define HSPWMA_OC1REFPWMMode2()         HSPWMA_SetOC1OutputMode(7)
#define HSPWMA_OC1REFReTrigOPMPWM1()    HSPWMA_SetOC1OutputMode(8)
#define HSPWMA_OC1REFReTrigOPMPWM2()    HSPWMA_SetOC1OutputMode(9)
#define HSPWMA_OC1REFCombinedPWM1()     HSPWMA_SetOC1OutputMode(12)
#define HSPWMA_OC1REFCombinedPWM2()     HSPWMA_SetOC1OutputMode(13)
#define HSPWMA_OC1REFAsymmetricPWM1()   HSPWMA_SetOC1OutputMode(14)
#define HSPWMA_OC1REFAsymmetricPWM2()   HSPWMA_SetOC1OutputMode(15)

#define PWMACCMR1_OC1PE_MSK             BIT3
#define PWMA_UnbufferCCR1()             CLR_REG_BIT(PWMA_CCMR1, PWMACCMR1_OC1PE_MSK)
#define PWMA_BufferCCR1()               SET_REG_BIT(PWMA_CCMR1, PWMACCMR1_OC1PE_MSK)

#define HSPWMA_UnbufferCCR1()           CLR_HSPWMA_BIT(PWMA_CCMR1, PWMACCMR1_OC1PE_MSK)
#define HSPWMA_BufferCCR1()             SET_HSPWMA_BIT(PWMA_CCMR1, PWMACCMR1_OC1PE_MSK)

#define PWMACCMR1_OC1FE_MSK             BIT2
#define PWMA_DisableOC1FastMode()       CLR_REG_BIT(PWMA_CCMR1, PWMACCMR1_OC1FE_MSK)
#define PWMA_EnableOC1FastMode()        SET_REG_BIT(PWMA_CCMR1, PWMACCMR1_OC1FE_MSK)

#define HSPWMA_DisableOC1FastMode()     CLR_HSPWMA_BIT(PWMA_CCMR1, PWMACCMR1_OC1FE_MSK)
#define HSPWMA_EnableOC1FastMode()      SET_HSPWMA_BIT(PWMA_CCMR1, PWMACCMR1_OC1FE_MSK)

#define PWMACCMR1_CC1S_MSK              (BIT1 | BIT0)
#define PWMA_SetCC1Mode(n)              MODIFY_REG(PWMA_CCMR1,  PWMACCMR1_CC1S_MSK, ((n) << 0))
#define PWMA_CC1Output()                PWMA_SetCC1Mode(0)
#define PWMA_CC1CaptureTI1FP1()         PWMA_SetCC1Mode(1)
#define PWMA_CC1CaptureTI2FP1()         PWMA_SetCC1Mode(2)
#define PWMA_CC1CaptureTRC()            PWMA_SetCC1Mode(3)

#define HSPWMA_SetCC1Mode(n)            MODIFY_HSPWMA(PWMA_CCMR1,  PWMACCMR1_CC1S_MSK, ((n) << 0))
#define HSPWMA_CC1Output()              HSPWMA_SetCC1Mode(0)
#define HSPWMA_CC1CaptureTI1FP1()       HSPWMA_SetCC1Mode(1)
#define HSPWMA_CC1CaptureTI2FP1()       HSPWMA_SetCC1Mode(2)
#define HSPWMA_CC1CaptureTRC()          HSPWMA_SetCC1Mode(3)

#define PWMACCMR1_IC1F_MSK              (BIT_HN)
#define PWMA_SetIC1Filter(n)            MODIFY_REG(PWMA_CCMR1,  PWMACCMR1_IC1F_MSK, ((n) << 4))
#define PWMA_IC1Filter1()               PWMA_SetIC1Filter(0)
#define PWMA_IC1Filter2()               PWMA_SetIC1Filter(1)
#define PWMA_IC1Filter4()               PWMA_SetIC1Filter(2)
#define PWMA_IC1Filter8()               PWMA_SetIC1Filter(3)
#define PWMA_IC1Filter12()              PWMA_SetIC1Filter(4)
#define PWMA_IC1Filter16()              PWMA_SetIC1Filter(5)
#define PWMA_IC1Filter24()              PWMA_SetIC1Filter(6)
#define PWMA_IC1Filter32()              PWMA_SetIC1Filter(7)
#define PWMA_IC1Filter48()              PWMA_SetIC1Filter(8)
#define PWMA_IC1Filter64()              PWMA_SetIC1Filter(9)
#define PWMA_IC1Filter80()              PWMA_SetIC1Filter(10)
#define PWMA_IC1Filter96()              PWMA_SetIC1Filter(11)
#define PWMA_IC1Filter128()             PWMA_SetIC1Filter(12)
#define PWMA_IC1Filter160()             PWMA_SetIC1Filter(13)
#define PWMA_IC1Filter192()             PWMA_SetIC1Filter(14)
#define PWMA_IC1Filter256()             PWMA_SetIC1Filter(15)

#define HSPWMA_SetIC1Filter(n)          MODIFY_HSPWMA(PWMA_CCMR1,  PWMACCMR1_IC1F_MSK, ((n) << 4))
#define HSPWMA_IC1Filter1()             HSPWMA_SetIC1Filter(0)
#define HSPWMA_IC1Filter2()             HSPWMA_SetIC1Filter(1)
#define HSPWMA_IC1Filter4()             HSPWMA_SetIC1Filter(2)
#define HSPWMA_IC1Filter8()             HSPWMA_SetIC1Filter(3)
#define HSPWMA_IC1Filter12()            HSPWMA_SetIC1Filter(4)
#define HSPWMA_IC1Filter16()            HSPWMA_SetIC1Filter(5)
#define HSPWMA_IC1Filter24()            HSPWMA_SetIC1Filter(6)
#define HSPWMA_IC1Filter32()            HSPWMA_SetIC1Filter(7)
#define HSPWMA_IC1Filter48()            HSPWMA_SetIC1Filter(8)
#define HSPWMA_IC1Filter64()            HSPWMA_SetIC1Filter(9)
#define HSPWMA_IC1Filter80()            HSPWMA_SetIC1Filter(10)
#define HSPWMA_IC1Filter96()            HSPWMA_SetIC1Filter(11)
#define HSPWMA_IC1Filter128()           HSPWMA_SetIC1Filter(12)
#define HSPWMA_IC1Filter160()           HSPWMA_SetIC1Filter(13)
#define HSPWMA_IC1Filter192()           HSPWMA_SetIC1Filter(14)
#define HSPWMA_IC1Filter256()           HSPWMA_SetIC1Filter(15)

#define PWMACCMR1_IC1PS_MSK             (BIT3 | BIT2)
#define PWMA_SetIC1Divider(n)           MODIFY_REG(PWMA_CCMR1,  PWMACCMR1_IC1PS_MSK, ((n) << 2))
#define PWMA_IC1Divider1()              PWMA_SetIC1Divider(0)
#define PWMA_IC1Divider2()              PWMA_SetIC1Divider(1)
#define PWMA_IC1Divider4()              PWMA_SetIC1Divider(2)
#define PWMA_IC1Divider8()              PWMA_SetIC1Divider(3)

#define HSPWMA_SetIC1Divider(n)         MODIFY_HSPWMA(PWMA_CCMR1,  PWMACCMR1_IC1PS_MSK, ((n) << 2))
#define HSPWMA_IC1Divider1()            HSPWMA_SetIC1Divider(0)
#define HSPWMA_IC1Divider2()            HSPWMA_SetIC1Divider(1)
#define HSPWMA_IC1Divider4()            HSPWMA_SetIC1Divider(2)
#define HSPWMA_IC1Divider8()            HSPWMA_SetIC1Divider(3)

#define PWMACCMR2_OC2CE_MSK             BIT7
#define PWMA_EnableETRFClearOC2REF()    SET_REG_BIT(PWMA_CCMR2, PWMACCMR2_OC2CE_MSK)
#define PWMA_DisableETRFClearOC2REF()   CLR_REG_BIT(PWMA_CCMR2, PWMACCMR2_OC2CE_MSK)

#define HSPWMA_EnableETRFClearOC2REF()  SET_HSPWMA_BIT(PWMA_CCMR2, PWMACCMR2_OC2CE_MSK)
#define HSPWMA_DisableETRFClearOC2REF() CLR_HSPWMA_BIT(PWMA_CCMR2, PWMACCMR2_OC2CE_MSK)

#define PWMACCMR2_OC2M_MSK              (BIT6 | BIT5 | BIT4)
#define PWMACCMR2X_OC2M3_MSK            BIT0
#define PWMA_SetOC2OutputMode(n)        MODIFY_REG(PWMA_CCMR2,  PWMACCMR2_OC2M_MSK, ((n) << 4)); \
                                        MODIFY_REG(PWMA_CCMR2X, PWMACCMR2X_OC2M3_MSK, (((n) >> 3) << 0))
#define PWMA_OC2REFFrozen()             PWMA_SetOC2OutputMode(0)
#define PWMA_OC2REFHighIfMatch()        PWMA_SetOC2OutputMode(1)
#define PWMA_OC2REFLowIfMatch()         PWMA_SetOC2OutputMode(2)
#define PWMA_OC2REFToggleIfMatch()      PWMA_SetOC2OutputMode(3)
#define PWMA_OC2REFForceLow()           PWMA_SetOC2OutputMode(4)
#define PWMA_OC2REFForceHigh()          PWMA_SetOC2OutputMode(5)
#define PWMA_OC2REFPWMMode1()           PWMA_SetOC2OutputMode(6)
#define PWMA_OC2REFPWMMode2()           PWMA_SetOC2OutputMode(7)
#define PWMA_OC2REFReTrigOPMPWM1()      PWMA_SetOC2OutputMode(8)
#define PWMA_OC2REFReTrigOPMPWM2()      PWMA_SetOC2OutputMode(9)
#define PWMA_OC2REFCombinedPWM1()       PWMA_SetOC2OutputMode(12)
#define PWMA_OC2REFCombinedPWM2()       PWMA_SetOC2OutputMode(13)
#define PWMA_OC2REFAsymmetricPWM1()     PWMA_SetOC2OutputMode(14)
#define PWMA_OC2REFAsymmetricPWM2()     PWMA_SetOC2OutputMode(15)

#define HSPWMA_SetOC2OutputMode(n)      MODIFY_HSPWMA(PWMA_CCMR2,  PWMACCMR2_OC2M_MSK, ((n) << 4)); \
                                        MODIFY_HSPWMA(PWMA_CCMR2X, PWMACCMR2X_OC2M3_MSK, (((n) >> 3) << 0))
#define HSPWMA_OC2REFFrozen()           HSPWMA_SetOC2OutputMode(0)
#define HSPWMA_OC2REFHighIfMatch()      HSPWMA_SetOC2OutputMode(1)
#define HSPWMA_OC2REFLowIfMatch()       HSPWMA_SetOC2OutputMode(2)
#define HSPWMA_OC2REFToggleIfMatch()    HSPWMA_SetOC2OutputMode(3)
#define HSPWMA_OC2REFForceLow()         HSPWMA_SetOC2OutputMode(4)
#define HSPWMA_OC2REFForceHigh()        HSPWMA_SetOC2OutputMode(5)
#define HSPWMA_OC2REFPWMMode1()         HSPWMA_SetOC2OutputMode(6)
#define HSPWMA_OC2REFPWMMode2()         HSPWMA_SetOC2OutputMode(7)
#define HSPWMA_OC2REFReTrigOPMPWM1()    HSPWMA_SetOC2OutputMode(8)
#define HSPWMA_OC2REFReTrigOPMPWM2()    HSPWMA_SetOC2OutputMode(9)
#define HSPWMA_OC2REFCombinedPWM1()     HSPWMA_SetOC2OutputMode(12)
#define HSPWMA_OC2REFCombinedPWM2()     HSPWMA_SetOC2OutputMode(13)
#define HSPWMA_OC2REFAsymmetricPWM1()   HSPWMA_SetOC2OutputMode(14)
#define HSPWMA_OC2REFAsymmetricPWM2()   HSPWMA_SetOC2OutputMode(15)

#define PWMACCMR2_OC2PE_MSK             BIT3
#define PWMA_UnbufferCCR2()             CLR_REG_BIT(PWMA_CCMR2, PWMACCMR2_OC2PE_MSK)
#define PWMA_BufferCCR2()               SET_REG_BIT(PWMA_CCMR2, PWMACCMR2_OC2PE_MSK)

#define HSPWMA_UnbufferCCR2()           CLR_HSPWMA_BIT(PWMA_CCMR2, PWMACCMR2_OC2PE_MSK)
#define HSPWMA_BufferCCR2()             SET_HSPWMA_BIT(PWMA_CCMR2, PWMACCMR2_OC2PE_MSK)

#define PWMACCMR2_OC2FE_MSK             BIT2
#define PWMA_DisableOC2FastMode()       CLR_REG_BIT(PWMA_CCMR2, PWMACCMR2_OC2FE_MSK)
#define PWMA_EnableOC2FastMode()        SET_REG_BIT(PWMA_CCMR2, PWMACCMR2_OC2FE_MSK)

#define HSPWMA_DisableOC2FastMode()     CLR_HSPWMA_BIT(PWMA_CCMR2, PWMACCMR2_OC2FE_MSK)
#define HSPWMA_EnableOC2FastMode()      SET_HSPWMA_BIT(PWMA_CCMR2, PWMACCMR2_OC2FE_MSK)

#define PWMACCMR2_CC2S_MSK              (BIT1 | BIT0)
#define PWMA_SetCC2Mode(n)              MODIFY_REG(PWMA_CCMR2,  PWMACCMR2_CC2S_MSK, ((n) << 0))
#define PWMA_CC2Output()                PWMA_SetCC2Mode(0)
#define PWMA_CC2CaptureTI2FP2()         PWMA_SetCC2Mode(1)
#define PWMA_CC2CaptureTI1FP2()         PWMA_SetCC2Mode(2)
#define PWMA_CC2CaptureTRC()            PWMA_SetCC2Mode(3)

#define HSPWMA_SetCC2Mode(n)            MODIFY_HSPWMA(PWMA_CCMR2,  PWMACCMR2_CC2S_MSK, ((n) << 0))
#define HSPWMA_CC2Output()              HSPWMA_SetCC2Mode(0)
#define HSPWMA_CC2CaptureTI2FP2()       HSPWMA_SetCC2Mode(1)
#define HSPWMA_CC2CaptureTI1FP2()       HSPWMA_SetCC2Mode(2)
#define HSPWMA_CC2CaptureTRC()          HSPWMA_SetCC2Mode(3)

#define PWMACCMR2_IC2F_MSK              (BIT_HN)
#define PWMA_SetIC2Filter(n)            MODIFY_REG(PWMA_CCMR2,  PWMACCMR2_IC2F_MSK, ((n) << 4))
#define PWMA_IC2Filter1()               PWMA_SetIC2Filter(0)
#define PWMA_IC2Filter2()               PWMA_SetIC2Filter(1)
#define PWMA_IC2Filter4()               PWMA_SetIC2Filter(2)
#define PWMA_IC2Filter8()               PWMA_SetIC2Filter(3)
#define PWMA_IC2Filter12()              PWMA_SetIC2Filter(4)
#define PWMA_IC2Filter16()              PWMA_SetIC2Filter(5)
#define PWMA_IC2Filter24()              PWMA_SetIC2Filter(6)
#define PWMA_IC2Filter32()              PWMA_SetIC2Filter(7)
#define PWMA_IC2Filter48()              PWMA_SetIC2Filter(8)
#define PWMA_IC2Filter64()              PWMA_SetIC2Filter(9)
#define PWMA_IC2Filter80()              PWMA_SetIC2Filter(10)
#define PWMA_IC2Filter96()              PWMA_SetIC2Filter(11)
#define PWMA_IC2Filter128()             PWMA_SetIC2Filter(12)
#define PWMA_IC2Filter160()             PWMA_SetIC2Filter(13)
#define PWMA_IC2Filter192()             PWMA_SetIC2Filter(14)
#define PWMA_IC2Filter256()             PWMA_SetIC2Filter(15)

#define HSPWMA_SetIC2Filter(n)          MODIFY_HSPWMA(PWMA_CCMR2,  PWMACCMR2_IC2F_MSK, ((n) << 4))
#define HSPWMA_IC2Filter1()             HSPWMA_SetIC2Filter(0)
#define HSPWMA_IC2Filter2()             HSPWMA_SetIC2Filter(1)
#define HSPWMA_IC2Filter4()             HSPWMA_SetIC2Filter(2)
#define HSPWMA_IC2Filter8()             HSPWMA_SetIC2Filter(3)
#define HSPWMA_IC2Filter12()            HSPWMA_SetIC2Filter(4)
#define HSPWMA_IC2Filter16()            HSPWMA_SetIC2Filter(5)
#define HSPWMA_IC2Filter24()            HSPWMA_SetIC2Filter(6)
#define HSPWMA_IC2Filter32()            HSPWMA_SetIC2Filter(7)
#define HSPWMA_IC2Filter48()            HSPWMA_SetIC2Filter(8)
#define HSPWMA_IC2Filter64()            HSPWMA_SetIC2Filter(9)
#define HSPWMA_IC2Filter80()            HSPWMA_SetIC2Filter(10)
#define HSPWMA_IC2Filter96()            HSPWMA_SetIC2Filter(11)
#define HSPWMA_IC2Filter128()           HSPWMA_SetIC2Filter(12)
#define HSPWMA_IC2Filter160()           HSPWMA_SetIC2Filter(13)
#define HSPWMA_IC2Filter192()           HSPWMA_SetIC2Filter(14)
#define HSPWMA_IC2Filter256()           HSPWMA_SetIC2Filter(15)

#define PWMACCMR2_IC2PS_MSK             (BIT3 | BIT2)
#define PWMA_SetIC2Divider(n)           MODIFY_REG(PWMA_CCMR2,  PWMACCMR2_IC2PS_MSK, ((n) << 2))
#define PWMA_IC2Divider1()              PWMA_SetIC2Divider(0)
#define PWMA_IC2Divider2()              PWMA_SetIC2Divider(1)
#define PWMA_IC2Divider4()              PWMA_SetIC2Divider(2)
#define PWMA_IC2Divider8()              PWMA_SetIC2Divider(3)

#define HSPWMA_SetIC2Divider(n)         MODIFY_HSPWMA(PWMA_CCMR2,  PWMACCMR2_IC2PS_MSK, ((n) << 2))
#define HSPWMA_IC2Divider1()            HSPWMA_SetIC2Divider(0)
#define HSPWMA_IC2Divider2()            HSPWMA_SetIC2Divider(1)
#define HSPWMA_IC2Divider4()            HSPWMA_SetIC2Divider(2)
#define HSPWMA_IC2Divider8()            HSPWMA_SetIC2Divider(3)

#define PWMACCMR3_OC3CE_MSK             BIT7
#define PWMA_EnableETRFClearOC3REF()    SET_REG_BIT(PWMA_CCMR3, PWMACCMR3_OC3CE_MSK)
#define PWMA_DisableETRFClearOC3REF()   CLR_REG_BIT(PWMA_CCMR3, PWMACCMR3_OC3CE_MSK)

#define HSPWMA_EnableETRFClearOC3REF()  SET_HSPWMA_BIT(PWMA_CCMR3, PWMACCMR3_OC3CE_MSK)
#define HSPWMA_DisableETRFClearOC3REF() CLR_HSPWMA_BIT(PWMA_CCMR3, PWMACCMR3_OC3CE_MSK)

#define PWMACCMR3_OC3M_MSK              (BIT6 | BIT5 | BIT4)
#define PWMACCMR3X_OC3M3_MSK            BIT0
#define PWMA_SetOC3OutputMode(n)        MODIFY_REG(PWMA_CCMR3,  PWMACCMR3_OC3M_MSK, ((n) << 4)); \
                                        MODIFY_REG(PWMA_CCMR3X, PWMACCMR3X_OC3M3_MSK, (((n) >> 3) << 0))
#define PWMA_OC3REFFrozen()             PWMA_SetOC3OutputMode(0)
#define PWMA_OC3REFHighIfMatch()        PWMA_SetOC3OutputMode(1)
#define PWMA_OC3REFLowIfMatch()         PWMA_SetOC3OutputMode(2)
#define PWMA_OC3REFToggleIfMatch()      PWMA_SetOC3OutputMode(3)
#define PWMA_OC3REFForceLow()           PWMA_SetOC3OutputMode(4)
#define PWMA_OC3REFForceHigh()          PWMA_SetOC3OutputMode(5)
#define PWMA_OC3REFPWMMode1()           PWMA_SetOC3OutputMode(6)
#define PWMA_OC3REFPWMMode2()           PWMA_SetOC3OutputMode(7)
#define PWMA_OC3REFReTrigOPMPWM1()      PWMA_SetOC3OutputMode(8)
#define PWMA_OC3REFReTrigOPMPWM2()      PWMA_SetOC3OutputMode(9)
#define PWMA_OC3REFCombinedPWM1()       PWMA_SetOC3OutputMode(12)
#define PWMA_OC3REFCombinedPWM2()       PWMA_SetOC3OutputMode(13)
#define PWMA_OC3REFAsymmetricPWM1()     PWMA_SetOC3OutputMode(14)
#define PWMA_OC3REFAsymmetricPWM2()     PWMA_SetOC3OutputMode(15)

#define HSPWMA_SetOC3OutputMode(n)      MODIFY_HSPWMA(PWMA_CCMR3,  PWMACCMR3_OC3M_MSK, ((n) << 4)); \
                                        MODIFY_HSPWMA(PWMA_CCMR3X, PWMACCMR3X_OC3M3_MSK, (((n) >> 3) << 0))
#define HSPWMA_OC3REFFrozen()           HSPWMA_SetOC3OutputMode(0)
#define HSPWMA_OC3REFHighIfMatch()      HSPWMA_SetOC3OutputMode(1)
#define HSPWMA_OC3REFLowIfMatch()       HSPWMA_SetOC3OutputMode(2)
#define HSPWMA_OC3REFToggleIfMatch()    HSPWMA_SetOC3OutputMode(3)
#define HSPWMA_OC3REFForceLow()         HSPWMA_SetOC3OutputMode(4)
#define HSPWMA_OC3REFForceHigh()        HSPWMA_SetOC3OutputMode(5)
#define HSPWMA_OC3REFPWMMode1()         HSPWMA_SetOC3OutputMode(6)
#define HSPWMA_OC3REFPWMMode2()         HSPWMA_SetOC3OutputMode(7)
#define HSPWMA_OC3REFReTrigOPMPWM1()    HSPWMA_SetOC3OutputMode(8)
#define HSPWMA_OC3REFReTrigOPMPWM2()    HSPWMA_SetOC3OutputMode(9)
#define HSPWMA_OC3REFCombinedPWM1()     HSPWMA_SetOC3OutputMode(12)
#define HSPWMA_OC3REFCombinedPWM2()     HSPWMA_SetOC3OutputMode(13)
#define HSPWMA_OC3REFAsymmetricPWM1()   HSPWMA_SetOC3OutputMode(14)
#define HSPWMA_OC3REFAsymmetricPWM2()   HSPWMA_SetOC3OutputMode(15)

#define PWMACCMR3_OC3PE_MSK             BIT3
#define PWMA_UnbufferCCR3()             CLR_REG_BIT(PWMA_CCMR3, PWMACCMR3_OC3PE_MSK)
#define PWMA_BufferCCR3()               SET_REG_BIT(PWMA_CCMR3, PWMACCMR3_OC3PE_MSK)

#define HSPWMA_UnbufferCCR3()           CLR_HSPWMA_BIT(PWMA_CCMR3, PWMACCMR3_OC3PE_MSK)
#define HSPWMA_BufferCCR3()             SET_HSPWMA_BIT(PWMA_CCMR3, PWMACCMR3_OC3PE_MSK)

#define PWMACCMR3_OC3FE_MSK             BIT2
#define PWMA_DisableOC3FastMode()       CLR_REG_BIT(PWMA_CCMR3, PWMACCMR3_OC3FE_MSK)
#define PWMA_EnableOC3FastMode()        SET_REG_BIT(PWMA_CCMR3, PWMACCMR3_OC3FE_MSK)

#define HSPWMA_DisableOC3FastMode()     CLR_HSPWMA_BIT(PWMA_CCMR3, PWMACCMR3_OC3FE_MSK)
#define HSPWMA_EnableOC3FastMode()      SET_HSPWMA_BIT(PWMA_CCMR3, PWMACCMR3_OC3FE_MSK)

#define PWMACCMR3_CC3S_MSK              (BIT1 | BIT0)
#define PWMA_SetCC3Mode(n)              MODIFY_REG(PWMA_CCMR3,  PWMACCMR3_CC3S_MSK, ((n) << 0))
#define PWMA_CC3Output()                PWMA_SetCC3Mode(0)
#define PWMA_CC3CaptureTI3FP3()         PWMA_SetCC3Mode(1)
#define PWMA_CC3CaptureTI4FP3()         PWMA_SetCC3Mode(2)
#define PWMA_CC3CaptureTRC()            PWMA_SetCC3Mode(3)

#define HSPWMA_SetCC3Mode(n)            MODIFY_HSPWMA(PWMA_CCMR3,  PWMACCMR3_CC3S_MSK, ((n) << 0))
#define HSPWMA_CC3Output()              HSPWMA_SetCC3Mode(0)
#define HSPWMA_CC3CaptureTI3FP3()       HSPWMA_SetCC3Mode(1)
#define HSPWMA_CC3CaptureTI4FP3()       HSPWMA_SetCC3Mode(2)
#define HSPWMA_CC3CaptureTRC()          HSPWMA_SetCC3Mode(3)

#define PWMACCMR3_IC3F_MSK              (BIT_HN)
#define PWMA_SetIC3Filter(n)            MODIFY_REG(PWMA_CCMR3,  PWMACCMR3_IC3F_MSK, ((n) << 4))
#define PWMA_IC3Filter1()               PWMA_SetIC3Filter(0)
#define PWMA_IC3Filter2()               PWMA_SetIC3Filter(1)
#define PWMA_IC3Filter4()               PWMA_SetIC3Filter(2)
#define PWMA_IC3Filter8()               PWMA_SetIC3Filter(3)
#define PWMA_IC3Filter12()              PWMA_SetIC3Filter(4)
#define PWMA_IC3Filter16()              PWMA_SetIC3Filter(5)
#define PWMA_IC3Filter24()              PWMA_SetIC3Filter(6)
#define PWMA_IC3Filter32()              PWMA_SetIC3Filter(7)
#define PWMA_IC3Filter48()              PWMA_SetIC3Filter(8)
#define PWMA_IC3Filter64()              PWMA_SetIC3Filter(9)
#define PWMA_IC3Filter80()              PWMA_SetIC3Filter(10)
#define PWMA_IC3Filter96()              PWMA_SetIC3Filter(11)
#define PWMA_IC3Filter128()             PWMA_SetIC3Filter(12)
#define PWMA_IC3Filter160()             PWMA_SetIC3Filter(13)
#define PWMA_IC3Filter192()             PWMA_SetIC3Filter(14)
#define PWMA_IC3Filter256()             PWMA_SetIC3Filter(15)

#define HSPWMA_SetIC3Filter(n)          MODIFY_HSPWMA(PWMA_CCMR3,  PWMACCMR3_IC3F_MSK, ((n) << 4))
#define HSPWMA_IC3Filter1()             HSPWMA_SetIC3Filter(0)
#define HSPWMA_IC3Filter2()             HSPWMA_SetIC3Filter(1)
#define HSPWMA_IC3Filter4()             HSPWMA_SetIC3Filter(2)
#define HSPWMA_IC3Filter8()             HSPWMA_SetIC3Filter(3)
#define HSPWMA_IC3Filter12()            HSPWMA_SetIC3Filter(4)
#define HSPWMA_IC3Filter16()            HSPWMA_SetIC3Filter(5)
#define HSPWMA_IC3Filter24()            HSPWMA_SetIC3Filter(6)
#define HSPWMA_IC3Filter32()            HSPWMA_SetIC3Filter(7)
#define HSPWMA_IC3Filter48()            HSPWMA_SetIC3Filter(8)
#define HSPWMA_IC3Filter64()            HSPWMA_SetIC3Filter(9)
#define HSPWMA_IC3Filter80()            HSPWMA_SetIC3Filter(10)
#define HSPWMA_IC3Filter96()            HSPWMA_SetIC3Filter(11)
#define HSPWMA_IC3Filter128()           HSPWMA_SetIC3Filter(12)
#define HSPWMA_IC3Filter160()           HSPWMA_SetIC3Filter(13)
#define HSPWMA_IC3Filter192()           HSPWMA_SetIC3Filter(14)
#define HSPWMA_IC3Filter256()           HSPWMA_SetIC3Filter(15)

#define PWMACCMR3_IC3PS_MSK             (BIT3 | BIT2)
#define PWMA_SetIC3Divider(n)           MODIFY_REG(PWMA_CCMR3,  PWMACCMR3_IC3PS_MSK, ((n) << 2))
#define PWMA_IC3Divider1()              PWMA_SetIC3Divider(0)
#define PWMA_IC3Divider2()              PWMA_SetIC3Divider(1)
#define PWMA_IC3Divider4()              PWMA_SetIC3Divider(2)
#define PWMA_IC3Divider8()              PWMA_SetIC3Divider(3)

#define HSPWMA_SetIC3Divider(n)         MODIFY_HSPWMA(PWMA_CCMR3,  PWMACCMR3_IC3PS_MSK, ((n) << 2))
#define HSPWMA_IC3Divider1()            HSPWMA_SetIC3Divider(0)
#define HSPWMA_IC3Divider2()            HSPWMA_SetIC3Divider(1)
#define HSPWMA_IC3Divider4()            HSPWMA_SetIC3Divider(2)
#define HSPWMA_IC3Divider8()            HSPWMA_SetIC3Divider(3)

#define PWMACCMR4_OC4CE_MSK             BIT7
#define PWMA_EnableETRFClearOC4REF()    SET_REG_BIT(PWMA_CCMR4, PWMACCMR4_OC4CE_MSK)
#define PWMA_DisableETRFClearOC4REF()   CLR_REG_BIT(PWMA_CCMR4, PWMACCMR4_OC4CE_MSK)

#define HSPWMA_EnableETRFClearOC4REF()  SET_HSPWMA_BIT(PWMA_CCMR4, PWMACCMR4_OC4CE_MSK)
#define HSPWMA_DisableETRFClearOC4REF() CLR_HSPWMA_BIT(PWMA_CCMR4, PWMACCMR4_OC4CE_MSK)

#define PWMACCMR4_OC4M_MSK              (BIT6 | BIT5 | BIT4)
#define PWMACCMR4X_OC4M3_MSK            BIT0
#define PWMA_SetOC4OutputMode(n)        MODIFY_REG(PWMA_CCMR4,  PWMACCMR4_OC4M_MSK, ((n) << 4)); \
                                        MODIFY_REG(PWMA_CCMR4X, PWMACCMR4X_OC4M3_MSK, (((n) >> 3) << 0))
#define PWMA_OC4REFFrozen()             PWMA_SetOC4OutputMode(0)
#define PWMA_OC4REFHighIfMatch()        PWMA_SetOC4OutputMode(1)
#define PWMA_OC4REFLowIfMatch()         PWMA_SetOC4OutputMode(2)
#define PWMA_OC4REFToggleIfMatch()      PWMA_SetOC4OutputMode(3)
#define PWMA_OC4REFForceLow()           PWMA_SetOC4OutputMode(4)
#define PWMA_OC4REFForceHigh()          PWMA_SetOC4OutputMode(5)
#define PWMA_OC4REFPWMMode1()           PWMA_SetOC4OutputMode(6)
#define PWMA_OC4REFPWMMode2()           PWMA_SetOC4OutputMode(7)
#define PWMA_OC4REFReTrigOPMPWM1()      PWMA_SetOC4OutputMode(8)
#define PWMA_OC4REFReTrigOPMPWM2()      PWMA_SetOC4OutputMode(9)
#define PWMA_OC4REFCombinedPWM1()       PWMA_SetOC4OutputMode(12)
#define PWMA_OC4REFCombinedPWM2()       PWMA_SetOC4OutputMode(13)
#define PWMA_OC4REFAsymmetricPWM1()     PWMA_SetOC4OutputMode(14)
#define PWMA_OC4REFAsymmetricPWM2()     PWMA_SetOC4OutputMode(15)

#define HSPWMA_SetOC4OutputMode(n)      MODIFY_HSPWMA(PWMA_CCMR4,  PWMACCMR4_OC4M_MSK, ((n) << 4)); \
                                        MODIFY_HSPWMA(PWMA_CCMR4X, PWMACCMR4X_OC4M3_MSK, (((n) >> 3) << 0))
#define HSPWMA_OC4REFFrozen()           HSPWMA_SetOC4OutputMode(0)
#define HSPWMA_OC4REFHighIfMatch()      HSPWMA_SetOC4OutputMode(1)
#define HSPWMA_OC4REFLowIfMatch()       HSPWMA_SetOC4OutputMode(2)
#define HSPWMA_OC4REFToggleIfMatch()    HSPWMA_SetOC4OutputMode(3)
#define HSPWMA_OC4REFForceLow()         HSPWMA_SetOC4OutputMode(4)
#define HSPWMA_OC4REFForceHigh()        HSPWMA_SetOC4OutputMode(5)
#define HSPWMA_OC4REFPWMMode1()         HSPWMA_SetOC4OutputMode(6)
#define HSPWMA_OC4REFPWMMode2()         HSPWMA_SetOC4OutputMode(7)
#define HSPWMA_OC4REFReTrigOPMPWM1()    HSPWMA_SetOC4OutputMode(8)
#define HSPWMA_OC4REFReTrigOPMPWM2()    HSPWMA_SetOC4OutputMode(9)
#define HSPWMA_OC4REFCombinedPWM1()     HSPWMA_SetOC4OutputMode(12)
#define HSPWMA_OC4REFCombinedPWM2()     HSPWMA_SetOC4OutputMode(13)
#define HSPWMA_OC4REFAsymmetricPWM1()   HSPWMA_SetOC4OutputMode(14)
#define HSPWMA_OC4REFAsymmetricPWM2()   HSPWMA_SetOC4OutputMode(15)

#define PWMACCMR4_OC4PE_MSK             BIT3
#define PWMA_UnbufferCCR4()             CLR_REG_BIT(PWMA_CCMR4, PWMACCMR4_OC4PE_MSK)
#define PWMA_BufferCCR4()               SET_REG_BIT(PWMA_CCMR4, PWMACCMR4_OC4PE_MSK)

#define HSPWMA_UnbufferCCR4()           CLR_HSPWMA_BIT(PWMA_CCMR4, PWMACCMR4_OC4PE_MSK)
#define HSPWMA_BufferCCR4()             SET_HSPWMA_BIT(PWMA_CCMR4, PWMACCMR4_OC4PE_MSK)

#define PWMACCMR4_OC4FE_MSK             BIT2
#define PWMA_DisableOC4FastMode()       CLR_REG_BIT(PWMA_CCMR4, PWMACCMR4_OC4FE_MSK)
#define PWMA_EnableOC4FastMode()        SET_REG_BIT(PWMA_CCMR4, PWMACCMR4_OC4FE_MSK)

#define HSPWMA_DisableOC4FastMode()     CLR_HSPWMA_BIT(PWMA_CCMR4, PWMACCMR4_OC4FE_MSK)
#define HSPWMA_EnableOC4FastMode()      SET_HSPWMA_BIT(PWMA_CCMR4, PWMACCMR4_OC4FE_MSK)

#define PWMACCMR4_CC4S_MSK              (BIT1 | BIT0)
#define PWMA_SetCC4Mode(n)              MODIFY_REG(PWMA_CCMR4,  PWMACCMR4_CC4S_MSK, ((n) << 0))
#define PWMA_CC4Output()                PWMA_SetCC4Mode(0)
#define PWMA_CC4CaptureTI4FP4()         PWMA_SetCC4Mode(1)
#define PWMA_CC4CaptureTI3FP4()         PWMA_SetCC4Mode(2)
#define PWMA_CC4CaptureTRC()            PWMA_SetCC4Mode(3)

#define HSPWMA_SetCC4Mode(n)            MODIFY_HSPWMA(PWMA_CCMR4,  PWMACCMR4_CC4S_MSK, ((n) << 0))
#define HSPWMA_CC4Output()              HSPWMA_SetCC4Mode(0)
#define HSPWMA_CC4CaptureTI4FP4()       HSPWMA_SetCC4Mode(1)
#define HSPWMA_CC4CaptureTI3FP4()       HSPWMA_SetCC4Mode(2)
#define HSPWMA_CC4CaptureTRC()          HSPWMA_SetCC4Mode(3)

#define PWMACCMR4_IC4F_MSK              (BIT_HN)
#define PWMA_SetIC4Filter(n)            MODIFY_REG(PWMA_CCMR4,  PWMACCMR4_IC4F_MSK, ((n) << 4))
#define PWMA_IC4Filter1()               PWMA_SetIC4Filter(0)
#define PWMA_IC4Filter2()               PWMA_SetIC4Filter(1)
#define PWMA_IC4Filter4()               PWMA_SetIC4Filter(2)
#define PWMA_IC4Filter8()               PWMA_SetIC4Filter(3)
#define PWMA_IC4Filter12()              PWMA_SetIC4Filter(4)
#define PWMA_IC4Filter16()              PWMA_SetIC4Filter(5)
#define PWMA_IC4Filter24()              PWMA_SetIC4Filter(6)
#define PWMA_IC4Filter32()              PWMA_SetIC4Filter(7)
#define PWMA_IC4Filter48()              PWMA_SetIC4Filter(8)
#define PWMA_IC4Filter64()              PWMA_SetIC4Filter(9)
#define PWMA_IC4Filter80()              PWMA_SetIC4Filter(10)
#define PWMA_IC4Filter96()              PWMA_SetIC4Filter(11)
#define PWMA_IC4Filter128()             PWMA_SetIC4Filter(12)
#define PWMA_IC4Filter160()             PWMA_SetIC4Filter(13)
#define PWMA_IC4Filter192()             PWMA_SetIC4Filter(14)
#define PWMA_IC4Filter256()             PWMA_SetIC4Filter(15)

#define HSPWMA_SetIC4Filter(n)          MODIFY_HSPWMA(PWMA_CCMR4,  PWMACCMR4_IC4F_MSK, ((n) << 4))
#define HSPWMA_IC4Filter1()             HSPWMA_SetIC4Filter(0)
#define HSPWMA_IC4Filter2()             HSPWMA_SetIC4Filter(1)
#define HSPWMA_IC4Filter4()             HSPWMA_SetIC4Filter(2)
#define HSPWMA_IC4Filter8()             HSPWMA_SetIC4Filter(3)
#define HSPWMA_IC4Filter12()            HSPWMA_SetIC4Filter(4)
#define HSPWMA_IC4Filter16()            HSPWMA_SetIC4Filter(5)
#define HSPWMA_IC4Filter24()            HSPWMA_SetIC4Filter(6)
#define HSPWMA_IC4Filter32()            HSPWMA_SetIC4Filter(7)
#define HSPWMA_IC4Filter48()            HSPWMA_SetIC4Filter(8)
#define HSPWMA_IC4Filter64()            HSPWMA_SetIC4Filter(9)
#define HSPWMA_IC4Filter80()            HSPWMA_SetIC4Filter(10)
#define HSPWMA_IC4Filter96()            HSPWMA_SetIC4Filter(11)
#define HSPWMA_IC4Filter128()           HSPWMA_SetIC4Filter(12)
#define HSPWMA_IC4Filter160()           HSPWMA_SetIC4Filter(13)
#define HSPWMA_IC4Filter192()           HSPWMA_SetIC4Filter(14)
#define HSPWMA_IC4Filter256()           HSPWMA_SetIC4Filter(15)

#define PWMACCMR4_IC4PS_MSK             (BIT3 | BIT2)
#define PWMA_SetIC4Divider(n)           MODIFY_REG(PWMA_CCMR4,  PWMACCMR4_IC4PS_MSK, ((n) << 2))
#define PWMA_IC4Divider1()              PWMA_SetIC4Divider(0)
#define PWMA_IC4Divider2()              PWMA_SetIC4Divider(1)
#define PWMA_IC4Divider4()              PWMA_SetIC4Divider(2)
#define PWMA_IC4Divider8()              PWMA_SetIC4Divider(3)

#define HSPWMA_SetIC4Divider(n)         MODIFY_HSPWMA(PWMA_CCMR4,  PWMACCMR4_IC4PS_MSK, ((n) << 2))
#define HSPWMA_IC4Divider1()            HSPWMA_SetIC4Divider(0)
#define HSPWMA_IC4Divider2()            HSPWMA_SetIC4Divider(1)
#define HSPWMA_IC4Divider4()            HSPWMA_SetIC4Divider(2)
#define HSPWMA_IC4Divider8()            HSPWMA_SetIC4Divider(3)

#define PWMACCMR5_OC5CE_MSK             BIT7
#define PWMA_EnableETRFClearOC5REF()    SET_REG_BIT(PWMA_CCMR5, PWMACCMR5_OC5CE_MSK)
#define PWMA_DisableETRFClearOC5REF()   CLR_REG_BIT(PWMA_CCMR5, PWMACCMR5_OC5CE_MSK)

#define HSPWMA_EnableETRFClearOC5REF()  SET_HSPWMA_BIT(PWMA_CCMR5, PWMACCMR5_OC5CE_MSK)
#define HSPWMA_DisableETRFClearOC5REF() CLR_HSPWMA_BIT(PWMA_CCMR5, PWMACCMR5_OC5CE_MSK)

#define PWMACCMR5_OC5M_MSK              (BIT6 | BIT5 | BIT4)
#define PWMACCMR5X_OC5M3_MSK            BIT0
#define PWMA_SetOC5OutputMode(n)        MODIFY_REG(PWMA_CCMR5,  PWMACCMR5_OC5M_MSK, ((n) << 4)); \
                                        MODIFY_REG(PWMA_CCMR5X, PWMACCMR5X_OC5M3_MSK, (((n) >> 3) << 0))
#define PWMA_OC5REFFrozen()             PWMA_SetOC5OutputMode(0)
#define PWMA_OC5REFHighIfMatch()        PWMA_SetOC5OutputMode(1)
#define PWMA_OC5REFLowIfMatch()         PWMA_SetOC5OutputMode(2)
#define PWMA_OC5REFToggleIfMatch()      PWMA_SetOC5OutputMode(3)
#define PWMA_OC5REFForceLow()           PWMA_SetOC5OutputMode(4)
#define PWMA_OC5REFForceHigh()          PWMA_SetOC5OutputMode(5)
#define PWMA_OC5REFPWMMode1()           PWMA_SetOC5OutputMode(6)
#define PWMA_OC5REFPWMMode2()           PWMA_SetOC5OutputMode(7)
#define PWMA_OC5REFReTrigOPMPWM1()      PWMA_SetOC5OutputMode(8)
#define PWMA_OC5REFReTrigOPMPWM2()      PWMA_SetOC5OutputMode(9)
#define PWMA_OC5REFCombinedPWM1()       PWMA_SetOC5OutputMode(12)
#define PWMA_OC5REFCombinedPWM2()       PWMA_SetOC5OutputMode(13)
#define PWMA_OC5REFAsymmetricPWM1()     PWMA_SetOC5OutputMode(14)
#define PWMA_OC5REFAsymmetricPWM2()     PWMA_SetOC5OutputMode(15)

#define HSPWMA_SetOC5OutputMode(n)      MODIFY_HSPWMA(PWMA_CCMR5,  PWMACCMR5_OC5M_MSK, ((n) << 4)); \
                                        MODIFY_HSPWMA(PWMA_CCMR5X, PWMACCMR5X_OC5M3_MSK, (((n) >> 3) << 0))
#define HSPWMA_OC5REFFrozen()           HSPWMA_SetOC5OutputMode(0)
#define HSPWMA_OC5REFHighIfMatch()      HSPWMA_SetOC5OutputMode(1)
#define HSPWMA_OC5REFLowIfMatch()       HSPWMA_SetOC5OutputMode(2)
#define HSPWMA_OC5REFToggleIfMatch()    HSPWMA_SetOC5OutputMode(3)
#define HSPWMA_OC5REFForceLow()         HSPWMA_SetOC5OutputMode(4)
#define HSPWMA_OC5REFForceHigh()        HSPWMA_SetOC5OutputMode(5)
#define HSPWMA_OC5REFPWMMode1()         HSPWMA_SetOC5OutputMode(6)
#define HSPWMA_OC5REFPWMMode2()         HSPWMA_SetOC5OutputMode(7)
#define HSPWMA_OC5REFReTrigOPMPWM1()    HSPWMA_SetOC5OutputMode(8)
#define HSPWMA_OC5REFReTrigOPMPWM2()    HSPWMA_SetOC5OutputMode(9)
#define HSPWMA_OC5REFCombinedPWM1()     HSPWMA_SetOC5OutputMode(12)
#define HSPWMA_OC5REFCombinedPWM2()     HSPWMA_SetOC5OutputMode(13)
#define HSPWMA_OC5REFAsymmetricPWM1()   HSPWMA_SetOC5OutputMode(14)
#define HSPWMA_OC5REFAsymmetricPWM2()   HSPWMA_SetOC5OutputMode(15)

#define PWMACCMR5_OC5PE_MSK             BIT3
#define PWMA_UnbufferCCR5()             CLR_REG_BIT(PWMA_CCMR5, PWMACCMR5_OC5PE_MSK)
#define PWMA_BufferCCR5()               SET_REG_BIT(PWMA_CCMR5, PWMACCMR5_OC5PE_MSK)

#define HSPWMA_UnbufferCCR5()           CLR_HSPWMA_BIT(PWMA_CCMR5, PWMACCMR5_OC5PE_MSK)
#define HSPWMA_BufferCCR5()             SET_HSPWMA_BIT(PWMA_CCMR5, PWMACCMR5_OC5PE_MSK)

#define PWMACCMR6_OC6CE_MSK             BIT7
#define PWMA_EnableETRFClearOC6REF()    SET_REG_BIT(PWMA_CCMR6, PWMACCMR6_OC6CE_MSK)
#define PWMA_DisableETRFClearOC6REF()   CLR_REG_BIT(PWMA_CCMR6, PWMACCMR6_OC6CE_MSK)

#define HSPWMA_EnableETRFClearOC6REF()  SET_HSPWMA_BIT(PWMA_CCMR6, PWMACCMR6_OC6CE_MSK)
#define HSPWMA_DisableETRFClearOC6REF() CLR_HSPWMA_BIT(PWMA_CCMR6, PWMACCMR6_OC6CE_MSK)

#define PWMACCMR6_OC6M_MSK              (BIT6 | BIT5 | BIT4)
#define PWMACCMR6X_OC6M3_MSK            BIT0
#define PWMA_SetOC6OutputMode(n)        MODIFY_REG(PWMA_CCMR6,  PWMACCMR6_OC6M_MSK, ((n) << 4)); \
                                        MODIFY_REG(PWMA_CCMR6X, PWMACCMR6X_OC6M3_MSK, (((n) >> 3) << 0))
#define PWMA_OC6REFFrozen()             PWMA_SetOC6OutputMode(0)
#define PWMA_OC6REFHighIfMatch()        PWMA_SetOC6OutputMode(1)
#define PWMA_OC6REFLowIfMatch()         PWMA_SetOC6OutputMode(2)
#define PWMA_OC6REFToggleIfMatch()      PWMA_SetOC6OutputMode(3)
#define PWMA_OC6REFForceLow()           PWMA_SetOC6OutputMode(4)
#define PWMA_OC6REFForceHigh()          PWMA_SetOC6OutputMode(5)
#define PWMA_OC6REFPWMMode1()           PWMA_SetOC6OutputMode(6)
#define PWMA_OC6REFPWMMode2()           PWMA_SetOC6OutputMode(7)
#define PWMA_OC6REFReTrigOPMPWM1()      PWMA_SetOC6OutputMode(8)
#define PWMA_OC6REFReTrigOPMPWM2()      PWMA_SetOC6OutputMode(9)
#define PWMA_OC6REFCombinedPWM1()       PWMA_SetOC6OutputMode(12)
#define PWMA_OC6REFCombinedPWM2()       PWMA_SetOC6OutputMode(13)
#define PWMA_OC6REFAsymmetricPWM1()     PWMA_SetOC6OutputMode(14)
#define PWMA_OC6REFAsymmetricPWM2()     PWMA_SetOC6OutputMode(15)

#define HSPWMA_SetOC6OutputMode(n)      MODIFY_HSPWMA(PWMA_CCMR6,  PWMACCMR6_OC6M_MSK, ((n) << 4)); \
                                        MODIFY_HSPWMA(PWMA_CCMR6X, PWMACCMR6X_OC6M3_MSK, (((n) >> 3) << 0))
#define HSPWMA_OC6REFFrozen()           HSPWMA_SetOC6OutputMode(0)
#define HSPWMA_OC6REFHighIfMatch()      HSPWMA_SetOC6OutputMode(1)
#define HSPWMA_OC6REFLowIfMatch()       HSPWMA_SetOC6OutputMode(2)
#define HSPWMA_OC6REFToggleIfMatch()    HSPWMA_SetOC6OutputMode(3)
#define HSPWMA_OC6REFForceLow()         HSPWMA_SetOC6OutputMode(4)
#define HSPWMA_OC6REFForceHigh()        HSPWMA_SetOC6OutputMode(5)
#define HSPWMA_OC6REFPWMMode1()         HSPWMA_SetOC6OutputMode(6)
#define HSPWMA_OC6REFPWMMode2()         HSPWMA_SetOC6OutputMode(7)
#define HSPWMA_OC6REFReTrigOPMPWM1()    HSPWMA_SetOC6OutputMode(8)
#define HSPWMA_OC6REFReTrigOPMPWM2()    HSPWMA_SetOC6OutputMode(9)
#define HSPWMA_OC6REFCombinedPWM1()     HSPWMA_SetOC6OutputMode(12)
#define HSPWMA_OC6REFCombinedPWM2()     HSPWMA_SetOC6OutputMode(13)
#define HSPWMA_OC6REFAsymmetricPWM1()   HSPWMA_SetOC6OutputMode(14)
#define HSPWMA_OC6REFAsymmetricPWM2()   HSPWMA_SetOC6OutputMode(15)

#define PWMACCMR6_OC6PE_MSK             BIT3
#define PWMA_UnbufferCCR6()             CLR_REG_BIT(PWMA_CCMR6, PWMACCMR6_OC6PE_MSK)
#define PWMA_BufferCCR6()               SET_REG_BIT(PWMA_CCMR6, PWMACCMR6_OC6PE_MSK)

#define HSPWMA_UnbufferCCR6()           CLR_HSPWMA_BIT(PWMA_CCMR6, PWMACCMR6_OC6PE_MSK)
#define HSPWMA_BufferCCR6()             SET_HSPWMA_BIT(PWMA_CCMR6, PWMACCMR6_OC6PE_MSK)

#define PWMACCER1_CC1E_MSK              BIT0
#define PWMA_CC1PEnable()               SET_REG_BIT(PWMA_CCER1, PWMACCER1_CC1E_MSK)
#define PWMA_CC1PDisable()              CLR_REG_BIT(PWMA_CCER1, PWMACCER1_CC1E_MSK)

#define HSPWMA_CC1PEnable()             SET_HSPWMA_BIT(PWMA_CCER1, PWMACCER1_CC1E_MSK)
#define HSPWMA_CC1PDisable()            CLR_HSPWMA_BIT(PWMA_CCER1, PWMACCER1_CC1E_MSK)

#define PWMACCER1_CC1P_MSK              BIT1
#define PWMA_CC1PNonInverted()          CLR_REG_BIT(PWMA_CCER1, PWMACCER1_CC1P_MSK)
#define PWMA_CC1PInverted()             SET_REG_BIT(PWMA_CCER1, PWMACCER1_CC1P_MSK)

#define HSPWMA_CC1PNonInverted()        CLR_HSPWMA_BIT(PWMA_CCER1, PWMACCER1_CC1P_MSK)
#define HSPWMA_CC1PInverted()           SET_HSPWMA_BIT(PWMA_CCER1, PWMACCER1_CC1P_MSK)

#define PWMACCER1_CC1NE_MSK             BIT2
#define PWMA_CC1NEnable()               SET_REG_BIT(PWMA_CCER1, PWMACCER1_CC1NE_MSK)
#define PWMA_CC1NDisable()              CLR_REG_BIT(PWMA_CCER1, PWMACCER1_CC1NE_MSK)

#define HSPWMA_CC1NEnable()             SET_HSPWMA_BIT(PWMA_CCER1, PWMACCER1_CC1NE_MSK)
#define HSPWMA_CC1NDisable()            CLR_HSPWMA_BIT(PWMA_CCER1, PWMACCER1_CC1NE_MSK)

#define PWMACCER1_CC1NP_MSK             BIT3
#define PWMA_CC1NNonInverted()          CLR_REG_BIT(PWMA_CCER1, PWMACCER1_CC1NP_MSK)
#define PWMA_CC1NInverted()             SET_REG_BIT(PWMA_CCER1, PWMACCER1_CC1NP_MSK)

#define HSPWMA_CC1NNonInverted()        CLR_HSPWMA_BIT(PWMA_CCER1, PWMACCER1_CC1NP_MSK)
#define HSPWMA_CC1NInverted()           SET_HSPWMA_BIT(PWMA_CCER1, PWMACCER1_CC1NP_MSK)

#define PWMACCER1_CC2E_MSK              BIT4
#define PWMA_CC2PEnable()               SET_REG_BIT(PWMA_CCER1, PWMACCER1_CC2E_MSK)
#define PWMA_CC2PDisable()              CLR_REG_BIT(PWMA_CCER1, PWMACCER1_CC2E_MSK)

#define HSPWMA_CC2PEnable()             SET_HSPWMA_BIT(PWMA_CCER1, PWMACCER1_CC2E_MSK)
#define HSPWMA_CC2PDisable()            CLR_HSPWMA_BIT(PWMA_CCER1, PWMACCER1_CC2E_MSK)

#define PWMACCER1_CC2P_MSK              BIT5
#define PWMA_CC2PNonInverted()          CLR_REG_BIT(PWMA_CCER1, PWMACCER1_CC2P_MSK)
#define PWMA_CC2PInverted()             SET_REG_BIT(PWMA_CCER1, PWMACCER1_CC2P_MSK)

#define HSPWMA_CC2PNonInverted()        CLR_HSPWMA_BIT(PWMA_CCER1, PWMACCER1_CC2P_MSK)
#define HSPWMA_CC2PInverted()           SET_HSPWMA_BIT(PWMA_CCER1, PWMACCER1_CC2P_MSK)

#define PWMACCER1_CC2NE_MSK             BIT6
#define PWMA_CC2NEnable()               SET_REG_BIT(PWMA_CCER1, PWMACCER1_CC2NE_MSK)
#define PWMA_CC2NDisable()              CLR_REG_BIT(PWMA_CCER1, PWMACCER1_CC2NE_MSK)

#define HSPWMA_CC2NEnable()             SET_HSPWMA_BIT(PWMA_CCER1, PWMACCER1_CC2NE_MSK)
#define HSPWMA_CC2NDisable()            CLR_HSPWMA_BIT(PWMA_CCER1, PWMACCER1_CC2NE_MSK)

#define PWMACCER1_CC2NP_MSK             BIT7
#define PWMA_CC2NNonInverted()          CLR_REG_BIT(PWMA_CCER1, PWMACCER1_CC2NP_MSK)
#define PWMA_CC2NInverted()             SET_REG_BIT(PWMA_CCER1, PWMACCER1_CC2NP_MSK)

#define HSPWMA_CC2NNonInverted()        CLR_HSPWMA_BIT(PWMA_CCER1, PWMACCER1_CC2NP_MSK)
#define HSPWMA_CC2NInverted()           SET_HSPWMA_BIT(PWMA_CCER1, PWMACCER1_CC2NP_MSK)

#define PWMACCER2_CC3E_MSK              BIT0
#define PWMA_CC3PEnable()               SET_REG_BIT(PWMA_CCER2, PWMACCER2_CC3E_MSK)
#define PWMA_CC3PDisable()              CLR_REG_BIT(PWMA_CCER2, PWMACCER2_CC3E_MSK)

#define HSPWMA_CC3PEnable()             SET_HSPWMA_BIT(PWMA_CCER2, PWMACCER2_CC3E_MSK)
#define HSPWMA_CC3PDisable()            CLR_HSPWMA_BIT(PWMA_CCER2, PWMACCER2_CC3E_MSK)

#define PWMACCER2_CC3P_MSK              BIT1
#define PWMA_CC3PNonInverted()          CLR_REG_BIT(PWMA_CCER2, PWMACCER2_CC3P_MSK)
#define PWMA_CC3PInverted()             SET_REG_BIT(PWMA_CCER2, PWMACCER2_CC3P_MSK)

#define HSPWMA_CC3PNonInverted()        CLR_HSPWMA_BIT(PWMA_CCER2, PWMACCER2_CC3P_MSK)
#define HSPWMA_CC3PInverted()           SET_HSPWMA_BIT(PWMA_CCER2, PWMACCER2_CC3P_MSK)

#define PWMACCER2_CC3NE_MSK             BIT2
#define PWMA_CC3NEnable()               SET_REG_BIT(PWMA_CCER2, PWMACCER2_CC3NE_MSK)
#define PWMA_CC3NDisable()              CLR_REG_BIT(PWMA_CCER2, PWMACCER2_CC3NE_MSK)

#define HSPWMA_CC3NEnable()             SET_HSPWMA_BIT(PWMA_CCER2, PWMACCER2_CC3NE_MSK)
#define HSPWMA_CC3NDisable()            CLR_HSPWMA_BIT(PWMA_CCER2, PWMACCER2_CC3NE_MSK)

#define PWMACCER2_CC3NP_MSK             BIT3
#define PWMA_CC3NNonInverted()          CLR_REG_BIT(PWMA_CCER2, PWMACCER2_CC3NP_MSK)
#define PWMA_CC3NInverted()             SET_REG_BIT(PWMA_CCER2, PWMACCER2_CC3NP_MSK)

#define HSPWMA_CC3NNonInverted()        CLR_HSPWMA_BIT(PWMA_CCER2, PWMACCER2_CC3NP_MSK)
#define HSPWMA_CC3NInverted()           SET_HSPWMA_BIT(PWMA_CCER2, PWMACCER2_CC3NP_MSK)

#define PWMACCER2_CC4E_MSK              BIT4
#define PWMA_CC4PEnable()               SET_REG_BIT(PWMA_CCER2, PWMACCER2_CC4E_MSK)
#define PWMA_CC4PDisable()              CLR_REG_BIT(PWMA_CCER2, PWMACCER2_CC4E_MSK)

#define HSPWMA_CC4PEnable()             SET_HSPWMA_BIT(PWMA_CCER2, PWMACCER2_CC4E_MSK)
#define HSPWMA_CC4PDisable()            CLR_HSPWMA_BIT(PWMA_CCER2, PWMACCER2_CC4E_MSK)

#define PWMACCER2_CC4P_MSK              BIT5
#define PWMA_CC4PNonInverted()          CLR_REG_BIT(PWMA_CCER2, PWMACCER2_CC4P_MSK)
#define PWMA_CC4PInverted()             SET_REG_BIT(PWMA_CCER2, PWMACCER2_CC4P_MSK)

#define HSPWMA_CC4PNonInverted()        CLR_HSPWMA_BIT(PWMA_CCER2, PWMACCER2_CC4P_MSK)
#define HSPWMA_CC4PInverted()           SET_HSPWMA_BIT(PWMA_CCER2, PWMACCER2_CC4P_MSK)

#define PWMACCER2_CC4NE_MSK             BIT6
#define PWMA_CC4NEnable()               SET_REG_BIT(PWMA_CCER2, PWMACCER2_CC4NE_MSK)
#define PWMA_CC4NDisable()              CLR_REG_BIT(PWMA_CCER2, PWMACCER2_CC4NE_MSK)

#define HSPWMA_CC4NEnable()             SET_HSPWMA_BIT(PWMA_CCER2, PWMACCER2_CC4NE_MSK)
#define HSPWMA_CC4NDisable()            CLR_HSPWMA_BIT(PWMA_CCER2, PWMACCER2_CC4NE_MSK)

#define PWMACCER2_CC4NP_MSK             BIT7
#define PWMA_CC4NNonInverted()          CLR_REG_BIT(PWMA_CCER2, PWMACCER2_CC4NP_MSK)
#define PWMA_CC4NInverted()             SET_REG_BIT(PWMA_CCER2, PWMACCER2_CC4NP_MSK)

#define HSPWMA_CC4NNonInverted()        CLR_HSPWMA_BIT(PWMA_CCER2, PWMACCER2_CC4NP_MSK)
#define HSPWMA_CC4NInverted()           SET_HSPWMA_BIT(PWMA_CCER2, PWMACCER2_CC4NP_MSK)

#define PWMACCER3_CC5E_MSK              BIT0
#define PWMA_CC5PEnable()               SET_REG_BIT(PWMA_CCER3, PWMACCER3_CC5E_MSK)
#define PWMA_CC5PDisable()              CLR_REG_BIT(PWMA_CCER3, PWMACCER3_CC5E_MSK)

#define HSPWMA_CC5PEnable()             SET_HSPWMA_BIT(PWMA_CCER3, PWMACCER3_CC5E_MSK)
#define HSPWMA_CC5PDisable()            CLR_HSPWMA_BIT(PWMA_CCER3, PWMACCER3_CC5E_MSK)

#define PWMACCER3_CC5P_MSK              BIT1
#define PWMA_CC5PNonInverted()          CLR_REG_BIT(PWMA_CCER3, PWMACCER3_CC5P_MSK)
#define PWMA_CC5PInverted()             SET_REG_BIT(PWMA_CCER3, PWMACCER3_CC5P_MSK)

#define HSPWMA_CC5PNonInverted()        CLR_HSPWMA_BIT(PWMA_CCER3, PWMACCER3_CC5P_MSK)
#define HSPWMA_CC5PInverted()           SET_HSPWMA_BIT(PWMA_CCER3, PWMACCER3_CC5P_MSK)

#define PWMACCER3_CC6E_MSK              BIT4
#define PWMA_CC6PEnable()               SET_REG_BIT(PWMA_CCER3, PWMACCER3_CC6E_MSK)
#define PWMA_CC6PDisable()              CLR_REG_BIT(PWMA_CCER3, PWMACCER3_CC6E_MSK)

#define HSPWMA_CC6PEnable()             SET_HSPWMA_BIT(PWMA_CCER3, PWMACCER3_CC6E_MSK)
#define HSPWMA_CC6PDisable()            CLR_HSPWMA_BIT(PWMA_CCER3, PWMACCER3_CC6E_MSK)

#define PWMACCER3_CC6P_MSK              BIT5
#define PWMA_CC6PNonInverted()          CLR_REG_BIT(PWMA_CCER3, PWMACCER3_CC6P_MSK)
#define PWMA_CC6PInverted()             SET_REG_BIT(PWMA_CCER3, PWMACCER3_CC6P_MSK)

#define HSPWMA_CC6PNonInverted()        CLR_HSPWMA_BIT(PWMA_CCER3, PWMACCER3_CC6P_MSK)
#define HSPWMA_CC6PInverted()           SET_HSPWMA_BIT(PWMA_CCER3, PWMACCER3_CC6P_MSK)

#define PWMABRK_MOE_MSK                 BIT7
#define PWMA_EnableMainOutput()         SET_REG_BIT(PWMA_BKR, PWMABRK_MOE_MSK)
#define PWMA_DisableMainOutput()        CLR_REG_BIT(PWMA_BKR, PWMABRK_MOE_MSK)

#define HSPWMA_EnableMainOutput()       SET_HSPWMA_BIT(PWMA_BKR, PWMABRK_MOE_MSK)
#define HSPWMA_DisableMainOutput()      CLR_HSPWMA_BIT(PWMA_BKR, PWMABRK_MOE_MSK)

#define PWMABRK_AOE_MSK                 BIT6
#define PWMA_EnableAutoOutput()         SET_REG_BIT(PWMA_BKR, PWMABRK_AOE_MSK)
#define PWMA_DisableAutoOutput()        CLR_REG_BIT(PWMA_BKR, PWMABRK_AOE_MSK)

#define HSPWMA_EnableAutoOutput()       SET_HSPWMA_BIT(PWMA_BKR, PWMABRK_AOE_MSK)
#define HSPWMA_DisableAutoOutput()      CLR_HSPWMA_BIT(PWMA_BKR, PWMABRK_AOE_MSK)

#define PWMABRK_BKP_MSK                 BIT5
#define PWMA_BRKNonInverted()           SET_REG_BIT(PWMA_BKR, PWMABRK_BKP_MSK)
#define PWMA_BRKInverted()              CLR_REG_BIT(PWMA_BKR, PWMABRK_BKP_MSK)

#define HSPWMA_BRKNonInverted()         SET_HSPWMA_BIT(PWMA_BKR, PWMABRK_BKP_MSK)
#define HSPWMA_BRKInverted()            CLR_HSPWMA_BIT(PWMA_BKR, PWMABRK_BKP_MSK)

#define PWMABRK_BKE_MSK                 BIT4
#define PWMA_BRKEnable()                SET_REG_BIT(PWMA_BKR, PWMABRK_BKE_MSK)
#define PWMA_BRKDisable()               CLR_REG_BIT(PWMA_BKR, PWMABRK_BKE_MSK)

#define HSPWMA_BRKEnable()              SET_HSPWMA_BIT(PWMA_BKR, PWMABRK_BKE_MSK)
#define HSPWMA_BRKDisable()             CLR_HSPWMA_BIT(PWMA_BKR, PWMABRK_BKE_MSK)

#define PWMABRK_OSSR_MSK                BIT3
#define PWMABRK_OSSI_MSK                BIT2
#define PWMA_RunInactiveNoOutput()      CLR_REG_BIT(PWMA_BKR, PWMABRK_OSSR_MSK)
#define PWMA_RunInactiveOutput()        SET_REG_BIT(PWMA_BKR, PWMABRK_OSSR_MSK)
#define PWMA_IdleInactiveNoOutput()     CLR_REG_BIT(PWMA_BKR, PWMABRK_OSSI_MSK)
#define PWMA_IdleInactiveOutput()       SET_REG_BIT(PWMA_BKR, PWMABRK_OSSI_MSK)

#define HSPWMA_RunInactiveNoOutput()    CLR_HSPWMA_BIT(PWMA_BKR, PWMABRK_OSSR_MSK)
#define HSPWMA_RunInactiveOutput()      SET_HSPWMA_BIT(PWMA_BKR, PWMABRK_OSSR_MSK)
#define HSPWMA_IdleInactiveNoOutput()   CLR_HSPWMA_BIT(PWMA_BKR, PWMABRK_OSSI_MSK)
#define HSPWMA_IdleInactiveOutput()     SET_HSPWMA_BIT(PWMA_BKR, PWMABRK_OSSI_MSK)

#define PWMABRK_LOCK_MSK                (BIT1 | BIT0)
#define PWMA_SetLockLevel(n)            MODIFY_REG(PWMA_BKR,  PWMABRK_LOCK_MSK, ((n) << 0))
#define PWMA_SetUnLock()                PWMA_SetLockLevel(0)

#define HSPWMA_SetLockLevel(n)          MODIFY_HSPWMA(PWMA_BKR,  PWMABRK_LOCK_MSK, ((n) << 0))
#define HSPWMA_SetUnLock()              HSPWMA_SetLockLevel(0)

#define PWMAOISR_OIS1_MSK               BIT0
#define PWMAOISR_OIS1N_MSK              BIT1
#define PWMAOISR_OIS2_MSK               BIT2
#define PWMAOISR_OIS2N_MSK              BIT3
#define PWMAOISR_OIS3_MSK               BIT4
#define PWMAOISR_OIS3N_MSK              BIT5
#define PWMAOISR_OIS4_MSK               BIT6
#define PWMAOISR_OIS4N_MSK              BIT7
#define PWMACR3_OIS5_MSK                BIT0
#define PWMACR3_OIS6_MSK                BIT2
#define PWMA_OC1PIdleLevelLow()         CLR_REG_BIT(PWMA_OISR, PWMAOISR_OIS1_MSK)
#define PWMA_OC1PIdleLevelHigh()        SET_REG_BIT(PWMA_OISR, PWMAOISR_OIS1_MSK)
#define PWMA_OC1NIdleLevelLow()         CLR_REG_BIT(PWMA_OISR, PWMAOISR_OIS1N_MSK)
#define PWMA_OC1NIdleLevelHigh()        SET_REG_BIT(PWMA_OISR, PWMAOISR_OIS1N_MSK)
#define PWMA_OC2PIdleLevelLow()         CLR_REG_BIT(PWMA_OISR, PWMAOISR_OIS2_MSK)
#define PWMA_OC2PIdleLevelHigh()        SET_REG_BIT(PWMA_OISR, PWMAOISR_OIS2_MSK)
#define PWMA_OC2NIdleLevelLow()         CLR_REG_BIT(PWMA_OISR, PWMAOISR_OIS2N_MSK)
#define PWMA_OC2NIdleLevelHigh()        SET_REG_BIT(PWMA_OISR, PWMAOISR_OIS2N_MSK)
#define PWMA_OC3PIdleLevelLow()         CLR_REG_BIT(PWMA_OISR, PWMAOISR_OIS3_MSK)
#define PWMA_OC3PIdleLevelHigh()        SET_REG_BIT(PWMA_OISR, PWMAOISR_OIS3_MSK)
#define PWMA_OC3NIdleLevelLow()         CLR_REG_BIT(PWMA_OISR, PWMAOISR_OIS3N_MSK)
#define PWMA_OC3NIdleLevelHigh()        SET_REG_BIT(PWMA_OISR, PWMAOISR_OIS3N_MSK)
#define PWMA_OC4PIdleLevelLow()         CLR_REG_BIT(PWMA_OISR, PWMAOISR_OIS4_MSK)
#define PWMA_OC4PIdleLevelHigh()        SET_REG_BIT(PWMA_OISR, PWMAOISR_OIS4_MSK)
#define PWMA_OC4NIdleLevelLow()         CLR_REG_BIT(PWMA_OISR, PWMAOISR_OIS4N_MSK)
#define PWMA_OC4NIdleLevelHigh()        SET_REG_BIT(PWMA_OISR, PWMAOISR_OIS4N_MSK)
#define PWMA_OC5PIdleLevelLow()         CLR_REG_BIT(PWMA_CR3, PWMACR3_OIS5_MSK)
#define PWMA_OC5PIdleLevelHigh()        SET_REG_BIT(PWMA_CR3, PWMACR3_OIS5_MSK)
#define PWMA_OC6PIdleLevelLow()         CLR_REG_BIT(PWMA_CR3, PWMACR3_OIS6_MSK)
#define PWMA_OC6PIdleLevelHigh()        SET_REG_BIT(PWMA_CR3, PWMACR3_OIS6_MSK)

#define HSPWMA_OC1PIdleLevelLow()       CLR_HSPWMA_BIT(PWMA_OISR, PWMAOISR_OIS1_MSK)
#define HSPWMA_OC1PIdleLevelHigh()      SET_HSPWMA_BIT(PWMA_OISR, PWMAOISR_OIS1_MSK)
#define HSPWMA_OC1NIdleLevelLow()       CLR_HSPWMA_BIT(PWMA_OISR, PWMAOISR_OIS1N_MSK)
#define HSPWMA_OC1NIdleLevelHigh()      SET_HSPWMA_BIT(PWMA_OISR, PWMAOISR_OIS1N_MSK)
#define HSPWMA_OC2PIdleLevelLow()       CLR_HSPWMA_BIT(PWMA_OISR, PWMAOISR_OIS2_MSK)
#define HSPWMA_OC2PIdleLevelHigh()      SET_HSPWMA_BIT(PWMA_OISR, PWMAOISR_OIS2_MSK)
#define HSPWMA_OC2NIdleLevelLow()       CLR_HSPWMA_BIT(PWMA_OISR, PWMAOISR_OIS2N_MSK)
#define HSPWMA_OC2NIdleLevelHigh()      SET_HSPWMA_BIT(PWMA_OISR, PWMAOISR_OIS2N_MSK)
#define HSPWMA_OC3PIdleLevelLow()       CLR_HSPWMA_BIT(PWMA_OISR, PWMAOISR_OIS3_MSK)
#define HSPWMA_OC3PIdleLevelHigh()      SET_HSPWMA_BIT(PWMA_OISR, PWMAOISR_OIS3_MSK)
#define HSPWMA_OC3NIdleLevelLow()       CLR_HSPWMA_BIT(PWMA_OISR, PWMAOISR_OIS3N_MSK)
#define HSPWMA_OC3NIdleLevelHigh()      SET_HSPWMA_BIT(PWMA_OISR, PWMAOISR_OIS3N_MSK)
#define HSPWMA_OC4PIdleLevelLow()       CLR_HSPWMA_BIT(PWMA_OISR, PWMAOISR_OIS4_MSK)
#define HSPWMA_OC4PIdleLevelHigh()      SET_HSPWMA_BIT(PWMA_OISR, PWMAOISR_OIS4_MSK)
#define HSPWMA_OC4NIdleLevelLow()       CLR_HSPWMA_BIT(PWMA_OISR, PWMAOISR_OIS4N_MSK)
#define HSPWMA_OC4NIdleLevelHigh()      SET_HSPWMA_BIT(PWMA_OISR, PWMAOISR_OIS4N_MSK)
#define HSPWMA_OC5PIdleLevelLow()       CLR_HSPWMA_BIT(PWMA_CR3, PWMACR3_OIS5_MSK)
#define HSPWMA_OC5PIdleLevelHigh()      SET_HSPWMA_BIT(PWMA_CR3, PWMACR3_OIS5_MSK)
#define HSPWMA_OC6PIdleLevelLow()       CLR_HSPWMA_BIT(PWMA_CR3, PWMACR3_OIS6_MSK)
#define HSPWMA_OC6PIdleLevelHigh()      SET_HSPWMA_BIT(PWMA_CR3, PWMACR3_OIS6_MSK)

#define PWMA_SetCounter(n)              (PWMA_CNTRH = HIBYTE(n), PWMA_CNTRL = LOBYTE(n))
#define PWMA_SetClockDivider(n)         (PWMA_PSCRH = HIBYTE(n), PWMA_PSCRL = LOBYTE(n))
#define PWMA_SetReload16(n)             (PWMA_ARRH = HIBYTE(n), PWMA_ARRL = LOBYTE(n))
#define PWMA_SetRepeatCounter(n)        (PWMA_RCRH = HIBYTE(n), PWMA_RCR = LOBYTE(n))

#define HSPWMA_SetCounter(n)            (WRITE_HSPWMA(PWMA_CNTRH, HIBYTE(n)), WRITE_HSPWMA(PWMA_CNTRL, LOBYTE(n)))
#define HSPWMA_SetClockDivider(n)       (WRITE_HSPWMA(PWMA_PSCRH, HIBYTE(n)), WRITE_HSPWMA(PWMA_PSCRL, LOBYTE(n)))
#define HSPWMA_SetReload16(n)           (WRITE_HSPWMA(PWMA_ARRH, HIBYTE(n)), WRITE_HSPWMA(PWMA_ARRL, LOBYTE(n)))
#define HSPWMA_SetRepeatCounter(n)      (WRITE_HSPWMA(PWMA_RCRH, HIBYTE(n)), WRITE_HSPWMA(PWMA_RCR, LOBYTE(n)))

#define PWMA_SetCCR1Value(n)            (PWMA_CCR1H = HIBYTE(n), PWMA_CCR1L = LOBYTE(n))
#define PWMA_SetCCR2Value(n)            (PWMA_CCR2H = HIBYTE(n), PWMA_CCR2L = LOBYTE(n))
#define PWMA_SetCCR3Value(n)            (PWMA_CCR3H = HIBYTE(n), PWMA_CCR3L = LOBYTE(n))
#define PWMA_SetCCR4Value(n)            (PWMA_CCR4H = HIBYTE(n), PWMA_CCR4L = LOBYTE(n))
#define PWMA_SetCCR5Value(n)            (PWMA_CCR5H = HIBYTE(n), PWMA_CCR5L = LOBYTE(n))
#define PWMA_SetCCR6Value(n)            (PWMA_CCR6H = HIBYTE(n), PWMA_CCR6L = LOBYTE(n))

#define HSPWMA_SetCCR1Value(n)          (WRITE_HSPWMA(PWMA_CCR1H, HIBYTE(n)), WRITE_HSPWMA(PWMA_CCR1L, LOBYTE(n)))
#define HSPWMA_SetCCR2Value(n)          (WRITE_HSPWMA(PWMA_CCR2H, HIBYTE(n)), WRITE_HSPWMA(PWMA_CCR2L, LOBYTE(n)))
#define HSPWMA_SetCCR3Value(n)          (WRITE_HSPWMA(PWMA_CCR3H, HIBYTE(n)), WRITE_HSPWMA(PWMA_CCR3L, LOBYTE(n)))
#define HSPWMA_SetCCR4Value(n)          (WRITE_HSPWMA(PWMA_CCR4H, HIBYTE(n)), WRITE_HSPWMA(PWMA_CCR4L, LOBYTE(n)))
#define HSPWMA_SetCCR5Value(n)          (WRITE_HSPWMA(PWMA_CCR5H, HIBYTE(n)), WRITE_HSPWMA(PWMA_CCR5L, LOBYTE(n)))
#define HSPWMA_SetCCR6Value(n)          (WRITE_HSPWMA(PWMA_CCR6H, HIBYTE(n)), WRITE_HSPWMA(PWMA_CCR6L, LOBYTE(n)))

#define PWMA_ReadReload16()             MAKEWORD(PWMA_ARRL, PWMA_ARRH)

#define HSPWMA_ReadReload16()           MAKEWORD(READ_HSPWMA(PWMA_ARRL), READ_HSPWMA(PWMA_ARRH))

#define PWMA_ReadCCR1Value()            MAKEWORD(PWMA_CCR1L, PWMA_CCR1H)
#define PWMA_ReadCCR2Value()            MAKEWORD(PWMA_CCR2L, PWMA_CCR2H)
#define PWMA_ReadCCR3Value()            MAKEWORD(PWMA_CCR3L, PWMA_CCR3H)
#define PWMA_ReadCCR4Value()            MAKEWORD(PWMA_CCR4L, PWMA_CCR4H)
#define PWMA_ReadCCR5Value()            MAKEWORD(PWMA_CCR5L, PWMA_CCR5H)
#define PWMA_ReadCCR6Value()            MAKEWORD(PWMA_CCR6L, PWMA_CCR6H)

#define HSPWMA_ReadCCR1Value()          MAKEWORD(READ_HSPWMA(PWMA_CCR1L), READ_HSPWMA(PWMA_CCR1H))
#define HSPWMA_ReadCCR2Value()          MAKEWORD(READ_HSPWMA(PWMA_CCR2L), READ_HSPWMA(PWMA_CCR2H))
#define HSPWMA_ReadCCR3Value()          MAKEWORD(READ_HSPWMA(PWMA_CCR3L), READ_HSPWMA(PWMA_CCR3H))
#define HSPWMA_ReadCCR4Value()          MAKEWORD(READ_HSPWMA(PWMA_CCR4L), READ_HSPWMA(PWMA_CCR4H))
#define HSPWMA_ReadCCR5Value()          MAKEWORD(READ_HSPWMA(PWMA_CCR5L), READ_HSPWMA(PWMA_CCR5H))
#define HSPWMA_ReadCCR6Value()          MAKEWORD(READ_HSPWMA(PWMA_CCR6L), READ_HSPWMA(PWMA_CCR6H))

#define PWMA_SetDeadTime(n)             PWMA_DTR = LOBYTE(n)

#define HSPWMA_SetDeadTime(n)           WRITE_HSPWMA(PWMA_DTR, LOBYTE(n))

#define PWMACCR5X_GC5C3_MSK             BIT7
#define PWMACCR5X_GC5C2_MSK             BIT6
#define PWMACCR5X_GC5C1_MSK             BIT5
#define PWMA_OC3REFCIndependent()       CLR_REG_BIT(PWMA_CCR5X, PWMACCR5X_GC5C3_MSK)
#define PWMA_OC2REFCIndependent()       CLR_REG_BIT(PWMA_CCR5X, PWMACCR5X_GC5C2_MSK)
#define PWMA_OC1REFCIndependent()       CLR_REG_BIT(PWMA_CCR5X, PWMACCR5X_GC5C1_MSK)
#define PWMA_OC3REFCAndWithOC5REF()     SET_REG_BIT(PWMA_CCR5X, PWMACCR5X_GC5C3_MSK)
#define PWMA_OC2REFCAndWithOC5REF()     SET_REG_BIT(PWMA_CCR5X, PWMACCR5X_GC5C2_MSK)
#define PWMA_OC1REFCAndWithOC5REF()     SET_REG_BIT(PWMA_CCR5X, PWMACCR5X_GC5C1_MSK)

#define HSPWMA_OC3REFCIndependent()     CLR_HSPWMA_BIT(PWMA_CCR5X, PWMACCR5X_GC5C3_MSK)
#define HSPWMA_OC2REFCIndependent()     CLR_HSPWMA_BIT(PWMA_CCR5X, PWMACCR5X_GC5C2_MSK)
#define HSPWMA_OC1REFCIndependent()     CLR_HSPWMA_BIT(PWMA_CCR5X, PWMACCR5X_GC5C1_MSK)
#define HSPWMA_OC3REFCAndWithOC5REF()   SET_HSPWMA_BIT(PWMA_CCR5X, PWMACCR5X_GC5C3_MSK)
#define HSPWMA_OC2REFCAndWithOC5REF()   SET_HSPWMA_BIT(PWMA_CCR5X, PWMACCR5X_GC5C2_MSK)
#define HSPWMA_OC1REFCAndWithOC5REF()   SET_HSPWMA_BIT(PWMA_CCR5X, PWMACCR5X_GC5C1_MSK)

////////////////////////

#define PWMADER_TDE_MSK                 BIT6
#define PWMADER_COMDE_MSK               BIT5
#define PWMADER_CC4DE_MSK               BIT4
#define PWMADER_CC3DE_MSK               BIT3
#define PWMADER_CC2DE_MSK               BIT2
#define PWMADER_CC1DE_MSK               BIT1
#define PWMADER_UDE_MSK                 BIT0
#define PWMA_TriggerIntAsDMAEvent()     SET_REG_BIT(PWMA_DER, PWMADER_TDE_MSK)
#define PWMA_COMIntAsDMAEvent()         SET_REG_BIT(PWMA_DER, PWMADER_COMDE_MSK)
#define PWMA_CC4IntAsDMAEvent()         SET_REG_BIT(PWMA_DER, PWMADER_CC4DE_MSK)
#define PWMA_CC3IntAsDMAEvent()         SET_REG_BIT(PWMA_DER, PWMADER_CC3DE_MSK)
#define PWMA_CC2IntAsDMAEvent()         SET_REG_BIT(PWMA_DER, PWMADER_CC2DE_MSK)
#define PWMA_CC1IntAsDMAEvent()         SET_REG_BIT(PWMA_DER, PWMADER_CC1DE_MSK)
#define PWMA_UpdateIntAsDMAEvent()      SET_REG_BIT(PWMA_DER, PWMADER_UDE_MSK)

#define HSPWMA_TriggerIntAsDMAEvent()   SET_HSPWMA_BIT(PWMA_DER, PWMADER_TDE_MSK)
#define HSPWMA_COMIntAsDMAEvent()       SET_HSPWMA_BIT(PWMA_DER, PWMADER_COMDE_MSK)
#define HSPWMA_CC4IntAsDMAEvent()       SET_HSPWMA_BIT(PWMA_DER, PWMADER_CC4DE_MSK)
#define HSPWMA_CC3IntAsDMAEvent()       SET_HSPWMA_BIT(PWMA_DER, PWMADER_CC3DE_MSK)
#define HSPWMA_CC2IntAsDMAEvent()       SET_HSPWMA_BIT(PWMA_DER, PWMADER_CC2DE_MSK)
#define HSPWMA_CC1IntAsDMAEvent()       SET_HSPWMA_BIT(PWMA_DER, PWMADER_CC1DE_MSK)
#define HSPWMA_UpdateIntAsDMAEvent()    SET_HSPWMA_BIT(PWMA_DER, PWMADER_UDE_MSK)

#define PWMADBA_DBA_MSK                 (BIT4 | BIT_LN)
#define PWMA_SetDMABaseAddress(d)       MODIFY_REG(PWMA_DBA,  PWMADBA_DBA_MSK, ((d) << 0))

#define HSPWMA_SetDMABaseAddress(d)     MODIFY_HSPWMA(PWMA_DBA,  PWMADBA_DBA_MSK, ((d) << 0))

#define PWMADBL_DBL_MSK                 (BIT4 | BIT_LN)
#define PWMA_SetDMABurstCount(d)        MODIFY_REG(PWMA_DBL,  PWMADBL_DBL_MSK, ((d) << 0))

#define HSPWMA_SetDMABurstCount(d)      MODIFY_HSPWMA(PWMA_DBL,  PWMADBL_DBL_MSK, ((d) << 0))

#define PWMADMACR_SIZE_MSK              (BIT1 | BIT0)
#define PWMA_SetDMABurstBytes(n)        MODIFY_REG(PWMA_DMACR,  PWMADMACR_SIZE_MSK, ((n) << 0))
#define PWMA_SetDMABurst1Byte()         PWMA_SetDMABurstBytes(0)
#define PWMA_SetDMABurst2Bytes()        PWMA_SetDMABurstBytes(1)
#define PWMA_SetDMABurst3Bytes()        PWMA_SetDMABurstBytes(2)
#define PWMA_SetDMABurst4Bytes()        PWMA_SetDMABurstBytes(3)

#define HSPWMA_SetDMABurstBytes(n)      MODIFY_HSPWMA(PWMA_DMACR,  PWMADMACR_SIZE_MSK, ((n) << 0))
#define HSPWMA_SetDMABurst1Byte()       HSPWMA_SetDMABurstBytes(0)
#define HSPWMA_SetDMABurst2Bytes()      HSPWMA_SetDMABurstBytes(1)
#define HSPWMA_SetDMABurst3Bytes()      HSPWMA_SetDMABurstBytes(2)
#define HSPWMA_SetDMABurst4Bytes()      HSPWMA_SetDMABurstBytes(3)

#define PWMADMACR_DSKIP_MSK             BIT4
#define PWMA_DMASkipSpace()             SET_REG_BIT(PWMA_DMACR, PWMADMACR_DSKIP_MSK)
#define PWMA_DMANeverSkipSpace()        CLR_REG_BIT(PWMA_DMACR, PWMADMACR_DSKIP_MSK)

#define HSPWMA_DMASkipSpace()           SET_HSPWMA_BIT(PWMA_DMACR, PWMADMACR_DSKIP_MSK)
#define HSPWMA_DMANeverSkipSpace()      CLR_HSPWMA_BIT(PWMA_DMACR, PWMADMACR_DSKIP_MSK)

#define PWMADMACR_DDIR_MSK              BIT3
#define PWMA_SetDMAOutput()             CLR_REG_BIT(PWMA_DMACR, PWMADMACR_DDIR_MSK)
#define PWMA_SetDMAInput()              SET_REG_BIT(PWMA_DMACR, PWMADMACR_DDIR_MSK)

#define HSPWMA_SetDMAOutput()           CLR_HSPWMA_BIT(PWMA_DMACR, PWMADMACR_DDIR_MSK)
#define HSPWMA_SetDMAInput()            SET_HSPWMA_BIT(PWMA_DMACR, PWMADMACR_DDIR_MSK)

#define PWMADMACR_DMAEN_MSK             BIT2
#define PWMA_EnableDMA()                SET_REG_BIT(PWMA_DMACR, PWMADMACR_DMAEN_MSK)
#define PWMA_DisableDMA()               CLR_REG_BIT(PWMA_DMACR, PWMADMACR_DMAEN_MSK)

#define HSPWMA_EnableDMA()              SET_HSPWMA_BIT(PWMA_DMACR, PWMADMACR_DMAEN_MSK)
#define HSPWMA_DisableDMA()             CLR_HSPWMA_BIT(PWMA_DMACR, PWMADMACR_DMAEN_MSK)

////////////////////////

#define PWMBENO_ENO5P_MSK               BIT0
#define PWMBENO_ENO6P_MSK               BIT2
#define PWMBENO_ENO7P_MSK               BIT4
#define PWMBENO_ENO8P_MSK               BIT6
#define PWMB_EnablePWM5POutput()        SET_REG_BIT(PWMB_ENO, PWMBENO_ENO5P_MSK)
#define PWMB_DisablePWM5POutput()       CLR_REG_BIT(PWMB_ENO, PWMBENO_ENO5P_MSK)
#define PWMB_EnablePWM6POutput()        SET_REG_BIT(PWMB_ENO, PWMBENO_ENO6P_MSK)
#define PWMB_DisablePWM6POutput()       CLR_REG_BIT(PWMB_ENO, PWMBENO_ENO6P_MSK)
#define PWMB_EnablePWM7POutput()        SET_REG_BIT(PWMB_ENO, PWMBENO_ENO7P_MSK)
#define PWMB_DisablePWM7POutput()       CLR_REG_BIT(PWMB_ENO, PWMBENO_ENO7P_MSK)
#define PWMB_EnablePWM8POutput()        SET_REG_BIT(PWMB_ENO, PWMBENO_ENO8P_MSK)
#define PWMB_DisablePWM8POutput()       CLR_REG_BIT(PWMB_ENO, PWMBENO_ENO8P_MSK)

#define HSPWMB_EnablePWM5POutput()      SET_HSPWMB_BIT(PWMB_ENO, PWMBENO_ENO5P_MSK)
#define HSPWMB_DisablePWM5POutput()     CLR_HSPWMB_BIT(PWMB_ENO, PWMBENO_ENO5P_MSK)
#define HSPWMB_EnablePWM6POutput()      SET_HSPWMB_BIT(PWMB_ENO, PWMBENO_ENO6P_MSK)
#define HSPWMB_DisablePWM6POutput()     CLR_HSPWMB_BIT(PWMB_ENO, PWMBENO_ENO6P_MSK)
#define HSPWMB_EnablePWM7POutput()      SET_HSPWMB_BIT(PWMB_ENO, PWMBENO_ENO7P_MSK)
#define HSPWMB_DisablePWM7POutput()     CLR_HSPWMB_BIT(PWMB_ENO, PWMBENO_ENO7P_MSK)
#define HSPWMB_EnablePWM8POutput()      SET_HSPWMB_BIT(PWMB_ENO, PWMBENO_ENO8P_MSK)
#define HSPWMB_DisablePWM8POutput()     CLR_HSPWMB_BIT(PWMB_ENO, PWMBENO_ENO8P_MSK)

#define PWMBIOAUX_AUX5P_MSK             BIT0
#define PWMBIOAUX_AUX6P_MSK             BIT2
#define PWMBIOAUX_AUX7P_MSK             BIT4
#define PWMBIOAUX_AUX8P_MSK             BIT6
#define PWMB_EnoCtrlPWM5P()             CLR_REG_BIT(PWMB_IOAUX, PWMBIOAUX_AUX5P_MSK)
#define PWMB_EnoBrkCtrlPWM5P()          SET_REG_BIT(PWMB_IOAUX, PWMBIOAUX_AUX5P_MSK)
#define PWMB_EnoCtrlPWM6P()             CLR_REG_BIT(PWMB_IOAUX, PWMBIOAUX_AUX6P_MSK)
#define PWMB_EnoBrkCtrlPWM6P()          SET_REG_BIT(PWMB_IOAUX, PWMBIOAUX_AUX6P_MSK)
#define PWMB_EnoCtrlPWM7P()             CLR_REG_BIT(PWMB_IOAUX, PWMBIOAUX_AUX7P_MSK)
#define PWMB_EnoBrkCtrlPWM7P()          SET_REG_BIT(PWMB_IOAUX, PWMBIOAUX_AUX7P_MSK)
#define PWMB_EnoCtrlPWM8P()             CLR_REG_BIT(PWMB_IOAUX, PWMBIOAUX_AUX8P_MSK)
#define PWMB_EnoBrkCtrlPWM8P()          SET_REG_BIT(PWMB_IOAUX, PWMBIOAUX_AUX8P_MSK)

#define HSPWMB_EnoCtrlPWM5P()           CLR_HSPWMB_BIT(PWMB_IOAUX, PWMBIOAUX_AUX5P_MSK)
#define HSPWMB_EnoBrkCtrlPWM5P()        SET_HSPWMB_BIT(PWMB_IOAUX, PWMBIOAUX_AUX5P_MSK)
#define HSPWMB_EnoCtrlPWM6P()           CLR_HSPWMB_BIT(PWMB_IOAUX, PWMBIOAUX_AUX6P_MSK)
#define HSPWMB_EnoBrkCtrlPWM6P()        SET_HSPWMB_BIT(PWMB_IOAUX, PWMBIOAUX_AUX6P_MSK)
#define HSPWMB_EnoCtrlPWM7P()           CLR_HSPWMB_BIT(PWMB_IOAUX, PWMBIOAUX_AUX7P_MSK)
#define HSPWMB_EnoBrkCtrlPWM7P()        SET_HSPWMB_BIT(PWMB_IOAUX, PWMBIOAUX_AUX7P_MSK)
#define HSPWMB_EnoCtrlPWM8P()           CLR_HSPWMB_BIT(PWMB_IOAUX, PWMBIOAUX_AUX8P_MSK)
#define HSPWMB_EnoBrkCtrlPWM8P()        SET_HSPWMB_BIT(PWMB_IOAUX, PWMBIOAUX_AUX8P_MSK)

#define PWMBCR1_ARPE_MSK                BIT7
#define PWMB_UnbufferARR()              CLR_REG_BIT(PWMB_CR1, PWMBCR1_ARPE_MSK)
#define PWMB_BufferARR()                SET_REG_BIT(PWMB_CR1, PWMBCR1_ARPE_MSK)

#define HSPWMB_UnbufferARR()            CLR_HSPWMB_BIT(PWMB_CR1, PWMBCR1_ARPE_MSK)
#define HSPWMB_BufferARR()              SET_HSPWMB_BIT(PWMB_CR1, PWMBCR1_ARPE_MSK)

#define PWMBCR1_CMS_MSK                 (BIT6 | BIT5)
#define PWMB_SetAlignMode(n)            MODIFY_REG(PWMB_CR1,  PWMBCR1_CMS_MSK, ((n) << 5))
#define PWMB_EdgeAlignMode()            PWMB_SetAlignMode(0)
#define PWMB_CenterAlignMode1()         PWMB_SetAlignMode(1)
#define PWMB_CenterAlignMode2()         PWMB_SetAlignMode(2)
#define PWMB_CenterAlignMode3()         PWMB_SetAlignMode(3)

#define HSPWMB_SetAlignMode(n)          MODIFY_HSPWMB(PWMB_CR1,  PWMBCR1_CMS_MSK, ((n) << 5))
#define HSPWMB_EdgeAlignMode()          HSPWMB_SetAlignMode(0)
#define HSPWMB_CenterAlignMode1()       HSPWMB_SetAlignMode(1)
#define HSPWMB_CenterAlignMode2()       HSPWMB_SetAlignMode(2)
#define HSPWMB_CenterAlignMode3()       HSPWMB_SetAlignMode(3)

#define PWMBCR1_DIR_MSK                 BIT4
#define PWMB_UpCounter()                CLR_REG_BIT(PWMB_CR1, PWMBCR1_DIR_MSK)
#define PWMB_DownCounter()              SET_REG_BIT(PWMB_CR1, PWMBCR1_DIR_MSK)

#define HSPWMB_UpCounter()              CLR_HSPWMB_BIT(PWMB_CR1, PWMBCR1_DIR_MSK)
#define HSPWMB_DownCounter()            SET_HSPWMB_BIT(PWMB_CR1, PWMBCR1_DIR_MSK)

#define PWMBCR1_OPM_MSK                 BIT3
#define PWMB_ContinueMode()             CLR_REG_BIT(PWMB_CR1, PWMBCR1_OPM_MSK)
#define PWMB_OnePulseMode()             SET_REG_BIT(PWMB_CR1, PWMBCR1_OPM_MSK)

#define HSPWMB_ContinueMode()           CLR_HSPWMB_BIT(PWMB_CR1, PWMBCR1_OPM_MSK)
#define HSPWMB_OnePulseMode()           SET_HSPWMB_BIT(PWMB_CR1, PWMBCR1_OPM_MSK)

#define PWMBCR1_URS_MSK                 BIT2
#define PWMB_UpdateRequestMode1()       SET_REG_BIT(PWMB_CR1, PWMBCR1_URS_MSK)
#define PWMB_UpdateRequestMode2()       CLR_REG_BIT(PWMB_CR1, PWMBCR1_URS_MSK)

#define HSPWMB_UpdateRequestMode1()     SET_HSPWMB_BIT(PWMB_CR1, PWMBCR1_URS_MSK)
#define HSPWMB_UpdateRequestMode2()     CLR_HSPWMB_BIT(PWMB_CR1, PWMBCR1_URS_MSK)

#define PWMBCR1_UDIS_MSK                BIT1
#define PWMB_EnableUpdate()             CLR_REG_BIT(PWMB_CR1, PWMBCR1_UDIS_MSK)
#define PWMB_DisableUpdate()            SET_REG_BIT(PWMB_CR1, PWMBCR1_UDIS_MSK)

#define HSPWMB_EnableUpdate()           CLR_HSPWMB_BIT(PWMB_CR1, PWMBCR1_UDIS_MSK)
#define HSPWMB_DisableUpdate()          SET_HSPWMB_BIT(PWMB_CR1, PWMBCR1_UDIS_MSK)

#define PWMBCR1_CEN_MSK                 BIT0
#define PWMB_Run()                      SET_REG_BIT(PWMB_CR1, PWMBCR1_CEN_MSK)
#define PWMB_Stop()                     CLR_REG_BIT(PWMB_CR1, PWMBCR1_CEN_MSK)

#define HSPWMB_Run()                    SET_HSPWMB_BIT(PWMB_CR1, PWMBCR1_CEN_MSK)
#define HSPWMB_Stop()                   CLR_HSPWMB_BIT(PWMB_CR1, PWMBCR1_CEN_MSK)

#define PWMBCR2_TIS_MSK                 BIT7
#define PWMB_PWM5PToTI()                CLR_REG_BIT(PWMB_CR2, PWMBCR2_TIS_MSK)
#define PWMB_Xor5P6P7PToTI()            SET_REG_BIT(PWMB_CR2, PWMBCR2_TIS_MSK)

#define HSPWMB_PWM5PToTI()              CLR_HSPWMB_BIT(PWMB_CR2, PWMBCR2_TIS_MSK)
#define HSPWMB_Xor5P6P7PToTI()          SET_HSPWMB_BIT(PWMB_CR2, PWMBCR2_TIS_MSK)

#define PWMBCR2_MMS_MSK                 (BIT6 | BIT5 | BIT4)
#define PWMB_SelectTRGO(n)              MODIFY_REG(PWMB_CR2,  PWMBCR2_MMS_MSK, ((n) << 4))
#define PWMB_ResetAsTRGO()              PWMB_SelectTRGO(0)
#define PWMB_EnableAsTRGO()             PWMB_SelectTRGO(1)
#define PWMB_UpdateAsTRGO()             PWMB_SelectTRGO(2)
#define PWMB_MatchAsTRGO()              PWMB_SelectTRGO(3)
#define PWMB_OC5REFAsTRGO()             PWMB_SelectTRGO(4)
#define PWMB_OC6REFAsTRGO()             PWMB_SelectTRGO(5)
#define PWMB_OC7REFAsTRGO()             PWMB_SelectTRGO(6)
#define PWMB_OC8REFAsTRGO()             PWMB_SelectTRGO(7)

#define HSPWMB_SelectTRGO(n)            MODIFY_HSPWMB(PWMB_CR2,  PWMBCR2_MMS_MSK, ((n) << 4))
#define HSPWMB_ResetAsTRGO()            HSPWMB_SelectTRGO(0)
#define HSPWMB_EnableAsTRGO()           HSPWMB_SelectTRGO(1)
#define HSPWMB_UpdateAsTRGO()           HSPWMB_SelectTRGO(2)
#define HSPWMB_MatchAsTRGO()            HSPWMB_SelectTRGO(3)
#define HSPWMB_OC5REFAsTRGO()           HSPWMB_SelectTRGO(4)
#define HSPWMB_OC6REFAsTRGO()           HSPWMB_SelectTRGO(5)
#define HSPWMB_OC7REFAsTRGO()           HSPWMB_SelectTRGO(6)
#define HSPWMB_OC8REFAsTRGO()           HSPWMB_SelectTRGO(7)

#define PWMBCR2_COMS_MSK                BIT2
#define PWMB_CCOCUpdateMode0()          CLR_REG_BIT(PWMB_CR2, PWMBCR2_COMS_MSK)
#define PWMB_CCOCUpdateMode1()          SET_REG_BIT(PWMB_CR2, PWMBCR2_COMS_MSK)

#define HSPWMB_CCOCUpdateMode0()        CLR_HSPWMB_BIT(PWMB_CR2, PWMBCR2_COMS_MSK)
#define HSPWMB_CCOCUpdateMode1()        SET_HSPWMB_BIT(PWMB_CR2, PWMBCR2_COMS_MSK)

#define PWMBCR2_CCPC_MSK                BIT0
#define PWMB_UnbufferCCOC()             CLR_REG_BIT(PWMB_CR2, PWMBCR2_CCPC_MSK)
#define PWMB_BufferCCOC()               SET_REG_BIT(PWMB_CR2, PWMBCR2_CCPC_MSK)

#define HSPWMB_UnbufferCCOC()           CLR_HSPWMB_BIT(PWMB_CR2, PWMBCR2_CCPC_MSK)
#define HSPWMB_BufferCCOC()             SET_HSPWMB_BIT(PWMB_CR2, PWMBCR2_CCPC_MSK)

#define PWMBSMCR_MSM_MSK                BIT7
#define PWMB_StandaloneMode()           CLR_REG_BIT(PWMB_SMCR, PWMBSMCR_MSM_MSK)
#define PWMB_MasterSlaveMode()          SET_REG_BIT(PWMB_SMCR, PWMBSMCR_MSM_MSK)

#define HSPWMB_StandaloneMode()         CLR_HSPWMB_BIT(PWMB_SMCR, PWMBSMCR_MSM_MSK)
#define HSPWMB_MasterSlaveMode()        SET_HSPWMB_BIT(PWMB_SMCR, PWMBSMCR_MSM_MSK)

#define PWMBSMCR_TS_MSK                 (BIT6 | BIT5 | BIT4)
#define PWMB_SelectTRGI(n)              MODIFY_REG(PWMB_SMCR,  PWMBSMCR_TS_MSK, ((n) << 4))
#define PWMB_DisableTRGI()              PWMB_SelectTRGI(0)
#define PWMB_TI5FEDAsTRGI()             PWMB_SelectTRGI(4)
#define PWMB_TI5FP5AsTRGI()             PWMB_SelectTRGI(5)
#define PWMB_TI6FP6AsTRGI()             PWMB_SelectTRGI(6)
#define PWMB_ETRFAsTRGI()               PWMB_SelectTRGI(7)

#define HSPWMB_SelectTRGI(n)            MODIFY_HSPWMB(PWMB_SMCR,  PWMBSMCR_TS_MSK, ((n) << 4))
#define HSPWMB_DisableTRGI()            HSPWMB_SelectTRGI(0)
#define HSPWMB_TI5FEDAsTRGI()           HSPWMB_SelectTRGI(4)
#define HSPWMB_TI5FP5AsTRGI()           HSPWMB_SelectTRGI(5)
#define HSPWMB_TI6FP6AsTRGI()           HSPWMB_SelectTRGI(6)
#define HSPWMB_ETRFAsTRGI()             HSPWMB_SelectTRGI(7)

#define PWMBSMCR_SMS_MSK                (BIT2 | BIT1 | BIT0)
#define PWMB_SetClockMode(n)            MODIFY_REG(PWMB_SMCR,  PWMBSMCR_SMS_MSK, ((n) << 0))
#define PWMB_InternalClockMode()        PWMB_SetClockMode(0)
#define PWMB_EncoderMode1()             PWMB_SetClockMode(1)
#define PWMB_EncoderMode2()             PWMB_SetClockMode(2)
#define PWMB_EncoderMode3()             PWMB_SetClockMode(3)
#define PWMB_TriggerResetMode()         PWMB_SetClockMode(4)
#define PWMB_TriggerGateMode()          PWMB_SetClockMode(5)
#define PWMB_TriggerStartMode()         PWMB_SetClockMode(6)
#define PWMB_ExternalClockMode()        PWMB_SetClockMode(7)

#define HSPWMB_SetClockMode(n)          MODIFY_HSPWMB(PWMB_SMCR,  PWMBSMCR_SMS_MSK, ((n) << 0))
#define HSPWMB_InternalClockMode()      HSPWMB_SetClockMode(0)
#define HSPWMB_EncoderMode1()           HSPWMB_SetClockMode(1)
#define HSPWMB_EncoderMode2()           HSPWMB_SetClockMode(2)
#define HSPWMB_EncoderMode3()           HSPWMB_SetClockMode(3)
#define HSPWMB_TriggerResetMode()       HSPWMB_SetClockMode(4)
#define HSPWMB_TriggerGateMode()        HSPWMB_SetClockMode(5)
#define HSPWMB_TriggerStartMode()       HSPWMB_SetClockMode(6)
#define HSPWMB_ExternalClockMode()      HSPWMB_SetClockMode(7)

#define PWMBETR_ETP_MSK                 BIT7
#define PWMB_ETRNonInverted()           CLR_REG_BIT(PWMB_ETR, PWMBETR_ETP_MSK)
#define PWMB_ETRInverted()              SET_REG_BIT(PWMB_ETR, PWMBETR_ETP_MSK)

#define HSPWMB_ETRNonInverted()         CLR_HSPWMB_BIT(PWMB_ETR, PWMBETR_ETP_MSK)
#define HSPWMB_ETRInverted()            SET_HSPWMB_BIT(PWMB_ETR, PWMBETR_ETP_MSK)

#define PWMBETR_ECE_MSK                 BIT6
#define PWMB_DisableExternalClock2()    CLR_REG_BIT(PWMB_ETR, PWMBETR_ECE_MSK)
#define PWMB_EnableExternalClock2()     SET_REG_BIT(PWMB_ETR, PWMBETR_ECE_MSK)

#define HSPWMB_DisableExternalClock2()  CLR_HSPWMB_BIT(PWMB_ETR, PWMBETR_ECE_MSK)
#define HSPWMB_EnableExternalClock2()   SET_HSPWMB_BIT(PWMB_ETR, PWMBETR_ECE_MSK)

#define PWMBETR_ETPS_MSK                (BIT5 | BIT4)
#define PWMB_SetETRDivider(n)           MODIFY_REG(PWMB_ETR,  PWMBETR_ETPS_MSK, ((n) << 4))
#define PWMB_ETRDivider1()              PWMB_SetETRDivider(0)
#define PWMB_ETRDivider2()              PWMB_SetETRDivider(1)
#define PWMB_ETRDivider4()              PWMB_SetETRDivider(2)
#define PWMB_ETRDivider8()              PWMB_SetETRDivider(3)

#define HSPWMB_SetETRDivider(n)         MODIFY_HSPWMB(PWMB_ETR,  PWMBETR_ETPS_MSK, ((n) << 4))
#define HSPWMB_ETRDivider1()            HSPWMB_SetETRDivider(0)
#define HSPWMB_ETRDivider2()            HSPWMB_SetETRDivider(1)
#define HSPWMB_ETRDivider4()            HSPWMB_SetETRDivider(2)
#define HSPWMB_ETRDivider8()            HSPWMB_SetETRDivider(3)

#define PWMBETR_ETF_MSK                 (BIT_LN)
#define PWMB_SetETRFilter(n)            MODIFY_REG(PWMB_ETR,  PWMBETR_ETF_MSK, ((n) << 0))
#define PWMB_ETRFilter1()               PWMB_SetETRFilter(0)
#define PWMB_ETRFilter2()               PWMB_SetETRFilter(1)
#define PWMB_ETRFilter4()               PWMB_SetETRFilter(2)
#define PWMB_ETRFilter8()               PWMB_SetETRFilter(3)
#define PWMB_ETRFilter12()              PWMB_SetETRFilter(4)
#define PWMB_ETRFilter16()              PWMB_SetETRFilter(5)
#define PWMB_ETRFilter24()              PWMB_SetETRFilter(6)
#define PWMB_ETRFilter32()              PWMB_SetETRFilter(7)
#define PWMB_ETRFilter48()              PWMB_SetETRFilter(8)
#define PWMB_ETRFilter64()              PWMB_SetETRFilter(9)
#define PWMB_ETRFilter80()              PWMB_SetETRFilter(10)
#define PWMB_ETRFilter96()              PWMB_SetETRFilter(11)
#define PWMB_ETRFilter128()             PWMB_SetETRFilter(12)
#define PWMB_ETRFilter160()             PWMB_SetETRFilter(13)
#define PWMB_ETRFilter192()             PWMB_SetETRFilter(14)
#define PWMB_ETRFilter256()             PWMB_SetETRFilter(15)

#define HSPWMB_SetETRFilter(n)          MODIFY_HSPWMB(PWMB_ETR,  PWMBETR_ETF_MSK, ((n) << 0))
#define HSPWMB_ETRFilter1()             HSPWMB_SetETRFilter(0)
#define HSPWMB_ETRFilter2()             HSPWMB_SetETRFilter(1)
#define HSPWMB_ETRFilter4()             HSPWMB_SetETRFilter(2)
#define HSPWMB_ETRFilter8()             HSPWMB_SetETRFilter(3)
#define HSPWMB_ETRFilter12()            HSPWMB_SetETRFilter(4)
#define HSPWMB_ETRFilter16()            HSPWMB_SetETRFilter(5)
#define HSPWMB_ETRFilter24()            HSPWMB_SetETRFilter(6)
#define HSPWMB_ETRFilter32()            HSPWMB_SetETRFilter(7)
#define HSPWMB_ETRFilter48()            HSPWMB_SetETRFilter(8)
#define HSPWMB_ETRFilter64()            HSPWMB_SetETRFilter(9)
#define HSPWMB_ETRFilter80()            HSPWMB_SetETRFilter(10)
#define HSPWMB_ETRFilter96()            HSPWMB_SetETRFilter(11)
#define HSPWMB_ETRFilter128()           HSPWMB_SetETRFilter(12)
#define HSPWMB_ETRFilter160()           HSPWMB_SetETRFilter(13)
#define HSPWMB_ETRFilter192()           HSPWMB_SetETRFilter(14)
#define HSPWMB_ETRFilter256()           HSPWMB_SetETRFilter(15)

#define PWMBEGR_BG_MSK                  BIT7
#define PWMBEGR_TG_MSK                  BIT6
#define PWMBEGR_COMG_MSK                BIT5
#define PWMBEGR_CC8G_MSK                BIT4
#define PWMBEGR_CC7G_MSK                BIT3
#define PWMBEGR_CC6G_MSK                BIT2
#define PWMBEGR_CC5G_MSK                BIT1
#define PWMBEGR_UG_MSK                  BIT0
#define PWMB_GenerateBreakEvent()       SET_REG_BIT(PWMB_EGR, PWMBEGR_BG_MSK)
#define PWMB_GenerateTriggerEvent()     SET_REG_BIT(PWMB_EGR, PWMBEGR_TG_MSK)
#define PWMB_GenerateCOMEvent()         SET_REG_BIT(PWMB_EGR, PWMBEGR_COMG_MSK)
#define PWMB_GenerateCC8Event()         SET_REG_BIT(PWMB_EGR, PWMBEGR_CC8G_MSK)
#define PWMB_GenerateCC7Event()         SET_REG_BIT(PWMB_EGR, PWMBEGR_CC7G_MSK)
#define PWMB_GenerateCC6Event()         SET_REG_BIT(PWMB_EGR, PWMBEGR_CC6G_MSK)
#define PWMB_GenerateCC5Event()         SET_REG_BIT(PWMB_EGR, PWMBEGR_CC5G_MSK)
#define PWMB_GenerateUpdateEvent()      SET_REG_BIT(PWMB_EGR, PWMBEGR_UG_MSK)

#define HSPWMB_GenerateBreakEvent()     SET_HSPWMB_BIT(PWMB_EGR, PWMBEGR_BG_MSK)
#define HSPWMB_GenerateTriggerEvent()   SET_HSPWMB_BIT(PWMB_EGR, PWMBEGR_TG_MSK)
#define HSPWMB_GenerateCOMEvent()       SET_HSPWMB_BIT(PWMB_EGR, PWMBEGR_COMG_MSK)
#define HSPWMB_GenerateCC8Event()       SET_HSPWMB_BIT(PWMB_EGR, PWMBEGR_CC8G_MSK)
#define HSPWMB_GenerateCC7Event()       SET_HSPWMB_BIT(PWMB_EGR, PWMBEGR_CC7G_MSK)
#define HSPWMB_GenerateCC6Event()       SET_HSPWMB_BIT(PWMB_EGR, PWMBEGR_CC6G_MSK)
#define HSPWMB_GenerateCC5Event()       SET_HSPWMB_BIT(PWMB_EGR, PWMBEGR_CC5G_MSK)
#define HSPWMB_GenerateUpdateEvent()    SET_HSPWMB_BIT(PWMB_EGR, PWMBEGR_UG_MSK)

#define PWMBCCMR1_OC5CE_MSK             BIT7
#define PWMB_EnableETRFClearOC5REF()    SET_REG_BIT(PWMB_CCMR1, PWMBCCMR1_OC5CE_MSK)
#define PWMB_DisableETRFClearOC5REF()   CLR_REG_BIT(PWMB_CCMR1, PWMBCCMR1_OC5CE_MSK)

#define HSPWMB_EnableETRFClearOC5REF()  SET_HSPWMB_BIT(PWMB_CCMR1, PWMBCCMR1_OC5CE_MSK)
#define HSPWMB_DisableETRFClearOC5REF() CLR_HSPWMB_BIT(PWMB_CCMR1, PWMBCCMR1_OC5CE_MSK)

#define PWMBCCMR1_OC5M_MSK              (BIT6 | BIT5 | BIT4)
#define PWMB_SetOC5OutputMode(n)        MODIFY_REG(PWMB_CCMR1,  PWMBCCMR1_OC5M_MSK, ((n) << 4))
#define PWMB_OC5REFFrozen()             PWMB_SetOC5OutputMode(0)
#define PWMB_OC5REFHighIfMatch()        PWMB_SetOC5OutputMode(1)
#define PWMB_OC5REFLowIfMatch()         PWMB_SetOC5OutputMode(2)
#define PWMB_OC5REFToggleIfMatch()      PWMB_SetOC5OutputMode(3)
#define PWMB_OC5REFForceLow()           PWMB_SetOC5OutputMode(4)
#define PWMB_OC5REFForceHigh()          PWMB_SetOC5OutputMode(5)
#define PWMB_OC5REFPWMMode1()           PWMB_SetOC5OutputMode(6)
#define PWMB_OC5REFPWMMode2()           PWMB_SetOC5OutputMode(7)

#define HSPWMB_SetOC5OutputMode(n)      MODIFY_HSPWMB(PWMB_CCMR1,  PWMBCCMR1_OC5M_MSK, ((n) << 4))
#define HSPWMB_OC5REFFrozen()           HSPWMB_SetOC5OutputMode(0)
#define HSPWMB_OC5REFHighIfMatch()      HSPWMB_SetOC5OutputMode(1)
#define HSPWMB_OC5REFLowIfMatch()       HSPWMB_SetOC5OutputMode(2)
#define HSPWMB_OC5REFToggleIfMatch()    HSPWMB_SetOC5OutputMode(3)
#define HSPWMB_OC5REFForceLow()         HSPWMB_SetOC5OutputMode(4)
#define HSPWMB_OC5REFForceHigh()        HSPWMB_SetOC5OutputMode(5)
#define HSPWMB_OC5REFPWMMode1()         HSPWMB_SetOC5OutputMode(6)
#define HSPWMB_OC5REFPWMMode2()         HSPWMB_SetOC5OutputMode(7)

#define PWMBCCMR1_OC5PE_MSK             BIT3
#define PWMB_UnbufferCCR5()             CLR_REG_BIT(PWMB_CCMR1, PWMBCCMR1_OC5PE_MSK)
#define PWMB_BufferCCR5()               SET_REG_BIT(PWMB_CCMR1, PWMBCCMR1_OC5PE_MSK)

#define HSPWMB_UnbufferCCR5()           CLR_HSPWMB_BIT(PWMB_CCMR1, PWMBCCMR1_OC5PE_MSK)
#define HSPWMB_BufferCCR5()             SET_HSPWMB_BIT(PWMB_CCMR1, PWMBCCMR1_OC5PE_MSK)

#define PWMBCCMR1_OC5FE_MSK             BIT2
#define PWMB_DisableOC5FastMode()       CLR_REG_BIT(PWMB_CCMR1, PWMBCCMR1_OC5FE_MSK)
#define PWMB_EnableOC5FastMode()        SET_REG_BIT(PWMB_CCMR1, PWMBCCMR1_OC5FE_MSK)

#define HSPWMB_DisableOC5FastMode()     CLR_HSPWMB_BIT(PWMB_CCMR1, PWMBCCMR1_OC5FE_MSK)
#define HSPWMB_EnableOC5FastMode()      SET_HSPWMB_BIT(PWMB_CCMR1, PWMBCCMR1_OC5FE_MSK)

#define PWMBCCMR1_CC5S_MSK              (BIT1 | BIT0)
#define PWMB_SetCC5Mode(n)              MODIFY_REG(PWMB_CCMR1,  PWMBCCMR1_CC5S_MSK, ((n) << 0))
#define PWMB_CC5Output()                PWMB_SetCC5Mode(0)
#define PWMB_CC5CaptureTI5FP5()         PWMB_SetCC5Mode(1)
#define PWMB_CC5CaptureTI6FP5()         PWMB_SetCC5Mode(2)
#define PWMB_CC5CaptureTRC()            PWMB_SetCC5Mode(3)

#define HSPWMB_SetCC5Mode(n)            MODIFY_HSPWMB(PWMB_CCMR1,  PWMBCCMR1_CC5S_MSK, ((n) << 0))
#define HSPWMB_CC5Output()              HSPWMB_SetCC5Mode(0)
#define HSPWMB_CC5CaptureTI5FP5()       HSPWMB_SetCC5Mode(1)
#define HSPWMB_CC5CaptureTI6FP5()       HSPWMB_SetCC5Mode(2)
#define HSPWMB_CC5CaptureTRC()          HSPWMB_SetCC5Mode(3)

#define PWMBCCMR1_IC5F_MSK              (BIT_HN)
#define PWMB_SetIC5Filter(n)            MODIFY_REG(PWMB_CCMR1,  PWMBCCMR1_IC5F_MSK, ((n) << 4))
#define PWMB_IC5Filter1()               PWMB_SetIC5Filter(0)
#define PWMB_IC5Filter2()               PWMB_SetIC5Filter(1)
#define PWMB_IC5Filter4()               PWMB_SetIC5Filter(2)
#define PWMB_IC5Filter8()               PWMB_SetIC5Filter(3)
#define PWMB_IC5Filter12()              PWMB_SetIC5Filter(4)
#define PWMB_IC5Filter16()              PWMB_SetIC5Filter(5)
#define PWMB_IC5Filter24()              PWMB_SetIC5Filter(6)
#define PWMB_IC5Filter32()              PWMB_SetIC5Filter(7)
#define PWMB_IC5Filter48()              PWMB_SetIC5Filter(8)
#define PWMB_IC5Filter64()              PWMB_SetIC5Filter(9)
#define PWMB_IC5Filter80()              PWMB_SetIC5Filter(10)
#define PWMB_IC5Filter96()              PWMB_SetIC5Filter(11)
#define PWMB_IC5Filter128()             PWMB_SetIC5Filter(12)
#define PWMB_IC5Filter160()             PWMB_SetIC5Filter(13)
#define PWMB_IC5Filter192()             PWMB_SetIC5Filter(14)
#define PWMB_IC5Filter256()             PWMB_SetIC5Filter(15)

#define HSPWMB_SetIC5Filter(n)          MODIFY_HSPWMB(PWMB_CCMR1,  PWMBCCMR1_IC5F_MSK, ((n) << 4))
#define HSPWMB_IC5Filter1()             HSPWMB_SetIC5Filter(0)
#define HSPWMB_IC5Filter2()             HSPWMB_SetIC5Filter(1)
#define HSPWMB_IC5Filter4()             HSPWMB_SetIC5Filter(2)
#define HSPWMB_IC5Filter8()             HSPWMB_SetIC5Filter(3)
#define HSPWMB_IC5Filter12()            HSPWMB_SetIC5Filter(4)
#define HSPWMB_IC5Filter16()            HSPWMB_SetIC5Filter(5)
#define HSPWMB_IC5Filter24()            HSPWMB_SetIC5Filter(6)
#define HSPWMB_IC5Filter32()            HSPWMB_SetIC5Filter(7)
#define HSPWMB_IC5Filter48()            HSPWMB_SetIC5Filter(8)
#define HSPWMB_IC5Filter64()            HSPWMB_SetIC5Filter(9)
#define HSPWMB_IC5Filter80()            HSPWMB_SetIC5Filter(10)
#define HSPWMB_IC5Filter96()            HSPWMB_SetIC5Filter(11)
#define HSPWMB_IC5Filter128()           HSPWMB_SetIC5Filter(12)
#define HSPWMB_IC5Filter160()           HSPWMB_SetIC5Filter(13)
#define HSPWMB_IC5Filter192()           HSPWMB_SetIC5Filter(14)
#define HSPWMB_IC5Filter256()           HSPWMB_SetIC5Filter(15)

#define PWMBCCMR1_IC5PS_MSK             (BIT3 | BIT2)
#define PWMB_SetIC5Divider(n)           MODIFY_REG(PWMB_CCMR1,  PWMBCCMR1_IC5PS_MSK, ((n) << 2))
#define PWMB_IC5Divider1()              PWMB_SetIC5Divider(0)
#define PWMB_IC5Divider2()              PWMB_SetIC5Divider(1)
#define PWMB_IC5Divider4()              PWMB_SetIC5Divider(2)
#define PWMB_IC5Divider8()              PWMB_SetIC5Divider(3)

#define HSPWMB_SetIC5Divider(n)         MODIFY_HSPWMB(PWMB_CCMR1,  PWMBCCMR1_IC5PS_MSK, ((n) << 2))
#define HSPWMB_IC5Divider1()            HSPWMB_SetIC5Divider(0)
#define HSPWMB_IC5Divider2()            HSPWMB_SetIC5Divider(1)
#define HSPWMB_IC5Divider4()            HSPWMB_SetIC5Divider(2)
#define HSPWMB_IC5Divider8()            HSPWMB_SetIC5Divider(3)

#define PWMBCCMR2_OC6CE_MSK             BIT7
#define PWMB_EnableETRFClearOC6REF()    SET_REG_BIT(PWMB_CCMR2, PWMBCCMR2_OC6CE_MSK)
#define PWMB_DisableETRFClearOC6REF()   CLR_REG_BIT(PWMB_CCMR2, PWMBCCMR2_OC6CE_MSK)

#define HSPWMB_EnableETRFClearOC6REF()  SET_HSPWMB_BIT(PWMB_CCMR2, PWMBCCMR2_OC6CE_MSK)
#define HSPWMB_DisableETRFClearOC6REF() CLR_HSPWMB_BIT(PWMB_CCMR2, PWMBCCMR2_OC6CE_MSK)

#define PWMBCCMR2_OC6M_MSK              (BIT6 | BIT5 | BIT4)
#define PWMB_SetOC6OutputMode(n)        MODIFY_REG(PWMB_CCMR2,  PWMBCCMR2_OC6M_MSK, ((n) << 4))
#define PWMB_OC6REFFrozen()             PWMB_SetOC6OutputMode(0)
#define PWMB_OC6REFHighIfMatch()        PWMB_SetOC6OutputMode(1)
#define PWMB_OC6REFLowIfMatch()         PWMB_SetOC6OutputMode(2)
#define PWMB_OC6REFToggleIfMatch()      PWMB_SetOC6OutputMode(3)
#define PWMB_OC6REFForceLow()           PWMB_SetOC6OutputMode(4)
#define PWMB_OC6REFForceHigh()          PWMB_SetOC6OutputMode(5)
#define PWMB_OC6REFPWMMode1()           PWMB_SetOC6OutputMode(6)
#define PWMB_OC6REFPWMMode2()           PWMB_SetOC6OutputMode(7)

#define HSPWMB_SetOC6OutputMode(n)      MODIFY_HSPWMB(PWMB_CCMR2,  PWMBCCMR2_OC6M_MSK, ((n) << 4))
#define HSPWMB_OC6REFFrozen()           HSPWMB_SetOC6OutputMode(0)
#define HSPWMB_OC6REFHighIfMatch()      HSPWMB_SetOC6OutputMode(1)
#define HSPWMB_OC6REFLowIfMatch()       HSPWMB_SetOC6OutputMode(2)
#define HSPWMB_OC6REFToggleIfMatch()    HSPWMB_SetOC6OutputMode(3)
#define HSPWMB_OC6REFForceLow()         HSPWMB_SetOC6OutputMode(4)
#define HSPWMB_OC6REFForceHigh()        HSPWMB_SetOC6OutputMode(5)
#define HSPWMB_OC6REFPWMMode1()         HSPWMB_SetOC6OutputMode(6)
#define HSPWMB_OC6REFPWMMode2()         HSPWMB_SetOC6OutputMode(7)

#define PWMBCCMR2_OC6PE_MSK             BIT3
#define PWMB_UnbufferCCR6()             CLR_REG_BIT(PWMB_CCMR2, PWMBCCMR2_OC6PE_MSK)
#define PWMB_BufferCCR6()               SET_REG_BIT(PWMB_CCMR2, PWMBCCMR2_OC6PE_MSK)

#define HSPWMB_UnbufferCCR6()           CLR_HSPWMB_BIT(PWMB_CCMR2, PWMBCCMR2_OC6PE_MSK)
#define HSPWMB_BufferCCR6()             SET_HSPWMB_BIT(PWMB_CCMR2, PWMBCCMR2_OC6PE_MSK)

#define PWMBCCMR2_OC6FE_MSK             BIT2
#define PWMB_DisableOC6FastMode()       CLR_REG_BIT(PWMB_CCMR2, PWMBCCMR2_OC6FE_MSK)
#define PWMB_EnableOC6FastMode()        SET_REG_BIT(PWMB_CCMR2, PWMBCCMR2_OC6FE_MSK)

#define HSPWMB_DisableOC6FastMode()     CLR_HSPWMB_BIT(PWMB_CCMR2, PWMBCCMR2_OC6FE_MSK)
#define HSPWMB_EnableOC6FastMode()      SET_HSPWMB_BIT(PWMB_CCMR2, PWMBCCMR2_OC6FE_MSK)

#define PWMBCCMR2_CC6S_MSK              (BIT1 | BIT0)
#define PWMB_SetCC6Mode(n)              MODIFY_REG(PWMB_CCMR2,  PWMBCCMR2_CC6S_MSK, ((n) << 0))
#define PWMB_CC6Output()                PWMB_SetCC6Mode(0)
#define PWMB_CC6CaptureTI6FP6()         PWMB_SetCC6Mode(1)
#define PWMB_CC6CaptureTI5FP6()         PWMB_SetCC6Mode(2)
#define PWMB_CC6CaptureTRC()            PWMB_SetCC6Mode(3)

#define HSPWMB_SetCC6Mode(n)            MODIFY_HSPWMB(PWMB_CCMR2,  PWMBCCMR2_CC6S_MSK, ((n) << 0))
#define HSPWMB_CC6Output()              HSPWMB_SetCC6Mode(0)
#define HSPWMB_CC6CaptureTI6FP6()       HSPWMB_SetCC6Mode(1)
#define HSPWMB_CC6CaptureTI5FP6()       HSPWMB_SetCC6Mode(2)
#define HSPWMB_CC6CaptureTRC()          HSPWMB_SetCC6Mode(3)

#define PWMBCCMR2_IC6F_MSK              (BIT_HN)
#define PWMB_SetIC6Filter(n)            MODIFY_REG(PWMB_CCMR2,  PWMBCCMR2_IC6F_MSK, ((n) << 4))
#define PWMB_IC6Filter1()               PWMB_SetIC6Filter(0)
#define PWMB_IC6Filter2()               PWMB_SetIC6Filter(1)
#define PWMB_IC6Filter4()               PWMB_SetIC6Filter(2)
#define PWMB_IC6Filter8()               PWMB_SetIC6Filter(3)
#define PWMB_IC6Filter12()              PWMB_SetIC6Filter(4)
#define PWMB_IC6Filter16()              PWMB_SetIC6Filter(5)
#define PWMB_IC6Filter24()              PWMB_SetIC6Filter(6)
#define PWMB_IC6Filter32()              PWMB_SetIC6Filter(7)
#define PWMB_IC6Filter48()              PWMB_SetIC6Filter(8)
#define PWMB_IC6Filter64()              PWMB_SetIC6Filter(9)
#define PWMB_IC6Filter80()              PWMB_SetIC6Filter(10)
#define PWMB_IC6Filter96()              PWMB_SetIC6Filter(11)
#define PWMB_IC6Filter128()             PWMB_SetIC6Filter(12)
#define PWMB_IC6Filter160()             PWMB_SetIC6Filter(13)
#define PWMB_IC6Filter192()             PWMB_SetIC6Filter(14)
#define PWMB_IC6Filter256()             PWMB_SetIC6Filter(15)

#define HSPWMB_SetIC6Filter(n)          MODIFY_HSPWMB(PWMB_CCMR2,  PWMBCCMR2_IC6F_MSK, ((n) << 4))
#define HSPWMB_IC6Filter1()             HSPWMB_SetIC6Filter(0)
#define HSPWMB_IC6Filter2()             HSPWMB_SetIC6Filter(1)
#define HSPWMB_IC6Filter4()             HSPWMB_SetIC6Filter(2)
#define HSPWMB_IC6Filter8()             HSPWMB_SetIC6Filter(3)
#define HSPWMB_IC6Filter12()            HSPWMB_SetIC6Filter(4)
#define HSPWMB_IC6Filter16()            HSPWMB_SetIC6Filter(5)
#define HSPWMB_IC6Filter24()            HSPWMB_SetIC6Filter(6)
#define HSPWMB_IC6Filter32()            HSPWMB_SetIC6Filter(7)
#define HSPWMB_IC6Filter48()            HSPWMB_SetIC6Filter(8)
#define HSPWMB_IC6Filter64()            HSPWMB_SetIC6Filter(9)
#define HSPWMB_IC6Filter80()            HSPWMB_SetIC6Filter(10)
#define HSPWMB_IC6Filter96()            HSPWMB_SetIC6Filter(11)
#define HSPWMB_IC6Filter128()           HSPWMB_SetIC6Filter(12)
#define HSPWMB_IC6Filter160()           HSPWMB_SetIC6Filter(13)
#define HSPWMB_IC6Filter192()           HSPWMB_SetIC6Filter(14)
#define HSPWMB_IC6Filter256()           HSPWMB_SetIC6Filter(15)

#define PWMBCCMR2_IC6PS_MSK             (BIT3 | BIT2)
#define PWMB_SetIC6Divider(n)           MODIFY_REG(PWMB_CCMR2,  PWMBCCMR2_IC6PS_MSK, ((n) << 2))
#define PWMB_IC6Divider1()              PWMB_SetIC6Divider(0)
#define PWMB_IC6Divider2()              PWMB_SetIC6Divider(1)
#define PWMB_IC6Divider4()              PWMB_SetIC6Divider(2)
#define PWMB_IC6Divider8()              PWMB_SetIC6Divider(3)

#define HSPWMB_SetIC6Divider(n)         MODIFY_HSPWMB(PWMB_CCMR2,  PWMBCCMR2_IC6PS_MSK, ((n) << 2))
#define HSPWMB_IC6Divider1()            HSPWMB_SetIC6Divider(0)
#define HSPWMB_IC6Divider2()            HSPWMB_SetIC6Divider(1)
#define HSPWMB_IC6Divider4()            HSPWMB_SetIC6Divider(2)
#define HSPWMB_IC6Divider8()            HSPWMB_SetIC6Divider(3)

#define PWMBCCMR3_OC7CE_MSK             BIT7
#define PWMB_EnableETRFClearOC7REF()    SET_REG_BIT(PWMB_CCMR3, PWMBCCMR3_OC7CE_MSK)
#define PWMB_DisableETRFClearOC7REF()   CLR_REG_BIT(PWMB_CCMR3, PWMBCCMR3_OC7CE_MSK)

#define HSPWMB_EnableETRFClearOC7REF()  SET_HSPWMB_BIT(PWMB_CCMR3, PWMBCCMR3_OC7CE_MSK)
#define HSPWMB_DisableETRFClearOC7REF() CLR_HSPWMB_BIT(PWMB_CCMR3, PWMBCCMR3_OC7CE_MSK)

#define PWMBCCMR3_OC7M_MSK              (BIT6 | BIT5 | BIT4)
#define PWMB_SetOC7OutputMode(n)        MODIFY_REG(PWMB_CCMR3,  PWMBCCMR3_OC7M_MSK, ((n) << 4))
#define PWMB_OC7REFFrozen()             PWMB_SetOC7OutputMode(0)
#define PWMB_OC7REFHighIfMatch()        PWMB_SetOC7OutputMode(1)
#define PWMB_OC7REFLowIfMatch()         PWMB_SetOC7OutputMode(2)
#define PWMB_OC7REFToggleIfMatch()      PWMB_SetOC7OutputMode(3)
#define PWMB_OC7REFForceLow()           PWMB_SetOC7OutputMode(4)
#define PWMB_OC7REFForceHigh()          PWMB_SetOC7OutputMode(5)
#define PWMB_OC7REFPWMMode1()           PWMB_SetOC7OutputMode(6)
#define PWMB_OC7REFPWMMode2()           PWMB_SetOC7OutputMode(7)

#define HSPWMB_SetOC7OutputMode(n)      MODIFY_HSPWMB(PWMB_CCMR3,  PWMBCCMR3_OC7M_MSK, ((n) << 4))
#define HSPWMB_OC7REFFrozen()           HSPWMB_SetOC7OutputMode(0)
#define HSPWMB_OC7REFHighIfMatch()      HSPWMB_SetOC7OutputMode(1)
#define HSPWMB_OC7REFLowIfMatch()       HSPWMB_SetOC7OutputMode(2)
#define HSPWMB_OC7REFToggleIfMatch()    HSPWMB_SetOC7OutputMode(3)
#define HSPWMB_OC7REFForceLow()         HSPWMB_SetOC7OutputMode(4)
#define HSPWMB_OC7REFForceHigh()        HSPWMB_SetOC7OutputMode(5)
#define HSPWMB_OC7REFPWMMode1()         HSPWMB_SetOC7OutputMode(6)
#define HSPWMB_OC7REFPWMMode2()         HSPWMB_SetOC7OutputMode(7)

#define PWMBCCMR3_OC7PE_MSK             BIT3
#define PWMB_UnbufferCCR7()             CLR_REG_BIT(PWMB_CCMR3, PWMBCCMR3_OC7PE_MSK)
#define PWMB_BufferCCR7()               SET_REG_BIT(PWMB_CCMR3, PWMBCCMR3_OC7PE_MSK)

#define HSPWMB_UnbufferCCR7()           CLR_HSPWMB_BIT(PWMB_CCMR3, PWMBCCMR3_OC7PE_MSK)
#define HSPWMB_BufferCCR7()             SET_HSPWMB_BIT(PWMB_CCMR3, PWMBCCMR3_OC7PE_MSK)

#define PWMBCCMR3_OC7FE_MSK             BIT2
#define PWMB_DisableOC7FastMode()       CLR_REG_BIT(PWMB_CCMR3, PWMBCCMR3_OC7FE_MSK)
#define PWMB_EnableOC7FastMode()        SET_REG_BIT(PWMB_CCMR3, PWMBCCMR3_OC7FE_MSK)

#define HSPWMB_DisableOC7FastMode()     CLR_HSPWMB_BIT(PWMB_CCMR3, PWMBCCMR3_OC7FE_MSK)
#define HSPWMB_EnableOC7FastMode()      SET_HSPWMB_BIT(PWMB_CCMR3, PWMBCCMR3_OC7FE_MSK)

#define PWMBCCMR3_CC7S_MSK              (BIT1 | BIT0)
#define PWMB_SetCC7Mode(n)              MODIFY_REG(PWMB_CCMR3,  PWMBCCMR3_CC7S_MSK, ((n) << 0))
#define PWMB_CC7Output()                PWMB_SetCC7Mode(0)
#define PWMB_CC7CaptureTI7FP7()         PWMB_SetCC7Mode(1)
#define PWMB_CC7CaptureTI8FP7()         PWMB_SetCC7Mode(2)
#define PWMB_CC7CaptureTRC()            PWMB_SetCC7Mode(3)

#define HSPWMB_SetCC7Mode(n)            MODIFY_HSPWMB(PWMB_CCMR3,  PWMBCCMR3_CC7S_MSK, ((n) << 0))
#define HSPWMB_CC7Output()              HSPWMB_SetCC7Mode(0)
#define HSPWMB_CC7CaptureTI7FP7()       HSPWMB_SetCC7Mode(1)
#define HSPWMB_CC7CaptureTI8FP7()       HSPWMB_SetCC7Mode(2)
#define HSPWMB_CC7CaptureTRC()          HSPWMB_SetCC7Mode(3)

#define PWMBCCMR3_IC7F_MSK              (BIT_HN)
#define PWMB_SetIC7Filter(n)            MODIFY_REG(PWMB_CCMR3,  PWMBCCMR3_IC7F_MSK, ((n) << 4))
#define PWMB_IC7Filter1()               PWMB_SetIC7Filter(0)
#define PWMB_IC7Filter2()               PWMB_SetIC7Filter(1)
#define PWMB_IC7Filter4()               PWMB_SetIC7Filter(2)
#define PWMB_IC7Filter8()               PWMB_SetIC7Filter(3)
#define PWMB_IC7Filter12()              PWMB_SetIC7Filter(4)
#define PWMB_IC7Filter16()              PWMB_SetIC7Filter(5)
#define PWMB_IC7Filter24()              PWMB_SetIC7Filter(6)
#define PWMB_IC7Filter32()              PWMB_SetIC7Filter(7)
#define PWMB_IC7Filter48()              PWMB_SetIC7Filter(8)
#define PWMB_IC7Filter64()              PWMB_SetIC7Filter(9)
#define PWMB_IC7Filter80()              PWMB_SetIC7Filter(10)
#define PWMB_IC7Filter96()              PWMB_SetIC7Filter(11)
#define PWMB_IC7Filter128()             PWMB_SetIC7Filter(12)
#define PWMB_IC7Filter160()             PWMB_SetIC7Filter(13)
#define PWMB_IC7Filter192()             PWMB_SetIC7Filter(14)
#define PWMB_IC7Filter256()             PWMB_SetIC7Filter(15)

#define HSPWMB_SetIC7Filter(n)          MODIFY_HSPWMB(PWMB_CCMR3,  PWMBCCMR3_IC7F_MSK, ((n) << 4))
#define HSPWMB_IC7Filter1()             HSPWMB_SetIC7Filter(0)
#define HSPWMB_IC7Filter2()             HSPWMB_SetIC7Filter(1)
#define HSPWMB_IC7Filter4()             HSPWMB_SetIC7Filter(2)
#define HSPWMB_IC7Filter8()             HSPWMB_SetIC7Filter(3)
#define HSPWMB_IC7Filter12()            HSPWMB_SetIC7Filter(4)
#define HSPWMB_IC7Filter16()            HSPWMB_SetIC7Filter(5)
#define HSPWMB_IC7Filter24()            HSPWMB_SetIC7Filter(6)
#define HSPWMB_IC7Filter32()            HSPWMB_SetIC7Filter(7)
#define HSPWMB_IC7Filter48()            HSPWMB_SetIC7Filter(8)
#define HSPWMB_IC7Filter64()            HSPWMB_SetIC7Filter(9)
#define HSPWMB_IC7Filter80()            HSPWMB_SetIC7Filter(10)
#define HSPWMB_IC7Filter96()            HSPWMB_SetIC7Filter(11)
#define HSPWMB_IC7Filter128()           HSPWMB_SetIC7Filter(12)
#define HSPWMB_IC7Filter160()           HSPWMB_SetIC7Filter(13)
#define HSPWMB_IC7Filter192()           HSPWMB_SetIC7Filter(14)
#define HSPWMB_IC7Filter256()           HSPWMB_SetIC7Filter(15)

#define PWMBCCMR3_IC7PS_MSK             (BIT3 | BIT2)
#define PWMB_SetIC7Divider(n)           MODIFY_REG(PWMB_CCMR3,  PWMBCCMR3_IC7PS_MSK, ((n) << 2))
#define PWMB_IC7Divider1()              PWMB_SetIC7Divider(0)
#define PWMB_IC7Divider2()              PWMB_SetIC7Divider(1)
#define PWMB_IC7Divider4()              PWMB_SetIC7Divider(2)
#define PWMB_IC7Divider8()              PWMB_SetIC7Divider(3)

#define HSPWMB_SetIC7Divider(n)         MODIFY_HSPWMB(PWMB_CCMR3,  PWMBCCMR3_IC7PS_MSK, ((n) << 2))
#define HSPWMB_IC7Divider1()            HSPWMB_SetIC7Divider(0)
#define HSPWMB_IC7Divider2()            HSPWMB_SetIC7Divider(1)
#define HSPWMB_IC7Divider4()            HSPWMB_SetIC7Divider(2)
#define HSPWMB_IC7Divider8()            HSPWMB_SetIC7Divider(3)

#define PWMBCCMR4_OC8CE_MSK             BIT7
#define PWMB_EnableETRFClearOC8REF()    SET_REG_BIT(PWMB_CCMR4, PWMBCCMR4_OC8CE_MSK)
#define PWMB_DisableETRFClearOC8REF()   CLR_REG_BIT(PWMB_CCMR4, PWMBCCMR4_OC8CE_MSK)

#define HSPWMB_EnableETRFClearOC8REF()  SET_HSPWMB_BIT(PWMB_CCMR4, PWMBCCMR4_OC8CE_MSK)
#define HSPWMB_DisableETRFClearOC8REF() CLR_HSPWMB_BIT(PWMB_CCMR4, PWMBCCMR4_OC8CE_MSK)

#define PWMBCCMR4_OC8M_MSK              (BIT6 | BIT5 | BIT4)
#define PWMB_SetOC8OutputMode(n)        MODIFY_REG(PWMB_CCMR4,  PWMBCCMR4_OC8M_MSK, ((n) << 4))
#define PWMB_OC8REFFrozen()             PWMB_SetOC8OutputMode(0)
#define PWMB_OC8REFHighIfMatch()        PWMB_SetOC8OutputMode(1)
#define PWMB_OC8REFLowIfMatch()         PWMB_SetOC8OutputMode(2)
#define PWMB_OC8REFToggleIfMatch()      PWMB_SetOC8OutputMode(3)
#define PWMB_OC8REFForceLow()           PWMB_SetOC8OutputMode(4)
#define PWMB_OC8REFForceHigh()          PWMB_SetOC8OutputMode(5)
#define PWMB_OC8REFPWMMode1()           PWMB_SetOC8OutputMode(6)
#define PWMB_OC8REFPWMMode2()           PWMB_SetOC8OutputMode(7)

#define HSPWMB_SetOC8OutputMode(n)      MODIFY_HSPWMB(PWMB_CCMR4,  PWMBCCMR4_OC8M_MSK, ((n) << 4))
#define HSPWMB_OC8REFFrozen()           HSPWMB_SetOC8OutputMode(0)
#define HSPWMB_OC8REFHighIfMatch()      HSPWMB_SetOC8OutputMode(1)
#define HSPWMB_OC8REFLowIfMatch()       HSPWMB_SetOC8OutputMode(2)
#define HSPWMB_OC8REFToggleIfMatch()    HSPWMB_SetOC8OutputMode(3)
#define HSPWMB_OC8REFForceLow()         HSPWMB_SetOC8OutputMode(4)
#define HSPWMB_OC8REFForceHigh()        HSPWMB_SetOC8OutputMode(5)
#define HSPWMB_OC8REFPWMMode1()         HSPWMB_SetOC8OutputMode(6)
#define HSPWMB_OC8REFPWMMode2()         HSPWMB_SetOC8OutputMode(7)

#define PWMBCCMR4_OC8PE_MSK             BIT3
#define PWMB_UnbufferCCR8()             CLR_REG_BIT(PWMB_CCMR4, PWMBCCMR4_OC8PE_MSK)
#define PWMB_BufferCCR8()               SET_REG_BIT(PWMB_CCMR4, PWMBCCMR4_OC8PE_MSK)

#define HSPWMB_UnbufferCCR8()           CLR_HSPWMB_BIT(PWMB_CCMR4, PWMBCCMR4_OC8PE_MSK)
#define HSPWMB_BufferCCR8()             SET_HSPWMB_BIT(PWMB_CCMR4, PWMBCCMR4_OC8PE_MSK)

#define PWMBCCMR4_OC8FE_MSK             BIT2
#define PWMB_DisableOC8FastMode()       CLR_REG_BIT(PWMB_CCMR4, PWMBCCMR4_OC8FE_MSK)
#define PWMB_EnableOC8FastMode()        SET_REG_BIT(PWMB_CCMR4, PWMBCCMR4_OC8FE_MSK)

#define HSPWMB_DisableOC8FastMode()     CLR_HSPWMB_BIT(PWMB_CCMR4, PWMBCCMR4_OC8FE_MSK)
#define HSPWMB_EnableOC8FastMode()      SET_HSPWMB_BIT(PWMB_CCMR4, PWMBCCMR4_OC8FE_MSK)

#define PWMBCCMR4_CC8S_MSK              (BIT1 | BIT0)
#define PWMB_SetCC8Mode(n)              MODIFY_REG(PWMB_CCMR4,  PWMBCCMR4_CC8S_MSK, ((n) << 0))
#define PWMB_CC8Output()                PWMB_SetCC8Mode(0)
#define PWMB_CC8CaptureTI8FP8()         PWMB_SetCC8Mode(1)
#define PWMB_CC8CaptureTI7FP8()         PWMB_SetCC8Mode(2)
#define PWMB_CC8CaptureTRC()            PWMB_SetCC8Mode(3)

#define HSPWMB_SetCC8Mode(n)            MODIFY_HSPWMB(PWMB_CCMR4,  PWMBCCMR4_CC8S_MSK, ((n) << 0))
#define HSPWMB_CC8Output()              HSPWMB_SetCC8Mode(0)
#define HSPWMB_CC8CaptureTI8FP8()       HSPWMB_SetCC8Mode(1)
#define HSPWMB_CC8CaptureTI7FP8()       HSPWMB_SetCC8Mode(2)
#define HSPWMB_CC8CaptureTRC()          HSPWMB_SetCC8Mode(3)

#define PWMBCCMR4_IC8F_MSK              (BIT_HN)
#define PWMB_SetIC8Filter(n)            MODIFY_REG(PWMB_CCMR4,  PWMBCCMR4_IC8F_MSK, ((n) << 4))
#define PWMB_IC8Filter1()               PWMB_SetIC8Filter(0)
#define PWMB_IC8Filter2()               PWMB_SetIC8Filter(1)
#define PWMB_IC8Filter4()               PWMB_SetIC8Filter(2)
#define PWMB_IC8Filter8()               PWMB_SetIC8Filter(3)
#define PWMB_IC8Filter12()              PWMB_SetIC8Filter(4)
#define PWMB_IC8Filter16()              PWMB_SetIC8Filter(5)
#define PWMB_IC8Filter24()              PWMB_SetIC8Filter(6)
#define PWMB_IC8Filter32()              PWMB_SetIC8Filter(7)
#define PWMB_IC8Filter48()              PWMB_SetIC8Filter(8)
#define PWMB_IC8Filter64()              PWMB_SetIC8Filter(9)
#define PWMB_IC8Filter80()              PWMB_SetIC8Filter(10)
#define PWMB_IC8Filter96()              PWMB_SetIC8Filter(11)
#define PWMB_IC8Filter128()             PWMB_SetIC8Filter(12)
#define PWMB_IC8Filter160()             PWMB_SetIC8Filter(13)
#define PWMB_IC8Filter192()             PWMB_SetIC8Filter(14)
#define PWMB_IC8Filter256()             PWMB_SetIC8Filter(15)

#define HSPWMB_SetIC8Filter(n)          MODIFY_HSPWMB(PWMB_CCMR4,  PWMBCCMR4_IC8F_MSK, ((n) << 4))
#define HSPWMB_IC8Filter1()             HSPWMB_SetIC8Filter(0)
#define HSPWMB_IC8Filter2()             HSPWMB_SetIC8Filter(1)
#define HSPWMB_IC8Filter4()             HSPWMB_SetIC8Filter(2)
#define HSPWMB_IC8Filter8()             HSPWMB_SetIC8Filter(3)
#define HSPWMB_IC8Filter12()            HSPWMB_SetIC8Filter(4)
#define HSPWMB_IC8Filter16()            HSPWMB_SetIC8Filter(5)
#define HSPWMB_IC8Filter24()            HSPWMB_SetIC8Filter(6)
#define HSPWMB_IC8Filter32()            HSPWMB_SetIC8Filter(7)
#define HSPWMB_IC8Filter48()            HSPWMB_SetIC8Filter(8)
#define HSPWMB_IC8Filter64()            HSPWMB_SetIC8Filter(9)
#define HSPWMB_IC8Filter80()            HSPWMB_SetIC8Filter(10)
#define HSPWMB_IC8Filter96()            HSPWMB_SetIC8Filter(11)
#define HSPWMB_IC8Filter128()           HSPWMB_SetIC8Filter(12)
#define HSPWMB_IC8Filter160()           HSPWMB_SetIC8Filter(13)
#define HSPWMB_IC8Filter192()           HSPWMB_SetIC8Filter(14)
#define HSPWMB_IC8Filter256()           HSPWMB_SetIC8Filter(15)

#define PWMBCCMR4_IC8PS_MSK             (BIT3 | BIT2)
#define PWMB_SetIC8Divider(n)           MODIFY_REG(PWMB_CCMR4,  PWMBCCMR4_IC8PS_MSK, ((n) << 2))
#define PWMB_IC8Divider1()              PWMB_SetIC8Divider(0)
#define PWMB_IC8Divider2()              PWMB_SetIC8Divider(1)
#define PWMB_IC8Divider4()              PWMB_SetIC8Divider(2)
#define PWMB_IC8Divider8()              PWMB_SetIC8Divider(3)

#define HSPWMB_SetIC8Divider(n)         MODIFY_HSPWMB(PWMB_CCMR4,  PWMBCCMR4_IC8PS_MSK, ((n) << 2))
#define HSPWMB_IC8Divider1()            HSPWMB_SetIC8Divider(0)
#define HSPWMB_IC8Divider2()            HSPWMB_SetIC8Divider(1)
#define HSPWMB_IC8Divider4()            HSPWMB_SetIC8Divider(2)
#define HSPWMB_IC8Divider8()            HSPWMB_SetIC8Divider(3)

#define PWMBCCER1_CC5E_MSK              BIT0
#define PWMB_CC5PEnable()               SET_REG_BIT(PWMB_CCER1, PWMBCCER1_CC5E_MSK)
#define PWMB_CC5PDisable()              CLR_REG_BIT(PWMB_CCER1, PWMBCCER1_CC5E_MSK)

#define HSPWMB_CC5PEnable()             SET_HSPWMB_BIT(PWMB_CCER1, PWMBCCER1_CC5E_MSK)
#define HSPWMB_CC5PDisable()            CLR_HSPWMB_BIT(PWMB_CCER1, PWMBCCER1_CC5E_MSK)

#define PWMBCCER1_CC5P_MSK              BIT1
#define PWMB_CC5PNonInverted()          CLR_REG_BIT(PWMB_CCER1, PWMBCCER1_CC5P_MSK)
#define PWMB_CC5PInverted()             SET_REG_BIT(PWMB_CCER1, PWMBCCER1_CC5P_MSK)

#define HSPWMB_CC5PNonInverted()        CLR_HSPWMB_BIT(PWMB_CCER1, PWMBCCER1_CC5P_MSK)
#define HSPWMB_CC5PInverted()           SET_HSPWMB_BIT(PWMB_CCER1, PWMBCCER1_CC5P_MSK)

#define PWMBCCER1_CC6E_MSK              BIT4
#define PWMB_CC6PEnable()               SET_REG_BIT(PWMB_CCER1, PWMBCCER1_CC6E_MSK)
#define PWMB_CC6PDisable()              CLR_REG_BIT(PWMB_CCER1, PWMBCCER1_CC6E_MSK)

#define HSPWMB_CC6PEnable()             SET_HSPWMB_BIT(PWMB_CCER1, PWMBCCER1_CC6E_MSK)
#define HSPWMB_CC6PDisable()            CLR_HSPWMB_BIT(PWMB_CCER1, PWMBCCER1_CC6E_MSK)

#define PWMBCCER1_CC6P_MSK              BIT5
#define PWMB_CC6PNonInverted()          CLR_REG_BIT(PWMB_CCER1, PWMBCCER1_CC6P_MSK)
#define PWMB_CC6PInverted()             SET_REG_BIT(PWMB_CCER1, PWMBCCER1_CC6P_MSK)

#define HSPWMB_CC6PNonInverted()        CLR_HSPWMB_BIT(PWMB_CCER1, PWMBCCER1_CC6P_MSK)
#define HSPWMB_CC6PInverted()           SET_HSPWMB_BIT(PWMB_CCER1, PWMBCCER1_CC6P_MSK)

#define PWMBCCER2_CC7E_MSK              BIT0
#define PWMB_CC7PEnable()               SET_REG_BIT(PWMB_CCER2, PWMBCCER2_CC7E_MSK)
#define PWMB_CC7PDisable()              CLR_REG_BIT(PWMB_CCER2, PWMBCCER2_CC7E_MSK)

#define HSPWMB_CC7PEnable()             SET_HSPWMB_BIT(PWMB_CCER2, PWMBCCER2_CC7E_MSK)
#define HSPWMB_CC7PDisable()            CLR_HSPWMB_BIT(PWMB_CCER2, PWMBCCER2_CC7E_MSK)

#define PWMBCCER2_CC7P_MSK              BIT1
#define PWMB_CC7PNonInverted()          CLR_REG_BIT(PWMB_CCER2, PWMBCCER2_CC7P_MSK)
#define PWMB_CC7PInverted()             SET_REG_BIT(PWMB_CCER2, PWMBCCER2_CC7P_MSK)

#define HSPWMB_CC7PNonInverted()        CLR_HSPWMB_BIT(PWMB_CCER2, PWMBCCER2_CC7P_MSK)
#define HSPWMB_CC7PInverted()           SET_HSPWMB_BIT(PWMB_CCER2, PWMBCCER2_CC7P_MSK)

#define PWMBCCER2_CC8E_MSK              BIT4
#define PWMB_CC8PEnable()               SET_REG_BIT(PWMB_CCER2, PWMBCCER2_CC8E_MSK)
#define PWMB_CC8PDisable()              CLR_REG_BIT(PWMB_CCER2, PWMBCCER2_CC8E_MSK)

#define HSPWMB_CC8PEnable()             SET_HSPWMB_BIT(PWMB_CCER2, PWMBCCER2_CC8E_MSK)
#define HSPWMB_CC8PDisable()            CLR_HSPWMB_BIT(PWMB_CCER2, PWMBCCER2_CC8E_MSK)

#define PWMBCCER2_CC8P_MSK              BIT5
#define PWMB_CC8PNonInverted()          CLR_REG_BIT(PWMB_CCER2, PWMBCCER2_CC8P_MSK)
#define PWMB_CC8PInverted()             SET_REG_BIT(PWMB_CCER2, PWMBCCER2_CC8P_MSK)

#define HSPWMB_CC8PNonInverted()        CLR_HSPWMB_BIT(PWMB_CCER2, PWMBCCER2_CC8P_MSK)
#define HSPWMB_CC8PInverted()           SET_HSPWMB_BIT(PWMB_CCER2, PWMBCCER2_CC8P_MSK)

#define PWMBBRK_MOE_MSK                 BIT7
#define PWMB_EnableMainOutput()         SET_REG_BIT(PWMB_BKR, PWMBBRK_MOE_MSK)
#define PWMB_DisableMainOutput()        CLR_REG_BIT(PWMB_BKR, PWMBBRK_MOE_MSK)

#define HSPWMB_EnableMainOutput()       SET_HSPWMB_BIT(PWMB_BKR, PWMBBRK_MOE_MSK)
#define HSPWMB_DisableMainOutput()      CLR_HSPWMB_BIT(PWMB_BKR, PWMBBRK_MOE_MSK)

#define PWMBBRK_AOE_MSK                 BIT6
#define PWMB_EnableAutoOutput()         SET_REG_BIT(PWMB_BKR, PWMBBRK_AOE_MSK)
#define PWMB_DisableAutoOutput()        CLR_REG_BIT(PWMB_BKR, PWMBBRK_AOE_MSK)

#define HSPWMB_EnableAutoOutput()       SET_HSPWMB_BIT(PWMB_BKR, PWMBBRK_AOE_MSK)
#define HSPWMB_DisableAutoOutput()      CLR_HSPWMB_BIT(PWMB_BKR, PWMBBRK_AOE_MSK)

#define PWMBBRK_BKP_MSK                 BIT5
#define PWMB_BRKNonInverted()           SET_REG_BIT(PWMB_BKR, PWMBBRK_BKP_MSK)
#define PWMB_BRKInverted()              CLR_REG_BIT(PWMB_BKR, PWMBBRK_BKP_MSK)

#define HSPWMB_BRKNonInverted()         SET_HSPWMB_BIT(PWMB_BKR, PWMBBRK_BKP_MSK)
#define HSPWMB_BRKInverted()            CLR_HSPWMB_BIT(PWMB_BKR, PWMBBRK_BKP_MSK)

#define PWMBBRK_BKE_MSK                 BIT4
#define PWMB_BRKEnable()                SET_REG_BIT(PWMB_BKR, PWMBBRK_BKE_MSK)
#define PWMB_BRKDisable()               CLR_REG_BIT(PWMB_BKR, PWMBBRK_BKE_MSK)

#define HSPWMB_BRKEnable()              SET_HSPWMB_BIT(PWMB_BKR, PWMBBRK_BKE_MSK)
#define HSPWMB_BRKDisable()             CLR_HSPWMB_BIT(PWMB_BKR, PWMBBRK_BKE_MSK)

#define PWMBBRK_OSSR_MSK                BIT3
#define PWMBBRK_OSSI_MSK                BIT2
#define PWMB_RunInactiveNoOutput()      CLR_REG_BIT(PWMB_BKR, PWMBBRK_OSSR_MSK)
#define PWMB_RunInactiveOutput()        SET_REG_BIT(PWMB_BKR, PWMBBRK_OSSR_MSK)
#define PWMB_IdleInactiveNoOutput()     CLR_REG_BIT(PWMB_BKR, PWMBBRK_OSSI_MSK)
#define PWMB_IdleInactiveOutput()       SET_REG_BIT(PWMB_BKR, PWMBBRK_OSSI_MSK)

#define HSPWMB_RunInactiveNoOutput()    CLR_HSPWMB_BIT(PWMB_BKR, PWMBBRK_OSSR_MSK)
#define HSPWMB_RunInactiveOutput()      SET_HSPWMB_BIT(PWMB_BKR, PWMBBRK_OSSR_MSK)
#define HSPWMB_IdleInactiveNoOutput()   CLR_HSPWMB_BIT(PWMB_BKR, PWMBBRK_OSSI_MSK)
#define HSPWMB_IdleInactiveOutput()     SET_HSPWMB_BIT(PWMB_BKR, PWMBBRK_OSSI_MSK)

#define PWMBBRK_LOCK_MSK                (BIT1 | BIT0)
#define PWMB_SetLockLevel(n)            MODIFY_REG(PWMB_BKR,  PWMBBRK_LOCK_MSK, ((n) << 0))
#define PWMB_SetUnLock()                PWMB_SetLockLevel(0)

#define HSPWMB_SetLockLevel(n)          MODIFY_HSPWMB(PWMB_BKR,  PWMBBRK_LOCK_MSK, ((n) << 0))
#define HSPWMB_SetUnLock()              HSPWMB_SetLockLevel(0)

#define PWMBOISR_OIS5_MSK               BIT0
#define PWMBOISR_OIS6_MSK               BIT2
#define PWMBOISR_OIS7_MSK               BIT4
#define PWMBOISR_OIS8_MSK               BIT6
#define PWMB_OC5PIdleLevelLow()         CLR_REG_BIT(PWMB_OISR, PWMBOISR_OIS5_MSK)
#define PWMB_OC5PIdleLevelHigh()        SET_REG_BIT(PWMB_OISR, PWMBOISR_OIS5_MSK)
#define PWMB_OC6PIdleLevelLow()         CLR_REG_BIT(PWMB_OISR, PWMBOISR_OIS6_MSK)
#define PWMB_OC6PIdleLevelHigh()        SET_REG_BIT(PWMB_OISR, PWMBOISR_OIS6_MSK)
#define PWMB_OC7PIdleLevelLow()         CLR_REG_BIT(PWMB_OISR, PWMBOISR_OIS7_MSK)
#define PWMB_OC7PIdleLevelHigh()        SET_REG_BIT(PWMB_OISR, PWMBOISR_OIS7_MSK)
#define PWMB_OC8PIdleLevelLow()         CLR_REG_BIT(PWMB_OISR, PWMBOISR_OIS8_MSK)
#define PWMB_OC8PIdleLevelHigh()        SET_REG_BIT(PWMB_OISR, PWMBOISR_OIS8_MSK)

#define HSPWMB_OC5PIdleLevelLow()       CLR_HSPWMB_BIT(PWMB_OISR, PWMBOISR_OIS5_MSK)
#define HSPWMB_OC5PIdleLevelHigh()      SET_HSPWMB_BIT(PWMB_OISR, PWMBOISR_OIS5_MSK)
#define HSPWMB_OC6PIdleLevelLow()       CLR_HSPWMB_BIT(PWMB_OISR, PWMBOISR_OIS6_MSK)
#define HSPWMB_OC6PIdleLevelHigh()      SET_HSPWMB_BIT(PWMB_OISR, PWMBOISR_OIS6_MSK)
#define HSPWMB_OC7PIdleLevelLow()       CLR_HSPWMB_BIT(PWMB_OISR, PWMBOISR_OIS7_MSK)
#define HSPWMB_OC7PIdleLevelHigh()      SET_HSPWMB_BIT(PWMB_OISR, PWMBOISR_OIS7_MSK)
#define HSPWMB_OC8PIdleLevelLow()       CLR_HSPWMB_BIT(PWMB_OISR, PWMBOISR_OIS8_MSK)
#define HSPWMB_OC8PIdleLevelHigh()      SET_HSPWMB_BIT(PWMB_OISR, PWMBOISR_OIS8_MSK)

#define PWMB_SetCounter(n)              (PWMB_CNTRH = HIBYTE(n), PWMB_CNTRL = LOBYTE(n))
#define PWMB_SetClockDivider(n)         (PWMB_PSCRH = HIBYTE(n), PWMB_PSCRL = LOBYTE(n))
#define PWMB_SetReload16(n)             (PWMB_ARRH = HIBYTE(n), PWMB_ARRL = LOBYTE(n))
#define PWMB_SetRepeatCounter(n)        (PWMB_RCRH = HIBYTE(n), PWMB_RCR = LOBYTE(n))

#define HSPWMB_SetCounter(n)            (WRITE_HSPWMB(PWMB_CNTRH, HIBYTE(n)), WRITE_HSPWMB(PWMB_CNTRL, LOBYTE(n)))
#define HSPWMB_SetClockDivider(n)       (WRITE_HSPWMB(PWMB_PSCRH, HIBYTE(n)), WRITE_HSPWMB(PWMB_PSCRL, LOBYTE(n)))
#define HSPWMB_SetReload16(n)           (WRITE_HSPWMB(PWMB_ARRH, HIBYTE(n)), WRITE_HSPWMB(PWMB_ARRL, LOBYTE(n)))
#define HSPWMB_SetRepeatCounter(n)      (WRITE_HSPWMB(PWMB_RCRH, HIBYTE(n)), WRITE_HSPWMB(PWMB_RCR, LOBYTE(n)))

#define PWMB_SetCCR5Value(n)            (PWMB_CCR5H = HIBYTE(n), PWMB_CCR5L = LOBYTE(n))
#define PWMB_SetCCR6Value(n)            (PWMB_CCR6H = HIBYTE(n), PWMB_CCR6L = LOBYTE(n))
#define PWMB_SetCCR7Value(n)            (PWMB_CCR7H = HIBYTE(n), PWMB_CCR7L = LOBYTE(n))
#define PWMB_SetCCR8Value(n)            (PWMB_CCR8H = HIBYTE(n), PWMB_CCR8L = LOBYTE(n))

#define HSPWMB_SetCCR5Value(n)          (WRITE_HSPWMB(PWMB_CCR5H, HIBYTE(n)), WRITE_HSPWMB(PWMB_CCR5L, LOBYTE(n)))
#define HSPWMB_SetCCR6Value(n)          (WRITE_HSPWMB(PWMB_CCR6H, HIBYTE(n)), WRITE_HSPWMB(PWMB_CCR6L, LOBYTE(n)))
#define HSPWMB_SetCCR7Value(n)          (WRITE_HSPWMB(PWMB_CCR7H, HIBYTE(n)), WRITE_HSPWMB(PWMB_CCR7L, LOBYTE(n)))
#define HSPWMB_SetCCR8Value(n)          (WRITE_HSPWMB(PWMB_CCR8H, HIBYTE(n)), WRITE_HSPWMB(PWMB_CCR8L, LOBYTE(n)))

#define PWMB_ReadReload16()             MAKEWORD(PWMB_ARRL, PWMB_ARRH)

#define HSPWMB_ReadReload16()           MAKEWORD(READ_HSPWMB(PWMB_ARRL), READ_HSPWMB(PWMB_ARRH))

#define PWMB_ReadCCR5Value()            MAKEWORD(PWMB_CCR5L, PWMB_CCR5H)
#define PWMB_ReadCCR6Value()            MAKEWORD(PWMB_CCR6L, PWMB_CCR6H)
#define PWMB_ReadCCR7Value()            MAKEWORD(PWMB_CCR7L, PWMB_CCR7H)
#define PWMB_ReadCCR8Value()            MAKEWORD(PWMB_CCR8L, PWMB_CCR8H)

#define HSPWMB_ReadCCR5Value()          MAKEWORD(READ_HSPWMB(PWMB_CCR5L), READ_HSPWMB(PWMB_CCR5H))
#define HSPWMB_ReadCCR6Value()          MAKEWORD(READ_HSPWMB(PWMB_CCR6L), READ_HSPWMB(PWMB_CCR6H))
#define HSPWMB_ReadCCR7Value()          MAKEWORD(READ_HSPWMB(PWMB_CCR7L), READ_HSPWMB(PWMB_CCR7H))
#define HSPWMB_ReadCCR8Value()          MAKEWORD(READ_HSPWMB(PWMB_CCR8L), READ_HSPWMB(PWMB_CCR8H))

#define PWMB_SetDeadTime(n)             PWMB_DTR = LOBYTE(n)

#define HSPWMB_SetDeadTime(n)           WRITE_HSPWMB(PWMB_DTR, LOBYTE(n))

////////////////////////

#define PWMCENO_ENO1P_MSK               BIT0
#define PWMCENO_ENO1N_MSK               BIT1
#define PWMCENO_ENO2P_MSK               BIT2
#define PWMCENO_ENO2N_MSK               BIT3
#define PWMCENO_ENO3P_MSK               BIT4
#define PWMCENO_ENO3N_MSK               BIT5
#define PWMCENO_ENO4P_MSK               BIT6
#define PWMCENO_ENO4N_MSK               BIT7
#define PWMCENO2_ENO5P_MSK              BIT0
#define PWMCENO2_ENO6P_MSK              BIT2
#define PWMC_EnablePWM1POutput()        SET_REG_BIT(PWMC_ENO, PWMCENO_ENO1P_MSK)
#define PWMC_DisablePWM1POutput()       CLR_REG_BIT(PWMC_ENO, PWMCENO_ENO1P_MSK)
#define PWMC_EnablePWM1NOutput()        SET_REG_BIT(PWMC_ENO, PWMCENO_ENO1N_MSK)
#define PWMC_DisablePWM1NOutput()       CLR_REG_BIT(PWMC_ENO, PWMCENO_ENO1N_MSK)
#define PWMC_EnablePWM2POutput()        SET_REG_BIT(PWMC_ENO, PWMCENO_ENO2P_MSK)
#define PWMC_DisablePWM2POutput()       CLR_REG_BIT(PWMC_ENO, PWMCENO_ENO2P_MSK)
#define PWMC_EnablePWM2NOutput()        SET_REG_BIT(PWMC_ENO, PWMCENO_ENO2N_MSK)
#define PWMC_DisablePWM2NOutput()       CLR_REG_BIT(PWMC_ENO, PWMCENO_ENO2N_MSK)
#define PWMC_EnablePWM3POutput()        SET_REG_BIT(PWMC_ENO, PWMCENO_ENO3P_MSK)
#define PWMC_DisablePWM3POutput()       CLR_REG_BIT(PWMC_ENO, PWMCENO_ENO3P_MSK)
#define PWMC_EnablePWM3NOutput()        SET_REG_BIT(PWMC_ENO, PWMCENO_ENO3N_MSK)
#define PWMC_DisablePWM3NOutput()       CLR_REG_BIT(PWMC_ENO, PWMCENO_ENO3N_MSK)
#define PWMC_EnablePWM4POutput()        SET_REG_BIT(PWMC_ENO, PWMCENO_ENO4P_MSK)
#define PWMC_DisablePWM4POutput()       CLR_REG_BIT(PWMC_ENO, PWMCENO_ENO4P_MSK)
#define PWMC_EnablePWM4NOutput()        SET_REG_BIT(PWMC_ENO, PWMCENO_ENO4N_MSK)
#define PWMC_DisablePWM4NOutput()       CLR_REG_BIT(PWMC_ENO, PWMCENO_ENO4N_MSK)
#define PWMC_EnablePWM5POutput()        SET_REG_BIT(PWMC_ENO2, PWMCENO2_ENO5P_MSK)
#define PWMC_DisablePWM5POutput()       CLR_REG_BIT(PWMC_ENO2, PWMCENO2_ENO5P_MSK)
#define PWMC_EnablePWM6POutput()        SET_REG_BIT(PWMC_ENO2, PWMCENO2_ENO6P_MSK)
#define PWMC_DisablePWM6POutput()       CLR_REG_BIT(PWMC_ENO2, PWMCENO2_ENO6P_MSK)

#define HSPWMC_EnablePWM1POutput()      SET_HSPWMC_BIT(PWMC_ENO, PWMCENO_ENO1P_MSK)
#define HSPWMC_DisablePWM1POutput()     CLR_HSPWMC_BIT(PWMC_ENO, PWMCENO_ENO1P_MSK)
#define HSPWMC_EnablePWM1NOutput()      SET_HSPWMC_BIT(PWMC_ENO, PWMCENO_ENO1N_MSK)
#define HSPWMC_DisablePWM1NOutput()     CLR_HSPWMC_BIT(PWMC_ENO, PWMCENO_ENO1N_MSK)
#define HSPWMC_EnablePWM2POutput()      SET_HSPWMC_BIT(PWMC_ENO, PWMCENO_ENO2P_MSK)
#define HSPWMC_DisablePWM2POutput()     CLR_HSPWMC_BIT(PWMC_ENO, PWMCENO_ENO2P_MSK)
#define HSPWMC_EnablePWM2NOutput()      SET_HSPWMC_BIT(PWMC_ENO, PWMCENO_ENO2N_MSK)
#define HSPWMC_DisablePWM2NOutput()     CLR_HSPWMC_BIT(PWMC_ENO, PWMCENO_ENO2N_MSK)
#define HSPWMC_EnablePWM3POutput()      SET_HSPWMC_BIT(PWMC_ENO, PWMCENO_ENO3P_MSK)
#define HSPWMC_DisablePWM3POutput()     CLR_HSPWMC_BIT(PWMC_ENO, PWMCENO_ENO3P_MSK)
#define HSPWMC_EnablePWM3NOutput()      SET_HSPWMC_BIT(PWMC_ENO, PWMCENO_ENO3N_MSK)
#define HSPWMC_DisablePWM3NOutput()     CLR_HSPWMC_BIT(PWMC_ENO, PWMCENO_ENO3N_MSK)
#define HSPWMC_EnablePWM4POutput()      SET_HSPWMC_BIT(PWMC_ENO, PWMCENO_ENO4P_MSK)
#define HSPWMC_DisablePWM4POutput()     CLR_HSPWMC_BIT(PWMC_ENO, PWMCENO_ENO4P_MSK)
#define HSPWMC_EnablePWM4NOutput()      SET_HSPWMC_BIT(PWMC_ENO, PWMCENO_ENO4N_MSK)
#define HSPWMC_DisablePWM4NOutput()     CLR_HSPWMC_BIT(PWMC_ENO, PWMCENO_ENO4N_MSK)
#define HSPWMC_EnablePWM5POutput()      SET_HSPWMC_BIT(PWMC_ENO2, PWMCENO2_ENO5P_MSK)
#define HSPWMC_DisablePWM5POutput()     CLR_HSPWMC_BIT(PWMC_ENO2, PWMCENO2_ENO5P_MSK)
#define HSPWMC_EnablePWM6POutput()      SET_HSPWMC_BIT(PWMC_ENO2, PWMCENO2_ENO6P_MSK)
#define HSPWMC_DisablePWM6POutput()     CLR_HSPWMC_BIT(PWMC_ENO2, PWMCENO2_ENO6P_MSK)

#define PWMCIOAUX_AUX1P_MSK             BIT0
#define PWMCIOAUX_AUX1N_MSK             BIT1
#define PWMCIOAUX_AUX2P_MSK             BIT2
#define PWMCIOAUX_AUX2N_MSK             BIT3
#define PWMCIOAUX_AUX3P_MSK             BIT4
#define PWMCIOAUX_AUX3N_MSK             BIT5
#define PWMCIOAUX_AUX4P_MSK             BIT6
#define PWMCIOAUX_AUX4N_MSK             BIT7
#define PWMCIOAUX2_AUX5P_MSK            BIT0
#define PWMCIOAUX2_AUX6P_MSK            BIT2
#define PWMC_EnoCtrlPWM1P()             CLR_REG_BIT(PWMC_IOAUX, PWMCIOAUX_AUX1P_MSK)
#define PWMC_EnoBrkCtrlPWM1P()          SET_REG_BIT(PWMC_IOAUX, PWMCIOAUX_AUX1P_MSK)
#define PWMC_EnoCtrlPWM1N()             CLR_REG_BIT(PWMC_IOAUX, PWMCIOAUX_AUX1N_MSK)
#define PWMC_EnoBrkCtrlPWM1N()          SET_REG_BIT(PWMC_IOAUX, PWMCIOAUX_AUX1N_MSK)
#define PWMC_EnoCtrlPWM2P()             CLR_REG_BIT(PWMC_IOAUX, PWMCIOAUX_AUX2P_MSK)
#define PWMC_EnoBrkCtrlPWM2P()          SET_REG_BIT(PWMC_IOAUX, PWMCIOAUX_AUX2P_MSK)
#define PWMC_EnoCtrlPWM2N()             CLR_REG_BIT(PWMC_IOAUX, PWMCIOAUX_AUX2N_MSK)
#define PWMC_EnoBrkCtrlPWM2N()          SET_REG_BIT(PWMC_IOAUX, PWMCIOAUX_AUX2N_MSK)
#define PWMC_EnoCtrlPWM3P()             CLR_REG_BIT(PWMC_IOAUX, PWMCIOAUX_AUX3P_MSK)
#define PWMC_EnoBrkCtrlPWM3P()          SET_REG_BIT(PWMC_IOAUX, PWMCIOAUX_AUX3P_MSK)
#define PWMC_EnoCtrlPWM3N()             CLR_REG_BIT(PWMC_IOAUX, PWMCIOAUX_AUX3N_MSK)
#define PWMC_EnoBrkCtrlPWM3N()          SET_REG_BIT(PWMC_IOAUX, PWMCIOAUX_AUX3N_MSK)
#define PWMC_EnoCtrlPWM4P()             CLR_REG_BIT(PWMC_IOAUX, PWMCIOAUX_AUX4P_MSK)
#define PWMC_EnoBrkCtrlPWM4P()          SET_REG_BIT(PWMC_IOAUX, PWMCIOAUX_AUX4P_MSK)
#define PWMC_EnoCtrlPWM4N()             CLR_REG_BIT(PWMC_IOAUX, PWMCIOAUX_AUX4N_MSK)
#define PWMC_EnoBrkCtrlPWM4N()          SET_REG_BIT(PWMC_IOAUX, PWMCIOAUX_AUX4N_MSK)
#define PWMC_EnoCtrlPWM5P()             CLR_REG_BIT(PWMC_IOAUX2, PWMCIOAUX2_AUX5P_MSK)
#define PWMC_EnoBrkCtrlPWM5P()          SET_REG_BIT(PWMC_IOAUX2, PWMCIOAUX2_AUX5P_MSK)
#define PWMC_EnoCtrlPWM6P()             CLR_REG_BIT(PWMC_IOAUX2, PWMCIOAUX2_AUX6P_MSK)
#define PWMC_EnoBrkCtrlPWM6P()          SET_REG_BIT(PWMC_IOAUX2, PWMCIOAUX2_AUX6P_MSK)

#define HSPWMC_EnoCtrlPWM1P()           CLR_HSPWMC_BIT(PWMC_IOAUX, PWMCIOAUX_AUX1P_MSK)
#define HSPWMC_EnoBrkCtrlPWM1P()        SET_HSPWMC_BIT(PWMC_IOAUX, PWMCIOAUX_AUX1P_MSK)
#define HSPWMC_EnoCtrlPWM1N()           CLR_HSPWMC_BIT(PWMC_IOAUX, PWMCIOAUX_AUX1N_MSK)
#define HSPWMC_EnoBrkCtrlPWM1N()        SET_HSPWMC_BIT(PWMC_IOAUX, PWMCIOAUX_AUX1N_MSK)
#define HSPWMC_EnoCtrlPWM2P()           CLR_HSPWMC_BIT(PWMC_IOAUX, PWMCIOAUX_AUX2P_MSK)
#define HSPWMC_EnoBrkCtrlPWM2P()        SET_HSPWMC_BIT(PWMC_IOAUX, PWMCIOAUX_AUX2P_MSK)
#define HSPWMC_EnoCtrlPWM2N()           CLR_HSPWMC_BIT(PWMC_IOAUX, PWMCIOAUX_AUX2N_MSK)
#define HSPWMC_EnoBrkCtrlPWM2N()        SET_HSPWMC_BIT(PWMC_IOAUX, PWMCIOAUX_AUX2N_MSK)
#define HSPWMC_EnoCtrlPWM3P()           CLR_HSPWMC_BIT(PWMC_IOAUX, PWMCIOAUX_AUX3P_MSK)
#define HSPWMC_EnoBrkCtrlPWM3P()        SET_HSPWMC_BIT(PWMC_IOAUX, PWMCIOAUX_AUX3P_MSK)
#define HSPWMC_EnoCtrlPWM3N()           CLR_HSPWMC_BIT(PWMC_IOAUX, PWMCIOAUX_AUX3N_MSK)
#define HSPWMC_EnoBrkCtrlPWM3N()        SET_HSPWMC_BIT(PWMC_IOAUX, PWMCIOAUX_AUX3N_MSK)
#define HSPWMC_EnoCtrlPWM4P()           CLR_HSPWMC_BIT(PWMC_IOAUX, PWMCIOAUX_AUX4P_MSK)
#define HSPWMC_EnoBrkCtrlPWM4P()        SET_HSPWMC_BIT(PWMC_IOAUX, PWMCIOAUX_AUX4P_MSK)
#define HSPWMC_EnoCtrlPWM4N()           CLR_HSPWMC_BIT(PWMC_IOAUX, PWMCIOAUX_AUX4N_MSK)
#define HSPWMC_EnoBrkCtrlPWM4N()        SET_HSPWMC_BIT(PWMC_IOAUX, PWMCIOAUX_AUX4N_MSK)
#define HSPWMC_EnoCtrlPWM5P()           CLR_HSPWMC_BIT(PWMC_IOAUX2, PWMCIOAUX2_AUX5P_MSK)
#define HSPWMC_EnoBrkCtrlPWM5P()        SET_HSPWMC_BIT(PWMC_IOAUX2, PWMCIOAUX2_AUX5P_MSK)
#define HSPWMC_EnoCtrlPWM6P()           CLR_HSPWMC_BIT(PWMC_IOAUX2, PWMCIOAUX2_AUX6P_MSK)
#define HSPWMC_EnoBrkCtrlPWM6P()        SET_HSPWMC_BIT(PWMC_IOAUX2, PWMCIOAUX2_AUX6P_MSK)

#define PWMCCR1_ARPE_MSK                BIT7
#define PWMC_UnbufferARR()              CLR_REG_BIT(PWMC_CR1, PWMCCR1_ARPE_MSK)
#define PWMC_BufferARR()                SET_REG_BIT(PWMC_CR1, PWMCCR1_ARPE_MSK)

#define HSPWMC_UnbufferARR()            CLR_HSPWMC_BIT(PWMC_CR1, PWMCCR1_ARPE_MSK)
#define HSPWMC_BufferARR()              SET_HSPWMC_BIT(PWMC_CR1, PWMCCR1_ARPE_MSK)

#define PWMCCR1_CMS_MSK                 (BIT6 | BIT5)
#define PWMC_SetAlignMode(n)            MODIFY_REG(PWMC_CR1,  PWMCCR1_CMS_MSK, ((n) << 5))
#define PWMC_EdgeAlignMode()            PWMC_SetAlignMode(0)
#define PWMC_CenterAlignMode1()         PWMC_SetAlignMode(1)
#define PWMC_CenterAlignMode2()         PWMC_SetAlignMode(2)
#define PWMC_CenterAlignMode3()         PWMC_SetAlignMode(3)

#define HSPWMC_SetAlignMode(n)          MODIFY_HSPWMC(PWMC_CR1,  PWMCCR1_CMS_MSK, ((n) << 5))
#define HSPWMC_EdgeAlignMode()          HSPWMC_SetAlignMode(0)
#define HSPWMC_CenterAlignMode1()       HSPWMC_SetAlignMode(1)
#define HSPWMC_CenterAlignMode2()       HSPWMC_SetAlignMode(2)
#define HSPWMC_CenterAlignMode3()       HSPWMC_SetAlignMode(3)

#define PWMCCR1_DIR_MSK                 BIT4
#define PWMC_UpCounter()                CLR_REG_BIT(PWMC_CR1, PWMCCR1_DIR_MSK)
#define PWMC_DownCounter()              SET_REG_BIT(PWMC_CR1, PWMCCR1_DIR_MSK)

#define HSPWMC_UpCounter()              CLR_HSPWMC_BIT(PWMC_CR1, PWMCCR1_DIR_MSK)
#define HSPWMC_DownCounter()            SET_HSPWMC_BIT(PWMC_CR1, PWMCCR1_DIR_MSK)

#define PWMCCR1_OPM_MSK                 BIT3
#define PWMC_ContinueMode()             CLR_REG_BIT(PWMC_CR1, PWMCCR1_OPM_MSK)
#define PWMC_OnePulseMode()             SET_REG_BIT(PWMC_CR1, PWMCCR1_OPM_MSK)

#define HSPWMC_ContinueMode()           CLR_HSPWMC_BIT(PWMC_CR1, PWMCCR1_OPM_MSK)
#define HSPWMC_OnePulseMode()           SET_HSPWMC_BIT(PWMC_CR1, PWMCCR1_OPM_MSK)

#define PWMCCR1_URS_MSK                 BIT2
#define PWMC_UpdateRequestMode1()       SET_REG_BIT(PWMC_CR1, PWMCCR1_URS_MSK)
#define PWMC_UpdateRequestMode2()       CLR_REG_BIT(PWMC_CR1, PWMCCR1_URS_MSK)

#define HSPWMC_UpdateRequestMode1()     SET_HSPWMC_BIT(PWMC_CR1, PWMCCR1_URS_MSK)
#define HSPWMC_UpdateRequestMode2()     CLR_HSPWMC_BIT(PWMC_CR1, PWMCCR1_URS_MSK)

#define PWMCCR1_UDIS_MSK                BIT1
#define PWMC_EnableUpdate()             CLR_REG_BIT(PWMC_CR1, PWMCCR1_UDIS_MSK)
#define PWMC_DisableUpdate()            SET_REG_BIT(PWMC_CR1, PWMCCR1_UDIS_MSK)

#define HSPWMC_EnableUpdate()           CLR_HSPWMC_BIT(PWMC_CR1, PWMCCR1_UDIS_MSK)
#define HSPWMC_DisableUpdate()          SET_HSPWMC_BIT(PWMC_CR1, PWMCCR1_UDIS_MSK)

#define PWMCCR1_CEN_MSK                 BIT0
#define PWMC_Run()                      SET_REG_BIT(PWMC_CR1, PWMCCR1_CEN_MSK)
#define PWMC_Stop()                     CLR_REG_BIT(PWMC_CR1, PWMCCR1_CEN_MSK)

#define HSPWMC_Run()                    SET_HSPWMC_BIT(PWMC_CR1, PWMCCR1_CEN_MSK)
#define HSPWMC_Stop()                   CLR_HSPWMC_BIT(PWMC_CR1, PWMCCR1_CEN_MSK)

#define PWMCCR2_TIS_MSK                 BIT7
#define PWMC_PWM1PToTI()                CLR_REG_BIT(PWMC_CR2, PWMCCR2_TIS_MSK)
#define PWMC_Xor1P2P3PToTI()            SET_REG_BIT(PWMC_CR2, PWMCCR2_TIS_MSK)

#define HSPWMC_PWM1PToTI()              CLR_HSPWMC_BIT(PWMC_CR2, PWMCCR2_TIS_MSK)
#define HSPWMC_Xor1P2P3PToTI()          SET_HSPWMC_BIT(PWMC_CR2, PWMCCR2_TIS_MSK)

#define PWMCCR2_MMS_MSK                 (BIT6 | BIT5 | BIT4)
#define PWMC_SelectTRGO(n)              MODIFY_REG(PWMC_CR2,  PWMCCR2_MMS_MSK, ((n) << 4))
#define PWMC_ResetAsTRGO()              PWMC_SelectTRGO(0)
#define PWMC_EnableAsTRGO()             PWMC_SelectTRGO(1)
#define PWMC_UpdateAsTRGO()             PWMC_SelectTRGO(2)
#define PWMC_MatchAsTRGO()              PWMC_SelectTRGO(3)
#define PWMC_OC1REFAsTRGO()             PWMC_SelectTRGO(4)
#define PWMC_OC2REFAsTRGO()             PWMC_SelectTRGO(5)
#define PWMC_OC3REFAsTRGO()             PWMC_SelectTRGO(6)
#define PWMC_OC4REFAsTRGO()             PWMC_SelectTRGO(7)

#define HSPWMC_SelectTRGO(n)            MODIFY_HSPWMC(PWMC_CR2,  PWMCCR2_MMS_MSK, ((n) << 4))
#define HSPWMC_ResetAsTRGO()            HSPWMC_SelectTRGO(0)
#define HSPWMC_EnableAsTRGO()           HSPWMC_SelectTRGO(1)
#define HSPWMC_UpdateAsTRGO()           HSPWMC_SelectTRGO(2)
#define HSPWMC_MatchAsTRGO()            HSPWMC_SelectTRGO(3)
#define HSPWMC_OC1REFAsTRGO()           HSPWMC_SelectTRGO(4)
#define HSPWMC_OC2REFAsTRGO()           HSPWMC_SelectTRGO(5)
#define HSPWMC_OC3REFAsTRGO()           HSPWMC_SelectTRGO(6)
#define HSPWMC_OC4REFAsTRGO()           HSPWMC_SelectTRGO(7)

#define PWMCCR2_COMS_MSK                BIT2
#define PWMC_CCOCUpdateMode0()          CLR_REG_BIT(PWMC_CR2, PWMCCR2_COMS_MSK)
#define PWMC_CCOCUpdateMode1()          SET_REG_BIT(PWMC_CR2, PWMCCR2_COMS_MSK)

#define HSPWMC_CCOCUpdateMode0()        CLR_HSPWMC_BIT(PWMC_CR2, PWMCCR2_COMS_MSK)
#define HSPWMC_CCOCUpdateMode1()        SET_HSPWMC_BIT(PWMC_CR2, PWMCCR2_COMS_MSK)

#define PWMCCR2_CCPC_MSK                BIT0
#define PWMC_UnbufferCCOC()             CLR_REG_BIT(PWMC_CR2, PWMCCR2_CCPC_MSK)
#define PWMC_BufferCCOC()               SET_REG_BIT(PWMC_CR2, PWMCCR2_CCPC_MSK)

#define HSPWMC_UnbufferCCOC()           CLR_HSPWMC_BIT(PWMC_CR2, PWMCCR2_CCPC_MSK)
#define HSPWMC_BufferCCOC()             SET_HSPWMC_BIT(PWMC_CR2, PWMCCR2_CCPC_MSK)

#define PWMCSMCR_MSM_MSK                BIT7
#define PWMC_StandaloneMode()           CLR_REG_BIT(PWMC_SMCR, PWMCSMCR_MSM_MSK)
#define PWMC_MasterSlaveMode()          SET_REG_BIT(PWMC_SMCR, PWMCSMCR_MSM_MSK)

#define HSPWMC_StandaloneMode()         CLR_HSPWMC_BIT(PWMC_SMCR, PWMCSMCR_MSM_MSK)
#define HSPWMC_MasterSlaveMode()        SET_HSPWMC_BIT(PWMC_SMCR, PWMCSMCR_MSM_MSK)

#define PWMCSMCR_TS_MSK                 (BIT6 | BIT5 | BIT4)
#define PWMC_SelectTRGI(n)              MODIFY_REG(PWMC_SMCR,  PWMCSMCR_TS_MSK, ((n) << 4))
#define PWMC_DisableTRGI()              PWMC_SelectTRGI(0)
#define PWMC_ITR2AsTRGI()               PWMC_SelectTRGI(2)
#define PWMC_TI1FEDAsTRGI()             PWMC_SelectTRGI(4)
#define PWMC_TI1FP1AsTRGI()             PWMC_SelectTRGI(5)
#define PWMC_TI2FP2AsTRGI()             PWMC_SelectTRGI(6)
#define PWMC_ETRFAsTRGI()               PWMC_SelectTRGI(7)

#define HSPWMC_SelectTRGI(n)            MODIFY_HSPWMC(PWMC_SMCR,  PWMCSMCR_TS_MSK, ((n) << 4))
#define HSPWMC_DisableTRGI()            HSPWMC_SelectTRGI(0)
#define HSPWMC_ITR2AsTRGI()             HSPWMC_SelectTRGI(2)
#define HSPWMC_TI1FEDAsTRGI()           HSPWMC_SelectTRGI(4)
#define HSPWMC_TI1FP1AsTRGI()           HSPWMC_SelectTRGI(5)
#define HSPWMC_TI2FP2AsTRGI()           HSPWMC_SelectTRGI(6)
#define HSPWMC_ETRFAsTRGI()             HSPWMC_SelectTRGI(7)

#define PWMCSMCR_SMS_MSK                (BIT2 | BIT1 | BIT0)
#define PWMC_SetClockMode(n)            MODIFY_REG(PWMC_SMCR,  PWMCSMCR_SMS_MSK, ((n) << 0))
#define PWMC_InternalClockMode()        PWMC_SetClockMode(0)
#define PWMC_EncoderMode1()             PWMC_SetClockMode(1)
#define PWMC_EncoderMode2()             PWMC_SetClockMode(2)
#define PWMC_EncoderMode3()             PWMC_SetClockMode(3)
#define PWMC_TriggerResetMode()         PWMC_SetClockMode(4)
#define PWMC_TriggerGateMode()          PWMC_SetClockMode(5)
#define PWMC_TriggerStartMode()         PWMC_SetClockMode(6)
#define PWMC_ExternalClockMode()        PWMC_SetClockMode(7)

#define HSPWMC_SetClockMode(n)          MODIFY_HSPWMC(PWMC_SMCR,  PWMCSMCR_SMS_MSK, ((n) << 0))
#define HSPWMC_InternalClockMode()      HSPWMC_SetClockMode(0)
#define HSPWMC_EncoderMode1()           HSPWMC_SetClockMode(1)
#define HSPWMC_EncoderMode2()           HSPWMC_SetClockMode(2)
#define HSPWMC_EncoderMode3()           HSPWMC_SetClockMode(3)
#define HSPWMC_TriggerResetMode()       HSPWMC_SetClockMode(4)
#define HSPWMC_TriggerGateMode()        HSPWMC_SetClockMode(5)
#define HSPWMC_TriggerStartMode()       HSPWMC_SetClockMode(6)
#define HSPWMC_ExternalClockMode()      HSPWMC_SetClockMode(7)

#define PWMCETR_ETP_MSK                 BIT7
#define PWMC_ETRNonInverted()           CLR_REG_BIT(PWMC_ETR, PWMCETR_ETP_MSK)
#define PWMC_ETRInverted()              SET_REG_BIT(PWMC_ETR, PWMCETR_ETP_MSK)

#define HSPWMC_ETRNonInverted()         CLR_HSPWMC_BIT(PWMC_ETR, PWMCETR_ETP_MSK)
#define HSPWMC_ETRInverted()            SET_HSPWMC_BIT(PWMC_ETR, PWMCETR_ETP_MSK)

#define PWMCETR_ECE_MSK                 BIT6
#define PWMC_DisableExternalClock2()    CLR_REG_BIT(PWMC_ETR, PWMCETR_ECE_MSK)
#define PWMC_EnableExternalClock2()     SET_REG_BIT(PWMC_ETR, PWMCETR_ECE_MSK)

#define HSPWMC_DisableExternalClock2()  CLR_HSPWMC_BIT(PWMC_ETR, PWMCETR_ECE_MSK)
#define HSPWMC_EnableExternalClock2()   SET_HSPWMC_BIT(PWMC_ETR, PWMCETR_ECE_MSK)

#define PWMCETR_ETPS_MSK                (BIT5 | BIT4)
#define PWMC_SetETRDivider(n)           MODIFY_REG(PWMC_ETR,  PWMCETR_ETPS_MSK, ((n) << 4))
#define PWMC_ETRDivider1()              PWMC_SetETRDivider(0)
#define PWMC_ETRDivider2()              PWMC_SetETRDivider(1)
#define PWMC_ETRDivider4()              PWMC_SetETRDivider(2)
#define PWMC_ETRDivider8()              PWMC_SetETRDivider(3)

#define HSPWMC_SetETRDivider(n)         MODIFY_HSPWMC(PWMC_ETR,  PWMCETR_ETPS_MSK, ((n) << 4))
#define HSPWMC_ETRDivider1()            HSPWMC_SetETRDivider(0)
#define HSPWMC_ETRDivider2()            HSPWMC_SetETRDivider(1)
#define HSPWMC_ETRDivider4()            HSPWMC_SetETRDivider(2)
#define HSPWMC_ETRDivider8()            HSPWMC_SetETRDivider(3)

#define PWMCETR_ETF_MSK                 (BIT_LN)
#define PWMC_SetETRFilter(n)            MODIFY_REG(PWMC_ETR,  PWMCETR_ETF_MSK, ((n) << 0))
#define PWMC_ETRFilter1()               PWMC_SetETRFilter(0)
#define PWMC_ETRFilter2()               PWMC_SetETRFilter(1)
#define PWMC_ETRFilter4()               PWMC_SetETRFilter(2)
#define PWMC_ETRFilter8()               PWMC_SetETRFilter(3)
#define PWMC_ETRFilter12()              PWMC_SetETRFilter(4)
#define PWMC_ETRFilter16()              PWMC_SetETRFilter(5)
#define PWMC_ETRFilter24()              PWMC_SetETRFilter(6)
#define PWMC_ETRFilter32()              PWMC_SetETRFilter(7)
#define PWMC_ETRFilter48()              PWMC_SetETRFilter(8)
#define PWMC_ETRFilter64()              PWMC_SetETRFilter(9)
#define PWMC_ETRFilter80()              PWMC_SetETRFilter(10)
#define PWMC_ETRFilter96()              PWMC_SetETRFilter(11)
#define PWMC_ETRFilter128()             PWMC_SetETRFilter(12)
#define PWMC_ETRFilter160()             PWMC_SetETRFilter(13)
#define PWMC_ETRFilter192()             PWMC_SetETRFilter(14)
#define PWMC_ETRFilter256()             PWMC_SetETRFilter(15)

#define HSPWMC_SetETRFilter(n)          MODIFY_HSPWMC(PWMC_ETR,  PWMCETR_ETF_MSK, ((n) << 0))
#define HSPWMC_ETRFilter1()             HSPWMC_SetETRFilter(0)
#define HSPWMC_ETRFilter2()             HSPWMC_SetETRFilter(1)
#define HSPWMC_ETRFilter4()             HSPWMC_SetETRFilter(2)
#define HSPWMC_ETRFilter8()             HSPWMC_SetETRFilter(3)
#define HSPWMC_ETRFilter12()            HSPWMC_SetETRFilter(4)
#define HSPWMC_ETRFilter16()            HSPWMC_SetETRFilter(5)
#define HSPWMC_ETRFilter24()            HSPWMC_SetETRFilter(6)
#define HSPWMC_ETRFilter32()            HSPWMC_SetETRFilter(7)
#define HSPWMC_ETRFilter48()            HSPWMC_SetETRFilter(8)
#define HSPWMC_ETRFilter64()            HSPWMC_SetETRFilter(9)
#define HSPWMC_ETRFilter80()            HSPWMC_SetETRFilter(10)
#define HSPWMC_ETRFilter96()            HSPWMC_SetETRFilter(11)
#define HSPWMC_ETRFilter128()           HSPWMC_SetETRFilter(12)
#define HSPWMC_ETRFilter160()           HSPWMC_SetETRFilter(13)
#define HSPWMC_ETRFilter192()           HSPWMC_SetETRFilter(14)
#define HSPWMC_ETRFilter256()           HSPWMC_SetETRFilter(15)

#define PWMCEGR_BG_MSK                  BIT7
#define PWMCEGR_TG_MSK                  BIT6
#define PWMCEGR_COMG_MSK                BIT5
#define PWMCEGR_CC4G_MSK                BIT4
#define PWMCEGR_CC3G_MSK                BIT3
#define PWMCEGR_CC2G_MSK                BIT2
#define PWMCEGR_CC1G_MSK                BIT1
#define PWMCEGR_UG_MSK                  BIT0
#define PWMC_GenerateBreakEvent()       SET_REG_BIT(PWMC_EGR, PWMCEGR_BG_MSK)
#define PWMC_GenerateTriggerEvent()     SET_REG_BIT(PWMC_EGR, PWMCEGR_TG_MSK)
#define PWMC_GenerateCOMEvent()         SET_REG_BIT(PWMC_EGR, PWMCEGR_COMG_MSK)
#define PWMC_GenerateCC4Event()         SET_REG_BIT(PWMC_EGR, PWMCEGR_CC4G_MSK)
#define PWMC_GenerateCC3Event()         SET_REG_BIT(PWMC_EGR, PWMCEGR_CC3G_MSK)
#define PWMC_GenerateCC2Event()         SET_REG_BIT(PWMC_EGR, PWMCEGR_CC2G_MSK)
#define PWMC_GenerateCC1Event()         SET_REG_BIT(PWMC_EGR, PWMCEGR_CC1G_MSK)
#define PWMC_GenerateUpdateEvent()      SET_REG_BIT(PWMC_EGR, PWMCEGR_UG_MSK)

#define HSPWMC_GenerateBreakEvent()     SET_HSPWMC_BIT(PWMC_EGR, PWMCEGR_BG_MSK)
#define HSPWMC_GenerateTriggerEvent()   SET_HSPWMC_BIT(PWMC_EGR, PWMCEGR_TG_MSK)
#define HSPWMC_GenerateCOMEvent()       SET_HSPWMC_BIT(PWMC_EGR, PWMCEGR_COMG_MSK)
#define HSPWMC_GenerateCC4Event()       SET_HSPWMC_BIT(PWMC_EGR, PWMCEGR_CC4G_MSK)
#define HSPWMC_GenerateCC3Event()       SET_HSPWMC_BIT(PWMC_EGR, PWMCEGR_CC3G_MSK)
#define HSPWMC_GenerateCC2Event()       SET_HSPWMC_BIT(PWMC_EGR, PWMCEGR_CC2G_MSK)
#define HSPWMC_GenerateCC1Event()       SET_HSPWMC_BIT(PWMC_EGR, PWMCEGR_CC1G_MSK)
#define HSPWMC_GenerateUpdateEvent()    SET_HSPWMC_BIT(PWMC_EGR, PWMCEGR_UG_MSK)

#define PWMCCCMR1_OC1CE_MSK             BIT7
#define PWMC_EnableETRFClearOC1REF()    SET_REG_BIT(PWMC_CCMR1, PWMCCCMR1_OC1CE_MSK)
#define PWMC_DisableETRFClearOC1REF()   CLR_REG_BIT(PWMC_CCMR1, PWMCCCMR1_OC1CE_MSK)

#define HSPWMC_EnableETRFClearOC1REF()  SET_HSPWMC_BIT(PWMC_CCMR1, PWMCCCMR1_OC1CE_MSK)
#define HSPWMC_DisableETRFClearOC1REF() CLR_HSPWMC_BIT(PWMC_CCMR1, PWMCCCMR1_OC1CE_MSK)

#define PWMCCCMR1_OC1M_MSK              (BIT6 | BIT5 | BIT4)
#define PWMCCCMR1X_OC1M3_MSK            BIT0
#define PWMC_SetOC1OutputMode(n)        MODIFY_REG(PWMC_CCMR1,  PWMCCCMR1_OC1M_MSK, ((n) << 4)); \
                                        MODIFY_REG(PWMC_CCMR1X, PWMCCCMR1X_OC1M3_MSK, (((n) >> 3) << 0))
#define PWMC_OC1REFFrozen()             PWMC_SetOC1OutputMode(0)
#define PWMC_OC1REFHighIfMatch()        PWMC_SetOC1OutputMode(1)
#define PWMC_OC1REFLowIfMatch()         PWMC_SetOC1OutputMode(2)
#define PWMC_OC1REFToggleIfMatch()      PWMC_SetOC1OutputMode(3)
#define PWMC_OC1REFForceLow()           PWMC_SetOC1OutputMode(4)
#define PWMC_OC1REFForceHigh()          PWMC_SetOC1OutputMode(5)
#define PWMC_OC1REFPWMMode1()           PWMC_SetOC1OutputMode(6)
#define PWMC_OC1REFPWMMode2()           PWMC_SetOC1OutputMode(7)
#define PWMC_OC1REFReTrigOPMPWM1()      PWMC_SetOC1OutputMode(8)
#define PWMC_OC1REFReTrigOPMPWM2()      PWMC_SetOC1OutputMode(9)
#define PWMC_OC1REFCombinedPWM1()       PWMC_SetOC1OutputMode(12)
#define PWMC_OC1REFCombinedPWM2()       PWMC_SetOC1OutputMode(13)
#define PWMC_OC1REFAsymmetricPWM1()     PWMC_SetOC1OutputMode(14)
#define PWMC_OC1REFAsymmetricPWM2()     PWMC_SetOC1OutputMode(15)

#define HSPWMC_SetOC1OutputMode(n)      MODIFY_HSPWMC(PWMC_CCMR1,  PWMCCCMR1_OC1M_MSK, ((n) << 4)); \
                                        MODIFY_HSPWMC(PWMC_CCMR1X, PWMCCCMR1X_OC1M3_MSK, (((n) >> 3) << 0))
#define HSPWMC_OC1REFFrozen()           HSPWMC_SetOC1OutputMode(0)
#define HSPWMC_OC1REFHighIfMatch()      HSPWMC_SetOC1OutputMode(1)
#define HSPWMC_OC1REFLowIfMatch()       HSPWMC_SetOC1OutputMode(2)
#define HSPWMC_OC1REFToggleIfMatch()    HSPWMC_SetOC1OutputMode(3)
#define HSPWMC_OC1REFForceLow()         HSPWMC_SetOC1OutputMode(4)
#define HSPWMC_OC1REFForceHigh()        HSPWMC_SetOC1OutputMode(5)
#define HSPWMC_OC1REFPWMMode1()         HSPWMC_SetOC1OutputMode(6)
#define HSPWMC_OC1REFPWMMode2()         HSPWMC_SetOC1OutputMode(7)
#define HSPWMC_OC1REFReTrigOPMPWM1()    HSPWMC_SetOC1OutputMode(8)
#define HSPWMC_OC1REFReTrigOPMPWM2()    HSPWMC_SetOC1OutputMode(9)
#define HSPWMC_OC1REFCombinedPWM1()     HSPWMC_SetOC1OutputMode(12)
#define HSPWMC_OC1REFCombinedPWM2()     HSPWMC_SetOC1OutputMode(13)
#define HSPWMC_OC1REFAsymmetricPWM1()   HSPWMC_SetOC1OutputMode(14)
#define HSPWMC_OC1REFAsymmetricPWM2()   HSPWMC_SetOC1OutputMode(15)

#define PWMCCCMR1_OC1PE_MSK             BIT3
#define PWMC_UnbufferCCR1()             CLR_REG_BIT(PWMC_CCMR1, PWMCCCMR1_OC1PE_MSK)
#define PWMC_BufferCCR1()               SET_REG_BIT(PWMC_CCMR1, PWMCCCMR1_OC1PE_MSK)

#define HSPWMC_UnbufferCCR1()           CLR_HSPWMC_BIT(PWMC_CCMR1, PWMCCCMR1_OC1PE_MSK)
#define HSPWMC_BufferCCR1()             SET_HSPWMC_BIT(PWMC_CCMR1, PWMCCCMR1_OC1PE_MSK)

#define PWMCCCMR1_OC1FE_MSK             BIT2
#define PWMC_DisableOC1FastMode()       CLR_REG_BIT(PWMC_CCMR1, PWMCCCMR1_OC1FE_MSK)
#define PWMC_EnableOC1FastMode()        SET_REG_BIT(PWMC_CCMR1, PWMCCCMR1_OC1FE_MSK)

#define HSPWMC_DisableOC1FastMode()     CLR_HSPWMC_BIT(PWMC_CCMR1, PWMCCCMR1_OC1FE_MSK)
#define HSPWMC_EnableOC1FastMode()      SET_HSPWMC_BIT(PWMC_CCMR1, PWMCCCMR1_OC1FE_MSK)

#define PWMCCCMR1_CC1S_MSK              (BIT1 | BIT0)
#define PWMC_SetCC1Mode(n)              MODIFY_REG(PWMC_CCMR1,  PWMCCCMR1_CC1S_MSK, ((n) << 0))
#define PWMC_CC1Output()                PWMC_SetCC1Mode(0)
#define PWMC_CC1CaptureTI1FP1()         PWMC_SetCC1Mode(1)
#define PWMC_CC1CaptureTI2FP1()         PWMC_SetCC1Mode(2)
#define PWMC_CC1CaptureTRC()            PWMC_SetCC1Mode(3)

#define HSPWMC_SetCC1Mode(n)            MODIFY_HSPWMC(PWMC_CCMR1,  PWMCCCMR1_CC1S_MSK, ((n) << 0))
#define HSPWMC_CC1Output()              HSPWMC_SetCC1Mode(0)
#define HSPWMC_CC1CaptureTI1FP1()       HSPWMC_SetCC1Mode(1)
#define HSPWMC_CC1CaptureTI2FP1()       HSPWMC_SetCC1Mode(2)
#define HSPWMC_CC1CaptureTRC()          HSPWMC_SetCC1Mode(3)

#define PWMCCCMR1_IC1F_MSK              (BIT_HN)
#define PWMC_SetIC1Filter(n)            MODIFY_REG(PWMC_CCMR1,  PWMCCCMR1_IC1F_MSK, ((n) << 4))
#define PWMC_IC1Filter1()               PWMC_SetIC1Filter(0)
#define PWMC_IC1Filter2()               PWMC_SetIC1Filter(1)
#define PWMC_IC1Filter4()               PWMC_SetIC1Filter(2)
#define PWMC_IC1Filter8()               PWMC_SetIC1Filter(3)
#define PWMC_IC1Filter12()              PWMC_SetIC1Filter(4)
#define PWMC_IC1Filter16()              PWMC_SetIC1Filter(5)
#define PWMC_IC1Filter24()              PWMC_SetIC1Filter(6)
#define PWMC_IC1Filter32()              PWMC_SetIC1Filter(7)
#define PWMC_IC1Filter48()              PWMC_SetIC1Filter(8)
#define PWMC_IC1Filter64()              PWMC_SetIC1Filter(9)
#define PWMC_IC1Filter80()              PWMC_SetIC1Filter(10)
#define PWMC_IC1Filter96()              PWMC_SetIC1Filter(11)
#define PWMC_IC1Filter128()             PWMC_SetIC1Filter(12)
#define PWMC_IC1Filter160()             PWMC_SetIC1Filter(13)
#define PWMC_IC1Filter192()             PWMC_SetIC1Filter(14)
#define PWMC_IC1Filter256()             PWMC_SetIC1Filter(15)

#define HSPWMC_SetIC1Filter(n)          MODIFY_HSPWMC(PWMC_CCMR1,  PWMCCCMR1_IC1F_MSK, ((n) << 4))
#define HSPWMC_IC1Filter1()             HSPWMC_SetIC1Filter(0)
#define HSPWMC_IC1Filter2()             HSPWMC_SetIC1Filter(1)
#define HSPWMC_IC1Filter4()             HSPWMC_SetIC1Filter(2)
#define HSPWMC_IC1Filter8()             HSPWMC_SetIC1Filter(3)
#define HSPWMC_IC1Filter12()            HSPWMC_SetIC1Filter(4)
#define HSPWMC_IC1Filter16()            HSPWMC_SetIC1Filter(5)
#define HSPWMC_IC1Filter24()            HSPWMC_SetIC1Filter(6)
#define HSPWMC_IC1Filter32()            HSPWMC_SetIC1Filter(7)
#define HSPWMC_IC1Filter48()            HSPWMC_SetIC1Filter(8)
#define HSPWMC_IC1Filter64()            HSPWMC_SetIC1Filter(9)
#define HSPWMC_IC1Filter80()            HSPWMC_SetIC1Filter(10)
#define HSPWMC_IC1Filter96()            HSPWMC_SetIC1Filter(11)
#define HSPWMC_IC1Filter128()           HSPWMC_SetIC1Filter(12)
#define HSPWMC_IC1Filter160()           HSPWMC_SetIC1Filter(13)
#define HSPWMC_IC1Filter192()           HSPWMC_SetIC1Filter(14)
#define HSPWMC_IC1Filter256()           HSPWMC_SetIC1Filter(15)

#define PWMCCCMR1_IC1PS_MSK             (BIT3 | BIT2)
#define PWMC_SetIC1Divider(n)           MODIFY_REG(PWMC_CCMR1,  PWMCCCMR1_IC1PS_MSK, ((n) << 2))
#define PWMC_IC1Divider1()              PWMC_SetIC1Divider(0)
#define PWMC_IC1Divider2()              PWMC_SetIC1Divider(1)
#define PWMC_IC1Divider4()              PWMC_SetIC1Divider(2)
#define PWMC_IC1Divider8()              PWMC_SetIC1Divider(3)

#define HSPWMC_SetIC1Divider(n)         MODIFY_HSPWMC(PWMC_CCMR1,  PWMCCCMR1_IC1PS_MSK, ((n) << 2))
#define HSPWMC_IC1Divider1()            HSPWMC_SetIC1Divider(0)
#define HSPWMC_IC1Divider2()            HSPWMC_SetIC1Divider(1)
#define HSPWMC_IC1Divider4()            HSPWMC_SetIC1Divider(2)
#define HSPWMC_IC1Divider8()            HSPWMC_SetIC1Divider(3)

#define PWMCCCMR2_OC2CE_MSK             BIT7
#define PWMC_EnableETRFClearOC2REF()    SET_REG_BIT(PWMC_CCMR2, PWMCCCMR2_OC2CE_MSK)
#define PWMC_DisableETRFClearOC2REF()   CLR_REG_BIT(PWMC_CCMR2, PWMCCCMR2_OC2CE_MSK)

#define HSPWMC_EnableETRFClearOC2REF()  SET_HSPWMC_BIT(PWMC_CCMR2, PWMCCCMR2_OC2CE_MSK)
#define HSPWMC_DisableETRFClearOC2REF() CLR_HSPWMC_BIT(PWMC_CCMR2, PWMCCCMR2_OC2CE_MSK)

#define PWMCCCMR2_OC2M_MSK              (BIT6 | BIT5 | BIT4)
#define PWMCCCMR2X_OC2M3_MSK            BIT0
#define PWMC_SetOC2OutputMode(n)        MODIFY_REG(PWMC_CCMR2,  PWMCCCMR2_OC2M_MSK, ((n) << 4)); \
                                        MODIFY_REG(PWMC_CCMR2X, PWMCCCMR2X_OC2M3_MSK, (((n) >> 3) << 0))
#define PWMC_OC2REFFrozen()             PWMC_SetOC2OutputMode(0)
#define PWMC_OC2REFHighIfMatch()        PWMC_SetOC2OutputMode(1)
#define PWMC_OC2REFLowIfMatch()         PWMC_SetOC2OutputMode(2)
#define PWMC_OC2REFToggleIfMatch()      PWMC_SetOC2OutputMode(3)
#define PWMC_OC2REFForceLow()           PWMC_SetOC2OutputMode(4)
#define PWMC_OC2REFForceHigh()          PWMC_SetOC2OutputMode(5)
#define PWMC_OC2REFPWMMode1()           PWMC_SetOC2OutputMode(6)
#define PWMC_OC2REFPWMMode2()           PWMC_SetOC2OutputMode(7)
#define PWMC_OC2REFReTrigOPMPWM1()      PWMC_SetOC2OutputMode(8)
#define PWMC_OC2REFReTrigOPMPWM2()      PWMC_SetOC2OutputMode(9)
#define PWMC_OC2REFCombinedPWM1()       PWMC_SetOC2OutputMode(12)
#define PWMC_OC2REFCombinedPWM2()       PWMC_SetOC2OutputMode(13)
#define PWMC_OC2REFAsymmetricPWM1()     PWMC_SetOC2OutputMode(14)
#define PWMC_OC2REFAsymmetricPWM2()     PWMC_SetOC2OutputMode(15)

#define HSPWMC_SetOC2OutputMode(n)      MODIFY_HSPWMC(PWMC_CCMR2,  PWMCCCMR2_OC2M_MSK, ((n) << 4)); \
                                        MODIFY_HSPWMC(PWMC_CCMR2X, PWMCCCMR2X_OC2M3_MSK, (((n) >> 3) << 0))
#define HSPWMC_OC2REFFrozen()           HSPWMC_SetOC2OutputMode(0)
#define HSPWMC_OC2REFHighIfMatch()      HSPWMC_SetOC2OutputMode(1)
#define HSPWMC_OC2REFLowIfMatch()       HSPWMC_SetOC2OutputMode(2)
#define HSPWMC_OC2REFToggleIfMatch()    HSPWMC_SetOC2OutputMode(3)
#define HSPWMC_OC2REFForceLow()         HSPWMC_SetOC2OutputMode(4)
#define HSPWMC_OC2REFForceHigh()        HSPWMC_SetOC2OutputMode(5)
#define HSPWMC_OC2REFPWMMode1()         HSPWMC_SetOC2OutputMode(6)
#define HSPWMC_OC2REFPWMMode2()         HSPWMC_SetOC2OutputMode(7)
#define HSPWMC_OC2REFReTrigOPMPWM1()    HSPWMC_SetOC2OutputMode(8)
#define HSPWMC_OC2REFReTrigOPMPWM2()    HSPWMC_SetOC2OutputMode(9)
#define HSPWMC_OC2REFCombinedPWM1()     HSPWMC_SetOC2OutputMode(12)
#define HSPWMC_OC2REFCombinedPWM2()     HSPWMC_SetOC2OutputMode(13)
#define HSPWMC_OC2REFAsymmetricPWM1()   HSPWMC_SetOC2OutputMode(14)
#define HSPWMC_OC2REFAsymmetricPWM2()   HSPWMC_SetOC2OutputMode(15)

#define PWMCCCMR2_OC2PE_MSK             BIT3
#define PWMC_UnbufferCCR2()             CLR_REG_BIT(PWMC_CCMR2, PWMCCCMR2_OC2PE_MSK)
#define PWMC_BufferCCR2()               SET_REG_BIT(PWMC_CCMR2, PWMCCCMR2_OC2PE_MSK)

#define HSPWMC_UnbufferCCR2()           CLR_HSPWMC_BIT(PWMC_CCMR2, PWMCCCMR2_OC2PE_MSK)
#define HSPWMC_BufferCCR2()             SET_HSPWMC_BIT(PWMC_CCMR2, PWMCCCMR2_OC2PE_MSK)

#define PWMCCCMR2_OC2FE_MSK             BIT2
#define PWMC_DisableOC2FastMode()       CLR_REG_BIT(PWMC_CCMR2, PWMCCCMR2_OC2FE_MSK)
#define PWMC_EnableOC2FastMode()        SET_REG_BIT(PWMC_CCMR2, PWMCCCMR2_OC2FE_MSK)

#define HSPWMC_DisableOC2FastMode()     CLR_HSPWMC_BIT(PWMC_CCMR2, PWMCCCMR2_OC2FE_MSK)
#define HSPWMC_EnableOC2FastMode()      SET_HSPWMC_BIT(PWMC_CCMR2, PWMCCCMR2_OC2FE_MSK)

#define PWMCCCMR2_CC2S_MSK              (BIT1 | BIT0)
#define PWMC_SetCC2Mode(n)              MODIFY_REG(PWMC_CCMR2,  PWMCCCMR2_CC2S_MSK, ((n) << 0))
#define PWMC_CC2Output()                PWMC_SetCC2Mode(0)
#define PWMC_CC2CaptureTI2FP2()         PWMC_SetCC2Mode(1)
#define PWMC_CC2CaptureTI1FP2()         PWMC_SetCC2Mode(2)
#define PWMC_CC2CaptureTRC()            PWMC_SetCC2Mode(3)

#define HSPWMC_SetCC2Mode(n)            MODIFY_HSPWMC(PWMC_CCMR2,  PWMCCCMR2_CC2S_MSK, ((n) << 0))
#define HSPWMC_CC2Output()              HSPWMC_SetCC2Mode(0)
#define HSPWMC_CC2CaptureTI2FP2()       HSPWMC_SetCC2Mode(1)
#define HSPWMC_CC2CaptureTI1FP2()       HSPWMC_SetCC2Mode(2)
#define HSPWMC_CC2CaptureTRC()          HSPWMC_SetCC2Mode(3)

#define PWMCCCMR2_IC2F_MSK              (BIT_HN)
#define PWMC_SetIC2Filter(n)            MODIFY_REG(PWMC_CCMR2,  PWMCCCMR2_IC2F_MSK, ((n) << 4))
#define PWMC_IC2Filter1()               PWMC_SetIC2Filter(0)
#define PWMC_IC2Filter2()               PWMC_SetIC2Filter(1)
#define PWMC_IC2Filter4()               PWMC_SetIC2Filter(2)
#define PWMC_IC2Filter8()               PWMC_SetIC2Filter(3)
#define PWMC_IC2Filter12()              PWMC_SetIC2Filter(4)
#define PWMC_IC2Filter16()              PWMC_SetIC2Filter(5)
#define PWMC_IC2Filter24()              PWMC_SetIC2Filter(6)
#define PWMC_IC2Filter32()              PWMC_SetIC2Filter(7)
#define PWMC_IC2Filter48()              PWMC_SetIC2Filter(8)
#define PWMC_IC2Filter64()              PWMC_SetIC2Filter(9)
#define PWMC_IC2Filter80()              PWMC_SetIC2Filter(10)
#define PWMC_IC2Filter96()              PWMC_SetIC2Filter(11)
#define PWMC_IC2Filter128()             PWMC_SetIC2Filter(12)
#define PWMC_IC2Filter160()             PWMC_SetIC2Filter(13)
#define PWMC_IC2Filter192()             PWMC_SetIC2Filter(14)
#define PWMC_IC2Filter256()             PWMC_SetIC2Filter(15)

#define HSPWMC_SetIC2Filter(n)          MODIFY_HSPWMC(PWMC_CCMR2,  PWMCCCMR2_IC2F_MSK, ((n) << 4))
#define HSPWMC_IC2Filter1()             HSPWMC_SetIC2Filter(0)
#define HSPWMC_IC2Filter2()             HSPWMC_SetIC2Filter(1)
#define HSPWMC_IC2Filter4()             HSPWMC_SetIC2Filter(2)
#define HSPWMC_IC2Filter8()             HSPWMC_SetIC2Filter(3)
#define HSPWMC_IC2Filter12()            HSPWMC_SetIC2Filter(4)
#define HSPWMC_IC2Filter16()            HSPWMC_SetIC2Filter(5)
#define HSPWMC_IC2Filter24()            HSPWMC_SetIC2Filter(6)
#define HSPWMC_IC2Filter32()            HSPWMC_SetIC2Filter(7)
#define HSPWMC_IC2Filter48()            HSPWMC_SetIC2Filter(8)
#define HSPWMC_IC2Filter64()            HSPWMC_SetIC2Filter(9)
#define HSPWMC_IC2Filter80()            HSPWMC_SetIC2Filter(10)
#define HSPWMC_IC2Filter96()            HSPWMC_SetIC2Filter(11)
#define HSPWMC_IC2Filter128()           HSPWMC_SetIC2Filter(12)
#define HSPWMC_IC2Filter160()           HSPWMC_SetIC2Filter(13)
#define HSPWMC_IC2Filter192()           HSPWMC_SetIC2Filter(14)
#define HSPWMC_IC2Filter256()           HSPWMC_SetIC2Filter(15)

#define PWMCCCMR2_IC2PS_MSK             (BIT3 | BIT2)
#define PWMC_SetIC2Divider(n)           MODIFY_REG(PWMC_CCMR2,  PWMCCCMR2_IC2PS_MSK, ((n) << 2))
#define PWMC_IC2Divider1()              PWMC_SetIC2Divider(0)
#define PWMC_IC2Divider2()              PWMC_SetIC2Divider(1)
#define PWMC_IC2Divider4()              PWMC_SetIC2Divider(2)
#define PWMC_IC2Divider8()              PWMC_SetIC2Divider(3)

#define HSPWMC_SetIC2Divider(n)         MODIFY_HSPWMC(PWMC_CCMR2,  PWMCCCMR2_IC2PS_MSK, ((n) << 2))
#define HSPWMC_IC2Divider1()            HSPWMC_SetIC2Divider(0)
#define HSPWMC_IC2Divider2()            HSPWMC_SetIC2Divider(1)
#define HSPWMC_IC2Divider4()            HSPWMC_SetIC2Divider(2)
#define HSPWMC_IC2Divider8()            HSPWMC_SetIC2Divider(3)

#define PWMCCCMR3_OC3CE_MSK             BIT7
#define PWMC_EnableETRFClearOC3REF()    SET_REG_BIT(PWMC_CCMR3, PWMCCCMR3_OC3CE_MSK)
#define PWMC_DisableETRFClearOC3REF()   CLR_REG_BIT(PWMC_CCMR3, PWMCCCMR3_OC3CE_MSK)

#define HSPWMC_EnableETRFClearOC3REF()  SET_HSPWMC_BIT(PWMC_CCMR3, PWMCCCMR3_OC3CE_MSK)
#define HSPWMC_DisableETRFClearOC3REF() CLR_HSPWMC_BIT(PWMC_CCMR3, PWMCCCMR3_OC3CE_MSK)

#define PWMCCCMR3_OC3M_MSK              (BIT6 | BIT5 | BIT4)
#define PWMCCCMR3X_OC3M3_MSK            BIT0
#define PWMC_SetOC3OutputMode(n)        MODIFY_REG(PWMC_CCMR3,  PWMCCCMR3_OC3M_MSK, ((n) << 4)); \
                                        MODIFY_REG(PWMC_CCMR3X, PWMCCCMR3X_OC3M3_MSK, (((n) >> 3) << 0))
#define PWMC_OC3REFFrozen()             PWMC_SetOC3OutputMode(0)
#define PWMC_OC3REFHighIfMatch()        PWMC_SetOC3OutputMode(1)
#define PWMC_OC3REFLowIfMatch()         PWMC_SetOC3OutputMode(2)
#define PWMC_OC3REFToggleIfMatch()      PWMC_SetOC3OutputMode(3)
#define PWMC_OC3REFForceLow()           PWMC_SetOC3OutputMode(4)
#define PWMC_OC3REFForceHigh()          PWMC_SetOC3OutputMode(5)
#define PWMC_OC3REFPWMMode1()           PWMC_SetOC3OutputMode(6)
#define PWMC_OC3REFPWMMode2()           PWMC_SetOC3OutputMode(7)
#define PWMC_OC3REFReTrigOPMPWM1()      PWMC_SetOC3OutputMode(8)
#define PWMC_OC3REFReTrigOPMPWM2()      PWMC_SetOC3OutputMode(9)
#define PWMC_OC3REFCombinedPWM1()       PWMC_SetOC3OutputMode(12)
#define PWMC_OC3REFCombinedPWM2()       PWMC_SetOC3OutputMode(13)
#define PWMC_OC3REFAsymmetricPWM1()     PWMC_SetOC3OutputMode(14)
#define PWMC_OC3REFAsymmetricPWM2()     PWMC_SetOC3OutputMode(15)

#define HSPWMC_SetOC3OutputMode(n)      MODIFY_HSPWMC(PWMC_CCMR3,  PWMCCCMR3_OC3M_MSK, ((n) << 4)); \
                                        MODIFY_HSPWMC(PWMC_CCMR3X, PWMCCCMR3X_OC3M3_MSK, (((n) >> 3) << 0))
#define HSPWMC_OC3REFFrozen()           HSPWMC_SetOC3OutputMode(0)
#define HSPWMC_OC3REFHighIfMatch()      HSPWMC_SetOC3OutputMode(1)
#define HSPWMC_OC3REFLowIfMatch()       HSPWMC_SetOC3OutputMode(2)
#define HSPWMC_OC3REFToggleIfMatch()    HSPWMC_SetOC3OutputMode(3)
#define HSPWMC_OC3REFForceLow()         HSPWMC_SetOC3OutputMode(4)
#define HSPWMC_OC3REFForceHigh()        HSPWMC_SetOC3OutputMode(5)
#define HSPWMC_OC3REFPWMMode1()         HSPWMC_SetOC3OutputMode(6)
#define HSPWMC_OC3REFPWMMode2()         HSPWMC_SetOC3OutputMode(7)
#define HSPWMC_OC3REFReTrigOPMPWM1()    HSPWMC_SetOC3OutputMode(8)
#define HSPWMC_OC3REFReTrigOPMPWM2()    HSPWMC_SetOC3OutputMode(9)
#define HSPWMC_OC3REFCombinedPWM1()     HSPWMC_SetOC3OutputMode(12)
#define HSPWMC_OC3REFCombinedPWM2()     HSPWMC_SetOC3OutputMode(13)
#define HSPWMC_OC3REFAsymmetricPWM1()   HSPWMC_SetOC3OutputMode(14)
#define HSPWMC_OC3REFAsymmetricPWM2()   HSPWMC_SetOC3OutputMode(15)

#define PWMCCCMR3_OC3PE_MSK             BIT3
#define PWMC_UnbufferCCR3()             CLR_REG_BIT(PWMC_CCMR3, PWMCCCMR3_OC3PE_MSK)
#define PWMC_BufferCCR3()               SET_REG_BIT(PWMC_CCMR3, PWMCCCMR3_OC3PE_MSK)

#define HSPWMC_UnbufferCCR3()           CLR_HSPWMC_BIT(PWMC_CCMR3, PWMCCCMR3_OC3PE_MSK)
#define HSPWMC_BufferCCR3()             SET_HSPWMC_BIT(PWMC_CCMR3, PWMCCCMR3_OC3PE_MSK)

#define PWMCCCMR3_OC3FE_MSK             BIT2
#define PWMC_DisableOC3FastMode()       CLR_REG_BIT(PWMC_CCMR3, PWMCCCMR3_OC3FE_MSK)
#define PWMC_EnableOC3FastMode()        SET_REG_BIT(PWMC_CCMR3, PWMCCCMR3_OC3FE_MSK)

#define HSPWMC_DisableOC3FastMode()     CLR_HSPWMC_BIT(PWMC_CCMR3, PWMCCCMR3_OC3FE_MSK)
#define HSPWMC_EnableOC3FastMode()      SET_HSPWMC_BIT(PWMC_CCMR3, PWMCCCMR3_OC3FE_MSK)

#define PWMCCCMR3_CC3S_MSK              (BIT1 | BIT0)
#define PWMC_SetCC3Mode(n)              MODIFY_REG(PWMC_CCMR3,  PWMCCCMR3_CC3S_MSK, ((n) << 0))
#define PWMC_CC3Output()                PWMC_SetCC3Mode(0)
#define PWMC_CC3CaptureTI3FP3()         PWMC_SetCC3Mode(1)
#define PWMC_CC3CaptureTI4FP3()         PWMC_SetCC3Mode(2)
#define PWMC_CC3CaptureTRC()            PWMC_SetCC3Mode(3)

#define HSPWMC_SetCC3Mode(n)            MODIFY_HSPWMC(PWMC_CCMR3,  PWMCCCMR3_CC3S_MSK, ((n) << 0))
#define HSPWMC_CC3Output()              HSPWMC_SetCC3Mode(0)
#define HSPWMC_CC3CaptureTI3FP3()       HSPWMC_SetCC3Mode(1)
#define HSPWMC_CC3CaptureTI4FP3()       HSPWMC_SetCC3Mode(2)
#define HSPWMC_CC3CaptureTRC()          HSPWMC_SetCC3Mode(3)

#define PWMCCCMR3_IC3F_MSK              (BIT_HN)
#define PWMC_SetIC3Filter(n)            MODIFY_REG(PWMC_CCMR3,  PWMCCCMR3_IC3F_MSK, ((n) << 4))
#define PWMC_IC3Filter1()               PWMC_SetIC3Filter(0)
#define PWMC_IC3Filter2()               PWMC_SetIC3Filter(1)
#define PWMC_IC3Filter4()               PWMC_SetIC3Filter(2)
#define PWMC_IC3Filter8()               PWMC_SetIC3Filter(3)
#define PWMC_IC3Filter12()              PWMC_SetIC3Filter(4)
#define PWMC_IC3Filter16()              PWMC_SetIC3Filter(5)
#define PWMC_IC3Filter24()              PWMC_SetIC3Filter(6)
#define PWMC_IC3Filter32()              PWMC_SetIC3Filter(7)
#define PWMC_IC3Filter48()              PWMC_SetIC3Filter(8)
#define PWMC_IC3Filter64()              PWMC_SetIC3Filter(9)
#define PWMC_IC3Filter80()              PWMC_SetIC3Filter(10)
#define PWMC_IC3Filter96()              PWMC_SetIC3Filter(11)
#define PWMC_IC3Filter128()             PWMC_SetIC3Filter(12)
#define PWMC_IC3Filter160()             PWMC_SetIC3Filter(13)
#define PWMC_IC3Filter192()             PWMC_SetIC3Filter(14)
#define PWMC_IC3Filter256()             PWMC_SetIC3Filter(15)

#define HSPWMC_SetIC3Filter(n)          MODIFY_HSPWMC(PWMC_CCMR3,  PWMCCCMR3_IC3F_MSK, ((n) << 4))
#define HSPWMC_IC3Filter1()             HSPWMC_SetIC3Filter(0)
#define HSPWMC_IC3Filter2()             HSPWMC_SetIC3Filter(1)
#define HSPWMC_IC3Filter4()             HSPWMC_SetIC3Filter(2)
#define HSPWMC_IC3Filter8()             HSPWMC_SetIC3Filter(3)
#define HSPWMC_IC3Filter12()            HSPWMC_SetIC3Filter(4)
#define HSPWMC_IC3Filter16()            HSPWMC_SetIC3Filter(5)
#define HSPWMC_IC3Filter24()            HSPWMC_SetIC3Filter(6)
#define HSPWMC_IC3Filter32()            HSPWMC_SetIC3Filter(7)
#define HSPWMC_IC3Filter48()            HSPWMC_SetIC3Filter(8)
#define HSPWMC_IC3Filter64()            HSPWMC_SetIC3Filter(9)
#define HSPWMC_IC3Filter80()            HSPWMC_SetIC3Filter(10)
#define HSPWMC_IC3Filter96()            HSPWMC_SetIC3Filter(11)
#define HSPWMC_IC3Filter128()           HSPWMC_SetIC3Filter(12)
#define HSPWMC_IC3Filter160()           HSPWMC_SetIC3Filter(13)
#define HSPWMC_IC3Filter192()           HSPWMC_SetIC3Filter(14)
#define HSPWMC_IC3Filter256()           HSPWMC_SetIC3Filter(15)

#define PWMCCCMR3_IC3PS_MSK             (BIT3 | BIT2)
#define PWMC_SetIC3Divider(n)           MODIFY_REG(PWMC_CCMR3,  PWMCCCMR3_IC3PS_MSK, ((n) << 2))
#define PWMC_IC3Divider1()              PWMC_SetIC3Divider(0)
#define PWMC_IC3Divider2()              PWMC_SetIC3Divider(1)
#define PWMC_IC3Divider4()              PWMC_SetIC3Divider(2)
#define PWMC_IC3Divider8()              PWMC_SetIC3Divider(3)

#define HSPWMC_SetIC3Divider(n)         MODIFY_HSPWMC(PWMC_CCMR3,  PWMCCCMR3_IC3PS_MSK, ((n) << 2))
#define HSPWMC_IC3Divider1()            HSPWMC_SetIC3Divider(0)
#define HSPWMC_IC3Divider2()            HSPWMC_SetIC3Divider(1)
#define HSPWMC_IC3Divider4()            HSPWMC_SetIC3Divider(2)
#define HSPWMC_IC3Divider8()            HSPWMC_SetIC3Divider(3)

#define PWMCCCMR4_OC4CE_MSK             BIT7
#define PWMC_EnableETRFClearOC4REF()    SET_REG_BIT(PWMC_CCMR4, PWMCCCMR4_OC4CE_MSK)
#define PWMC_DisableETRFClearOC4REF()   CLR_REG_BIT(PWMC_CCMR4, PWMCCCMR4_OC4CE_MSK)

#define HSPWMC_EnableETRFClearOC4REF()  SET_HSPWMC_BIT(PWMC_CCMR4, PWMCCCMR4_OC4CE_MSK)
#define HSPWMC_DisableETRFClearOC4REF() CLR_HSPWMC_BIT(PWMC_CCMR4, PWMCCCMR4_OC4CE_MSK)

#define PWMCCCMR4_OC4M_MSK              (BIT6 | BIT5 | BIT4)
#define PWMCCCMR4X_OC4M3_MSK            BIT0
#define PWMC_SetOC4OutputMode(n)        MODIFY_REG(PWMC_CCMR4,  PWMCCCMR4_OC4M_MSK, ((n) << 4)); \
                                        MODIFY_REG(PWMC_CCMR4X, PWMCCCMR4X_OC4M3_MSK, (((n) >> 3) << 0))
#define PWMC_OC4REFFrozen()             PWMC_SetOC4OutputMode(0)
#define PWMC_OC4REFHighIfMatch()        PWMC_SetOC4OutputMode(1)
#define PWMC_OC4REFLowIfMatch()         PWMC_SetOC4OutputMode(2)
#define PWMC_OC4REFToggleIfMatch()      PWMC_SetOC4OutputMode(3)
#define PWMC_OC4REFForceLow()           PWMC_SetOC4OutputMode(4)
#define PWMC_OC4REFForceHigh()          PWMC_SetOC4OutputMode(5)
#define PWMC_OC4REFPWMMode1()           PWMC_SetOC4OutputMode(6)
#define PWMC_OC4REFPWMMode2()           PWMC_SetOC4OutputMode(7)
#define PWMC_OC4REFReTrigOPMPWM1()      PWMC_SetOC4OutputMode(8)
#define PWMC_OC4REFReTrigOPMPWM2()      PWMC_SetOC4OutputMode(9)
#define PWMC_OC4REFCombinedPWM1()       PWMC_SetOC4OutputMode(12)
#define PWMC_OC4REFCombinedPWM2()       PWMC_SetOC4OutputMode(13)
#define PWMC_OC4REFAsymmetricPWM1()     PWMC_SetOC4OutputMode(14)
#define PWMC_OC4REFAsymmetricPWM2()     PWMC_SetOC4OutputMode(15)

#define HSPWMC_SetOC4OutputMode(n)      MODIFY_HSPWMC(PWMC_CCMR4,  PWMCCCMR4_OC4M_MSK, ((n) << 4)); \
                                        MODIFY_HSPWMC(PWMC_CCMR4X, PWMCCCMR4X_OC4M3_MSK, (((n) >> 3) << 0))
#define HSPWMC_OC4REFFrozen()           HSPWMC_SetOC4OutputMode(0)
#define HSPWMC_OC4REFHighIfMatch()      HSPWMC_SetOC4OutputMode(1)
#define HSPWMC_OC4REFLowIfMatch()       HSPWMC_SetOC4OutputMode(2)
#define HSPWMC_OC4REFToggleIfMatch()    HSPWMC_SetOC4OutputMode(3)
#define HSPWMC_OC4REFForceLow()         HSPWMC_SetOC4OutputMode(4)
#define HSPWMC_OC4REFForceHigh()        HSPWMC_SetOC4OutputMode(5)
#define HSPWMC_OC4REFPWMMode1()         HSPWMC_SetOC4OutputMode(6)
#define HSPWMC_OC4REFPWMMode2()         HSPWMC_SetOC4OutputMode(7)
#define HSPWMC_OC4REFReTrigOPMPWM1()    HSPWMC_SetOC4OutputMode(8)
#define HSPWMC_OC4REFReTrigOPMPWM2()    HSPWMC_SetOC4OutputMode(9)
#define HSPWMC_OC4REFCombinedPWM1()     HSPWMC_SetOC4OutputMode(12)
#define HSPWMC_OC4REFCombinedPWM2()     HSPWMC_SetOC4OutputMode(13)
#define HSPWMC_OC4REFAsymmetricPWM1()   HSPWMC_SetOC4OutputMode(14)
#define HSPWMC_OC4REFAsymmetricPWM2()   HSPWMC_SetOC4OutputMode(15)

#define PWMCCCMR4_OC4PE_MSK             BIT3
#define PWMC_UnbufferCCR4()             CLR_REG_BIT(PWMC_CCMR4, PWMCCCMR4_OC4PE_MSK)
#define PWMC_BufferCCR4()               SET_REG_BIT(PWMC_CCMR4, PWMCCCMR4_OC4PE_MSK)

#define HSPWMC_UnbufferCCR4()           CLR_HSPWMC_BIT(PWMC_CCMR4, PWMCCCMR4_OC4PE_MSK)
#define HSPWMC_BufferCCR4()             SET_HSPWMC_BIT(PWMC_CCMR4, PWMCCCMR4_OC4PE_MSK)

#define PWMCCCMR4_OC4FE_MSK             BIT2
#define PWMC_DisableOC4FastMode()       CLR_REG_BIT(PWMC_CCMR4, PWMCCCMR4_OC4FE_MSK)
#define PWMC_EnableOC4FastMode()        SET_REG_BIT(PWMC_CCMR4, PWMCCCMR4_OC4FE_MSK)

#define HSPWMC_DisableOC4FastMode()     CLR_HSPWMC_BIT(PWMC_CCMR4, PWMCCCMR4_OC4FE_MSK)
#define HSPWMC_EnableOC4FastMode()      SET_HSPWMC_BIT(PWMC_CCMR4, PWMCCCMR4_OC4FE_MSK)

#define PWMCCCMR4_CC4S_MSK              (BIT1 | BIT0)
#define PWMC_SetCC4Mode(n)              MODIFY_REG(PWMC_CCMR4,  PWMCCCMR4_CC4S_MSK, ((n) << 0))
#define PWMC_CC4Output()                PWMC_SetCC4Mode(0)
#define PWMC_CC4CaptureTI4FP4()         PWMC_SetCC4Mode(1)
#define PWMC_CC4CaptureTI3FP4()         PWMC_SetCC4Mode(2)
#define PWMC_CC4CaptureTRC()            PWMC_SetCC4Mode(3)

#define HSPWMC_SetCC4Mode(n)            MODIFY_HSPWMC(PWMC_CCMR4,  PWMCCCMR4_CC4S_MSK, ((n) << 0))
#define HSPWMC_CC4Output()              HSPWMC_SetCC4Mode(0)
#define HSPWMC_CC4CaptureTI4FP4()       HSPWMC_SetCC4Mode(1)
#define HSPWMC_CC4CaptureTI3FP4()       HSPWMC_SetCC4Mode(2)
#define HSPWMC_CC4CaptureTRC()          HSPWMC_SetCC4Mode(3)

#define PWMCCCMR4_IC4F_MSK              (BIT_HN)
#define PWMC_SetIC4Filter(n)            MODIFY_REG(PWMC_CCMR4,  PWMCCCMR4_IC4F_MSK, ((n) << 4))
#define PWMC_IC4Filter1()               PWMC_SetIC4Filter(0)
#define PWMC_IC4Filter2()               PWMC_SetIC4Filter(1)
#define PWMC_IC4Filter4()               PWMC_SetIC4Filter(2)
#define PWMC_IC4Filter8()               PWMC_SetIC4Filter(3)
#define PWMC_IC4Filter12()              PWMC_SetIC4Filter(4)
#define PWMC_IC4Filter16()              PWMC_SetIC4Filter(5)
#define PWMC_IC4Filter24()              PWMC_SetIC4Filter(6)
#define PWMC_IC4Filter32()              PWMC_SetIC4Filter(7)
#define PWMC_IC4Filter48()              PWMC_SetIC4Filter(8)
#define PWMC_IC4Filter64()              PWMC_SetIC4Filter(9)
#define PWMC_IC4Filter80()              PWMC_SetIC4Filter(10)
#define PWMC_IC4Filter96()              PWMC_SetIC4Filter(11)
#define PWMC_IC4Filter128()             PWMC_SetIC4Filter(12)
#define PWMC_IC4Filter160()             PWMC_SetIC4Filter(13)
#define PWMC_IC4Filter192()             PWMC_SetIC4Filter(14)
#define PWMC_IC4Filter256()             PWMC_SetIC4Filter(15)

#define HSPWMC_SetIC4Filter(n)          MODIFY_HSPWMC(PWMC_CCMR4,  PWMCCCMR4_IC4F_MSK, ((n) << 4))
#define HSPWMC_IC4Filter1()             HSPWMC_SetIC4Filter(0)
#define HSPWMC_IC4Filter2()             HSPWMC_SetIC4Filter(1)
#define HSPWMC_IC4Filter4()             HSPWMC_SetIC4Filter(2)
#define HSPWMC_IC4Filter8()             HSPWMC_SetIC4Filter(3)
#define HSPWMC_IC4Filter12()            HSPWMC_SetIC4Filter(4)
#define HSPWMC_IC4Filter16()            HSPWMC_SetIC4Filter(5)
#define HSPWMC_IC4Filter24()            HSPWMC_SetIC4Filter(6)
#define HSPWMC_IC4Filter32()            HSPWMC_SetIC4Filter(7)
#define HSPWMC_IC4Filter48()            HSPWMC_SetIC4Filter(8)
#define HSPWMC_IC4Filter64()            HSPWMC_SetIC4Filter(9)
#define HSPWMC_IC4Filter80()            HSPWMC_SetIC4Filter(10)
#define HSPWMC_IC4Filter96()            HSPWMC_SetIC4Filter(11)
#define HSPWMC_IC4Filter128()           HSPWMC_SetIC4Filter(12)
#define HSPWMC_IC4Filter160()           HSPWMC_SetIC4Filter(13)
#define HSPWMC_IC4Filter192()           HSPWMC_SetIC4Filter(14)
#define HSPWMC_IC4Filter256()           HSPWMC_SetIC4Filter(15)

#define PWMCCCMR4_IC4PS_MSK             (BIT3 | BIT2)
#define PWMC_SetIC4Divider(n)           MODIFY_REG(PWMC_CCMR4,  PWMCCCMR4_IC4PS_MSK, ((n) << 2))
#define PWMC_IC4Divider1()              PWMC_SetIC4Divider(0)
#define PWMC_IC4Divider2()              PWMC_SetIC4Divider(1)
#define PWMC_IC4Divider4()              PWMC_SetIC4Divider(2)
#define PWMC_IC4Divider8()              PWMC_SetIC4Divider(3)

#define HSPWMC_SetIC4Divider(n)         MODIFY_HSPWMC(PWMC_CCMR4,  PWMCCCMR4_IC4PS_MSK, ((n) << 2))
#define HSPWMC_IC4Divider1()            HSPWMC_SetIC4Divider(0)
#define HSPWMC_IC4Divider2()            HSPWMC_SetIC4Divider(1)
#define HSPWMC_IC4Divider4()            HSPWMC_SetIC4Divider(2)
#define HSPWMC_IC4Divider8()            HSPWMC_SetIC4Divider(3)

#define PWMCCCMR5_OC5CE_MSK             BIT7
#define PWMC_EnableETRFClearOC5REF()    SET_REG_BIT(PWMC_CCMR5, PWMCCCMR5_OC5CE_MSK)
#define PWMC_DisableETRFClearOC5REF()   CLR_REG_BIT(PWMC_CCMR5, PWMCCCMR5_OC5CE_MSK)

#define HSPWMC_EnableETRFClearOC5REF()  SET_HSPWMC_BIT(PWMC_CCMR5, PWMCCCMR5_OC5CE_MSK)
#define HSPWMC_DisableETRFClearOC5REF() CLR_HSPWMC_BIT(PWMC_CCMR5, PWMCCCMR5_OC5CE_MSK)

#define PWMCCCMR5_OC5M_MSK              (BIT6 | BIT5 | BIT4)
#define PWMCCCMR5X_OC5M3_MSK            BIT0
#define PWMC_SetOC5OutputMode(n)        MODIFY_REG(PWMC_CCMR5,  PWMCCCMR5_OC5M_MSK, ((n) << 4)); \
                                        MODIFY_REG(PWMC_CCMR5X, PWMCCCMR5X_OC5M3_MSK, (((n) >> 3) << 0))
#define PWMC_OC5REFFrozen()             PWMC_SetOC5OutputMode(0)
#define PWMC_OC5REFHighIfMatch()        PWMC_SetOC5OutputMode(1)
#define PWMC_OC5REFLowIfMatch()         PWMC_SetOC5OutputMode(2)
#define PWMC_OC5REFToggleIfMatch()      PWMC_SetOC5OutputMode(3)
#define PWMC_OC5REFForceLow()           PWMC_SetOC5OutputMode(4)
#define PWMC_OC5REFForceHigh()          PWMC_SetOC5OutputMode(5)
#define PWMC_OC5REFPWMMode1()           PWMC_SetOC5OutputMode(6)
#define PWMC_OC5REFPWMMode2()           PWMC_SetOC5OutputMode(7)
#define PWMC_OC5REFReTrigOPMPWM1()      PWMC_SetOC5OutputMode(8)
#define PWMC_OC5REFReTrigOPMPWM2()      PWMC_SetOC5OutputMode(9)
#define PWMC_OC5REFCombinedPWM1()       PWMC_SetOC5OutputMode(12)
#define PWMC_OC5REFCombinedPWM2()       PWMC_SetOC5OutputMode(13)
#define PWMC_OC5REFAsymmetricPWM1()     PWMC_SetOC5OutputMode(14)
#define PWMC_OC5REFAsymmetricPWM2()     PWMC_SetOC5OutputMode(15)

#define HSPWMC_SetOC5OutputMode(n)      MODIFY_HSPWMC(PWMC_CCMR5,  PWMCCCMR5_OC5M_MSK, ((n) << 4)); \
                                        MODIFY_HSPWMC(PWMC_CCMR5X, PWMCCCMR5X_OC5M3_MSK, (((n) >> 3) << 0))
#define HSPWMC_OC5REFFrozen()           HSPWMC_SetOC5OutputMode(0)
#define HSPWMC_OC5REFHighIfMatch()      HSPWMC_SetOC5OutputMode(1)
#define HSPWMC_OC5REFLowIfMatch()       HSPWMC_SetOC5OutputMode(2)
#define HSPWMC_OC5REFToggleIfMatch()    HSPWMC_SetOC5OutputMode(3)
#define HSPWMC_OC5REFForceLow()         HSPWMC_SetOC5OutputMode(4)
#define HSPWMC_OC5REFForceHigh()        HSPWMC_SetOC5OutputMode(5)
#define HSPWMC_OC5REFPWMMode1()         HSPWMC_SetOC5OutputMode(6)
#define HSPWMC_OC5REFPWMMode2()         HSPWMC_SetOC5OutputMode(7)
#define HSPWMC_OC5REFReTrigOPMPWM1()    HSPWMC_SetOC5OutputMode(8)
#define HSPWMC_OC5REFReTrigOPMPWM2()    HSPWMC_SetOC5OutputMode(9)
#define HSPWMC_OC5REFCombinedPWM1()     HSPWMC_SetOC5OutputMode(12)
#define HSPWMC_OC5REFCombinedPWM2()     HSPWMC_SetOC5OutputMode(13)
#define HSPWMC_OC5REFAsymmetricPWM1()   HSPWMC_SetOC5OutputMode(14)
#define HSPWMC_OC5REFAsymmetricPWM2()   HSPWMC_SetOC5OutputMode(15)

#define PWMCCCMR5_OC5PE_MSK             BIT3
#define PWMC_UnbufferCCR5()             CLR_REG_BIT(PWMC_CCMR5, PWMCCCMR5_OC5PE_MSK)
#define PWMC_BufferCCR5()               SET_REG_BIT(PWMC_CCMR5, PWMCCCMR5_OC5PE_MSK)

#define HSPWMC_UnbufferCCR5()           CLR_HSPWMC_BIT(PWMC_CCMR5, PWMCCCMR5_OC5PE_MSK)
#define HSPWMC_BufferCCR5()             SET_HSPWMC_BIT(PWMC_CCMR5, PWMCCCMR5_OC5PE_MSK)

#define PWMCCCMR6_OC6CE_MSK             BIT7
#define PWMC_EnableETRFClearOC6REF()    SET_REG_BIT(PWMC_CCMR6, PWMCCCMR6_OC6CE_MSK)
#define PWMC_DisableETRFClearOC6REF()   CLR_REG_BIT(PWMC_CCMR6, PWMCCCMR6_OC6CE_MSK)

#define HSPWMC_EnableETRFClearOC6REF()  SET_HSPWMC_BIT(PWMC_CCMR6, PWMCCCMR6_OC6CE_MSK)
#define HSPWMC_DisableETRFClearOC6REF() CLR_HSPWMC_BIT(PWMC_CCMR6, PWMCCCMR6_OC6CE_MSK)

#define PWMCCCMR6_OC6M_MSK              (BIT6 | BIT5 | BIT4)
#define PWMCCCMR6X_OC6M3_MSK            BIT0
#define PWMC_SetOC6OutputMode(n)        MODIFY_REG(PWMC_CCMR6,  PWMCCCMR6_OC6M_MSK, ((n) << 4)); \
                                        MODIFY_REG(PWMC_CCMR6X, PWMCCCMR6X_OC6M3_MSK, (((n) >> 3) << 0))
#define PWMC_OC6REFFrozen()             PWMC_SetOC6OutputMode(0)
#define PWMC_OC6REFHighIfMatch()        PWMC_SetOC6OutputMode(1)
#define PWMC_OC6REFLowIfMatch()         PWMC_SetOC6OutputMode(2)
#define PWMC_OC6REFToggleIfMatch()      PWMC_SetOC6OutputMode(3)
#define PWMC_OC6REFForceLow()           PWMC_SetOC6OutputMode(4)
#define PWMC_OC6REFForceHigh()          PWMC_SetOC6OutputMode(5)
#define PWMC_OC6REFPWMMode1()           PWMC_SetOC6OutputMode(6)
#define PWMC_OC6REFPWMMode2()           PWMC_SetOC6OutputMode(7)
#define PWMC_OC6REFReTrigOPMPWM1()      PWMC_SetOC6OutputMode(8)
#define PWMC_OC6REFReTrigOPMPWM2()      PWMC_SetOC6OutputMode(9)
#define PWMC_OC6REFCombinedPWM1()       PWMC_SetOC6OutputMode(12)
#define PWMC_OC6REFCombinedPWM2()       PWMC_SetOC6OutputMode(13)
#define PWMC_OC6REFAsymmetricPWM1()     PWMC_SetOC6OutputMode(14)
#define PWMC_OC6REFAsymmetricPWM2()     PWMC_SetOC6OutputMode(15)

#define HSPWMC_SetOC6OutputMode(n)      MODIFY_HSPWMC(PWMC_CCMR6,  PWMCCCMR6_OC6M_MSK, ((n) << 4)); \
                                        MODIFY_HSPWMC(PWMC_CCMR6X, PWMCCCMR6X_OC6M3_MSK, (((n) >> 3) << 0))
#define HSPWMC_OC6REFFrozen()           HSPWMC_SetOC6OutputMode(0)
#define HSPWMC_OC6REFHighIfMatch()      HSPWMC_SetOC6OutputMode(1)
#define HSPWMC_OC6REFLowIfMatch()       HSPWMC_SetOC6OutputMode(2)
#define HSPWMC_OC6REFToggleIfMatch()    HSPWMC_SetOC6OutputMode(3)
#define HSPWMC_OC6REFForceLow()         HSPWMC_SetOC6OutputMode(4)
#define HSPWMC_OC6REFForceHigh()        HSPWMC_SetOC6OutputMode(5)
#define HSPWMC_OC6REFPWMMode1()         HSPWMC_SetOC6OutputMode(6)
#define HSPWMC_OC6REFPWMMode2()         HSPWMC_SetOC6OutputMode(7)
#define HSPWMC_OC6REFReTrigOPMPWM1()    HSPWMC_SetOC6OutputMode(8)
#define HSPWMC_OC6REFReTrigOPMPWM2()    HSPWMC_SetOC6OutputMode(9)
#define HSPWMC_OC6REFCombinedPWM1()     HSPWMC_SetOC6OutputMode(12)
#define HSPWMC_OC6REFCombinedPWM2()     HSPWMC_SetOC6OutputMode(13)
#define HSPWMC_OC6REFAsymmetricPWM1()   HSPWMC_SetOC6OutputMode(14)
#define HSPWMC_OC6REFAsymmetricPWM2()   HSPWMC_SetOC6OutputMode(15)

#define PWMCCCMR6_OC6PE_MSK             BIT3
#define PWMC_UnbufferCCR6()             CLR_REG_BIT(PWMC_CCMR6, PWMCCCMR6_OC6PE_MSK)
#define PWMC_BufferCCR6()               SET_REG_BIT(PWMC_CCMR6, PWMCCCMR6_OC6PE_MSK)

#define HSPWMC_UnbufferCCR6()           CLR_HSPWMC_BIT(PWMC_CCMR6, PWMCCCMR6_OC6PE_MSK)
#define HSPWMC_BufferCCR6()             SET_HSPWMC_BIT(PWMC_CCMR6, PWMCCCMR6_OC6PE_MSK)

#define PWMCCCER1_CC1E_MSK              BIT0
#define PWMC_CC1PEnable()               SET_REG_BIT(PWMC_CCER1, PWMCCCER1_CC1E_MSK)
#define PWMC_CC1PDisable()              CLR_REG_BIT(PWMC_CCER1, PWMCCCER1_CC1E_MSK)

#define HSPWMC_CC1PEnable()             SET_HSPWMC_BIT(PWMC_CCER1, PWMCCCER1_CC1E_MSK)
#define HSPWMC_CC1PDisable()            CLR_HSPWMC_BIT(PWMC_CCER1, PWMCCCER1_CC1E_MSK)

#define PWMCCCER1_CC1P_MSK              BIT1
#define PWMC_CC1PNonInverted()          CLR_REG_BIT(PWMC_CCER1, PWMCCCER1_CC1P_MSK)
#define PWMC_CC1PInverted()             SET_REG_BIT(PWMC_CCER1, PWMCCCER1_CC1P_MSK)

#define HSPWMC_CC1PNonInverted()        CLR_HSPWMC_BIT(PWMC_CCER1, PWMCCCER1_CC1P_MSK)
#define HSPWMC_CC1PInverted()           SET_HSPWMC_BIT(PWMC_CCER1, PWMCCCER1_CC1P_MSK)

#define PWMCCCER1_CC1NE_MSK             BIT2
#define PWMC_CC1NEnable()               SET_REG_BIT(PWMC_CCER1, PWMCCCER1_CC1NE_MSK)
#define PWMC_CC1NDisable()              CLR_REG_BIT(PWMC_CCER1, PWMCCCER1_CC1NE_MSK)

#define HSPWMC_CC1NEnable()             SET_HSPWMC_BIT(PWMC_CCER1, PWMCCCER1_CC1NE_MSK)
#define HSPWMC_CC1NDisable()            CLR_HSPWMC_BIT(PWMC_CCER1, PWMCCCER1_CC1NE_MSK)

#define PWMCCCER1_CC1NP_MSK             BIT3
#define PWMC_CC1NNonInverted()          CLR_REG_BIT(PWMC_CCER1, PWMCCCER1_CC1NP_MSK)
#define PWMC_CC1NInverted()             SET_REG_BIT(PWMC_CCER1, PWMCCCER1_CC1NP_MSK)

#define HSPWMC_CC1NNonInverted()        CLR_HSPWMC_BIT(PWMC_CCER1, PWMCCCER1_CC1NP_MSK)
#define HSPWMC_CC1NInverted()           SET_HSPWMC_BIT(PWMC_CCER1, PWMCCCER1_CC1NP_MSK)

#define PWMCCCER1_CC2E_MSK              BIT4
#define PWMC_CC2PEnable()               SET_REG_BIT(PWMC_CCER1, PWMCCCER1_CC2E_MSK)
#define PWMC_CC2PDisable()              CLR_REG_BIT(PWMC_CCER1, PWMCCCER1_CC2E_MSK)

#define HSPWMC_CC2PEnable()             SET_HSPWMC_BIT(PWMC_CCER1, PWMCCCER1_CC2E_MSK)
#define HSPWMC_CC2PDisable()            CLR_HSPWMC_BIT(PWMC_CCER1, PWMCCCER1_CC2E_MSK)

#define PWMCCCER1_CC2P_MSK              BIT5
#define PWMC_CC2PNonInverted()          CLR_REG_BIT(PWMC_CCER1, PWMCCCER1_CC2P_MSK)
#define PWMC_CC2PInverted()             SET_REG_BIT(PWMC_CCER1, PWMCCCER1_CC2P_MSK)

#define HSPWMC_CC2PNonInverted()        CLR_HSPWMC_BIT(PWMC_CCER1, PWMCCCER1_CC2P_MSK)
#define HSPWMC_CC2PInverted()           SET_HSPWMC_BIT(PWMC_CCER1, PWMCCCER1_CC2P_MSK)

#define PWMCCCER1_CC2NE_MSK             BIT6
#define PWMC_CC2NEnable()               SET_REG_BIT(PWMC_CCER1, PWMCCCER1_CC2NE_MSK)
#define PWMC_CC2NDisable()              CLR_REG_BIT(PWMC_CCER1, PWMCCCER1_CC2NE_MSK)

#define HSPWMC_CC2NEnable()             SET_HSPWMC_BIT(PWMC_CCER1, PWMCCCER1_CC2NE_MSK)
#define HSPWMC_CC2NDisable()            CLR_HSPWMC_BIT(PWMC_CCER1, PWMCCCER1_CC2NE_MSK)

#define PWMCCCER1_CC2NP_MSK             BIT7
#define PWMC_CC2NNonInverted()          CLR_REG_BIT(PWMC_CCER1, PWMCCCER1_CC2NP_MSK)
#define PWMC_CC2NInverted()             SET_REG_BIT(PWMC_CCER1, PWMCCCER1_CC2NP_MSK)

#define HSPWMC_CC2NNonInverted()        CLR_HSPWMC_BIT(PWMC_CCER1, PWMCCCER1_CC2NP_MSK)
#define HSPWMC_CC2NInverted()           SET_HSPWMC_BIT(PWMC_CCER1, PWMCCCER1_CC2NP_MSK)

#define PWMCCCER2_CC3E_MSK              BIT0
#define PWMC_CC3PEnable()               SET_REG_BIT(PWMC_CCER2, PWMCCCER2_CC3E_MSK)
#define PWMC_CC3PDisable()              CLR_REG_BIT(PWMC_CCER2, PWMCCCER2_CC3E_MSK)

#define HSPWMC_CC3PEnable()             SET_HSPWMC_BIT(PWMC_CCER2, PWMCCCER2_CC3E_MSK)
#define HSPWMC_CC3PDisable()            CLR_HSPWMC_BIT(PWMC_CCER2, PWMCCCER2_CC3E_MSK)

#define PWMCCCER2_CC3P_MSK              BIT1
#define PWMC_CC3PNonInverted()          CLR_REG_BIT(PWMC_CCER2, PWMCCCER2_CC3P_MSK)
#define PWMC_CC3PInverted()             SET_REG_BIT(PWMC_CCER2, PWMCCCER2_CC3P_MSK)

#define HSPWMC_CC3PNonInverted()        CLR_HSPWMC_BIT(PWMC_CCER2, PWMCCCER2_CC3P_MSK)
#define HSPWMC_CC3PInverted()           SET_HSPWMC_BIT(PWMC_CCER2, PWMCCCER2_CC3P_MSK)

#define PWMCCCER2_CC3NE_MSK             BIT2
#define PWMC_CC3NEnable()               SET_REG_BIT(PWMC_CCER2, PWMCCCER2_CC3NE_MSK)
#define PWMC_CC3NDisable()              CLR_REG_BIT(PWMC_CCER2, PWMCCCER2_CC3NE_MSK)

#define HSPWMC_CC3NEnable()             SET_HSPWMC_BIT(PWMC_CCER2, PWMCCCER2_CC3NE_MSK)
#define HSPWMC_CC3NDisable()            CLR_HSPWMC_BIT(PWMC_CCER2, PWMCCCER2_CC3NE_MSK)

#define PWMCCCER2_CC3NP_MSK             BIT3
#define PWMC_CC3NNonInverted()          CLR_REG_BIT(PWMC_CCER2, PWMCCCER2_CC3NP_MSK)
#define PWMC_CC3NInverted()             SET_REG_BIT(PWMC_CCER2, PWMCCCER2_CC3NP_MSK)

#define HSPWMC_CC3NNonInverted()        CLR_HSPWMC_BIT(PWMC_CCER2, PWMCCCER2_CC3NP_MSK)
#define HSPWMC_CC3NInverted()           SET_HSPWMC_BIT(PWMC_CCER2, PWMCCCER2_CC3NP_MSK)

#define PWMCCCER2_CC4E_MSK              BIT4
#define PWMC_CC4PEnable()               SET_REG_BIT(PWMC_CCER2, PWMCCCER2_CC4E_MSK)
#define PWMC_CC4PDisable()              CLR_REG_BIT(PWMC_CCER2, PWMCCCER2_CC4E_MSK)

#define HSPWMC_CC4PEnable()             SET_HSPWMC_BIT(PWMC_CCER2, PWMCCCER2_CC4E_MSK)
#define HSPWMC_CC4PDisable()            CLR_HSPWMC_BIT(PWMC_CCER2, PWMCCCER2_CC4E_MSK)

#define PWMCCCER2_CC4P_MSK              BIT5
#define PWMC_CC4PNonInverted()          CLR_REG_BIT(PWMC_CCER2, PWMCCCER2_CC4P_MSK)
#define PWMC_CC4PInverted()             SET_REG_BIT(PWMC_CCER2, PWMCCCER2_CC4P_MSK)

#define HSPWMC_CC4PNonInverted()        CLR_HSPWMC_BIT(PWMC_CCER2, PWMCCCER2_CC4P_MSK)
#define HSPWMC_CC4PInverted()           SET_HSPWMC_BIT(PWMC_CCER2, PWMCCCER2_CC4P_MSK)

#define PWMCCCER2_CC4NE_MSK             BIT6
#define PWMC_CC4NEnable()               SET_REG_BIT(PWMC_CCER2, PWMCCCER2_CC4NE_MSK)
#define PWMC_CC4NDisable()              CLR_REG_BIT(PWMC_CCER2, PWMCCCER2_CC4NE_MSK)

#define HSPWMC_CC4NEnable()             SET_HSPWMC_BIT(PWMC_CCER2, PWMCCCER2_CC4NE_MSK)
#define HSPWMC_CC4NDisable()            CLR_HSPWMC_BIT(PWMC_CCER2, PWMCCCER2_CC4NE_MSK)

#define PWMCCCER2_CC4NP_MSK             BIT7
#define PWMC_CC4NNonInverted()          CLR_REG_BIT(PWMC_CCER2, PWMCCCER2_CC4NP_MSK)
#define PWMC_CC4NInverted()             SET_REG_BIT(PWMC_CCER2, PWMCCCER2_CC4NP_MSK)

#define HSPWMC_CC4NNonInverted()        CLR_HSPWMC_BIT(PWMC_CCER2, PWMCCCER2_CC4NP_MSK)
#define HSPWMC_CC4NInverted()           SET_HSPWMC_BIT(PWMC_CCER2, PWMCCCER2_CC4NP_MSK)

#define PWMCCCER3_CC5E_MSK              BIT0
#define PWMC_CC5PEnable()               SET_REG_BIT(PWMC_CCER3, PWMCCCER3_CC5E_MSK)
#define PWMC_CC5PDisable()              CLR_REG_BIT(PWMC_CCER3, PWMCCCER3_CC5E_MSK)

#define HSPWMC_CC5PEnable()             SET_HSPWMC_BIT(PWMC_CCER3, PWMCCCER3_CC5E_MSK)
#define HSPWMC_CC5PDisable()            CLR_HSPWMC_BIT(PWMC_CCER3, PWMCCCER3_CC5E_MSK)

#define PWMCCCER3_CC5P_MSK              BIT1
#define PWMC_CC5PNonInverted()          CLR_REG_BIT(PWMC_CCER3, PWMCCCER3_CC5P_MSK)
#define PWMC_CC5PInverted()             SET_REG_BIT(PWMC_CCER3, PWMCCCER3_CC5P_MSK)

#define HSPWMC_CC5PNonInverted()        CLR_HSPWMC_BIT(PWMC_CCER3, PWMCCCER3_CC5P_MSK)
#define HSPWMC_CC5PInverted()           SET_HSPWMC_BIT(PWMC_CCER3, PWMCCCER3_CC5P_MSK)

#define PWMCCCER3_CC6E_MSK              BIT4
#define PWMC_CC6PEnable()               SET_REG_BIT(PWMC_CCER3, PWMCCCER3_CC6E_MSK)
#define PWMC_CC6PDisable()              CLR_REG_BIT(PWMC_CCER3, PWMCCCER3_CC6E_MSK)

#define HSPWMC_CC6PEnable()             SET_HSPWMC_BIT(PWMC_CCER3, PWMCCCER3_CC6E_MSK)
#define HSPWMC_CC6PDisable()            CLR_HSPWMC_BIT(PWMC_CCER3, PWMCCCER3_CC6E_MSK)

#define PWMCCCER3_CC6P_MSK              BIT5
#define PWMC_CC6PNonInverted()          CLR_REG_BIT(PWMC_CCER3, PWMCCCER3_CC6P_MSK)
#define PWMC_CC6PInverted()             SET_REG_BIT(PWMC_CCER3, PWMCCCER3_CC6P_MSK)

#define HSPWMC_CC6PNonInverted()        CLR_HSPWMC_BIT(PWMC_CCER3, PWMCCCER3_CC6P_MSK)
#define HSPWMC_CC6PInverted()           SET_HSPWMC_BIT(PWMC_CCER3, PWMCCCER3_CC6P_MSK)

#define PWMCBRK_MOE_MSK                 BIT7
#define PWMC_EnableMainOutput()         SET_REG_BIT(PWMC_BKR, PWMCBRK_MOE_MSK)
#define PWMC_DisableMainOutput()        CLR_REG_BIT(PWMC_BKR, PWMCBRK_MOE_MSK)

#define HSPWMC_EnableMainOutput()       SET_HSPWMC_BIT(PWMC_BKR, PWMCBRK_MOE_MSK)
#define HSPWMC_DisableMainOutput()      CLR_HSPWMC_BIT(PWMC_BKR, PWMCBRK_MOE_MSK)

#define PWMCBRK_AOE_MSK                 BIT6
#define PWMC_EnableAutoOutput()         SET_REG_BIT(PWMC_BKR, PWMCBRK_AOE_MSK)
#define PWMC_DisableAutoOutput()        CLR_REG_BIT(PWMC_BKR, PWMCBRK_AOE_MSK)

#define HSPWMC_EnableAutoOutput()       SET_HSPWMC_BIT(PWMC_BKR, PWMCBRK_AOE_MSK)
#define HSPWMC_DisableAutoOutput()      CLR_HSPWMC_BIT(PWMC_BKR, PWMCBRK_AOE_MSK)

#define PWMCBRK_BKP_MSK                 BIT5
#define PWMC_BRKNonInverted()           SET_REG_BIT(PWMC_BKR, PWMCBRK_BKP_MSK)
#define PWMC_BRKInverted()              CLR_REG_BIT(PWMC_BKR, PWMCBRK_BKP_MSK)

#define HSPWMC_BRKNonInverted()         SET_HSPWMC_BIT(PWMC_BKR, PWMCBRK_BKP_MSK)
#define HSPWMC_BRKInverted()            CLR_HSPWMC_BIT(PWMC_BKR, PWMCBRK_BKP_MSK)

#define PWMCBRK_BKE_MSK                 BIT4
#define PWMC_BRKEnable()                SET_REG_BIT(PWMC_BKR, PWMCBRK_BKE_MSK)
#define PWMC_BRKDisable()               CLR_REG_BIT(PWMC_BKR, PWMCBRK_BKE_MSK)

#define HSPWMC_BRKEnable()              SET_HSPWMC_BIT(PWMC_BKR, PWMCBRK_BKE_MSK)
#define HSPWMC_BRKDisable()             CLR_HSPWMC_BIT(PWMC_BKR, PWMCBRK_BKE_MSK)

#define PWMCBRK_OSSR_MSK                BIT3
#define PWMCBRK_OSSI_MSK                BIT2
#define PWMC_RunInactiveNoOutput()      CLR_REG_BIT(PWMC_BKR, PWMCBRK_OSSR_MSK)
#define PWMC_RunInactiveOutput()        SET_REG_BIT(PWMC_BKR, PWMCBRK_OSSR_MSK)
#define PWMC_IdleInactiveNoOutput()     CLR_REG_BIT(PWMC_BKR, PWMCBRK_OSSI_MSK)
#define PWMC_IdleInactiveOutput()       SET_REG_BIT(PWMC_BKR, PWMCBRK_OSSI_MSK)

#define HSPWMC_RunInactiveNoOutput()    CLR_HSPWMC_BIT(PWMC_BKR, PWMCBRK_OSSR_MSK)
#define HSPWMC_RunInactiveOutput()      SET_HSPWMC_BIT(PWMC_BKR, PWMCBRK_OSSR_MSK)
#define HSPWMC_IdleInactiveNoOutput()   CLR_HSPWMC_BIT(PWMC_BKR, PWMCBRK_OSSI_MSK)
#define HSPWMC_IdleInactiveOutput()     SET_HSPWMC_BIT(PWMC_BKR, PWMCBRK_OSSI_MSK)

#define PWMCBRK_LOCK_MSK                (BIT1 | BIT0)
#define PWMC_SetLockLevel(n)            MODIFY_REG(PWMC_BKR,  PWMCBRK_LOCK_MSK, ((n) << 0))
#define PWMC_SetUnLock()                PWMC_SetLockLevel(0)

#define HSPWMC_SetLockLevel(n)          MODIFY_HSPWMC(PWMC_BKR,  PWMCBRK_LOCK_MSK, ((n) << 0))
#define HSPWMC_SetUnLock()              HSPWMC_SetLockLevel(0)

#define PWMCOISR_OIS1_MSK               BIT0
#define PWMCOISR_OIS1N_MSK              BIT1
#define PWMCOISR_OIS2_MSK               BIT2
#define PWMCOISR_OIS2N_MSK              BIT3
#define PWMCOISR_OIS3_MSK               BIT4
#define PWMCOISR_OIS3N_MSK              BIT5
#define PWMCOISR_OIS4_MSK               BIT6
#define PWMCOISR_OIS4N_MSK              BIT7
#define PWMCCR3_OIS5_MSK                BIT0
#define PWMCCR3_OIS6_MSK                BIT2
#define PWMC_OC1PIdleLevelLow()         CLR_REG_BIT(PWMC_OISR, PWMCOISR_OIS1_MSK)
#define PWMC_OC1PIdleLevelHigh()        SET_REG_BIT(PWMC_OISR, PWMCOISR_OIS1_MSK)
#define PWMC_OC1NIdleLevelLow()         CLR_REG_BIT(PWMC_OISR, PWMCOISR_OIS1N_MSK)
#define PWMC_OC1NIdleLevelHigh()        SET_REG_BIT(PWMC_OISR, PWMCOISR_OIS1N_MSK)
#define PWMC_OC2PIdleLevelLow()         CLR_REG_BIT(PWMC_OISR, PWMCOISR_OIS2_MSK)
#define PWMC_OC2PIdleLevelHigh()        SET_REG_BIT(PWMC_OISR, PWMCOISR_OIS2_MSK)
#define PWMC_OC2NIdleLevelLow()         CLR_REG_BIT(PWMC_OISR, PWMCOISR_OIS2N_MSK)
#define PWMC_OC2NIdleLevelHigh()        SET_REG_BIT(PWMC_OISR, PWMCOISR_OIS2N_MSK)
#define PWMC_OC3PIdleLevelLow()         CLR_REG_BIT(PWMC_OISR, PWMCOISR_OIS3_MSK)
#define PWMC_OC3PIdleLevelHigh()        SET_REG_BIT(PWMC_OISR, PWMCOISR_OIS3_MSK)
#define PWMC_OC3NIdleLevelLow()         CLR_REG_BIT(PWMC_OISR, PWMCOISR_OIS3N_MSK)
#define PWMC_OC3NIdleLevelHigh()        SET_REG_BIT(PWMC_OISR, PWMCOISR_OIS3N_MSK)
#define PWMC_OC4PIdleLevelLow()         CLR_REG_BIT(PWMC_OISR, PWMCOISR_OIS4_MSK)
#define PWMC_OC4PIdleLevelHigh()        SET_REG_BIT(PWMC_OISR, PWMCOISR_OIS4_MSK)
#define PWMC_OC4NIdleLevelLow()         CLR_REG_BIT(PWMC_OISR, PWMCOISR_OIS4N_MSK)
#define PWMC_OC4NIdleLevelHigh()        SET_REG_BIT(PWMC_OISR, PWMCOISR_OIS4N_MSK)
#define PWMC_OC5PIdleLevelLow()         CLR_REG_BIT(PWMC_CR3, PWMCCR3_OIS5_MSK)
#define PWMC_OC5PIdleLevelHigh()        SET_REG_BIT(PWMC_CR3, PWMCCR3_OIS5_MSK)
#define PWMC_OC6PIdleLevelLow()         CLR_REG_BIT(PWMC_CR3, PWMCCR3_OIS6_MSK)
#define PWMC_OC6PIdleLevelHigh()        SET_REG_BIT(PWMC_CR3, PWMCCR3_OIS6_MSK)

#define HSPWMC_OC1PIdleLevelLow()       CLR_HSPWMC_BIT(PWMC_OISR, PWMCOISR_OIS1_MSK)
#define HSPWMC_OC1PIdleLevelHigh()      SET_HSPWMC_BIT(PWMC_OISR, PWMCOISR_OIS1_MSK)
#define HSPWMC_OC1NIdleLevelLow()       CLR_HSPWMC_BIT(PWMC_OISR, PWMCOISR_OIS1N_MSK)
#define HSPWMC_OC1NIdleLevelHigh()      SET_HSPWMC_BIT(PWMC_OISR, PWMCOISR_OIS1N_MSK)
#define HSPWMC_OC2PIdleLevelLow()       CLR_HSPWMC_BIT(PWMC_OISR, PWMCOISR_OIS2_MSK)
#define HSPWMC_OC2PIdleLevelHigh()      SET_HSPWMC_BIT(PWMC_OISR, PWMCOISR_OIS2_MSK)
#define HSPWMC_OC2NIdleLevelLow()       CLR_HSPWMC_BIT(PWMC_OISR, PWMCOISR_OIS2N_MSK)
#define HSPWMC_OC2NIdleLevelHigh()      SET_HSPWMC_BIT(PWMC_OISR, PWMCOISR_OIS2N_MSK)
#define HSPWMC_OC3PIdleLevelLow()       CLR_HSPWMC_BIT(PWMC_OISR, PWMCOISR_OIS3_MSK)
#define HSPWMC_OC3PIdleLevelHigh()      SET_HSPWMC_BIT(PWMC_OISR, PWMCOISR_OIS3_MSK)
#define HSPWMC_OC3NIdleLevelLow()       CLR_HSPWMC_BIT(PWMC_OISR, PWMCOISR_OIS3N_MSK)
#define HSPWMC_OC3NIdleLevelHigh()      SET_HSPWMC_BIT(PWMC_OISR, PWMCOISR_OIS3N_MSK)
#define HSPWMC_OC4PIdleLevelLow()       CLR_HSPWMC_BIT(PWMC_OISR, PWMCOISR_OIS4_MSK)
#define HSPWMC_OC4PIdleLevelHigh()      SET_HSPWMC_BIT(PWMC_OISR, PWMCOISR_OIS4_MSK)
#define HSPWMC_OC4NIdleLevelLow()       CLR_HSPWMC_BIT(PWMC_OISR, PWMCOISR_OIS4N_MSK)
#define HSPWMC_OC4NIdleLevelHigh()      SET_HSPWMC_BIT(PWMC_OISR, PWMCOISR_OIS4N_MSK)
#define HSPWMC_OC5PIdleLevelLow()       CLR_HSPWMC_BIT(PWMC_CR3, PWMCCR3_OIS5_MSK)
#define HSPWMC_OC5PIdleLevelHigh()      SET_HSPWMC_BIT(PWMC_CR3, PWMCCR3_OIS5_MSK)
#define HSPWMC_OC6PIdleLevelLow()       CLR_HSPWMC_BIT(PWMC_CR3, PWMCCR3_OIS6_MSK)
#define HSPWMC_OC6PIdleLevelHigh()      SET_HSPWMC_BIT(PWMC_CR3, PWMCCR3_OIS6_MSK)

#define PWMC_SetCounter(n)              (PWMC_CNTRH = HIBYTE(n), PWMC_CNTRL = LOBYTE(n))
#define PWMC_SetClockDivider(n)         (PWMC_PSCRH = HIBYTE(n), PWMC_PSCRL = LOBYTE(n))
#define PWMC_SetReload16(n)             (PWMC_ARRH = HIBYTE(n), PWMC_ARRL = LOBYTE(n))
#define PWMC_SetRepeatCounter(n)        (PWMC_RCRH = HIBYTE(n), PWMC_RCR = LOBYTE(n))

#define HSPWMC_SetCounter(n)            (WRITE_HSPWMC(PWMC_CNTRH, HIBYTE(n)), WRITE_HSPWMC(PWMC_CNTRL, LOBYTE(n)))
#define HSPWMC_SetClockDivider(n)       (WRITE_HSPWMC(PWMC_PSCRH, HIBYTE(n)), WRITE_HSPWMC(PWMC_PSCRL, LOBYTE(n)))
#define HSPWMC_SetReload16(n)           (WRITE_HSPWMC(PWMC_ARRH, HIBYTE(n)), WRITE_HSPWMC(PWMC_ARRL, LOBYTE(n)))
#define HSPWMC_SetRepeatCounter(n)      (WRITE_HSPWMC(PWMC_RCRH, HIBYTE(n)), WRITE_HSPWMC(PWMC_RCR, LOBYTE(n)))

#define PWMC_SetCCR1Value(n)            (PWMC_CCR1H = HIBYTE(n), PWMC_CCR1L = LOBYTE(n))
#define PWMC_SetCCR2Value(n)            (PWMC_CCR2H = HIBYTE(n), PWMC_CCR2L = LOBYTE(n))
#define PWMC_SetCCR3Value(n)            (PWMC_CCR3H = HIBYTE(n), PWMC_CCR3L = LOBYTE(n))
#define PWMC_SetCCR4Value(n)            (PWMC_CCR4H = HIBYTE(n), PWMC_CCR4L = LOBYTE(n))
#define PWMC_SetCCR5Value(n)            (PWMC_CCR5H = HIBYTE(n), PWMC_CCR5L = LOBYTE(n))
#define PWMC_SetCCR6Value(n)            (PWMC_CCR6H = HIBYTE(n), PWMC_CCR6L = LOBYTE(n))

#define HSPWMC_SetCCR1Value(n)          (WRITE_HSPWMC(PWMC_CCR1H, HIBYTE(n)), WRITE_HSPWMC(PWMC_CCR1L, LOBYTE(n)))
#define HSPWMC_SetCCR2Value(n)          (WRITE_HSPWMC(PWMC_CCR2H, HIBYTE(n)), WRITE_HSPWMC(PWMC_CCR2L, LOBYTE(n)))
#define HSPWMC_SetCCR3Value(n)          (WRITE_HSPWMC(PWMC_CCR3H, HIBYTE(n)), WRITE_HSPWMC(PWMC_CCR3L, LOBYTE(n)))
#define HSPWMC_SetCCR4Value(n)          (WRITE_HSPWMC(PWMC_CCR4H, HIBYTE(n)), WRITE_HSPWMC(PWMC_CCR4L, LOBYTE(n)))
#define HSPWMC_SetCCR5Value(n)          (WRITE_HSPWMC(PWMC_CCR5H, HIBYTE(n)), WRITE_HSPWMC(PWMC_CCR5L, LOBYTE(n)))
#define HSPWMC_SetCCR6Value(n)          (WRITE_HSPWMC(PWMC_CCR6H, HIBYTE(n)), WRITE_HSPWMC(PWMC_CCR6L, LOBYTE(n)))

#define PWMC_ReadReload16()             MAKEWORD(PWMC_ARRL, PWMC_ARRH)

#define HSPWMC_ReadReload16()           MAKEWORD(READ_HSPWMC(PWMC_ARRL), READ_HSPWMC(PWMC_ARRH))

#define PWMC_ReadCCR1Value()            MAKEWORD(PWMC_CCR1L, PWMC_CCR1H)
#define PWMC_ReadCCR2Value()            MAKEWORD(PWMC_CCR2L, PWMC_CCR2H)
#define PWMC_ReadCCR3Value()            MAKEWORD(PWMC_CCR3L, PWMC_CCR3H)
#define PWMC_ReadCCR4Value()            MAKEWORD(PWMC_CCR4L, PWMC_CCR4H)
#define PWMC_ReadCCR5Value()            MAKEWORD(PWMC_CCR5L, PWMC_CCR5H)
#define PWMC_ReadCCR6Value()            MAKEWORD(PWMC_CCR6L, PWMC_CCR6H)

#define HSPWMC_ReadCCR1Value()          MAKEWORD(READ_HSPWMC(PWMC_CCR1L), READ_HSPWMC(PWMC_CCR1H))
#define HSPWMC_ReadCCR2Value()          MAKEWORD(READ_HSPWMC(PWMC_CCR2L), READ_HSPWMC(PWMC_CCR2H))
#define HSPWMC_ReadCCR3Value()          MAKEWORD(READ_HSPWMC(PWMC_CCR3L), READ_HSPWMC(PWMC_CCR3H))
#define HSPWMC_ReadCCR4Value()          MAKEWORD(READ_HSPWMC(PWMC_CCR4L), READ_HSPWMC(PWMC_CCR4H))
#define HSPWMC_ReadCCR5Value()          MAKEWORD(READ_HSPWMC(PWMC_CCR5L), READ_HSPWMC(PWMC_CCR5H))
#define HSPWMC_ReadCCR6Value()          MAKEWORD(READ_HSPWMC(PWMC_CCR6L), READ_HSPWMC(PWMC_CCR6H))

#define PWMC_SetDeadTime(n)             PWMC_DTR = LOBYTE(n)

#define HSPWMC_SetDeadTime(n)           WRITE_HSPWMC(PWMC_DTR, LOBYTE(n))

#define PWMCCCR5X_GC5C3_MSK             BIT7
#define PWMCCCR5X_GC5C2_MSK             BIT6
#define PWMCCCR5X_GC5C1_MSK             BIT5
#define PWMC_OC3REFCIndependent()       CLR_REG_BIT(PWMC_CCR5X, PWMCCCR5X_GC5C3_MSK)
#define PWMC_OC2REFCIndependent()       CLR_REG_BIT(PWMC_CCR5X, PWMCCCR5X_GC5C2_MSK)
#define PWMC_OC1REFCIndependent()       CLR_REG_BIT(PWMC_CCR5X, PWMCCCR5X_GC5C1_MSK)
#define PWMC_OC3REFCAndWithOC5REF()     SET_REG_BIT(PWMC_CCR5X, PWMCCCR5X_GC5C3_MSK)
#define PWMC_OC2REFCAndWithOC5REF()     SET_REG_BIT(PWMC_CCR5X, PWMCCCR5X_GC5C2_MSK)
#define PWMC_OC1REFCAndWithOC5REF()     SET_REG_BIT(PWMC_CCR5X, PWMCCCR5X_GC5C1_MSK)

#define HSPWMC_OC3REFCIndependent()     CLR_HSPWMC_BIT(PWMC_CCR5X, PWMCCCR5X_GC5C3_MSK)
#define HSPWMC_OC2REFCIndependent()     CLR_HSPWMC_BIT(PWMC_CCR5X, PWMCCCR5X_GC5C2_MSK)
#define HSPWMC_OC1REFCIndependent()     CLR_HSPWMC_BIT(PWMC_CCR5X, PWMCCCR5X_GC5C1_MSK)
#define HSPWMC_OC3REFCAndWithOC5REF()   SET_HSPWMC_BIT(PWMC_CCR5X, PWMCCCR5X_GC5C3_MSK)
#define HSPWMC_OC2REFCAndWithOC5REF()   SET_HSPWMC_BIT(PWMC_CCR5X, PWMCCCR5X_GC5C2_MSK)
#define HSPWMC_OC1REFCAndWithOC5REF()   SET_HSPWMC_BIT(PWMC_CCR5X, PWMCCCR5X_GC5C1_MSK)

////////////////////////

#define PWMCDER_TDE_MSK                 BIT6
#define PWMCDER_COMDE_MSK               BIT5
#define PWMCDER_CC4DE_MSK               BIT4
#define PWMCDER_CC3DE_MSK               BIT3
#define PWMCDER_CC2DE_MSK               BIT2
#define PWMCDER_CC1DE_MSK               BIT1
#define PWMCDER_UDE_MSK                 BIT0
#define PWMC_TriggerIntAsDMAEvent()     SET_REG_BIT(PWMC_DER, PWMCDER_TDE_MSK)
#define PWMC_COMIntAsDMAEvent()         SET_REG_BIT(PWMC_DER, PWMCDER_COMDE_MSK)
#define PWMC_CC4IntAsDMAEvent()         SET_REG_BIT(PWMC_DER, PWMCDER_CC4DE_MSK)
#define PWMC_CC3IntAsDMAEvent()         SET_REG_BIT(PWMC_DER, PWMCDER_CC3DE_MSK)
#define PWMC_CC2IntAsDMAEvent()         SET_REG_BIT(PWMC_DER, PWMCDER_CC2DE_MSK)
#define PWMC_CC1IntAsDMAEvent()         SET_REG_BIT(PWMC_DER, PWMCDER_CC1DE_MSK)
#define PWMC_UpdateIntAsDMAEvent()      SET_REG_BIT(PWMC_DER, PWMCDER_UDE_MSK)

#define HSPWMC_TriggerIntAsDMAEvent()   SET_HSPWMC_BIT(PWMC_DER, PWMCDER_TDE_MSK)
#define HSPWMC_COMIntAsDMAEvent()       SET_HSPWMC_BIT(PWMC_DER, PWMCDER_COMDE_MSK)
#define HSPWMC_CC4IntAsDMAEvent()       SET_HSPWMC_BIT(PWMC_DER, PWMCDER_CC4DE_MSK)
#define HSPWMC_CC3IntAsDMAEvent()       SET_HSPWMC_BIT(PWMC_DER, PWMCDER_CC3DE_MSK)
#define HSPWMC_CC2IntAsDMAEvent()       SET_HSPWMC_BIT(PWMC_DER, PWMCDER_CC2DE_MSK)
#define HSPWMC_CC1IntAsDMAEvent()       SET_HSPWMC_BIT(PWMC_DER, PWMCDER_CC1DE_MSK)
#define HSPWMC_UpdateIntAsDMAEvent()    SET_HSPWMC_BIT(PWMC_DER, PWMCDER_UDE_MSK)

#define PWMCDBA_DBA_MSK                 (BIT4 | BIT_LN)
#define PWMC_SetDMABaseAddress(d)       MODIFY_REG(PWMC_DBA,  PWMCDBA_DBA_MSK, ((d) << 0))

#define HSPWMC_SetDMABaseAddress(d)     MODIFY_HSPWMC(PWMC_DBA,  PWMCDBA_DBA_MSK, ((d) << 0))

#define PWMCDBL_DBL_MSK                 (BIT4 | BIT_LN)
#define PWMC_SetDMABurstCount(d)        MODIFY_REG(PWMC_DBL,  PWMCDBL_DBL_MSK, ((d) << 0))

#define HSPWMC_SetDMABurstCount(d)      MODIFY_HSPWMC(PWMC_DBL,  PWMCDBL_DBL_MSK, ((d) << 0))

#define PWMCDMACR_SIZE_MSK              (BIT1 | BIT0)
#define PWMC_SetDMABurstBytes(n)        MODIFY_REG(PWMC_DMACR,  PWMCDMACR_SIZE_MSK, ((n) << 0))
#define PWMC_SetDMABurst1Byte()         PWMC_SetDMABurstBytes(0)
#define PWMC_SetDMABurst2Bytes()        PWMC_SetDMABurstBytes(1)
#define PWMC_SetDMABurst3Bytes()        PWMC_SetDMABurstBytes(2)
#define PWMC_SetDMABurst4Bytes()        PWMC_SetDMABurstBytes(3)

#define HSPWMC_SetDMABurstBytes(n)      MODIFY_HSPWMC(PWMC_DMACR,  PWMCDMACR_SIZE_MSK, ((n) << 0))
#define HSPWMC_SetDMABurst1Byte()       HSPWMC_SetDMABurstBytes(0)
#define HSPWMC_SetDMABurst2Bytes()      HSPWMC_SetDMABurstBytes(1)
#define HSPWMC_SetDMABurst3Bytes()      HSPWMC_SetDMABurstBytes(2)
#define HSPWMC_SetDMABurst4Bytes()      HSPWMC_SetDMABurstBytes(3)

#define PWMCDMACR_DSKIP_MSK             BIT4
#define PWMC_DMASkipSpace()             SET_REG_BIT(PWMC_DMACR, PWMCDMACR_DSKIP_MSK)
#define PWMC_DMANeverSkipSpace()        CLR_REG_BIT(PWMC_DMACR, PWMCDMACR_DSKIP_MSK)

#define HSPWMC_DMASkipSpace()           SET_HSPWMC_BIT(PWMC_DMACR, PWMCDMACR_DSKIP_MSK)
#define HSPWMC_DMANeverSkipSpace()      CLR_HSPWMC_BIT(PWMC_DMACR, PWMCDMACR_DSKIP_MSK)

#define PWMCDMACR_DDIR_MSK              BIT3
#define PWMC_SetDMAOutput()             CLR_REG_BIT(PWMC_DMACR, PWMCDMACR_DDIR_MSK)
#define PWMC_SetDMAInput()              SET_REG_BIT(PWMC_DMACR, PWMCDMACR_DDIR_MSK)

#define HSPWMC_SetDMAOutput()           CLR_HSPWMC_BIT(PWMC_DMACR, PWMCDMACR_DDIR_MSK)
#define HSPWMC_SetDMAInput()            SET_HSPWMC_BIT(PWMC_DMACR, PWMCDMACR_DDIR_MSK)

#define PWMCDMACR_DMAEN_MSK             BIT2
#define PWMC_EnableDMA()                SET_REG_BIT(PWMC_DMACR, PWMCDMACR_DMAEN_MSK)
#define PWMC_DisableDMA()               CLR_REG_BIT(PWMC_DMACR, PWMCDMACR_DMAEN_MSK)

#define HSPWMC_EnableDMA()              SET_HSPWMC_BIT(PWMC_DMACR, PWMCDMACR_DMAEN_MSK)
#define HSPWMC_DisableDMA()             CLR_HSPWMC_BIT(PWMC_DMACR, PWMCDMACR_DMAEN_MSK)

////////////////////////

#define PWMDENO_ENO5P_MSK               BIT0
#define PWMDENO_ENO6P_MSK               BIT2
#define PWMDENO_ENO7P_MSK               BIT4
#define PWMDENO_ENO8P_MSK               BIT6
#define PWMD_EnablePWM5POutput()        SET_REG_BIT(PWMD_ENO, PWMDENO_ENO5P_MSK)
#define PWMD_DisablePWM5POutput()       CLR_REG_BIT(PWMD_ENO, PWMDENO_ENO5P_MSK)
#define PWMD_EnablePWM6POutput()        SET_REG_BIT(PWMD_ENO, PWMDENO_ENO6P_MSK)
#define PWMD_DisablePWM6POutput()       CLR_REG_BIT(PWMD_ENO, PWMDENO_ENO6P_MSK)
#define PWMD_EnablePWM7POutput()        SET_REG_BIT(PWMD_ENO, PWMDENO_ENO7P_MSK)
#define PWMD_DisablePWM7POutput()       CLR_REG_BIT(PWMD_ENO, PWMDENO_ENO7P_MSK)
#define PWMD_EnablePWM8POutput()        SET_REG_BIT(PWMD_ENO, PWMDENO_ENO8P_MSK)
#define PWMD_DisablePWM8POutput()       CLR_REG_BIT(PWMD_ENO, PWMDENO_ENO8P_MSK)

#define HSPWMD_EnablePWM5POutput()      SET_HSPWMD_BIT(PWMD_ENO, PWMDENO_ENO5P_MSK)
#define HSPWMD_DisablePWM5POutput()     CLR_HSPWMD_BIT(PWMD_ENO, PWMDENO_ENO5P_MSK)
#define HSPWMD_EnablePWM6POutput()      SET_HSPWMD_BIT(PWMD_ENO, PWMDENO_ENO6P_MSK)
#define HSPWMD_DisablePWM6POutput()     CLR_HSPWMD_BIT(PWMD_ENO, PWMDENO_ENO6P_MSK)
#define HSPWMD_EnablePWM7POutput()      SET_HSPWMD_BIT(PWMD_ENO, PWMDENO_ENO7P_MSK)
#define HSPWMD_DisablePWM7POutput()     CLR_HSPWMD_BIT(PWMD_ENO, PWMDENO_ENO7P_MSK)
#define HSPWMD_EnablePWM8POutput()      SET_HSPWMD_BIT(PWMD_ENO, PWMDENO_ENO8P_MSK)
#define HSPWMD_DisablePWM8POutput()     CLR_HSPWMD_BIT(PWMD_ENO, PWMDENO_ENO8P_MSK)

#define PWMDIOAUX_AUX5P_MSK             BIT0
#define PWMDIOAUX_AUX6P_MSK             BIT2
#define PWMDIOAUX_AUX7P_MSK             BIT4
#define PWMDIOAUX_AUX8P_MSK             BIT6
#define PWMD_EnoCtrlPWM5P()             CLR_REG_BIT(PWMD_IOAUX, PWMDIOAUX_AUX5P_MSK)
#define PWMD_EnoBrkCtrlPWM5P()          SET_REG_BIT(PWMD_IOAUX, PWMDIOAUX_AUX5P_MSK)
#define PWMD_EnoCtrlPWM6P()             CLR_REG_BIT(PWMD_IOAUX, PWMDIOAUX_AUX6P_MSK)
#define PWMD_EnoBrkCtrlPWM6P()          SET_REG_BIT(PWMD_IOAUX, PWMDIOAUX_AUX6P_MSK)
#define PWMD_EnoCtrlPWM7P()             CLR_REG_BIT(PWMD_IOAUX, PWMDIOAUX_AUX7P_MSK)
#define PWMD_EnoBrkCtrlPWM7P()          SET_REG_BIT(PWMD_IOAUX, PWMDIOAUX_AUX7P_MSK)
#define PWMD_EnoCtrlPWM8P()             CLR_REG_BIT(PWMD_IOAUX, PWMDIOAUX_AUX8P_MSK)
#define PWMD_EnoBrkCtrlPWM8P()          SET_REG_BIT(PWMD_IOAUX, PWMDIOAUX_AUX8P_MSK)

#define HSPWMD_EnoCtrlPWM5P()           CLR_HSPWMD_BIT(PWMD_IOAUX, PWMDIOAUX_AUX5P_MSK)
#define HSPWMD_EnoBrkCtrlPWM5P()        SET_HSPWMD_BIT(PWMD_IOAUX, PWMDIOAUX_AUX5P_MSK)
#define HSPWMD_EnoCtrlPWM6P()           CLR_HSPWMD_BIT(PWMD_IOAUX, PWMDIOAUX_AUX6P_MSK)
#define HSPWMD_EnoBrkCtrlPWM6P()        SET_HSPWMD_BIT(PWMD_IOAUX, PWMDIOAUX_AUX6P_MSK)
#define HSPWMD_EnoCtrlPWM7P()           CLR_HSPWMD_BIT(PWMD_IOAUX, PWMDIOAUX_AUX7P_MSK)
#define HSPWMD_EnoBrkCtrlPWM7P()        SET_HSPWMD_BIT(PWMD_IOAUX, PWMDIOAUX_AUX7P_MSK)
#define HSPWMD_EnoCtrlPWM8P()           CLR_HSPWMD_BIT(PWMD_IOAUX, PWMDIOAUX_AUX8P_MSK)
#define HSPWMD_EnoBrkCtrlPWM8P()        SET_HSPWMD_BIT(PWMD_IOAUX, PWMDIOAUX_AUX8P_MSK)

#define PWMDCR1_ARPE_MSK                BIT7
#define PWMD_UnbufferARR()              CLR_REG_BIT(PWMD_CR1, PWMDCR1_ARPE_MSK)
#define PWMD_BufferARR()                SET_REG_BIT(PWMD_CR1, PWMDCR1_ARPE_MSK)

#define HSPWMD_UnbufferARR()            CLR_HSPWMD_BIT(PWMD_CR1, PWMDCR1_ARPE_MSK)
#define HSPWMD_BufferARR()              SET_HSPWMD_BIT(PWMD_CR1, PWMDCR1_ARPE_MSK)

#define PWMDCR1_CMS_MSK                 (BIT6 | BIT5)
#define PWMD_SetAlignMode(n)            MODIFY_REG(PWMD_CR1,  PWMDCR1_CMS_MSK, ((n) << 5))
#define PWMD_EdgeAlignMode()            PWMD_SetAlignMode(0)
#define PWMD_CenterAlignMode1()         PWMD_SetAlignMode(1)
#define PWMD_CenterAlignMode2()         PWMD_SetAlignMode(2)
#define PWMD_CenterAlignMode3()         PWMD_SetAlignMode(3)

#define HSPWMD_SetAlignMode(n)          MODIFY_HSPWMD(PWMD_CR1,  PWMDCR1_CMS_MSK, ((n) << 5))
#define HSPWMD_EdgeAlignMode()          HSPWMD_SetAlignMode(0)
#define HSPWMD_CenterAlignMode1()       HSPWMD_SetAlignMode(1)
#define HSPWMD_CenterAlignMode2()       HSPWMD_SetAlignMode(2)
#define HSPWMD_CenterAlignMode3()       HSPWMD_SetAlignMode(3)

#define PWMDCR1_DIR_MSK                 BIT4
#define PWMD_UpCounter()                CLR_REG_BIT(PWMD_CR1, PWMDCR1_DIR_MSK)
#define PWMD_DownCounter()              SET_REG_BIT(PWMD_CR1, PWMDCR1_DIR_MSK)

#define HSPWMD_UpCounter()              CLR_HSPWMD_BIT(PWMD_CR1, PWMDCR1_DIR_MSK)
#define HSPWMD_DownCounter()            SET_HSPWMD_BIT(PWMD_CR1, PWMDCR1_DIR_MSK)

#define PWMDCR1_OPM_MSK                 BIT3
#define PWMD_ContinueMode()             CLR_REG_BIT(PWMD_CR1, PWMDCR1_OPM_MSK)
#define PWMD_OnePulseMode()             SET_REG_BIT(PWMD_CR1, PWMDCR1_OPM_MSK)

#define HSPWMD_ContinueMode()           CLR_HSPWMD_BIT(PWMD_CR1, PWMDCR1_OPM_MSK)
#define HSPWMD_OnePulseMode()           SET_HSPWMD_BIT(PWMD_CR1, PWMDCR1_OPM_MSK)

#define PWMDCR1_URS_MSK                 BIT2
#define PWMD_UpdateRequestMode1()       SET_REG_BIT(PWMD_CR1, PWMDCR1_URS_MSK)
#define PWMD_UpdateRequestMode2()       CLR_REG_BIT(PWMD_CR1, PWMDCR1_URS_MSK)

#define HSPWMD_UpdateRequestMode1()     SET_HSPWMD_BIT(PWMD_CR1, PWMDCR1_URS_MSK)
#define HSPWMD_UpdateRequestMode2()     CLR_HSPWMD_BIT(PWMD_CR1, PWMDCR1_URS_MSK)

#define PWMDCR1_UDIS_MSK                BIT1
#define PWMD_EnableUpdate()             CLR_REG_BIT(PWMD_CR1, PWMDCR1_UDIS_MSK)
#define PWMD_DisableUpdate()            SET_REG_BIT(PWMD_CR1, PWMDCR1_UDIS_MSK)

#define HSPWMD_EnableUpdate()           CLR_HSPWMD_BIT(PWMD_CR1, PWMDCR1_UDIS_MSK)
#define HSPWMD_DisableUpdate()          SET_HSPWMD_BIT(PWMD_CR1, PWMDCR1_UDIS_MSK)

#define PWMDCR1_CEN_MSK                 BIT0
#define PWMD_Run()                      SET_REG_BIT(PWMD_CR1, PWMDCR1_CEN_MSK)
#define PWMD_Stop()                     CLR_REG_BIT(PWMD_CR1, PWMDCR1_CEN_MSK)

#define HSPWMD_Run()                    SET_HSPWMD_BIT(PWMD_CR1, PWMDCR1_CEN_MSK)
#define HSPWMD_Stop()                   CLR_HSPWMD_BIT(PWMD_CR1, PWMDCR1_CEN_MSK)

#define PWMDCR2_TIS_MSK                 BIT7
#define PWMD_PWM5PToTI()                CLR_REG_BIT(PWMD_CR2, PWMDCR2_TIS_MSK)
#define PWMD_Xor5P6P7PToTI()            SET_REG_BIT(PWMD_CR2, PWMDCR2_TIS_MSK)

#define HSPWMD_PWM5PToTI()              CLR_HSPWMD_BIT(PWMD_CR2, PWMDCR2_TIS_MSK)
#define HSPWMD_Xor5P6P7PToTI()          SET_HSPWMD_BIT(PWMD_CR2, PWMDCR2_TIS_MSK)

#define PWMDCR2_MMS_MSK                 (BIT6 | BIT5 | BIT4)
#define PWMD_SelectTRGO(n)              MODIFY_REG(PWMD_CR2,  PWMDCR2_MMS_MSK, ((n) << 4))
#define PWMD_ResetAsTRGO()              PWMD_SelectTRGO(0)
#define PWMD_EnableAsTRGO()             PWMD_SelectTRGO(1)
#define PWMD_UpdateAsTRGO()             PWMD_SelectTRGO(2)
#define PWMD_MatchAsTRGO()              PWMD_SelectTRGO(3)
#define PWMD_OC5REFAsTRGO()             PWMD_SelectTRGO(4)
#define PWMD_OC6REFAsTRGO()             PWMD_SelectTRGO(5)
#define PWMD_OC7REFAsTRGO()             PWMD_SelectTRGO(6)
#define PWMD_OC8REFAsTRGO()             PWMD_SelectTRGO(7)

#define HSPWMD_SelectTRGO(n)            MODIFY_HSPWMD(PWMD_CR2,  PWMDCR2_MMS_MSK, ((n) << 4))
#define HSPWMD_ResetAsTRGO()            HSPWMD_SelectTRGO(0)
#define HSPWMD_EnableAsTRGO()           HSPWMD_SelectTRGO(1)
#define HSPWMD_UpdateAsTRGO()           HSPWMD_SelectTRGO(2)
#define HSPWMD_MatchAsTRGO()            HSPWMD_SelectTRGO(3)
#define HSPWMD_OC5REFAsTRGO()           HSPWMD_SelectTRGO(4)
#define HSPWMD_OC6REFAsTRGO()           HSPWMD_SelectTRGO(5)
#define HSPWMD_OC7REFAsTRGO()           HSPWMD_SelectTRGO(6)
#define HSPWMD_OC8REFAsTRGO()           HSPWMD_SelectTRGO(7)

#define PWMDCR2_COMS_MSK                BIT2
#define PWMD_CCOCUpdateMode0()          CLR_REG_BIT(PWMD_CR2, PWMDCR2_COMS_MSK)
#define PWMD_CCOCUpdateMode1()          SET_REG_BIT(PWMD_CR2, PWMDCR2_COMS_MSK)

#define HSPWMD_CCOCUpdateMode0()        CLR_HSPWMD_BIT(PWMD_CR2, PWMDCR2_COMS_MSK)
#define HSPWMD_CCOCUpdateMode1()        SET_HSPWMD_BIT(PWMD_CR2, PWMDCR2_COMS_MSK)

#define PWMDCR2_CCPC_MSK                BIT0
#define PWMD_UnbufferCCOC()             CLR_REG_BIT(PWMD_CR2, PWMDCR2_CCPC_MSK)
#define PWMD_BufferCCOC()               SET_REG_BIT(PWMD_CR2, PWMDCR2_CCPC_MSK)

#define HSPWMD_UnbufferCCOC()           CLR_HSPWMD_BIT(PWMD_CR2, PWMDCR2_CCPC_MSK)
#define HSPWMD_BufferCCOC()             SET_HSPWMD_BIT(PWMD_CR2, PWMDCR2_CCPC_MSK)

#define PWMDSMCR_MSM_MSK                BIT7
#define PWMD_StandaloneMode()           CLR_REG_BIT(PWMD_SMCR, PWMDSMCR_MSM_MSK)
#define PWMD_MasterSlaveMode()          SET_REG_BIT(PWMD_SMCR, PWMDSMCR_MSM_MSK)

#define HSPWMD_StandaloneMode()         CLR_HSPWMD_BIT(PWMD_SMCR, PWMDSMCR_MSM_MSK)
#define HSPWMD_MasterSlaveMode()        SET_HSPWMD_BIT(PWMD_SMCR, PWMDSMCR_MSM_MSK)

#define PWMDSMCR_TS_MSK                 (BIT6 | BIT5 | BIT4)
#define PWMD_SelectTRGI(n)              MODIFY_REG(PWMD_SMCR,  PWMDSMCR_TS_MSK, ((n) << 4))
#define PWMD_DisableTRGI()              PWMD_SelectTRGI(0)
#define PWMD_TI5FEDAsTRGI()             PWMD_SelectTRGI(4)
#define PWMD_TI5FP5AsTRGI()             PWMD_SelectTRGI(5)
#define PWMD_TI6FP6AsTRGI()             PWMD_SelectTRGI(6)
#define PWMD_ETRFAsTRGI()               PWMD_SelectTRGI(7)

#define HSPWMD_SelectTRGI(n)            MODIFY_HSPWMD(PWMD_SMCR,  PWMDSMCR_TS_MSK, ((n) << 4))
#define HSPWMD_DisableTRGI()            HSPWMD_SelectTRGI(0)
#define HSPWMD_TI5FEDAsTRGI()           HSPWMD_SelectTRGI(4)
#define HSPWMD_TI5FP5AsTRGI()           HSPWMD_SelectTRGI(5)
#define HSPWMD_TI6FP6AsTRGI()           HSPWMD_SelectTRGI(6)
#define HSPWMD_ETRFAsTRGI()             HSPWMD_SelectTRGI(7)

#define PWMDSMCR_SMS_MSK                (BIT2 | BIT1 | BIT0)
#define PWMD_SetClockMode(n)            MODIFY_REG(PWMD_SMCR,  PWMDSMCR_SMS_MSK, ((n) << 0))
#define PWMD_InternalClockMode()        PWMD_SetClockMode(0)
#define PWMD_EncoderMode1()             PWMD_SetClockMode(1)
#define PWMD_EncoderMode2()             PWMD_SetClockMode(2)
#define PWMD_EncoderMode3()             PWMD_SetClockMode(3)
#define PWMD_TriggerResetMode()         PWMD_SetClockMode(4)
#define PWMD_TriggerGateMode()          PWMD_SetClockMode(5)
#define PWMD_TriggerStartMode()         PWMD_SetClockMode(6)
#define PWMD_ExternalClockMode()        PWMD_SetClockMode(7)

#define HSPWMD_SetClockMode(n)          MODIFY_HSPWMD(PWMD_SMCR,  PWMDSMCR_SMS_MSK, ((n) << 0))
#define HSPWMD_InternalClockMode()      HSPWMD_SetClockMode(0)
#define HSPWMD_EncoderMode1()           HSPWMD_SetClockMode(1)
#define HSPWMD_EncoderMode2()           HSPWMD_SetClockMode(2)
#define HSPWMD_EncoderMode3()           HSPWMD_SetClockMode(3)
#define HSPWMD_TriggerResetMode()       HSPWMD_SetClockMode(4)
#define HSPWMD_TriggerGateMode()        HSPWMD_SetClockMode(5)
#define HSPWMD_TriggerStartMode()       HSPWMD_SetClockMode(6)
#define HSPWMD_ExternalClockMode()      HSPWMD_SetClockMode(7)

#define PWMDETR_ETP_MSK                 BIT7
#define PWMD_ETRNonInverted()           CLR_REG_BIT(PWMD_ETR, PWMDETR_ETP_MSK)
#define PWMD_ETRInverted()              SET_REG_BIT(PWMD_ETR, PWMDETR_ETP_MSK)

#define HSPWMD_ETRNonInverted()         CLR_HSPWMD_BIT(PWMD_ETR, PWMDETR_ETP_MSK)
#define HSPWMD_ETRInverted()            SET_HSPWMD_BIT(PWMD_ETR, PWMDETR_ETP_MSK)

#define PWMDETR_ECE_MSK                 BIT6
#define PWMD_DisableExternalClock2()    CLR_REG_BIT(PWMD_ETR, PWMDETR_ECE_MSK)
#define PWMD_EnableExternalClock2()     SET_REG_BIT(PWMD_ETR, PWMDETR_ECE_MSK)

#define HSPWMD_DisableExternalClock2()  CLR_HSPWMD_BIT(PWMD_ETR, PWMDETR_ECE_MSK)
#define HSPWMD_EnableExternalClock2()   SET_HSPWMD_BIT(PWMD_ETR, PWMDETR_ECE_MSK)

#define PWMDETR_ETPS_MSK                (BIT5 | BIT4)
#define PWMD_SetETRDivider(n)           MODIFY_REG(PWMD_ETR,  PWMDETR_ETPS_MSK, ((n) << 4))
#define PWMD_ETRDivider1()              PWMD_SetETRDivider(0)
#define PWMD_ETRDivider2()              PWMD_SetETRDivider(1)
#define PWMD_ETRDivider4()              PWMD_SetETRDivider(2)
#define PWMD_ETRDivider8()              PWMD_SetETRDivider(3)

#define HSPWMD_SetETRDivider(n)         MODIFY_HSPWMD(PWMD_ETR,  PWMDETR_ETPS_MSK, ((n) << 4))
#define HSPWMD_ETRDivider1()            HSPWMD_SetETRDivider(0)
#define HSPWMD_ETRDivider2()            HSPWMD_SetETRDivider(1)
#define HSPWMD_ETRDivider4()            HSPWMD_SetETRDivider(2)
#define HSPWMD_ETRDivider8()            HSPWMD_SetETRDivider(3)

#define PWMDETR_ETF_MSK                 (BIT_LN)
#define PWMD_SetETRFilter(n)            MODIFY_REG(PWMD_ETR,  PWMDETR_ETF_MSK, ((n) << 0))
#define PWMD_ETRFilter1()               PWMD_SetETRFilter(0)
#define PWMD_ETRFilter2()               PWMD_SetETRFilter(1)
#define PWMD_ETRFilter4()               PWMD_SetETRFilter(2)
#define PWMD_ETRFilter8()               PWMD_SetETRFilter(3)
#define PWMD_ETRFilter12()              PWMD_SetETRFilter(4)
#define PWMD_ETRFilter16()              PWMD_SetETRFilter(5)
#define PWMD_ETRFilter24()              PWMD_SetETRFilter(6)
#define PWMD_ETRFilter32()              PWMD_SetETRFilter(7)
#define PWMD_ETRFilter48()              PWMD_SetETRFilter(8)
#define PWMD_ETRFilter64()              PWMD_SetETRFilter(9)
#define PWMD_ETRFilter80()              PWMD_SetETRFilter(10)
#define PWMD_ETRFilter96()              PWMD_SetETRFilter(11)
#define PWMD_ETRFilter128()             PWMD_SetETRFilter(12)
#define PWMD_ETRFilter160()             PWMD_SetETRFilter(13)
#define PWMD_ETRFilter192()             PWMD_SetETRFilter(14)
#define PWMD_ETRFilter256()             PWMD_SetETRFilter(15)

#define HSPWMD_SetETRFilter(n)          MODIFY_HSPWMD(PWMD_ETR,  PWMDETR_ETF_MSK, ((n) << 0))
#define HSPWMD_ETRFilter1()             HSPWMD_SetETRFilter(0)
#define HSPWMD_ETRFilter2()             HSPWMD_SetETRFilter(1)
#define HSPWMD_ETRFilter4()             HSPWMD_SetETRFilter(2)
#define HSPWMD_ETRFilter8()             HSPWMD_SetETRFilter(3)
#define HSPWMD_ETRFilter12()            HSPWMD_SetETRFilter(4)
#define HSPWMD_ETRFilter16()            HSPWMD_SetETRFilter(5)
#define HSPWMD_ETRFilter24()            HSPWMD_SetETRFilter(6)
#define HSPWMD_ETRFilter32()            HSPWMD_SetETRFilter(7)
#define HSPWMD_ETRFilter48()            HSPWMD_SetETRFilter(8)
#define HSPWMD_ETRFilter64()            HSPWMD_SetETRFilter(9)
#define HSPWMD_ETRFilter80()            HSPWMD_SetETRFilter(10)
#define HSPWMD_ETRFilter96()            HSPWMD_SetETRFilter(11)
#define HSPWMD_ETRFilter128()           HSPWMD_SetETRFilter(12)
#define HSPWMD_ETRFilter160()           HSPWMD_SetETRFilter(13)
#define HSPWMD_ETRFilter192()           HSPWMD_SetETRFilter(14)
#define HSPWMD_ETRFilter256()           HSPWMD_SetETRFilter(15)

#define PWMDEGR_BG_MSK                  BIT7
#define PWMDEGR_TG_MSK                  BIT6
#define PWMDEGR_COMG_MSK                BIT5
#define PWMDEGR_CC8G_MSK                BIT4
#define PWMDEGR_CC7G_MSK                BIT3
#define PWMDEGR_CC6G_MSK                BIT2
#define PWMDEGR_CC5G_MSK                BIT1
#define PWMDEGR_UG_MSK                  BIT0
#define PWMD_GenerateBreakEvent()       SET_REG_BIT(PWMD_EGR, PWMDEGR_BG_MSK)
#define PWMD_GenerateTriggerEvent()     SET_REG_BIT(PWMD_EGR, PWMDEGR_TG_MSK)
#define PWMD_GenerateCOMEvent()         SET_REG_BIT(PWMD_EGR, PWMDEGR_COMG_MSK)
#define PWMD_GenerateCC8Event()         SET_REG_BIT(PWMD_EGR, PWMDEGR_CC8G_MSK)
#define PWMD_GenerateCC7Event()         SET_REG_BIT(PWMD_EGR, PWMDEGR_CC7G_MSK)
#define PWMD_GenerateCC6Event()         SET_REG_BIT(PWMD_EGR, PWMDEGR_CC6G_MSK)
#define PWMD_GenerateCC5Event()         SET_REG_BIT(PWMD_EGR, PWMDEGR_CC5G_MSK)
#define PWMD_GenerateUpdateEvent()      SET_REG_BIT(PWMD_EGR, PWMDEGR_UG_MSK)

#define HSPWMD_GenerateBreakEvent()     SET_HSPWMD_BIT(PWMD_EGR, PWMDEGR_BG_MSK)
#define HSPWMD_GenerateTriggerEvent()   SET_HSPWMD_BIT(PWMD_EGR, PWMDEGR_TG_MSK)
#define HSPWMD_GenerateCOMEvent()       SET_HSPWMD_BIT(PWMD_EGR, PWMDEGR_COMG_MSK)
#define HSPWMD_GenerateCC8Event()       SET_HSPWMD_BIT(PWMD_EGR, PWMDEGR_CC8G_MSK)
#define HSPWMD_GenerateCC7Event()       SET_HSPWMD_BIT(PWMD_EGR, PWMDEGR_CC7G_MSK)
#define HSPWMD_GenerateCC6Event()       SET_HSPWMD_BIT(PWMD_EGR, PWMDEGR_CC6G_MSK)
#define HSPWMD_GenerateCC5Event()       SET_HSPWMD_BIT(PWMD_EGR, PWMDEGR_CC5G_MSK)
#define HSPWMD_GenerateUpdateEvent()    SET_HSPWMD_BIT(PWMD_EGR, PWMDEGR_UG_MSK)

#define PWMDCCMR1_OC5CE_MSK             BIT7
#define PWMD_EnableETRFClearOC5REF()    SET_REG_BIT(PWMD_CCMR1, PWMDCCMR1_OC5CE_MSK)
#define PWMD_DisableETRFClearOC5REF()   CLR_REG_BIT(PWMD_CCMR1, PWMDCCMR1_OC5CE_MSK)

#define HSPWMD_EnableETRFClearOC5REF()  SET_HSPWMD_BIT(PWMD_CCMR1, PWMDCCMR1_OC5CE_MSK)
#define HSPWMD_DisableETRFClearOC5REF() CLR_HSPWMD_BIT(PWMD_CCMR1, PWMDCCMR1_OC5CE_MSK)

#define PWMDCCMR1_OC5M_MSK              (BIT6 | BIT5 | BIT4)
#define PWMD_SetOC5OutputMode(n)        MODIFY_REG(PWMD_CCMR1,  PWMDCCMR1_OC5M_MSK, ((n) << 4))
#define PWMD_OC5REFFrozen()             PWMD_SetOC5OutputMode(0)
#define PWMD_OC5REFHighIfMatch()        PWMD_SetOC5OutputMode(1)
#define PWMD_OC5REFLowIfMatch()         PWMD_SetOC5OutputMode(2)
#define PWMD_OC5REFToggleIfMatch()      PWMD_SetOC5OutputMode(3)
#define PWMD_OC5REFForceLow()           PWMD_SetOC5OutputMode(4)
#define PWMD_OC5REFForceHigh()          PWMD_SetOC5OutputMode(5)
#define PWMD_OC5REFPWMMode1()           PWMD_SetOC5OutputMode(6)
#define PWMD_OC5REFPWMMode2()           PWMD_SetOC5OutputMode(7)

#define HSPWMD_SetOC5OutputMode(n)      MODIFY_HSPWMD(PWMD_CCMR1,  PWMDCCMR1_OC5M_MSK, ((n) << 4))
#define HSPWMD_OC5REFFrozen()           HSPWMD_SetOC5OutputMode(0)
#define HSPWMD_OC5REFHighIfMatch()      HSPWMD_SetOC5OutputMode(1)
#define HSPWMD_OC5REFLowIfMatch()       HSPWMD_SetOC5OutputMode(2)
#define HSPWMD_OC5REFToggleIfMatch()    HSPWMD_SetOC5OutputMode(3)
#define HSPWMD_OC5REFForceLow()         HSPWMD_SetOC5OutputMode(4)
#define HSPWMD_OC5REFForceHigh()        HSPWMD_SetOC5OutputMode(5)
#define HSPWMD_OC5REFPWMMode1()         HSPWMD_SetOC5OutputMode(6)
#define HSPWMD_OC5REFPWMMode2()         HSPWMD_SetOC5OutputMode(7)

#define PWMDCCMR1_OC5PE_MSK             BIT3
#define PWMD_UnbufferCCR5()             CLR_REG_BIT(PWMD_CCMR1, PWMDCCMR1_OC5PE_MSK)
#define PWMD_BufferCCR5()               SET_REG_BIT(PWMD_CCMR1, PWMDCCMR1_OC5PE_MSK)

#define HSPWMD_UnbufferCCR5()           CLR_HSPWMD_BIT(PWMD_CCMR1, PWMDCCMR1_OC5PE_MSK)
#define HSPWMD_BufferCCR5()             SET_HSPWMD_BIT(PWMD_CCMR1, PWMDCCMR1_OC5PE_MSK)

#define PWMDCCMR1_OC5FE_MSK             BIT2
#define PWMD_DisableOC5FastMode()       CLR_REG_BIT(PWMD_CCMR1, PWMDCCMR1_OC5FE_MSK)
#define PWMD_EnableOC5FastMode()        SET_REG_BIT(PWMD_CCMR1, PWMDCCMR1_OC5FE_MSK)

#define HSPWMD_DisableOC5FastMode()     CLR_HSPWMD_BIT(PWMD_CCMR1, PWMDCCMR1_OC5FE_MSK)
#define HSPWMD_EnableOC5FastMode()      SET_HSPWMD_BIT(PWMD_CCMR1, PWMDCCMR1_OC5FE_MSK)

#define PWMDCCMR1_CC5S_MSK              (BIT1 | BIT0)
#define PWMD_SetCC5Mode(n)              MODIFY_REG(PWMD_CCMR1,  PWMDCCMR1_CC5S_MSK, ((n) << 0))
#define PWMD_CC5Output()                PWMD_SetCC5Mode(0)
#define PWMD_CC5CaptureTI5FP5()         PWMD_SetCC5Mode(1)
#define PWMD_CC5CaptureTI6FP5()         PWMD_SetCC5Mode(2)
#define PWMD_CC5CaptureTRC()            PWMD_SetCC5Mode(3)

#define HSPWMD_SetCC5Mode(n)            MODIFY_HSPWMD(PWMD_CCMR1,  PWMDCCMR1_CC5S_MSK, ((n) << 0))
#define HSPWMD_CC5Output()              HSPWMD_SetCC5Mode(0)
#define HSPWMD_CC5CaptureTI5FP5()       HSPWMD_SetCC5Mode(1)
#define HSPWMD_CC5CaptureTI6FP5()       HSPWMD_SetCC5Mode(2)
#define HSPWMD_CC5CaptureTRC()          HSPWMD_SetCC5Mode(3)

#define PWMDCCMR1_IC5F_MSK              (BIT_HN)
#define PWMD_SetIC5Filter(n)            MODIFY_REG(PWMD_CCMR1,  PWMDCCMR1_IC5F_MSK, ((n) << 4))
#define PWMD_IC5Filter1()               PWMD_SetIC5Filter(0)
#define PWMD_IC5Filter2()               PWMD_SetIC5Filter(1)
#define PWMD_IC5Filter4()               PWMD_SetIC5Filter(2)
#define PWMD_IC5Filter8()               PWMD_SetIC5Filter(3)
#define PWMD_IC5Filter12()              PWMD_SetIC5Filter(4)
#define PWMD_IC5Filter16()              PWMD_SetIC5Filter(5)
#define PWMD_IC5Filter24()              PWMD_SetIC5Filter(6)
#define PWMD_IC5Filter32()              PWMD_SetIC5Filter(7)
#define PWMD_IC5Filter48()              PWMD_SetIC5Filter(8)
#define PWMD_IC5Filter64()              PWMD_SetIC5Filter(9)
#define PWMD_IC5Filter80()              PWMD_SetIC5Filter(10)
#define PWMD_IC5Filter96()              PWMD_SetIC5Filter(11)
#define PWMD_IC5Filter128()             PWMD_SetIC5Filter(12)
#define PWMD_IC5Filter160()             PWMD_SetIC5Filter(13)
#define PWMD_IC5Filter192()             PWMD_SetIC5Filter(14)
#define PWMD_IC5Filter256()             PWMD_SetIC5Filter(15)

#define HSPWMD_SetIC5Filter(n)          MODIFY_HSPWMD(PWMD_CCMR1,  PWMDCCMR1_IC5F_MSK, ((n) << 4))
#define HSPWMD_IC5Filter1()             HSPWMD_SetIC5Filter(0)
#define HSPWMD_IC5Filter2()             HSPWMD_SetIC5Filter(1)
#define HSPWMD_IC5Filter4()             HSPWMD_SetIC5Filter(2)
#define HSPWMD_IC5Filter8()             HSPWMD_SetIC5Filter(3)
#define HSPWMD_IC5Filter12()            HSPWMD_SetIC5Filter(4)
#define HSPWMD_IC5Filter16()            HSPWMD_SetIC5Filter(5)
#define HSPWMD_IC5Filter24()            HSPWMD_SetIC5Filter(6)
#define HSPWMD_IC5Filter32()            HSPWMD_SetIC5Filter(7)
#define HSPWMD_IC5Filter48()            HSPWMD_SetIC5Filter(8)
#define HSPWMD_IC5Filter64()            HSPWMD_SetIC5Filter(9)
#define HSPWMD_IC5Filter80()            HSPWMD_SetIC5Filter(10)
#define HSPWMD_IC5Filter96()            HSPWMD_SetIC5Filter(11)
#define HSPWMD_IC5Filter128()           HSPWMD_SetIC5Filter(12)
#define HSPWMD_IC5Filter160()           HSPWMD_SetIC5Filter(13)
#define HSPWMD_IC5Filter192()           HSPWMD_SetIC5Filter(14)
#define HSPWMD_IC5Filter256()           HSPWMD_SetIC5Filter(15)

#define PWMDCCMR1_IC5PS_MSK             (BIT3 | BIT2)
#define PWMD_SetIC5Divider(n)           MODIFY_REG(PWMD_CCMR1,  PWMDCCMR1_IC5PS_MSK, ((n) << 2))
#define PWMD_IC5Divider1()              PWMD_SetIC5Divider(0)
#define PWMD_IC5Divider2()              PWMD_SetIC5Divider(1)
#define PWMD_IC5Divider4()              PWMD_SetIC5Divider(2)
#define PWMD_IC5Divider8()              PWMD_SetIC5Divider(3)

#define HSPWMD_SetIC5Divider(n)         MODIFY_HSPWMD(PWMD_CCMR1,  PWMDCCMR1_IC5PS_MSK, ((n) << 2))
#define HSPWMD_IC5Divider1()            HSPWMD_SetIC5Divider(0)
#define HSPWMD_IC5Divider2()            HSPWMD_SetIC5Divider(1)
#define HSPWMD_IC5Divider4()            HSPWMD_SetIC5Divider(2)
#define HSPWMD_IC5Divider8()            HSPWMD_SetIC5Divider(3)

#define PWMDCCMR2_OC6CE_MSK             BIT7
#define PWMD_EnableETRFClearOC6REF()    SET_REG_BIT(PWMD_CCMR2, PWMDCCMR2_OC6CE_MSK)
#define PWMD_DisableETRFClearOC6REF()   CLR_REG_BIT(PWMD_CCMR2, PWMDCCMR2_OC6CE_MSK)

#define HSPWMD_EnableETRFClearOC6REF()  SET_HSPWMD_BIT(PWMD_CCMR2, PWMDCCMR2_OC6CE_MSK)
#define HSPWMD_DisableETRFClearOC6REF() CLR_HSPWMD_BIT(PWMD_CCMR2, PWMDCCMR2_OC6CE_MSK)

#define PWMDCCMR2_OC6M_MSK              (BIT6 | BIT5 | BIT4)
#define PWMD_SetOC6OutputMode(n)        MODIFY_REG(PWMD_CCMR2,  PWMDCCMR2_OC6M_MSK, ((n) << 4))
#define PWMD_OC6REFFrozen()             PWMD_SetOC6OutputMode(0)
#define PWMD_OC6REFHighIfMatch()        PWMD_SetOC6OutputMode(1)
#define PWMD_OC6REFLowIfMatch()         PWMD_SetOC6OutputMode(2)
#define PWMD_OC6REFToggleIfMatch()      PWMD_SetOC6OutputMode(3)
#define PWMD_OC6REFForceLow()           PWMD_SetOC6OutputMode(4)
#define PWMD_OC6REFForceHigh()          PWMD_SetOC6OutputMode(5)
#define PWMD_OC6REFPWMMode1()           PWMD_SetOC6OutputMode(6)
#define PWMD_OC6REFPWMMode2()           PWMD_SetOC6OutputMode(7)

#define HSPWMD_SetOC6OutputMode(n)      MODIFY_HSPWMD(PWMD_CCMR2,  PWMDCCMR2_OC6M_MSK, ((n) << 4))
#define HSPWMD_OC6REFFrozen()           HSPWMD_SetOC6OutputMode(0)
#define HSPWMD_OC6REFHighIfMatch()      HSPWMD_SetOC6OutputMode(1)
#define HSPWMD_OC6REFLowIfMatch()       HSPWMD_SetOC6OutputMode(2)
#define HSPWMD_OC6REFToggleIfMatch()    HSPWMD_SetOC6OutputMode(3)
#define HSPWMD_OC6REFForceLow()         HSPWMD_SetOC6OutputMode(4)
#define HSPWMD_OC6REFForceHigh()        HSPWMD_SetOC6OutputMode(5)
#define HSPWMD_OC6REFPWMMode1()         HSPWMD_SetOC6OutputMode(6)
#define HSPWMD_OC6REFPWMMode2()         HSPWMD_SetOC6OutputMode(7)

#define PWMDCCMR2_OC6PE_MSK             BIT3
#define PWMD_UnbufferCCR6()             CLR_REG_BIT(PWMD_CCMR2, PWMDCCMR2_OC6PE_MSK)
#define PWMD_BufferCCR6()               SET_REG_BIT(PWMD_CCMR2, PWMDCCMR2_OC6PE_MSK)

#define HSPWMD_UnbufferCCR6()           CLR_HSPWMD_BIT(PWMD_CCMR2, PWMDCCMR2_OC6PE_MSK)
#define HSPWMD_BufferCCR6()             SET_HSPWMD_BIT(PWMD_CCMR2, PWMDCCMR2_OC6PE_MSK)

#define PWMDCCMR2_OC6FE_MSK             BIT2
#define PWMD_DisableOC6FastMode()       CLR_REG_BIT(PWMD_CCMR2, PWMDCCMR2_OC6FE_MSK)
#define PWMD_EnableOC6FastMode()        SET_REG_BIT(PWMD_CCMR2, PWMDCCMR2_OC6FE_MSK)

#define HSPWMD_DisableOC6FastMode()     CLR_HSPWMD_BIT(PWMD_CCMR2, PWMDCCMR2_OC6FE_MSK)
#define HSPWMD_EnableOC6FastMode()      SET_HSPWMD_BIT(PWMD_CCMR2, PWMDCCMR2_OC6FE_MSK)

#define PWMDCCMR2_CC6S_MSK              (BIT1 | BIT0)
#define PWMD_SetCC6Mode(n)              MODIFY_REG(PWMD_CCMR2,  PWMDCCMR2_CC6S_MSK, ((n) << 0))
#define PWMD_CC6Output()                PWMD_SetCC6Mode(0)
#define PWMD_CC6CaptureTI6FP6()         PWMD_SetCC6Mode(1)
#define PWMD_CC6CaptureTI5FP6()         PWMD_SetCC6Mode(2)
#define PWMD_CC6CaptureTRC()            PWMD_SetCC6Mode(3)

#define HSPWMD_SetCC6Mode(n)            MODIFY_HSPWMD(PWMD_CCMR2,  PWMDCCMR2_CC6S_MSK, ((n) << 0))
#define HSPWMD_CC6Output()              HSPWMD_SetCC6Mode(0)
#define HSPWMD_CC6CaptureTI6FP6()       HSPWMD_SetCC6Mode(1)
#define HSPWMD_CC6CaptureTI5FP6()       HSPWMD_SetCC6Mode(2)
#define HSPWMD_CC6CaptureTRC()          HSPWMD_SetCC6Mode(3)

#define PWMDCCMR2_IC6F_MSK              (BIT_HN)
#define PWMD_SetIC6Filter(n)            MODIFY_REG(PWMD_CCMR2,  PWMDCCMR2_IC6F_MSK, ((n) << 4))
#define PWMD_IC6Filter1()               PWMD_SetIC6Filter(0)
#define PWMD_IC6Filter2()               PWMD_SetIC6Filter(1)
#define PWMD_IC6Filter4()               PWMD_SetIC6Filter(2)
#define PWMD_IC6Filter8()               PWMD_SetIC6Filter(3)
#define PWMD_IC6Filter12()              PWMD_SetIC6Filter(4)
#define PWMD_IC6Filter16()              PWMD_SetIC6Filter(5)
#define PWMD_IC6Filter24()              PWMD_SetIC6Filter(6)
#define PWMD_IC6Filter32()              PWMD_SetIC6Filter(7)
#define PWMD_IC6Filter48()              PWMD_SetIC6Filter(8)
#define PWMD_IC6Filter64()              PWMD_SetIC6Filter(9)
#define PWMD_IC6Filter80()              PWMD_SetIC6Filter(10)
#define PWMD_IC6Filter96()              PWMD_SetIC6Filter(11)
#define PWMD_IC6Filter128()             PWMD_SetIC6Filter(12)
#define PWMD_IC6Filter160()             PWMD_SetIC6Filter(13)
#define PWMD_IC6Filter192()             PWMD_SetIC6Filter(14)
#define PWMD_IC6Filter256()             PWMD_SetIC6Filter(15)

#define HSPWMD_SetIC6Filter(n)          MODIFY_HSPWMD(PWMD_CCMR2,  PWMDCCMR2_IC6F_MSK, ((n) << 4))
#define HSPWMD_IC6Filter1()             HSPWMD_SetIC6Filter(0)
#define HSPWMD_IC6Filter2()             HSPWMD_SetIC6Filter(1)
#define HSPWMD_IC6Filter4()             HSPWMD_SetIC6Filter(2)
#define HSPWMD_IC6Filter8()             HSPWMD_SetIC6Filter(3)
#define HSPWMD_IC6Filter12()            HSPWMD_SetIC6Filter(4)
#define HSPWMD_IC6Filter16()            HSPWMD_SetIC6Filter(5)
#define HSPWMD_IC6Filter24()            HSPWMD_SetIC6Filter(6)
#define HSPWMD_IC6Filter32()            HSPWMD_SetIC6Filter(7)
#define HSPWMD_IC6Filter48()            HSPWMD_SetIC6Filter(8)
#define HSPWMD_IC6Filter64()            HSPWMD_SetIC6Filter(9)
#define HSPWMD_IC6Filter80()            HSPWMD_SetIC6Filter(10)
#define HSPWMD_IC6Filter96()            HSPWMD_SetIC6Filter(11)
#define HSPWMD_IC6Filter128()           HSPWMD_SetIC6Filter(12)
#define HSPWMD_IC6Filter160()           HSPWMD_SetIC6Filter(13)
#define HSPWMD_IC6Filter192()           HSPWMD_SetIC6Filter(14)
#define HSPWMD_IC6Filter256()           HSPWMD_SetIC6Filter(15)

#define PWMDCCMR2_IC6PS_MSK             (BIT3 | BIT2)
#define PWMD_SetIC6Divider(n)           MODIFY_REG(PWMD_CCMR2,  PWMDCCMR2_IC6PS_MSK, ((n) << 2))
#define PWMD_IC6Divider1()              PWMD_SetIC6Divider(0)
#define PWMD_IC6Divider2()              PWMD_SetIC6Divider(1)
#define PWMD_IC6Divider4()              PWMD_SetIC6Divider(2)
#define PWMD_IC6Divider8()              PWMD_SetIC6Divider(3)

#define HSPWMD_SetIC6Divider(n)         MODIFY_HSPWMD(PWMD_CCMR2,  PWMDCCMR2_IC6PS_MSK, ((n) << 2))
#define HSPWMD_IC6Divider1()            HSPWMD_SetIC6Divider(0)
#define HSPWMD_IC6Divider2()            HSPWMD_SetIC6Divider(1)
#define HSPWMD_IC6Divider4()            HSPWMD_SetIC6Divider(2)
#define HSPWMD_IC6Divider8()            HSPWMD_SetIC6Divider(3)

#define PWMDCCMR3_OC7CE_MSK             BIT7
#define PWMD_EnableETRFClearOC7REF()    SET_REG_BIT(PWMD_CCMR3, PWMDCCMR3_OC7CE_MSK)
#define PWMD_DisableETRFClearOC7REF()   CLR_REG_BIT(PWMD_CCMR3, PWMDCCMR3_OC7CE_MSK)

#define HSPWMD_EnableETRFClearOC7REF()  SET_HSPWMD_BIT(PWMD_CCMR3, PWMDCCMR3_OC7CE_MSK)
#define HSPWMD_DisableETRFClearOC7REF() CLR_HSPWMD_BIT(PWMD_CCMR3, PWMDCCMR3_OC7CE_MSK)

#define PWMDCCMR3_OC7M_MSK              (BIT6 | BIT5 | BIT4)
#define PWMD_SetOC7OutputMode(n)        MODIFY_REG(PWMD_CCMR3,  PWMDCCMR3_OC7M_MSK, ((n) << 4))
#define PWMD_OC7REFFrozen()             PWMD_SetOC7OutputMode(0)
#define PWMD_OC7REFHighIfMatch()        PWMD_SetOC7OutputMode(1)
#define PWMD_OC7REFLowIfMatch()         PWMD_SetOC7OutputMode(2)
#define PWMD_OC7REFToggleIfMatch()      PWMD_SetOC7OutputMode(3)
#define PWMD_OC7REFForceLow()           PWMD_SetOC7OutputMode(4)
#define PWMD_OC7REFForceHigh()          PWMD_SetOC7OutputMode(5)
#define PWMD_OC7REFPWMMode1()           PWMD_SetOC7OutputMode(6)
#define PWMD_OC7REFPWMMode2()           PWMD_SetOC7OutputMode(7)

#define HSPWMD_SetOC7OutputMode(n)      MODIFY_HSPWMD(PWMD_CCMR3,  PWMDCCMR3_OC7M_MSK, ((n) << 4))
#define HSPWMD_OC7REFFrozen()           HSPWMD_SetOC7OutputMode(0)
#define HSPWMD_OC7REFHighIfMatch()      HSPWMD_SetOC7OutputMode(1)
#define HSPWMD_OC7REFLowIfMatch()       HSPWMD_SetOC7OutputMode(2)
#define HSPWMD_OC7REFToggleIfMatch()    HSPWMD_SetOC7OutputMode(3)
#define HSPWMD_OC7REFForceLow()         HSPWMD_SetOC7OutputMode(4)
#define HSPWMD_OC7REFForceHigh()        HSPWMD_SetOC7OutputMode(5)
#define HSPWMD_OC7REFPWMMode1()         HSPWMD_SetOC7OutputMode(6)
#define HSPWMD_OC7REFPWMMode2()         HSPWMD_SetOC7OutputMode(7)

#define PWMDCCMR3_OC7PE_MSK             BIT3
#define PWMD_UnbufferCCR7()             CLR_REG_BIT(PWMD_CCMR3, PWMDCCMR3_OC7PE_MSK)
#define PWMD_BufferCCR7()               SET_REG_BIT(PWMD_CCMR3, PWMDCCMR3_OC7PE_MSK)

#define HSPWMD_UnbufferCCR7()           CLR_HSPWMD_BIT(PWMD_CCMR3, PWMDCCMR3_OC7PE_MSK)
#define HSPWMD_BufferCCR7()             SET_HSPWMD_BIT(PWMD_CCMR3, PWMDCCMR3_OC7PE_MSK)

#define PWMDCCMR3_OC7FE_MSK             BIT2
#define PWMD_DisableOC7FastMode()       CLR_REG_BIT(PWMD_CCMR3, PWMDCCMR3_OC7FE_MSK)
#define PWMD_EnableOC7FastMode()        SET_REG_BIT(PWMD_CCMR3, PWMDCCMR3_OC7FE_MSK)

#define HSPWMD_DisableOC7FastMode()     CLR_HSPWMD_BIT(PWMD_CCMR3, PWMDCCMR3_OC7FE_MSK)
#define HSPWMD_EnableOC7FastMode()      SET_HSPWMD_BIT(PWMD_CCMR3, PWMDCCMR3_OC7FE_MSK)

#define PWMDCCMR3_CC7S_MSK              (BIT1 | BIT0)
#define PWMD_SetCC7Mode(n)              MODIFY_REG(PWMD_CCMR3,  PWMDCCMR3_CC7S_MSK, ((n) << 0))
#define PWMD_CC7Output()                PWMD_SetCC7Mode(0)
#define PWMD_CC7CaptureTI7FP7()         PWMD_SetCC7Mode(1)
#define PWMD_CC7CaptureTI8FP7()         PWMD_SetCC7Mode(2)
#define PWMD_CC7CaptureTRC()            PWMD_SetCC7Mode(3)

#define HSPWMD_SetCC7Mode(n)            MODIFY_HSPWMD(PWMD_CCMR3,  PWMDCCMR3_CC7S_MSK, ((n) << 0))
#define HSPWMD_CC7Output()              HSPWMD_SetCC7Mode(0)
#define HSPWMD_CC7CaptureTI7FP7()       HSPWMD_SetCC7Mode(1)
#define HSPWMD_CC7CaptureTI8FP7()       HSPWMD_SetCC7Mode(2)
#define HSPWMD_CC7CaptureTRC()          HSPWMD_SetCC7Mode(3)

#define PWMDCCMR3_IC7F_MSK              (BIT_HN)
#define PWMD_SetIC7Filter(n)            MODIFY_REG(PWMD_CCMR3,  PWMDCCMR3_IC7F_MSK, ((n) << 4))
#define PWMD_IC7Filter1()               PWMD_SetIC7Filter(0)
#define PWMD_IC7Filter2()               PWMD_SetIC7Filter(1)
#define PWMD_IC7Filter4()               PWMD_SetIC7Filter(2)
#define PWMD_IC7Filter8()               PWMD_SetIC7Filter(3)
#define PWMD_IC7Filter12()              PWMD_SetIC7Filter(4)
#define PWMD_IC7Filter16()              PWMD_SetIC7Filter(5)
#define PWMD_IC7Filter24()              PWMD_SetIC7Filter(6)
#define PWMD_IC7Filter32()              PWMD_SetIC7Filter(7)
#define PWMD_IC7Filter48()              PWMD_SetIC7Filter(8)
#define PWMD_IC7Filter64()              PWMD_SetIC7Filter(9)
#define PWMD_IC7Filter80()              PWMD_SetIC7Filter(10)
#define PWMD_IC7Filter96()              PWMD_SetIC7Filter(11)
#define PWMD_IC7Filter128()             PWMD_SetIC7Filter(12)
#define PWMD_IC7Filter160()             PWMD_SetIC7Filter(13)
#define PWMD_IC7Filter192()             PWMD_SetIC7Filter(14)
#define PWMD_IC7Filter256()             PWMD_SetIC7Filter(15)

#define HSPWMD_SetIC7Filter(n)          MODIFY_HSPWMD(PWMD_CCMR3,  PWMDCCMR3_IC7F_MSK, ((n) << 4))
#define HSPWMD_IC7Filter1()             HSPWMD_SetIC7Filter(0)
#define HSPWMD_IC7Filter2()             HSPWMD_SetIC7Filter(1)
#define HSPWMD_IC7Filter4()             HSPWMD_SetIC7Filter(2)
#define HSPWMD_IC7Filter8()             HSPWMD_SetIC7Filter(3)
#define HSPWMD_IC7Filter12()            HSPWMD_SetIC7Filter(4)
#define HSPWMD_IC7Filter16()            HSPWMD_SetIC7Filter(5)
#define HSPWMD_IC7Filter24()            HSPWMD_SetIC7Filter(6)
#define HSPWMD_IC7Filter32()            HSPWMD_SetIC7Filter(7)
#define HSPWMD_IC7Filter48()            HSPWMD_SetIC7Filter(8)
#define HSPWMD_IC7Filter64()            HSPWMD_SetIC7Filter(9)
#define HSPWMD_IC7Filter80()            HSPWMD_SetIC7Filter(10)
#define HSPWMD_IC7Filter96()            HSPWMD_SetIC7Filter(11)
#define HSPWMD_IC7Filter128()           HSPWMD_SetIC7Filter(12)
#define HSPWMD_IC7Filter160()           HSPWMD_SetIC7Filter(13)
#define HSPWMD_IC7Filter192()           HSPWMD_SetIC7Filter(14)
#define HSPWMD_IC7Filter256()           HSPWMD_SetIC7Filter(15)

#define PWMDCCMR3_IC7PS_MSK             (BIT3 | BIT2)
#define PWMD_SetIC7Divider(n)           MODIFY_REG(PWMD_CCMR3,  PWMDCCMR3_IC7PS_MSK, ((n) << 2))
#define PWMD_IC7Divider1()              PWMD_SetIC7Divider(0)
#define PWMD_IC7Divider2()              PWMD_SetIC7Divider(1)
#define PWMD_IC7Divider4()              PWMD_SetIC7Divider(2)
#define PWMD_IC7Divider8()              PWMD_SetIC7Divider(3)

#define HSPWMD_SetIC7Divider(n)         MODIFY_HSPWMD(PWMD_CCMR3,  PWMDCCMR3_IC7PS_MSK, ((n) << 2))
#define HSPWMD_IC7Divider1()            HSPWMD_SetIC7Divider(0)
#define HSPWMD_IC7Divider2()            HSPWMD_SetIC7Divider(1)
#define HSPWMD_IC7Divider4()            HSPWMD_SetIC7Divider(2)
#define HSPWMD_IC7Divider8()            HSPWMD_SetIC7Divider(3)

#define PWMDCCMR4_OC8CE_MSK             BIT7
#define PWMD_EnableETRFClearOC8REF()    SET_REG_BIT(PWMD_CCMR4, PWMDCCMR4_OC8CE_MSK)
#define PWMD_DisableETRFClearOC8REF()   CLR_REG_BIT(PWMD_CCMR4, PWMDCCMR4_OC8CE_MSK)

#define HSPWMD_EnableETRFClearOC8REF()  SET_HSPWMD_BIT(PWMD_CCMR4, PWMDCCMR4_OC8CE_MSK)
#define HSPWMD_DisableETRFClearOC8REF() CLR_HSPWMD_BIT(PWMD_CCMR4, PWMDCCMR4_OC8CE_MSK)

#define PWMDCCMR4_OC8M_MSK              (BIT6 | BIT5 | BIT4)
#define PWMD_SetOC8OutputMode(n)        MODIFY_REG(PWMD_CCMR4,  PWMDCCMR4_OC8M_MSK, ((n) << 4))
#define PWMD_OC8REFFrozen()             PWMD_SetOC8OutputMode(0)
#define PWMD_OC8REFHighIfMatch()        PWMD_SetOC8OutputMode(1)
#define PWMD_OC8REFLowIfMatch()         PWMD_SetOC8OutputMode(2)
#define PWMD_OC8REFToggleIfMatch()      PWMD_SetOC8OutputMode(3)
#define PWMD_OC8REFForceLow()           PWMD_SetOC8OutputMode(4)
#define PWMD_OC8REFForceHigh()          PWMD_SetOC8OutputMode(5)
#define PWMD_OC8REFPWMMode1()           PWMD_SetOC8OutputMode(6)
#define PWMD_OC8REFPWMMode2()           PWMD_SetOC8OutputMode(7)

#define HSPWMD_SetOC8OutputMode(n)      MODIFY_HSPWMD(PWMD_CCMR4,  PWMDCCMR4_OC8M_MSK, ((n) << 4))
#define HSPWMD_OC8REFFrozen()           HSPWMD_SetOC8OutputMode(0)
#define HSPWMD_OC8REFHighIfMatch()      HSPWMD_SetOC8OutputMode(1)
#define HSPWMD_OC8REFLowIfMatch()       HSPWMD_SetOC8OutputMode(2)
#define HSPWMD_OC8REFToggleIfMatch()    HSPWMD_SetOC8OutputMode(3)
#define HSPWMD_OC8REFForceLow()         HSPWMD_SetOC8OutputMode(4)
#define HSPWMD_OC8REFForceHigh()        HSPWMD_SetOC8OutputMode(5)
#define HSPWMD_OC8REFPWMMode1()         HSPWMD_SetOC8OutputMode(6)
#define HSPWMD_OC8REFPWMMode2()         HSPWMD_SetOC8OutputMode(7)

#define PWMDCCMR4_OC8PE_MSK             BIT3
#define PWMD_UnbufferCCR8()             CLR_REG_BIT(PWMD_CCMR4, PWMDCCMR4_OC8PE_MSK)
#define PWMD_BufferCCR8()               SET_REG_BIT(PWMD_CCMR4, PWMDCCMR4_OC8PE_MSK)

#define HSPWMD_UnbufferCCR8()           CLR_HSPWMD_BIT(PWMD_CCMR4, PWMDCCMR4_OC8PE_MSK)
#define HSPWMD_BufferCCR8()             SET_HSPWMD_BIT(PWMD_CCMR4, PWMDCCMR4_OC8PE_MSK)

#define PWMDCCMR4_OC8FE_MSK             BIT2
#define PWMD_DisableOC8FastMode()       CLR_REG_BIT(PWMD_CCMR4, PWMDCCMR4_OC8FE_MSK)
#define PWMD_EnableOC8FastMode()        SET_REG_BIT(PWMD_CCMR4, PWMDCCMR4_OC8FE_MSK)

#define HSPWMD_DisableOC8FastMode()     CLR_HSPWMD_BIT(PWMD_CCMR4, PWMDCCMR4_OC8FE_MSK)
#define HSPWMD_EnableOC8FastMode()      SET_HSPWMD_BIT(PWMD_CCMR4, PWMDCCMR4_OC8FE_MSK)

#define PWMDCCMR4_CC8S_MSK              (BIT1 | BIT0)
#define PWMD_SetCC8Mode(n)              MODIFY_REG(PWMD_CCMR4,  PWMDCCMR4_CC8S_MSK, ((n) << 0))
#define PWMD_CC8Output()                PWMD_SetCC8Mode(0)
#define PWMD_CC8CaptureTI8FP8()         PWMD_SetCC8Mode(1)
#define PWMD_CC8CaptureTI7FP8()         PWMD_SetCC8Mode(2)
#define PWMD_CC8CaptureTRC()            PWMD_SetCC8Mode(3)

#define HSPWMD_SetCC8Mode(n)            MODIFY_HSPWMD(PWMD_CCMR4,  PWMDCCMR4_CC8S_MSK, ((n) << 0))
#define HSPWMD_CC8Output()              HSPWMD_SetCC8Mode(0)
#define HSPWMD_CC8CaptureTI8FP8()       HSPWMD_SetCC8Mode(1)
#define HSPWMD_CC8CaptureTI7FP8()       HSPWMD_SetCC8Mode(2)
#define HSPWMD_CC8CaptureTRC()          HSPWMD_SetCC8Mode(3)

#define PWMDCCMR4_IC8F_MSK              (BIT_HN)
#define PWMD_SetIC8Filter(n)            MODIFY_REG(PWMD_CCMR4,  PWMDCCMR4_IC8F_MSK, ((n) << 4))
#define PWMD_IC8Filter1()               PWMD_SetIC8Filter(0)
#define PWMD_IC8Filter2()               PWMD_SetIC8Filter(1)
#define PWMD_IC8Filter4()               PWMD_SetIC8Filter(2)
#define PWMD_IC8Filter8()               PWMD_SetIC8Filter(3)
#define PWMD_IC8Filter12()              PWMD_SetIC8Filter(4)
#define PWMD_IC8Filter16()              PWMD_SetIC8Filter(5)
#define PWMD_IC8Filter24()              PWMD_SetIC8Filter(6)
#define PWMD_IC8Filter32()              PWMD_SetIC8Filter(7)
#define PWMD_IC8Filter48()              PWMD_SetIC8Filter(8)
#define PWMD_IC8Filter64()              PWMD_SetIC8Filter(9)
#define PWMD_IC8Filter80()              PWMD_SetIC8Filter(10)
#define PWMD_IC8Filter96()              PWMD_SetIC8Filter(11)
#define PWMD_IC8Filter128()             PWMD_SetIC8Filter(12)
#define PWMD_IC8Filter160()             PWMD_SetIC8Filter(13)
#define PWMD_IC8Filter192()             PWMD_SetIC8Filter(14)
#define PWMD_IC8Filter256()             PWMD_SetIC8Filter(15)

#define HSPWMD_SetIC8Filter(n)          MODIFY_HSPWMD(PWMD_CCMR4,  PWMDCCMR4_IC8F_MSK, ((n) << 4))
#define HSPWMD_IC8Filter1()             HSPWMD_SetIC8Filter(0)
#define HSPWMD_IC8Filter2()             HSPWMD_SetIC8Filter(1)
#define HSPWMD_IC8Filter4()             HSPWMD_SetIC8Filter(2)
#define HSPWMD_IC8Filter8()             HSPWMD_SetIC8Filter(3)
#define HSPWMD_IC8Filter12()            HSPWMD_SetIC8Filter(4)
#define HSPWMD_IC8Filter16()            HSPWMD_SetIC8Filter(5)
#define HSPWMD_IC8Filter24()            HSPWMD_SetIC8Filter(6)
#define HSPWMD_IC8Filter32()            HSPWMD_SetIC8Filter(7)
#define HSPWMD_IC8Filter48()            HSPWMD_SetIC8Filter(8)
#define HSPWMD_IC8Filter64()            HSPWMD_SetIC8Filter(9)
#define HSPWMD_IC8Filter80()            HSPWMD_SetIC8Filter(10)
#define HSPWMD_IC8Filter96()            HSPWMD_SetIC8Filter(11)
#define HSPWMD_IC8Filter128()           HSPWMD_SetIC8Filter(12)
#define HSPWMD_IC8Filter160()           HSPWMD_SetIC8Filter(13)
#define HSPWMD_IC8Filter192()           HSPWMD_SetIC8Filter(14)
#define HSPWMD_IC8Filter256()           HSPWMD_SetIC8Filter(15)

#define PWMDCCMR4_IC8PS_MSK             (BIT3 | BIT2)
#define PWMD_SetIC8Divider(n)           MODIFY_REG(PWMD_CCMR4,  PWMDCCMR4_IC8PS_MSK, ((n) << 2))
#define PWMD_IC8Divider1()              PWMD_SetIC8Divider(0)
#define PWMD_IC8Divider2()              PWMD_SetIC8Divider(1)
#define PWMD_IC8Divider4()              PWMD_SetIC8Divider(2)
#define PWMD_IC8Divider8()              PWMD_SetIC8Divider(3)

#define HSPWMD_SetIC8Divider(n)         MODIFY_HSPWMD(PWMD_CCMR4,  PWMDCCMR4_IC8PS_MSK, ((n) << 2))
#define HSPWMD_IC8Divider1()            HSPWMD_SetIC8Divider(0)
#define HSPWMD_IC8Divider2()            HSPWMD_SetIC8Divider(1)
#define HSPWMD_IC8Divider4()            HSPWMD_SetIC8Divider(2)
#define HSPWMD_IC8Divider8()            HSPWMD_SetIC8Divider(3)

#define PWMDCCER1_CC5E_MSK              BIT0
#define PWMD_CC5PEnable()               SET_REG_BIT(PWMD_CCER1, PWMDCCER1_CC5E_MSK)
#define PWMD_CC5PDisable()              CLR_REG_BIT(PWMD_CCER1, PWMDCCER1_CC5E_MSK)

#define HSPWMD_CC5PEnable()             SET_HSPWMD_BIT(PWMD_CCER1, PWMDCCER1_CC5E_MSK)
#define HSPWMD_CC5PDisable()            CLR_HSPWMD_BIT(PWMD_CCER1, PWMDCCER1_CC5E_MSK)

#define PWMDCCER1_CC5P_MSK              BIT1
#define PWMD_CC5PNonInverted()          CLR_REG_BIT(PWMD_CCER1, PWMDCCER1_CC5P_MSK)
#define PWMD_CC5PInverted()             SET_REG_BIT(PWMD_CCER1, PWMDCCER1_CC5P_MSK)

#define HSPWMD_CC5PNonInverted()        CLR_HSPWMD_BIT(PWMD_CCER1, PWMDCCER1_CC5P_MSK)
#define HSPWMD_CC5PInverted()           SET_HSPWMD_BIT(PWMD_CCER1, PWMDCCER1_CC5P_MSK)

#define PWMDCCER1_CC6E_MSK              BIT4
#define PWMD_CC6PEnable()               SET_REG_BIT(PWMD_CCER1, PWMDCCER1_CC6E_MSK)
#define PWMD_CC6PDisable()              CLR_REG_BIT(PWMD_CCER1, PWMDCCER1_CC6E_MSK)

#define HSPWMD_CC6PEnable()             SET_HSPWMD_BIT(PWMD_CCER1, PWMDCCER1_CC6E_MSK)
#define HSPWMD_CC6PDisable()            CLR_HSPWMD_BIT(PWMD_CCER1, PWMDCCER1_CC6E_MSK)

#define PWMDCCER1_CC6P_MSK              BIT5
#define PWMD_CC6PNonInverted()          CLR_REG_BIT(PWMD_CCER1, PWMDCCER1_CC6P_MSK)
#define PWMD_CC6PInverted()             SET_REG_BIT(PWMD_CCER1, PWMDCCER1_CC6P_MSK)

#define HSPWMD_CC6PNonInverted()        CLR_HSPWMD_BIT(PWMD_CCER1, PWMDCCER1_CC6P_MSK)
#define HSPWMD_CC6PInverted()           SET_HSPWMD_BIT(PWMD_CCER1, PWMDCCER1_CC6P_MSK)

#define PWMDCCER2_CC7E_MSK              BIT0
#define PWMD_CC7PEnable()               SET_REG_BIT(PWMD_CCER2, PWMDCCER2_CC7E_MSK)
#define PWMD_CC7PDisable()              CLR_REG_BIT(PWMD_CCER2, PWMDCCER2_CC7E_MSK)

#define HSPWMD_CC7PEnable()             SET_HSPWMD_BIT(PWMD_CCER2, PWMDCCER2_CC7E_MSK)
#define HSPWMD_CC7PDisable()            CLR_HSPWMD_BIT(PWMD_CCER2, PWMDCCER2_CC7E_MSK)

#define PWMDCCER2_CC7P_MSK              BIT1
#define PWMD_CC7PNonInverted()          CLR_REG_BIT(PWMD_CCER2, PWMDCCER2_CC7P_MSK)
#define PWMD_CC7PInverted()             SET_REG_BIT(PWMD_CCER2, PWMDCCER2_CC7P_MSK)

#define HSPWMD_CC7PNonInverted()        CLR_HSPWMD_BIT(PWMD_CCER2, PWMDCCER2_CC7P_MSK)
#define HSPWMD_CC7PInverted()           SET_HSPWMD_BIT(PWMD_CCER2, PWMDCCER2_CC7P_MSK)

#define PWMDCCER2_CC8E_MSK              BIT4
#define PWMD_CC8PEnable()               SET_REG_BIT(PWMD_CCER2, PWMDCCER2_CC8E_MSK)
#define PWMD_CC8PDisable()              CLR_REG_BIT(PWMD_CCER2, PWMDCCER2_CC8E_MSK)

#define HSPWMD_CC8PEnable()             SET_HSPWMD_BIT(PWMD_CCER2, PWMDCCER2_CC8E_MSK)
#define HSPWMD_CC8PDisable()            CLR_HSPWMD_BIT(PWMD_CCER2, PWMDCCER2_CC8E_MSK)

#define PWMDCCER2_CC8P_MSK              BIT5
#define PWMD_CC8PNonInverted()          CLR_REG_BIT(PWMD_CCER2, PWMDCCER2_CC8P_MSK)
#define PWMD_CC8PInverted()             SET_REG_BIT(PWMD_CCER2, PWMDCCER2_CC8P_MSK)

#define HSPWMD_CC8PNonInverted()        CLR_HSPWMD_BIT(PWMD_CCER2, PWMDCCER2_CC8P_MSK)
#define HSPWMD_CC8PInverted()           SET_HSPWMD_BIT(PWMD_CCER2, PWMDCCER2_CC8P_MSK)

#define PWMDBRK_MOE_MSK                 BIT7
#define PWMD_EnableMainOutput()         SET_REG_BIT(PWMD_BKR, PWMDBRK_MOE_MSK)
#define PWMD_DisableMainOutput()        CLR_REG_BIT(PWMD_BKR, PWMDBRK_MOE_MSK)

#define HSPWMD_EnableMainOutput()       SET_HSPWMD_BIT(PWMD_BKR, PWMDBRK_MOE_MSK)
#define HSPWMD_DisableMainOutput()      CLR_HSPWMD_BIT(PWMD_BKR, PWMDBRK_MOE_MSK)

#define PWMDBRK_AOE_MSK                 BIT6
#define PWMD_EnableAutoOutput()         SET_REG_BIT(PWMD_BKR, PWMDBRK_AOE_MSK)
#define PWMD_DisableAutoOutput()        CLR_REG_BIT(PWMD_BKR, PWMDBRK_AOE_MSK)

#define HSPWMD_EnableAutoOutput()       SET_HSPWMD_BIT(PWMD_BKR, PWMDBRK_AOE_MSK)
#define HSPWMD_DisableAutoOutput()      CLR_HSPWMD_BIT(PWMD_BKR, PWMDBRK_AOE_MSK)

#define PWMDBRK_BKP_MSK                 BIT5
#define PWMD_BRKNonInverted()           SET_REG_BIT(PWMD_BKR, PWMDBRK_BKP_MSK)
#define PWMD_BRKInverted()              CLR_REG_BIT(PWMD_BKR, PWMDBRK_BKP_MSK)

#define HSPWMD_BRKNonInverted()         SET_HSPWMD_BIT(PWMD_BKR, PWMDBRK_BKP_MSK)
#define HSPWMD_BRKInverted()            CLR_HSPWMD_BIT(PWMD_BKR, PWMDBRK_BKP_MSK)

#define PWMDBRK_BKE_MSK                 BIT4
#define PWMD_BRKEnable()                SET_REG_BIT(PWMD_BKR, PWMDBRK_BKE_MSK)
#define PWMD_BRKDisable()               CLR_REG_BIT(PWMD_BKR, PWMDBRK_BKE_MSK)

#define HSPWMD_BRKEnable()              SET_HSPWMD_BIT(PWMD_BKR, PWMDBRK_BKE_MSK)
#define HSPWMD_BRKDisable()             CLR_HSPWMD_BIT(PWMD_BKR, PWMDBRK_BKE_MSK)

#define PWMDBRK_OSSR_MSK                BIT3
#define PWMDBRK_OSSI_MSK                BIT2
#define PWMD_RunInactiveNoOutput()      CLR_REG_BIT(PWMD_BKR, PWMDBRK_OSSR_MSK)
#define PWMD_RunInactiveOutput()        SET_REG_BIT(PWMD_BKR, PWMDBRK_OSSR_MSK)
#define PWMD_IdleInactiveNoOutput()     CLR_REG_BIT(PWMD_BKR, PWMDBRK_OSSI_MSK)
#define PWMD_IdleInactiveOutput()       SET_REG_BIT(PWMD_BKR, PWMDBRK_OSSI_MSK)

#define HSPWMD_RunInactiveNoOutput()    CLR_HSPWMD_BIT(PWMD_BKR, PWMDBRK_OSSR_MSK)
#define HSPWMD_RunInactiveOutput()      SET_HSPWMD_BIT(PWMD_BKR, PWMDBRK_OSSR_MSK)
#define HSPWMD_IdleInactiveNoOutput()   CLR_HSPWMD_BIT(PWMD_BKR, PWMDBRK_OSSI_MSK)
#define HSPWMD_IdleInactiveOutput()     SET_HSPWMD_BIT(PWMD_BKR, PWMDBRK_OSSI_MSK)

#define PWMDBRK_LOCK_MSK                (BIT1 | BIT0)
#define PWMD_SetLockLevel(n)            MODIFY_REG(PWMD_BKR,  PWMDBRK_LOCK_MSK, ((n) << 0))
#define PWMD_SetUnLock()                PWMD_SetLockLevel(0)

#define HSPWMD_SetLockLevel(n)          MODIFY_HSPWMD(PWMD_BKR,  PWMDBRK_LOCK_MSK, ((n) << 0))
#define HSPWMD_SetUnLock()              HSPWMD_SetLockLevel(0)

#define PWMDOISR_OIS5_MSK               BIT0
#define PWMDOISR_OIS6_MSK               BIT2
#define PWMDOISR_OIS7_MSK               BIT4
#define PWMDOISR_OIS8_MSK               BIT6
#define PWMD_OC5PIdleLevelLow()         CLR_REG_BIT(PWMD_OISR, PWMDOISR_OIS5_MSK)
#define PWMD_OC5PIdleLevelHigh()        SET_REG_BIT(PWMD_OISR, PWMDOISR_OIS5_MSK)
#define PWMD_OC6PIdleLevelLow()         CLR_REG_BIT(PWMD_OISR, PWMDOISR_OIS6_MSK)
#define PWMD_OC6PIdleLevelHigh()        SET_REG_BIT(PWMD_OISR, PWMDOISR_OIS6_MSK)
#define PWMD_OC7PIdleLevelLow()         CLR_REG_BIT(PWMD_OISR, PWMDOISR_OIS7_MSK)
#define PWMD_OC7PIdleLevelHigh()        SET_REG_BIT(PWMD_OISR, PWMDOISR_OIS7_MSK)
#define PWMD_OC8PIdleLevelLow()         CLR_REG_BIT(PWMD_OISR, PWMDOISR_OIS8_MSK)
#define PWMD_OC8PIdleLevelHigh()        SET_REG_BIT(PWMD_OISR, PWMDOISR_OIS8_MSK)

#define HSPWMD_OC5PIdleLevelLow()       CLR_HSPWMD_BIT(PWMD_OISR, PWMDOISR_OIS5_MSK)
#define HSPWMD_OC5PIdleLevelHigh()      SET_HSPWMD_BIT(PWMD_OISR, PWMDOISR_OIS5_MSK)
#define HSPWMD_OC6PIdleLevelLow()       CLR_HSPWMD_BIT(PWMD_OISR, PWMDOISR_OIS6_MSK)
#define HSPWMD_OC6PIdleLevelHigh()      SET_HSPWMD_BIT(PWMD_OISR, PWMDOISR_OIS6_MSK)
#define HSPWMD_OC7PIdleLevelLow()       CLR_HSPWMD_BIT(PWMD_OISR, PWMDOISR_OIS7_MSK)
#define HSPWMD_OC7PIdleLevelHigh()      SET_HSPWMD_BIT(PWMD_OISR, PWMDOISR_OIS7_MSK)
#define HSPWMD_OC8PIdleLevelLow()       CLR_HSPWMD_BIT(PWMD_OISR, PWMDOISR_OIS8_MSK)
#define HSPWMD_OC8PIdleLevelHigh()      SET_HSPWMD_BIT(PWMD_OISR, PWMDOISR_OIS8_MSK)

#define PWMD_SetCounter(n)              (PWMD_CNTRH = HIBYTE(n), PWMD_CNTRL = LOBYTE(n))
#define PWMD_SetClockDivider(n)         (PWMD_PSCRH = HIBYTE(n), PWMD_PSCRL = LOBYTE(n))
#define PWMD_SetReload16(n)             (PWMD_ARRH = HIBYTE(n), PWMD_ARRL = LOBYTE(n))
#define PWMD_SetRepeatCounter(n)        (PWMD_RCRH = HIBYTE(n), PWMD_RCR = LOBYTE(n))

#define HSPWMD_SetCounter(n)            (WRITE_HSPWMD(PWMD_CNTRH, HIBYTE(n)), WRITE_HSPWMD(PWMD_CNTRL, LOBYTE(n)))
#define HSPWMD_SetClockDivider(n)       (WRITE_HSPWMD(PWMD_PSCRH, HIBYTE(n)), WRITE_HSPWMD(PWMD_PSCRL, LOBYTE(n)))
#define HSPWMD_SetReload16(n)           (WRITE_HSPWMD(PWMD_ARRH, HIBYTE(n)), WRITE_HSPWMD(PWMD_ARRL, LOBYTE(n)))
#define HSPWMD_SetRepeatCounter(n)      (WRITE_HSPWMD(PWMD_RCRH, HIBYTE(n)), WRITE_HSPWMD(PWMD_RCR, LOBYTE(n)))

#define PWMD_SetCCR5Value(n)            (PWMD_CCR5H = HIBYTE(n), PWMD_CCR5L = LOBYTE(n))
#define PWMD_SetCCR6Value(n)            (PWMD_CCR6H = HIBYTE(n), PWMD_CCR6L = LOBYTE(n))
#define PWMD_SetCCR7Value(n)            (PWMD_CCR7H = HIBYTE(n), PWMD_CCR7L = LOBYTE(n))
#define PWMD_SetCCR8Value(n)            (PWMD_CCR8H = HIBYTE(n), PWMD_CCR8L = LOBYTE(n))

#define HSPWMD_SetCCR5Value(n)          (WRITE_HSPWMD(PWMD_CCR5H, HIBYTE(n)), WRITE_HSPWMD(PWMD_CCR5L, LOBYTE(n)))
#define HSPWMD_SetCCR6Value(n)          (WRITE_HSPWMD(PWMD_CCR6H, HIBYTE(n)), WRITE_HSPWMD(PWMD_CCR6L, LOBYTE(n)))
#define HSPWMD_SetCCR7Value(n)          (WRITE_HSPWMD(PWMD_CCR7H, HIBYTE(n)), WRITE_HSPWMD(PWMD_CCR7L, LOBYTE(n)))
#define HSPWMD_SetCCR8Value(n)          (WRITE_HSPWMD(PWMD_CCR8H, HIBYTE(n)), WRITE_HSPWMD(PWMD_CCR8L, LOBYTE(n)))

#define PWMD_ReadReload16()             MAKEWORD(PWMD_ARRL, PWMD_ARRH)

#define HSPWMD_ReadReload16()           MAKEWORD(READ_HSPWMD(PWMD_ARRL), READ_HSPWMD(PWMD_ARRH))

#define PWMD_ReadCCR5Value()            MAKEWORD(PWMD_CCR5L, PWMD_CCR5H)
#define PWMD_ReadCCR6Value()            MAKEWORD(PWMD_CCR6L, PWMD_CCR6H)
#define PWMD_ReadCCR7Value()            MAKEWORD(PWMD_CCR7L, PWMD_CCR7H)
#define PWMD_ReadCCR8Value()            MAKEWORD(PWMD_CCR8L, PWMD_CCR8H)

#define HSPWMD_ReadCCR5Value()          MAKEWORD(READ_HSPWMD(PWMD_CCR5L), READ_HSPWMD(PWMD_CCR5H))
#define HSPWMD_ReadCCR6Value()          MAKEWORD(READ_HSPWMD(PWMD_CCR6L), READ_HSPWMD(PWMD_CCR6H))
#define HSPWMD_ReadCCR7Value()          MAKEWORD(READ_HSPWMD(PWMD_CCR7L), READ_HSPWMD(PWMD_CCR7H))
#define HSPWMD_ReadCCR8Value()          MAKEWORD(READ_HSPWMD(PWMD_CCR8L), READ_HSPWMD(PWMD_CCR8H))

#define PWMD_SetDeadTime(n)             PWMD_DTR = LOBYTE(n)

#define HSPWMD_SetDeadTime(n)           WRITE_HSPWMD(PWMD_DTR, LOBYTE(n))

////////////////////////

#define PWMEENO_ENO1P_MSK               BIT0
#define PWMEENO_ENO1N_MSK               BIT1
#define PWMEENO_ENO2P_MSK               BIT2
#define PWMEENO_ENO2N_MSK               BIT3
#define PWMEENO_ENO3P_MSK               BIT4
#define PWMEENO_ENO3N_MSK               BIT5
#define PWMEENO_ENO4P_MSK               BIT6
#define PWMEENO_ENO4N_MSK               BIT7
#define PWMEENO2_ENO5P_MSK              BIT0
#define PWMEENO2_ENO6P_MSK              BIT2
#define PWME_EnablePWM1POutput()        SET_REG_BIT(PWME_ENO, PWMEENO_ENO1P_MSK)
#define PWME_DisablePWM1POutput()       CLR_REG_BIT(PWME_ENO, PWMEENO_ENO1P_MSK)
#define PWME_EnablePWM1NOutput()        SET_REG_BIT(PWME_ENO, PWMEENO_ENO1N_MSK)
#define PWME_DisablePWM1NOutput()       CLR_REG_BIT(PWME_ENO, PWMEENO_ENO1N_MSK)
#define PWME_EnablePWM2POutput()        SET_REG_BIT(PWME_ENO, PWMEENO_ENO2P_MSK)
#define PWME_DisablePWM2POutput()       CLR_REG_BIT(PWME_ENO, PWMEENO_ENO2P_MSK)
#define PWME_EnablePWM2NOutput()        SET_REG_BIT(PWME_ENO, PWMEENO_ENO2N_MSK)
#define PWME_DisablePWM2NOutput()       CLR_REG_BIT(PWME_ENO, PWMEENO_ENO2N_MSK)
#define PWME_EnablePWM3POutput()        SET_REG_BIT(PWME_ENO, PWMEENO_ENO3P_MSK)
#define PWME_DisablePWM3POutput()       CLR_REG_BIT(PWME_ENO, PWMEENO_ENO3P_MSK)
#define PWME_EnablePWM3NOutput()        SET_REG_BIT(PWME_ENO, PWMEENO_ENO3N_MSK)
#define PWME_DisablePWM3NOutput()       CLR_REG_BIT(PWME_ENO, PWMEENO_ENO3N_MSK)
#define PWME_EnablePWM4POutput()        SET_REG_BIT(PWME_ENO, PWMEENO_ENO4P_MSK)
#define PWME_DisablePWM4POutput()       CLR_REG_BIT(PWME_ENO, PWMEENO_ENO4P_MSK)
#define PWME_EnablePWM4NOutput()        SET_REG_BIT(PWME_ENO, PWMEENO_ENO4N_MSK)
#define PWME_DisablePWM4NOutput()       CLR_REG_BIT(PWME_ENO, PWMEENO_ENO4N_MSK)
#define PWME_EnablePWM5POutput()        SET_REG_BIT(PWME_ENO2, PWMEENO2_ENO5P_MSK)
#define PWME_DisablePWM5POutput()       CLR_REG_BIT(PWME_ENO2, PWMEENO2_ENO5P_MSK)
#define PWME_EnablePWM6POutput()        SET_REG_BIT(PWME_ENO2, PWMEENO2_ENO6P_MSK)
#define PWME_DisablePWM6POutput()       CLR_REG_BIT(PWME_ENO2, PWMEENO2_ENO6P_MSK)

#define HSPWME_EnablePWM1POutput()      SET_HSPWME_BIT(PWME_ENO, PWMEENO_ENO1P_MSK)
#define HSPWME_DisablePWM1POutput()     CLR_HSPWME_BIT(PWME_ENO, PWMEENO_ENO1P_MSK)
#define HSPWME_EnablePWM1NOutput()      SET_HSPWME_BIT(PWME_ENO, PWMEENO_ENO1N_MSK)
#define HSPWME_DisablePWM1NOutput()     CLR_HSPWME_BIT(PWME_ENO, PWMEENO_ENO1N_MSK)
#define HSPWME_EnablePWM2POutput()      SET_HSPWME_BIT(PWME_ENO, PWMEENO_ENO2P_MSK)
#define HSPWME_DisablePWM2POutput()     CLR_HSPWME_BIT(PWME_ENO, PWMEENO_ENO2P_MSK)
#define HSPWME_EnablePWM2NOutput()      SET_HSPWME_BIT(PWME_ENO, PWMEENO_ENO2N_MSK)
#define HSPWME_DisablePWM2NOutput()     CLR_HSPWME_BIT(PWME_ENO, PWMEENO_ENO2N_MSK)
#define HSPWME_EnablePWM3POutput()      SET_HSPWME_BIT(PWME_ENO, PWMEENO_ENO3P_MSK)
#define HSPWME_DisablePWM3POutput()     CLR_HSPWME_BIT(PWME_ENO, PWMEENO_ENO3P_MSK)
#define HSPWME_EnablePWM3NOutput()      SET_HSPWME_BIT(PWME_ENO, PWMEENO_ENO3N_MSK)
#define HSPWME_DisablePWM3NOutput()     CLR_HSPWME_BIT(PWME_ENO, PWMEENO_ENO3N_MSK)
#define HSPWME_EnablePWM4POutput()      SET_HSPWME_BIT(PWME_ENO, PWMEENO_ENO4P_MSK)
#define HSPWME_DisablePWM4POutput()     CLR_HSPWME_BIT(PWME_ENO, PWMEENO_ENO4P_MSK)
#define HSPWME_EnablePWM4NOutput()      SET_HSPWME_BIT(PWME_ENO, PWMEENO_ENO4N_MSK)
#define HSPWME_DisablePWM4NOutput()     CLR_HSPWME_BIT(PWME_ENO, PWMEENO_ENO4N_MSK)
#define HSPWME_EnablePWM5POutput()      SET_HSPWME_BIT(PWME_ENO2, PWMEENO2_ENO5P_MSK)
#define HSPWME_DisablePWM5POutput()     CLR_HSPWME_BIT(PWME_ENO2, PWMEENO2_ENO5P_MSK)
#define HSPWME_EnablePWM6POutput()      SET_HSPWME_BIT(PWME_ENO2, PWMEENO2_ENO6P_MSK)
#define HSPWME_DisablePWM6POutput()     CLR_HSPWME_BIT(PWME_ENO2, PWMEENO2_ENO6P_MSK)

#define PWMEIOAUX_AUX1P_MSK             BIT0
#define PWMEIOAUX_AUX1N_MSK             BIT1
#define PWMEIOAUX_AUX2P_MSK             BIT2
#define PWMEIOAUX_AUX2N_MSK             BIT3
#define PWMEIOAUX_AUX3P_MSK             BIT4
#define PWMEIOAUX_AUX3N_MSK             BIT5
#define PWMEIOAUX_AUX4P_MSK             BIT6
#define PWMEIOAUX_AUX4N_MSK             BIT7
#define PWMEIOAUX2_AUX5P_MSK            BIT0
#define PWMEIOAUX2_AUX6P_MSK            BIT2
#define PWME_EnoCtrlPWM1P()             CLR_REG_BIT(PWME_IOAUX, PWMEIOAUX_AUX1P_MSK)
#define PWME_EnoBrkCtrlPWM1P()          SET_REG_BIT(PWME_IOAUX, PWMEIOAUX_AUX1P_MSK)
#define PWME_EnoCtrlPWM1N()             CLR_REG_BIT(PWME_IOAUX, PWMEIOAUX_AUX1N_MSK)
#define PWME_EnoBrkCtrlPWM1N()          SET_REG_BIT(PWME_IOAUX, PWMEIOAUX_AUX1N_MSK)
#define PWME_EnoCtrlPWM2P()             CLR_REG_BIT(PWME_IOAUX, PWMEIOAUX_AUX2P_MSK)
#define PWME_EnoBrkCtrlPWM2P()          SET_REG_BIT(PWME_IOAUX, PWMEIOAUX_AUX2P_MSK)
#define PWME_EnoCtrlPWM2N()             CLR_REG_BIT(PWME_IOAUX, PWMEIOAUX_AUX2N_MSK)
#define PWME_EnoBrkCtrlPWM2N()          SET_REG_BIT(PWME_IOAUX, PWMEIOAUX_AUX2N_MSK)
#define PWME_EnoCtrlPWM3P()             CLR_REG_BIT(PWME_IOAUX, PWMEIOAUX_AUX3P_MSK)
#define PWME_EnoBrkCtrlPWM3P()          SET_REG_BIT(PWME_IOAUX, PWMEIOAUX_AUX3P_MSK)
#define PWME_EnoCtrlPWM3N()             CLR_REG_BIT(PWME_IOAUX, PWMEIOAUX_AUX3N_MSK)
#define PWME_EnoBrkCtrlPWM3N()          SET_REG_BIT(PWME_IOAUX, PWMEIOAUX_AUX3N_MSK)
#define PWME_EnoCtrlPWM4P()             CLR_REG_BIT(PWME_IOAUX, PWMEIOAUX_AUX4P_MSK)
#define PWME_EnoBrkCtrlPWM4P()          SET_REG_BIT(PWME_IOAUX, PWMEIOAUX_AUX4P_MSK)
#define PWME_EnoCtrlPWM4N()             CLR_REG_BIT(PWME_IOAUX, PWMEIOAUX_AUX4N_MSK)
#define PWME_EnoBrkCtrlPWM4N()          SET_REG_BIT(PWME_IOAUX, PWMEIOAUX_AUX4N_MSK)
#define PWME_EnoCtrlPWM5P()             CLR_REG_BIT(PWME_IOAUX2, PWMEIOAUX2_AUX5P_MSK)
#define PWME_EnoBrkCtrlPWM5P()          SET_REG_BIT(PWME_IOAUX2, PWMEIOAUX2_AUX5P_MSK)
#define PWME_EnoCtrlPWM6P()             CLR_REG_BIT(PWME_IOAUX2, PWMEIOAUX2_AUX6P_MSK)
#define PWME_EnoBrkCtrlPWM6P()          SET_REG_BIT(PWME_IOAUX2, PWMEIOAUX2_AUX6P_MSK)

#define HSPWME_EnoCtrlPWM1P()           CLR_HSPWME_BIT(PWME_IOAUX, PWMEIOAUX_AUX1P_MSK)
#define HSPWME_EnoBrkCtrlPWM1P()        SET_HSPWME_BIT(PWME_IOAUX, PWMEIOAUX_AUX1P_MSK)
#define HSPWME_EnoCtrlPWM1N()           CLR_HSPWME_BIT(PWME_IOAUX, PWMEIOAUX_AUX1N_MSK)
#define HSPWME_EnoBrkCtrlPWM1N()        SET_HSPWME_BIT(PWME_IOAUX, PWMEIOAUX_AUX1N_MSK)
#define HSPWME_EnoCtrlPWM2P()           CLR_HSPWME_BIT(PWME_IOAUX, PWMEIOAUX_AUX2P_MSK)
#define HSPWME_EnoBrkCtrlPWM2P()        SET_HSPWME_BIT(PWME_IOAUX, PWMEIOAUX_AUX2P_MSK)
#define HSPWME_EnoCtrlPWM2N()           CLR_HSPWME_BIT(PWME_IOAUX, PWMEIOAUX_AUX2N_MSK)
#define HSPWME_EnoBrkCtrlPWM2N()        SET_HSPWME_BIT(PWME_IOAUX, PWMEIOAUX_AUX2N_MSK)
#define HSPWME_EnoCtrlPWM3P()           CLR_HSPWME_BIT(PWME_IOAUX, PWMEIOAUX_AUX3P_MSK)
#define HSPWME_EnoBrkCtrlPWM3P()        SET_HSPWME_BIT(PWME_IOAUX, PWMEIOAUX_AUX3P_MSK)
#define HSPWME_EnoCtrlPWM3N()           CLR_HSPWME_BIT(PWME_IOAUX, PWMEIOAUX_AUX3N_MSK)
#define HSPWME_EnoBrkCtrlPWM3N()        SET_HSPWME_BIT(PWME_IOAUX, PWMEIOAUX_AUX3N_MSK)
#define HSPWME_EnoCtrlPWM4P()           CLR_HSPWME_BIT(PWME_IOAUX, PWMEIOAUX_AUX4P_MSK)
#define HSPWME_EnoBrkCtrlPWM4P()        SET_HSPWME_BIT(PWME_IOAUX, PWMEIOAUX_AUX4P_MSK)
#define HSPWME_EnoCtrlPWM4N()           CLR_HSPWME_BIT(PWME_IOAUX, PWMEIOAUX_AUX4N_MSK)
#define HSPWME_EnoBrkCtrlPWM4N()        SET_HSPWME_BIT(PWME_IOAUX, PWMEIOAUX_AUX4N_MSK)
#define HSPWME_EnoCtrlPWM5P()           CLR_HSPWME_BIT(PWME_IOAUX2, PWMEIOAUX2_AUX5P_MSK)
#define HSPWME_EnoBrkCtrlPWM5P()        SET_HSPWME_BIT(PWME_IOAUX2, PWMEIOAUX2_AUX5P_MSK)
#define HSPWME_EnoCtrlPWM6P()           CLR_HSPWME_BIT(PWME_IOAUX2, PWMEIOAUX2_AUX6P_MSK)
#define HSPWME_EnoBrkCtrlPWM6P()        SET_HSPWME_BIT(PWME_IOAUX2, PWMEIOAUX2_AUX6P_MSK)

#define PWMECR1_ARPE_MSK                BIT7
#define PWME_UnbufferARR()              CLR_REG_BIT(PWME_CR1, PWMECR1_ARPE_MSK)
#define PWME_BufferARR()                SET_REG_BIT(PWME_CR1, PWMECR1_ARPE_MSK)

#define HSPWME_UnbufferARR()            CLR_HSPWME_BIT(PWME_CR1, PWMECR1_ARPE_MSK)
#define HSPWME_BufferARR()              SET_HSPWME_BIT(PWME_CR1, PWMECR1_ARPE_MSK)

#define PWMECR1_CMS_MSK                 (BIT6 | BIT5)
#define PWME_SetAlignMode(n)            MODIFY_REG(PWME_CR1,  PWMECR1_CMS_MSK, ((n) << 5))
#define PWME_EdgeAlignMode()            PWME_SetAlignMode(0)
#define PWME_CenterAlignMode1()         PWME_SetAlignMode(1)
#define PWME_CenterAlignMode2()         PWME_SetAlignMode(2)
#define PWME_CenterAlignMode3()         PWME_SetAlignMode(3)

#define HSPWME_SetAlignMode(n)          MODIFY_HSPWME(PWME_CR1,  PWMECR1_CMS_MSK, ((n) << 5))
#define HSPWME_EdgeAlignMode()          HSPWME_SetAlignMode(0)
#define HSPWME_CenterAlignMode1()       HSPWME_SetAlignMode(1)
#define HSPWME_CenterAlignMode2()       HSPWME_SetAlignMode(2)
#define HSPWME_CenterAlignMode3()       HSPWME_SetAlignMode(3)

#define PWMECR1_DIR_MSK                 BIT4
#define PWME_UpCounter()                CLR_REG_BIT(PWME_CR1, PWMECR1_DIR_MSK)
#define PWME_DownCounter()              SET_REG_BIT(PWME_CR1, PWMECR1_DIR_MSK)

#define HSPWME_UpCounter()              CLR_HSPWME_BIT(PWME_CR1, PWMECR1_DIR_MSK)
#define HSPWME_DownCounter()            SET_HSPWME_BIT(PWME_CR1, PWMECR1_DIR_MSK)

#define PWMECR1_OPM_MSK                 BIT3
#define PWME_ContinueMode()             CLR_REG_BIT(PWME_CR1, PWMECR1_OPM_MSK)
#define PWME_OnePulseMode()             SET_REG_BIT(PWME_CR1, PWMECR1_OPM_MSK)

#define HSPWME_ContinueMode()           CLR_HSPWME_BIT(PWME_CR1, PWMECR1_OPM_MSK)
#define HSPWME_OnePulseMode()           SET_HSPWME_BIT(PWME_CR1, PWMECR1_OPM_MSK)

#define PWMECR1_URS_MSK                 BIT2
#define PWME_UpdateRequestMode1()       SET_REG_BIT(PWME_CR1, PWMECR1_URS_MSK)
#define PWME_UpdateRequestMode2()       CLR_REG_BIT(PWME_CR1, PWMECR1_URS_MSK)

#define HSPWME_UpdateRequestMode1()     SET_HSPWME_BIT(PWME_CR1, PWMECR1_URS_MSK)
#define HSPWME_UpdateRequestMode2()     CLR_HSPWME_BIT(PWME_CR1, PWMECR1_URS_MSK)

#define PWMECR1_UDIS_MSK                BIT1
#define PWME_EnableUpdate()             CLR_REG_BIT(PWME_CR1, PWMECR1_UDIS_MSK)
#define PWME_DisableUpdate()            SET_REG_BIT(PWME_CR1, PWMECR1_UDIS_MSK)

#define HSPWME_EnableUpdate()           CLR_HSPWME_BIT(PWME_CR1, PWMECR1_UDIS_MSK)
#define HSPWME_DisableUpdate()          SET_HSPWME_BIT(PWME_CR1, PWMECR1_UDIS_MSK)

#define PWMECR1_CEN_MSK                 BIT0
#define PWME_Run()                      SET_REG_BIT(PWME_CR1, PWMECR1_CEN_MSK)
#define PWME_Stop()                     CLR_REG_BIT(PWME_CR1, PWMECR1_CEN_MSK)

#define HSPWME_Run()                    SET_HSPWME_BIT(PWME_CR1, PWMECR1_CEN_MSK)
#define HSPWME_Stop()                   CLR_HSPWME_BIT(PWME_CR1, PWMECR1_CEN_MSK)

#define PWMECR2_TIS_MSK                 BIT7
#define PWME_PWM1PToTI()                CLR_REG_BIT(PWME_CR2, PWMECR2_TIS_MSK)
#define PWME_Xor1P2P3PToTI()            SET_REG_BIT(PWME_CR2, PWMECR2_TIS_MSK)

#define HSPWME_PWM1PToTI()              CLR_HSPWME_BIT(PWME_CR2, PWMECR2_TIS_MSK)
#define HSPWME_Xor1P2P3PToTI()          SET_HSPWME_BIT(PWME_CR2, PWMECR2_TIS_MSK)

#define PWMECR2_MMS_MSK                 (BIT6 | BIT5 | BIT4)
#define PWME_SelectTRGO(n)              MODIFY_REG(PWME_CR2,  PWMECR2_MMS_MSK, ((n) << 4))
#define PWME_ResetAsTRGO()              PWME_SelectTRGO(0)
#define PWME_EnableAsTRGO()             PWME_SelectTRGO(1)
#define PWME_UpdateAsTRGO()             PWME_SelectTRGO(2)
#define PWME_MatchAsTRGO()              PWME_SelectTRGO(3)
#define PWME_OC1REFAsTRGO()             PWME_SelectTRGO(4)
#define PWME_OC2REFAsTRGO()             PWME_SelectTRGO(5)
#define PWME_OC3REFAsTRGO()             PWME_SelectTRGO(6)
#define PWME_OC4REFAsTRGO()             PWME_SelectTRGO(7)

#define HSPWME_SelectTRGO(n)            MODIFY_HSPWME(PWME_CR2,  PWMECR2_MMS_MSK, ((n) << 4))
#define HSPWME_ResetAsTRGO()            HSPWME_SelectTRGO(0)
#define HSPWME_EnableAsTRGO()           HSPWME_SelectTRGO(1)
#define HSPWME_UpdateAsTRGO()           HSPWME_SelectTRGO(2)
#define HSPWME_MatchAsTRGO()            HSPWME_SelectTRGO(3)
#define HSPWME_OC1REFAsTRGO()           HSPWME_SelectTRGO(4)
#define HSPWME_OC2REFAsTRGO()           HSPWME_SelectTRGO(5)
#define HSPWME_OC3REFAsTRGO()           HSPWME_SelectTRGO(6)
#define HSPWME_OC4REFAsTRGO()           HSPWME_SelectTRGO(7)

#define PWMECR2_COMS_MSK                BIT2
#define PWME_CCOCUpdateMode0()          CLR_REG_BIT(PWME_CR2, PWMECR2_COMS_MSK)
#define PWME_CCOCUpdateMode1()          SET_REG_BIT(PWME_CR2, PWMECR2_COMS_MSK)

#define HSPWME_CCOCUpdateMode0()        CLR_HSPWME_BIT(PWME_CR2, PWMECR2_COMS_MSK)
#define HSPWME_CCOCUpdateMode1()        SET_HSPWME_BIT(PWME_CR2, PWMECR2_COMS_MSK)

#define PWMECR2_CCPC_MSK                BIT0
#define PWME_UnbufferCCOC()             CLR_REG_BIT(PWME_CR2, PWMECR2_CCPC_MSK)
#define PWME_BufferCCOC()               SET_REG_BIT(PWME_CR2, PWMECR2_CCPC_MSK)

#define HSPWME_UnbufferCCOC()           CLR_HSPWME_BIT(PWME_CR2, PWMECR2_CCPC_MSK)
#define HSPWME_BufferCCOC()             SET_HSPWME_BIT(PWME_CR2, PWMECR2_CCPC_MSK)

#define PWMESMCR_MSM_MSK                BIT7
#define PWME_StandaloneMode()           CLR_REG_BIT(PWME_SMCR, PWMESMCR_MSM_MSK)
#define PWME_MasterSlaveMode()          SET_REG_BIT(PWME_SMCR, PWMESMCR_MSM_MSK)

#define HSPWME_StandaloneMode()         CLR_HSPWME_BIT(PWME_SMCR, PWMESMCR_MSM_MSK)
#define HSPWME_MasterSlaveMode()        SET_HSPWME_BIT(PWME_SMCR, PWMESMCR_MSM_MSK)

#define PWMESMCR_TS_MSK                 (BIT6 | BIT5 | BIT4)
#define PWME_SelectTRGI(n)              MODIFY_REG(PWME_SMCR,  PWMESMCR_TS_MSK, ((n) << 4))
#define PWME_DisableTRGI()              PWME_SelectTRGI(0)
#define PWME_ITR2AsTRGI()               PWME_SelectTRGI(2)
#define PWME_TI1FEDAsTRGI()             PWME_SelectTRGI(4)
#define PWME_TI1FP1AsTRGI()             PWME_SelectTRGI(5)
#define PWME_TI2FP2AsTRGI()             PWME_SelectTRGI(6)
#define PWME_ETRFAsTRGI()               PWME_SelectTRGI(7)

#define HSPWME_SelectTRGI(n)            MODIFY_HSPWME(PWME_SMCR,  PWMESMCR_TS_MSK, ((n) << 4))
#define HSPWME_DisableTRGI()            HSPWME_SelectTRGI(0)
#define HSPWME_ITR2AsTRGI()             HSPWME_SelectTRGI(2)
#define HSPWME_TI1FEDAsTRGI()           HSPWME_SelectTRGI(4)
#define HSPWME_TI1FP1AsTRGI()           HSPWME_SelectTRGI(5)
#define HSPWME_TI2FP2AsTRGI()           HSPWME_SelectTRGI(6)
#define HSPWME_ETRFAsTRGI()             HSPWME_SelectTRGI(7)

#define PWMESMCR_SMS_MSK                (BIT2 | BIT1 | BIT0)
#define PWME_SetClockMode(n)            MODIFY_REG(PWME_SMCR,  PWMESMCR_SMS_MSK, ((n) << 0))
#define PWME_InternalClockMode()        PWME_SetClockMode(0)
#define PWME_EncoderMode1()             PWME_SetClockMode(1)
#define PWME_EncoderMode2()             PWME_SetClockMode(2)
#define PWME_EncoderMode3()             PWME_SetClockMode(3)
#define PWME_TriggerResetMode()         PWME_SetClockMode(4)
#define PWME_TriggerGateMode()          PWME_SetClockMode(5)
#define PWME_TriggerStartMode()         PWME_SetClockMode(6)
#define PWME_ExternalClockMode()        PWME_SetClockMode(7)

#define HSPWME_SetClockMode(n)          MODIFY_HSPWME(PWME_SMCR,  PWMESMCR_SMS_MSK, ((n) << 0))
#define HSPWME_InternalClockMode()      HSPWME_SetClockMode(0)
#define HSPWME_EncoderMode1()           HSPWME_SetClockMode(1)
#define HSPWME_EncoderMode2()           HSPWME_SetClockMode(2)
#define HSPWME_EncoderMode3()           HSPWME_SetClockMode(3)
#define HSPWME_TriggerResetMode()       HSPWME_SetClockMode(4)
#define HSPWME_TriggerGateMode()        HSPWME_SetClockMode(5)
#define HSPWME_TriggerStartMode()       HSPWME_SetClockMode(6)
#define HSPWME_ExternalClockMode()      HSPWME_SetClockMode(7)

#define PWMEETR_ETP_MSK                 BIT7
#define PWME_ETRNonInverted()           CLR_REG_BIT(PWME_ETR, PWMEETR_ETP_MSK)
#define PWME_ETRInverted()              SET_REG_BIT(PWME_ETR, PWMEETR_ETP_MSK)

#define HSPWME_ETRNonInverted()         CLR_HSPWME_BIT(PWME_ETR, PWMEETR_ETP_MSK)
#define HSPWME_ETRInverted()            SET_HSPWME_BIT(PWME_ETR, PWMEETR_ETP_MSK)

#define PWMEETR_ECE_MSK                 BIT6
#define PWME_DisableExternalClock2()    CLR_REG_BIT(PWME_ETR, PWMEETR_ECE_MSK)
#define PWME_EnableExternalClock2()     SET_REG_BIT(PWME_ETR, PWMEETR_ECE_MSK)

#define HSPWME_DisableExternalClock2()  CLR_HSPWME_BIT(PWME_ETR, PWMEETR_ECE_MSK)
#define HSPWME_EnableExternalClock2()   SET_HSPWME_BIT(PWME_ETR, PWMEETR_ECE_MSK)

#define PWMEETR_ETPS_MSK                (BIT5 | BIT4)
#define PWME_SetETRDivider(n)           MODIFY_REG(PWME_ETR,  PWMEETR_ETPS_MSK, ((n) << 4))
#define PWME_ETRDivider1()              PWME_SetETRDivider(0)
#define PWME_ETRDivider2()              PWME_SetETRDivider(1)
#define PWME_ETRDivider4()              PWME_SetETRDivider(2)
#define PWME_ETRDivider8()              PWME_SetETRDivider(3)

#define HSPWME_SetETRDivider(n)         MODIFY_HSPWME(PWME_ETR,  PWMEETR_ETPS_MSK, ((n) << 4))
#define HSPWME_ETRDivider1()            HSPWME_SetETRDivider(0)
#define HSPWME_ETRDivider2()            HSPWME_SetETRDivider(1)
#define HSPWME_ETRDivider4()            HSPWME_SetETRDivider(2)
#define HSPWME_ETRDivider8()            HSPWME_SetETRDivider(3)

#define PWMEETR_ETF_MSK                 (BIT_LN)
#define PWME_SetETRFilter(n)            MODIFY_REG(PWME_ETR,  PWMEETR_ETF_MSK, ((n) << 0))
#define PWME_ETRFilter1()               PWME_SetETRFilter(0)
#define PWME_ETRFilter2()               PWME_SetETRFilter(1)
#define PWME_ETRFilter4()               PWME_SetETRFilter(2)
#define PWME_ETRFilter8()               PWME_SetETRFilter(3)
#define PWME_ETRFilter12()              PWME_SetETRFilter(4)
#define PWME_ETRFilter16()              PWME_SetETRFilter(5)
#define PWME_ETRFilter24()              PWME_SetETRFilter(6)
#define PWME_ETRFilter32()              PWME_SetETRFilter(7)
#define PWME_ETRFilter48()              PWME_SetETRFilter(8)
#define PWME_ETRFilter64()              PWME_SetETRFilter(9)
#define PWME_ETRFilter80()              PWME_SetETRFilter(10)
#define PWME_ETRFilter96()              PWME_SetETRFilter(11)
#define PWME_ETRFilter128()             PWME_SetETRFilter(12)
#define PWME_ETRFilter160()             PWME_SetETRFilter(13)
#define PWME_ETRFilter192()             PWME_SetETRFilter(14)
#define PWME_ETRFilter256()             PWME_SetETRFilter(15)

#define HSPWME_SetETRFilter(n)          MODIFY_HSPWME(PWME_ETR,  PWMEETR_ETF_MSK, ((n) << 0))
#define HSPWME_ETRFilter1()             HSPWME_SetETRFilter(0)
#define HSPWME_ETRFilter2()             HSPWME_SetETRFilter(1)
#define HSPWME_ETRFilter4()             HSPWME_SetETRFilter(2)
#define HSPWME_ETRFilter8()             HSPWME_SetETRFilter(3)
#define HSPWME_ETRFilter12()            HSPWME_SetETRFilter(4)
#define HSPWME_ETRFilter16()            HSPWME_SetETRFilter(5)
#define HSPWME_ETRFilter24()            HSPWME_SetETRFilter(6)
#define HSPWME_ETRFilter32()            HSPWME_SetETRFilter(7)
#define HSPWME_ETRFilter48()            HSPWME_SetETRFilter(8)
#define HSPWME_ETRFilter64()            HSPWME_SetETRFilter(9)
#define HSPWME_ETRFilter80()            HSPWME_SetETRFilter(10)
#define HSPWME_ETRFilter96()            HSPWME_SetETRFilter(11)
#define HSPWME_ETRFilter128()           HSPWME_SetETRFilter(12)
#define HSPWME_ETRFilter160()           HSPWME_SetETRFilter(13)
#define HSPWME_ETRFilter192()           HSPWME_SetETRFilter(14)
#define HSPWME_ETRFilter256()           HSPWME_SetETRFilter(15)

#define PWMEEGR_BG_MSK                  BIT7
#define PWMEEGR_TG_MSK                  BIT6
#define PWMEEGR_COMG_MSK                BIT5
#define PWMEEGR_CC4G_MSK                BIT4
#define PWMEEGR_CC3G_MSK                BIT3
#define PWMEEGR_CC2G_MSK                BIT2
#define PWMEEGR_CC1G_MSK                BIT1
#define PWMEEGR_UG_MSK                  BIT0
#define PWME_GenerateBreakEvent()       SET_REG_BIT(PWME_EGR, PWMEEGR_BG_MSK)
#define PWME_GenerateTriggerEvent()     SET_REG_BIT(PWME_EGR, PWMEEGR_TG_MSK)
#define PWME_GenerateCOMEvent()         SET_REG_BIT(PWME_EGR, PWMEEGR_COMG_MSK)
#define PWME_GenerateCC4Event()         SET_REG_BIT(PWME_EGR, PWMEEGR_CC4G_MSK)
#define PWME_GenerateCC3Event()         SET_REG_BIT(PWME_EGR, PWMEEGR_CC3G_MSK)
#define PWME_GenerateCC2Event()         SET_REG_BIT(PWME_EGR, PWMEEGR_CC2G_MSK)
#define PWME_GenerateCC1Event()         SET_REG_BIT(PWME_EGR, PWMEEGR_CC1G_MSK)
#define PWME_GenerateUpdateEvent()      SET_REG_BIT(PWME_EGR, PWMEEGR_UG_MSK)

#define HSPWME_GenerateBreakEvent()     SET_HSPWME_BIT(PWME_EGR, PWMEEGR_BG_MSK)
#define HSPWME_GenerateTriggerEvent()   SET_HSPWME_BIT(PWME_EGR, PWMEEGR_TG_MSK)
#define HSPWME_GenerateCOMEvent()       SET_HSPWME_BIT(PWME_EGR, PWMEEGR_COMG_MSK)
#define HSPWME_GenerateCC4Event()       SET_HSPWME_BIT(PWME_EGR, PWMEEGR_CC4G_MSK)
#define HSPWME_GenerateCC3Event()       SET_HSPWME_BIT(PWME_EGR, PWMEEGR_CC3G_MSK)
#define HSPWME_GenerateCC2Event()       SET_HSPWME_BIT(PWME_EGR, PWMEEGR_CC2G_MSK)
#define HSPWME_GenerateCC1Event()       SET_HSPWME_BIT(PWME_EGR, PWMEEGR_CC1G_MSK)
#define HSPWME_GenerateUpdateEvent()    SET_HSPWME_BIT(PWME_EGR, PWMEEGR_UG_MSK)

#define PWMECCMR1_OC1CE_MSK             BIT7
#define PWME_EnableETRFClearOC1REF()    SET_REG_BIT(PWME_CCMR1, PWMECCMR1_OC1CE_MSK)
#define PWME_DisableETRFClearOC1REF()   CLR_REG_BIT(PWME_CCMR1, PWMECCMR1_OC1CE_MSK)

#define HSPWME_EnableETRFClearOC1REF()  SET_HSPWME_BIT(PWME_CCMR1, PWMECCMR1_OC1CE_MSK)
#define HSPWME_DisableETRFClearOC1REF() CLR_HSPWME_BIT(PWME_CCMR1, PWMECCMR1_OC1CE_MSK)

#define PWMECCMR1_OC1M_MSK              (BIT6 | BIT5 | BIT4)
#define PWMECCMR1X_OC1M3_MSK            BIT0
#define PWME_SetOC1OutputMode(n)        MODIFY_REG(PWME_CCMR1,  PWMECCMR1_OC1M_MSK, ((n) << 4)); \
                                        MODIFY_REG(PWME_CCMR1X, PWMECCMR1X_OC1M3_MSK, (((n) >> 3) << 0))
#define PWME_OC1REFFrozen()             PWME_SetOC1OutputMode(0)
#define PWME_OC1REFHighIfMatch()        PWME_SetOC1OutputMode(1)
#define PWME_OC1REFLowIfMatch()         PWME_SetOC1OutputMode(2)
#define PWME_OC1REFToggleIfMatch()      PWME_SetOC1OutputMode(3)
#define PWME_OC1REFForceLow()           PWME_SetOC1OutputMode(4)
#define PWME_OC1REFForceHigh()          PWME_SetOC1OutputMode(5)
#define PWME_OC1REFPWMMode1()           PWME_SetOC1OutputMode(6)
#define PWME_OC1REFPWMMode2()           PWME_SetOC1OutputMode(7)
#define PWME_OC1REFReTrigOPMPWM1()      PWME_SetOC1OutputMode(8)
#define PWME_OC1REFReTrigOPMPWM2()      PWME_SetOC1OutputMode(9)
#define PWME_OC1REFCombinedPWM1()       PWME_SetOC1OutputMode(12)
#define PWME_OC1REFCombinedPWM2()       PWME_SetOC1OutputMode(13)
#define PWME_OC1REFAsymmetricPWM1()     PWME_SetOC1OutputMode(14)
#define PWME_OC1REFAsymmetricPWM2()     PWME_SetOC1OutputMode(15)

#define HSPWME_SetOC1OutputMode(n)      MODIFY_HSPWME(PWME_CCMR1,  PWMECCMR1_OC1M_MSK, ((n) << 4)); \
                                        MODIFY_HSPWME(PWME_CCMR1X, PWMECCMR1X_OC1M3_MSK, (((n) >> 3) << 0))
#define HSPWME_OC1REFFrozen()           HSPWME_SetOC1OutputMode(0)
#define HSPWME_OC1REFHighIfMatch()      HSPWME_SetOC1OutputMode(1)
#define HSPWME_OC1REFLowIfMatch()       HSPWME_SetOC1OutputMode(2)
#define HSPWME_OC1REFToggleIfMatch()    HSPWME_SetOC1OutputMode(3)
#define HSPWME_OC1REFForceLow()         HSPWME_SetOC1OutputMode(4)
#define HSPWME_OC1REFForceHigh()        HSPWME_SetOC1OutputMode(5)
#define HSPWME_OC1REFPWMMode1()         HSPWME_SetOC1OutputMode(6)
#define HSPWME_OC1REFPWMMode2()         HSPWME_SetOC1OutputMode(7)
#define HSPWME_OC1REFReTrigOPMPWM1()    HSPWME_SetOC1OutputMode(8)
#define HSPWME_OC1REFReTrigOPMPWM2()    HSPWME_SetOC1OutputMode(9)
#define HSPWME_OC1REFCombinedPWM1()     HSPWME_SetOC1OutputMode(12)
#define HSPWME_OC1REFCombinedPWM2()     HSPWME_SetOC1OutputMode(13)
#define HSPWME_OC1REFAsymmetricPWM1()   HSPWME_SetOC1OutputMode(14)
#define HSPWME_OC1REFAsymmetricPWM2()   HSPWME_SetOC1OutputMode(15)

#define PWMECCMR1_OC1PE_MSK             BIT3
#define PWME_UnbufferCCR1()             CLR_REG_BIT(PWME_CCMR1, PWMECCMR1_OC1PE_MSK)
#define PWME_BufferCCR1()               SET_REG_BIT(PWME_CCMR1, PWMECCMR1_OC1PE_MSK)

#define HSPWME_UnbufferCCR1()           CLR_HSPWME_BIT(PWME_CCMR1, PWMECCMR1_OC1PE_MSK)
#define HSPWME_BufferCCR1()             SET_HSPWME_BIT(PWME_CCMR1, PWMECCMR1_OC1PE_MSK)

#define PWMECCMR1_OC1FE_MSK             BIT2
#define PWME_DisableOC1FastMode()       CLR_REG_BIT(PWME_CCMR1, PWMECCMR1_OC1FE_MSK)
#define PWME_EnableOC1FastMode()        SET_REG_BIT(PWME_CCMR1, PWMECCMR1_OC1FE_MSK)

#define HSPWME_DisableOC1FastMode()     CLR_HSPWME_BIT(PWME_CCMR1, PWMECCMR1_OC1FE_MSK)
#define HSPWME_EnableOC1FastMode()      SET_HSPWME_BIT(PWME_CCMR1, PWMECCMR1_OC1FE_MSK)

#define PWMECCMR1_CC1S_MSK              (BIT1 | BIT0)
#define PWME_SetCC1Mode(n)              MODIFY_REG(PWME_CCMR1,  PWMECCMR1_CC1S_MSK, ((n) << 0))
#define PWME_CC1Output()                PWME_SetCC1Mode(0)
#define PWME_CC1CaptureTI1FP1()         PWME_SetCC1Mode(1)
#define PWME_CC1CaptureTI2FP1()         PWME_SetCC1Mode(2)
#define PWME_CC1CaptureTRC()            PWME_SetCC1Mode(3)

#define HSPWME_SetCC1Mode(n)            MODIFY_HSPWME(PWME_CCMR1,  PWMECCMR1_CC1S_MSK, ((n) << 0))
#define HSPWME_CC1Output()              HSPWME_SetCC1Mode(0)
#define HSPWME_CC1CaptureTI1FP1()       HSPWME_SetCC1Mode(1)
#define HSPWME_CC1CaptureTI2FP1()       HSPWME_SetCC1Mode(2)
#define HSPWME_CC1CaptureTRC()          HSPWME_SetCC1Mode(3)

#define PWMECCMR1_IC1F_MSK              (BIT_HN)
#define PWME_SetIC1Filter(n)            MODIFY_REG(PWME_CCMR1,  PWMECCMR1_IC1F_MSK, ((n) << 4))
#define PWME_IC1Filter1()               PWME_SetIC1Filter(0)
#define PWME_IC1Filter2()               PWME_SetIC1Filter(1)
#define PWME_IC1Filter4()               PWME_SetIC1Filter(2)
#define PWME_IC1Filter8()               PWME_SetIC1Filter(3)
#define PWME_IC1Filter12()              PWME_SetIC1Filter(4)
#define PWME_IC1Filter16()              PWME_SetIC1Filter(5)
#define PWME_IC1Filter24()              PWME_SetIC1Filter(6)
#define PWME_IC1Filter32()              PWME_SetIC1Filter(7)
#define PWME_IC1Filter48()              PWME_SetIC1Filter(8)
#define PWME_IC1Filter64()              PWME_SetIC1Filter(9)
#define PWME_IC1Filter80()              PWME_SetIC1Filter(10)
#define PWME_IC1Filter96()              PWME_SetIC1Filter(11)
#define PWME_IC1Filter128()             PWME_SetIC1Filter(12)
#define PWME_IC1Filter160()             PWME_SetIC1Filter(13)
#define PWME_IC1Filter192()             PWME_SetIC1Filter(14)
#define PWME_IC1Filter256()             PWME_SetIC1Filter(15)

#define HSPWME_SetIC1Filter(n)          MODIFY_HSPWME(PWME_CCMR1,  PWMECCMR1_IC1F_MSK, ((n) << 4))
#define HSPWME_IC1Filter1()             HSPWME_SetIC1Filter(0)
#define HSPWME_IC1Filter2()             HSPWME_SetIC1Filter(1)
#define HSPWME_IC1Filter4()             HSPWME_SetIC1Filter(2)
#define HSPWME_IC1Filter8()             HSPWME_SetIC1Filter(3)
#define HSPWME_IC1Filter12()            HSPWME_SetIC1Filter(4)
#define HSPWME_IC1Filter16()            HSPWME_SetIC1Filter(5)
#define HSPWME_IC1Filter24()            HSPWME_SetIC1Filter(6)
#define HSPWME_IC1Filter32()            HSPWME_SetIC1Filter(7)
#define HSPWME_IC1Filter48()            HSPWME_SetIC1Filter(8)
#define HSPWME_IC1Filter64()            HSPWME_SetIC1Filter(9)
#define HSPWME_IC1Filter80()            HSPWME_SetIC1Filter(10)
#define HSPWME_IC1Filter96()            HSPWME_SetIC1Filter(11)
#define HSPWME_IC1Filter128()           HSPWME_SetIC1Filter(12)
#define HSPWME_IC1Filter160()           HSPWME_SetIC1Filter(13)
#define HSPWME_IC1Filter192()           HSPWME_SetIC1Filter(14)
#define HSPWME_IC1Filter256()           HSPWME_SetIC1Filter(15)

#define PWMECCMR1_IC1PS_MSK             (BIT3 | BIT2)
#define PWME_SetIC1Divider(n)           MODIFY_REG(PWME_CCMR1,  PWMECCMR1_IC1PS_MSK, ((n) << 2))
#define PWME_IC1Divider1()              PWME_SetIC1Divider(0)
#define PWME_IC1Divider2()              PWME_SetIC1Divider(1)
#define PWME_IC1Divider4()              PWME_SetIC1Divider(2)
#define PWME_IC1Divider8()              PWME_SetIC1Divider(3)

#define HSPWME_SetIC1Divider(n)         MODIFY_HSPWME(PWME_CCMR1,  PWMECCMR1_IC1PS_MSK, ((n) << 2))
#define HSPWME_IC1Divider1()            HSPWME_SetIC1Divider(0)
#define HSPWME_IC1Divider2()            HSPWME_SetIC1Divider(1)
#define HSPWME_IC1Divider4()            HSPWME_SetIC1Divider(2)
#define HSPWME_IC1Divider8()            HSPWME_SetIC1Divider(3)

#define PWMECCMR2_OC2CE_MSK             BIT7
#define PWME_EnableETRFClearOC2REF()    SET_REG_BIT(PWME_CCMR2, PWMECCMR2_OC2CE_MSK)
#define PWME_DisableETRFClearOC2REF()   CLR_REG_BIT(PWME_CCMR2, PWMECCMR2_OC2CE_MSK)

#define HSPWME_EnableETRFClearOC2REF()  SET_HSPWME_BIT(PWME_CCMR2, PWMECCMR2_OC2CE_MSK)
#define HSPWME_DisableETRFClearOC2REF() CLR_HSPWME_BIT(PWME_CCMR2, PWMECCMR2_OC2CE_MSK)

#define PWMECCMR2_OC2M_MSK              (BIT6 | BIT5 | BIT4)
#define PWMECCMR2X_OC2M3_MSK            BIT0
#define PWME_SetOC2OutputMode(n)        MODIFY_REG(PWME_CCMR2,  PWMECCMR2_OC2M_MSK, ((n) << 4)); \
                                        MODIFY_REG(PWME_CCMR2X, PWMECCMR2X_OC2M3_MSK, (((n) >> 3) << 0))
#define PWME_OC2REFFrozen()             PWME_SetOC2OutputMode(0)
#define PWME_OC2REFHighIfMatch()        PWME_SetOC2OutputMode(1)
#define PWME_OC2REFLowIfMatch()         PWME_SetOC2OutputMode(2)
#define PWME_OC2REFToggleIfMatch()      PWME_SetOC2OutputMode(3)
#define PWME_OC2REFForceLow()           PWME_SetOC2OutputMode(4)
#define PWME_OC2REFForceHigh()          PWME_SetOC2OutputMode(5)
#define PWME_OC2REFPWMMode1()           PWME_SetOC2OutputMode(6)
#define PWME_OC2REFPWMMode2()           PWME_SetOC2OutputMode(7)
#define PWME_OC2REFReTrigOPMPWM1()      PWME_SetOC2OutputMode(8)
#define PWME_OC2REFReTrigOPMPWM2()      PWME_SetOC2OutputMode(9)
#define PWME_OC2REFCombinedPWM1()       PWME_SetOC2OutputMode(12)
#define PWME_OC2REFCombinedPWM2()       PWME_SetOC2OutputMode(13)
#define PWME_OC2REFAsymmetricPWM1()     PWME_SetOC2OutputMode(14)
#define PWME_OC2REFAsymmetricPWM2()     PWME_SetOC2OutputMode(15)

#define HSPWME_SetOC2OutputMode(n)      MODIFY_HSPWME(PWME_CCMR2,  PWMECCMR2_OC2M_MSK, ((n) << 4)); \
                                        MODIFY_HSPWME(PWME_CCMR2X, PWMECCMR2X_OC2M3_MSK, (((n) >> 3) << 0))
#define HSPWME_OC2REFFrozen()           HSPWME_SetOC2OutputMode(0)
#define HSPWME_OC2REFHighIfMatch()      HSPWME_SetOC2OutputMode(1)
#define HSPWME_OC2REFLowIfMatch()       HSPWME_SetOC2OutputMode(2)
#define HSPWME_OC2REFToggleIfMatch()    HSPWME_SetOC2OutputMode(3)
#define HSPWME_OC2REFForceLow()         HSPWME_SetOC2OutputMode(4)
#define HSPWME_OC2REFForceHigh()        HSPWME_SetOC2OutputMode(5)
#define HSPWME_OC2REFPWMMode1()         HSPWME_SetOC2OutputMode(6)
#define HSPWME_OC2REFPWMMode2()         HSPWME_SetOC2OutputMode(7)
#define HSPWME_OC2REFReTrigOPMPWM1()    HSPWME_SetOC2OutputMode(8)
#define HSPWME_OC2REFReTrigOPMPWM2()    HSPWME_SetOC2OutputMode(9)
#define HSPWME_OC2REFCombinedPWM1()     HSPWME_SetOC2OutputMode(12)
#define HSPWME_OC2REFCombinedPWM2()     HSPWME_SetOC2OutputMode(13)
#define HSPWME_OC2REFAsymmetricPWM1()   HSPWME_SetOC2OutputMode(14)
#define HSPWME_OC2REFAsymmetricPWM2()   HSPWME_SetOC2OutputMode(15)

#define PWMECCMR2_OC2PE_MSK             BIT3
#define PWME_UnbufferCCR2()             CLR_REG_BIT(PWME_CCMR2, PWMECCMR2_OC2PE_MSK)
#define PWME_BufferCCR2()               SET_REG_BIT(PWME_CCMR2, PWMECCMR2_OC2PE_MSK)

#define HSPWME_UnbufferCCR2()           CLR_HSPWME_BIT(PWME_CCMR2, PWMECCMR2_OC2PE_MSK)
#define HSPWME_BufferCCR2()             SET_HSPWME_BIT(PWME_CCMR2, PWMECCMR2_OC2PE_MSK)

#define PWMECCMR2_OC2FE_MSK             BIT2
#define PWME_DisableOC2FastMode()       CLR_REG_BIT(PWME_CCMR2, PWMECCMR2_OC2FE_MSK)
#define PWME_EnableOC2FastMode()        SET_REG_BIT(PWME_CCMR2, PWMECCMR2_OC2FE_MSK)

#define HSPWME_DisableOC2FastMode()     CLR_HSPWME_BIT(PWME_CCMR2, PWMECCMR2_OC2FE_MSK)
#define HSPWME_EnableOC2FastMode()      SET_HSPWME_BIT(PWME_CCMR2, PWMECCMR2_OC2FE_MSK)

#define PWMECCMR2_CC2S_MSK              (BIT1 | BIT0)
#define PWME_SetCC2Mode(n)              MODIFY_REG(PWME_CCMR2,  PWMECCMR2_CC2S_MSK, ((n) << 0))
#define PWME_CC2Output()                PWME_SetCC2Mode(0)
#define PWME_CC2CaptureTI2FP2()         PWME_SetCC2Mode(1)
#define PWME_CC2CaptureTI1FP2()         PWME_SetCC2Mode(2)
#define PWME_CC2CaptureTRC()            PWME_SetCC2Mode(3)

#define HSPWME_SetCC2Mode(n)            MODIFY_HSPWME(PWME_CCMR2,  PWMECCMR2_CC2S_MSK, ((n) << 0))
#define HSPWME_CC2Output()              HSPWME_SetCC2Mode(0)
#define HSPWME_CC2CaptureTI2FP2()       HSPWME_SetCC2Mode(1)
#define HSPWME_CC2CaptureTI1FP2()       HSPWME_SetCC2Mode(2)
#define HSPWME_CC2CaptureTRC()          HSPWME_SetCC2Mode(3)

#define PWMECCMR2_IC2F_MSK              (BIT_HN)
#define PWME_SetIC2Filter(n)            MODIFY_REG(PWME_CCMR2,  PWMECCMR2_IC2F_MSK, ((n) << 4))
#define PWME_IC2Filter1()               PWME_SetIC2Filter(0)
#define PWME_IC2Filter2()               PWME_SetIC2Filter(1)
#define PWME_IC2Filter4()               PWME_SetIC2Filter(2)
#define PWME_IC2Filter8()               PWME_SetIC2Filter(3)
#define PWME_IC2Filter12()              PWME_SetIC2Filter(4)
#define PWME_IC2Filter16()              PWME_SetIC2Filter(5)
#define PWME_IC2Filter24()              PWME_SetIC2Filter(6)
#define PWME_IC2Filter32()              PWME_SetIC2Filter(7)
#define PWME_IC2Filter48()              PWME_SetIC2Filter(8)
#define PWME_IC2Filter64()              PWME_SetIC2Filter(9)
#define PWME_IC2Filter80()              PWME_SetIC2Filter(10)
#define PWME_IC2Filter96()              PWME_SetIC2Filter(11)
#define PWME_IC2Filter128()             PWME_SetIC2Filter(12)
#define PWME_IC2Filter160()             PWME_SetIC2Filter(13)
#define PWME_IC2Filter192()             PWME_SetIC2Filter(14)
#define PWME_IC2Filter256()             PWME_SetIC2Filter(15)

#define HSPWME_SetIC2Filter(n)          MODIFY_HSPWME(PWME_CCMR2,  PWMECCMR2_IC2F_MSK, ((n) << 4))
#define HSPWME_IC2Filter1()             HSPWME_SetIC2Filter(0)
#define HSPWME_IC2Filter2()             HSPWME_SetIC2Filter(1)
#define HSPWME_IC2Filter4()             HSPWME_SetIC2Filter(2)
#define HSPWME_IC2Filter8()             HSPWME_SetIC2Filter(3)
#define HSPWME_IC2Filter12()            HSPWME_SetIC2Filter(4)
#define HSPWME_IC2Filter16()            HSPWME_SetIC2Filter(5)
#define HSPWME_IC2Filter24()            HSPWME_SetIC2Filter(6)
#define HSPWME_IC2Filter32()            HSPWME_SetIC2Filter(7)
#define HSPWME_IC2Filter48()            HSPWME_SetIC2Filter(8)
#define HSPWME_IC2Filter64()            HSPWME_SetIC2Filter(9)
#define HSPWME_IC2Filter80()            HSPWME_SetIC2Filter(10)
#define HSPWME_IC2Filter96()            HSPWME_SetIC2Filter(11)
#define HSPWME_IC2Filter128()           HSPWME_SetIC2Filter(12)
#define HSPWME_IC2Filter160()           HSPWME_SetIC2Filter(13)
#define HSPWME_IC2Filter192()           HSPWME_SetIC2Filter(14)
#define HSPWME_IC2Filter256()           HSPWME_SetIC2Filter(15)

#define PWMECCMR2_IC2PS_MSK             (BIT3 | BIT2)
#define PWME_SetIC2Divider(n)           MODIFY_REG(PWME_CCMR2,  PWMECCMR2_IC2PS_MSK, ((n) << 2))
#define PWME_IC2Divider1()              PWME_SetIC2Divider(0)
#define PWME_IC2Divider2()              PWME_SetIC2Divider(1)
#define PWME_IC2Divider4()              PWME_SetIC2Divider(2)
#define PWME_IC2Divider8()              PWME_SetIC2Divider(3)

#define HSPWME_SetIC2Divider(n)         MODIFY_HSPWME(PWME_CCMR2,  PWMECCMR2_IC2PS_MSK, ((n) << 2))
#define HSPWME_IC2Divider1()            HSPWME_SetIC2Divider(0)
#define HSPWME_IC2Divider2()            HSPWME_SetIC2Divider(1)
#define HSPWME_IC2Divider4()            HSPWME_SetIC2Divider(2)
#define HSPWME_IC2Divider8()            HSPWME_SetIC2Divider(3)

#define PWMECCMR3_OC3CE_MSK             BIT7
#define PWME_EnableETRFClearOC3REF()    SET_REG_BIT(PWME_CCMR3, PWMECCMR3_OC3CE_MSK)
#define PWME_DisableETRFClearOC3REF()   CLR_REG_BIT(PWME_CCMR3, PWMECCMR3_OC3CE_MSK)

#define HSPWME_EnableETRFClearOC3REF()  SET_HSPWME_BIT(PWME_CCMR3, PWMECCMR3_OC3CE_MSK)
#define HSPWME_DisableETRFClearOC3REF() CLR_HSPWME_BIT(PWME_CCMR3, PWMECCMR3_OC3CE_MSK)

#define PWMECCMR3_OC3M_MSK              (BIT6 | BIT5 | BIT4)
#define PWMECCMR3X_OC3M3_MSK            BIT0
#define PWME_SetOC3OutputMode(n)        MODIFY_REG(PWME_CCMR3,  PWMECCMR3_OC3M_MSK, ((n) << 4)); \
                                        MODIFY_REG(PWME_CCMR3X, PWMECCMR3X_OC3M3_MSK, (((n) >> 3) << 0))
#define PWME_OC3REFFrozen()             PWME_SetOC3OutputMode(0)
#define PWME_OC3REFHighIfMatch()        PWME_SetOC3OutputMode(1)
#define PWME_OC3REFLowIfMatch()         PWME_SetOC3OutputMode(2)
#define PWME_OC3REFToggleIfMatch()      PWME_SetOC3OutputMode(3)
#define PWME_OC3REFForceLow()           PWME_SetOC3OutputMode(4)
#define PWME_OC3REFForceHigh()          PWME_SetOC3OutputMode(5)
#define PWME_OC3REFPWMMode1()           PWME_SetOC3OutputMode(6)
#define PWME_OC3REFPWMMode2()           PWME_SetOC3OutputMode(7)
#define PWME_OC3REFReTrigOPMPWM1()      PWME_SetOC3OutputMode(8)
#define PWME_OC3REFReTrigOPMPWM2()      PWME_SetOC3OutputMode(9)
#define PWME_OC3REFCombinedPWM1()       PWME_SetOC3OutputMode(12)
#define PWME_OC3REFCombinedPWM2()       PWME_SetOC3OutputMode(13)
#define PWME_OC3REFAsymmetricPWM1()     PWME_SetOC3OutputMode(14)
#define PWME_OC3REFAsymmetricPWM2()     PWME_SetOC3OutputMode(15)

#define HSPWME_SetOC3OutputMode(n)      MODIFY_HSPWME(PWME_CCMR3,  PWMECCMR3_OC3M_MSK, ((n) << 4)); \
                                        MODIFY_HSPWME(PWME_CCMR3X, PWMECCMR3X_OC3M3_MSK, (((n) >> 3) << 0))
#define HSPWME_OC3REFFrozen()           HSPWME_SetOC3OutputMode(0)
#define HSPWME_OC3REFHighIfMatch()      HSPWME_SetOC3OutputMode(1)
#define HSPWME_OC3REFLowIfMatch()       HSPWME_SetOC3OutputMode(2)
#define HSPWME_OC3REFToggleIfMatch()    HSPWME_SetOC3OutputMode(3)
#define HSPWME_OC3REFForceLow()         HSPWME_SetOC3OutputMode(4)
#define HSPWME_OC3REFForceHigh()        HSPWME_SetOC3OutputMode(5)
#define HSPWME_OC3REFPWMMode1()         HSPWME_SetOC3OutputMode(6)
#define HSPWME_OC3REFPWMMode2()         HSPWME_SetOC3OutputMode(7)
#define HSPWME_OC3REFReTrigOPMPWM1()    HSPWME_SetOC3OutputMode(8)
#define HSPWME_OC3REFReTrigOPMPWM2()    HSPWME_SetOC3OutputMode(9)
#define HSPWME_OC3REFCombinedPWM1()     HSPWME_SetOC3OutputMode(12)
#define HSPWME_OC3REFCombinedPWM2()     HSPWME_SetOC3OutputMode(13)
#define HSPWME_OC3REFAsymmetricPWM1()   HSPWME_SetOC3OutputMode(14)
#define HSPWME_OC3REFAsymmetricPWM2()   HSPWME_SetOC3OutputMode(15)

#define PWMECCMR3_OC3PE_MSK             BIT3
#define PWME_UnbufferCCR3()             CLR_REG_BIT(PWME_CCMR3, PWMECCMR3_OC3PE_MSK)
#define PWME_BufferCCR3()               SET_REG_BIT(PWME_CCMR3, PWMECCMR3_OC3PE_MSK)

#define HSPWME_UnbufferCCR3()           CLR_HSPWME_BIT(PWME_CCMR3, PWMECCMR3_OC3PE_MSK)
#define HSPWME_BufferCCR3()             SET_HSPWME_BIT(PWME_CCMR3, PWMECCMR3_OC3PE_MSK)

#define PWMECCMR3_OC3FE_MSK             BIT2
#define PWME_DisableOC3FastMode()       CLR_REG_BIT(PWME_CCMR3, PWMECCMR3_OC3FE_MSK)
#define PWME_EnableOC3FastMode()        SET_REG_BIT(PWME_CCMR3, PWMECCMR3_OC3FE_MSK)

#define HSPWME_DisableOC3FastMode()     CLR_HSPWME_BIT(PWME_CCMR3, PWMECCMR3_OC3FE_MSK)
#define HSPWME_EnableOC3FastMode()      SET_HSPWME_BIT(PWME_CCMR3, PWMECCMR3_OC3FE_MSK)

#define PWMECCMR3_CC3S_MSK              (BIT1 | BIT0)
#define PWME_SetCC3Mode(n)              MODIFY_REG(PWME_CCMR3,  PWMECCMR3_CC3S_MSK, ((n) << 0))
#define PWME_CC3Output()                PWME_SetCC3Mode(0)
#define PWME_CC3CaptureTI3FP3()         PWME_SetCC3Mode(1)
#define PWME_CC3CaptureTI4FP3()         PWME_SetCC3Mode(2)
#define PWME_CC3CaptureTRC()            PWME_SetCC3Mode(3)

#define HSPWME_SetCC3Mode(n)            MODIFY_HSPWME(PWME_CCMR3,  PWMECCMR3_CC3S_MSK, ((n) << 0))
#define HSPWME_CC3Output()              HSPWME_SetCC3Mode(0)
#define HSPWME_CC3CaptureTI3FP3()       HSPWME_SetCC3Mode(1)
#define HSPWME_CC3CaptureTI4FP3()       HSPWME_SetCC3Mode(2)
#define HSPWME_CC3CaptureTRC()          HSPWME_SetCC3Mode(3)

#define PWMECCMR3_IC3F_MSK              (BIT_HN)
#define PWME_SetIC3Filter(n)            MODIFY_REG(PWME_CCMR3,  PWMECCMR3_IC3F_MSK, ((n) << 4))
#define PWME_IC3Filter1()               PWME_SetIC3Filter(0)
#define PWME_IC3Filter2()               PWME_SetIC3Filter(1)
#define PWME_IC3Filter4()               PWME_SetIC3Filter(2)
#define PWME_IC3Filter8()               PWME_SetIC3Filter(3)
#define PWME_IC3Filter12()              PWME_SetIC3Filter(4)
#define PWME_IC3Filter16()              PWME_SetIC3Filter(5)
#define PWME_IC3Filter24()              PWME_SetIC3Filter(6)
#define PWME_IC3Filter32()              PWME_SetIC3Filter(7)
#define PWME_IC3Filter48()              PWME_SetIC3Filter(8)
#define PWME_IC3Filter64()              PWME_SetIC3Filter(9)
#define PWME_IC3Filter80()              PWME_SetIC3Filter(10)
#define PWME_IC3Filter96()              PWME_SetIC3Filter(11)
#define PWME_IC3Filter128()             PWME_SetIC3Filter(12)
#define PWME_IC3Filter160()             PWME_SetIC3Filter(13)
#define PWME_IC3Filter192()             PWME_SetIC3Filter(14)
#define PWME_IC3Filter256()             PWME_SetIC3Filter(15)

#define HSPWME_SetIC3Filter(n)          MODIFY_HSPWME(PWME_CCMR3,  PWMECCMR3_IC3F_MSK, ((n) << 4))
#define HSPWME_IC3Filter1()             HSPWME_SetIC3Filter(0)
#define HSPWME_IC3Filter2()             HSPWME_SetIC3Filter(1)
#define HSPWME_IC3Filter4()             HSPWME_SetIC3Filter(2)
#define HSPWME_IC3Filter8()             HSPWME_SetIC3Filter(3)
#define HSPWME_IC3Filter12()            HSPWME_SetIC3Filter(4)
#define HSPWME_IC3Filter16()            HSPWME_SetIC3Filter(5)
#define HSPWME_IC3Filter24()            HSPWME_SetIC3Filter(6)
#define HSPWME_IC3Filter32()            HSPWME_SetIC3Filter(7)
#define HSPWME_IC3Filter48()            HSPWME_SetIC3Filter(8)
#define HSPWME_IC3Filter64()            HSPWME_SetIC3Filter(9)
#define HSPWME_IC3Filter80()            HSPWME_SetIC3Filter(10)
#define HSPWME_IC3Filter96()            HSPWME_SetIC3Filter(11)
#define HSPWME_IC3Filter128()           HSPWME_SetIC3Filter(12)
#define HSPWME_IC3Filter160()           HSPWME_SetIC3Filter(13)
#define HSPWME_IC3Filter192()           HSPWME_SetIC3Filter(14)
#define HSPWME_IC3Filter256()           HSPWME_SetIC3Filter(15)

#define PWMECCMR3_IC3PS_MSK             (BIT3 | BIT2)
#define PWME_SetIC3Divider(n)           MODIFY_REG(PWME_CCMR3,  PWMECCMR3_IC3PS_MSK, ((n) << 2))
#define PWME_IC3Divider1()              PWME_SetIC3Divider(0)
#define PWME_IC3Divider2()              PWME_SetIC3Divider(1)
#define PWME_IC3Divider4()              PWME_SetIC3Divider(2)
#define PWME_IC3Divider8()              PWME_SetIC3Divider(3)

#define HSPWME_SetIC3Divider(n)         MODIFY_HSPWME(PWME_CCMR3,  PWMECCMR3_IC3PS_MSK, ((n) << 2))
#define HSPWME_IC3Divider1()            HSPWME_SetIC3Divider(0)
#define HSPWME_IC3Divider2()            HSPWME_SetIC3Divider(1)
#define HSPWME_IC3Divider4()            HSPWME_SetIC3Divider(2)
#define HSPWME_IC3Divider8()            HSPWME_SetIC3Divider(3)

#define PWMECCMR4_OC4CE_MSK             BIT7
#define PWME_EnableETRFClearOC4REF()    SET_REG_BIT(PWME_CCMR4, PWMECCMR4_OC4CE_MSK)
#define PWME_DisableETRFClearOC4REF()   CLR_REG_BIT(PWME_CCMR4, PWMECCMR4_OC4CE_MSK)

#define HSPWME_EnableETRFClearOC4REF()  SET_HSPWME_BIT(PWME_CCMR4, PWMECCMR4_OC4CE_MSK)
#define HSPWME_DisableETRFClearOC4REF() CLR_HSPWME_BIT(PWME_CCMR4, PWMECCMR4_OC4CE_MSK)

#define PWMECCMR4_OC4M_MSK              (BIT6 | BIT5 | BIT4)
#define PWMECCMR4X_OC4M3_MSK            BIT0
#define PWME_SetOC4OutputMode(n)        MODIFY_REG(PWME_CCMR4,  PWMECCMR4_OC4M_MSK, ((n) << 4)); \
                                        MODIFY_REG(PWME_CCMR4X, PWMECCMR4X_OC4M3_MSK, (((n) >> 3) << 0))
#define PWME_OC4REFFrozen()             PWME_SetOC4OutputMode(0)
#define PWME_OC4REFHighIfMatch()        PWME_SetOC4OutputMode(1)
#define PWME_OC4REFLowIfMatch()         PWME_SetOC4OutputMode(2)
#define PWME_OC4REFToggleIfMatch()      PWME_SetOC4OutputMode(3)
#define PWME_OC4REFForceLow()           PWME_SetOC4OutputMode(4)
#define PWME_OC4REFForceHigh()          PWME_SetOC4OutputMode(5)
#define PWME_OC4REFPWMMode1()           PWME_SetOC4OutputMode(6)
#define PWME_OC4REFPWMMode2()           PWME_SetOC4OutputMode(7)
#define PWME_OC4REFReTrigOPMPWM1()      PWME_SetOC4OutputMode(8)
#define PWME_OC4REFReTrigOPMPWM2()      PWME_SetOC4OutputMode(9)
#define PWME_OC4REFCombinedPWM1()       PWME_SetOC4OutputMode(12)
#define PWME_OC4REFCombinedPWM2()       PWME_SetOC4OutputMode(13)
#define PWME_OC4REFAsymmetricPWM1()     PWME_SetOC4OutputMode(14)
#define PWME_OC4REFAsymmetricPWM2()     PWME_SetOC4OutputMode(15)

#define HSPWME_SetOC4OutputMode(n)      MODIFY_HSPWME(PWME_CCMR4,  PWMECCMR4_OC4M_MSK, ((n) << 4)); \
                                        MODIFY_HSPWME(PWME_CCMR4X, PWMECCMR4X_OC4M3_MSK, (((n) >> 3) << 0))
#define HSPWME_OC4REFFrozen()           HSPWME_SetOC4OutputMode(0)
#define HSPWME_OC4REFHighIfMatch()      HSPWME_SetOC4OutputMode(1)
#define HSPWME_OC4REFLowIfMatch()       HSPWME_SetOC4OutputMode(2)
#define HSPWME_OC4REFToggleIfMatch()    HSPWME_SetOC4OutputMode(3)
#define HSPWME_OC4REFForceLow()         HSPWME_SetOC4OutputMode(4)
#define HSPWME_OC4REFForceHigh()        HSPWME_SetOC4OutputMode(5)
#define HSPWME_OC4REFPWMMode1()         HSPWME_SetOC4OutputMode(6)
#define HSPWME_OC4REFPWMMode2()         HSPWME_SetOC4OutputMode(7)
#define HSPWME_OC4REFReTrigOPMPWM1()    HSPWME_SetOC4OutputMode(8)
#define HSPWME_OC4REFReTrigOPMPWM2()    HSPWME_SetOC4OutputMode(9)
#define HSPWME_OC4REFCombinedPWM1()     HSPWME_SetOC4OutputMode(12)
#define HSPWME_OC4REFCombinedPWM2()     HSPWME_SetOC4OutputMode(13)
#define HSPWME_OC4REFAsymmetricPWM1()   HSPWME_SetOC4OutputMode(14)
#define HSPWME_OC4REFAsymmetricPWM2()   HSPWME_SetOC4OutputMode(15)

#define PWMECCMR4_OC4PE_MSK             BIT3
#define PWME_UnbufferCCR4()             CLR_REG_BIT(PWME_CCMR4, PWMECCMR4_OC4PE_MSK)
#define PWME_BufferCCR4()               SET_REG_BIT(PWME_CCMR4, PWMECCMR4_OC4PE_MSK)

#define HSPWME_UnbufferCCR4()           CLR_HSPWME_BIT(PWME_CCMR4, PWMECCMR4_OC4PE_MSK)
#define HSPWME_BufferCCR4()             SET_HSPWME_BIT(PWME_CCMR4, PWMECCMR4_OC4PE_MSK)

#define PWMECCMR4_OC4FE_MSK             BIT2
#define PWME_DisableOC4FastMode()       CLR_REG_BIT(PWME_CCMR4, PWMECCMR4_OC4FE_MSK)
#define PWME_EnableOC4FastMode()        SET_REG_BIT(PWME_CCMR4, PWMECCMR4_OC4FE_MSK)

#define HSPWME_DisableOC4FastMode()     CLR_HSPWME_BIT(PWME_CCMR4, PWMECCMR4_OC4FE_MSK)
#define HSPWME_EnableOC4FastMode()      SET_HSPWME_BIT(PWME_CCMR4, PWMECCMR4_OC4FE_MSK)

#define PWMECCMR4_CC4S_MSK              (BIT1 | BIT0)
#define PWME_SetCC4Mode(n)              MODIFY_REG(PWME_CCMR4,  PWMECCMR4_CC4S_MSK, ((n) << 0))
#define PWME_CC4Output()                PWME_SetCC4Mode(0)
#define PWME_CC4CaptureTI4FP4()         PWME_SetCC4Mode(1)
#define PWME_CC4CaptureTI3FP4()         PWME_SetCC4Mode(2)
#define PWME_CC4CaptureTRC()            PWME_SetCC4Mode(3)

#define HSPWME_SetCC4Mode(n)            MODIFY_HSPWME(PWME_CCMR4,  PWMECCMR4_CC4S_MSK, ((n) << 0))
#define HSPWME_CC4Output()              HSPWME_SetCC4Mode(0)
#define HSPWME_CC4CaptureTI4FP4()       HSPWME_SetCC4Mode(1)
#define HSPWME_CC4CaptureTI3FP4()       HSPWME_SetCC4Mode(2)
#define HSPWME_CC4CaptureTRC()          HSPWME_SetCC4Mode(3)

#define PWMECCMR4_IC4F_MSK              (BIT_HN)
#define PWME_SetIC4Filter(n)            MODIFY_REG(PWME_CCMR4,  PWMECCMR4_IC4F_MSK, ((n) << 4))
#define PWME_IC4Filter1()               PWME_SetIC4Filter(0)
#define PWME_IC4Filter2()               PWME_SetIC4Filter(1)
#define PWME_IC4Filter4()               PWME_SetIC4Filter(2)
#define PWME_IC4Filter8()               PWME_SetIC4Filter(3)
#define PWME_IC4Filter12()              PWME_SetIC4Filter(4)
#define PWME_IC4Filter16()              PWME_SetIC4Filter(5)
#define PWME_IC4Filter24()              PWME_SetIC4Filter(6)
#define PWME_IC4Filter32()              PWME_SetIC4Filter(7)
#define PWME_IC4Filter48()              PWME_SetIC4Filter(8)
#define PWME_IC4Filter64()              PWME_SetIC4Filter(9)
#define PWME_IC4Filter80()              PWME_SetIC4Filter(10)
#define PWME_IC4Filter96()              PWME_SetIC4Filter(11)
#define PWME_IC4Filter128()             PWME_SetIC4Filter(12)
#define PWME_IC4Filter160()             PWME_SetIC4Filter(13)
#define PWME_IC4Filter192()             PWME_SetIC4Filter(14)
#define PWME_IC4Filter256()             PWME_SetIC4Filter(15)

#define HSPWME_SetIC4Filter(n)          MODIFY_HSPWME(PWME_CCMR4,  PWMECCMR4_IC4F_MSK, ((n) << 4))
#define HSPWME_IC4Filter1()             HSPWME_SetIC4Filter(0)
#define HSPWME_IC4Filter2()             HSPWME_SetIC4Filter(1)
#define HSPWME_IC4Filter4()             HSPWME_SetIC4Filter(2)
#define HSPWME_IC4Filter8()             HSPWME_SetIC4Filter(3)
#define HSPWME_IC4Filter12()            HSPWME_SetIC4Filter(4)
#define HSPWME_IC4Filter16()            HSPWME_SetIC4Filter(5)
#define HSPWME_IC4Filter24()            HSPWME_SetIC4Filter(6)
#define HSPWME_IC4Filter32()            HSPWME_SetIC4Filter(7)
#define HSPWME_IC4Filter48()            HSPWME_SetIC4Filter(8)
#define HSPWME_IC4Filter64()            HSPWME_SetIC4Filter(9)
#define HSPWME_IC4Filter80()            HSPWME_SetIC4Filter(10)
#define HSPWME_IC4Filter96()            HSPWME_SetIC4Filter(11)
#define HSPWME_IC4Filter128()           HSPWME_SetIC4Filter(12)
#define HSPWME_IC4Filter160()           HSPWME_SetIC4Filter(13)
#define HSPWME_IC4Filter192()           HSPWME_SetIC4Filter(14)
#define HSPWME_IC4Filter256()           HSPWME_SetIC4Filter(15)

#define PWMECCMR4_IC4PS_MSK             (BIT3 | BIT2)
#define PWME_SetIC4Divider(n)           MODIFY_REG(PWME_CCMR4,  PWMECCMR4_IC4PS_MSK, ((n) << 2))
#define PWME_IC4Divider1()              PWME_SetIC4Divider(0)
#define PWME_IC4Divider2()              PWME_SetIC4Divider(1)
#define PWME_IC4Divider4()              PWME_SetIC4Divider(2)
#define PWME_IC4Divider8()              PWME_SetIC4Divider(3)

#define HSPWME_SetIC4Divider(n)         MODIFY_HSPWME(PWME_CCMR4,  PWMECCMR4_IC4PS_MSK, ((n) << 2))
#define HSPWME_IC4Divider1()            HSPWME_SetIC4Divider(0)
#define HSPWME_IC4Divider2()            HSPWME_SetIC4Divider(1)
#define HSPWME_IC4Divider4()            HSPWME_SetIC4Divider(2)
#define HSPWME_IC4Divider8()            HSPWME_SetIC4Divider(3)

#define PWMECCMR5_OC5CE_MSK             BIT7
#define PWME_EnableETRFClearOC5REF()    SET_REG_BIT(PWME_CCMR5, PWMECCMR5_OC5CE_MSK)
#define PWME_DisableETRFClearOC5REF()   CLR_REG_BIT(PWME_CCMR5, PWMECCMR5_OC5CE_MSK)

#define HSPWME_EnableETRFClearOC5REF()  SET_HSPWME_BIT(PWME_CCMR5, PWMECCMR5_OC5CE_MSK)
#define HSPWME_DisableETRFClearOC5REF() CLR_HSPWME_BIT(PWME_CCMR5, PWMECCMR5_OC5CE_MSK)

#define PWMECCMR5_OC5M_MSK              (BIT6 | BIT5 | BIT4)
#define PWMECCMR5X_OC5M3_MSK            BIT0
#define PWME_SetOC5OutputMode(n)        MODIFY_REG(PWME_CCMR5,  PWMECCMR5_OC5M_MSK, ((n) << 4)); \
                                        MODIFY_REG(PWME_CCMR5X, PWMECCMR5X_OC5M3_MSK, (((n) >> 3) << 0))
#define PWME_OC5REFFrozen()             PWME_SetOC5OutputMode(0)
#define PWME_OC5REFHighIfMatch()        PWME_SetOC5OutputMode(1)
#define PWME_OC5REFLowIfMatch()         PWME_SetOC5OutputMode(2)
#define PWME_OC5REFToggleIfMatch()      PWME_SetOC5OutputMode(3)
#define PWME_OC5REFForceLow()           PWME_SetOC5OutputMode(4)
#define PWME_OC5REFForceHigh()          PWME_SetOC5OutputMode(5)
#define PWME_OC5REFPWMMode1()           PWME_SetOC5OutputMode(6)
#define PWME_OC5REFPWMMode2()           PWME_SetOC5OutputMode(7)
#define PWME_OC5REFReTrigOPMPWM1()      PWME_SetOC5OutputMode(8)
#define PWME_OC5REFReTrigOPMPWM2()      PWME_SetOC5OutputMode(9)
#define PWME_OC5REFCombinedPWM1()       PWME_SetOC5OutputMode(12)
#define PWME_OC5REFCombinedPWM2()       PWME_SetOC5OutputMode(13)
#define PWME_OC5REFAsymmetricPWM1()     PWME_SetOC5OutputMode(14)
#define PWME_OC5REFAsymmetricPWM2()     PWME_SetOC5OutputMode(15)

#define HSPWME_SetOC5OutputMode(n)      MODIFY_HSPWME(PWME_CCMR5,  PWMECCMR5_OC5M_MSK, ((n) << 4)); \
                                        MODIFY_HSPWME(PWME_CCMR5X, PWMECCMR5X_OC5M3_MSK, (((n) >> 3) << 0))
#define HSPWME_OC5REFFrozen()           HSPWME_SetOC5OutputMode(0)
#define HSPWME_OC5REFHighIfMatch()      HSPWME_SetOC5OutputMode(1)
#define HSPWME_OC5REFLowIfMatch()       HSPWME_SetOC5OutputMode(2)
#define HSPWME_OC5REFToggleIfMatch()    HSPWME_SetOC5OutputMode(3)
#define HSPWME_OC5REFForceLow()         HSPWME_SetOC5OutputMode(4)
#define HSPWME_OC5REFForceHigh()        HSPWME_SetOC5OutputMode(5)
#define HSPWME_OC5REFPWMMode1()         HSPWME_SetOC5OutputMode(6)
#define HSPWME_OC5REFPWMMode2()         HSPWME_SetOC5OutputMode(7)
#define HSPWME_OC5REFReTrigOPMPWM1()    HSPWME_SetOC5OutputMode(8)
#define HSPWME_OC5REFReTrigOPMPWM2()    HSPWME_SetOC5OutputMode(9)
#define HSPWME_OC5REFCombinedPWM1()     HSPWME_SetOC5OutputMode(12)
#define HSPWME_OC5REFCombinedPWM2()     HSPWME_SetOC5OutputMode(13)
#define HSPWME_OC5REFAsymmetricPWM1()   HSPWME_SetOC5OutputMode(14)
#define HSPWME_OC5REFAsymmetricPWM2()   HSPWME_SetOC5OutputMode(15)

#define PWMECCMR5_OC5PE_MSK             BIT3
#define PWME_UnbufferCCR5()             CLR_REG_BIT(PWME_CCMR5, PWMECCMR5_OC5PE_MSK)
#define PWME_BufferCCR5()               SET_REG_BIT(PWME_CCMR5, PWMECCMR5_OC5PE_MSK)

#define HSPWME_UnbufferCCR5()           CLR_HSPWME_BIT(PWME_CCMR5, PWMECCMR5_OC5PE_MSK)
#define HSPWME_BufferCCR5()             SET_HSPWME_BIT(PWME_CCMR5, PWMECCMR5_OC5PE_MSK)

#define PWMECCMR6_OC6CE_MSK             BIT7
#define PWME_EnableETRFClearOC6REF()    SET_REG_BIT(PWME_CCMR6, PWMECCMR6_OC6CE_MSK)
#define PWME_DisableETRFClearOC6REF()   CLR_REG_BIT(PWME_CCMR6, PWMECCMR6_OC6CE_MSK)

#define HSPWME_EnableETRFClearOC6REF()  SET_HSPWME_BIT(PWME_CCMR6, PWMECCMR6_OC6CE_MSK)
#define HSPWME_DisableETRFClearOC6REF() CLR_HSPWME_BIT(PWME_CCMR6, PWMECCMR6_OC6CE_MSK)

#define PWMECCMR6_OC6M_MSK              (BIT6 | BIT5 | BIT4)
#define PWMECCMR6X_OC6M3_MSK            BIT0
#define PWME_SetOC6OutputMode(n)        MODIFY_REG(PWME_CCMR6,  PWMECCMR6_OC6M_MSK, ((n) << 4)); \
                                        MODIFY_REG(PWME_CCMR6X, PWMECCMR6X_OC6M3_MSK, (((n) >> 3) << 0))
#define PWME_OC6REFFrozen()             PWME_SetOC6OutputMode(0)
#define PWME_OC6REFHighIfMatch()        PWME_SetOC6OutputMode(1)
#define PWME_OC6REFLowIfMatch()         PWME_SetOC6OutputMode(2)
#define PWME_OC6REFToggleIfMatch()      PWME_SetOC6OutputMode(3)
#define PWME_OC6REFForceLow()           PWME_SetOC6OutputMode(4)
#define PWME_OC6REFForceHigh()          PWME_SetOC6OutputMode(5)
#define PWME_OC6REFPWMMode1()           PWME_SetOC6OutputMode(6)
#define PWME_OC6REFPWMMode2()           PWME_SetOC6OutputMode(7)
#define PWME_OC6REFReTrigOPMPWM1()      PWME_SetOC6OutputMode(8)
#define PWME_OC6REFReTrigOPMPWM2()      PWME_SetOC6OutputMode(9)
#define PWME_OC6REFCombinedPWM1()       PWME_SetOC6OutputMode(12)
#define PWME_OC6REFCombinedPWM2()       PWME_SetOC6OutputMode(13)
#define PWME_OC6REFAsymmetricPWM1()     PWME_SetOC6OutputMode(14)
#define PWME_OC6REFAsymmetricPWM2()     PWME_SetOC6OutputMode(15)

#define HSPWME_SetOC6OutputMode(n)      MODIFY_HSPWME(PWME_CCMR6,  PWMECCMR6_OC6M_MSK, ((n) << 4)); \
                                        MODIFY_HSPWME(PWME_CCMR6X, PWMECCMR6X_OC6M3_MSK, (((n) >> 3) << 0))
#define HSPWME_OC6REFFrozen()           HSPWME_SetOC6OutputMode(0)
#define HSPWME_OC6REFHighIfMatch()      HSPWME_SetOC6OutputMode(1)
#define HSPWME_OC6REFLowIfMatch()       HSPWME_SetOC6OutputMode(2)
#define HSPWME_OC6REFToggleIfMatch()    HSPWME_SetOC6OutputMode(3)
#define HSPWME_OC6REFForceLow()         HSPWME_SetOC6OutputMode(4)
#define HSPWME_OC6REFForceHigh()        HSPWME_SetOC6OutputMode(5)
#define HSPWME_OC6REFPWMMode1()         HSPWME_SetOC6OutputMode(6)
#define HSPWME_OC6REFPWMMode2()         HSPWME_SetOC6OutputMode(7)
#define HSPWME_OC6REFReTrigOPMPWM1()    HSPWME_SetOC6OutputMode(8)
#define HSPWME_OC6REFReTrigOPMPWM2()    HSPWME_SetOC6OutputMode(9)
#define HSPWME_OC6REFCombinedPWM1()     HSPWME_SetOC6OutputMode(12)
#define HSPWME_OC6REFCombinedPWM2()     HSPWME_SetOC6OutputMode(13)
#define HSPWME_OC6REFAsymmetricPWM1()   HSPWME_SetOC6OutputMode(14)
#define HSPWME_OC6REFAsymmetricPWM2()   HSPWME_SetOC6OutputMode(15)

#define PWMECCMR6_OC6PE_MSK             BIT3
#define PWME_UnbufferCCR6()             CLR_REG_BIT(PWME_CCMR6, PWMECCMR6_OC6PE_MSK)
#define PWME_BufferCCR6()               SET_REG_BIT(PWME_CCMR6, PWMECCMR6_OC6PE_MSK)

#define HSPWME_UnbufferCCR6()           CLR_HSPWME_BIT(PWME_CCMR6, PWMECCMR6_OC6PE_MSK)
#define HSPWME_BufferCCR6()             SET_HSPWME_BIT(PWME_CCMR6, PWMECCMR6_OC6PE_MSK)

#define PWMECCER1_CC1E_MSK              BIT0
#define PWME_CC1PEnable()               SET_REG_BIT(PWME_CCER1, PWMECCER1_CC1E_MSK)
#define PWME_CC1PDisable()              CLR_REG_BIT(PWME_CCER1, PWMECCER1_CC1E_MSK)

#define HSPWME_CC1PEnable()             SET_HSPWME_BIT(PWME_CCER1, PWMECCER1_CC1E_MSK)
#define HSPWME_CC1PDisable()            CLR_HSPWME_BIT(PWME_CCER1, PWMECCER1_CC1E_MSK)

#define PWMECCER1_CC1P_MSK              BIT1
#define PWME_CC1PNonInverted()          CLR_REG_BIT(PWME_CCER1, PWMECCER1_CC1P_MSK)
#define PWME_CC1PInverted()             SET_REG_BIT(PWME_CCER1, PWMECCER1_CC1P_MSK)

#define HSPWME_CC1PNonInverted()        CLR_HSPWME_BIT(PWME_CCER1, PWMECCER1_CC1P_MSK)
#define HSPWME_CC1PInverted()           SET_HSPWME_BIT(PWME_CCER1, PWMECCER1_CC1P_MSK)

#define PWMECCER1_CC1NE_MSK             BIT2
#define PWME_CC1NEnable()               SET_REG_BIT(PWME_CCER1, PWMECCER1_CC1NE_MSK)
#define PWME_CC1NDisable()              CLR_REG_BIT(PWME_CCER1, PWMECCER1_CC1NE_MSK)

#define HSPWME_CC1NEnable()             SET_HSPWME_BIT(PWME_CCER1, PWMECCER1_CC1NE_MSK)
#define HSPWME_CC1NDisable()            CLR_HSPWME_BIT(PWME_CCER1, PWMECCER1_CC1NE_MSK)

#define PWMECCER1_CC1NP_MSK             BIT3
#define PWME_CC1NNonInverted()          CLR_REG_BIT(PWME_CCER1, PWMECCER1_CC1NP_MSK)
#define PWME_CC1NInverted()             SET_REG_BIT(PWME_CCER1, PWMECCER1_CC1NP_MSK)

#define HSPWME_CC1NNonInverted()        CLR_HSPWME_BIT(PWME_CCER1, PWMECCER1_CC1NP_MSK)
#define HSPWME_CC1NInverted()           SET_HSPWME_BIT(PWME_CCER1, PWMECCER1_CC1NP_MSK)

#define PWMECCER1_CC2E_MSK              BIT4
#define PWME_CC2PEnable()               SET_REG_BIT(PWME_CCER1, PWMECCER1_CC2E_MSK)
#define PWME_CC2PDisable()              CLR_REG_BIT(PWME_CCER1, PWMECCER1_CC2E_MSK)

#define HSPWME_CC2PEnable()             SET_HSPWME_BIT(PWME_CCER1, PWMECCER1_CC2E_MSK)
#define HSPWME_CC2PDisable()            CLR_HSPWME_BIT(PWME_CCER1, PWMECCER1_CC2E_MSK)

#define PWMECCER1_CC2P_MSK              BIT5
#define PWME_CC2PNonInverted()          CLR_REG_BIT(PWME_CCER1, PWMECCER1_CC2P_MSK)
#define PWME_CC2PInverted()             SET_REG_BIT(PWME_CCER1, PWMECCER1_CC2P_MSK)

#define HSPWME_CC2PNonInverted()        CLR_HSPWME_BIT(PWME_CCER1, PWMECCER1_CC2P_MSK)
#define HSPWME_CC2PInverted()           SET_HSPWME_BIT(PWME_CCER1, PWMECCER1_CC2P_MSK)

#define PWMECCER1_CC2NE_MSK             BIT6
#define PWME_CC2NEnable()               SET_REG_BIT(PWME_CCER1, PWMECCER1_CC2NE_MSK)
#define PWME_CC2NDisable()              CLR_REG_BIT(PWME_CCER1, PWMECCER1_CC2NE_MSK)

#define HSPWME_CC2NEnable()             SET_HSPWME_BIT(PWME_CCER1, PWMECCER1_CC2NE_MSK)
#define HSPWME_CC2NDisable()            CLR_HSPWME_BIT(PWME_CCER1, PWMECCER1_CC2NE_MSK)

#define PWMECCER1_CC2NP_MSK             BIT7
#define PWME_CC2NNonInverted()          CLR_REG_BIT(PWME_CCER1, PWMECCER1_CC2NP_MSK)
#define PWME_CC2NInverted()             SET_REG_BIT(PWME_CCER1, PWMECCER1_CC2NP_MSK)

#define HSPWME_CC2NNonInverted()        CLR_HSPWME_BIT(PWME_CCER1, PWMECCER1_CC2NP_MSK)
#define HSPWME_CC2NInverted()           SET_HSPWME_BIT(PWME_CCER1, PWMECCER1_CC2NP_MSK)

#define PWMECCER2_CC3E_MSK              BIT0
#define PWME_CC3PEnable()               SET_REG_BIT(PWME_CCER2, PWMECCER2_CC3E_MSK)
#define PWME_CC3PDisable()              CLR_REG_BIT(PWME_CCER2, PWMECCER2_CC3E_MSK)

#define HSPWME_CC3PEnable()             SET_HSPWME_BIT(PWME_CCER2, PWMECCER2_CC3E_MSK)
#define HSPWME_CC3PDisable()            CLR_HSPWME_BIT(PWME_CCER2, PWMECCER2_CC3E_MSK)

#define PWMECCER2_CC3P_MSK              BIT1
#define PWME_CC3PNonInverted()          CLR_REG_BIT(PWME_CCER2, PWMECCER2_CC3P_MSK)
#define PWME_CC3PInverted()             SET_REG_BIT(PWME_CCER2, PWMECCER2_CC3P_MSK)

#define HSPWME_CC3PNonInverted()        CLR_HSPWME_BIT(PWME_CCER2, PWMECCER2_CC3P_MSK)
#define HSPWME_CC3PInverted()           SET_HSPWME_BIT(PWME_CCER2, PWMECCER2_CC3P_MSK)

#define PWMECCER2_CC3NE_MSK             BIT2
#define PWME_CC3NEnable()               SET_REG_BIT(PWME_CCER2, PWMECCER2_CC3NE_MSK)
#define PWME_CC3NDisable()              CLR_REG_BIT(PWME_CCER2, PWMECCER2_CC3NE_MSK)

#define HSPWME_CC3NEnable()             SET_HSPWME_BIT(PWME_CCER2, PWMECCER2_CC3NE_MSK)
#define HSPWME_CC3NDisable()            CLR_HSPWME_BIT(PWME_CCER2, PWMECCER2_CC3NE_MSK)

#define PWMECCER2_CC3NP_MSK             BIT3
#define PWME_CC3NNonInverted()          CLR_REG_BIT(PWME_CCER2, PWMECCER2_CC3NP_MSK)
#define PWME_CC3NInverted()             SET_REG_BIT(PWME_CCER2, PWMECCER2_CC3NP_MSK)

#define HSPWME_CC3NNonInverted()        CLR_HSPWME_BIT(PWME_CCER2, PWMECCER2_CC3NP_MSK)
#define HSPWME_CC3NInverted()           SET_HSPWME_BIT(PWME_CCER2, PWMECCER2_CC3NP_MSK)

#define PWMECCER2_CC4E_MSK              BIT4
#define PWME_CC4PEnable()               SET_REG_BIT(PWME_CCER2, PWMECCER2_CC4E_MSK)
#define PWME_CC4PDisable()              CLR_REG_BIT(PWME_CCER2, PWMECCER2_CC4E_MSK)

#define HSPWME_CC4PEnable()             SET_HSPWME_BIT(PWME_CCER2, PWMECCER2_CC4E_MSK)
#define HSPWME_CC4PDisable()            CLR_HSPWME_BIT(PWME_CCER2, PWMECCER2_CC4E_MSK)

#define PWMECCER2_CC4P_MSK              BIT5
#define PWME_CC4PNonInverted()          CLR_REG_BIT(PWME_CCER2, PWMECCER2_CC4P_MSK)
#define PWME_CC4PInverted()             SET_REG_BIT(PWME_CCER2, PWMECCER2_CC4P_MSK)

#define HSPWME_CC4PNonInverted()        CLR_HSPWME_BIT(PWME_CCER2, PWMECCER2_CC4P_MSK)
#define HSPWME_CC4PInverted()           SET_HSPWME_BIT(PWME_CCER2, PWMECCER2_CC4P_MSK)

#define PWMECCER2_CC4NE_MSK             BIT6
#define PWME_CC4NEnable()               SET_REG_BIT(PWME_CCER2, PWMECCER2_CC4NE_MSK)
#define PWME_CC4NDisable()              CLR_REG_BIT(PWME_CCER2, PWMECCER2_CC4NE_MSK)

#define HSPWME_CC4NEnable()             SET_HSPWME_BIT(PWME_CCER2, PWMECCER2_CC4NE_MSK)
#define HSPWME_CC4NDisable()            CLR_HSPWME_BIT(PWME_CCER2, PWMECCER2_CC4NE_MSK)

#define PWMECCER2_CC4NP_MSK             BIT7
#define PWME_CC4NNonInverted()          CLR_REG_BIT(PWME_CCER2, PWMECCER2_CC4NP_MSK)
#define PWME_CC4NInverted()             SET_REG_BIT(PWME_CCER2, PWMECCER2_CC4NP_MSK)

#define HSPWME_CC4NNonInverted()        CLR_HSPWME_BIT(PWME_CCER2, PWMECCER2_CC4NP_MSK)
#define HSPWME_CC4NInverted()           SET_HSPWME_BIT(PWME_CCER2, PWMECCER2_CC4NP_MSK)

#define PWMECCER3_CC5E_MSK              BIT0
#define PWME_CC5PEnable()               SET_REG_BIT(PWME_CCER3, PWMECCER3_CC5E_MSK)
#define PWME_CC5PDisable()              CLR_REG_BIT(PWME_CCER3, PWMECCER3_CC5E_MSK)

#define HSPWME_CC5PEnable()             SET_HSPWME_BIT(PWME_CCER3, PWMECCER3_CC5E_MSK)
#define HSPWME_CC5PDisable()            CLR_HSPWME_BIT(PWME_CCER3, PWMECCER3_CC5E_MSK)

#define PWMECCER3_CC5P_MSK              BIT1
#define PWME_CC5PNonInverted()          CLR_REG_BIT(PWME_CCER3, PWMECCER3_CC5P_MSK)
#define PWME_CC5PInverted()             SET_REG_BIT(PWME_CCER3, PWMECCER3_CC5P_MSK)

#define HSPWME_CC5PNonInverted()        CLR_HSPWME_BIT(PWME_CCER3, PWMECCER3_CC5P_MSK)
#define HSPWME_CC5PInverted()           SET_HSPWME_BIT(PWME_CCER3, PWMECCER3_CC5P_MSK)

#define PWMECCER3_CC6E_MSK              BIT4
#define PWME_CC6PEnable()               SET_REG_BIT(PWME_CCER3, PWMECCER3_CC6E_MSK)
#define PWME_CC6PDisable()              CLR_REG_BIT(PWME_CCER3, PWMECCER3_CC6E_MSK)

#define HSPWME_CC6PEnable()             SET_HSPWME_BIT(PWME_CCER3, PWMECCER3_CC6E_MSK)
#define HSPWME_CC6PDisable()            CLR_HSPWME_BIT(PWME_CCER3, PWMECCER3_CC6E_MSK)

#define PWMECCER3_CC6P_MSK              BIT5
#define PWME_CC6PNonInverted()          CLR_REG_BIT(PWME_CCER3, PWMECCER3_CC6P_MSK)
#define PWME_CC6PInverted()             SET_REG_BIT(PWME_CCER3, PWMECCER3_CC6P_MSK)

#define HSPWME_CC6PNonInverted()        CLR_HSPWME_BIT(PWME_CCER3, PWMECCER3_CC6P_MSK)
#define HSPWME_CC6PInverted()           SET_HSPWME_BIT(PWME_CCER3, PWMECCER3_CC6P_MSK)

#define PWMEBRK_MOE_MSK                 BIT7
#define PWME_EnableMainOutput()         SET_REG_BIT(PWME_BKR, PWMEBRK_MOE_MSK)
#define PWME_DisableMainOutput()        CLR_REG_BIT(PWME_BKR, PWMEBRK_MOE_MSK)

#define HSPWME_EnableMainOutput()       SET_HSPWME_BIT(PWME_BKR, PWMEBRK_MOE_MSK)
#define HSPWME_DisableMainOutput()      CLR_HSPWME_BIT(PWME_BKR, PWMEBRK_MOE_MSK)

#define PWMEBRK_AOE_MSK                 BIT6
#define PWME_EnableAutoOutput()         SET_REG_BIT(PWME_BKR, PWMEBRK_AOE_MSK)
#define PWME_DisableAutoOutput()        CLR_REG_BIT(PWME_BKR, PWMEBRK_AOE_MSK)

#define HSPWME_EnableAutoOutput()       SET_HSPWME_BIT(PWME_BKR, PWMEBRK_AOE_MSK)
#define HSPWME_DisableAutoOutput()      CLR_HSPWME_BIT(PWME_BKR, PWMEBRK_AOE_MSK)

#define PWMEBRK_BKP_MSK                 BIT5
#define PWME_BRKNonInverted()           SET_REG_BIT(PWME_BKR, PWMEBRK_BKP_MSK)
#define PWME_BRKInverted()              CLR_REG_BIT(PWME_BKR, PWMEBRK_BKP_MSK)

#define HSPWME_BRKNonInverted()         SET_HSPWME_BIT(PWME_BKR, PWMEBRK_BKP_MSK)
#define HSPWME_BRKInverted()            CLR_HSPWME_BIT(PWME_BKR, PWMEBRK_BKP_MSK)

#define PWMEBRK_BKE_MSK                 BIT4
#define PWME_BRKEnable()                SET_REG_BIT(PWME_BKR, PWMEBRK_BKE_MSK)
#define PWME_BRKDisable()               CLR_REG_BIT(PWME_BKR, PWMEBRK_BKE_MSK)

#define HSPWME_BRKEnable()              SET_HSPWME_BIT(PWME_BKR, PWMEBRK_BKE_MSK)
#define HSPWME_BRKDisable()             CLR_HSPWME_BIT(PWME_BKR, PWMEBRK_BKE_MSK)

#define PWMEBRK_OSSR_MSK                BIT3
#define PWMEBRK_OSSI_MSK                BIT2
#define PWME_RunInactiveNoOutput()      CLR_REG_BIT(PWME_BKR, PWMEBRK_OSSR_MSK)
#define PWME_RunInactiveOutput()        SET_REG_BIT(PWME_BKR, PWMEBRK_OSSR_MSK)
#define PWME_IdleInactiveNoOutput()     CLR_REG_BIT(PWME_BKR, PWMEBRK_OSSI_MSK)
#define PWME_IdleInactiveOutput()       SET_REG_BIT(PWME_BKR, PWMEBRK_OSSI_MSK)

#define HSPWME_RunInactiveNoOutput()    CLR_HSPWME_BIT(PWME_BKR, PWMEBRK_OSSR_MSK)
#define HSPWME_RunInactiveOutput()      SET_HSPWME_BIT(PWME_BKR, PWMEBRK_OSSR_MSK)
#define HSPWME_IdleInactiveNoOutput()   CLR_HSPWME_BIT(PWME_BKR, PWMEBRK_OSSI_MSK)
#define HSPWME_IdleInactiveOutput()     SET_HSPWME_BIT(PWME_BKR, PWMEBRK_OSSI_MSK)

#define PWMEBRK_LOCK_MSK                (BIT1 | BIT0)
#define PWME_SetLockLevel(n)            MODIFY_REG(PWME_BKR,  PWMEBRK_LOCK_MSK, ((n) << 0))
#define PWME_SetUnLock()                PWME_SetLockLevel(0)

#define HSPWME_SetLockLevel(n)          MODIFY_HSPWME(PWME_BKR,  PWMEBRK_LOCK_MSK, ((n) << 0))
#define HSPWME_SetUnLock()              HSPWME_SetLockLevel(0)

#define PWMEOISR_OIS1_MSK               BIT0
#define PWMEOISR_OIS1N_MSK              BIT1
#define PWMEOISR_OIS2_MSK               BIT2
#define PWMEOISR_OIS2N_MSK              BIT3
#define PWMEOISR_OIS3_MSK               BIT4
#define PWMEOISR_OIS3N_MSK              BIT5
#define PWMEOISR_OIS4_MSK               BIT6
#define PWMEOISR_OIS4N_MSK              BIT7
#define PWMECR3_OIS5_MSK                BIT0
#define PWMECR3_OIS6_MSK                BIT2
#define PWME_OC1PIdleLevelLow()         CLR_REG_BIT(PWME_OISR, PWMEOISR_OIS1_MSK)
#define PWME_OC1PIdleLevelHigh()        SET_REG_BIT(PWME_OISR, PWMEOISR_OIS1_MSK)
#define PWME_OC1NIdleLevelLow()         CLR_REG_BIT(PWME_OISR, PWMEOISR_OIS1N_MSK)
#define PWME_OC1NIdleLevelHigh()        SET_REG_BIT(PWME_OISR, PWMEOISR_OIS1N_MSK)
#define PWME_OC2PIdleLevelLow()         CLR_REG_BIT(PWME_OISR, PWMEOISR_OIS2_MSK)
#define PWME_OC2PIdleLevelHigh()        SET_REG_BIT(PWME_OISR, PWMEOISR_OIS2_MSK)
#define PWME_OC2NIdleLevelLow()         CLR_REG_BIT(PWME_OISR, PWMEOISR_OIS2N_MSK)
#define PWME_OC2NIdleLevelHigh()        SET_REG_BIT(PWME_OISR, PWMEOISR_OIS2N_MSK)
#define PWME_OC3PIdleLevelLow()         CLR_REG_BIT(PWME_OISR, PWMEOISR_OIS3_MSK)
#define PWME_OC3PIdleLevelHigh()        SET_REG_BIT(PWME_OISR, PWMEOISR_OIS3_MSK)
#define PWME_OC3NIdleLevelLow()         CLR_REG_BIT(PWME_OISR, PWMEOISR_OIS3N_MSK)
#define PWME_OC3NIdleLevelHigh()        SET_REG_BIT(PWME_OISR, PWMEOISR_OIS3N_MSK)
#define PWME_OC4PIdleLevelLow()         CLR_REG_BIT(PWME_OISR, PWMEOISR_OIS4_MSK)
#define PWME_OC4PIdleLevelHigh()        SET_REG_BIT(PWME_OISR, PWMEOISR_OIS4_MSK)
#define PWME_OC4NIdleLevelLow()         CLR_REG_BIT(PWME_OISR, PWMEOISR_OIS4N_MSK)
#define PWME_OC4NIdleLevelHigh()        SET_REG_BIT(PWME_OISR, PWMEOISR_OIS4N_MSK)
#define PWME_OC5PIdleLevelLow()         CLR_REG_BIT(PWME_CR3, PWMECR3_OIS5_MSK)
#define PWME_OC5PIdleLevelHigh()        SET_REG_BIT(PWME_CR3, PWMECR3_OIS5_MSK)
#define PWME_OC6PIdleLevelLow()         CLR_REG_BIT(PWME_CR3, PWMECR3_OIS6_MSK)
#define PWME_OC6PIdleLevelHigh()        SET_REG_BIT(PWME_CR3, PWMECR3_OIS6_MSK)

#define HSPWME_OC1PIdleLevelLow()       CLR_HSPWME_BIT(PWME_OISR, PWMEOISR_OIS1_MSK)
#define HSPWME_OC1PIdleLevelHigh()      SET_HSPWME_BIT(PWME_OISR, PWMEOISR_OIS1_MSK)
#define HSPWME_OC1NIdleLevelLow()       CLR_HSPWME_BIT(PWME_OISR, PWMEOISR_OIS1N_MSK)
#define HSPWME_OC1NIdleLevelHigh()      SET_HSPWME_BIT(PWME_OISR, PWMEOISR_OIS1N_MSK)
#define HSPWME_OC2PIdleLevelLow()       CLR_HSPWME_BIT(PWME_OISR, PWMEOISR_OIS2_MSK)
#define HSPWME_OC2PIdleLevelHigh()      SET_HSPWME_BIT(PWME_OISR, PWMEOISR_OIS2_MSK)
#define HSPWME_OC2NIdleLevelLow()       CLR_HSPWME_BIT(PWME_OISR, PWMEOISR_OIS2N_MSK)
#define HSPWME_OC2NIdleLevelHigh()      SET_HSPWME_BIT(PWME_OISR, PWMEOISR_OIS2N_MSK)
#define HSPWME_OC3PIdleLevelLow()       CLR_HSPWME_BIT(PWME_OISR, PWMEOISR_OIS3_MSK)
#define HSPWME_OC3PIdleLevelHigh()      SET_HSPWME_BIT(PWME_OISR, PWMEOISR_OIS3_MSK)
#define HSPWME_OC3NIdleLevelLow()       CLR_HSPWME_BIT(PWME_OISR, PWMEOISR_OIS3N_MSK)
#define HSPWME_OC3NIdleLevelHigh()      SET_HSPWME_BIT(PWME_OISR, PWMEOISR_OIS3N_MSK)
#define HSPWME_OC4PIdleLevelLow()       CLR_HSPWME_BIT(PWME_OISR, PWMEOISR_OIS4_MSK)
#define HSPWME_OC4PIdleLevelHigh()      SET_HSPWME_BIT(PWME_OISR, PWMEOISR_OIS4_MSK)
#define HSPWME_OC4NIdleLevelLow()       CLR_HSPWME_BIT(PWME_OISR, PWMEOISR_OIS4N_MSK)
#define HSPWME_OC4NIdleLevelHigh()      SET_HSPWME_BIT(PWME_OISR, PWMEOISR_OIS4N_MSK)
#define HSPWME_OC5PIdleLevelLow()       CLR_HSPWME_BIT(PWME_CR3, PWMECR3_OIS5_MSK)
#define HSPWME_OC5PIdleLevelHigh()      SET_HSPWME_BIT(PWME_CR3, PWMECR3_OIS5_MSK)
#define HSPWME_OC6PIdleLevelLow()       CLR_HSPWME_BIT(PWME_CR3, PWMECR3_OIS6_MSK)
#define HSPWME_OC6PIdleLevelHigh()      SET_HSPWME_BIT(PWME_CR3, PWMECR3_OIS6_MSK)

#define PWME_SetCounter(n)              (PWME_CNTRH = HIBYTE(n), PWME_CNTRL = LOBYTE(n))
#define PWME_SetClockDivider(n)         (PWME_PSCRH = HIBYTE(n), PWME_PSCRL = LOBYTE(n))
#define PWME_SetReload16(n)             (PWME_ARRH = HIBYTE(n), PWME_ARRL = LOBYTE(n))
#define PWME_SetRepeatCounter(n)        (PWME_RCRH = HIBYTE(n), PWME_RCR = LOBYTE(n))

#define HSPWME_SetCounter(n)            (WRITE_HSPWME(PWME_CNTRH, HIBYTE(n)), WRITE_HSPWME(PWME_CNTRL, LOBYTE(n)))
#define HSPWME_SetClockDivider(n)       (WRITE_HSPWME(PWME_PSCRH, HIBYTE(n)), WRITE_HSPWME(PWME_PSCRL, LOBYTE(n)))
#define HSPWME_SetReload16(n)           (WRITE_HSPWME(PWME_ARRH, HIBYTE(n)), WRITE_HSPWME(PWME_ARRL, LOBYTE(n)))
#define HSPWME_SetRepeatCounter(n)      (WRITE_HSPWME(PWME_RCRH, HIBYTE(n)), WRITE_HSPWME(PWME_RCR, LOBYTE(n)))

#define PWME_SetCCR1Value(n)            (PWME_CCR1H = HIBYTE(n), PWME_CCR1L = LOBYTE(n))
#define PWME_SetCCR2Value(n)            (PWME_CCR2H = HIBYTE(n), PWME_CCR2L = LOBYTE(n))
#define PWME_SetCCR3Value(n)            (PWME_CCR3H = HIBYTE(n), PWME_CCR3L = LOBYTE(n))
#define PWME_SetCCR4Value(n)            (PWME_CCR4H = HIBYTE(n), PWME_CCR4L = LOBYTE(n))
#define PWME_SetCCR5Value(n)            (PWME_CCR5H = HIBYTE(n), PWME_CCR5L = LOBYTE(n))
#define PWME_SetCCR6Value(n)            (PWME_CCR6H = HIBYTE(n), PWME_CCR6L = LOBYTE(n))

#define HSPWME_SetCCR1Value(n)          (WRITE_HSPWME(PWME_CCR1H, HIBYTE(n)), WRITE_HSPWME(PWME_CCR1L, LOBYTE(n)))
#define HSPWME_SetCCR2Value(n)          (WRITE_HSPWME(PWME_CCR2H, HIBYTE(n)), WRITE_HSPWME(PWME_CCR2L, LOBYTE(n)))
#define HSPWME_SetCCR3Value(n)          (WRITE_HSPWME(PWME_CCR3H, HIBYTE(n)), WRITE_HSPWME(PWME_CCR3L, LOBYTE(n)))
#define HSPWME_SetCCR4Value(n)          (WRITE_HSPWME(PWME_CCR4H, HIBYTE(n)), WRITE_HSPWME(PWME_CCR4L, LOBYTE(n)))
#define HSPWME_SetCCR5Value(n)          (WRITE_HSPWME(PWME_CCR5H, HIBYTE(n)), WRITE_HSPWME(PWME_CCR5L, LOBYTE(n)))
#define HSPWME_SetCCR6Value(n)          (WRITE_HSPWME(PWME_CCR6H, HIBYTE(n)), WRITE_HSPWME(PWME_CCR6L, LOBYTE(n)))

#define PWME_ReadReload16()             MAKEWORD(PWME_ARRL, PWME_ARRH)

#define HSPWME_ReadReload16()           MAKEWORD(READ_HSPWME(PWME_ARRL), READ_HSPWME(PWME_ARRH))

#define PWME_ReadCCR1Value()            MAKEWORD(PWME_CCR1L, PWME_CCR1H)
#define PWME_ReadCCR2Value()            MAKEWORD(PWME_CCR2L, PWME_CCR2H)
#define PWME_ReadCCR3Value()            MAKEWORD(PWME_CCR3L, PWME_CCR3H)
#define PWME_ReadCCR4Value()            MAKEWORD(PWME_CCR4L, PWME_CCR4H)
#define PWME_ReadCCR5Value()            MAKEWORD(PWME_CCR5L, PWME_CCR5H)
#define PWME_ReadCCR6Value()            MAKEWORD(PWME_CCR6L, PWME_CCR6H)

#define HSPWME_ReadCCR1Value()          MAKEWORD(READ_HSPWME(PWME_CCR1L), READ_HSPWME(PWME_CCR1H))
#define HSPWME_ReadCCR2Value()          MAKEWORD(READ_HSPWME(PWME_CCR2L), READ_HSPWME(PWME_CCR2H))
#define HSPWME_ReadCCR3Value()          MAKEWORD(READ_HSPWME(PWME_CCR3L), READ_HSPWME(PWME_CCR3H))
#define HSPWME_ReadCCR4Value()          MAKEWORD(READ_HSPWME(PWME_CCR4L), READ_HSPWME(PWME_CCR4H))
#define HSPWME_ReadCCR5Value()          MAKEWORD(READ_HSPWME(PWME_CCR5L), READ_HSPWME(PWME_CCR5H))
#define HSPWME_ReadCCR6Value()          MAKEWORD(READ_HSPWME(PWME_CCR6L), READ_HSPWME(PWME_CCR6H))

#define PWME_SetDeadTime(n)             PWME_DTR = LOBYTE(n)

#define HSPWME_SetDeadTime(n)           WRITE_HSPWME(PWME_DTR, LOBYTE(n))

#define PWMECCR5X_GC5C3_MSK             BIT7
#define PWMECCR5X_GC5C2_MSK             BIT6
#define PWMECCR5X_GC5C1_MSK             BIT5
#define PWME_OC3REFCIndependent()       CLR_REG_BIT(PWME_CCR5X, PWMECCR5X_GC5C3_MSK)
#define PWME_OC2REFCIndependent()       CLR_REG_BIT(PWME_CCR5X, PWMECCR5X_GC5C2_MSK)
#define PWME_OC1REFCIndependent()       CLR_REG_BIT(PWME_CCR5X, PWMECCR5X_GC5C1_MSK)
#define PWME_OC3REFCAndWithOC5REF()     SET_REG_BIT(PWME_CCR5X, PWMECCR5X_GC5C3_MSK)
#define PWME_OC2REFCAndWithOC5REF()     SET_REG_BIT(PWME_CCR5X, PWMECCR5X_GC5C2_MSK)
#define PWME_OC1REFCAndWithOC5REF()     SET_REG_BIT(PWME_CCR5X, PWMECCR5X_GC5C1_MSK)

#define HSPWME_OC3REFCIndependent()     CLR_HSPWME_BIT(PWME_CCR5X, PWMECCR5X_GC5C3_MSK)
#define HSPWME_OC2REFCIndependent()     CLR_HSPWME_BIT(PWME_CCR5X, PWMECCR5X_GC5C2_MSK)
#define HSPWME_OC1REFCIndependent()     CLR_HSPWME_BIT(PWME_CCR5X, PWMECCR5X_GC5C1_MSK)
#define HSPWME_OC3REFCAndWithOC5REF()   SET_HSPWME_BIT(PWME_CCR5X, PWMECCR5X_GC5C3_MSK)
#define HSPWME_OC2REFCAndWithOC5REF()   SET_HSPWME_BIT(PWME_CCR5X, PWMECCR5X_GC5C2_MSK)
#define HSPWME_OC1REFCAndWithOC5REF()   SET_HSPWME_BIT(PWME_CCR5X, PWMECCR5X_GC5C1_MSK)

////////////////////////

#define PWMEDER_TDE_MSK                 BIT6
#define PWMEDER_COMDE_MSK               BIT5
#define PWMEDER_CC4DE_MSK               BIT4
#define PWMEDER_CC3DE_MSK               BIT3
#define PWMEDER_CC2DE_MSK               BIT2
#define PWMEDER_CC1DE_MSK               BIT1
#define PWMEDER_UDE_MSK                 BIT0
#define PWME_TriggerIntAsDMAEvent()     SET_REG_BIT(PWME_DER, PWMEDER_TDE_MSK)
#define PWME_COMIntAsDMAEvent()         SET_REG_BIT(PWME_DER, PWMEDER_COMDE_MSK)
#define PWME_CC4IntAsDMAEvent()         SET_REG_BIT(PWME_DER, PWMEDER_CC4DE_MSK)
#define PWME_CC3IntAsDMAEvent()         SET_REG_BIT(PWME_DER, PWMEDER_CC3DE_MSK)
#define PWME_CC2IntAsDMAEvent()         SET_REG_BIT(PWME_DER, PWMEDER_CC2DE_MSK)
#define PWME_CC1IntAsDMAEvent()         SET_REG_BIT(PWME_DER, PWMEDER_CC1DE_MSK)
#define PWME_UpdateIntAsDMAEvent()      SET_REG_BIT(PWME_DER, PWMEDER_UDE_MSK)

#define HSPWME_TriggerIntAsDMAEvent()   SET_HSPWME_BIT(PWME_DER, PWMEDER_TDE_MSK)
#define HSPWME_COMIntAsDMAEvent()       SET_HSPWME_BIT(PWME_DER, PWMEDER_COMDE_MSK)
#define HSPWME_CC4IntAsDMAEvent()       SET_HSPWME_BIT(PWME_DER, PWMEDER_CC4DE_MSK)
#define HSPWME_CC3IntAsDMAEvent()       SET_HSPWME_BIT(PWME_DER, PWMEDER_CC3DE_MSK)
#define HSPWME_CC2IntAsDMAEvent()       SET_HSPWME_BIT(PWME_DER, PWMEDER_CC2DE_MSK)
#define HSPWME_CC1IntAsDMAEvent()       SET_HSPWME_BIT(PWME_DER, PWMEDER_CC1DE_MSK)
#define HSPWME_UpdateIntAsDMAEvent()    SET_HSPWME_BIT(PWME_DER, PWMEDER_UDE_MSK)

#define PWMEDBA_DBA_MSK                 (BIT4 | BIT_LN)
#define PWME_SetDMABaseAddress(d)       MODIFY_REG(PWME_DBA,  PWMEDBA_DBA_MSK, ((d) << 0))

#define HSPWME_SetDMABaseAddress(d)     MODIFY_HSPWME(PWME_DBA,  PWMEDBA_DBA_MSK, ((d) << 0))

#define PWMEDBL_DBL_MSK                 (BIT4 | BIT_LN)
#define PWME_SetDMABurstCount(d)        MODIFY_REG(PWME_DBL,  PWMEDBL_DBL_MSK, ((d) << 0))

#define HSPWME_SetDMABurstCount(d)      MODIFY_HSPWME(PWME_DBL,  PWMEDBL_DBL_MSK, ((d) << 0))

#define PWMEDMACR_SIZE_MSK              (BIT1 | BIT0)
#define PWME_SetDMABurstBytes(n)        MODIFY_REG(PWME_DMACR,  PWMEDMACR_SIZE_MSK, ((n) << 0))
#define PWME_SetDMABurst1Byte()         PWME_SetDMABurstBytes(0)
#define PWME_SetDMABurst2Bytes()        PWME_SetDMABurstBytes(1)
#define PWME_SetDMABurst3Bytes()        PWME_SetDMABurstBytes(2)
#define PWME_SetDMABurst4Bytes()        PWME_SetDMABurstBytes(3)

#define HSPWME_SetDMABurstBytes(n)      MODIFY_HSPWME(PWME_DMACR,  PWMEDMACR_SIZE_MSK, ((n) << 0))
#define HSPWME_SetDMABurst1Byte()       HSPWME_SetDMABurstBytes(0)
#define HSPWME_SetDMABurst2Bytes()      HSPWME_SetDMABurstBytes(1)
#define HSPWME_SetDMABurst3Bytes()      HSPWME_SetDMABurstBytes(2)
#define HSPWME_SetDMABurst4Bytes()      HSPWME_SetDMABurstBytes(3)

#define PWMEDMACR_DSKIP_MSK             BIT4
#define PWME_DMASkipSpace()             SET_REG_BIT(PWME_DMACR, PWMEDMACR_DSKIP_MSK)
#define PWME_DMANeverSkipSpace()        CLR_REG_BIT(PWME_DMACR, PWMEDMACR_DSKIP_MSK)

#define HSPWME_DMASkipSpace()           SET_HSPWME_BIT(PWME_DMACR, PWMEDMACR_DSKIP_MSK)
#define HSPWME_DMANeverSkipSpace()      CLR_HSPWME_BIT(PWME_DMACR, PWMEDMACR_DSKIP_MSK)

#define PWMEDMACR_DDIR_MSK              BIT3
#define PWME_SetDMAOutput()             CLR_REG_BIT(PWME_DMACR, PWMEDMACR_DDIR_MSK)
#define PWME_SetDMAInput()              SET_REG_BIT(PWME_DMACR, PWMEDMACR_DDIR_MSK)

#define HSPWME_SetDMAOutput()           CLR_HSPWME_BIT(PWME_DMACR, PWMEDMACR_DDIR_MSK)
#define HSPWME_SetDMAInput()            SET_HSPWME_BIT(PWME_DMACR, PWMEDMACR_DDIR_MSK)

#define PWMEDMACR_DMAEN_MSK             BIT2
#define PWME_EnableDMA()                SET_REG_BIT(PWME_DMACR, PWMEDMACR_DMAEN_MSK)
#define PWME_DisableDMA()               CLR_REG_BIT(PWME_DMACR, PWMEDMACR_DMAEN_MSK)

#define HSPWME_EnableDMA()              SET_HSPWME_BIT(PWME_DMACR, PWMEDMACR_DMAEN_MSK)
#define HSPWME_DisableDMA()             CLR_HSPWME_BIT(PWME_DMACR, PWMEDMACR_DMAEN_MSK)

////////////////////////

#define PWMFENO_ENO5P_MSK               BIT0
#define PWMFENO_ENO6P_MSK               BIT2
#define PWMFENO_ENO7P_MSK               BIT4
#define PWMFENO_ENO8P_MSK               BIT6
#define PWMF_EnablePWM5POutput()        SET_REG_BIT(PWMF_ENO, PWMFENO_ENO5P_MSK)
#define PWMF_DisablePWM5POutput()       CLR_REG_BIT(PWMF_ENO, PWMFENO_ENO5P_MSK)
#define PWMF_EnablePWM6POutput()        SET_REG_BIT(PWMF_ENO, PWMFENO_ENO6P_MSK)
#define PWMF_DisablePWM6POutput()       CLR_REG_BIT(PWMF_ENO, PWMFENO_ENO6P_MSK)
#define PWMF_EnablePWM7POutput()        SET_REG_BIT(PWMF_ENO, PWMFENO_ENO7P_MSK)
#define PWMF_DisablePWM7POutput()       CLR_REG_BIT(PWMF_ENO, PWMFENO_ENO7P_MSK)
#define PWMF_EnablePWM8POutput()        SET_REG_BIT(PWMF_ENO, PWMFENO_ENO8P_MSK)
#define PWMF_DisablePWM8POutput()       CLR_REG_BIT(PWMF_ENO, PWMFENO_ENO8P_MSK)

#define HSPWMF_EnablePWM5POutput()      SET_HSPWMF_BIT(PWMF_ENO, PWMFENO_ENO5P_MSK)
#define HSPWMF_DisablePWM5POutput()     CLR_HSPWMF_BIT(PWMF_ENO, PWMFENO_ENO5P_MSK)
#define HSPWMF_EnablePWM6POutput()      SET_HSPWMF_BIT(PWMF_ENO, PWMFENO_ENO6P_MSK)
#define HSPWMF_DisablePWM6POutput()     CLR_HSPWMF_BIT(PWMF_ENO, PWMFENO_ENO6P_MSK)
#define HSPWMF_EnablePWM7POutput()      SET_HSPWMF_BIT(PWMF_ENO, PWMFENO_ENO7P_MSK)
#define HSPWMF_DisablePWM7POutput()     CLR_HSPWMF_BIT(PWMF_ENO, PWMFENO_ENO7P_MSK)
#define HSPWMF_EnablePWM8POutput()      SET_HSPWMF_BIT(PWMF_ENO, PWMFENO_ENO8P_MSK)
#define HSPWMF_DisablePWM8POutput()     CLR_HSPWMF_BIT(PWMF_ENO, PWMFENO_ENO8P_MSK)

#define PWMFIOAUX_AUX5P_MSK             BIT0
#define PWMFIOAUX_AUX6P_MSK             BIT2
#define PWMFIOAUX_AUX7P_MSK             BIT4
#define PWMFIOAUX_AUX8P_MSK             BIT6
#define PWMF_EnoCtrlPWM5P()             CLR_REG_BIT(PWMF_IOAUX, PWMFIOAUX_AUX5P_MSK)
#define PWMF_EnoBrkCtrlPWM5P()          SET_REG_BIT(PWMF_IOAUX, PWMFIOAUX_AUX5P_MSK)
#define PWMF_EnoCtrlPWM6P()             CLR_REG_BIT(PWMF_IOAUX, PWMFIOAUX_AUX6P_MSK)
#define PWMF_EnoBrkCtrlPWM6P()          SET_REG_BIT(PWMF_IOAUX, PWMFIOAUX_AUX6P_MSK)
#define PWMF_EnoCtrlPWM7P()             CLR_REG_BIT(PWMF_IOAUX, PWMFIOAUX_AUX7P_MSK)
#define PWMF_EnoBrkCtrlPWM7P()          SET_REG_BIT(PWMF_IOAUX, PWMFIOAUX_AUX7P_MSK)
#define PWMF_EnoCtrlPWM8P()             CLR_REG_BIT(PWMF_IOAUX, PWMFIOAUX_AUX8P_MSK)
#define PWMF_EnoBrkCtrlPWM8P()          SET_REG_BIT(PWMF_IOAUX, PWMFIOAUX_AUX8P_MSK)

#define HSPWMF_EnoCtrlPWM5P()           CLR_HSPWMF_BIT(PWMF_IOAUX, PWMFIOAUX_AUX5P_MSK)
#define HSPWMF_EnoBrkCtrlPWM5P()        SET_HSPWMF_BIT(PWMF_IOAUX, PWMFIOAUX_AUX5P_MSK)
#define HSPWMF_EnoCtrlPWM6P()           CLR_HSPWMF_BIT(PWMF_IOAUX, PWMFIOAUX_AUX6P_MSK)
#define HSPWMF_EnoBrkCtrlPWM6P()        SET_HSPWMF_BIT(PWMF_IOAUX, PWMFIOAUX_AUX6P_MSK)
#define HSPWMF_EnoCtrlPWM7P()           CLR_HSPWMF_BIT(PWMF_IOAUX, PWMFIOAUX_AUX7P_MSK)
#define HSPWMF_EnoBrkCtrlPWM7P()        SET_HSPWMF_BIT(PWMF_IOAUX, PWMFIOAUX_AUX7P_MSK)
#define HSPWMF_EnoCtrlPWM8P()           CLR_HSPWMF_BIT(PWMF_IOAUX, PWMFIOAUX_AUX8P_MSK)
#define HSPWMF_EnoBrkCtrlPWM8P()        SET_HSPWMF_BIT(PWMF_IOAUX, PWMFIOAUX_AUX8P_MSK)

#define PWMFCR1_ARPE_MSK                BIT7
#define PWMF_UnbufferARR()              CLR_REG_BIT(PWMF_CR1, PWMFCR1_ARPE_MSK)
#define PWMF_BufferARR()                SET_REG_BIT(PWMF_CR1, PWMFCR1_ARPE_MSK)

#define HSPWMF_UnbufferARR()            CLR_HSPWMF_BIT(PWMF_CR1, PWMFCR1_ARPE_MSK)
#define HSPWMF_BufferARR()              SET_HSPWMF_BIT(PWMF_CR1, PWMFCR1_ARPE_MSK)

#define PWMFCR1_CMS_MSK                 (BIT6 | BIT5)
#define PWMF_SetAlignMode(n)            MODIFY_REG(PWMF_CR1,  PWMFCR1_CMS_MSK, ((n) << 5))
#define PWMF_EdgeAlignMode()            PWMF_SetAlignMode(0)
#define PWMF_CenterAlignMode1()         PWMF_SetAlignMode(1)
#define PWMF_CenterAlignMode2()         PWMF_SetAlignMode(2)
#define PWMF_CenterAlignMode3()         PWMF_SetAlignMode(3)

#define HSPWMF_SetAlignMode(n)          MODIFY_HSPWMF(PWMF_CR1,  PWMFCR1_CMS_MSK, ((n) << 5))
#define HSPWMF_EdgeAlignMode()          HSPWMF_SetAlignMode(0)
#define HSPWMF_CenterAlignMode1()       HSPWMF_SetAlignMode(1)
#define HSPWMF_CenterAlignMode2()       HSPWMF_SetAlignMode(2)
#define HSPWMF_CenterAlignMode3()       HSPWMF_SetAlignMode(3)

#define PWMFCR1_DIR_MSK                 BIT4
#define PWMF_UpCounter()                CLR_REG_BIT(PWMF_CR1, PWMFCR1_DIR_MSK)
#define PWMF_DownCounter()              SET_REG_BIT(PWMF_CR1, PWMFCR1_DIR_MSK)

#define HSPWMF_UpCounter()              CLR_HSPWMF_BIT(PWMF_CR1, PWMFCR1_DIR_MSK)
#define HSPWMF_DownCounter()            SET_HSPWMF_BIT(PWMF_CR1, PWMFCR1_DIR_MSK)

#define PWMFCR1_OPM_MSK                 BIT3
#define PWMF_ContinueMode()             CLR_REG_BIT(PWMF_CR1, PWMFCR1_OPM_MSK)
#define PWMF_OnePulseMode()             SET_REG_BIT(PWMF_CR1, PWMFCR1_OPM_MSK)

#define HSPWMF_ContinueMode()           CLR_HSPWMF_BIT(PWMF_CR1, PWMFCR1_OPM_MSK)
#define HSPWMF_OnePulseMode()           SET_HSPWMF_BIT(PWMF_CR1, PWMFCR1_OPM_MSK)

#define PWMFCR1_URS_MSK                 BIT2
#define PWMF_UpdateRequestMode1()       SET_REG_BIT(PWMF_CR1, PWMFCR1_URS_MSK)
#define PWMF_UpdateRequestMode2()       CLR_REG_BIT(PWMF_CR1, PWMFCR1_URS_MSK)

#define HSPWMF_UpdateRequestMode1()     SET_HSPWMF_BIT(PWMF_CR1, PWMFCR1_URS_MSK)
#define HSPWMF_UpdateRequestMode2()     CLR_HSPWMF_BIT(PWMF_CR1, PWMFCR1_URS_MSK)

#define PWMFCR1_UDIS_MSK                BIT1
#define PWMF_EnableUpdate()             CLR_REG_BIT(PWMF_CR1, PWMFCR1_UDIS_MSK)
#define PWMF_DisableUpdate()            SET_REG_BIT(PWMF_CR1, PWMFCR1_UDIS_MSK)

#define HSPWMF_EnableUpdate()           CLR_HSPWMF_BIT(PWMF_CR1, PWMFCR1_UDIS_MSK)
#define HSPWMF_DisableUpdate()          SET_HSPWMF_BIT(PWMF_CR1, PWMFCR1_UDIS_MSK)

#define PWMFCR1_CEN_MSK                 BIT0
#define PWMF_Run()                      SET_REG_BIT(PWMF_CR1, PWMFCR1_CEN_MSK)
#define PWMF_Stop()                     CLR_REG_BIT(PWMF_CR1, PWMFCR1_CEN_MSK)

#define HSPWMF_Run()                    SET_HSPWMF_BIT(PWMF_CR1, PWMFCR1_CEN_MSK)
#define HSPWMF_Stop()                   CLR_HSPWMF_BIT(PWMF_CR1, PWMFCR1_CEN_MSK)

#define PWMFCR2_TIS_MSK                 BIT7
#define PWMF_PWM5PToTI()                CLR_REG_BIT(PWMF_CR2, PWMFCR2_TIS_MSK)
#define PWMF_Xor5P6P7PToTI()            SET_REG_BIT(PWMF_CR2, PWMFCR2_TIS_MSK)

#define HSPWMF_PWM5PToTI()              CLR_HSPWMF_BIT(PWMF_CR2, PWMFCR2_TIS_MSK)
#define HSPWMF_Xor5P6P7PToTI()          SET_HSPWMF_BIT(PWMF_CR2, PWMFCR2_TIS_MSK)

#define PWMFCR2_MMS_MSK                 (BIT6 | BIT5 | BIT4)
#define PWMF_SelectTRGO(n)              MODIFY_REG(PWMF_CR2,  PWMFCR2_MMS_MSK, ((n) << 4))
#define PWMF_ResetAsTRGO()              PWMF_SelectTRGO(0)
#define PWMF_EnableAsTRGO()             PWMF_SelectTRGO(1)
#define PWMF_UpdateAsTRGO()             PWMF_SelectTRGO(2)
#define PWMF_MatchAsTRGO()              PWMF_SelectTRGO(3)
#define PWMF_OC5REFAsTRGO()             PWMF_SelectTRGO(4)
#define PWMF_OC6REFAsTRGO()             PWMF_SelectTRGO(5)
#define PWMF_OC7REFAsTRGO()             PWMF_SelectTRGO(6)
#define PWMF_OC8REFAsTRGO()             PWMF_SelectTRGO(7)

#define HSPWMF_SelectTRGO(n)            MODIFY_HSPWMF(PWMF_CR2,  PWMFCR2_MMS_MSK, ((n) << 4))
#define HSPWMF_ResetAsTRGO()            HSPWMF_SelectTRGO(0)
#define HSPWMF_EnableAsTRGO()           HSPWMF_SelectTRGO(1)
#define HSPWMF_UpdateAsTRGO()           HSPWMF_SelectTRGO(2)
#define HSPWMF_MatchAsTRGO()            HSPWMF_SelectTRGO(3)
#define HSPWMF_OC5REFAsTRGO()           HSPWMF_SelectTRGO(4)
#define HSPWMF_OC6REFAsTRGO()           HSPWMF_SelectTRGO(5)
#define HSPWMF_OC7REFAsTRGO()           HSPWMF_SelectTRGO(6)
#define HSPWMF_OC8REFAsTRGO()           HSPWMF_SelectTRGO(7)

#define PWMFCR2_COMS_MSK                BIT2
#define PWMF_CCOCUpdateMode0()          CLR_REG_BIT(PWMF_CR2, PWMFCR2_COMS_MSK)
#define PWMF_CCOCUpdateMode1()          SET_REG_BIT(PWMF_CR2, PWMFCR2_COMS_MSK)

#define HSPWMF_CCOCUpdateMode0()        CLR_HSPWMF_BIT(PWMF_CR2, PWMFCR2_COMS_MSK)
#define HSPWMF_CCOCUpdateMode1()        SET_HSPWMF_BIT(PWMF_CR2, PWMFCR2_COMS_MSK)

#define PWMFCR2_CCPC_MSK                BIT0
#define PWMF_UnbufferCCOC()             CLR_REG_BIT(PWMF_CR2, PWMFCR2_CCPC_MSK)
#define PWMF_BufferCCOC()               SET_REG_BIT(PWMF_CR2, PWMFCR2_CCPC_MSK)

#define HSPWMF_UnbufferCCOC()           CLR_HSPWMF_BIT(PWMF_CR2, PWMFCR2_CCPC_MSK)
#define HSPWMF_BufferCCOC()             SET_HSPWMF_BIT(PWMF_CR2, PWMFCR2_CCPC_MSK)

#define PWMFSMCR_MSM_MSK                BIT7
#define PWMF_StandaloneMode()           CLR_REG_BIT(PWMF_SMCR, PWMFSMCR_MSM_MSK)
#define PWMF_MasterSlaveMode()          SET_REG_BIT(PWMF_SMCR, PWMFSMCR_MSM_MSK)

#define HSPWMF_StandaloneMode()         CLR_HSPWMF_BIT(PWMF_SMCR, PWMFSMCR_MSM_MSK)
#define HSPWMF_MasterSlaveMode()        SET_HSPWMF_BIT(PWMF_SMCR, PWMFSMCR_MSM_MSK)

#define PWMFSMCR_TS_MSK                 (BIT6 | BIT5 | BIT4)
#define PWMF_SelectTRGI(n)              MODIFY_REG(PWMF_SMCR,  PWMFSMCR_TS_MSK, ((n) << 4))
#define PWMF_DisableTRGI()              PWMF_SelectTRGI(0)
#define PWMF_TI5FEDAsTRGI()             PWMF_SelectTRGI(4)
#define PWMF_TI5FP5AsTRGI()             PWMF_SelectTRGI(5)
#define PWMF_TI6FP6AsTRGI()             PWMF_SelectTRGI(6)
#define PWMF_ETRFAsTRGI()               PWMF_SelectTRGI(7)

#define HSPWMF_SelectTRGI(n)            MODIFY_HSPWMF(PWMF_SMCR,  PWMFSMCR_TS_MSK, ((n) << 4))
#define HSPWMF_DisableTRGI()            HSPWMF_SelectTRGI(0)
#define HSPWMF_TI5FEDAsTRGI()           HSPWMF_SelectTRGI(4)
#define HSPWMF_TI5FP5AsTRGI()           HSPWMF_SelectTRGI(5)
#define HSPWMF_TI6FP6AsTRGI()           HSPWMF_SelectTRGI(6)
#define HSPWMF_ETRFAsTRGI()             HSPWMF_SelectTRGI(7)

#define PWMFSMCR_SMS_MSK                (BIT2 | BIT1 | BIT0)
#define PWMF_SetClockMode(n)            MODIFY_REG(PWMF_SMCR,  PWMFSMCR_SMS_MSK, ((n) << 0))
#define PWMF_InternalClockMode()        PWMF_SetClockMode(0)
#define PWMF_EncoderMode1()             PWMF_SetClockMode(1)
#define PWMF_EncoderMode2()             PWMF_SetClockMode(2)
#define PWMF_EncoderMode3()             PWMF_SetClockMode(3)
#define PWMF_TriggerResetMode()         PWMF_SetClockMode(4)
#define PWMF_TriggerGateMode()          PWMF_SetClockMode(5)
#define PWMF_TriggerStartMode()         PWMF_SetClockMode(6)
#define PWMF_ExternalClockMode()        PWMF_SetClockMode(7)

#define HSPWMF_SetClockMode(n)          MODIFY_HSPWMF(PWMF_SMCR,  PWMFSMCR_SMS_MSK, ((n) << 0))
#define HSPWMF_InternalClockMode()      HSPWMF_SetClockMode(0)
#define HSPWMF_EncoderMode1()           HSPWMF_SetClockMode(1)
#define HSPWMF_EncoderMode2()           HSPWMF_SetClockMode(2)
#define HSPWMF_EncoderMode3()           HSPWMF_SetClockMode(3)
#define HSPWMF_TriggerResetMode()       HSPWMF_SetClockMode(4)
#define HSPWMF_TriggerGateMode()        HSPWMF_SetClockMode(5)
#define HSPWMF_TriggerStartMode()       HSPWMF_SetClockMode(6)
#define HSPWMF_ExternalClockMode()      HSPWMF_SetClockMode(7)

#define PWMFETR_ETP_MSK                 BIT7
#define PWMF_ETRNonInverted()           CLR_REG_BIT(PWMF_ETR, PWMFETR_ETP_MSK)
#define PWMF_ETRInverted()              SET_REG_BIT(PWMF_ETR, PWMFETR_ETP_MSK)

#define HSPWMF_ETRNonInverted()         CLR_HSPWMF_BIT(PWMF_ETR, PWMFETR_ETP_MSK)
#define HSPWMF_ETRInverted()            SET_HSPWMF_BIT(PWMF_ETR, PWMFETR_ETP_MSK)

#define PWMFETR_ECE_MSK                 BIT6
#define PWMF_DisableExternalClock2()    CLR_REG_BIT(PWMF_ETR, PWMFETR_ECE_MSK)
#define PWMF_EnableExternalClock2()     SET_REG_BIT(PWMF_ETR, PWMFETR_ECE_MSK)

#define HSPWMF_DisableExternalClock2()  CLR_HSPWMF_BIT(PWMF_ETR, PWMFETR_ECE_MSK)
#define HSPWMF_EnableExternalClock2()   SET_HSPWMF_BIT(PWMF_ETR, PWMFETR_ECE_MSK)

#define PWMFETR_ETPS_MSK                (BIT5 | BIT4)
#define PWMF_SetETRDivider(n)           MODIFY_REG(PWMF_ETR,  PWMFETR_ETPS_MSK, ((n) << 4))
#define PWMF_ETRDivider1()              PWMF_SetETRDivider(0)
#define PWMF_ETRDivider2()              PWMF_SetETRDivider(1)
#define PWMF_ETRDivider4()              PWMF_SetETRDivider(2)
#define PWMF_ETRDivider8()              PWMF_SetETRDivider(3)

#define HSPWMF_SetETRDivider(n)         MODIFY_HSPWMF(PWMF_ETR,  PWMFETR_ETPS_MSK, ((n) << 4))
#define HSPWMF_ETRDivider1()            HSPWMF_SetETRDivider(0)
#define HSPWMF_ETRDivider2()            HSPWMF_SetETRDivider(1)
#define HSPWMF_ETRDivider4()            HSPWMF_SetETRDivider(2)
#define HSPWMF_ETRDivider8()            HSPWMF_SetETRDivider(3)

#define PWMFETR_ETF_MSK                 (BIT_LN)
#define PWMF_SetETRFilter(n)            MODIFY_REG(PWMF_ETR,  PWMFETR_ETF_MSK, ((n) << 0))
#define PWMF_ETRFilter1()               PWMF_SetETRFilter(0)
#define PWMF_ETRFilter2()               PWMF_SetETRFilter(1)
#define PWMF_ETRFilter4()               PWMF_SetETRFilter(2)
#define PWMF_ETRFilter8()               PWMF_SetETRFilter(3)
#define PWMF_ETRFilter12()              PWMF_SetETRFilter(4)
#define PWMF_ETRFilter16()              PWMF_SetETRFilter(5)
#define PWMF_ETRFilter24()              PWMF_SetETRFilter(6)
#define PWMF_ETRFilter32()              PWMF_SetETRFilter(7)
#define PWMF_ETRFilter48()              PWMF_SetETRFilter(8)
#define PWMF_ETRFilter64()              PWMF_SetETRFilter(9)
#define PWMF_ETRFilter80()              PWMF_SetETRFilter(10)
#define PWMF_ETRFilter96()              PWMF_SetETRFilter(11)
#define PWMF_ETRFilter128()             PWMF_SetETRFilter(12)
#define PWMF_ETRFilter160()             PWMF_SetETRFilter(13)
#define PWMF_ETRFilter192()             PWMF_SetETRFilter(14)
#define PWMF_ETRFilter256()             PWMF_SetETRFilter(15)

#define HSPWMF_SetETRFilter(n)          MODIFY_HSPWMF(PWMF_ETR,  PWMFETR_ETF_MSK, ((n) << 0))
#define HSPWMF_ETRFilter1()             HSPWMF_SetETRFilter(0)
#define HSPWMF_ETRFilter2()             HSPWMF_SetETRFilter(1)
#define HSPWMF_ETRFilter4()             HSPWMF_SetETRFilter(2)
#define HSPWMF_ETRFilter8()             HSPWMF_SetETRFilter(3)
#define HSPWMF_ETRFilter12()            HSPWMF_SetETRFilter(4)
#define HSPWMF_ETRFilter16()            HSPWMF_SetETRFilter(5)
#define HSPWMF_ETRFilter24()            HSPWMF_SetETRFilter(6)
#define HSPWMF_ETRFilter32()            HSPWMF_SetETRFilter(7)
#define HSPWMF_ETRFilter48()            HSPWMF_SetETRFilter(8)
#define HSPWMF_ETRFilter64()            HSPWMF_SetETRFilter(9)
#define HSPWMF_ETRFilter80()            HSPWMF_SetETRFilter(10)
#define HSPWMF_ETRFilter96()            HSPWMF_SetETRFilter(11)
#define HSPWMF_ETRFilter128()           HSPWMF_SetETRFilter(12)
#define HSPWMF_ETRFilter160()           HSPWMF_SetETRFilter(13)
#define HSPWMF_ETRFilter192()           HSPWMF_SetETRFilter(14)
#define HSPWMF_ETRFilter256()           HSPWMF_SetETRFilter(15)

#define PWMFEGR_BG_MSK                  BIT7
#define PWMFEGR_TG_MSK                  BIT6
#define PWMFEGR_COMG_MSK                BIT5
#define PWMFEGR_CC8G_MSK                BIT4
#define PWMFEGR_CC7G_MSK                BIT3
#define PWMFEGR_CC6G_MSK                BIT2
#define PWMFEGR_CC5G_MSK                BIT1
#define PWMFEGR_UG_MSK                  BIT0
#define PWMF_GenerateBreakEvent()       SET_REG_BIT(PWMF_EGR, PWMFEGR_BG_MSK)
#define PWMF_GenerateTriggerEvent()     SET_REG_BIT(PWMF_EGR, PWMFEGR_TG_MSK)
#define PWMF_GenerateCOMEvent()         SET_REG_BIT(PWMF_EGR, PWMFEGR_COMG_MSK)
#define PWMF_GenerateCC8Event()         SET_REG_BIT(PWMF_EGR, PWMFEGR_CC8G_MSK)
#define PWMF_GenerateCC7Event()         SET_REG_BIT(PWMF_EGR, PWMFEGR_CC7G_MSK)
#define PWMF_GenerateCC6Event()         SET_REG_BIT(PWMF_EGR, PWMFEGR_CC6G_MSK)
#define PWMF_GenerateCC5Event()         SET_REG_BIT(PWMF_EGR, PWMFEGR_CC5G_MSK)
#define PWMF_GenerateUpdateEvent()      SET_REG_BIT(PWMF_EGR, PWMFEGR_UG_MSK)

#define HSPWMF_GenerateBreakEvent()     SET_HSPWMF_BIT(PWMF_EGR, PWMFEGR_BG_MSK)
#define HSPWMF_GenerateTriggerEvent()   SET_HSPWMF_BIT(PWMF_EGR, PWMFEGR_TG_MSK)
#define HSPWMF_GenerateCOMEvent()       SET_HSPWMF_BIT(PWMF_EGR, PWMFEGR_COMG_MSK)
#define HSPWMF_GenerateCC8Event()       SET_HSPWMF_BIT(PWMF_EGR, PWMFEGR_CC8G_MSK)
#define HSPWMF_GenerateCC7Event()       SET_HSPWMF_BIT(PWMF_EGR, PWMFEGR_CC7G_MSK)
#define HSPWMF_GenerateCC6Event()       SET_HSPWMF_BIT(PWMF_EGR, PWMFEGR_CC6G_MSK)
#define HSPWMF_GenerateCC5Event()       SET_HSPWMF_BIT(PWMF_EGR, PWMFEGR_CC5G_MSK)
#define HSPWMF_GenerateUpdateEvent()    SET_HSPWMF_BIT(PWMF_EGR, PWMFEGR_UG_MSK)

#define PWMFCCMR1_OC5CE_MSK             BIT7
#define PWMF_EnableETRFClearOC5REF()    SET_REG_BIT(PWMF_CCMR1, PWMFCCMR1_OC5CE_MSK)
#define PWMF_DisableETRFClearOC5REF()   CLR_REG_BIT(PWMF_CCMR1, PWMFCCMR1_OC5CE_MSK)

#define HSPWMF_EnableETRFClearOC5REF()  SET_HSPWMF_BIT(PWMF_CCMR1, PWMFCCMR1_OC5CE_MSK)
#define HSPWMF_DisableETRFClearOC5REF() CLR_HSPWMF_BIT(PWMF_CCMR1, PWMFCCMR1_OC5CE_MSK)

#define PWMFCCMR1_OC5M_MSK              (BIT6 | BIT5 | BIT4)
#define PWMF_SetOC5OutputMode(n)        MODIFY_REG(PWMF_CCMR1,  PWMFCCMR1_OC5M_MSK, ((n) << 4))
#define PWMF_OC5REFFrozen()             PWMF_SetOC5OutputMode(0)
#define PWMF_OC5REFHighIfMatch()        PWMF_SetOC5OutputMode(1)
#define PWMF_OC5REFLowIfMatch()         PWMF_SetOC5OutputMode(2)
#define PWMF_OC5REFToggleIfMatch()      PWMF_SetOC5OutputMode(3)
#define PWMF_OC5REFForceLow()           PWMF_SetOC5OutputMode(4)
#define PWMF_OC5REFForceHigh()          PWMF_SetOC5OutputMode(5)
#define PWMF_OC5REFPWMMode1()           PWMF_SetOC5OutputMode(6)
#define PWMF_OC5REFPWMMode2()           PWMF_SetOC5OutputMode(7)

#define HSPWMF_SetOC5OutputMode(n)      MODIFY_HSPWMF(PWMF_CCMR1,  PWMFCCMR1_OC5M_MSK, ((n) << 4))
#define HSPWMF_OC5REFFrozen()           HSPWMF_SetOC5OutputMode(0)
#define HSPWMF_OC5REFHighIfMatch()      HSPWMF_SetOC5OutputMode(1)
#define HSPWMF_OC5REFLowIfMatch()       HSPWMF_SetOC5OutputMode(2)
#define HSPWMF_OC5REFToggleIfMatch()    HSPWMF_SetOC5OutputMode(3)
#define HSPWMF_OC5REFForceLow()         HSPWMF_SetOC5OutputMode(4)
#define HSPWMF_OC5REFForceHigh()        HSPWMF_SetOC5OutputMode(5)
#define HSPWMF_OC5REFPWMMode1()         HSPWMF_SetOC5OutputMode(6)
#define HSPWMF_OC5REFPWMMode2()         HSPWMF_SetOC5OutputMode(7)

#define PWMFCCMR1_OC5PE_MSK             BIT3
#define PWMF_UnbufferCCR5()             CLR_REG_BIT(PWMF_CCMR1, PWMFCCMR1_OC5PE_MSK)
#define PWMF_BufferCCR5()               SET_REG_BIT(PWMF_CCMR1, PWMFCCMR1_OC5PE_MSK)

#define HSPWMF_UnbufferCCR5()           CLR_HSPWMF_BIT(PWMF_CCMR1, PWMFCCMR1_OC5PE_MSK)
#define HSPWMF_BufferCCR5()             SET_HSPWMF_BIT(PWMF_CCMR1, PWMFCCMR1_OC5PE_MSK)

#define PWMFCCMR1_OC5FE_MSK             BIT2
#define PWMF_DisableOC5FastMode()       CLR_REG_BIT(PWMF_CCMR1, PWMFCCMR1_OC5FE_MSK)
#define PWMF_EnableOC5FastMode()        SET_REG_BIT(PWMF_CCMR1, PWMFCCMR1_OC5FE_MSK)

#define HSPWMF_DisableOC5FastMode()     CLR_HSPWMF_BIT(PWMF_CCMR1, PWMFCCMR1_OC5FE_MSK)
#define HSPWMF_EnableOC5FastMode()      SET_HSPWMF_BIT(PWMF_CCMR1, PWMFCCMR1_OC5FE_MSK)

#define PWMFCCMR1_CC5S_MSK              (BIT1 | BIT0)
#define PWMF_SetCC5Mode(n)              MODIFY_REG(PWMF_CCMR1,  PWMFCCMR1_CC5S_MSK, ((n) << 0))
#define PWMF_CC5Output()                PWMF_SetCC5Mode(0)
#define PWMF_CC5CaptureTI5FP5()         PWMF_SetCC5Mode(1)
#define PWMF_CC5CaptureTI6FP5()         PWMF_SetCC5Mode(2)
#define PWMF_CC5CaptureTRC()            PWMF_SetCC5Mode(3)

#define HSPWMF_SetCC5Mode(n)            MODIFY_HSPWMF(PWMF_CCMR1,  PWMFCCMR1_CC5S_MSK, ((n) << 0))
#define HSPWMF_CC5Output()              HSPWMF_SetCC5Mode(0)
#define HSPWMF_CC5CaptureTI5FP5()       HSPWMF_SetCC5Mode(1)
#define HSPWMF_CC5CaptureTI6FP5()       HSPWMF_SetCC5Mode(2)
#define HSPWMF_CC5CaptureTRC()          HSPWMF_SetCC5Mode(3)

#define PWMFCCMR1_IC5F_MSK              (BIT_HN)
#define PWMF_SetIC5Filter(n)            MODIFY_REG(PWMF_CCMR1,  PWMFCCMR1_IC5F_MSK, ((n) << 4))
#define PWMF_IC5Filter1()               PWMF_SetIC5Filter(0)
#define PWMF_IC5Filter2()               PWMF_SetIC5Filter(1)
#define PWMF_IC5Filter4()               PWMF_SetIC5Filter(2)
#define PWMF_IC5Filter8()               PWMF_SetIC5Filter(3)
#define PWMF_IC5Filter12()              PWMF_SetIC5Filter(4)
#define PWMF_IC5Filter16()              PWMF_SetIC5Filter(5)
#define PWMF_IC5Filter24()              PWMF_SetIC5Filter(6)
#define PWMF_IC5Filter32()              PWMF_SetIC5Filter(7)
#define PWMF_IC5Filter48()              PWMF_SetIC5Filter(8)
#define PWMF_IC5Filter64()              PWMF_SetIC5Filter(9)
#define PWMF_IC5Filter80()              PWMF_SetIC5Filter(10)
#define PWMF_IC5Filter96()              PWMF_SetIC5Filter(11)
#define PWMF_IC5Filter128()             PWMF_SetIC5Filter(12)
#define PWMF_IC5Filter160()             PWMF_SetIC5Filter(13)
#define PWMF_IC5Filter192()             PWMF_SetIC5Filter(14)
#define PWMF_IC5Filter256()             PWMF_SetIC5Filter(15)

#define HSPWMF_SetIC5Filter(n)          MODIFY_HSPWMF(PWMF_CCMR1,  PWMFCCMR1_IC5F_MSK, ((n) << 4))
#define HSPWMF_IC5Filter1()             HSPWMF_SetIC5Filter(0)
#define HSPWMF_IC5Filter2()             HSPWMF_SetIC5Filter(1)
#define HSPWMF_IC5Filter4()             HSPWMF_SetIC5Filter(2)
#define HSPWMF_IC5Filter8()             HSPWMF_SetIC5Filter(3)
#define HSPWMF_IC5Filter12()            HSPWMF_SetIC5Filter(4)
#define HSPWMF_IC5Filter16()            HSPWMF_SetIC5Filter(5)
#define HSPWMF_IC5Filter24()            HSPWMF_SetIC5Filter(6)
#define HSPWMF_IC5Filter32()            HSPWMF_SetIC5Filter(7)
#define HSPWMF_IC5Filter48()            HSPWMF_SetIC5Filter(8)
#define HSPWMF_IC5Filter64()            HSPWMF_SetIC5Filter(9)
#define HSPWMF_IC5Filter80()            HSPWMF_SetIC5Filter(10)
#define HSPWMF_IC5Filter96()            HSPWMF_SetIC5Filter(11)
#define HSPWMF_IC5Filter128()           HSPWMF_SetIC5Filter(12)
#define HSPWMF_IC5Filter160()           HSPWMF_SetIC5Filter(13)
#define HSPWMF_IC5Filter192()           HSPWMF_SetIC5Filter(14)
#define HSPWMF_IC5Filter256()           HSPWMF_SetIC5Filter(15)

#define PWMFCCMR1_IC5PS_MSK             (BIT3 | BIT2)
#define PWMF_SetIC5Divider(n)           MODIFY_REG(PWMF_CCMR1,  PWMFCCMR1_IC5PS_MSK, ((n) << 2))
#define PWMF_IC5Divider1()              PWMF_SetIC5Divider(0)
#define PWMF_IC5Divider2()              PWMF_SetIC5Divider(1)
#define PWMF_IC5Divider4()              PWMF_SetIC5Divider(2)
#define PWMF_IC5Divider8()              PWMF_SetIC5Divider(3)

#define HSPWMF_SetIC5Divider(n)         MODIFY_HSPWMF(PWMF_CCMR1,  PWMFCCMR1_IC5PS_MSK, ((n) << 2))
#define HSPWMF_IC5Divider1()            HSPWMF_SetIC5Divider(0)
#define HSPWMF_IC5Divider2()            HSPWMF_SetIC5Divider(1)
#define HSPWMF_IC5Divider4()            HSPWMF_SetIC5Divider(2)
#define HSPWMF_IC5Divider8()            HSPWMF_SetIC5Divider(3)

#define PWMFCCMR2_OC6CE_MSK             BIT7
#define PWMF_EnableETRFClearOC6REF()    SET_REG_BIT(PWMF_CCMR2, PWMFCCMR2_OC6CE_MSK)
#define PWMF_DisableETRFClearOC6REF()   CLR_REG_BIT(PWMF_CCMR2, PWMFCCMR2_OC6CE_MSK)

#define HSPWMF_EnableETRFClearOC6REF()  SET_HSPWMF_BIT(PWMF_CCMR2, PWMFCCMR2_OC6CE_MSK)
#define HSPWMF_DisableETRFClearOC6REF() CLR_HSPWMF_BIT(PWMF_CCMR2, PWMFCCMR2_OC6CE_MSK)

#define PWMFCCMR2_OC6M_MSK              (BIT6 | BIT5 | BIT4)
#define PWMF_SetOC6OutputMode(n)        MODIFY_REG(PWMF_CCMR2,  PWMFCCMR2_OC6M_MSK, ((n) << 4))
#define PWMF_OC6REFFrozen()             PWMF_SetOC6OutputMode(0)
#define PWMF_OC6REFHighIfMatch()        PWMF_SetOC6OutputMode(1)
#define PWMF_OC6REFLowIfMatch()         PWMF_SetOC6OutputMode(2)
#define PWMF_OC6REFToggleIfMatch()      PWMF_SetOC6OutputMode(3)
#define PWMF_OC6REFForceLow()           PWMF_SetOC6OutputMode(4)
#define PWMF_OC6REFForceHigh()          PWMF_SetOC6OutputMode(5)
#define PWMF_OC6REFPWMMode1()           PWMF_SetOC6OutputMode(6)
#define PWMF_OC6REFPWMMode2()           PWMF_SetOC6OutputMode(7)

#define HSPWMF_SetOC6OutputMode(n)      MODIFY_HSPWMF(PWMF_CCMR2,  PWMFCCMR2_OC6M_MSK, ((n) << 4))
#define HSPWMF_OC6REFFrozen()           HSPWMF_SetOC6OutputMode(0)
#define HSPWMF_OC6REFHighIfMatch()      HSPWMF_SetOC6OutputMode(1)
#define HSPWMF_OC6REFLowIfMatch()       HSPWMF_SetOC6OutputMode(2)
#define HSPWMF_OC6REFToggleIfMatch()    HSPWMF_SetOC6OutputMode(3)
#define HSPWMF_OC6REFForceLow()         HSPWMF_SetOC6OutputMode(4)
#define HSPWMF_OC6REFForceHigh()        HSPWMF_SetOC6OutputMode(5)
#define HSPWMF_OC6REFPWMMode1()         HSPWMF_SetOC6OutputMode(6)
#define HSPWMF_OC6REFPWMMode2()         HSPWMF_SetOC6OutputMode(7)

#define PWMFCCMR2_OC6PE_MSK             BIT3
#define PWMF_UnbufferCCR6()             CLR_REG_BIT(PWMF_CCMR2, PWMFCCMR2_OC6PE_MSK)
#define PWMF_BufferCCR6()               SET_REG_BIT(PWMF_CCMR2, PWMFCCMR2_OC6PE_MSK)

#define HSPWMF_UnbufferCCR6()           CLR_HSPWMF_BIT(PWMF_CCMR2, PWMFCCMR2_OC6PE_MSK)
#define HSPWMF_BufferCCR6()             SET_HSPWMF_BIT(PWMF_CCMR2, PWMFCCMR2_OC6PE_MSK)

#define PWMFCCMR2_OC6FE_MSK             BIT2
#define PWMF_DisableOC6FastMode()       CLR_REG_BIT(PWMF_CCMR2, PWMFCCMR2_OC6FE_MSK)
#define PWMF_EnableOC6FastMode()        SET_REG_BIT(PWMF_CCMR2, PWMFCCMR2_OC6FE_MSK)

#define HSPWMF_DisableOC6FastMode()     CLR_HSPWMF_BIT(PWMF_CCMR2, PWMFCCMR2_OC6FE_MSK)
#define HSPWMF_EnableOC6FastMode()      SET_HSPWMF_BIT(PWMF_CCMR2, PWMFCCMR2_OC6FE_MSK)

#define PWMFCCMR2_CC6S_MSK              (BIT1 | BIT0)
#define PWMF_SetCC6Mode(n)              MODIFY_REG(PWMF_CCMR2,  PWMFCCMR2_CC6S_MSK, ((n) << 0))
#define PWMF_CC6Output()                PWMF_SetCC6Mode(0)
#define PWMF_CC6CaptureTI6FP6()         PWMF_SetCC6Mode(1)
#define PWMF_CC6CaptureTI5FP6()         PWMF_SetCC6Mode(2)
#define PWMF_CC6CaptureTRC()            PWMF_SetCC6Mode(3)

#define HSPWMF_SetCC6Mode(n)            MODIFY_HSPWMF(PWMF_CCMR2,  PWMFCCMR2_CC6S_MSK, ((n) << 0))
#define HSPWMF_CC6Output()              HSPWMF_SetCC6Mode(0)
#define HSPWMF_CC6CaptureTI6FP6()       HSPWMF_SetCC6Mode(1)
#define HSPWMF_CC6CaptureTI5FP6()       HSPWMF_SetCC6Mode(2)
#define HSPWMF_CC6CaptureTRC()          HSPWMF_SetCC6Mode(3)

#define PWMFCCMR2_IC6F_MSK              (BIT_HN)
#define PWMF_SetIC6Filter(n)            MODIFY_REG(PWMF_CCMR2,  PWMFCCMR2_IC6F_MSK, ((n) << 4))
#define PWMF_IC6Filter1()               PWMF_SetIC6Filter(0)
#define PWMF_IC6Filter2()               PWMF_SetIC6Filter(1)
#define PWMF_IC6Filter4()               PWMF_SetIC6Filter(2)
#define PWMF_IC6Filter8()               PWMF_SetIC6Filter(3)
#define PWMF_IC6Filter12()              PWMF_SetIC6Filter(4)
#define PWMF_IC6Filter16()              PWMF_SetIC6Filter(5)
#define PWMF_IC6Filter24()              PWMF_SetIC6Filter(6)
#define PWMF_IC6Filter32()              PWMF_SetIC6Filter(7)
#define PWMF_IC6Filter48()              PWMF_SetIC6Filter(8)
#define PWMF_IC6Filter64()              PWMF_SetIC6Filter(9)
#define PWMF_IC6Filter80()              PWMF_SetIC6Filter(10)
#define PWMF_IC6Filter96()              PWMF_SetIC6Filter(11)
#define PWMF_IC6Filter128()             PWMF_SetIC6Filter(12)
#define PWMF_IC6Filter160()             PWMF_SetIC6Filter(13)
#define PWMF_IC6Filter192()             PWMF_SetIC6Filter(14)
#define PWMF_IC6Filter256()             PWMF_SetIC6Filter(15)

#define HSPWMF_SetIC6Filter(n)          MODIFY_HSPWMF(PWMF_CCMR2,  PWMFCCMR2_IC6F_MSK, ((n) << 4))
#define HSPWMF_IC6Filter1()             HSPWMF_SetIC6Filter(0)
#define HSPWMF_IC6Filter2()             HSPWMF_SetIC6Filter(1)
#define HSPWMF_IC6Filter4()             HSPWMF_SetIC6Filter(2)
#define HSPWMF_IC6Filter8()             HSPWMF_SetIC6Filter(3)
#define HSPWMF_IC6Filter12()            HSPWMF_SetIC6Filter(4)
#define HSPWMF_IC6Filter16()            HSPWMF_SetIC6Filter(5)
#define HSPWMF_IC6Filter24()            HSPWMF_SetIC6Filter(6)
#define HSPWMF_IC6Filter32()            HSPWMF_SetIC6Filter(7)
#define HSPWMF_IC6Filter48()            HSPWMF_SetIC6Filter(8)
#define HSPWMF_IC6Filter64()            HSPWMF_SetIC6Filter(9)
#define HSPWMF_IC6Filter80()            HSPWMF_SetIC6Filter(10)
#define HSPWMF_IC6Filter96()            HSPWMF_SetIC6Filter(11)
#define HSPWMF_IC6Filter128()           HSPWMF_SetIC6Filter(12)
#define HSPWMF_IC6Filter160()           HSPWMF_SetIC6Filter(13)
#define HSPWMF_IC6Filter192()           HSPWMF_SetIC6Filter(14)
#define HSPWMF_IC6Filter256()           HSPWMF_SetIC6Filter(15)

#define PWMFCCMR2_IC6PS_MSK             (BIT3 | BIT2)
#define PWMF_SetIC6Divider(n)           MODIFY_REG(PWMF_CCMR2,  PWMFCCMR2_IC6PS_MSK, ((n) << 2))
#define PWMF_IC6Divider1()              PWMF_SetIC6Divider(0)
#define PWMF_IC6Divider2()              PWMF_SetIC6Divider(1)
#define PWMF_IC6Divider4()              PWMF_SetIC6Divider(2)
#define PWMF_IC6Divider8()              PWMF_SetIC6Divider(3)

#define HSPWMF_SetIC6Divider(n)         MODIFY_HSPWMF(PWMF_CCMR2,  PWMFCCMR2_IC6PS_MSK, ((n) << 2))
#define HSPWMF_IC6Divider1()            HSPWMF_SetIC6Divider(0)
#define HSPWMF_IC6Divider2()            HSPWMF_SetIC6Divider(1)
#define HSPWMF_IC6Divider4()            HSPWMF_SetIC6Divider(2)
#define HSPWMF_IC6Divider8()            HSPWMF_SetIC6Divider(3)

#define PWMFCCMR3_OC7CE_MSK             BIT7
#define PWMF_EnableETRFClearOC7REF()    SET_REG_BIT(PWMF_CCMR3, PWMFCCMR3_OC7CE_MSK)
#define PWMF_DisableETRFClearOC7REF()   CLR_REG_BIT(PWMF_CCMR3, PWMFCCMR3_OC7CE_MSK)

#define HSPWMF_EnableETRFClearOC7REF()  SET_HSPWMF_BIT(PWMF_CCMR3, PWMFCCMR3_OC7CE_MSK)
#define HSPWMF_DisableETRFClearOC7REF() CLR_HSPWMF_BIT(PWMF_CCMR3, PWMFCCMR3_OC7CE_MSK)

#define PWMFCCMR3_OC7M_MSK              (BIT6 | BIT5 | BIT4)
#define PWMF_SetOC7OutputMode(n)        MODIFY_REG(PWMF_CCMR3,  PWMFCCMR3_OC7M_MSK, ((n) << 4))
#define PWMF_OC7REFFrozen()             PWMF_SetOC7OutputMode(0)
#define PWMF_OC7REFHighIfMatch()        PWMF_SetOC7OutputMode(1)
#define PWMF_OC7REFLowIfMatch()         PWMF_SetOC7OutputMode(2)
#define PWMF_OC7REFToggleIfMatch()      PWMF_SetOC7OutputMode(3)
#define PWMF_OC7REFForceLow()           PWMF_SetOC7OutputMode(4)
#define PWMF_OC7REFForceHigh()          PWMF_SetOC7OutputMode(5)
#define PWMF_OC7REFPWMMode1()           PWMF_SetOC7OutputMode(6)
#define PWMF_OC7REFPWMMode2()           PWMF_SetOC7OutputMode(7)

#define HSPWMF_SetOC7OutputMode(n)      MODIFY_HSPWMF(PWMF_CCMR3,  PWMFCCMR3_OC7M_MSK, ((n) << 4))
#define HSPWMF_OC7REFFrozen()           HSPWMF_SetOC7OutputMode(0)
#define HSPWMF_OC7REFHighIfMatch()      HSPWMF_SetOC7OutputMode(1)
#define HSPWMF_OC7REFLowIfMatch()       HSPWMF_SetOC7OutputMode(2)
#define HSPWMF_OC7REFToggleIfMatch()    HSPWMF_SetOC7OutputMode(3)
#define HSPWMF_OC7REFForceLow()         HSPWMF_SetOC7OutputMode(4)
#define HSPWMF_OC7REFForceHigh()        HSPWMF_SetOC7OutputMode(5)
#define HSPWMF_OC7REFPWMMode1()         HSPWMF_SetOC7OutputMode(6)
#define HSPWMF_OC7REFPWMMode2()         HSPWMF_SetOC7OutputMode(7)

#define PWMFCCMR3_OC7PE_MSK             BIT3
#define PWMF_UnbufferCCR7()             CLR_REG_BIT(PWMF_CCMR3, PWMFCCMR3_OC7PE_MSK)
#define PWMF_BufferCCR7()               SET_REG_BIT(PWMF_CCMR3, PWMFCCMR3_OC7PE_MSK)

#define HSPWMF_UnbufferCCR7()           CLR_HSPWMF_BIT(PWMF_CCMR3, PWMFCCMR3_OC7PE_MSK)
#define HSPWMF_BufferCCR7()             SET_HSPWMF_BIT(PWMF_CCMR3, PWMFCCMR3_OC7PE_MSK)

#define PWMFCCMR3_OC7FE_MSK             BIT2
#define PWMF_DisableOC7FastMode()       CLR_REG_BIT(PWMF_CCMR3, PWMFCCMR3_OC7FE_MSK)
#define PWMF_EnableOC7FastMode()        SET_REG_BIT(PWMF_CCMR3, PWMFCCMR3_OC7FE_MSK)

#define HSPWMF_DisableOC7FastMode()     CLR_HSPWMF_BIT(PWMF_CCMR3, PWMFCCMR3_OC7FE_MSK)
#define HSPWMF_EnableOC7FastMode()      SET_HSPWMF_BIT(PWMF_CCMR3, PWMFCCMR3_OC7FE_MSK)

#define PWMFCCMR3_CC7S_MSK              (BIT1 | BIT0)
#define PWMF_SetCC7Mode(n)              MODIFY_REG(PWMF_CCMR3,  PWMFCCMR3_CC7S_MSK, ((n) << 0))
#define PWMF_CC7Output()                PWMF_SetCC7Mode(0)
#define PWMF_CC7CaptureTI7FP7()         PWMF_SetCC7Mode(1)
#define PWMF_CC7CaptureTI8FP7()         PWMF_SetCC7Mode(2)
#define PWMF_CC7CaptureTRC()            PWMF_SetCC7Mode(3)

#define HSPWMF_SetCC7Mode(n)            MODIFY_HSPWMF(PWMF_CCMR3,  PWMFCCMR3_CC7S_MSK, ((n) << 0))
#define HSPWMF_CC7Output()              HSPWMF_SetCC7Mode(0)
#define HSPWMF_CC7CaptureTI7FP7()       HSPWMF_SetCC7Mode(1)
#define HSPWMF_CC7CaptureTI8FP7()       HSPWMF_SetCC7Mode(2)
#define HSPWMF_CC7CaptureTRC()          HSPWMF_SetCC7Mode(3)

#define PWMFCCMR3_IC7F_MSK              (BIT_HN)
#define PWMF_SetIC7Filter(n)            MODIFY_REG(PWMF_CCMR3,  PWMFCCMR3_IC7F_MSK, ((n) << 4))
#define PWMF_IC7Filter1()               PWMF_SetIC7Filter(0)
#define PWMF_IC7Filter2()               PWMF_SetIC7Filter(1)
#define PWMF_IC7Filter4()               PWMF_SetIC7Filter(2)
#define PWMF_IC7Filter8()               PWMF_SetIC7Filter(3)
#define PWMF_IC7Filter12()              PWMF_SetIC7Filter(4)
#define PWMF_IC7Filter16()              PWMF_SetIC7Filter(5)
#define PWMF_IC7Filter24()              PWMF_SetIC7Filter(6)
#define PWMF_IC7Filter32()              PWMF_SetIC7Filter(7)
#define PWMF_IC7Filter48()              PWMF_SetIC7Filter(8)
#define PWMF_IC7Filter64()              PWMF_SetIC7Filter(9)
#define PWMF_IC7Filter80()              PWMF_SetIC7Filter(10)
#define PWMF_IC7Filter96()              PWMF_SetIC7Filter(11)
#define PWMF_IC7Filter128()             PWMF_SetIC7Filter(12)
#define PWMF_IC7Filter160()             PWMF_SetIC7Filter(13)
#define PWMF_IC7Filter192()             PWMF_SetIC7Filter(14)
#define PWMF_IC7Filter256()             PWMF_SetIC7Filter(15)

#define HSPWMF_SetIC7Filter(n)          MODIFY_HSPWMF(PWMF_CCMR3,  PWMFCCMR3_IC7F_MSK, ((n) << 4))
#define HSPWMF_IC7Filter1()             HSPWMF_SetIC7Filter(0)
#define HSPWMF_IC7Filter2()             HSPWMF_SetIC7Filter(1)
#define HSPWMF_IC7Filter4()             HSPWMF_SetIC7Filter(2)
#define HSPWMF_IC7Filter8()             HSPWMF_SetIC7Filter(3)
#define HSPWMF_IC7Filter12()            HSPWMF_SetIC7Filter(4)
#define HSPWMF_IC7Filter16()            HSPWMF_SetIC7Filter(5)
#define HSPWMF_IC7Filter24()            HSPWMF_SetIC7Filter(6)
#define HSPWMF_IC7Filter32()            HSPWMF_SetIC7Filter(7)
#define HSPWMF_IC7Filter48()            HSPWMF_SetIC7Filter(8)
#define HSPWMF_IC7Filter64()            HSPWMF_SetIC7Filter(9)
#define HSPWMF_IC7Filter80()            HSPWMF_SetIC7Filter(10)
#define HSPWMF_IC7Filter96()            HSPWMF_SetIC7Filter(11)
#define HSPWMF_IC7Filter128()           HSPWMF_SetIC7Filter(12)
#define HSPWMF_IC7Filter160()           HSPWMF_SetIC7Filter(13)
#define HSPWMF_IC7Filter192()           HSPWMF_SetIC7Filter(14)
#define HSPWMF_IC7Filter256()           HSPWMF_SetIC7Filter(15)

#define PWMFCCMR3_IC7PS_MSK             (BIT3 | BIT2)
#define PWMF_SetIC7Divider(n)           MODIFY_REG(PWMF_CCMR3,  PWMFCCMR3_IC7PS_MSK, ((n) << 2))
#define PWMF_IC7Divider1()              PWMF_SetIC7Divider(0)
#define PWMF_IC7Divider2()              PWMF_SetIC7Divider(1)
#define PWMF_IC7Divider4()              PWMF_SetIC7Divider(2)
#define PWMF_IC7Divider8()              PWMF_SetIC7Divider(3)

#define HSPWMF_SetIC7Divider(n)         MODIFY_HSPWMF(PWMF_CCMR3,  PWMFCCMR3_IC7PS_MSK, ((n) << 2))
#define HSPWMF_IC7Divider1()            HSPWMF_SetIC7Divider(0)
#define HSPWMF_IC7Divider2()            HSPWMF_SetIC7Divider(1)
#define HSPWMF_IC7Divider4()            HSPWMF_SetIC7Divider(2)
#define HSPWMF_IC7Divider8()            HSPWMF_SetIC7Divider(3)

#define PWMFCCMR4_OC8CE_MSK             BIT7
#define PWMF_EnableETRFClearOC8REF()    SET_REG_BIT(PWMF_CCMR4, PWMFCCMR4_OC8CE_MSK)
#define PWMF_DisableETRFClearOC8REF()   CLR_REG_BIT(PWMF_CCMR4, PWMFCCMR4_OC8CE_MSK)

#define HSPWMF_EnableETRFClearOC8REF()  SET_HSPWMF_BIT(PWMF_CCMR4, PWMFCCMR4_OC8CE_MSK)
#define HSPWMF_DisableETRFClearOC8REF() CLR_HSPWMF_BIT(PWMF_CCMR4, PWMFCCMR4_OC8CE_MSK)

#define PWMFCCMR4_OC8M_MSK              (BIT6 | BIT5 | BIT4)
#define PWMF_SetOC8OutputMode(n)        MODIFY_REG(PWMF_CCMR4,  PWMFCCMR4_OC8M_MSK, ((n) << 4))
#define PWMF_OC8REFFrozen()             PWMF_SetOC8OutputMode(0)
#define PWMF_OC8REFHighIfMatch()        PWMF_SetOC8OutputMode(1)
#define PWMF_OC8REFLowIfMatch()         PWMF_SetOC8OutputMode(2)
#define PWMF_OC8REFToggleIfMatch()      PWMF_SetOC8OutputMode(3)
#define PWMF_OC8REFForceLow()           PWMF_SetOC8OutputMode(4)
#define PWMF_OC8REFForceHigh()          PWMF_SetOC8OutputMode(5)
#define PWMF_OC8REFPWMMode1()           PWMF_SetOC8OutputMode(6)
#define PWMF_OC8REFPWMMode2()           PWMF_SetOC8OutputMode(7)

#define HSPWMF_SetOC8OutputMode(n)      MODIFY_HSPWMF(PWMF_CCMR4,  PWMFCCMR4_OC8M_MSK, ((n) << 4))
#define HSPWMF_OC8REFFrozen()           HSPWMF_SetOC8OutputMode(0)
#define HSPWMF_OC8REFHighIfMatch()      HSPWMF_SetOC8OutputMode(1)
#define HSPWMF_OC8REFLowIfMatch()       HSPWMF_SetOC8OutputMode(2)
#define HSPWMF_OC8REFToggleIfMatch()    HSPWMF_SetOC8OutputMode(3)
#define HSPWMF_OC8REFForceLow()         HSPWMF_SetOC8OutputMode(4)
#define HSPWMF_OC8REFForceHigh()        HSPWMF_SetOC8OutputMode(5)
#define HSPWMF_OC8REFPWMMode1()         HSPWMF_SetOC8OutputMode(6)
#define HSPWMF_OC8REFPWMMode2()         HSPWMF_SetOC8OutputMode(7)

#define PWMFCCMR4_OC8PE_MSK             BIT3
#define PWMF_UnbufferCCR8()             CLR_REG_BIT(PWMF_CCMR4, PWMFCCMR4_OC8PE_MSK)
#define PWMF_BufferCCR8()               SET_REG_BIT(PWMF_CCMR4, PWMFCCMR4_OC8PE_MSK)

#define HSPWMF_UnbufferCCR8()           CLR_HSPWMF_BIT(PWMF_CCMR4, PWMFCCMR4_OC8PE_MSK)
#define HSPWMF_BufferCCR8()             SET_HSPWMF_BIT(PWMF_CCMR4, PWMFCCMR4_OC8PE_MSK)

#define PWMFCCMR4_OC8FE_MSK             BIT2
#define PWMF_DisableOC8FastMode()       CLR_REG_BIT(PWMF_CCMR4, PWMFCCMR4_OC8FE_MSK)
#define PWMF_EnableOC8FastMode()        SET_REG_BIT(PWMF_CCMR4, PWMFCCMR4_OC8FE_MSK)

#define HSPWMF_DisableOC8FastMode()     CLR_HSPWMF_BIT(PWMF_CCMR4, PWMFCCMR4_OC8FE_MSK)
#define HSPWMF_EnableOC8FastMode()      SET_HSPWMF_BIT(PWMF_CCMR4, PWMFCCMR4_OC8FE_MSK)

#define PWMFCCMR4_CC8S_MSK              (BIT1 | BIT0)
#define PWMF_SetCC8Mode(n)              MODIFY_REG(PWMF_CCMR4,  PWMFCCMR4_CC8S_MSK, ((n) << 0))
#define PWMF_CC8Output()                PWMF_SetCC8Mode(0)
#define PWMF_CC8CaptureTI8FP8()         PWMF_SetCC8Mode(1)
#define PWMF_CC8CaptureTI7FP8()         PWMF_SetCC8Mode(2)
#define PWMF_CC8CaptureTRC()            PWMF_SetCC8Mode(3)

#define HSPWMF_SetCC8Mode(n)            MODIFY_HSPWMF(PWMF_CCMR4,  PWMFCCMR4_CC8S_MSK, ((n) << 0))
#define HSPWMF_CC8Output()              HSPWMF_SetCC8Mode(0)
#define HSPWMF_CC8CaptureTI8FP8()       HSPWMF_SetCC8Mode(1)
#define HSPWMF_CC8CaptureTI7FP8()       HSPWMF_SetCC8Mode(2)
#define HSPWMF_CC8CaptureTRC()          HSPWMF_SetCC8Mode(3)

#define PWMFCCMR4_IC8F_MSK              (BIT_HN)
#define PWMF_SetIC8Filter(n)            MODIFY_REG(PWMF_CCMR4,  PWMFCCMR4_IC8F_MSK, ((n) << 4))
#define PWMF_IC8Filter1()               PWMF_SetIC8Filter(0)
#define PWMF_IC8Filter2()               PWMF_SetIC8Filter(1)
#define PWMF_IC8Filter4()               PWMF_SetIC8Filter(2)
#define PWMF_IC8Filter8()               PWMF_SetIC8Filter(3)
#define PWMF_IC8Filter12()              PWMF_SetIC8Filter(4)
#define PWMF_IC8Filter16()              PWMF_SetIC8Filter(5)
#define PWMF_IC8Filter24()              PWMF_SetIC8Filter(6)
#define PWMF_IC8Filter32()              PWMF_SetIC8Filter(7)
#define PWMF_IC8Filter48()              PWMF_SetIC8Filter(8)
#define PWMF_IC8Filter64()              PWMF_SetIC8Filter(9)
#define PWMF_IC8Filter80()              PWMF_SetIC8Filter(10)
#define PWMF_IC8Filter96()              PWMF_SetIC8Filter(11)
#define PWMF_IC8Filter128()             PWMF_SetIC8Filter(12)
#define PWMF_IC8Filter160()             PWMF_SetIC8Filter(13)
#define PWMF_IC8Filter192()             PWMF_SetIC8Filter(14)
#define PWMF_IC8Filter256()             PWMF_SetIC8Filter(15)

#define HSPWMF_SetIC8Filter(n)          MODIFY_HSPWMF(PWMF_CCMR4,  PWMFCCMR4_IC8F_MSK, ((n) << 4))
#define HSPWMF_IC8Filter1()             HSPWMF_SetIC8Filter(0)
#define HSPWMF_IC8Filter2()             HSPWMF_SetIC8Filter(1)
#define HSPWMF_IC8Filter4()             HSPWMF_SetIC8Filter(2)
#define HSPWMF_IC8Filter8()             HSPWMF_SetIC8Filter(3)
#define HSPWMF_IC8Filter12()            HSPWMF_SetIC8Filter(4)
#define HSPWMF_IC8Filter16()            HSPWMF_SetIC8Filter(5)
#define HSPWMF_IC8Filter24()            HSPWMF_SetIC8Filter(6)
#define HSPWMF_IC8Filter32()            HSPWMF_SetIC8Filter(7)
#define HSPWMF_IC8Filter48()            HSPWMF_SetIC8Filter(8)
#define HSPWMF_IC8Filter64()            HSPWMF_SetIC8Filter(9)
#define HSPWMF_IC8Filter80()            HSPWMF_SetIC8Filter(10)
#define HSPWMF_IC8Filter96()            HSPWMF_SetIC8Filter(11)
#define HSPWMF_IC8Filter128()           HSPWMF_SetIC8Filter(12)
#define HSPWMF_IC8Filter160()           HSPWMF_SetIC8Filter(13)
#define HSPWMF_IC8Filter192()           HSPWMF_SetIC8Filter(14)
#define HSPWMF_IC8Filter256()           HSPWMF_SetIC8Filter(15)

#define PWMFCCMR4_IC8PS_MSK             (BIT3 | BIT2)
#define PWMF_SetIC8Divider(n)           MODIFY_REG(PWMF_CCMR4,  PWMFCCMR4_IC8PS_MSK, ((n) << 2))
#define PWMF_IC8Divider1()              PWMF_SetIC8Divider(0)
#define PWMF_IC8Divider2()              PWMF_SetIC8Divider(1)
#define PWMF_IC8Divider4()              PWMF_SetIC8Divider(2)
#define PWMF_IC8Divider8()              PWMF_SetIC8Divider(3)

#define HSPWMF_SetIC8Divider(n)         MODIFY_HSPWMF(PWMF_CCMR4,  PWMFCCMR4_IC8PS_MSK, ((n) << 2))
#define HSPWMF_IC8Divider1()            HSPWMF_SetIC8Divider(0)
#define HSPWMF_IC8Divider2()            HSPWMF_SetIC8Divider(1)
#define HSPWMF_IC8Divider4()            HSPWMF_SetIC8Divider(2)
#define HSPWMF_IC8Divider8()            HSPWMF_SetIC8Divider(3)

#define PWMFCCER1_CC5E_MSK              BIT0
#define PWMF_CC5PEnable()               SET_REG_BIT(PWMF_CCER1, PWMFCCER1_CC5E_MSK)
#define PWMF_CC5PDisable()              CLR_REG_BIT(PWMF_CCER1, PWMFCCER1_CC5E_MSK)

#define HSPWMF_CC5PEnable()             SET_HSPWMF_BIT(PWMF_CCER1, PWMFCCER1_CC5E_MSK)
#define HSPWMF_CC5PDisable()            CLR_HSPWMF_BIT(PWMF_CCER1, PWMFCCER1_CC5E_MSK)

#define PWMFCCER1_CC5P_MSK              BIT1
#define PWMF_CC5PNonInverted()          CLR_REG_BIT(PWMF_CCER1, PWMFCCER1_CC5P_MSK)
#define PWMF_CC5PInverted()             SET_REG_BIT(PWMF_CCER1, PWMFCCER1_CC5P_MSK)

#define HSPWMF_CC5PNonInverted()        CLR_HSPWMF_BIT(PWMF_CCER1, PWMFCCER1_CC5P_MSK)
#define HSPWMF_CC5PInverted()           SET_HSPWMF_BIT(PWMF_CCER1, PWMFCCER1_CC5P_MSK)

#define PWMFCCER1_CC6E_MSK              BIT4
#define PWMF_CC6PEnable()               SET_REG_BIT(PWMF_CCER1, PWMFCCER1_CC6E_MSK)
#define PWMF_CC6PDisable()              CLR_REG_BIT(PWMF_CCER1, PWMFCCER1_CC6E_MSK)

#define HSPWMF_CC6PEnable()             SET_HSPWMF_BIT(PWMF_CCER1, PWMFCCER1_CC6E_MSK)
#define HSPWMF_CC6PDisable()            CLR_HSPWMF_BIT(PWMF_CCER1, PWMFCCER1_CC6E_MSK)

#define PWMFCCER1_CC6P_MSK              BIT5
#define PWMF_CC6PNonInverted()          CLR_REG_BIT(PWMF_CCER1, PWMFCCER1_CC6P_MSK)
#define PWMF_CC6PInverted()             SET_REG_BIT(PWMF_CCER1, PWMFCCER1_CC6P_MSK)

#define HSPWMF_CC6PNonInverted()        CLR_HSPWMF_BIT(PWMF_CCER1, PWMFCCER1_CC6P_MSK)
#define HSPWMF_CC6PInverted()           SET_HSPWMF_BIT(PWMF_CCER1, PWMFCCER1_CC6P_MSK)

#define PWMFCCER2_CC7E_MSK              BIT0
#define PWMF_CC7PEnable()               SET_REG_BIT(PWMF_CCER2, PWMFCCER2_CC7E_MSK)
#define PWMF_CC7PDisable()              CLR_REG_BIT(PWMF_CCER2, PWMFCCER2_CC7E_MSK)

#define HSPWMF_CC7PEnable()             SET_HSPWMF_BIT(PWMF_CCER2, PWMFCCER2_CC7E_MSK)
#define HSPWMF_CC7PDisable()            CLR_HSPWMF_BIT(PWMF_CCER2, PWMFCCER2_CC7E_MSK)

#define PWMFCCER2_CC7P_MSK              BIT1
#define PWMF_CC7PNonInverted()          CLR_REG_BIT(PWMF_CCER2, PWMFCCER2_CC7P_MSK)
#define PWMF_CC7PInverted()             SET_REG_BIT(PWMF_CCER2, PWMFCCER2_CC7P_MSK)

#define HSPWMF_CC7PNonInverted()        CLR_HSPWMF_BIT(PWMF_CCER2, PWMFCCER2_CC7P_MSK)
#define HSPWMF_CC7PInverted()           SET_HSPWMF_BIT(PWMF_CCER2, PWMFCCER2_CC7P_MSK)

#define PWMFCCER2_CC8E_MSK              BIT4
#define PWMF_CC8PEnable()               SET_REG_BIT(PWMF_CCER2, PWMFCCER2_CC8E_MSK)
#define PWMF_CC8PDisable()              CLR_REG_BIT(PWMF_CCER2, PWMFCCER2_CC8E_MSK)

#define HSPWMF_CC8PEnable()             SET_HSPWMF_BIT(PWMF_CCER2, PWMFCCER2_CC8E_MSK)
#define HSPWMF_CC8PDisable()            CLR_HSPWMF_BIT(PWMF_CCER2, PWMFCCER2_CC8E_MSK)

#define PWMFCCER2_CC8P_MSK              BIT5
#define PWMF_CC8PNonInverted()          CLR_REG_BIT(PWMF_CCER2, PWMFCCER2_CC8P_MSK)
#define PWMF_CC8PInverted()             SET_REG_BIT(PWMF_CCER2, PWMFCCER2_CC8P_MSK)

#define HSPWMF_CC8PNonInverted()        CLR_HSPWMF_BIT(PWMF_CCER2, PWMFCCER2_CC8P_MSK)
#define HSPWMF_CC8PInverted()           SET_HSPWMF_BIT(PWMF_CCER2, PWMFCCER2_CC8P_MSK)

#define PWMFBRK_MOE_MSK                 BIT7
#define PWMF_EnableMainOutput()         SET_REG_BIT(PWMF_BKR, PWMFBRK_MOE_MSK)
#define PWMF_DisableMainOutput()        CLR_REG_BIT(PWMF_BKR, PWMFBRK_MOE_MSK)

#define HSPWMF_EnableMainOutput()       SET_HSPWMF_BIT(PWMF_BKR, PWMFBRK_MOE_MSK)
#define HSPWMF_DisableMainOutput()      CLR_HSPWMF_BIT(PWMF_BKR, PWMFBRK_MOE_MSK)

#define PWMFBRK_AOE_MSK                 BIT6
#define PWMF_EnableAutoOutput()         SET_REG_BIT(PWMF_BKR, PWMFBRK_AOE_MSK)
#define PWMF_DisableAutoOutput()        CLR_REG_BIT(PWMF_BKR, PWMFBRK_AOE_MSK)

#define HSPWMF_EnableAutoOutput()       SET_HSPWMF_BIT(PWMF_BKR, PWMFBRK_AOE_MSK)
#define HSPWMF_DisableAutoOutput()      CLR_HSPWMF_BIT(PWMF_BKR, PWMFBRK_AOE_MSK)

#define PWMFBRK_BKP_MSK                 BIT5
#define PWMF_BRKNonInverted()           SET_REG_BIT(PWMF_BKR, PWMFBRK_BKP_MSK)
#define PWMF_BRKInverted()              CLR_REG_BIT(PWMF_BKR, PWMFBRK_BKP_MSK)

#define HSPWMF_BRKNonInverted()         SET_HSPWMF_BIT(PWMF_BKR, PWMFBRK_BKP_MSK)
#define HSPWMF_BRKInverted()            CLR_HSPWMF_BIT(PWMF_BKR, PWMFBRK_BKP_MSK)

#define PWMFBRK_BKE_MSK                 BIT4
#define PWMF_BRKEnable()                SET_REG_BIT(PWMF_BKR, PWMFBRK_BKE_MSK)
#define PWMF_BRKDisable()               CLR_REG_BIT(PWMF_BKR, PWMFBRK_BKE_MSK)

#define HSPWMF_BRKEnable()              SET_HSPWMF_BIT(PWMF_BKR, PWMFBRK_BKE_MSK)
#define HSPWMF_BRKDisable()             CLR_HSPWMF_BIT(PWMF_BKR, PWMFBRK_BKE_MSK)

#define PWMFBRK_OSSR_MSK                BIT3
#define PWMFBRK_OSSI_MSK                BIT2
#define PWMF_RunInactiveNoOutput()      CLR_REG_BIT(PWMF_BKR, PWMFBRK_OSSR_MSK)
#define PWMF_RunInactiveOutput()        SET_REG_BIT(PWMF_BKR, PWMFBRK_OSSR_MSK)
#define PWMF_IdleInactiveNoOutput()     CLR_REG_BIT(PWMF_BKR, PWMFBRK_OSSI_MSK)
#define PWMF_IdleInactiveOutput()       SET_REG_BIT(PWMF_BKR, PWMFBRK_OSSI_MSK)

#define HSPWMF_RunInactiveNoOutput()    CLR_HSPWMF_BIT(PWMF_BKR, PWMFBRK_OSSR_MSK)
#define HSPWMF_RunInactiveOutput()      SET_HSPWMF_BIT(PWMF_BKR, PWMFBRK_OSSR_MSK)
#define HSPWMF_IdleInactiveNoOutput()   CLR_HSPWMF_BIT(PWMF_BKR, PWMFBRK_OSSI_MSK)
#define HSPWMF_IdleInactiveOutput()     SET_HSPWMF_BIT(PWMF_BKR, PWMFBRK_OSSI_MSK)

#define PWMFBRK_LOCK_MSK                (BIT1 | BIT0)
#define PWMF_SetLockLevel(n)            MODIFY_REG(PWMF_BKR,  PWMFBRK_LOCK_MSK, ((n) << 0))
#define PWMF_SetUnLock()                PWMF_SetLockLevel(0)

#define HSPWMF_SetLockLevel(n)          MODIFY_HSPWMF(PWMF_BKR,  PWMFBRK_LOCK_MSK, ((n) << 0))
#define HSPWMF_SetUnLock()              HSPWMF_SetLockLevel(0)

#define PWMFOISR_OIS5_MSK               BIT0
#define PWMFOISR_OIS6_MSK               BIT2
#define PWMFOISR_OIS7_MSK               BIT4
#define PWMFOISR_OIS8_MSK               BIT6
#define PWMF_OC5PIdleLevelLow()         CLR_REG_BIT(PWMF_OISR, PWMFOISR_OIS5_MSK)
#define PWMF_OC5PIdleLevelHigh()        SET_REG_BIT(PWMF_OISR, PWMFOISR_OIS5_MSK)
#define PWMF_OC6PIdleLevelLow()         CLR_REG_BIT(PWMF_OISR, PWMFOISR_OIS6_MSK)
#define PWMF_OC6PIdleLevelHigh()        SET_REG_BIT(PWMF_OISR, PWMFOISR_OIS6_MSK)
#define PWMF_OC7PIdleLevelLow()         CLR_REG_BIT(PWMF_OISR, PWMFOISR_OIS7_MSK)
#define PWMF_OC7PIdleLevelHigh()        SET_REG_BIT(PWMF_OISR, PWMFOISR_OIS7_MSK)
#define PWMF_OC8PIdleLevelLow()         CLR_REG_BIT(PWMF_OISR, PWMFOISR_OIS8_MSK)
#define PWMF_OC8PIdleLevelHigh()        SET_REG_BIT(PWMF_OISR, PWMFOISR_OIS8_MSK)

#define HSPWMF_OC5PIdleLevelLow()       CLR_HSPWMF_BIT(PWMF_OISR, PWMFOISR_OIS5_MSK)
#define HSPWMF_OC5PIdleLevelHigh()      SET_HSPWMF_BIT(PWMF_OISR, PWMFOISR_OIS5_MSK)
#define HSPWMF_OC6PIdleLevelLow()       CLR_HSPWMF_BIT(PWMF_OISR, PWMFOISR_OIS6_MSK)
#define HSPWMF_OC6PIdleLevelHigh()      SET_HSPWMF_BIT(PWMF_OISR, PWMFOISR_OIS6_MSK)
#define HSPWMF_OC7PIdleLevelLow()       CLR_HSPWMF_BIT(PWMF_OISR, PWMFOISR_OIS7_MSK)
#define HSPWMF_OC7PIdleLevelHigh()      SET_HSPWMF_BIT(PWMF_OISR, PWMFOISR_OIS7_MSK)
#define HSPWMF_OC8PIdleLevelLow()       CLR_HSPWMF_BIT(PWMF_OISR, PWMFOISR_OIS8_MSK)
#define HSPWMF_OC8PIdleLevelHigh()      SET_HSPWMF_BIT(PWMF_OISR, PWMFOISR_OIS8_MSK)

#define PWMF_SetCounter(n)              (PWMF_CNTRH = HIBYTE(n), PWMF_CNTRL = LOBYTE(n))
#define PWMF_SetClockDivider(n)         (PWMF_PSCRH = HIBYTE(n), PWMF_PSCRL = LOBYTE(n))
#define PWMF_SetReload16(n)             (PWMF_ARRH = HIBYTE(n), PWMF_ARRL = LOBYTE(n))
#define PWMF_SetRepeatCounter(n)        (PWMF_RCRH = HIBYTE(n), PWMF_RCR = LOBYTE(n))

#define HSPWMF_SetCounter(n)            (WRITE_HSPWMF(PWMF_CNTRH, HIBYTE(n)), WRITE_HSPWMF(PWMF_CNTRL, LOBYTE(n)))
#define HSPWMF_SetClockDivider(n)       (WRITE_HSPWMF(PWMF_PSCRH, HIBYTE(n)), WRITE_HSPWMF(PWMF_PSCRL, LOBYTE(n)))
#define HSPWMF_SetReload16(n)           (WRITE_HSPWMF(PWMF_ARRH, HIBYTE(n)), WRITE_HSPWMF(PWMF_ARRL, LOBYTE(n)))
#define HSPWMF_SetRepeatCounter(n)      (WRITE_HSPWMF(PWMF_RCRH, HIBYTE(n)), WRITE_HSPWMF(PWMF_RCR, LOBYTE(n)))

#define PWMF_SetCCR5Value(n)            (PWMF_CCR5H = HIBYTE(n), PWMF_CCR5L = LOBYTE(n))
#define PWMF_SetCCR6Value(n)            (PWMF_CCR6H = HIBYTE(n), PWMF_CCR6L = LOBYTE(n))
#define PWMF_SetCCR7Value(n)            (PWMF_CCR7H = HIBYTE(n), PWMF_CCR7L = LOBYTE(n))
#define PWMF_SetCCR8Value(n)            (PWMF_CCR8H = HIBYTE(n), PWMF_CCR8L = LOBYTE(n))

#define HSPWMF_SetCCR5Value(n)          (WRITE_HSPWMF(PWMF_CCR5H, HIBYTE(n)), WRITE_HSPWMF(PWMF_CCR5L, LOBYTE(n)))
#define HSPWMF_SetCCR6Value(n)          (WRITE_HSPWMF(PWMF_CCR6H, HIBYTE(n)), WRITE_HSPWMF(PWMF_CCR6L, LOBYTE(n)))
#define HSPWMF_SetCCR7Value(n)          (WRITE_HSPWMF(PWMF_CCR7H, HIBYTE(n)), WRITE_HSPWMF(PWMF_CCR7L, LOBYTE(n)))
#define HSPWMF_SetCCR8Value(n)          (WRITE_HSPWMF(PWMF_CCR8H, HIBYTE(n)), WRITE_HSPWMF(PWMF_CCR8L, LOBYTE(n)))

#define PWMF_ReadReload16()             MAKEWORD(PWMF_ARRL, PWMF_ARRH)

#define HSPWMF_ReadReload16()           MAKEWORD(READ_HSPWMF(PWMF_ARRL), READ_HSPWMF(PWMF_ARRH))

#define PWMF_ReadCCR5Value()            MAKEWORD(PWMF_CCR5L, PWMF_CCR5H)
#define PWMF_ReadCCR6Value()            MAKEWORD(PWMF_CCR6L, PWMF_CCR6H)
#define PWMF_ReadCCR7Value()            MAKEWORD(PWMF_CCR7L, PWMF_CCR7H)
#define PWMF_ReadCCR8Value()            MAKEWORD(PWMF_CCR8L, PWMF_CCR8H)

#define HSPWMF_ReadCCR5Value()          MAKEWORD(READ_HSPWMF(PWMF_CCR5L), READ_HSPWMF(PWMF_CCR5H))
#define HSPWMF_ReadCCR6Value()          MAKEWORD(READ_HSPWMF(PWMF_CCR6L), READ_HSPWMF(PWMF_CCR6H))
#define HSPWMF_ReadCCR7Value()          MAKEWORD(READ_HSPWMF(PWMF_CCR7L), READ_HSPWMF(PWMF_CCR7H))
#define HSPWMF_ReadCCR8Value()          MAKEWORD(READ_HSPWMF(PWMF_CCR8L), READ_HSPWMF(PWMF_CCR8H))

#define PWMF_SetDeadTime(n)             PWMF_DTR = LOBYTE(n)

#define HSPWMF_SetDeadTime(n)           WRITE_HSPWMF(PWMF_DTR, LOBYTE(n))

/////////////////////////////////////////////////

#define READ_HSPWMA(r)                  HSPWMA_ReadReg(BYTE0(&r) & 0x7f)
#define WRITE_HSPWMA(r, d)              HSPWMA_WriteReg((BYTE0(&r) & 0x7f), BYTE0(d))
#define MODIFY_HSPWMA(r, clr, set)      WRITE_HSPWMA((r), ((READ_HSPWMA(r) & ~(clr)) | ((set) & (clr))))
#define READ_HSPWMA_BIT(r, b)           (READ_HSPWMA(r) & (b))
#define CLR_HSPWMA_BIT(r, b)            WRITE_HSPWMA((r), (READ_HSPWMA(r) & ~(b)))
#define SET_HSPWMA_BIT(r, b)            WRITE_HSPWMA((r), (READ_HSPWMA(r) | (b)))

#define READ_HSPWMB(r)                  HSPWMB_ReadReg(BYTE0(&r) & 0x7f)
#define WRITE_HSPWMB(r, d)              HSPWMB_WriteReg((BYTE0(&r) & 0x7f), BYTE0(d))
#define MODIFY_HSPWMB(r, clr, set)      WRITE_HSPWMB((r), ((READ_HSPWMB(r) & ~(clr)) | ((set) & (clr))))
#define READ_HSPWMB_BIT(r, b)           (READ_HSPWMB(r) & (b))
#define CLR_HSPWMB_BIT(r, b)            WRITE_HSPWMB((r), (READ_HSPWMB(r) & ~(b)))
#define SET_HSPWMB_BIT(r, b)            WRITE_HSPWMB((r), (READ_HSPWMB(r) | (b)))

#define READ_HSPWMC(r)                  HSPWMC_ReadReg(BYTE0(&r) & 0x7f)
#define WRITE_HSPWMC(r, d)              HSPWMC_WriteReg((BYTE0(&r) & 0x7f), BYTE0(d))
#define MODIFY_HSPWMC(r, clr, set)      WRITE_HSPWMC((r), ((READ_HSPWMC(r) & ~(clr)) | ((set) & (clr))))
#define READ_HSPWMC_BIT(r, b)           (READ_HSPWMC(r) & (b))
#define CLR_HSPWMC_BIT(r, b)            WRITE_HSPWMC((r), (READ_HSPWMC(r) & ~(b)))
#define SET_HSPWMC_BIT(r, b)            WRITE_HSPWMC((r), (READ_HSPWMC(r) | (b)))

#define READ_HSPWMD(r)                  HSPWMD_ReadReg(BYTE0(&r) & 0x7f)
#define WRITE_HSPWMD(r, d)              HSPWMD_WriteReg((BYTE0(&r) & 0x7f), BYTE0(d))
#define MODIFY_HSPWMD(r, clr, set)      WRITE_HSPWMD((r), ((READ_HSPWMD(r) & ~(clr)) | ((set) & (clr))))
#define READ_HSPWMD_BIT(r, b)           (READ_HSPWMD(r) & (b))
#define CLR_HSPWMD_BIT(r, b)            WRITE_HSPWMD((r), (READ_HSPWMD(r) & ~(b)))
#define SET_HSPWMD_BIT(r, b)            WRITE_HSPWMD((r), (READ_HSPWMD(r) | (b)))

#define READ_HSPWME(r)                  HSPWME_ReadReg(BYTE0(&r) & 0x7f)
#define WRITE_HSPWME(r, d)              HSPWME_WriteReg((BYTE0(&r) & 0x7f), BYTE0(d))
#define MODIFY_HSPWME(r, clr, set)      WRITE_HSPWME((r), ((READ_HSPWME(r) & ~(clr)) | ((set) & (clr))))
#define READ_HSPWME_BIT(r, b)           (READ_HSPWME(r) & (b))
#define CLR_HSPWME_BIT(r, b)            WRITE_HSPWME((r), (READ_HSPWME(r) & ~(b)))
#define SET_HSPWME_BIT(r, b)            WRITE_HSPWME((r), (READ_HSPWME(r) | (b)))

#define READ_HSPWMF(r)                  HSPWMF_ReadReg(BYTE0(&r) & 0x7f)
#define WRITE_HSPWMF(r, d)              HSPWMF_WriteReg((BYTE0(&r) & 0x7f), BYTE0(d))
#define MODIFY_HSPWMF(r, clr, set)      WRITE_HSPWMF((r), ((READ_HSPWMF(r) & ~(clr)) | ((set) & (clr))))
#define READ_HSPWMF_BIT(r, b)           (READ_HSPWMF(r) & (b))
#define CLR_HSPWMF_BIT(r, b)            WRITE_HSPWMF((r), (READ_HSPWMF(r) & ~(b)))
#define SET_HSPWMF_BIT(r, b)            WRITE_HSPWMF((r), (READ_HSPWMF(r) | (b)))

////////////////////////

#define HSPWMACFG_ASYNCEN_MSK           (BIT1 | BIT0)
#define HSPWMA_Enable()                 MODIFY_REG(HSPWMA_CFG, HSPWMACFG_ASYNCEN_MSK, ((3) << 0))
#define HSPWMA_Disable()                MODIFY_REG(HSPWMA_CFG, HSPWMACFG_ASYNCEN_MSK, ((0) << 0))

#define HSPWMACFG_INTEN_MSK             BIT2
#define HSPWMA_EnableInt()              SET_REG_BIT(HSPWMA_CFG, HSPWMACFG_INTEN_MSK)
#define HSPWMA_DisableInt()             CLR_REG_BIT(HSPWMA_CFG, HSPWMACFG_INTEN_MSK)

#define HSPWMACFG_EXTN_MSK              BIT3
#define HSPWMA_SelectBankFE80H()        CLR_REG_BIT(HSPWMA_CFG, HSPWMACFG_EXTN_MSK)
#define HSPWMA_SelectBankF900H()        SET_REG_BIT(HSPWMA_CFG, HSPWMACFG_EXTN_MSK)

#define HSPWMAADR_BUSY_MSK              BIT7
#define HSPWMA_CheckBusy()              READ_REG_BIT(HSPWMA_ADR, HSPWMAADR_BUSY_MSK)

#define HSPWMAADR_READ_MSK              BIT7
#define HSPWMA_AsyncRead(r, d)          HSPWMA_ADR = ((r) | HSPWMAADR_READ_MSK);    \
                                        while (HSPWMA_CheckBusy());                 \
                                        (d) = HSPWMA_DAT

#define HSPWMA_AsyncWrite(r, d)         HSPWMA_DAT = (d);                           \
                                        HSPWMA_ADR = ((r) & ~HSPWMAADR_READ_MSK)

////////////////////////

#define HSPWMBCFG_ASYNCEN_MSK           (BIT1 | BIT0)
#define HSPWMB_Enable()                 MODIFY_REG(HSPWMB_CFG, HSPWMBCFG_ASYNCEN_MSK, ((3) << 0))
#define HSPWMB_Disable()                MODIFY_REG(HSPWMB_CFG, HSPWMBCFG_ASYNCEN_MSK, ((0) << 0))

#define HSPWMBCFG_INTEN_MSK             BIT2
#define HSPWMB_EnableInt()              SET_REG_BIT(HSPWMB_CFG, HSPWMBCFG_INTEN_MSK)
#define HSPWMB_DisableInt()             CLR_REG_BIT(HSPWMB_CFG, HSPWMBCFG_INTEN_MSK)

#define HSPWMBCFG_EXTN_MSK              BIT3
#define HSPWMB_SelectBankFE80H()        CLR_REG_BIT(HSPWMB_CFG, HSPWMBCFG_EXTN_MSK)
#define HSPWMB_SelectBankF900H()        SET_REG_BIT(HSPWMB_CFG, HSPWMBCFG_EXTN_MSK)

#define HSPWMBADR_BUSY_MSK              BIT7
#define HSPWMB_CheckBusy()              READ_REG_BIT(HSPWMB_ADR, HSPWMBADR_BUSY_MSK)

#define HSPWMBADR_READ_MSK              BIT7
#define HSPWMB_AsyncRead(r, d)          HSPWMB_ADR = ((r) | HSPWMBADR_READ_MSK);    \
                                        while (HSPWMB_CheckBusy());                 \
                                        (d) = HSPWMB_DAT

#define HSPWMB_AsyncWrite(r, d)         HSPWMB_DAT = (d);                           \
                                        HSPWMB_ADR = ((r) & ~HSPWMBADR_READ_MSK)

////////////////////////

#define HSPWMCCFG_ASYNCEN_MSK           (BIT1 | BIT0)
#define HSPWMC_Enable()                 MODIFY_REG(HSPWMC_CFG, HSPWMCCFG_ASYNCEN_MSK, ((3) << 0))
#define HSPWMC_Disable()                MODIFY_REG(HSPWMC_CFG, HSPWMCCFG_ASYNCEN_MSK, ((0) << 0))

#define HSPWMCCFG_INTEN_MSK             BIT2
#define HSPWMC_EnableInt()              SET_REG_BIT(HSPWMC_CFG, HSPWMCCFG_INTEN_MSK)
#define HSPWMC_DisableInt()             CLR_REG_BIT(HSPWMC_CFG, HSPWMCCFG_INTEN_MSK)

#define HSPWMCCFG_EXTN_MSK              BIT3
#define HSPWMC_SelectBankFE80H()        CLR_REG_BIT(HSPWMC_CFG, HSPWMCCFG_EXTN_MSK)
#define HSPWMC_SelectBankF900H()        SET_REG_BIT(HSPWMC_CFG, HSPWMCCFG_EXTN_MSK)

#define HSPWMCADR_BUSY_MSK              BIT7
#define HSPWMC_CheckBusy()              READ_REG_BIT(HSPWMC_ADR, HSPWMCADR_BUSY_MSK)

#define HSPWMCADR_READ_MSK              BIT7
#define HSPWMC_AsyncRead(r, d)          HSPWMC_ADR = ((r) | HSPWMCADR_READ_MSK);    \
                                        while (HSPWMC_CheckBusy());                 \
                                        (d) = HSPWMC_DAT

#define HSPWMC_AsyncWrite(r, d)         HSPWMC_DAT = (d);                           \
                                        HSPWMC_ADR = ((r) & ~HSPWMCADR_READ_MSK)

////////////////////////

#define HSPWMDCFG_ASYNCEN_MSK           (BIT1 | BIT0)
#define HSPWMD_Enable()                 MODIFY_REG(HSPWMD_CFG, HSPWMDCFG_ASYNCEN_MSK, ((3) << 0))
#define HSPWMD_Disable()                MODIFY_REG(HSPWMD_CFG, HSPWMDCFG_ASYNCEN_MSK, ((0) << 0))

#define HSPWMDCFG_INTEN_MSK             BIT2
#define HSPWMD_EnableInt()              SET_REG_BIT(HSPWMD_CFG, HSPWMDCFG_INTEN_MSK)
#define HSPWMD_DisableInt()             CLR_REG_BIT(HSPWMD_CFG, HSPWMDCFG_INTEN_MSK)

#define HSPWMDCFG_EXTN_MSK              BIT3
#define HSPWMD_SelectBankFE80H()        CLR_REG_BIT(HSPWMD_CFG, HSPWMDCFG_EXTN_MSK)
#define HSPWMD_SelectBankF900H()        SET_REG_BIT(HSPWMD_CFG, HSPWMDCFG_EXTN_MSK)

#define HSPWMDADR_BUSY_MSK              BIT7
#define HSPWMD_CheckBusy()              READ_REG_BIT(HSPWMD_ADR, HSPWMDADR_BUSY_MSK)

#define HSPWMDADR_READ_MSK              BIT7
#define HSPWMD_AsyncRead(r, d)          HSPWMD_ADR = ((r) | HSPWMDADR_READ_MSK);    \
                                        while (HSPWMD_CheckBusy());                 \
                                        (d) = HSPWMD_DAT

#define HSPWMD_AsyncWrite(r, d)         HSPWMD_DAT = (d);                           \
                                        HSPWMD_ADR = ((r) & ~HSPWMDADR_READ_MSK)

////////////////////////

#define HSPWMECFG_ASYNCEN_MSK           (BIT1 | BIT0)
#define HSPWME_Enable()                 MODIFY_REG(HSPWME_CFG, HSPWMECFG_ASYNCEN_MSK, ((3) << 0))
#define HSPWME_Disable()                MODIFY_REG(HSPWME_CFG, HSPWMECFG_ASYNCEN_MSK, ((0) << 0))

#define HSPWMECFG_INTEN_MSK             BIT2
#define HSPWME_EnableInt()              SET_REG_BIT(HSPWME_CFG, HSPWMECFG_INTEN_MSK)
#define HSPWME_DisableInt()             CLR_REG_BIT(HSPWME_CFG, HSPWMECFG_INTEN_MSK)

#define HSPWMECFG_EXTN_MSK              BIT3
#define HSPWME_SelectBankFE80H()        CLR_REG_BIT(HSPWME_CFG, HSPWMECFG_EXTN_MSK)
#define HSPWME_SelectBankF900H()        SET_REG_BIT(HSPWME_CFG, HSPWMECFG_EXTN_MSK)

#define HSPWMEADR_BUSY_MSK              BIT7
#define HSPWME_CheckBusy()              READ_REG_BIT(HSPWME_ADR, HSPWMEADR_BUSY_MSK)

#define HSPWMEADR_READ_MSK              BIT7
#define HSPWME_AsyncRead(r, d)          HSPWME_ADR = ((r) | HSPWMEADR_READ_MSK);    \
                                        while (HSPWME_CheckBusy());                 \
                                        (d) = HSPWME_DAT

#define HSPWME_AsyncWrite(r, d)         HSPWME_DAT = (d);                           \
                                        HSPWME_ADR = ((r) & ~HSPWMEADR_READ_MSK)

////////////////////////

#define HSPWMFCFG_ASYNCEN_MSK           (BIT1 | BIT0)
#define HSPWMF_Enable()                 MODIFY_REG(HSPWMF_CFG, HSPWMFCFG_ASYNCEN_MSK, ((3) << 0))
#define HSPWMF_Disable()                MODIFY_REG(HSPWMF_CFG, HSPWMFCFG_ASYNCEN_MSK, ((0) << 0))

#define HSPWMFCFG_INTEN_MSK             BIT2
#define HSPWMF_EnableInt()              SET_REG_BIT(HSPWMF_CFG, HSPWMFCFG_INTEN_MSK)
#define HSPWMF_DisableInt()             CLR_REG_BIT(HSPWMF_CFG, HSPWMFCFG_INTEN_MSK)

#define HSPWMFCFG_EXTN_MSK              BIT3
#define HSPWMF_SelectBankFE80H()        CLR_REG_BIT(HSPWMF_CFG, HSPWMFCFG_EXTN_MSK)
#define HSPWMF_SelectBankF900H()        SET_REG_BIT(HSPWMF_CFG, HSPWMFCFG_EXTN_MSK)

#define HSPWMFADR_BUSY_MSK              BIT7
#define HSPWMF_CheckBusy()              READ_REG_BIT(HSPWMF_ADR, HSPWMFADR_BUSY_MSK)

#define HSPWMFADR_READ_MSK              BIT7
#define HSPWMF_AsyncRead(r, d)          HSPWMF_ADR = ((r) | HSPWMFADR_READ_MSK);    \
                                        while (HSPWMF_CheckBusy());                 \
                                        (d) = HSPWMF_DAT

#define HSPWMF_AsyncWrite(r, d)         HSPWMF_DAT = (d);                           \
                                        HSPWMF_ADR = ((r) & ~HSPWMFADR_READ_MSK)

/////////////////////////////////////////////////


#define P2PDMA_SetSource(p, n)          DMA_P2P##p##_SRC = (n)
#define P2PDMA_SetDestination(p, n)     DMA_P2P##p##_DEST = (n)

#define DMA_P2PA_SetUART1Receive()      P2PDMA_SetSource(1, P2P_SRC_UR1RX )
#define DMA_P2PA_SetUART2Receive()      P2PDMA_SetSource(1, P2P_SRC_UR2RX )
#define DMA_P2PA_SetUART3Receive()      P2PDMA_SetSource(1, P2P_SRC_UR3RX )
#define DMA_P2PA_SetUART4Receive()      P2PDMA_SetSource(1, P2P_SRC_UR4RX )
#define DMA_P2PA_SetSPI1Receive()       P2PDMA_SetSource(1, P2P_SRC_SPI1RX)
#define DMA_P2PA_SetI2C1Receive()       P2PDMA_SetSource(1, P2P_SRC_I2C1RX)
#define DMA_P2PA_SetLCMReceive()        P2PDMA_SetSource(1, P2P_SRC_LCMRX )
#define DMA_P2PA_SetQSPIReceive()       P2PDMA_SetSource(1, P2P_SRC_QSPIRX)
#define DMA_P2PA_SetADC1Receive()       P2PDMA_SetSource(1, P2P_SRC_ADC1  )
#define DMA_P2PA_SetI2S1Receive()       P2PDMA_SetSource(1, P2P_SRC_I2S1RX)
#define DMA_P2PA_SetUART5Receive()      P2PDMA_SetSource(1, P2P_SRC_UR5RX )
#define DMA_P2PA_SetUART6Receive()      P2PDMA_SetSource(1, P2P_SRC_UR6RX )
#define DMA_P2PA_SetUART7Receive()      P2PDMA_SetSource(1, P2P_SRC_UR7RX )
#define DMA_P2PA_SetUART8Receive()      P2PDMA_SetSource(1, P2P_SRC_UR8RX )
#define DMA_P2PA_SetSPI2Receive()       P2PDMA_SetSource(1, P2P_SRC_SPI2RX)
#define DMA_P2PA_SetSPI3Receive()       P2PDMA_SetSource(1, P2P_SRC_SPI3RX)
#define DMA_P2PA_SetSPI4Receive()       P2PDMA_SetSource(1, P2P_SRC_SPI4RX)
#define DMA_P2PA_SetI2C2Receive()       P2PDMA_SetSource(1, P2P_SRC_I2C2RX)
#define DMA_P2PA_SetI2S2Receive()       P2PDMA_SetSource(1, P2P_SRC_I2S2RX)
#define DMA_P2PA_SetCAN1Receive()       P2PDMA_SetSource(1, P2P_SRC_CAN1RX)
#define DMA_P2PA_SetCAN2Receive()       P2PDMA_SetSource(1, P2P_SRC_CAN2RX)
#define DMA_P2PA_SetADC2Receive()       P2PDMA_SetSource(1, P2P_SRC_ADC2  )

#define DMA_P2PA_SetUART1Send()         P2PDMA_SetDestination(1, P2P_DEST_UR1TX )
#define DMA_P2PA_SetUART2Send()         P2PDMA_SetDestination(1, P2P_DEST_UR2TX )
#define DMA_P2PA_SetUART3Send()         P2PDMA_SetDestination(1, P2P_DEST_UR3TX )
#define DMA_P2PA_SetUART4Send()         P2PDMA_SetDestination(1, P2P_DEST_UR4TX )
#define DMA_P2PA_SetSPI1Send()          P2PDMA_SetDestination(1, P2P_DEST_SPI1TX)
#define DMA_P2PA_SetI2C1Send()          P2PDMA_SetDestination(1, P2P_DEST_I2C1TX)
#define DMA_P2PA_SetLCMSend()           P2PDMA_SetDestination(1, P2P_DEST_LCMTX )
#define DMA_P2PA_SetQSPISend()          P2PDMA_SetDestination(1, P2P_DEST_QSPITX)
#define DMA_P2PA_SetI2S1Send()          P2PDMA_SetDestination(1, P2P_DEST_I2S1TX)
#define DMA_P2PA_SetUART5Send()         P2PDMA_SetDestination(1, P2P_DEST_UR5TX )
#define DMA_P2PA_SetUART6Send()         P2PDMA_SetDestination(1, P2P_DEST_UR6TX )
#define DMA_P2PA_SetUART7Send()         P2PDMA_SetDestination(1, P2P_DEST_UR7TX )
#define DMA_P2PA_SetUART8Send()         P2PDMA_SetDestination(1, P2P_DEST_UR8TX )
#define DMA_P2PA_SetSPI2Send()          P2PDMA_SetDestination(1, P2P_DEST_SPI2TX)
#define DMA_P2PA_SetSPI3Send()          P2PDMA_SetDestination(1, P2P_DEST_SPI3TX)
#define DMA_P2PA_SetSPI4Send()          P2PDMA_SetDestination(1, P2P_DEST_SPI4TX)
#define DMA_P2PA_SetI2C2Send()          P2PDMA_SetDestination(1, P2P_DEST_I2C2TX)
#define DMA_P2PA_SetI2S2Send()          P2PDMA_SetDestination(1, P2P_DEST_I2S2TX)
#define DMA_P2PA_SetDAC1Send()          P2PDMA_SetDestination(1, P2P_DEST_DAC1TX)
#define DMA_P2PA_SetDAC2Send()          P2PDMA_SetDestination(1, P2P_DEST_DAC2TX)
#define DMA_P2PA_SetCAN1Send()          P2PDMA_SetDestination(1, P2P_DEST_CAN1TX)
#define DMA_P2PA_SetCAN2Send()          P2PDMA_SetDestination(1, P2P_DEST_CAN2TX)

#define DMA_P2PB_SetUART1Receive()      P2PDMA_SetSource(2, P2P_SRC_UR1RX )
#define DMA_P2PB_SetUART2Receive()      P2PDMA_SetSource(2, P2P_SRC_UR2RX )
#define DMA_P2PB_SetUART3Receive()      P2PDMA_SetSource(2, P2P_SRC_UR3RX )
#define DMA_P2PB_SetUART4Receive()      P2PDMA_SetSource(2, P2P_SRC_UR4RX )
#define DMA_P2PB_SetSPI1Receive()       P2PDMA_SetSource(2, P2P_SRC_SPI1RX)
#define DMA_P2PB_SetI2C1Receive()       P2PDMA_SetSource(2, P2P_SRC_I2C1RX)
#define DMA_P2PB_SetLCMReceive()        P2PDMA_SetSource(2, P2P_SRC_LCMRX )
#define DMA_P2PB_SetQSPIReceive()       P2PDMA_SetSource(2, P2P_SRC_QSPIRX)
#define DMA_P2PB_SetADC1Receive()       P2PDMA_SetSource(2, P2P_SRC_ADC1  )
#define DMA_P2PB_SetI2S1Receive()       P2PDMA_SetSource(2, P2P_SRC_I2S1RX)
#define DMA_P2PB_SetUART5Receive()      P2PDMA_SetSource(2, P2P_SRC_UR5RX )
#define DMA_P2PB_SetUART6Receive()      P2PDMA_SetSource(2, P2P_SRC_UR6RX )
#define DMA_P2PB_SetUART7Receive()      P2PDMA_SetSource(2, P2P_SRC_UR7RX )
#define DMA_P2PB_SetUART8Receive()      P2PDMA_SetSource(2, P2P_SRC_UR8RX )
#define DMA_P2PB_SetSPI2Receive()       P2PDMA_SetSource(2, P2P_SRC_SPI2RX)
#define DMA_P2PB_SetSPI3Receive()       P2PDMA_SetSource(2, P2P_SRC_SPI3RX)
#define DMA_P2PB_SetSPI4Receive()       P2PDMA_SetSource(2, P2P_SRC_SPI4RX)
#define DMA_P2PB_SetI2C2Receive()       P2PDMA_SetSource(2, P2P_SRC_I2C2RX)
#define DMA_P2PB_SetI2S2Receive()       P2PDMA_SetSource(2, P2P_SRC_I2S2RX)
#define DMA_P2PB_SetCAN1Receive()       P2PDMA_SetSource(2, P2P_SRC_CAN1RX)
#define DMA_P2PB_SetCAN2Receive()       P2PDMA_SetSource(2, P2P_SRC_CAN2RX)
#define DMA_P2PB_SetADC2Receive()       P2PDMA_SetSource(2, P2P_SRC_ADC2  )

#define DMA_P2PB_SetUART1Send()         P2PDMA_SetDestination(2, P2P_DEST_UR1TX )
#define DMA_P2PB_SetUART2Send()         P2PDMA_SetDestination(2, P2P_DEST_UR2TX )
#define DMA_P2PB_SetUART3Send()         P2PDMA_SetDestination(2, P2P_DEST_UR3TX )
#define DMA_P2PB_SetUART4Send()         P2PDMA_SetDestination(2, P2P_DEST_UR4TX )
#define DMA_P2PB_SetSPI1Send()          P2PDMA_SetDestination(2, P2P_DEST_SPI1TX)
#define DMA_P2PB_SetI2C1Send()          P2PDMA_SetDestination(2, P2P_DEST_I2C1TX)
#define DMA_P2PB_SetLCMSend()           P2PDMA_SetDestination(2, P2P_DEST_LCMTX )
#define DMA_P2PB_SetQSPISend()          P2PDMA_SetDestination(2, P2P_DEST_QSPITX)
#define DMA_P2PB_SetI2S1Send()          P2PDMA_SetDestination(2, P2P_DEST_I2S1TX)
#define DMA_P2PB_SetUART5Send()         P2PDMA_SetDestination(2, P2P_DEST_UR5TX )
#define DMA_P2PB_SetUART6Send()         P2PDMA_SetDestination(2, P2P_DEST_UR6TX )
#define DMA_P2PB_SetUART7Send()         P2PDMA_SetDestination(2, P2P_DEST_UR7TX )
#define DMA_P2PB_SetUART8Send()         P2PDMA_SetDestination(2, P2P_DEST_UR8TX )
#define DMA_P2PB_SetSPI2Send()          P2PDMA_SetDestination(2, P2P_DEST_SPI2TX)
#define DMA_P2PB_SetSPI3Send()          P2PDMA_SetDestination(2, P2P_DEST_SPI3TX)
#define DMA_P2PB_SetSPI4Send()          P2PDMA_SetDestination(2, P2P_DEST_SPI4TX)
#define DMA_P2PB_SetI2C2Send()          P2PDMA_SetDestination(2, P2P_DEST_I2C2TX)
#define DMA_P2PB_SetI2S2Send()          P2PDMA_SetDestination(2, P2P_DEST_I2S2TX)
#define DMA_P2PB_SetDAC1Send()          P2PDMA_SetDestination(2, P2P_DEST_DAC1TX)
#define DMA_P2PB_SetDAC2Send()          P2PDMA_SetDestination(2, P2P_DEST_DAC2TX)
#define DMA_P2PB_SetCAN1Send()          P2PDMA_SetDestination(2, P2P_DEST_CAN1TX)
#define DMA_P2PB_SetCAN2Send()          P2PDMA_SetDestination(2, P2P_DEST_CAN2TX)

#define DMA_P2PA_Disable()              (DMA_P2P1_DEST = 0, DMA_P2P1_SRC = 0)
#define DMA_P2PB_Disable()              (DMA_P2P2_DEST = 0, DMA_P2P2_SRC = 0)

/////////////////////////////////////////////////

#define CRCCR_RST_MSK                   BIT7
#define CRC_Reset()                     SET_REG_BIT(CRC_CR, CRCCR_RST_MSK)

#define CRCCR_MODE_MSK                  BIT4
#define CRC_ModebusMode()               CLR_REG_BIT(CRC_CR, CRCCR_MODE_MSK)
#define CRC_EthernetMode()              SET_REG_BIT(CRC_CR, CRCCR_MODE_MSK)
#define CRC_IsCRC32()                   READ_REG_BIT(CRC_CR, CRCCR_MODE_MSK)

#define CRCCR_INVOUT_MSK                BIT2
#define CRC_ResultNonInverted()         CLR_REG_BIT(CRC_CR, CRCCR_INVOUT_MSK)
#define CRC_ResultInverted()            SET_REG_BIT(CRC_CR, CRCCR_INVOUT_MSK)

#define CRCCR_REVIN_MSK                 BIT1
#define CRC_DataNonReverse()            CLR_REG_BIT(CRC_CR, CRCCR_REVIN_MSK)
#define CRC_DataReverse()               SET_REG_BIT(CRC_CR, CRCCR_REVIN_MSK)

#define CRCCR_REVOUT_MSK                BIT0
#define CRC_ResultNonReverse()          CLR_REG_BIT(CRC_CR, CRCCR_REVOUT_MSK)
#define CRC_ResultReverse()             SET_REG_BIT(CRC_CR, CRCCR_REVOUT_MSK)

#define CRC_DataIn(n)                   CRC_DIN = LOBYTE(n)

#define CRC_SetInitial16(n)             CRC_DOH = HIBYTE(n);    \
                                        CRC_DOL = LOBYTE(n)

#define CRC_SetInitial32(n)             CRC_DO3 = BYTE0(n);     \
                                        CRC_DO2 = BYTE1(n);     \
                                        CRC_DO1 = BYTE2(n);     \
                                        CRC_DO0 = BYTE3(n)

#define CRC_ReadResult16()              MAKEWORD(CRC_DOL, CRC_DOH)
#define CRC_ReadResult32()              MAKELONG(MAKEWORD(CRC_DO3, CRC_DO2), MAKEWORD(CRC_DO1, CRC_DO0))

/////////////////////////////////////////////////

#endif

