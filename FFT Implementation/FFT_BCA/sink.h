#ifndef SINK_H
#define SINK_H

#include "systemc.h"

 SC_MODULE(SINK) 
    {
         sc_in_clk    clk; 
         sc_in<float> in; 
         sc_in<bool> slave_valid;
         sc_out<bool> slave_request;

        void COMPORTEMENT(); 

         SC_CTOR(SINK)
              {
                     SC_THREAD(COMPORTEMENT);
                     sensitive << clk.pos();
              }    
private :

     float in_buffer[16]; 

     };


#endif
