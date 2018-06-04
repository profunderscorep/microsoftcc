#pragma once

#include "GUI.h"

enum SliderFormat
{
	FORMAT_INT = 1,
	FORMAT_DECDIG1,
	FORMAT_DECDIG2
};

class CCheckBox : public CControl
{
public:
	CCheckBox();
	void SetState(bool s);
	bool GetState();
protected:
	bool Checked;
	void Draw(bool hover);
	void OnUpdate();
	void OnClick();
};

class CLabel : public CControl
{
public:
	CLabel();
	void SetText(std::string text);
protected:
	std::string Text;
	void Draw(bool hover);
	void OnUpdate();
	void OnClick();
};

class CGroupBox : public CControl
{
public:
	CGroupBox();
	void SetText(std::string text);
	void SetSpacing(int Spacing);
	void PlaceLabledControl(std::string Label, CTab *Tab, CControl* control);
	void PlaceCheckBox(std::string Label, CTab * Tab, CControl * control);
	void PlaceOtherControl(std::string Label, CTab * Tab, CControl * control);
protected:
	int Items;
	std::string Text;
	float iYAdd;
	int ItemSpacing;
	void Draw(bool hover);
	void OnUpdate();
	void OnClick();
};

class CSlider : public CControl
{
public:
	CSlider();
	float GetValue();
	void SetValue(float v);
	void SetBoundaries(float min, float max);
protected:
	float Value;
	float Min;
	float Max;
	bool DoDrag;
	void Draw(bool hover);
	void OnUpdate();
	void OnClick();
};

class CSlider2 : public CControl
{
public:
	CSlider2();
	float GetValue();
	void SetValue(float v);
	void SetBoundaries(float min, float max);
protected:
	float Value;
	float Min;
	float Max;
	bool DoDrag;
	void Draw(bool hover);
	void OnUpdate();
	void OnClick();
};

class CSlider3 : public CControl
{
public:
	CSlider3();
	int GetValue();
	void SetValue(int v);
	void SetBoundaries(int min, int max);
protected:
	int Value;
	int Min;
	int Max;
	bool DoDrag;
	void Draw(bool hover);
	void OnUpdate();
	void OnClick();
};

class CKeyBind : public CControl
{
public:
	CKeyBind();
	int GetKey();
	void SetKey(int key);
protected:
	int Key;
	bool IsGettingKey;
	void Draw(bool hover);
	void OnUpdate();
	void OnClick();
};

class CButton : public CControl
{
public:
	typedef void(*ButtonCallback_t)(void);
	CButton();
	void SetCallback(ButtonCallback_t callback);
	void SetText(std::string text);
protected:
	ButtonCallback_t CallBack;
	std::string Text;
	void Draw(bool hover);
	void OnUpdate();
	void OnClick();
};

class CComboBox : public CControl
{
public:
	CComboBox();
	void AddItem(std::string text);
	void SelectIndex(int idx);
	int GetIndex();
	void SetIndex(int);
	std::string GetItem();
protected:
	std::vector<std::string> Items;
	int SelectedIndex;
	bool IsOpen;
	int winWidth;
	int winHeight;
	void Draw(bool hover);
	void OnUpdate();
	void OnClick();
};

class CTextField : public CControl
{
public:
	CTextField();
	std::string getText();
	void SetText(std::string);
private:
	std::string text;
	bool IsGettingKey;
	void Draw(bool hover);
	void OnUpdate();
	void OnClick();
};

class CTextField2 : public CControl
{
public:
	CTextField2();
	std::string getText();
	void SetText(std::string);
private:
	std::string text;
	bool IsGettingKey;
	void Draw(bool hover);
	void OnUpdate();
	void OnClick();
};