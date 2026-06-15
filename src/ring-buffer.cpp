#include <iostream>
#include <vector>
#include <cstring> // Required for std::memcpy

class ring_buffer {
private:
    std::vector<float> m_audio;
    size_t m_write_pos = 0;
    size_t m_read_pos  = 0;

public:
    ring_buffer(size_t capacity) : m_audio(capacity, 0.0f) {}

    // Writes data into the ring buffer
    void write_samples(const float* src_data, size_t n_samples) {
        // Check if writing this many samples goes past the end of the vector
        if (m_write_pos + n_samples > m_audio.size()) {
            // Wrap-around required
            const size_t n0 = m_audio.size() - m_write_pos; // Samples left before hitting the edge
            
            // Fill up to the edge
            std::memcpy(&m_audio[m_write_pos], src_data, n0 * sizeof(float));
            // Wrap around to index 0 and write the remainder
            std::memcpy(&m_audio[0], src_data + n0, (n_samples - n0) * sizeof(float));
        } else {
            std::memcpy(&m_audio[m_write_pos], src_data, n_samples * sizeof(float));
        }

        // Advance the write pointer, wrapping it back smoothly using modulo
        m_write_pos = (m_write_pos + n_samples) % m_audio.size();
    }

    // Reads data out of the ring buffer into a destination array.
    void read_samples(float* dst_data, size_t n_samples) {
        // Check if reading this many samples goes past the end of the vector
        if (m_read_pos + n_samples > m_audio.size()) {
            // Wrap-around required
            const size_t n0 = m_audio.size() - m_read_pos; // Samples left before hitting the edge
            
            // Read up to the edge
            std::memcpy(dst_data, &m_audio[m_read_pos], n0 * sizeof(float));
            // Wrap around to index 0 and read the remainder
            std::memcpy(dst_data + n0, &m_audio[0], (n_samples - n0) * sizeof(float));
        } else {
            // Fits cleanly in a single straight block
            std::memcpy(dst_data, &m_audio[m_read_pos], n_samples * sizeof(float));
        }

        // Advance the read pointer, wrapping it back smoothly using modulo
        m_read_pos = (m_read_pos + n_samples) % m_audio.size();
    }

    void print_buffer_state() const {
        std::cout << "[ ";
        for (float val : m_audio) {
            std::cout << val << " ";
        }
        std::cout << "]\n(Write Pos: " << m_write_pos << ", Read Pos: " << m_read_pos << ")\n";
    }
};

int main() {
    ring_buffer ring(5);
    std::cout << "Initial empty state:\n";
    ring.print_buffer_state();

    // Push 3 samples (Fits cleanly: indices 0, 1, 2)
    float input_chunk1[] = { 1.0f, 2.0f, 3.0f };
    std::cout << "Pushing 3 samples:\n";
    ring.write_samples(input_chunk1, 3);
    ring.print_buffer_state();

    /*
    // 2. Pop 2 samples (Reads cleanly from 0, 1)
    float output_chunk1[2];
    ring.read_samples(output_chunk1, 2);
    std::cout << "Popped 2 samples: {" << output_chunk1[0] << ", " << output_chunk1[1] << "}\n";
    ring.print_buffer_state();
    std::cout << "--------------------------------------------------------\n";

    // 3. Push 3 samples (Will cause WRAP-AROUND!)
    // Current write pos is 3. We want to write 3 samples. 
    // 3 + 3 = 6, which is greater than our capacity (5).
    // It will write 2 samples to indices [3, 4], and 1 sample to index [0].
    float input_chunk2[] = {4.4f, 5.5f, 6.6f};
    std::cout << "Pushing 3 samples: {4.4, 5.5, 6.6} (Forces wrap-around)\n";
    ring.write_samples(input_chunk2, 3);
    ring.print_buffer_state();

    // 4. Pop 3 samples (Forces wrap-around reading)
    // Current read pos is 2. Reading 3 samples will read index [2, 3, 4].
    // If we read more after this, it would wrap to [0].
    float output_chunk2[3];
    ring.read_samples(output_chunk2, 3);
    std::cout << "Popped 3 samples: {" << output_chunk2[0] << ", " << output_chunk2[1] << ", " << output_chunk2[2] << "}\n";
    ring.print_buffer_state();
    */

    return 0;
}
