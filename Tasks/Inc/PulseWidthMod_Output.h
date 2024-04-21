#ifndef INC_PULSEWIDTHMOD_OUTPUT_H_
#define INC_PULSEWIDTHMOD_OUTPUT_H_

#include "DataHandles.h"

/*CCER Register for TIMx*/
#define CCE1_Pos					(0U)
#define CapComp1_Enable				(1U << CCE1_Pos)
#define CCE2_Pos					(4U)
#define CapComp2_Enable				(1U << CCE2_Pos)
#define CCE4_Pos					(12U)
#define CapComp4_Enable				(1U << CCE4_Pos)

/*CCMR Register TIMx*/
#define OCM1_Pos					(4U)					//Output Compare Mode for channel 1
#define OCM1_PWM_Mode				(6U << OCM1_Pos)
#define OCM2_Pos					(12U)					//Output Compare Mode for channel 2
#define OCM2_PWM_Mode				(6U << OCM2_Pos)
#define OCM4_Pos					(12U)					//Output Compare Mode for channel 4
#define OCM4_PWM_Mode				(6U << OCM4_Pos)
#define OCPE1_Pos					(3U)					//Output Compare pre-load enable channel 1
#define OCPE1_Enable				(1U << OCPE1_Pos)
#define OCPE2_Pos					(11U)					//Output Compare pre-load enable channel 2
#define OCPE2_Enable				(1U << OCPE2_Pos)
#define OCPE4_Pos					(11U)					//Output Compare pre-load enable channel 4
#define OCPE4_Enable				(1U << OCPE4_Pos)

/*Control Register 1*/
#define CR1_ARPE_Pos				(7U)					//ARPE Bit
#define CR1_ARPE_Enable				(1U << CR1_ARPE_Pos)
#define CR1_CEN_Pos					(0U)					//Counter Enable
#define CR1_CEN						(1U << CR1_CEN_Pos)

/*EGR Register*/
#define EGR_UG_Pos					(0U)
#define EGR_Enable					(1U << EGR_UG_Pos)

void DisplayData_PWM(void *pvParameters);

#endif /* INC_PULSEWIDTHMOD_OUTPUT_H_ */
