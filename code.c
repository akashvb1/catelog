#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
long long decode_value(const char* value, int base) {
    return strtoll(value, NULL, base); 
}
double lagrange_interpolation(int* x, long long* y, int k) {
    double c = 0.0;
    for (int i = 0; i < k; i++) {
        double term = y[i];
        for (int j = 0; j < k; j++) {
            if (i != j) {
                term *= (0.0 - x[j]) / (x[i] - x[j]); 
            }
        }
        c += term;
    }
    return c;
}
int is_point_valid(int* x, long long* y, int k, int idx) {
    double actual_y = lagrange_interpolation(x, y, k); 
    return fabs(actual_y - y[idx]) < 1e-6; 
}

int main() {
    const char* testcase1 = "{\"keys\": {\"n\": 4, \"k\": 3}, \"1\": {\"base\": \"10\", \"value\": \"4\"}, \"2\": {\"base\": \"2\", \"value\": \"111\"}, \"3\": {\"base\": \"10\", \"value\": \"12\"}, \"6\": {\"base\": \"4\", \"value\": \"213\"}}";
    const char* testcase2 = "{\"keys\": {\"n\": 9, \"k\": 6}, \"1\": {\"base\": \"10\", \"value\": \"28735619723837\"}, \"2\": {\"base\": \"16\", \"value\": \"1A228867F0CA\"}, \"3\": {\"base\": \"12\", \"value\": \"32811A4AA0B7B\"}, \"4\": {\"base\": \"11\", \"value\": \"917978721331A\"}, \"5\": {\"base\": \"16\", \"value\": \"1A22886782E1\"}, \"6\": {\"base\": \"10\", \"value\": \"28735619654702\"}, \"7\": {\"base\": \"14\", \"value\": \"71AB5070CC4B\"}, \"8\": {\"base\": \"9\", \"value\": \"122662581541670\"}, \"9\": {\"base\": \"8\", \"value\": \"642121030037605\"}}";
    int x1[] = {1, 2, 3, 6}; 
    long long y1[] = {4, 7, 12, 39}; 
    int k1 = 3;  // m+1
    double secret1 = lagrange_interpolation(x1, y1, k1);
    
    printf("Secret for the first testcase: %.0f\n", secret1);
    int x2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; 
    long long y2[] = {28735619723837LL, 0x1A228867F0CA, 0x32811A4AA0B7B, 0x917978721331A, 0x1A22886782E1, 28735619654702LL, 0x71AB5070CC4B, 0x122662581541670LL, 0x642121030037605LL};  // Decoded Y values
    
    int k2 = 6;  
    double secret2 = lagrange_interpolation(x2, y2, k2);
    
    printf("Secret for the second testcase: %.0f\n", secret2);
    for (int i = 0; i < 9; i++) {
        if (!is_point_valid(x2, y2, k2, i)) {
            printf("Point (%d, %lld) is an imposter\n", x2[i], y2[i]);
        }
    }
    return 0;
}
