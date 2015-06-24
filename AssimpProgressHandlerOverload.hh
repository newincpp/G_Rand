#ifndef ASSIMPPROGRESSHANDLEROVERLOAD_H_
# define ASSIMPPROGRESSHANDLEROVERLOAD_H_

#include "assimp/ProgressHandler.hpp"

class AssimpProgressHandlerOverload : public Assimp::ProgressHandler {
    private:
	std::string _loadingMessage;
	int	    _p;
    public:
	AssimpProgressHandlerOverload();
	AssimpProgressHandlerOverload(std::string msg);
	bool Update(float percentage);
	void SetLoadingMessage(std::string msg);
};

#endif /* !ASSIMPPROGRESSHANDLEROVERLOAD_H_ */
