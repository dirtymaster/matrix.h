# matrix.h
1. [In English](#description)
2. [На русском](#описание)
### Description
Implementation of the matrix.h library for working with matrices. The library is developed in C language of C11 standard using gcc compiler.

### Matrix structure in C language
```c
typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;
```

### Matrix operations

All operations (except matrix comparison) return the resulting code:
- 0 - OK
- 1 - Error, incorrect matrix
- 2 - Calculation error (mismatched matrix sizes; matrix for which calculations cannot be performed, etc.)

```
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
```
***

### Описание
Реализация библиотеки matrix.h для работы с матрицами. Библиотека разработана на языке C стандарта C11 с использованием компилятора gcc.

### Структура матрицы на языке C
```c
typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;
```

### Операции над матрицами
Все операции (кроме сравнения матриц) возвращают результирующий код:
- 0 - OK
- 1 - Ошибка, некорректная матрица
- 2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой нельзя провести вычисления и т.д.)

```
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
```
