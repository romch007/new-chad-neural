/* New Chad Neural - C library to train neural networks
 * Copyright (C) 2024 Lucas Logan
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef NCN_NEURAL_NETWORK_H
#define NCN_NEURAL_NETWORK_H

#include <common_defs.h>
#include <vector.h>
#include <matrix.h>

#include <stddef.h>

typedef struct {
    size_t input_size;
    Matrix* hidden_layer;
    Matrix* output_layer;

    Matrix* input_hidden_weights;
    Matrix* hidden_output_weights;

    Vector* hidden_biases;
    Vector* output_biases;

    activation_function activation_function;
    activation_function activation_function_derivative;
} NeuralNetwork;

NeuralNetwork* new_neural_network(size_t num_inputs, size_t num_hidden, size_t num_outputs);
void free_neural_network(NeuralNetwork* nn);

void set_activation_functions(NeuralNetwork* nn, activation_function af, activation_function daf);
void set_batch_size(NeuralNetwork* nn, size_t batch_size);

void forward_pass(NeuralNetwork* nn, Matrix* inputs);
void back_propagation(NeuralNetwork* nn, Matrix* inputs, Matrix* expected_outputs, double learning_rate);

int save_neural_network(NeuralNetwork* nn, const char* filename);
NeuralNetwork* new_neural_network_from_file(const char* filename);

#endif // NCN_NEURAL_NETWORK_H
