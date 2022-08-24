#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    int return_value = OK;
    if ((rows > 0) && (columns > 0)) {
        result->rows = rows;
        result->columns = columns;
        result->matrix = calloc(rows, sizeof(double *));
        for (int i = 0; i < result->rows; i++) {
            result->matrix[i] = calloc(columns, sizeof(double));
        }
    } else {
        return_value = INCORRECT_MATRIX;
    }
    return return_value;
}

void s21_remove_matrix(matrix_t *A) {
    for (int i = 0; i < A->rows; i++) {
        free(A->matrix[i]);
    }
    free(A->matrix);
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int return_value = SUCCESS;
    if (A->rows != B->rows || A->columns != B->columns || A->rows <= 0 ||
        A->columns <= 0 || B->rows <= 0 || B->columns <= 0) {
        return_value = FAILURE;
    } else {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-07) {
                    return_value = FAILURE;
                    break;
                }
            }
            if (return_value == FAILURE) break;
        }
    }
    return return_value;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int return_value = OK;
    if (!A || !B || !A->matrix || !B->matrix || A->rows <= 0 ||
        A->columns <= 0 || B->rows <= 0 || B->columns <= 0) {
        return_value = INCORRECT_MATRIX;
    } else if (A->columns != B->columns || A->rows != B->rows) {
        return_value = CALCULATION_ERROR;
    } else {
        s21_create_matrix(A->rows, A->columns, result);

        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
            }
        }
    }
    return return_value;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int return_value = OK;
    if (!A || !B || !A->matrix || !B->matrix || A->rows <= 0 ||
        A->columns <= 0 || B->rows <= 0 || B->columns <= 0) {
        return_value = INCORRECT_MATRIX;
    } else if (A->columns != B->columns || A->rows != B->rows ||
               !result->matrix) {
        return_value = CALCULATION_ERROR;
    } else {
        s21_create_matrix(A->rows, A->columns, result);

        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
            }
        }
    }
    return return_value;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    int return_value = OK;
    if (!A || !A->matrix || A->rows <= 0 || A->columns <= 0) {
        return_value = INCORRECT_MATRIX;
    } else {
        s21_create_matrix(A->rows, A->columns, result);

        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                result->matrix[i][j] = A->matrix[i][j] * number;
            }
        }
    }
    return return_value;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int return_value = OK;
    if (!A || !B || !A->matrix || !B->matrix || A->rows <= 0 ||
        A->columns <= 0 || B->rows <= 0 || B->columns <= 0) {
        return_value = INCORRECT_MATRIX;
    } else if (A->columns != B->rows || A->rows != B->columns) {
        return_value = CALCULATION_ERROR;
    } else {
        s21_create_matrix(A->rows, B->columns, result);

        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < B->columns; j++) {
                for (int k = 0; k < A->columns; k++) {
                    result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
                }
            }
        }
    }
    return return_value;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
    int return_value = OK;
    if (!A->matrix || A->rows <= 0 || A->columns <= 0) {
        return_value = INCORRECT_MATRIX;
    } else {
        s21_create_matrix(A->columns, A->rows, result);

        for (int i = 0; i < result->rows; i++) {
            for (int j = 0; j < result->columns; j++) {
                result->matrix[i][j] = A->matrix[j][i];
            }
        }
    }
    return return_value;
}

void find_minor(int i, int j, matrix_t A, matrix_t *result) {
    s21_create_matrix(A.rows - 1, A.columns - 1, result);
    int i_counter = 0, j_counter = 0;
    for (int k = 0; k < A.rows; k++) {
        if (k == i) continue;
        for (int l = 0; l < A.columns; l++) {
            if (l == j) continue;
            result->matrix[i_counter][j_counter] = A.matrix[k][l];
            j_counter++;
        }
        j_counter = 0;
        i_counter++;
    }
}

int s21_determinant(matrix_t *A, double *result) {
    int return_value = OK;
    if (!A || !A->matrix || !result || A->columns <= 0 || A->rows <= 0) {
        return_value = INCORRECT_MATRIX;
    } else if (A->columns != A->rows) {
        return_value = CALCULATION_ERROR;
    } else {
        if (A->rows == 1) {
            *result = A->matrix[0][0];
        } else if (A->rows == 2) {
            *result = A->matrix[0][0] * A->matrix[1][1] -
                      A->matrix[0][1] * A->matrix[1][0];
        } else {
            *result = 0;
            for (int i = 0; i < A->columns; i++) {
                matrix_t minor_matrix;
                find_minor(0, i, *A, &minor_matrix);
                double tmp_det;
                s21_determinant(&minor_matrix, &tmp_det);
                s21_remove_matrix(&minor_matrix);
                double tmp_res = pow(-1, 2 + i) * A->matrix[0][i] * tmp_det;
                *result += tmp_res;
            }
        }
    }
    return return_value;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
    int return_value = OK;
    if (!A || !A->matrix || !result || A->columns <= 1 || A->rows <= 1) {
        return_value = INCORRECT_MATRIX;
    } else if (A->columns != A->rows) {
        return_value = CALCULATION_ERROR;
    } else {
        s21_create_matrix(A->rows, A->columns, result);

        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                matrix_t minor_matrix;
                find_minor(i, j, *A, &minor_matrix);
                double determinant_value;
                s21_determinant(&minor_matrix, &determinant_value);
                s21_remove_matrix(&minor_matrix);
                determinant_value *= pow(-1, 2 + i + j);
                result->matrix[i][j] = determinant_value;
            }
        }
    }
    return return_value;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    int return_value = OK;
    if (!A || !A->matrix || !result || A->columns <= 1 || A->rows <= 1) {
        return_value = INCORRECT_MATRIX;
    } else if (A->rows != A->columns) {
        return_value = CALCULATION_ERROR;
    } else {
        double determ = 0;
        matrix_t tmp;
        matrix_t tmp1;
        s21_determinant(A, &determ);
        if (fabs(determ) > 1e-7) {
            s21_calc_complements(A, &tmp);
            s21_transpose(&tmp, &tmp1);
            s21_remove_matrix(&tmp);
            s21_mult_number(&tmp1, 1. / fabs(determ), result);
            s21_remove_matrix(&tmp1);
            for (int i = 0; i < result->rows; i++) {
                for (int j = 0; j < result->columns; j++) {
                    result->matrix[i][j] *= -1;
                }
            }
        } else {
            return_value = CALCULATION_ERROR;
        }
    }

    return return_value;
}
