//  main.h

#include <systemc.h>
#include "source.h"
#include "fft.h"
#include "sink.h"

SC_MODULE (TOP) {
  
  // signals
  sc_clock clk;
  sc_signal<sc_int<23>> source_fft;
  sc_signal<sc_int<23>> fft_sink;
  sc_signal<bool> source_valid;
  sc_signal<bool> source_request;
  sc_signal<bool> sink_valid;
  sc_signal<bool> sink_request;
      
   
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
  FFT1.master_request(sink_request);
  FFT1.slave_request(source_request);
  FFT1.master_valid(sink_valid);
  FFT1.slave_valid(source_valid);

	SOURCE1.clk(clk);
	SOURCE1.out(source_fft);
  SOURCE1.master_request(source_request);
  SOURCE1.master_valid(source_valid);

	SINK1.clk(clk);
	SINK1.in(fft_sink);   
  SINK1.slave_request(sink_request);
  SINK1.slave_valid(sink_valid);

      }
};

