//  main.cpp 
// Testbench pour FFT avec donn�es en flottant

#include <systemc.h>
#include "main.h"


int sc_main(int argc, char *argv[])
{

  // Instanciation du TOP
  TOP mainTop("top");

  // Creation des traces
  sc_trace_file *tf = sc_create_vcd_trace_file("trace");
  tf->set_time_unit(1, SC_NS);
  // ATTENTION:
  // on peut pas faire ceci:
  //sc_trace(tf, mainTop.source_fft, "fifo1");
  // MAIS il faut faire appel a la methode
  // trace() du canal que l'on veut suivre
  mainTop.source_fft.trace(tf);
  mainTop.fft_sink.trace(tf);
  mainTop.sink_request.trace(tf);
  mainTop.source_request.trace(tf);
  mainTop.sink_valid.trace(tf);
  mainTop.source_valid.trace(tf);
  mainTop.clk.trace(tf);

  //Lancement de la simulation
  sc_start(2000, SC_NS);

  //Fin
  cout << "Finished at " << sc_time_stamp() << "\n";
  //Fermeture du fichier de traces
  sc_close_vcd_trace_file(tf);

  return 0;

}
