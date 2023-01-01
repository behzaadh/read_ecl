# read_ecl
Read binary output data files (such as restart files) from Schlumberger's reservoir simulator, Eclipse. 

For more information: https://se.mathworks.com/matlabcentral/fileexchange/47607-read_ecl-m

## How to use?
Call contructor by passing the file name path, for example ```READ_ECL("2D_model.INIT")```. Then, you can have an access to a struct, called ```SLB_DATA```, containing all data from the binary file specified by "filename" string. Note that the string and number formats are separated to ```HEADER``` and ```DATA``` variables, respectively. Please have a look at test file to see more examples.

## Performance?
The test samples took **409** [ms] to be read using MinGW 64-bit, while it took **940** [ms] in MATLAB with using the same machine
