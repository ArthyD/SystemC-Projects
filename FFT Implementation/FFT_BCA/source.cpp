/* fichier source.cpp */
#include "source.h"
#include <fstream>
#include <iostream>

using std::cout;
using std::endl;


void SOURCE::COMPORTEMENT()
{ 
  std::ifstream realStream("in_real.txt");
  std::ifstream imagStream("in_imag.txt");
		
  float tmp_val;
  bool send_real = true;
  master_valid.write(false); 

  if(!realStream||!imagStream)
    cout<<"[SOURCE] "<<"Un des fichiers d'entree n'est pas ouvert"<<endl;

  wait();

  while(true)
    {
      wait();
      if(!realStream.eof()&&!imagStream.eof()){
        if(master_request.read()){   
          if (send_real)
          {  
          realStream>>tmp_val;
          out.write(tmp_val);
          cout << "[SOURCE]" << "sending real = " << tmp_val << endl;
          master_valid.write(true);    
          send_real = false;   
          }  
          else { 
          imagStream>>tmp_val;
          out.write(tmp_val);
          cout << "[SOURCE]" << "sending img = " << tmp_val << endl;
          master_valid.write(true);

          send_real = true;
          }
        }
      }
      else
      
	{ 
	  cout<<"[SOURCE] "<< "Fin des fichiers d'entree atteinte." << endl;
    master_valid.write(false);
	}
    }
}	
