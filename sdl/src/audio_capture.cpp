#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <cmath>

// Audio specifications
static SDL_AudioSpec wanted_spec, obtained_spec;
static SDL_AudioDeviceID audio_device_id = 0;
static std::vector<float> audio_buffer;
static size_t buffer_size = 0;
static bool recording = false;

static int call_count = 0;

// Audio capture callback function
// This function will be called by SDL and how often is determined by:
// time_between_calls = (buffer_size / sample_rate)
// For example:
// buffer_size = 1024 samples
// sample_rate = 16000 Hz
// time_between_calls = 1024 / 16000 = 0.064 seconds (64 ms)
//
// Note that this is we set the number of samples:
// wanted_spec.samples = 1024;
// This is the buffer size in samples, not bytes, so the len of the stream
// will not be 1024 bytes, but 1024 * sizeof(float) bytes = 4096 bytes
void audio_capture_callback(void* userdata, Uint8* stream, int len) {
    std::cout << "Audio callback called with " << len << " bytes. call_count: " << call_count++ << '\n';
    // Convert the raw bytes to float samples
    float* samples = reinterpret_cast<float*>(stream);
    int num_samples = len / sizeof(float);
    
    // Print some info about the captured audio
    if (recording) {
        // Calculate RMS (Root Mean Square) for volume level
        float rms = 0.0f;
        for (int i = 0; i < num_samples; i++) {
            rms += samples[i] * samples[i];
        }
        rms = std::sqrt(rms / num_samples);
        
        // Print audio info every ~100 calls (adjust based on sample rate)
        static int call_count = 0;
        call_count++;
        if (call_count % 100 == 0) {
            std::cout << "Captured " << num_samples << " samples, "
                      << "RMS level: " << rms << std::endl;
        }
        
        // Store samples in buffer (optional - for processing)
        audio_buffer.insert(audio_buffer.end(), samples, samples + num_samples);
        
        // Keep buffer from growing too large
        if (audio_buffer.size() > 48000) { // ~1 second at 48kHz
            audio_buffer.erase(audio_buffer.begin(), audio_buffer.begin() + (audio_buffer.size() - 48000));
        }
    }
}

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << '\n';
        return 1;
    }
    
    // Set up desired audio specification
    memset(&wanted_spec, 0, sizeof(wanted_spec));
    wanted_spec.freq = 16000;
    wanted_spec.format = AUDIO_F32SYS;  // 32-bit float samples
    wanted_spec.channels = 1;           // Mono
    wanted_spec.samples = 1024;         // Buffer size in samples (not bytes)
    wanted_spec.callback = audio_capture_callback;
    wanted_spec.userdata = nullptr;
    
    // List available audio devices
    std::cout << "Available audio capture devices:\n";
    int num_devices = SDL_GetNumAudioDevices(1); // 1 for capture devices (0 for playback devices)
    for (int i = 0; i < num_devices; i++) {
        const char* device_name = SDL_GetAudioDeviceName(i, 1);
        std::cout << "  " << i << ": " << (device_name ? device_name : "Unknown") << '\n';
    }
    
    // Open the default audio capture device
    audio_device_id = SDL_OpenAudioDevice(nullptr, 1, &wanted_spec, &obtained_spec, 
                                          SDL_AUDIO_ALLOW_FORMAT_CHANGE | SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
    
    if (audio_device_id == 0) {
        std::cerr << "Failed to open audio device! SDL_Error: " << SDL_GetError() << '\n';
        SDL_Quit();
        return 1;
    }
    
    // Print obtained audio specifications
    std::cout << "\nObtained audio specification:\n";
    std::cout << "  Frequency: " << obtained_spec.freq << " Hz\n";
    std::cout << "  Channels: " << (int)obtained_spec.channels << '\n';
    std::cout << "  Samples: " << obtained_spec.samples << '\n';
    std::cout << "  Format: ";
    switch (obtained_spec.format) {
        case AUDIO_F32SYS: std::cout << "32-bit float"; break;
        case AUDIO_S16SYS: std::cout << "16-bit signed"; break;
        case AUDIO_S32SYS: std::cout << "32-bit signed"; break;
        default: std::cout << "Other (" << obtained_spec.format << ")"; break;
    }
    std::cout << std::endl;
    
    // Reserve space for audio buffer
    audio_buffer.reserve(obtained_spec.freq * 2); // 2 seconds worth
    
    // Start recording
    std::cout << "\nStarting audio capture...\n";
    std::cout << "Press Enter to stop recording.\n";
    recording = true;
    SDL_PauseAudioDevice(audio_device_id, 0); // 0 = unpause (start)
    
    // Wait for user input
    std::cin.get();
    
    // Stop recording
    recording = false;
    SDL_PauseAudioDevice(audio_device_id, 1); // 1 = pause (stop)
    
    // Print final statistics
    std::cout << "\nRecording stopped.\n";
    std::cout << "Total samples captured: " << audio_buffer.size() << '\n';
    std::cout << "Duration: " << (float)audio_buffer.size() / obtained_spec.freq << " seconds\n";
    
    std::cout << "\nFirst 10 audio samples:\n";
    for (size_t i = 0; i < std::min((size_t)10, audio_buffer.size()); i++) {
        std::cout << "  Sample " << i << ": " << audio_buffer[i] << '\n';
    }
    
    // Cleanup
    SDL_CloseAudioDevice(audio_device_id);
    SDL_Quit();
    
    return 0;
}
