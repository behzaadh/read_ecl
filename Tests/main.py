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
        if(round(t[i][j],precision) != round(S0001.Data.DATA["PARAMS"][i][j],precision)):
            print(":Failed to read PARAMS matrix")
            exit()
print("Successfully read PARAMS matrix!")

# Testing X0000 - SWAT
matrix = [];
with open('Examples/SWAT.mtx', 'r') as f:
    for line in f:
        matrix.append([float(x) for x in line.split()])

t = [[row[i] for row in matrix] for i in range(len(matrix[0]))]

for i in range(len(t)):
    for j in range(len(t[i])):
        if(round(t[i][j],precision) != round(X0000.Data.DATA["SWAT"][i][j],precision)):
            print(":Failed to read SWAT matrix")
            exit()
print("Successfully read SWAT matrix!")

# Testing X0000 - IWEL
matrix = [];
with open('Examples/IWEL.mtx', 'r') as f:
    for line in f:
        matrix.append([float(x) for x in line.split()])

t = [[row[i] for row in matrix] for i in range(len(matrix[0]))]

for i in range(len(t)):
    for j in range(len(t[i])):
        if(round(t[i][j],precision) != round(X0000.Data.DATA["IWEL"][i][j],precision)):
            print(":Failed to read IWEL matrix")
            exit()
print("Successfully read IWEL matrix!")

# Testing INIT - DX
matrix = [];
with open('Examples/DX.mtx', 'r') as f:
    for line in f:
        matrix.append([float(x) for x in line.split()])

t = [[row[i] for row in matrix] for i in range(len(matrix[0]))]

for i in range(len(t)):
    for j in range(len(t[i])):
        if(round(t[i][j],precision) != round(INIT.Data.DATA["DX"][i][j],precision)):
            print(":Failed to read DX matrix")
            exit()
print("Successfully read DX matrix!")

# Testing INIT - LOGIHEAD
matrix = [];
with open('Examples/LOGIHEAD.mtx', 'r') as f:
    for line in f:
        matrix.append([int(x) for x in line.split()])

t = [[row[i] for row in matrix] for i in range(len(matrix[0]))]

for i in range(len(t)):
    for j in range(len(t[i])):
        if(bool(t[i][j]) != bool(INIT.Data.DATA["LOGIHEAD"][i][j])):
            exit()
print("Successfully read LOGIHEAD matrix!")

# Testing INSPEC
matrix = [];
with open('Examples/NAMES.mtx', 'r') as f:
    for line in f:
        matrix.append([str(x) for x in line.split()])

t = [[row[i] for row in matrix] for i in range(len(matrix[0]))]

for i in range(len(t)):
    for j in range(len(t[i])):
        if(t[i][j] != INSPEC.Data.HEADER["NAME"][i][j].replace(" ", "")):
            print(":Failed to read NAMES matrix")
            exit()
print("Successfully read NAMES matrix!")

# Testing INSPEC
matrix = [];
with open('Examples/TYPE.mtx', 'r') as f:
    for line in f:
        matrix.append([str(x) for x in line.split()])

for i in range(len(matrix)):
    for j in range(len(matrix[i])):
        if(matrix[i][j] != RSSPEC.Data.HEADER["TYPE"][j][i].replace(" ", "")):
            print(i,"-",j)
            print(":Failed to read TYPE matrix")
            exit()
print("Successfully read TYPE matrix!")

# Testing SMSPEC - DIMENS
matrix = [];
with open('Examples/DIMENS.mtx', 'r') as f:
    for line in f:
        matrix.append([float(x) for x in line.split()])

t = [[row[i] for row in matrix] for i in range(len(matrix[0]))]

for i in range(len(t)):
    for j in range(len(t[i])):
        if(round(t[i][j],precision) != round(SMSPEC.Data.DATA["DIMENS"][i][j],precision)):
            print(":Failed to read DIMENS matrix")
            exit()
print("Successfully read DIMENS matrix!")
