#pragma once
#include "SceneBase.h"

class EscapeScene : public SceneBase
{
public:
	EscapeScene();
	~EscapeScene();
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
