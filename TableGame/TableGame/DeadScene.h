#pragma once
#include "SceneBase.h"

class DeadScene : public SceneBase
{
public:
	DeadScene();
	~DeadScene();
	virtual void Run() override;
protected:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Music() override;
	virtual bool SelectProcess() override;
private:
	HANDLE hStdout;
	std::string _restartBtnText;
	std::string _exitBtnText;
};
