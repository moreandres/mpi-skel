#define SIZE 2048

float a[SIZE][SIZE];
float b[SIZE][SIZE];
float c[SIZE][SIZE];

int main()
{
	int i, j, k;

	for (i = 0; i < SIZE; ++i) {
		for (j = 0; j < SIZE; ++j) {
			a[i][j] = (float)i + j;
			b[i][j] = (float)i - j;
			c[i][j] = 0.0f;
		}
	}

#pragma omp parallel for shared(a,b,c) 
	for (i = 0; i < SIZE; ++i) {
		for (j = 0; j < SIZE; ++j) {
			for (k = 0; k < SIZE; ++k) {
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}

	return 0;
}
