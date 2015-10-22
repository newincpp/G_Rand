#include <iostream>
#include "AssimpProgressHandlerOverload.hh"

AssimpProgressHandlerOverload::AssimpProgressHandlerOverload() : _loadingMessage(""), _p(0.0f) {
}

AssimpProgressHandlerOverload::AssimpProgressHandlerOverload(std::string msg) : _loadingMessage(msg), _p(0.0f) {
}

bool AssimpProgressHandlerOverload::Update(float percentage) {
    if (percentage != -1.0f) {
	std::cout << "Loading" << _loadingMessage << ": " << percentage << "%";
	_p = percentage;
    } else {
	std::cout << "Loading" << _loadingMessage << ": " << _p << "%";
	_p += 6.0f;
    }
    std::cout << "\r";
    return (true);
}

void AssimpProgressHandlerOverload::SetLoadingMessage(std::string msg) {
    _loadingMessage = msg;
}
