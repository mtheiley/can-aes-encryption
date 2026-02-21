#include <iostream>
#include <cstdint>
#include <chrono>

#include "matrix.hpp"
#include "aes128.hpp"

#include <cstdint>
#include <random>
#include <cassert>
#include <fstream>
#include <thread>
#include <algorithm>
#include <cmath>

struct TickConverter {
    uint64_t frequency;

    TickConverter() {
        // Read the fixed frequency (CNTFRQ_EL0) once at startup
        asm volatile("mrs %0, cntfrq_el0" : "=r"(frequency));
    }

    uint64_t ticks_to_ns(uint64_t ticks) const {
        // Using __int128 to prevent overflow during the multiplication
        return (unsigned __int128)ticks * 1000000000 / frequency;
    }
};

inline uint64_t __rdtscp() {
    uint64_t val;
    // ISB flushes the pipeline to ensure previous instructions are finished.
    // The "memory" clobber prevents the COMPILER from reordering code around this.
    asm volatile("isb\n"
                 "mrs %0, cntvct_el0" 
                 : "=r"(val) 
                 : 
                 : "memory");
    return val;
}

#include <mach/mach.h>
#include <mach/thread_policy.h>
#include <pthread.h>

class BenchShield {
public:
    BenchShield() {
        // 1. High-level Quality of Service
        pthread_set_qos_class_self_np(QOS_CLASS_USER_INTERACTIVE, 0);

        // 2. Disable "Fair Share" (No timeslicing)
        thread_extended_policy_data_t extended_policy = { .timeshare = 0 };
        thread_policy_set(mach_thread_self(), THREAD_EXTENDED_POLICY, 
                          (thread_policy_t)&extended_policy, THREAD_EXTENDED_POLICY_COUNT);

        // 3. AFFINITY: This is the "glue" that keeps you on one core cluster
        thread_affinity_policy_data_t affinity_policy = { 1 }; // Tag '1' for P-cores
        thread_policy_set(mach_thread_self(), THREAD_AFFINITY_POLICY, 
                          (thread_policy_t)&affinity_policy, THREAD_AFFINITY_POLICY_COUNT);

        // 4. Real-Time Constraints (The heavy hitter)
        thread_time_constraint_policy_data_t policy;
        policy.period = 100000;      
        policy.computation = 95000; // Ask for 95% to avoid the "hogging" penalty
        policy.constraint = 95000;    
        policy.preemptible = FALSE;   

        thread_policy_set(mach_thread_self(), THREAD_TIME_CONSTRAINT_POLICY, 
                          (thread_policy_t)&policy, THREAD_TIME_CONSTRAINT_POLICY_COUNT);
    }

    ~BenchShield() {
        // Return to default behavior to avoid starving the OS
        pthread_set_qos_class_self_np(QOS_CLASS_DEFAULT, 0);
        
        // Clearing Mach constraints (revert to standard throughput)
        thread_standard_policy_data_t policy = {0};
        thread_policy_set(mach_thread_self(), 
                          THREAD_STANDARD_POLICY, 
                          (thread_policy_t)&policy, 
                          THREAD_STANDARD_POLICY_COUNT);
    }
};

uint8_t randomChar() {
    // 'static' ensures these are initialized only once for the life of the program
    static std::random_device rd;
    static std::mt19937 gen(rd());
    
    // Limits range to printable ASCII characters (Space to '~')
    // Use (0, 255) if you want the full range of a uint8_t
    static std::uniform_int_distribution<int> dist(32, 126);

    return static_cast<uint8_t>(dist(gen));
}

matrix::Matrix<uint8_t, 4, 4> genRandom() {
    return matrix::Matrix<uint8_t, 4, 4>({
        {randomChar(), randomChar(), randomChar(), randomChar()},
        {randomChar(), randomChar(), randomChar(), randomChar()},
        {randomChar(), randomChar(), randomChar(), randomChar()},
        {randomChar(), randomChar(), randomChar(), randomChar()}
    });
}

bool checkEqual(matrix::Matrix<uint8_t, 4, 4>& m1, matrix::Matrix<uint8_t, 4, 4>& m2) {
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            if(m1[i][j] != m2[i][j]) return false;
        }
    }
    return true;
}

void writeJournal(const std::vector<short>& journal) {
    std::ofstream outFile("journal.csv");

    // Optional: Check if the file was opened successfully
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return;
    }

    for(int i = 0; i < journal.size(); ++i) {
        outFile << journal[i];
        if(i != journal.size() - 1) {
            outFile << ",";
        }
    }

    // 3. Close the file
    outFile.close();

    std::cout << "Data written to journal.csv successfully." << std::endl;
}

int main() {
    matrix::Matrix<uint8_t, 4, 4> key ({
        {0x2b, 0x28, 0xab, 0x09},
        {0x7e, 0xae, 0xf7, 0xcf},
        {0x15, 0xd2, 0x15, 0x4f},
        {0x16, 0xa6, 0x88, 0x3c}
    });

    AES128 aes128(key);

    // //Ensure that matricies are equal
    // uint32_t testSamples = 100;
    // for(int i = 0; i < testSamples; ++i) {
    //     matrix::Matrix<uint8_t, 4, 4> data{genRandom()};
    //     matrix::Matrix<uint8_t, 4, 4> fullCycle{data};
    //     //std::cout << data << std::endl;
    //     aes128.encrypt(fullCycle);
    //     //std::cout << data << std::endl;
    //     aes128.decrypt(fullCycle);
    //     //std::cout << data << std::endl;
    //     if(!checkEqual(data, fullCycle)) {
    //         std::cout << "ERROR: mismatch in starting data and full encrypt/decrypt cycle" << std::endl; 
    //         std::cout << data << std::endl;
    //         std::cout << fullCycle << std::endl;
    //         return -1;
    //     }
    // }

    //Benchmarks
    const auto startTime = __rdtscp();
    uint64_t totalTime = startTime;
    TickConverter converter;
    uint32_t samples = 1000000;
    std::vector<short> journal;
    journal.reserve(samples);

    std::array<matrix::Matrix<uint8_t, 4, 4>, 1024> data_pool;
    for(int i = 0; i < 1024; ++i) data_pool[i] = genRandom();

    BenchShield benchShield;

    //Warm up the cache and branch predictor
    for(int i = 0; i < samples/10; ++i) {
        matrix::Matrix<uint8_t, 4, 4> data = data_pool[i & 1023];
        aes128.encrypt(data);
        aes128.decrypt(data);
    }

    for(int i = 0; i < samples; ++i) {
        matrix::Matrix<uint8_t, 4, 4> data = data_pool[i & 1023];
        
        const auto startWindow = __rdtscp();
        aes128.encrypt(data);
        aes128.decrypt(data);
        const auto endWindow = __rdtscp();

        const auto deltaWindow = endWindow - startWindow;
        journal.push_back((short) converter.ticks_to_ns(deltaWindow));
        totalTime += deltaWindow;
    }
    writeJournal(journal);

    const auto timeDelta = (totalTime - startTime)/samples;

    std::cout << "Per Encrypt/Decrypt Cycle Cost | " << "Ticks: " << timeDelta << " Freq: " << converter.frequency << " Nanos: " << converter.ticks_to_ns(timeDelta) << std::endl;

    // ... after the loop ...

    std::sort(journal.begin(), journal.end());

    double minVal = journal.front();
    double maxVal = journal.back();
    double median = journal[samples / 2];
    double p99    = journal[static_cast<size_t>(samples * 0.99)];
    double p999   = journal[static_cast<size_t>(samples * 0.999)];

    std::cout << "\n--- FINAL PERFORMANCE REPORT ---\n";
    std::cout << "Min:    " << minVal << " ns\n";
    std::cout << "Median: " << median << " ns <-- TRUE PERFORMANCE\n";
    std::cout << "P99:    " << p99    << " ns\n";
    std::cout << "P99.9:  " << p999   << " ns\n";
    std::cout << "Max:    " << maxVal << " ns\n";

    // 1. Define the "Interrupt Threshold" 
    // (Anything 50% slower than the median is likely an interrupt)
    const double threshold = median * 1.5; 

    // 2. Count how many samples exceeded this threshold
    long long interrupt_count = 0;
    for (short sample : journal) {
        if (sample > threshold) {
            interrupt_count++;
        }
    }

    // 3. Calculate Empirical Probability
    double probability = (double)interrupt_count / samples;

    std::cout << "\n--- INTERRUPT ANALYSIS ---\n";
    std::cout << "Threshold used:    " << threshold << " ns\n";
    std::cout << "Total Outliers:    " << interrupt_count << " samples\n";
    std::cout << "Prob. of Interrupt: " << (probability * 100.0) << " %\n";
    std::cout << "Clean Cycles Gap:  ~" << (int)(1.0 / probability) << " cycles between hits\n";
}