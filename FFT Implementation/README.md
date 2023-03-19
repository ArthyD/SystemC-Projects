# FFT project

This project aims to implement a synthetisable FFT for FPGA (Xilinx Nexys board). The project is divided into several development steps :

* FFT_FIFO_FLOAT : first implementation using fifo.
* FFT_BCA : Bus Cycle Accurate, add clock and communication protocols but not synthetisable because of the float.
* FFT_CABA : Cycle Accurate Bus Accurate, data are now encoded into fixed point (18,5) values
* FFT_CABA_OPTIM : Optimisation of the design for better space exploration during synthesis. 