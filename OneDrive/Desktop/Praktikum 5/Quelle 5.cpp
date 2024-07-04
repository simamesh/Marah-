#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>
#include <queue>
#include <condition_variable>

// OSI-Schichten-Klassen bleiben unverändert
// ... (Application, Transport, Network, DataLink, Presentation, Display)
class Application {
public:
    std::string addProtocol(const std::string& message, const std::string& protocol) {
        return "Protocol: " + protocol + "|" + message;
    }

    std::string removeProtocol(const std::string& message) {
        return message.substr(message.find("|") + 1);
    }
};

class Transport {
public:
    std::string addTTL(const std::string& message, int ttl) {
        return "TTL: " + std::to_string(ttl) + "|" + message;
    }

    std::string removeTTL(const std::string& message) {
        return message.substr(message.find("|") + 1);
    }
};

class Network {
public:
    std::string addAddresses(const std::string& message, const std::string& sourceAddr, const std::string& destAddr) {
        return "Source: " + sourceAddr + ", Dest: " + destAddr + "|" + message;
    }

    std::string removeAddresses(const std::string& message) {
        return message.substr(message.find("|") + 1);
    }
};

class DataLink {
public:
    std::string addChecksum(const std::string& message, const std::string& checksum) {
        return "Checksum: " + checksum + "|" + message;
    }

    std::string removeChecksum(const std::string& message) {
        return message.substr(message.find("|") + 1);
    }
};

class Presentation {
public:
    std::string encrypt(const std::string& message, int shift) {
        std::string encrypted;
        for (char c : message) {
            if (isalpha(c)) {
                char base = isupper(c) ? 'A' : 'a';
                encrypted += char((c - base + shift) % 26 + base);
            }
            else {
                encrypted += c;
            }
        }
        return encrypted;
    }

    std::string decrypt(const std::string& message, int shift) {
        std::string decrypted;
        for (char c : message) {
            if (isalpha(c)) {
                char base = isupper(c) ? 'A' : 'a';
                decrypted += char((c - base - shift + 26) % 26 + base);
            }
            else {
                decrypted += c;
            }
        }
        return decrypted;
    }
};

class Display {
public:
    void showMessage(const std::string& message, const std::string& destAddr) {
        if (destAddr == "10.0.0.1") {
            std::cout << "Received message: " << message << std::endl;
        }
        else {
            std::cout << "Invalid destination address" << std::endl;
        }
    }
};






class NetworkInterface {
private:
    std::queue<std::string> messageQueue;
    std::mutex queueMutex;
    std::condition_variable cv;
    bool running;
    Application app;
    Transport trans;
    Network net;
    DataLink link;
    Presentation pres;
    Display disp;

public:
    NetworkInterface() : running(true) {}

    void addMessage(const std::string& message, const std::string& sourceAddr, const std::string& destAddr, 
                    int ttl, const std::string& protocol, const std::string& checksum, int shift) {
        std::string encapsulated = message;
        encapsulated = app.addProtocol(encapsulated, protocol);
        encapsulated = trans.addTTL(encapsulated, ttl);
        encapsulated = net.addAddresses(encapsulated, sourceAddr, destAddr);
        encapsulated = link.addChecksum(encapsulated, checksum);
        encapsulated = pres.encrypt(encapsulated, shift);

        {
            std::lock_guard<std::mutex> lock(queueMutex);
            messageQueue.push(encapsulated);
        }
        cv.notify_one(); 
    }

    void processMessages() {
        while (running) {
            std::unique_lock<std::mutex> lock(queueMutex);
            cv.wait(lock, [this] { return !messageQueue.empty() || !running; });

            if (!running && messageQueue.empty()) {
                break;
            }

            std::string message = messageQueue.front();
            messageQueue.pop();
            lock.unlock();

            
            std::cout << "Processing message: " << message << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));

            std::string decapsulated = pres.decrypt(message, 3); 
            decapsulated = link.removeChecksum(decapsulated);
            decapsulated = net.removeAddresses(decapsulated);
            decapsulated = trans.removeTTL(decapsulated);
            decapsulated = app.removeProtocol(decapsulated);

            disp.showMessage(decapsulated, "10.0.0.1");
        }
    }

    void stop() {
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            running = false;
        }
        cv.notify_one(); 
    }
};

int main() {
    NetworkInterface network;
    std::thread networkThread(&NetworkInterface::processMessages, &network);

    
    for (int i = 0; i < 3; ++i) {
        std::string message = "Hello, World! " + std::to_string(i + 1);
        network.addMessage(message, "192.168.0.1", "10.0.0.1", 64, "HTTP", "ABC123", 3);
        std::cout << "Message sent: " << message << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    // Warte, bis alle Nachrichten verarbeitet wurden
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Beende den Thread
    network.stop();
    networkThread.join();

    return 0;
}


// // mithilfe von perplexity 