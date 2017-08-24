/*######################################################
##
## cwm_pick_up
##									
## version  v3.02						2016-04-14
##
######################################################*/
#ifndef __cwm_pick_up_H__
#define __cwm_pick_up_H__


/*
    *
    *   Call this function when enable this sensor
    *
*/  
void enable_cwm_pick_up(void);


/*
    *
    *   Call this function when disable this sensor
    *
*/
void disable_cwm_pick_up(void);


/*
    *
    *   Initialize all variables
    *
*/
void init_cwm_pick_up(void);


/*
    *
    *   Get version
    *
    *   Output:
    *       version[0] = date (yyyymmdd)
    *       version[1] = version
    *       version[2] = subversion
    *       version[3] = build
    *
*/
void version_cwm_pick_up(int *version);


/*
    *   Set configurations and parameters of algorithm 
    *   Default: char data[5] = {5, 5, 5, 5, 5};
*/
void set_config_cwm_pick_up(void *data, int size);


/**
        *      Sensors Requirement:
        *              
        *                     
        *              Acceleration:
        *                      rate: 10ms
        *              
        *                      
        *
        *      Trigger source: (which sensors to calculate this algo)
        *              Acceleration
        *
        *      Sensors type:  one shot
        *              continuous
        *              on change
        *              one shot(mean only trigger onetime(need to be re-initial))
        *
        *      output:
        *              size: float[x].
        *
        *      output report format:
       *               [0] = Trigger Result (0: none  1:pick)
        *              [1] = Trigger count, plus 1 for each trigger
        *              [2] = None
		  
                return value:
                        -9     set config success 
                               (return data  data[0]=100*parameters[0]+parameters[1];
                                             data[1]=100*parameters[2]+parameters[3];
                                             data[2]=100*parameters[4];)

                        -8     set config fail
                        -4     data wrong
                        -3     dt wrong
                        -2:    not initial
                        -1:    error
                        0:     nothing to do
                        1:     report event.		  
        *              
        *              
        *              
        *
        *      Algo introduction:
        *              Pick up the device.
        *
        *      Algo test scenario: 
									  Pick up the device from the table or hand.
        *
        *      Algo history list:
        *         20160328 V3.00  for new format and add set config function
        *         20160408 V3.01  for new format and add set config function         
        *         20160414 V3.02  add set config info  

  */
int cwm_pick_up(float *acc_g, float *output, float dt_us_g);
  
#endif