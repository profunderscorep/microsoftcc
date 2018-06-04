#include "Controls.h"
#include "RenderManager.h"
#include "Menu.h"
#include "Gui.h"

#define UI_COL_MAIN2		Color(27, 220, 117, MenuAlpha5)
#define UI_COL_SHADOW2		Color(0, 0, 0, MenuAlpha)

#pragma region Base Control

void CControl::SetPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}

void CControl::SetSize(int w, int h)
{
	m_iWidth = w;
	m_iHeight = h;
}

void CControl::GetSize(int &w, int &h)
{
	w = m_iWidth;
	h = m_iHeight;
}

bool CControl::Flag(int f)
{
	if (m_Flags & f)
		return true;
	else
		return false;
}

POINT CControl::GetAbsolutePos()
{
	POINT p;
	RECT client = parent->GetClientArea();
	if (parent)
	{
		p.x = m_x + client.left;
		p.y = m_y + client.top + 29;
	}

	return p;
}

void CControl::SetFileId(std::string fid)
{
	FileIdentifier = fid;
}
#pragma endregion Implementations of the Base control functions

#pragma region CheckBox
CCheckBox::CCheckBox()
{
	Checked = false;

	m_Flags = UIFlags::UI_Clickable | UIFlags::UI_Drawable | UIFlags::UI_SaveFile;
	m_iWidth = 10;
	m_iHeight = 10;

	FileControlType = UIControlTypes::UIC_CheckBox;
}

void CCheckBox::SetState(bool s)
{
	Checked = s;
}

bool CCheckBox::GetState()
{
	return Checked;
}

void CCheckBox::Draw(bool hover)
{
	POINT a = GetAbsolutePos();
	Render::Clear(a.x, a.y, 10, 10, Color(19, 19, 19, MenuAlpha));
	Render::Outline(a.x, a.y, 10, 10, Color(2, 2, 2, MenuAlpha));

	if (Checked)
	{
		Render::Clear(a.x, a.y, 10, 10, Color(Menu::Window.CheatSkinTab.rUI_CURSORFILL.GetValue(), Menu::Window.CheatSkinTab.gUI_CURSORFILL.GetValue(), Menu::Window.CheatSkinTab.bUI_CURSORFILL.GetValue(), MenuAlpha)); //124 167 18
		Render::Outline(a.x, a.y, 10, 10, Color(2, 2, 2, MenuAlpha));
	}
}

void CCheckBox::OnUpdate() { m_iWidth = 10; 	m_iHeight = 10; }

void CCheckBox::OnClick()
{
	Checked = !Checked;
}
#pragma endregion Implementations of the Check Box functions

#pragma region Label
CLabel::CLabel()
{
	m_Flags = UIFlags::UI_Drawable;
	Text = "Default";
	FileIdentifier = "Default";
}

void CLabel::Draw(bool hover)
{
	POINT a = GetAbsolutePos();
	Render::Text(a.x, a.y, Color(Menu::Window.CheatSkinTab.rText.GetValue(), Menu::Window.CheatSkinTab.gText.GetValue(), Menu::Window.CheatSkinTab.bText.GetValue(), MenuAlpha), Render::Fonts::MenuBold, Text.c_str()); // 255 255 255
}

void CLabel::SetText(std::string text)
{
	Text = text;
}

void CLabel::OnUpdate() {}
void CLabel::OnClick() {}
#pragma endregion Implementations of the Label functions

#pragma region GroupBox
CGroupBox::CGroupBox()
{
	Items = 1;
	iYAdd = 0;
	ItemSpacing = 20;
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_RenderFirst;
	Text = "Default";
	FileIdentifier = "Default";
}

void CGroupBox::Draw(bool hover)
{
	POINT a = GetAbsolutePos();
	RECT txtSize = Render::GetTextSize(Render::Fonts::Menu, Text.c_str());
	Render::Clear(a.x + 2, a.y + 2, m_iWidth - 4, m_iHeight - 4, Color(90, 90, 90, MenuAlpha21));
	Render::Text(a.x + (m_iWidth / 2) - (txtSize.right / 2), a.y - (txtSize.bottom / 2) - 1, Color(Menu::Window.CheatSkinTab.rText.GetValue(), Menu::Window.CheatSkinTab.gText.GetValue(), Menu::Window.CheatSkinTab.bText.GetValue(), MenuAlpha), Render::Fonts::Menu, Text.c_str()); // 244 244 244

	Render::Line(a.x, a.y, a.x + (m_iWidth / 2) - (txtSize.right / 2) - 2, a.y, Color(48, 48, 48, MenuAlpha));
	Render::Line(a.x + (m_iWidth / 2) + (txtSize.right / 2) + 2, a.y, a.x + m_iWidth, a.y, Color(48, 48, 48, MenuAlpha));
	Render::Line(a.x, a.y, a.x, a.y + m_iHeight, Color(48, 48, 48, MenuAlpha));
	Render::Line(a.x, a.y + m_iHeight, a.x + m_iWidth, a.y + m_iHeight, Color(48, 48, 48, MenuAlpha));
	Render::Line(a.x + m_iWidth, a.y, a.x + m_iWidth, a.y + m_iHeight, Color(48, 48, 48, MenuAlpha));
}

void CGroupBox::SetText(std::string text)
{
	Text = text;
}

void CGroupBox::SetSpacing(int Spacing)
{
	ItemSpacing = Spacing;
}

void CGroupBox::PlaceCheckBox(std::string Label, CTab *Tab, CControl* control)
{
	int x = m_x + 29;
	int y = m_y + Items * 32; //24

	int cw, ch;
	control->SetPosition(x, y);
	control->GetSize(cw, ch);
	control->SetSize((m_iWidth / 2) - 32, ch);
	Tab->RegisterControl(control);

	x += 20;

	CLabel* label = new CLabel;
	label->SetPosition(x, y);
	label->SetText(Label);
	Tab->RegisterControl(label);
	Items++;
}

void CGroupBox::PlaceOtherControl(std::string Label, CTab *Tab, CControl* control)
{
	int x = m_x + 29;
	int y = m_y + Items * 32; //24

	int cw, ch;
	control->SetPosition(x, y);
	control->GetSize(cw, ch);
	control->SetSize((m_iWidth / 2) - 32, ch);
	Tab->RegisterControl(control);

	x += m_iWidth / 2 - 25;

	CLabel* label = new CLabel;
	label->SetPosition(x, y);
	label->SetText(Label);
	Tab->RegisterControl(label);
	Items++;
}

void CGroupBox::PlaceLabledControl(std::string Label, CTab *Tab, CControl* control)
{
	if (control->FileControlType == UIControlTypes::UIC_CheckBox)
	{
		int x = m_x + 34;
		int y = m_y + Items * ItemSpacing + iYAdd;

		CLabel* label = new CLabel;
		label->SetPosition(x, y);
		label->SetText(Label);
		Tab->RegisterControl(label);

		x = m_x + 16;

		int cw, ch;
		control->SetPosition(x, y);
		control->GetSize(cw, ch);
		control->SetSize((m_iWidth / 2) - 32, ch);
		Tab->RegisterControl(control);
	}
	else if (control->FileControlType == UIControlTypes::UIC_ComboBox)
	{
		int x = m_x + 34;
		int y = m_y + Items * ItemSpacing + iYAdd;

		x += m_iWidth / 2 - 13;

		RECT txtSize = Render::GetTextSize(Render::Fonts::Menu, Label.c_str());
		y = y + 10 - (txtSize.bottom / 2);

		CLabel* label = new CLabel;
		label->SetPosition(x, y);
		label->SetText(Label);
		Tab->RegisterControl(label);

		x = m_x + 34;
		y = m_y + Items * ItemSpacing + iYAdd;

		int cw, ch;
		control->SetPosition(x, y);
		control->GetSize(cw, ch);
		control->SetSize((m_iWidth / 2) - 25, ch);
		Tab->RegisterControl(control);

		iYAdd += 6;
	}
	else if (control->FileControlType == UIControlTypes::UIC_Slider)
	{
		int x = m_x + 34;
		int y = m_y + Items * ItemSpacing + iYAdd - 1;

		x += m_iWidth / 2 - 13;

		CLabel* label = new CLabel;
		label->SetPosition(x, y);
		label->SetText(Label);
		Tab->RegisterControl(label);

		x = m_x + 34;
		y += 1;

		int cw, ch;
		control->SetPosition(x, y);
		control->GetSize(cw, ch);
		control->SetSize((m_iWidth / 2) - 25, ch);
		Tab->RegisterControl(control);
	}
	else if (control->FileControlType == UIControlTypes::UIC_Button)
	{
		int x = m_x + 34;
		int y = m_y + Items * ItemSpacing + iYAdd - 2;

		x += m_iWidth / 2;

		CLabel* label = new CLabel;
		label->SetPosition(x, y);
		label->SetText(Label);
		Tab->RegisterControl(label);

		x = m_x + 34;
		y += 2;

		int cw, ch;
		control->SetPosition(x, y);
		control->GetSize(cw, ch);
		control->SetSize(m_iWidth, 24);
		Tab->RegisterControl(control);
	}
	else
	{
		int x = m_x + 34;
		int y = m_y + Items * ItemSpacing + iYAdd;

		x += m_iWidth / 2 - 13;

		CLabel* label = new CLabel;
		label->SetPosition(x, y);
		label->SetText(Label);
		Tab->RegisterControl(label);

		x = m_x + 34;

		int cw, ch;
		control->SetPosition(x, y);
		control->GetSize(cw, ch);
		control->SetSize((m_iWidth / 2) - 25, ch);
		Tab->RegisterControl(control);
	}
	Items++;
}

void CGroupBox::OnUpdate() {}
void CGroupBox::OnClick() {}
#pragma endregion Implementations of the Group Box functions

#pragma region Sliders

CSlider::CSlider()
{
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_Clickable | UIFlags::UI_SaveFile;

	FileControlType = UIControlTypes::UIC_Slider;
}

void CSlider::Draw(bool hover)
{
	POINT a = GetAbsolutePos();

	float Ratio = Value / (Max - Min);
	float Location = Ratio*m_iWidth;

	Render::Clear(a.x, a.y + 5, m_iWidth, 9, Color(12, 12, 12, MenuAlpha));
	Render::Clear(a.x, a.y + 5, Location, 9, Color(Menu::Window.CheatSkinTab.rUI_CURSORFILL.GetValue(), Menu::Window.CheatSkinTab.gUI_CURSORFILL.GetValue(), Menu::Window.CheatSkinTab.bUI_CURSORFILL.GetValue(), MenuAlpha));
	Render::Outline(a.x, a.y + 5, m_iWidth, 9, Color(0, 0, 0, MenuAlpha));


	char buffer[24];
	sprintf_s(buffer, "%.2f", Value);
	RECT txtSize = Render::GetTextSize(Render::Fonts::MenuBold, buffer);
	Render::Text(a.x + Location - txtSize.right / 2, a.y + 10, Color(Menu::Window.CheatSkinTab.rText.GetValue(), Menu::Window.CheatSkinTab.gText.GetValue(), Menu::Window.CheatSkinTab.bText.GetValue(), MenuAlpha), Render::Fonts::MenuBold, buffer); // 200 200 200
}

void CSlider::OnUpdate()
{
	POINT a = GetAbsolutePos();
	m_iHeight = 11;

	if (DoDrag)
	{
		if (GUI.GetKeyState(VK_LBUTTON))
		{
			POINT m = GUI.GetMouse();
			float NewX;
			float Ratio;
			NewX = m.x - a.x - 1;
			if (NewX < 0) NewX = 0;
			if (NewX > m_iWidth) NewX = m_iWidth;
			Ratio = NewX / float(m_iWidth);
			Value = Min + (Max - Min)*Ratio;
		}
		else
		{
			DoDrag = false;
		}
	}
}

void CSlider::OnClick() {
	POINT a = GetAbsolutePos();
	RECT SliderRegion = { a.x, a.y, m_iWidth, 11 };
	if (GUI.IsMouseInRegion(SliderRegion))
	{
		DoDrag = true;
	}
}

float CSlider::GetValue()
{
	return Value;
}

void CSlider::SetValue(float v)
{
	Value = v;
}

void CSlider::SetBoundaries(float min, float max)
{
	Min = min; Max = max;
}
#pragma endregion Implementations of the Slider functions

#pragma region Sliders2

CSlider2::CSlider2()
{
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_Clickable | UIFlags::UI_SaveFile;

	FileControlType = UIControlTypes::UIC_Slider;
}

void CSlider2::Draw(bool hover)
{
	POINT a = GetAbsolutePos();

	float Ratio = Value / (Max - Min);
	float Location = Ratio*m_iWidth;

	Render::Clear(a.x, a.y + 5, m_iWidth, 9, Color(12, 12, 12, MenuAlpha));
	Render::Clear(a.x, a.y + 5, Location, 9, Color(Menu::Window.CheatSkinTab.rUI_CURSORFILL.GetValue(), Menu::Window.CheatSkinTab.gUI_CURSORFILL.GetValue(), Menu::Window.CheatSkinTab.bUI_CURSORFILL.GetValue(), MenuAlpha));
	Render::Outline(a.x, a.y + 5, m_iWidth, 9, Color(0, 0, 0, MenuAlpha));


	char buffer[24];
	sprintf_s(buffer, "%.f", Value);
	RECT txtSize = Render::GetTextSize(Render::Fonts::MenuBold, buffer);
	Render::Text(a.x + Location - txtSize.right / 2, a.y + 10, Color(Menu::Window.CheatSkinTab.rText.GetValue(), Menu::Window.CheatSkinTab.gText.GetValue(), Menu::Window.CheatSkinTab.bText.GetValue(), MenuAlpha), Render::Fonts::MenuBold, buffer); // 200 200 200
}

void CSlider2::OnUpdate()
{
	POINT a = GetAbsolutePos();
	m_iHeight = 11;

	if (DoDrag)
	{
		if (GUI.GetKeyState(VK_LBUTTON))
		{
			POINT m = GUI.GetMouse();
			float NewX;
			float Ratio;
			NewX = m.x - a.x - 1;
			if (NewX < 0) NewX = 0;
			if (NewX > m_iWidth) NewX = m_iWidth;
			Ratio = NewX / float(m_iWidth);
			Value = Min + (Max - Min)*Ratio;
		}
		else
		{
			DoDrag = false;
		}
	}
}

void CSlider2::OnClick() {
	POINT a = GetAbsolutePos();
	RECT SliderRegion = { a.x, a.y, m_iWidth, 11 };
	if (GUI.IsMouseInRegion(SliderRegion))
	{
		DoDrag = true;
	}
}

float CSlider2::GetValue()
{
	return Value;
}

void CSlider2::SetValue(float v)
{
	Value = v;
}

void CSlider2::SetBoundaries(float min, float max)
{
	Min = min; Max = max;
}
#pragma endregion Slider2

#pragma region Slider3

CSlider3::CSlider3()
{
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_Clickable | UIFlags::UI_SaveFile;

	FileControlType = UIControlTypes::UIC_Slider;
}

void CSlider3::Draw(bool hover)
{
	POINT a = GetAbsolutePos();

	int Ratio = Value / (Max - Min);
	int Location = Ratio*m_iWidth;

	Render::Clear(a.x, a.y + 5, m_iWidth, 9, Color(12, 12, 12, MenuAlpha));
	Render::Clear(a.x, a.y + 5, Location, 9, Color(Menu::Window.CheatSkinTab.rUI_CURSORFILL.GetValue(), Menu::Window.CheatSkinTab.gUI_CURSORFILL.GetValue(), Menu::Window.CheatSkinTab.bUI_CURSORFILL.GetValue(), MenuAlpha));
	Render::Outline(a.x, a.y + 5, m_iWidth, 9, Color(0, 0, 0, MenuAlpha));


	char buffer[24];
	sprintf_s(buffer, "%", Value);
	RECT txtSize = Render::GetTextSize(Render::Fonts::MenuBold, buffer);
	Render::Text(a.x + Location - txtSize.right / 2, a.y + 10, Color(Menu::Window.CheatSkinTab.rText.GetValue(), Menu::Window.CheatSkinTab.gText.GetValue(), Menu::Window.CheatSkinTab.bText.GetValue(), MenuAlpha), Render::Fonts::MenuBold, buffer); //200 200 200
}

void CSlider3::OnUpdate()
{
	POINT a = GetAbsolutePos();
	m_iHeight = 11;

	if (DoDrag)
	{
		if (GUI.GetKeyState(VK_LBUTTON))
		{
			POINT m = GUI.GetMouse();
			int NewX;
			int Ratio;
			NewX = m.x - a.x - 1;
			if (NewX < 0) NewX = 0;
			if (NewX > m_iWidth) NewX = m_iWidth;
			Ratio = NewX / int(m_iWidth);
			Value = Min + (Max - Min)*Ratio;
		}
		else
		{
			DoDrag = false;
		}
	}
}

void CSlider3::OnClick() {
	POINT a = GetAbsolutePos();
	RECT SliderRegion = { a.x, a.y, m_iWidth, 11 };
	if (GUI.IsMouseInRegion(SliderRegion))
	{
		DoDrag = true;
	}
}

int CSlider3::GetValue()
{
	return Value;
}

void CSlider3::SetValue(int v)
{
	Value = v;
}

void CSlider3::SetBoundaries(int min, int max)
{
	Min = min; Max = max;
}
#pragma endregion Slider3


#pragma region KeyBinders

char* KeyStrings[254] = { nullptr, "Left Mouse", "Right Mouse", "Control+Break", "Middle Mouse", "Mouse 4", "Mouse 5",
nullptr, "Backspace", "TAB", nullptr, nullptr, nullptr, "ENTER", nullptr, nullptr, "SHIFT", "CTRL", "ALT", "PAUSE",
"CAPS LOCK", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "ESC", nullptr, nullptr, nullptr, nullptr, "SPACEBAR",
"PG UP", "PG DOWN", "END", "HOME", "Left", "Up", "Right", "Down", nullptr, "Print", nullptr, "Print Screen", "Insert",
"Delete", nullptr, "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X",
"Y", "Z", "Left Windows", "Right Windows", nullptr, nullptr, nullptr, "NUM 0", "NUM 1", "NUM 2", "NUM 3", "NUM 4", "NUM 5", "NUM 6",
"NUM 7", "NUM 8", "NUM 9", "*", "+", "_", "-", ".", "/", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
"F13", "F14", "F15", "F16", "F17", "F18", "F19", "F20", "F21", "F22", "F23", "F24", nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, "NUM LOCK", "SCROLL LOCK", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, "LSHIFT", "RSHIFT", "LCONTROL", "RCONTROL", "LMENU", "RMENU", nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "Next Track", "Previous Track", "Stop", "Play/Pause", nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, ";", "+", ",", "-", ".", "/?", "~", nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "[{", "\\|", "}]", "'\"", nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };

CKeyBind::CKeyBind()
{
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_Clickable | UIFlags::UI_SaveFile;
	FileControlType = UIControlTypes::UIC_KeyBind;
}

void CKeyBind::Draw(bool hover)
{
	POINT a = GetAbsolutePos();

	Render::Outline(a.x, a.y, m_iWidth, m_iHeight, Color(2, 2, 2, MenuAlpha));
	Render::Clear(a.x + 2, a.y + 2, m_iWidth - 4, 12, Color(50, 50, 50, MenuAlpha));
	if (hover)
		Render::Clear(a.x + 2, a.y + 2, m_iWidth - 4, 12, Color(55, 55, 55, MenuAlpha));
	bool GoodKeyName = false;
	char NameBuffer[128];
	char* KeyName = "Not Bound";

	if (IsGettingKey)
	{
		KeyName = "<Press A Key>";
	}
	else
	{
		if (Key >= 0)
		{
			KeyName = KeyStrings[Key];
			if (KeyName)
			{
				GoodKeyName = true;
			}
			else
			{
				if (GetKeyNameText(Key << 16, NameBuffer, 127))
				{
					KeyName = NameBuffer;
					GoodKeyName = true;
				}
			}
		}

		if (!GoodKeyName)
		{
			KeyName = "No Key Bound";
		}
	}


	Render::Text(a.x + 4, a.y + 2 - 1, Color(Menu::Window.CheatSkinTab.rText.GetValue(), Menu::Window.CheatSkinTab.gText.GetValue(), Menu::Window.CheatSkinTab.bText.GetValue(), MenuAlpha), Render::Fonts::Menu, KeyName); // 244 244 244
}

void CKeyBind::OnUpdate() {
	m_iHeight = 16;
	POINT a = GetAbsolutePos();
	if (IsGettingKey)
	{
		for (int i = 0; i < 255; i++)
		{
			if (GUI.GetKeyPress(i))
			{
				if (i == VK_ESCAPE)
				{
					IsGettingKey = false;
					Key = -1;
					return;
				}

				Key = i;
				IsGettingKey = false;
				return;
			}
		}
	}
}

void CKeyBind::OnClick() {
	POINT a = GetAbsolutePos();
	if (!IsGettingKey)
	{
		IsGettingKey = true;
	}
}

int CKeyBind::GetKey()
{
	return Key;
}

void CKeyBind::SetKey(int key)
{
	Key = key;
}

#pragma endregion Implementations of the KeyBind Control functions

#pragma region Button
CButton::CButton()
{
	m_iWidth = 177;
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_Clickable;
	FileControlType == UIControlTypes::UIC_Button;
	Text = "Default";
	CallBack = nullptr;
	FileIdentifier = "Default";
}

void CButton::Draw(bool hover)
{
	POINT a = GetAbsolutePos();
	Render::Outline(a.x, a.y, m_iWidth, m_iHeight, Color(2, 2, 2, MenuAlpha));
	if (hover)
		Render::Clear(a.x + 2, a.y + 2, m_iWidth - 4, m_iHeight - 4, Color(40, 40, 40, MenuAlpha));
	else
		Render::Clear(a.x + 2, a.y + 2, m_iWidth - 4, m_iHeight - 4, Color(35, 35, 35, MenuAlpha));

	RECT TextSize = Render::GetTextSize(Render::Fonts::MenuBold, Text.c_str());
	int TextX = a.x + (m_iWidth / 2) - (TextSize.left / 2);
	int TextY = a.y + (m_iHeight / 2) - (TextSize.bottom / 2);

	Render::Text(TextX, TextY - 1, Color(Menu::Window.CheatSkinTab.rText.GetValue(), Menu::Window.CheatSkinTab.gText.GetValue(), Menu::Window.CheatSkinTab.bText.GetValue(), MenuAlpha), Render::Fonts::MenuBold, Text.c_str()); // 200 200 200
}

void CButton::SetText(std::string text)
{
	Text = text;
}

void CButton::SetCallback(CButton::ButtonCallback_t callback)
{
	CallBack = callback;
}

void CButton::OnUpdate()
{
	m_iHeight = 26;
}

void CButton::OnClick()
{
	if (CallBack)
		CallBack();
}
#pragma endregion Implementations of the Button functions

#pragma region ComboBox
CComboBox::CComboBox()
{
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_Clickable | UIFlags::UI_Focusable | UIFlags::UI_SaveFile;
	FileControlType = UIControlTypes::UIC_ComboBox;
	winWidth = 400;
	winHeight = 400;
}

void CComboBox::Draw(bool hover)
{
	POINT a = GetAbsolutePos();
	RECT Region = { a.x, a.y, m_iWidth, 20 };
	Render::Outline(a.x, a.y, m_iWidth, 20, Color(2, 2, 2, MenuAlpha));
	Render::Clear(a.x + 2, a.y + 2, m_iWidth - 4, 16, Color(35, 35, 35, MenuAlpha));

	if (GUI.IsMouseInRegion(Region))
		Render::Clear(a.x + 2, a.y + 2, m_iWidth - 4, 16, Color(40, 40, 40, MenuAlpha));

	if (Items.size() > 0)
	{
		RECT txtSize = Render::GetTextSize(Render::Fonts::Menu, GetItem().c_str());
		Render::Text(a.x + 4, a.y + (Region.bottom / 2) - (txtSize.bottom / 2), Color(Menu::Window.CheatSkinTab.rText.GetValue(), Menu::Window.CheatSkinTab.gText.GetValue(), Menu::Window.CheatSkinTab.bText.GetValue(), MenuAlpha), Render::Fonts::Menu, GetItem().c_str()); // 244 244 244

		if (IsOpen)
		{
			if (Menu::Window.Open())
			{
			}

			Render::Clear(a.x, a.y + 20, m_iWidth, Items.size() * 16, Color(35, 35, 35, MenuAlpha));

			for (int i = 0; i < Items.size(); i++)
			{
				RECT ItemRegion = { a.x, a.y + 17 + i * 16, m_iWidth, 16 };

				// Hover
				if (GUI.IsMouseInRegion(ItemRegion))
				{
					Render::Clear(a.x + 2, a.y + 20 + i * 16, m_iWidth - 4, 16, Color(40, 40, 40, MenuAlpha));
				}

				Render::Text(a.x + 4, a.y + 19 + i * 16 - 1 + 4, Color(Menu::Window.CheatSkinTab.rText.GetValue(), Menu::Window.CheatSkinTab.gText.GetValue(), Menu::Window.CheatSkinTab.bText.GetValue(), MenuAlpha), Render::Fonts::Menu, Items[i].c_str()); // 244 244 244
			}
			Render::Outline(a.x, a.y + 20, m_iWidth, Items.size() * 16, Color(2, 2, 2, MenuAlpha));
		}
	}
	Vertex_t Verts2[3];
	Verts2[0].m_Position.x = a.x + m_iWidth - 10;
	Verts2[0].m_Position.y = a.y + 8;
	Verts2[1].m_Position.x = a.x + m_iWidth - 5;
	Verts2[1].m_Position.y = a.y + 8;
	Verts2[2].m_Position.x = a.x + m_iWidth - 7.5;
	Verts2[2].m_Position.y = a.y + 11;

	Render::Polygon(3, Verts2, Color(2, 2, 2, MenuAlpha));
}

void CComboBox::AddItem(std::string text)
{
	Items.push_back(text);
	SelectedIndex = 0;
}

void CComboBox::OnUpdate()
{
	if (IsOpen)
	{
		m_iHeight = 16 + 16 * Items.size();

		if (parent->GetFocus() != this)
			IsOpen = false;
	}
	else
	{
		m_iHeight = 16;
	}

}

void CComboBox::OnClick()
{
	POINT a = GetAbsolutePos();
	RECT Region = { a.x, a.y, m_iWidth, 16 };

	if (IsOpen)
	{
		if (!GUI.IsMouseInRegion(Region))
		{
			for (int i = 0; i < Items.size(); i++)
			{
				RECT ItemRegion = { a.x, a.y + 16 + i * 16, m_iWidth, 16 };

				if (GUI.IsMouseInRegion(ItemRegion))
				{
					SelectedIndex = i;
				}
			}
		}

		IsOpen = false;
	}
	else
	{
		IsOpen = true;
	}

}

int CComboBox::GetIndex()
{
	return SelectedIndex;
}

void CComboBox::SetIndex(int index)
{
	SelectedIndex = index;
}

std::string CComboBox::GetItem()
{
	if (SelectedIndex >= 0 && SelectedIndex < Items.size())
	{
		return Items[SelectedIndex];
	}

	return "Error";
}

void CComboBox::SelectIndex(int idx)
{
	if (idx >= 0 && idx < Items.size())
	{
		SelectedIndex = idx;
	}
}

#pragma endregion Implementations of the ComboBox functions

char* KeyDigits[254] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X",
"Y", "Z", nullptr, nullptr, nullptr, nullptr, nullptr, "0", "1", "2", "3", "4", "5", "6",
"7", "8", "9", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, ";", "+", ",", "-", ".", "?", "~", nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "{", "|", "}", "\"", nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };

CTextField::CTextField()
{
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_Clickable | UIFlags::UI_SaveFile;
	FileControlType = UIControlTypes::UIC_KeyBind;
}

std::string CTextField::getText()
{
	return text;
}

void CTextField::SetText(std::string stext)
{
	text = stext;
}

void CTextField::Draw(bool hover)
{
	POINT a = GetAbsolutePos();

	Render::Outline(a.x, a.y, m_iWidth, 16, Color(2, 2, 2, MenuAlpha));
	Render::Clear(a.x + 2, a.y + 2, m_iWidth - 4, 12, Color(50, 50, 50, MenuAlpha));
	if (hover || IsGettingKey)
		Render::Clear(a.x + 2, a.y + 2, m_iWidth - 4, 12, Color(55, 55, 55, MenuAlpha));

	const char *cstr = text.c_str();

	Render::Text(a.x + 2, a.y + 2 - 1, Color(244, 244, 244, MenuAlpha), Render::Fonts::Menu, cstr);
}

void CTextField::OnUpdate()
{
	m_iHeight = 16;
	POINT a = GetAbsolutePos();
	POINT b;
	const char *strg = text.c_str();

	if (IsGettingKey)
	{
		b = GetAbsolutePos();
		for (int i = 0; i < 255; i++)
		{

			if (GUI.GetKeyPress(i))
			{
				if (i == VK_ESCAPE || i == VK_RETURN || i == VK_INSERT)
				{
					IsGettingKey = false;
					return;
				}

				if (i == VK_BACK && strlen(strg) != 0)
				{
					text = text.substr(0, strlen(strg) - 1);
				}

				if (strlen(strg) < 20 && i != NULL && KeyDigits[i] != nullptr)
				{
					if (GetAsyncKeyState(VK_SHIFT))
					{
						text = text + KeyDigits[i];
					}
					else
					{
						text = text + KeyDigits[i];
					}
					return;
				}

				if (strlen(strg) < 20 && i == 32)
				{
					text = text + " ";
					return;
				}
			}
		}
	}
}

void CTextField::OnClick()
{
	POINT a = GetAbsolutePos();
	if (!IsGettingKey)
	{
		IsGettingKey = true;
	}
}

#pragma region TextField2

char* KeyDigitss[254] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X",
"Y", "Z", nullptr, nullptr, nullptr, nullptr, nullptr, "0", "1", "2", "3", "4", "5", "6",
"7", "8", "9", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };

CTextField2::CTextField2()
{
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_Clickable | UIFlags::UI_SaveFile;
	FileControlType = UIControlTypes::UIC_KeyBind;
}

std::string CTextField2::getText()
{
	return text;
}

void CTextField2::SetText(std::string stext)
{
	text = stext;
}

void CTextField2::Draw(bool hover)
{
	POINT a = GetAbsolutePos();

	Render::Clear(a.x, a.y, m_iWidth, m_iHeight, Color(30, 30, 30, MenuAlpha));
	if (hover || IsGettingKey)
		Render::Clear(a.x + 2, a.y + 2, m_iWidth - 4, m_iHeight - 4, Color(35, 35, 35, MenuAlpha7));

	const char *cstr = text.c_str();

	Render::Text(a.x + 2, a.y + 2, Color(Menu::Window.CheatSkinTab.rText.GetValue(), Menu::Window.CheatSkinTab.gText.GetValue(), Menu::Window.CheatSkinTab.bText.GetValue(), MenuAlpha), Render::Fonts::MenuBold, cstr); //255 255 255
}

void CTextField2::OnUpdate()
{
	m_iHeight = 16;
	POINT a = GetAbsolutePos();
	POINT b;
	const char *strg = text.c_str();

	if (IsGettingKey)
	{
		b = GetAbsolutePos();
		for (int i = 0; i < 255; i++)
		{
			if (GUI.GetKeyPress(i))
			{
				if (i == VK_ESCAPE || i == VK_RETURN || i == VK_INSERT)
				{
					IsGettingKey = false;
					return;
				}

				if (i == VK_BACK && strlen(strg) != 0)
				{
					text = text.substr(0, strlen(strg) - 1);
				}

				if (strlen(strg) < 20 && i != NULL && KeyDigitss[i] != nullptr)
				{
					text = text + KeyDigitss[i];
					return;
				}

				if (strlen(strg) < 20 && i == 32)
				{
					text = text + " ";
					return;
				}
			}
		}
	}
}

void CTextField2::OnClick()
{
	POINT a = GetAbsolutePos();
	if (!IsGettingKey)
	{
		IsGettingKey = true;
	}
}

#pragma endregion Implementation of the Textfield2