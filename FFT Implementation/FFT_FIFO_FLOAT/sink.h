#ifndef SINK_H
#define SINK_H

#include "systemc.h"

 SC_MODULE(SINK) 
    {
         sc_in_clk    clk; 
         sc_fifo_in<float> in; 

        void COMPORTEMENT(); 

         SC_CTOR(SINK)
              {
                     SC_THREAD(COMPORTEMENT);
                     sensitive << clk.pos();
              }    };
#endif
