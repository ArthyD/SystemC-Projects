/* fichier fft.cpp */
#include <systemc.h>
#include "fft.h"
#include <stdio.h>


void FFT::fft(){
    float stage1_real[8], stage1_img[8], stage2_real[8], stage2_img[8];

    //1sr stage
    but(real_weight[0], img_weight[0], sample_real[0], sample_img[0], sample_real[4], sample_img[4], &stage1_real[0],&stage1_img[0], &stage1_real[1],&stage1_img[1]);
    but(real_weight[0], img_weight[0], sample_real[2], sample_img[2], sample_real[6], sample_img[6], &stage1_real[2],&stage1_img[2], &stage1_real[3],&stage1_img[3]);
    but(real_weight[0], img_weight[0], sample_real[1], sample_img[1], sample_real[5], sample_img[5], &stage1_real[4],&stage1_img[4], &stage1_real[5],&stage1_img[5]);
    but(real_weight[0], img_weight[0], sample_real[3], sample_img[3], sample_real[7], sample_img[7], &stage1_real[6],&stage1_img[6], &stage1_real[7],&stage1_img[7]);

    //2nd Stage
    but(real_weight[0], img_weight[0], stage1_real[0], stage1_img[0], stage1_real[2], stage1_img[2], &stage2_real[0],&stage2_img[0], &stage2_real[2],&stage2_img[2]);
    but(real_weight[2], img_weight[2], stage1_real[1], stage1_img[1], stage1_real[3], stage1_img[3], &stage2_real[1],&stage2_img[1], &stage2_real[3],&stage2_img[3]);
    but(real_weight[0], img_weight[0], stage1_real[4], stage1_img[4], stage1_real[6], stage1_img[6], &stage2_real[4],&stage2_img[4], &stage2_real[6],&stage2_img[6]);
    but(real_weight[2], img_weight[2], stage1_real[5], stage1_img[5], stage1_real[7], stage1_img[7], &stage2_real[5],&stage2_img[5], &stage2_real[7],&stage2_img[7]);

    //3rd stage
    but(real_weight[0], img_weight[0], stage2_real[0], stage2_img[0], stage2_real[4], stage2_img[4], &sample_real_out[0],&sample_img_out[0], &sample_real_out[4],&sample_img_out[4]);
    but(real_weight[1], img_weight[1], stage2_real[1], stage2_img[1], stage2_real[5], stage2_img[5], &sample_real_out[1],&sample_img_out[1], &sample_real_out[5],&sample_img_out[5]);
    but(real_weight[2], img_weight[2], stage2_real[2], stage2_img[2], stage2_real[6], stage2_img[6], &sample_real_out[2],&sample_img_out[2], &sample_real_out[6],&sample_img_out[6]);
    but(real_weight[3], img_weight[3], stage2_real[3], stage2_img[3], stage2_real[7], stage2_img[7], &sample_real_out[3],&sample_img_out[3], &sample_real_out[7],&sample_img_out[7]);


}

void FFT::but(float real_weight,float img_weight, float real0_in, float img0_in,float real1_in,float img1_in, float *real0_out, float *img0_out,  float *real1_out, float *img1_out){

      *real0_out = (real0_in + ((real1_in * real_weight) - (img1_in * img_weight)));
      *img0_out = (img0_in + ((real1_in * img_weight) + (img1_in * real_weight)));
      *real1_out = (real0_in - ((real1_in * real_weight) - (img1_in * img_weight)));
      *img1_out = (img0_in - ((real1_in * img_weight) + (img1_in * real_weight)));

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

        if(data_in_counter < 16){
            if (data_in_counter == 15){
                slave_request.write(false);
            }
            else {
            slave_request.write(true);
            }
            master_valid.write(false);
            if(slave_valid.read()){
                cout << "[FFT] value received " << in.read() << " with index " << data_in_counter << endl;
                buffer[data_in_counter]= in.read();
                data_in_counter += 1;
            }
        }

        else if (treatment_done == false){
            slave_request.write(false);
            master_valid.write(false);
            for (int k = 0; k<8;k++){
                cout << "[FFT]" << "Buffer entrée real,img " << buffer[2*k] << " , " << buffer[2*k+1] << endl;
            }
            for(int i = 0; i<8; i++){
                sample_real[i]=buffer[2*i];
                sample_img[i]=buffer[2*i+1];
            }
            fft();
            for(int i = 0; i < 8; i++){
                buffer[2*i]=sample_real_out[i];
                buffer[2*i+1]=sample_img_out[i];                
            }
            treatment_done=true;
        }

        else if (treatment_done == true && data_out_counter < 16){
            slave_request.write(false);
            master_valid.write(true);
            if(master_request.read()==true){
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



