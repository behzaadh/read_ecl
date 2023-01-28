import time
import read_ecl4py

start_time = time.process_time();

INIT = read_ecl4py.READ_ECL("Examples/2D.INIT");
INSPEC = read_ecl4py.READ_ECL("Examples/2D.INSPEC");
RSSPEC = read_ecl4py.READ_ECL("Examples/2D.RSSPEC");
S0001 = read_ecl4py.READ_ECL("Examples/2D.S0001");
X0000 = read_ecl4py.READ_ECL("Examples/2D.X0000");
SMSPEC = read_ecl4py.READ_ECL("Examples/2D.SMSPEC");
EGRID = read_ecl4py.READ_ECL("Examples/SPE9.EGRID");

end_time = time.process_time();

elapsed_time = end_time - start_time;
print("Elapsed time: ", elapsed_time, "[s]");

precision = 9;

# Testing S0001
matrix = [];
with open('Examples/PARAMS.mtx', 'r') as f:
    for line in f:
        matrix.append([float(x) for x in line.split()])

t = [[row[i] for row in matrix] for i in range(len(matrix[0]))]


for i in range(len(t)):
    for j in range(len(t[i])):
        if(round(matrix[j][i],precision) != round(S0001.Data.DATA["PARAMS"][i][j],precision)):
            print(":Failed to read PARAMS matrix")
            exit()
print("Successfully read PARAMS matrix!")

# Testing X0000
matrix = [];
with open('Examples/SWAT.mtx', 'r') as f:
    for line in f:
        matrix.append([float(x) for x in line.split()])

t = [[row[i] for row in matrix] for i in range(len(matrix[0]))]

for i in range(len(t)):
    for j in range(len(t[i])):
        if(round(matrix[j][i],precision) != round(X0000.Data.DATA["SWAT"][i][j],precision)):
            print(":Failed to read SWAT matrix")
            exit()
print("Successfully read SWAT matrix!")
