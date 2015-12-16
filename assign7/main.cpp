#include <iostream>
#include <cstdlib>
#include <ctime>

const int NULL_FRAME = -1;
const int NUM_L_FRAMES = 250;
const int MAX_P_FRAMES = 100;
const int NUM_SEQUENCES = 100;
const int SEQUENCE_SIZE = 1000;

int countFaults(int* sequence, int* page_table, int* main_memory, int size);

int main() {
    // Print the opening display
    std::cout
        << "--- Belady's Anomaly Simulator ---" << std::endl
        << "# of sequences tested: " << NUM_SEQUENCES << std::endl
        << "Length of memory reference string: " << SEQUENCE_SIZE << std::endl
        << "Frames of physical memory: " << MAX_P_FRAMES << std::endl
        << "Frames of logical memory: " << NUM_L_FRAMES << std::endl
        << std::endl;

    // Memory simulation objects
    int sequences[NUM_SEQUENCES][SEQUENCE_SIZE];
    int page_table[NUM_L_FRAMES];
    int main_memory[MAX_P_FRAMES];
    int anomalies = 0;

    // Generate the random sequences
    std::srand(std::time(NULL)); // Seed the time
    for (int i = 0; i < NUM_SEQUENCES; ++i) {
        for (int j = 0; j < SEQUENCE_SIZE; ++j) {
            sequences[i][j] = std::rand() % NUM_L_FRAMES;
        }
    }

    // Test each sequence
    for (int i = 0; i < NUM_SEQUENCES; ++i) {
        int faults[MAX_P_FRAMES];
        faults[0] = SEQUENCE_SIZE;
        for (int size = 1; size < MAX_P_FRAMES; ++size) {
            faults[size] = countFaults(sequences[i], page_table, main_memory, size + 1);
            if (faults[size] > faults[size - 1]) {
                ++anomalies;
                std::cout
                    << "Anomaly Discovered!" << std::endl
                    << "  Sequence: " << i + 1 << std::endl
                    << "  Page Faults: " << faults[size - 1] << " @ Frame Size: " << size << std::endl
                    << "  Page Faults: " << faults[size] << " @ Frame Size: " << size + 1 << std::endl;
            }
        }
    }

    std::cout << std::endl
        << "Anomaly detected " << anomalies << " time(s)." << std::endl
        << std::endl;

    return 0;
}

int countFaults(int* sequence, int* page_table, int* main_memory, int size) {
    int faults = 0, next = 0;

    // Clear the page table and RAM
    for (int i = 0; i < NUM_L_FRAMES; ++i) { page_table[i] = NULL_FRAME; }
    for (int i = 0; i < MAX_P_FRAMES; ++i) { main_memory[i] = NULL_FRAME; }

    // Count the number of faults
    for (int i = 0; i < SEQUENCE_SIZE; ++i) {
        if (page_table[sequence[i]] == NULL_FRAME) {
            ++faults;
            int old = main_memory[next];
            page_table[sequence[i]] = next;
            main_memory[next] = sequence[i];

            // Remove the old reference
            if (old != NULL_FRAME) {
                page_table[old] = NULL_FRAME;
            }

            // Increment the FIFO position
            next = (next + 1) % size;
        }
    }

    return faults;
}
