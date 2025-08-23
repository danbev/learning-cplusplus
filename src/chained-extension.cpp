#include <iostream>
#include <string>

// Base chain struct - every extension inherits from this
enum class ExtensionType {
    None = 0,
    DatabaseConfig = 1,
    CacheConfig = 2,
    LoggingConfig = 3
};

struct ChainedExtension {
    ExtensionType type = ExtensionType::None;
    ChainedExtension* next = nullptr;
};

// Main API struct - this is what your function takes
struct ServerConfig {
    std::string host = "localhost";
    int port = 8080;
    ChainedExtension* extensions = nullptr;  // The chain!
};

// Extension 1: Database configuration
struct DatabaseConfig : public ChainedExtension {
    DatabaseConfig() { 
        type = ExtensionType::DatabaseConfig; 
    }
    
    std::string connectionString = "";
    int poolSize = 10;
};

// Extension 2: Cache configuration  
struct CacheConfig : public ChainedExtension {
    CacheConfig() { 
        type = ExtensionType::CacheConfig; 
    }
    
    int maxMemoryMB = 256;
    int ttlSeconds = 3600;
};

// Extension 3: Logging configuration
struct LoggingConfig : public ChainedExtension {
    LoggingConfig() { 
        type = ExtensionType::LoggingConfig; 
    }
    
    std::string logLevel = "INFO";
    std::string logFile = "server.log";
};

// The API function that processes the config
void startServer(const ServerConfig& config) {
    std::cout << "Starting server on " << config.host << ":" << config.port << std::endl;
    
    // Walk the chain and handle each extension
    ChainedExtension* current = config.extensions;
    while (current != nullptr) {
        switch (current->type) {
            case ExtensionType::DatabaseConfig: {
                DatabaseConfig* dbConfig = static_cast<DatabaseConfig*>(current);
                std::cout << "  Database: " << dbConfig->connectionString 
                         << " (pool size: " << dbConfig->poolSize << ")" << std::endl;
                break;
            }
            case ExtensionType::CacheConfig: {
                CacheConfig* cacheConfig = static_cast<CacheConfig*>(current);
                std::cout << "  Cache: " << cacheConfig->maxMemoryMB 
                         << "MB, TTL: " << cacheConfig->ttlSeconds << "s" << std::endl;
                break;
            }
            case ExtensionType::LoggingConfig: {
                LoggingConfig* logConfig = static_cast<LoggingConfig*>(current);
                std::cout << "  Logging: " << logConfig->logLevel 
                         << " -> " << logConfig->logFile << std::endl;
                break;
            }
            default:
                std::cout << "  Unknown extension type: " << (int)current->type << std::endl;
                break;
        }
        current = current->next;
    }
}

int main() {
    // Create base config
    ServerConfig config;
    config.host = "production.com";
    config.port = 443;
    
    // Create extensions
    DatabaseConfig dbConfig;
    dbConfig.connectionString = "postgresql://db:5432/myapp";
    dbConfig.poolSize = 20;
    
    CacheConfig cacheConfig;
    cacheConfig.maxMemoryMB = 512;
    cacheConfig.ttlSeconds = 7200;
    
    LoggingConfig logConfig;
    logConfig.logLevel = "DEBUG";
    logConfig.logFile = "/var/log/myapp.log";
    
    // Chain them together: config -> db -> cache -> logging -> null
    config.extensions = &dbConfig;
    dbConfig.next = &cacheConfig;
    cacheConfig.next = &logConfig;
    logConfig.next = nullptr;
    
    // Call the API - it handles all extensions automatically!
    startServer(config);
    
    std::cout << "\n--- Now with just database config ---\n";
    
    // Different scenario: only database config
    ServerConfig simpleConfig;
    DatabaseConfig simpleDbConfig;
    simpleDbConfig.connectionString = "sqlite://simple.db";
    
    simpleConfig.extensions = &simpleDbConfig;
    // No next pointer set, so chain ends here
    
    startServer(simpleConfig);
    
    return 0;
}
