#ifndef READ_ECL_C_H
#define READ_ECL_C_H

#if defined(__cplusplus)
extern "C" {
#endif

void Create_Instance_C(const char *filename);

void value2D(const char *key, double **data);

void value1D(const char *key, int col, double *data);

void name2D(const char *key, char ***data);

void name1D(const char *key, int col, char **data);

#if defined(__cplusplus)
}
#endif

#endif // READ_ECL_C_H
