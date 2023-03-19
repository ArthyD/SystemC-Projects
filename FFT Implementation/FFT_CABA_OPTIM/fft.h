#ifndef FFT_H
#define FFT_H
#include <systemc.h>

#pragma hls_design top
SC_MODULE(FFT)
{
public :

  sc_in<bool> clk;
  sc_in<bool> slave_valid;
  sc_in<bool> master_request;
  sc_out<bool> slave_request;
  sc_out<bool> master_valid;
  sc_in<sc_int<23>> in; 
  sc_out<sc_int<23>> out;  

  sc_in<bool> reset;

  SC_CTOR(FFT)
    {
      SC_THREAD(comportement)
      sensitive<<clk.pos() << reset.pos();
    }
        // your code;      
private :

  void comportement(); 
  void but(sc_int<23> real_weight,sc_int<23> img_weight, sc_int<23> real0_in, sc_int<23> img0_in,sc_int<23> real1_in,sc_int<23> img1_in, sc_int<23>* real0_out, sc_int<23>* img0_out,  sc_int<23>* real1_out, sc_int<23>* img1_out);
  void fft();
  sc_int<23> buffer[16];
  sc_int<23> real_weight[4]={32,22,0,-22};
  sc_int<23> img_weight[4] = {0, -22, -32, -22};
  sc_int<23> coeff_stage[60] = {0,0,4,0,1,0,2,6,2,3,0,1,5,4,5,0,3,7,6,7,0,0,2,0,2,2,1,3,1,3,0,4,6,4,6,2,5,7,5,7,0,0,4,0,4,1,1,5,1,5,2,2,6,2,6,3,3,7,3,7};
  sc_int<23> stage_real[4][8];
  sc_int<23> stage_imag[4][8];
};
#endif

