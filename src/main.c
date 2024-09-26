#include <matrix.h>
#include <time.h>
#include <vector.h>
#include <neural_network.h>
#include <utils.h>

#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

void shuffle(int* array, int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand_double_range(0, i);
        swap(&array[i], &array[j]);
    }
}

double f(double x) {
    return 0.4 * x + 0.2;
}

// This is a test main
int main(void) {
    struct timeval tm;
    gettimeofday(&tm, NULL);
    srandom(tm.tv_sec + tm.tv_usec * 1000000ul);

    NeuralNetwork* nn = new_neural_network(2, 3, 1);
    Matrix* m1 = new_uninitialized_matrix(2, 1);
    m1->buffer[0][0] = 1.0;
    m1->buffer[1][0] = 0.5;
    Matrix* m2 = new_uninitialized_matrix(2, 1);
    m2->buffer[0][0] = 0.18;
    m2->buffer[1][0] = 0.34;

    forward_pass(nn, m1);
    printf("single m1:\n");
    print_matrix(nn->output_layer);

    forward_pass(nn, m2);
    printf("single m2:\n");
    print_matrix(nn->output_layer);

    free(m2);
    m1 = new_uninitialized_matrix(2, 2);
    m1->buffer[0][0] = 1.0;
    m1->buffer[1][0] = 0.5;
    m1->buffer[0][1] = 0.18;
    m1->buffer[1][1] = 0.34;
    set_batch_size(nn, 2);

    forward_pass(nn, m1);
    printf("double m:\n");
    print_matrix(nn->output_layer);

    free_matrix(m1);
    free_neural_network(nn);
    return 0;
}

/*
int main(void) {
    struct timeval tm;
    gettimeofday(&tm, NULL);
    srandom(tm.tv_sec + tm.tv_usec * 1000000ul);

    size_t epochs = 1000;
    NeuralNetwork* nn = new_neural_network(1, 3, 1);

    Vector* input = new_uninitialized_vector(1);
    Vector* expected_output = new_uninitialized_vector(1);

    int Xs[epochs];
    for (size_t i = 0; i < epochs; i++) {
        Xs[i] = i;
    }
    shuffle(Xs, epochs);
    
    double x;
    double y;
    for (size_t i = 0; i < epochs; i++) {
        if (i % 100 == 0)
            printf("training epoch = %lu\n", i);

        x = (double) Xs[i] / epochs;
        y = f(x);

        input->buffer[0] = x;
        expected_output->buffer[0] = y;
        forward_pass(nn, input);
        back_propagation(nn, input, expected_output);
    }

    double prediction;
    printf("testing training results:\n");
    x = 0.1;
    y = f(x);
    input->buffer[0] = x;
    forward_pass(nn, input);
    prediction = nn->output_layer->buffer[0];
    printf("x = %f, f(x) = %f, model predicted : %f\n", x, y, prediction);
    x = 0.5;
    y = f(x);
    input->buffer[0] = x;
    forward_pass(nn, input);
    prediction = nn->output_layer->buffer[0];
    printf("x = %f, f(x) = %f, model predicted : %f\n", x, y, prediction);
    x = 0.73;
    y = f(x);
    input->buffer[0] = x;
    forward_pass(nn, input);
    prediction = nn->output_layer->buffer[0];
    printf("x = %f, f(x) = %f, model predicted : %f\n", x, y, prediction);


    free_vector(input);
    free_vector(expected_output);
    free_neural_network(nn);
    return 0;
}
*/
