#include <iostream>
#include <string>
#include <thread>
#include <chrono>

// OSI-Schichten
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

void sendThread(const std::string& message, int delay) {
    std::this_thread::sleep_for(std::chrono::seconds(delay));
    std::cout << "Message sent: " << message << std::endl;
}

int main() {
    std::string message = "Hello,  World!";
    std::string sourceAddr = "192.168.0.1";
    std::string destAddr = "10.0.0.1";
    int ttl = 64;
    std::string protocol = "HTTP";
    std::string checksum = "ABC123";
    int delay = 2; // Verzögerung in Sekunden
    int shift = 3; // Verschiebung für Caesar-Verschlüsselung

    Application app;
    Transport trans;
    Network net;
    DataLink link;
    Presentation pres;
    Display disp;

    std::string encapsulated = message;
    encapsulated = app.addProtocol(encapsulated, protocol);
    encapsulated = trans.addTTL(encapsulated, ttl);
    encapsulated = net.addAddresses(encapsulated, sourceAddr, destAddr);
    encapsulated = link.addChecksum(encapsulated, checksum);
    encapsulated = pres.encrypt(encapsulated, shift); // Verschlüsseln

    disp.showMessage(encapsulated, destAddr);

    // Starte einen Thread für die Versandsimulation
    std::thread sendingThread(sendThread, encapsulated, delay);
    sendingThread.join();

    std::string decapsulated = pres.decrypt(encapsulated, shift); // Entschlüsseln
    decapsulated = link.removeChecksum(decapsulated);
    decapsulated = net.removeAddresses(decapsulated);
    decapsulated = trans.removeTTL(decapsulated);
    decapsulated = app.removeProtocol(decapsulated);

    disp.showMessage(decapsulated, destAddr);

    return 0;
}