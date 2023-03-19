#ifndef FFT_H
#define FFT_H
#include <systemc.h>

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

  SC_CTOR(FFT)
    {
      SC_THREAD(comportement)
      sensitive<<clk.pos();
    }
        // your code;      
private :

  void comportement(); 
  void but(sc_int<23> real_weight,sc_int<23> img_weight, sc_int<23> real0_in, sc_int<23> img0_in,sc_int<23> real1_in,sc_int<23> img1_in, sc_int<23>* real0_out, sc_int<23>* img0_out,  sc_int<23>* real1_out, sc_int<23>* img1_out);
  void fft();
  sc_int<23> buffer[16];
  sc_int<23> sample_real[8];
  sc_int<23> sample_img[8];
  sc_int<23> sample_real_out[8];
  sc_int<23> sample_img_out[8];
  sc_int<23> real_weight[4]={32,22,0,-22};
  sc_int<23> img_weight[4] = {0, -22, -32, -22};

};
#endif

