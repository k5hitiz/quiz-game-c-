#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>
#include "json.hpp"
#include "utils.h"

using json = nlohmann::json;
using namespace std;
using namespace chrono;

struct Question {
    string text;
    vector<string> options;
    int correct;
};

vector<Question> loadQuestions(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << " file." << endl;
        exit(1);
    }

    json j;
    try {
        file >> j;
    } catch (const json::parse_error& e) {
        cerr << "JSON parse error: " << e.what() << endl;
        exit(1);
    }

    vector<Question> questions;
    for (auto& item : j) {
        questions.push_back({ item["question"], item["options"], item["answer"] });
    }
    return questions;
}

int main() {
  vector<Question> questions = loadQuestions("C:\\Users\\kshitiz sharma\\Music\\quiz-game_fixed\\output\\questions.json");


    int score = 0;
    int attempts = 0;
    vector<double> times;

    for (size_t i = 0; i < questions.size(); ++i) {
        const Question& q = questions[i];
        cout << "\nQ" << i + 1 << ": " << q.text << endl;

        for (size_t j = 0; j < q.options.size(); ++j)
            cout << j + 1 << ". " << q.options[j] << endl;

        auto start = steady_clock::now();
        int choice;
        cout << "Your answer (1-" << q.options.size() << "): ";
        cin >> choice;
        auto end = steady_clock::now();

        double timeTaken = duration<double>(end - start).count();
        times.push_back(timeTaken);
        attempts++;

        if (choice - 1 == q.correct) {
            cout << "✅ Correct!\n";
            score++;
        } else {
            cout << " Wrong! Correct answer was: " << q.options[q.correct] << "\n";
            cout << " Score: " << score<<"\n";
            
        }

        cout << "Time taken: " << fixed << setprecision(2) << timeTaken << "s\n";
    }

    // Final summary
    cout << "\n======  Final Summary ======\n";
     cout << "====== :) ====== \n";
    cout << "Score: " << score << "/" << questions.size() << endl;
    cout << "Attempts: " << attempts << endl;
    float per0= (score*100)/attempts;
    cout<<"Percentage:"<< per0<<"percent \n";
    double totalTime = 0;
    for (double t : times) totalTime += t;
    cout << "Avg Time per Question:--" << totalTime / questions.size() << "s\n";

    return 0;
}