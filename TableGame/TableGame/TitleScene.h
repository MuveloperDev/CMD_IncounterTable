#pragma once
#include "SceneBase.h"
#include "DifficultSelectPage.h"

class DifficultSelectPage;
class TitleScene : public SceneBase
{
public:
	TitleScene();
	~TitleScene();
	virtual void Run() override;

	void SetMode(TitleMode InMode);
	TitleMode GetMode();
protected:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Music() override;
	virtual bool SelectProcess() override;

private:

	HANDLE hStdout;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	SMALL_RECT srWindowRect;
	COORD coordScreen;
	std::string _startBtnText;
	std::string _difficultBtnText;
	std::string _exitBtnText;
	TitleMode _CURRENT_MODE;
	DifficultSelectPage* _difficultSelectPage;
};

