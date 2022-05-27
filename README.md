# Velocity analyzer

C program developed to perform analysis in gathered .imu data to find out min and max value of train velocity.


## Build instruction
This project uses CMake build system. In order to properly build it follow steps mentioned below.
### Step 1.
Open window terminal and navigate to root directory of this project.

$ cd nevomo_rekrutacja
...
### Step 2.
Create new folder called 'build'
> $ mkdir build

### Step 3.
Run cmake build system by typing:
> $ cmake -B ./build

### Step 4
Navigate to build directiory
> $ cd ./build
> 
and type:
> $ make 

## Run 
Now project should be compiled and ready to go.
Program can be executed by command
> $ ./velocity_analyzer "abs_path_to_dir_containing_imu_data"

#### Example:
> *$ ./velocity_analyzer "/home/igosor/Downloads/ZADANIE/imu"*

##### Output:
  > *Min velocity: 0.004341   Max velocity: 5.406754*
