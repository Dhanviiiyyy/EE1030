#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define EPSILON 1e-8
#define MAX_ITER 1000

#define GET(A, n, i, j) (A[(i) * (n) + (j)])
#define SET(A, n, i, j, value) (A[(i) * (n) + (j)] = (value))

// Helper functions
double sign(double x) {
    return (x > 0) - (x < 0);
}

// Access elements in a 1D representation of the NxN matrix
double get_element(double *matrix, int N, int row, int col) {
    return matrix[row * N + col];
}

void set_element(double *matrix, int N, int row, int col, double value) {
    matrix[row * N + col] = value;
}

// Check if a matrix is symmetric
int is_symmetric(double *matrix, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (fabs(get_element(matrix, N, i, j) - get_element(matrix, N, j, i)) > EPSILON) {
                return 0;
            }
        }
    }
    return 1;
}

// Givens rotation for QR decomposition (for symmetric matrices)
void apply_givens_rotation(double *matrix, int N, int p, int q, double c, double s) {
    for (int i = 0; i < N; i++) {
        double tmp1 = c * get_element(matrix, N, i, p) - s * get_element(matrix, N, i, q);
        double tmp2 = s * get_element(matrix, N, i, p) + c * get_element(matrix, N, i, q);
        set_element(matrix, N, i, p, tmp1);
        set_element(matrix, N, i, q, tmp2);
    }
    for (int i = 0; i < N; i++) {
        double tmp1 = c * get_element(matrix, N, p, i) - s * get_element(matrix, N, q, i);
        double tmp2 = s * get_element(matrix, N, p, i) + c * get_element(matrix, N, q, i);
        set_element(matrix, N, p, i, tmp1);
        set_element(matrix, N, q, i, tmp2);
    }
}

// Perform tridiagonalization for symmetric matrices
void tridiagonalize(double *matrix, int N) {
    for (int k = 0; k < N - 2; k++) {
        double norm = 0;
        for (int i = k + 1; i < N; i++) norm += get_element(matrix, N, i, k) * get_element(matrix, N, i, k);
        norm = sqrt(norm);

        double alpha = -sign(get_element(matrix, N, k + 1, k)) * norm;
        double r = sqrt(0.5 * (alpha * alpha - get_element(matrix, N, k + 1, k) * alpha));
        double v[N];
        for (int i = 0; i < N; i++) v[i] = 0;
        v[k + 1] = (get_element(matrix, N, k + 1, k) - alpha) / (2 * r);
        for (int i = k + 2; i < N; i++) v[i] = get_element(matrix, N, i, k) / (2 * r);

        // Apply the Householder transformation
        for (int i = k; i < N; i++) {
            double sum = 0;
            for (int j = k; j < N; j++) sum += get_element(matrix, N, i, j) * v[j];
            for (int j = k; j < N; j++) set_element(matrix, N, i, j, get_element(matrix, N, i, j) - 2 * sum * v[j]);
        }
        for (int i = 0; i < N; i++) {
            double sum = 0;
            for (int j = k; j < N; j++) sum += v[j] * get_element(matrix, N, j, i);
            for (int j = k; j < N; j++) set_element(matrix, N, j, i, get_element(matrix, N, j, i) - 2 * sum * v[j]);
        }
    }
}

// Perform QR iteration for eigenvalues
void qr_algorithm(double *matrix, int N, double eigenvalues[]) {
    double A[N * N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            set_element(A, N, i, j, get_element(matrix, N, i, j));

    for (int iter = 0; iter < MAX_ITER; iter++) {
        // Apply Givens rotations to create a tridiagonal form
        for (int i = 0; i < N - 1; i++) {
            double a = get_element(A, N, i, i);
            double b = get_element(A, N, i + 1, i);
            double r = sqrt(a * a + b * b);
            double c = a / r;
            double s = -b / r;

            apply_givens_rotation(A, N, i, i + 1, c, s);
        }

        // Check for convergence
        double off_diagonal_sum = 0;
        for (int i = 0; i < N - 1; i++) {
            off_diagonal_sum += fabs(get_element(A, N, i, i + 1));
        }
        if (off_diagonal_sum < EPSILON) break;
    }

    // Eigenvalues are the diagonal elements after convergence
    for (int i = 0; i < N; i++) {
        eigenvalues[i] = get_element(A, N, i, i);
    }
}

// Calculate eigenvalues for 1x1 or 2x2 complex matrices
void eigenvalues_small(double complex *A, int n) {
    if (n == 1) {
        printf("Eigenvalue: %.10f + %.10fi\n", creal(GET(A, n, 0, 0)), cimag(GET(A, n, 0, 0)));
    } else if (n == 2) {
        double complex trace = GET(A, n, 0, 0) + GET(A, n, 1, 1); 
        double complex determinant = GET(A, n, 0, 0) * GET(A, n, 1, 1) - GET(A, n, 0, 1) * GET(A, n, 1, 0);
        double complex discriminant = csqrt(trace * trace - 4.0 * determinant);
        
        double complex lambda1 = (trace + discriminant) / 2.0;
        double complex lambda2 = (trace - discriminant) / 2.0;

        printf("Eigenvalues: %.10f + %.10fi, %.10f + %.10fi\n", 
               creal(lambda1), cimag(lambda1), creal(lambda2), cimag(lambda2));
    }
}

int main() {
    int N;
    printf("Enter the size of the matrix (N): ");
    scanf("%d", &N);

    if (N <= 0) {
        printf("Invalid matrix size.\n");
        return 1;
    }

    if (N == 1 || N == 2) {
        double complex *A = (double complex *)malloc(N * N * sizeof(double complex));

        if (A == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }

        printf("Enter the elements of the matrix (real and imaginary parts):\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                double real, imag;
                printf("A[%d][%d] = ", i, j);
                scanf("%lf %lf", &real, &imag);
                SET(A, N, i, j, real + imag * I);
            }
        }

        eigenvalues_small(A, N);
        free(A);
        return 0;
    }

    double *matrix = (double *)malloc(N * N * sizeof(double));
    if (matrix == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter the elements of the real symmetric matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double value;
            printf("A[%d][%d] = ", i, j);
            scanf("%lf", &value);
            set_element(matrix, N, i, j, value);
        }
    }

    double eigenvalues[N];

    // Check if the matrix is symmetric and tridiagonalize if it is
    if (is_symmetric(matrix, N)) {
        printf("Matrix is symmetric. Optimizing for symmetric matrix.\n");
        tridiagonalize(matrix, N);
    } else {
        printf("Matrix is not symmetric. Using general QR algorithm.\n");
    }

    // Apply QR algorithm to find eigenvalues
    qr_algorithm(matrix, N, eigenvalues);

    printf("Eigenvalues:\n");
    for (int i = 0; i < N; i++) {
        printf("%.6f\n", eigenvalues[i]);
    }

    free(matrix);
    return 0;
}


