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
  sc_in<float> in; 
  sc_out<float> out;  

  SC_CTOR(FFT)
    {
      SC_THREAD(comportement)
      sensitive<<clk.pos();
    }
        // your code;      
private :

  void comportement(); 
  void but(float real_weight,float img_weight, float real0_in, float img0_in,float real1_in,float img1_in, float* real0_out, float* img0_out,  float* real1_out, float* img1_out);
  void fft();
  float buffer[16];
  float sample_real[8];
  float sample_img[8];
  float sample_real_out[8];
  float sample_img_out[8];
  float real_weight[4]={1,0.7071067812,0,-0.7071067812};
  float img_weight[4] = {0, -0.7071067812, -1, -0.7071067812};

};
#endif

