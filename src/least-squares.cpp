#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
    // Our 4 float values to quantize
    float values[] = {10.0f, 11.0f, 13.0f, 14.0f};
    int n = 4;
    
    std::cout << "Least squareS quantization example\n\n";
    
    std::cout << "Original values: ";
    for (int i = 0; i < n; i++) {
        std::cout << values[i] << " ";
    }
    std::cout << "\n";
    std::cout << "Quantized levels available: [0, 1, 2, 3]\n\n";
    
    // Calculate all the sums we need
    float sum_w = n;              // Sum of weights (all weights = 1)
    float sum_x = 0;              // Sum of original values
    float sum_l = 0;              // Sum of levels [0+1+2+3]
    float sum_l2 = 0;             // Sum of levels squared [0²+1²+2²+3²]
    float sum_xl = 0;             // Sum of (level × original_value)
    
    for (int i = 0; i < n; i++) {
        int level = i;  // For this example: level 0,1,2,3 for values 0,1,2,3
        sum_x += values[i];
        sum_l += level;
        sum_l2 += level * level;
        sum_xl += level * values[i];
    }
    
    std::cout << "Calculated sums:\n";
    std::cout << "  sum_w (n): " << sum_w << "\n";
    std::cout << "  sum_x: " << sum_x << "\n";
    std::cout << "  sum_l: " << sum_l << "\n";
    std::cout << "  sum_l2: " << sum_l2 << "\n";
    std::cout << "  sum_xl: " << sum_xl << "\n\n";
    
    // Apply least squares formulas
    float D = sum_w * sum_l2 - sum_l * sum_l;
    
    std::cout << "Denominator D = sum_w * sum_l2 - sum_l * sum_l\n";
    std::cout << "D = " << sum_w << " * " << sum_l2 << " - " << sum_l << " * " << sum_l;
    std::cout << " = " << D << "\n\n";
    
    float optimal_scale = (sum_w * sum_xl - sum_x * sum_l) / D;
    float optimal_min = (sum_l2 * sum_x - sum_l * sum_xl) / D;
    
    std::cout << "Optimal scale = (sum_w * sum_xl - sum_x * sum_l) / D\n";
    std::cout << "             = (" << sum_w << " * " << sum_xl << " - " << sum_x << " * " << sum_l << ") / " << D << "\n";
    std::cout << "             = " << optimal_scale << "\n\n";
    
    std::cout << "Optimal min = (sum_l2 * sum_x - sum_l * sum_xl) / D\n";
    std::cout << "            = (" << sum_l2 << " * " << sum_x << " - " << sum_l << " * " << sum_xl << ") / " << D << "\n";
    std::cout << "            = " << optimal_min << "\n\n";
    
    // Test the optimal solution
    float optimal_error = 0.0f;
    std::cout << "Quantization results with optimal scale/min:\n";
    for (int i = 0; i < n; i++) {
        int level = i;  // Using levels 0,1,2,3 for values 0,1,2,3
        float dequantized = optimal_scale * level + optimal_min;
        float error = values[i] - dequantized;
        optimal_error += error * error;
        
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "  " << values[i] << " -> level " << level 
                  << " -> " << dequantized << " (error: " << error << ")\n";
    }
    std::cout << "Total squared error: " << optimal_error << "\n\n";
    
    return 0;
}
