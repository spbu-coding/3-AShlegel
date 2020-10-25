#include <stdio.h>
#include <math.h>

void calculate_double(char key) {
    double x_correct = 1.0, y_correct = 1.0, x, y, delta = 0.0001;
    int count = 0;
    double err = 0.000001;
    switch(key){
        case '1':
            while (count < 22){
                y = (2.0001 + delta - 2.0) / 0.0001;
                x = 2.0 - y;
                fprintf(stdout, "%d\t%lf\t%lf\n", count, x, y);
                count++;
                delta = delta / 2.0f;
            }
            break;
        case '5':
            while (count >= 0){
                delta = 0.0001;
                count = 0;
                while (count >= 0){
                    y = (2.0001 + delta - 2.0) / 0.0001;
                    x = 2.0 - y;
                    if (sqrt(pow(fabs(x - x_correct), 2) + pow(fabs(y - y_correct), 2)) <= err)
                        break;
                    count++;
                    delta = delta / 2.0;
                }
                printf("%d\t\t %0.20lf\n", count, err);
                err /= 10;
            }
            break;
        default:
            while (count >= 0){
                y = (2.0001 + delta - 2.0f) / 0.0001;
                x = 2.0 - y;

                if (sqrtf(powf(fabsf(x - x_correct), 2) + powf(fabsf(y - y_correct), 2)) <= 0.000001)
                    break;
                count++;
                delta = delta / 2.0;
            }
            fprintf(stdout, "%d\n", count > 0? count : -1);
            break;
    }
}

float roundoff_err(float a, float b){
    float x, y, b_virtual, a_virtual, b_roundoff, a_roundoff;
    x = a + b;
    b_virtual = x - a;
    a_virtual = x - b_virtual;
    b_roundoff = b - b_virtual;
    a_roundoff = a - a_virtual;
    y = a_roundoff + b_roundoff;
    return y;
}

void calculate_float(char key) {
    float x_correct = 1.0f, y_correct = 1.0f, x, y, delta = 0.0001f;
    int count = 0;
    switch(key){
        case '1':
            while (count < 22){
                y = (2.0001f + delta - 2.0f) / 0.0001f;
                x = 2.0f - y;
                fprintf(stdout, "%d\t%f\t%f\n", count, x, y);
                count++;
                delta = delta / 2.0f;
            }
            break;
        case '2':
            while (count < 22){
                y = (2.0001f + delta - 2.0f) / 0.0001f;
                x = 2.0f - y;
                fprintf(stdout, "%d\t%.20f\t%.20f\n", count, x, y);
                count++;
                delta = delta / 2.0f;
            }
            break;
        case '3':
            while (count < 12){
                y = (2.0001f + delta - 2.0f) / 0.0001f;
                x = 2.0f - y;
                fprintf(stdout, "%d\t%.20f\t%.20f\t%.20f\n", count, 2.0001f + delta, 2.0001f + delta - 2.0f, y);
                count++;
                delta = delta / 2.0f;
            }
            break;
        case '4':
            while (count < 16){
                y = (2.0001f + delta - 2.0f) / 0.0001f;
                x = 2.0f - y;
                float err = roundoff_err(2.0001f, delta);
                printf("%d\t%.20f\t%.20f\t  %d\n", count, fabsf(err), delta, fabsf(err) == delta);
                count++;
                delta = delta / 2.0f;
            }
            break;
        default:
            while (count >= 0){
                y = (2.0001f + delta - 2.0f) / 0.0001f;
                x = 2.0f - y;

                if (sqrtf(powf(fabsf(x - x_correct), 2) + powf(fabsf(y - y_correct), 2)) <= 0.000001f)
                    break;
                count++;
                delta = delta / 2.0f;
            }
            fprintf(stdout, "%d\n", count > 0? count : -1);
            break;
    }
}

void integrate(char key){
    switch(key){
        case '1':
            fprintf(stdout, "count\tx_double\ty_double\n\n");
            calculate_double('1');
            fprintf(stdout, "\ncount\tx_float \ty_float\n\n");
            calculate_float('1');
            break;
        case '2':
            fprintf(stdout, "count\tx_float \t\ty_double\n\n");
            calculate_float('2');
            break;
        case '3':
            fprintf(stdout, "count\tsum     \t\tsub     \t\tdiv\n\n");
            calculate_float('3');
            break;
        case '4':
            fprintf(stdout, "count\terror\t\t\tdelta\t\t\t  equal\n\n");
            calculate_float('4');
            break;
        case '5':
            fprintf(stdout, "exit count\tallowable err\n\n");
            calculate_double('5');
            break;
        default:
            fprintf(stdout, "exit count double\t");
            calculate_double('0');
            fprintf(stdout, "exit count float \t");
            calculate_float('0');
            break;
    }
}

int main(int argc, char **argv){
    if (argc <= 1)
        integrate('0');
    else
        integrate(argv[1][0]);
    return 0;
}
