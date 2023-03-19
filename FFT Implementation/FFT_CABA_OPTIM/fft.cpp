/* fichier fft.cpp */
#include <systemc.h>
#include "fft.h"
#include <stdio.h>


sc_int<23> multiply(sc_int<23> a, sc_int<23> b){
    sc_int<23> result = (a*b)>> 5;
    return result;
}

void FFT::fft(){
    
    for(int stage = 0;stage<3;stage++){
        for(int offset = 0; offset<4; offset++)
        {
            but(real_weight[coeff_stage[20*stage + 5*offset]],img_weight[coeff_stage[20*stage+5*offset]],
                stage_real[stage][coeff_stage[20*stage + 5 * offset +1]],stage_imag[stage][coeff_stage[20*stage + 5 * offset +1]],
                stage_real[stage][coeff_stage[20*stage + 5 * offset +2]],stage_imag[stage][coeff_stage[20*stage + 5 * offset +2]],
                &stage_real[stage+1][coeff_stage[20*stage + 5 * offset +3]],&stage_imag[stage+1][coeff_stage[20*stage + 5 * offset +3]],
                &stage_real[stage+1][coeff_stage[20*stage + 5 * offset +4]],&stage_imag[stage+1][coeff_stage[20*stage + 5 * offset +4]]);
        }
    }

}

void FFT::but(sc_int<23> real_weight,sc_int<23> img_weight, sc_int<23> real0_in, sc_int<23> img0_in,sc_int<23> real1_in,sc_int<23> img1_in, sc_int<23> *real0_out, sc_int<23> *img0_out,  sc_int<23> *real1_out, sc_int<23> *img1_out){
      *real0_out = real0_in + (multiply(real1_in, real_weight) - multiply(img1_in,img_weight));
      *img0_out = img0_in + (multiply(real1_in, img_weight) + multiply(img1_in,real_weight));
      *real1_out = real0_in - (multiply(real1_in, real_weight) - multiply(img1_in, img_weight));
      *img1_out = img0_in - (multiply(real1_in, img_weight) + multiply(img1_in, real_weight));
}


// your code
void FFT::comportement(){
    int data_in_counter = 0;
    int data_out_counter = 0;
    bool treatment_done = false;
    slave_request.write(false);
    master_valid.write(false);

    while(1){
        wait();
        if (reset)
        {
            data_in_counter = 0;
            data_out_counter = 0;
            treatment_done = false;
            slave_request.write(false);
            master_valid.write(false);  
            out.write(0);
        }
        else{
        if(data_in_counter < 16){
            if (data_in_counter == 15){
                slave_request.write(false);
            }
            else {
            slave_request.write(true);
            }
            master_valid.write(false);
            if(slave_valid.read()){
                buffer[data_in_counter]= in.read();
                data_in_counter += 1;
            }
        }

        else if (treatment_done == false){
            slave_request.write(false);
            master_valid.write(false);

            for(int i = 0; i<8; i++){
                stage_real[0][i]=buffer[2*i];
                stage_imag[0][i]=buffer[2*i+1];
            }
            fft();
            for(int i = 0; i < 8; i++){
                buffer[2*i]=stage_real[3][i];
                buffer[2*i+1]=stage_imag[3][i];                
            }
            treatment_done=true;
        }

        else if (treatment_done == true && data_out_counter < 16){
            slave_request.write(false);
            master_valid.write(true);
            if(master_request.read()){
                out.write(buffer[data_out_counter]);
                data_out_counter += 1;
            }
        }

        else {
            treatment_done=false;
            slave_request.write(true);
            master_valid.write(false);
            data_in_counter=0;
            data_out_counter=0;
        }


        }
    }
     
}



