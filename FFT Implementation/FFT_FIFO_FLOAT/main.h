//  main.h

#include <systemc.h>
#include "source.h"
#include "fft.h"
#include "sink.h"

SC_MODULE (TOP) {
  
  // signals
  sc_clock clk;
  sc_fifo<float> source_fft;
  sc_fifo<float> fft_sink;
      
   
  // instanciate
  SOURCE SOURCE1;
  FFT FFT1;
  SINK SINK1;

 SC_CTOR(TOP)
   :  clk("clk", 10, SC_NS, 0.5),
    source_fft("source_fft", 16),
    fft_sink("fft_sink", 16),
    FFT1("FFT_PROCESS"),
    SOURCE1("SOURCE_PROCESS"),
    SINK1("SINK_PROCESS")
      {

	FFT1.clk(clk);
	FFT1.in(source_fft);
	FFT1.out(fft_sink);

	SOURCE1.clk(clk);
	SOURCE1.out(source_fft);

	SINK1.clk(clk);
	SINK1.in(fft_sink);   

      }
};

