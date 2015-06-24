#include <iostream>
#include "AssimpProgressHandlerOverload.hh"

AssimpProgressHandlerOverload::AssimpProgressHandlerOverload() : _loadingMessage(""), _p(0) {
}

AssimpProgressHandlerOverload::AssimpProgressHandlerOverload(std::string msg) : _loadingMessage(msg), _p(0) {
}

bool AssimpProgressHandlerOverload::Update(float percentage) {
    if (percentage != -1) {
	std::cout << "Loading" << _loadingMessage << ": " << percentage << "%" << std::endl;
	_p = percentage;
    } else {
	std::cout << "Loading" << _loadingMessage << ": " << _p << "%" << std::endl;
	_p += 6;
    }
    return (true);
}

void AssimpProgressHandlerOverload::SetLoadingMessage(std::string msg) {
    _loadingMessage = msg;
}
