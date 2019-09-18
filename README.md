# Flopper_acheiver

This Project is divided into 2 sections:

  1. Model
  2. Design
  
  
  MODEL:
  
   This section is about understanding the hardware architecture of the machine (can be either CPU or GPU).
   Another motive of the section is theoretically estimating and proving the maximum flops* and Iops* achievable by the respective            Machine.
    
   *Notes: Flops - Floating Point Operations per Sceond
           Iops  - Interger operations per Second
            
  Pre-requisite Knowledge:
  1. Assembly Lang
  2. Intel and AMD Chip Architectures
  3. Chip Performance terminologies.
  
  
  
  DESIGN:
  
   This section is about achieving the theoretical value suggested by writing a code.
      
   In this section, we tried to achieve the maximum performing capability of the machine by below process:
        1. Providing the sufficient instructions to machine or Processor to avoid bubbles.
        2. Eliminating the looping and Conditonal jumps to our best to decrease unnecesary instruction in the pipeline.
        3. Loop Unrolling is used to decrease the branchment instructions.
        4. Usage of OpenMP to parllel the instruction to all the available threads.
        5. Intrinsic commands to saturate the the instruction bits to max the the instruction that can be provided to the machine.
