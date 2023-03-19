/* fichier sink.cpp */
#include "sink.h"
#include <fstream>
#include <iostream>

using std::cout;
using std::endl;

void SINK::COMPORTEMENT()
{  
  std::ofstream realStream("out_real.txt");
  std::ofstream imagStream("out_imag.txt");

  std::ifstream realStream_ref("out_real_ref_valid.txt");
  std::ifstream imagStream_ref("out_imag_ref_valid.txt");
		
  float real, imag, real_ref, imag_ref, diff, max_error=0.;
        
  int i, data_counter = 0;
  if(!realStream||!imagStream||!realStream_ref||!imagStream_ref)
    cout<<"[SINK] "<<"Un des fichiers d'entree n'est pas ouvert"<<endl;
	
  wait();

  while(true)
    { 
	  wait();
	  if (data_counter < 16)
	  {
		slave_request.write(true);
		if (slave_valid.read()) {
			in_buffer[data_counter]=in.read();
			data_counter += 1;
		}
	  }
	  else {
		slave_request.write(false);
	  cout<<"[SINK] "<< "Lecture des 16 �chantillons par le bloc SINK..." << endl;

	  for (i = 0; i < 8; i++)
	    { 
	      real= in_buffer[2*i];
	      imag= in_buffer[2*i+1];
	
	      realStream<<real<<endl;
	      imagStream<<imag<<endl;
	     
              if(!realStream_ref.eof()&&!imagStream_ref.eof()){
		realStream_ref>>real_ref;
		imagStream_ref>>imag_ref;
		diff=abs(real-real_ref);
		max_error= diff>max_error ? diff : max_error;
		diff=abs(imag-imag_ref);
		max_error= diff>max_error ? diff : max_error;
		}	
		
	    }
	    data_counter = 0;
	cout<<"[SINK] "<<"Erreur maximale actuelle: "<<max_error<<endl; 
	}
  }  
  
}
