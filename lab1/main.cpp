#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

// Сигмоидальная функция активации
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// Производная сигмоида для обратного распространения ошибки
double sigmoid_derivative(double x) {
    return x * (1.0 - x);
}

class NeuralNetwork {
public:
    // Конструктор: определение структуры сети
    NeuralNetwork(int input_size, int hidden_size, int output_size) {
        this->input_size = input_size;
        this->hidden_size = hidden_size;
        this->output_size = output_size;

        // Инициализация весов для входного и скрытого слоя
        input_hidden_weights.resize(input_size, std::vector<double>(hidden_size));
        hidden_output_weights.resize(hidden_size, std::vector<double>(output_size));

        // Случайная инициализация весов
        initialize_weights();
    }

    // Обучение сети методом обратного распространения ошибки
    void train(std::vector<double> inputs, std::vector<double> targets, double learning_rate, int epochs) {
        for (int epoch = 0; epoch < epochs; ++epoch) {
            // Прямое распространение (forward propagation)
            std::vector<double> hidden_outputs = compute_layer(inputs, input_hidden_weights);
            std::vector<double> final_outputs = compute_layer(hidden_outputs, hidden_output_weights);

            // Вычисление ошибки (среднеквадратичная ошибка)
            double total_error = 0.0;
            for (int i = 0; i < output_size; ++i) {
                total_error += 0.5 * std::pow(targets[i] - final_outputs[i], 2);
            }

            // Вывод ошибки для каждой эпохи
            /*if (epoch % 100 == 0) {
                std::cout << "Эпоха: " << epoch + 1 << ", Ошибка: " << total_error << std::endl;
            }*/

            // Обратное распространение ошибки (backpropagation)
            std::vector<double> output_errors(output_size);
            for (int i = 0; i < output_size; ++i) {
                output_errors[i] = targets[i] - final_outputs[i];
            }

            // Корректировка весов между скрытым и выходным слоем
            for (int i = 0; i < hidden_size; ++i) {
                for (int j = 0; j < output_size; ++j) {
                    double delta = output_errors[j] * sigmoid_derivative(final_outputs[j]);
                    hidden_output_weights[i][j] += learning_rate * delta * hidden_outputs[i];
                }
            }

            // Корректировка весов между входным и скрытым слоем
            std::vector<double> hidden_errors(hidden_size);
            for (int i = 0; i < hidden_size; ++i) {
                for (int j = 0; j < output_size; ++j) {
                    hidden_errors[i] += output_errors[j] * hidden_output_weights[i][j];
                }
            }

            for (int i = 0; i < input_size; ++i) {
                for (int j = 0; j < hidden_size; ++j) {
                    double delta = hidden_errors[j] * sigmoid_derivative(hidden_outputs[j]);
                    input_hidden_weights[i][j] += learning_rate * delta * inputs[i];
                }
            }
        }
    }

    // Прямое распространение для предсказания
    std::vector<double> predict(std::vector<double> inputs) {
        std::vector<double> hidden_outputs = compute_layer(inputs, input_hidden_weights);
        return compute_layer(hidden_outputs, hidden_output_weights);
    }

private:
    int input_size;
    int hidden_size;
    int output_size;

    std::vector<std::vector<double>> input_hidden_weights;
    std::vector<std::vector<double>> hidden_output_weights;

    // Функция для инициализации весов случайными значениями
    void initialize_weights() {
        srand(static_cast<unsigned int>(time(0)));
        for (int i = 0; i < input_size; ++i) {
            for (int j = 0; j < hidden_size; ++j) {
                input_hidden_weights[i][j] = (rand() % 100) / 100.0 - 0.5;
            }
        }
        for (int i = 0; i < hidden_size; ++i) {
            for (int j = 0; j < output_size; ++j) {
                hidden_output_weights[i][j] = (rand() % 100) / 100.0 - 0.5;
            }
        }
    }

    // Функция для вычисления выхода слоя
    std::vector<double> compute_layer(std::vector<double> inputs, std::vector<std::vector<double>> weights) {
        std::vector<double> outputs(weights[0].size(), 0.0);
        for (int j = 0; j < weights[0].size(); ++j) {
            for (int i = 0; i < inputs.size(); ++i) {
                outputs[j] += inputs[i] * weights[i][j];
            }
            outputs[j] = sigmoid(outputs[j]);
        }
        return outputs;
    }
};

// Функция для чтения данных из файлов и обучения сети
void load_and_train_from_directory(NeuralNetwork& nn, const std::string& directory, const std::vector<double>& target_output, double learning_rate, int epochs) {
    // Проход по файлам в директории
    for (const auto& entry : fs::directory_iterator(directory)) {
        std::ifstream file(entry.path());

        if (!file.is_open()) {
            std::cerr << "Не удалось открыть файл: " << entry.path() << std::endl;
            continue;
        }

        std::vector<double> inputs;
        double value;

        // Чтение содержимого файла (7x7 пикселей)
        for (int i = 0; i < 7 * 7; ++i) {
            file >> value;
            inputs.push_back(value);
        }

        // Закрываем файл
        file.close();

        // Обучение нейронной сети на данных из этого файла
        nn.train(inputs, target_output, learning_rate, epochs);
    }
}

void load_and_valid_from_directory(NeuralNetwork& nn, const std::string& directory, const std::string& figure) {
    // Проход по файлам в директории
    for (const auto& entry : fs::directory_iterator(directory)) {
        std::ifstream file(entry.path());

        if (!file.is_open()) {
            std::cerr << "Не удалось открыть файл: " << entry.path() << std::endl;
            continue;
        }

        std::vector<double> inputs;
        double value;

        // Чтение содержимого файла (7x7 пикселей)
        for (int i = 0; i < 7 * 7; ++i) {
            file >> value;
            inputs.push_back(value);
        }

        // Закрываем файл
        file.close();

        // Обучение нейронной сети на данных из этого файла
        std::vector<double> prediction = nn.predict(inputs);

        std::cout << "Предсказание для " + figure + ": ";
        for (double p : prediction) {
            std::cout << p << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    // Инициализация сети: 49 входов, 5 нейронов в скрытом слое, 3 выхода (круг, квадрат, треугольник)
    NeuralNetwork nn(49, 5, 3);

    // Пример целевых выходных данных для обучения (например, [1, 0, 0] для круга)
    std::vector<double> target_output_circle = {1, 0, 0};
    std::vector<double> target_output_square = {0, 1, 0};
    std::vector<double> target_output_triangle = {0, 0, 1};

    // Количество эпох обучения
    int epochs = 1000;
    double learning_rate = 0.01;

    // Путь к директории с обучающими файлами
    std::string circle_train_directory = "/home/etoxto/Documents/itmo/ovs/lab1/train/circle";
    std::string circle_valid_directory = "/home/etoxto/Documents/itmo/ovs/lab1/valid/circle";

    std::string square_train_directory = "/home/etoxto/Documents/itmo/ovs/lab1/train/square";
    std::string square_valid_directory = "/home/etoxto/Documents/itmo/ovs/lab1/valid/square";

    std::string triangle_train_directory = "/home/etoxto/Documents/itmo/ovs/lab1/train/triangle";
    std::string triangle_valid_directory = "/home/etoxto/Documents/itmo/ovs/lab1/valid/triangle";

    // Обучение сети на данных из файлов
    load_and_train_from_directory(nn, circle_train_directory, target_output_circle, learning_rate, epochs);
    load_and_valid_from_directory(nn, circle_valid_directory, "круга");

    load_and_train_from_directory(nn, square_train_directory, target_output_square, learning_rate, epochs);
    load_and_valid_from_directory(nn, square_valid_directory, "квадрата");

    load_and_train_from_directory(nn, triangle_train_directory, target_output_triangle, learning_rate, epochs);
    load_and_valid_from_directory(nn, triangle_valid_directory, "треугольника");

    return 0;
}
