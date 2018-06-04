#include "GUI.h"
#include "Menu.h"
#include "RenderManager.h"
#include <algorithm>
#include "tinyxml2.h"
#include "Controls.h"

float MenuAlpha = 0.05f; //0.05f
float MenuAlpha3 = 0.05f;
float MenuAlpha5 = 0.05f;
float MenuAlpha7 = 0.05f;
float MenuAlpha9 = 0.05f;
float MenuAlpha11 = 0.05f;
float MenuAlpha13 = 0.05f;
float MenuAlpha15 = 0.05f;
float MenuAlpha17 = 0.05f;
float MenuAlpha19 = 0.05f;
float MenuAlpha21 = 0.05f;
float Globals::MenuAlpha22 = MenuAlpha21;
float Globals::MenuAlpha20 = MenuAlpha19;
float Globals::MenuAlpha18 = MenuAlpha17;
float Globals::MenuAlpha16 = MenuAlpha15;
float Globals::MenuAlpha14 = MenuAlpha13;
float Globals::MenuAlpha12 = MenuAlpha11;
float Globals::MenuAlpha10 = MenuAlpha9;
float Globals::MenuAlpha8 = MenuAlpha7;
float Globals::MenuAlpha6 = MenuAlpha5;
float Globals::MenuAlpha2 = MenuAlpha;
float Globals::MenuAlpha4 = MenuAlpha3;


CGUI GUI;
bool SaveFile = false;
bool LoadFile = false;

CGUI::CGUI()
{

}

#define UI_CURSORSIZE       12
#define UI_CURSOROUTLINE    Color(20,20,20,MenuAlpha13)
#define UI_WIN_TOPHEIGHT	26
#define UI_WIN_TITLEHEIGHT	0 //0
#define UI_TAB_WIDTH		150 
#define UI_TAB_HEIGHT		50
#define UI_WIN_CLOSE_X		20
#define UI_WIN_CLOSE_Y      6
#define UI_CHK_SIZE			16
#define COL_WHITE           Color(255, 255, 255, MenuAlpha17)
#define UI_COL_MAINE        Color(0, 204, 0, MenuAlpha) // useless
#define UI_COL_MAINDARK     Color(113, 236, 159, MenuAlpha) // useless
#define UI_COL_FADEMAIN     Color(27, 206, 94, MenuAlpha15) // useless
#define UI_COL_CLIENTBACK   Color(238, 0, 50, MenuAlpha) // useless
#define UI_COL_TABTEXT      Color(255, 255, 255, MenuAlpha) // useless
#define UI_COL_GROUPOUTLINE Color(222, 100, 150, MenuAlpha) // useless

void CGUI::Draw()
{
	bool ShouldDrawCursor = false;

	for (auto window : Windows)
	{
		if (window->m_bIsOpen)
			MenuAlpha = min(MenuAlpha + 6, 255);
		else
			MenuAlpha = max(MenuAlpha - 6, 0);
		
		if (window->m_bIsOpen)
			MenuAlpha5 = min(MenuAlpha5 + 6, 120);
		else
			MenuAlpha5 = max(MenuAlpha5 - 6, 0);

		if (window->m_bIsOpen)
			MenuAlpha3 = min(MenuAlpha3 + 6, 15);
		else
			MenuAlpha3 = max(MenuAlpha3 - 6, 0);

		if (window->m_bIsOpen)
			MenuAlpha7 = min(MenuAlpha7 + 6, 200);
		else
			MenuAlpha7 = max(MenuAlpha7 - 6, 0);

		if (window->m_bIsOpen)
			MenuAlpha9 = min(MenuAlpha9 + 6, 245);
		else
			MenuAlpha9 = max(MenuAlpha9 - 6, 0);

		if (window->m_bIsOpen)
			MenuAlpha11 = min(MenuAlpha11 + 6, 80);
		else
			MenuAlpha11 = max(MenuAlpha11 - 6, 0);

		if (window->m_bIsOpen)
			MenuAlpha13 = min(MenuAlpha13 + 6, 140);
		else
			MenuAlpha13 = max(MenuAlpha13 - 6, 0);

		if (window->m_bIsOpen)
			MenuAlpha15 = min(MenuAlpha15 + 6, 40);
		else
			MenuAlpha15 = max(MenuAlpha15 - 6, 0);

		if (window->m_bIsOpen)
			MenuAlpha17 = min(MenuAlpha17 + 6, 50);
		else
			MenuAlpha17 = max(MenuAlpha17 - 6, 0);

		if (window->m_bIsOpen)
			MenuAlpha21 = min(MenuAlpha21 + 6, 1);
		else
			MenuAlpha21 = max(MenuAlpha21 - 6, 0);

		if (window->m_bIsOpen)
			MenuAlpha19 = min(MenuAlpha19 + 6, 100);
		else
			MenuAlpha19 = max(MenuAlpha19 - 6, 0);
		
		{
			ShouldDrawCursor = true;
			DrawWindow(window);
		}
	}
	if (ShouldDrawCursor)
	{
		Render::Clear(Mouse.x + 1, Mouse.y, 1, 17, Color(Menu::Window.CheatSkinTab.rUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.gUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.bUI_COURSOUR.GetValue(), MenuAlpha));
		for (int i = 0; i < 11; i++)
			Render::Clear(Mouse.x + 2 + i, Mouse.y + 1 + i, 1, 1, Color(Menu::Window.CheatSkinTab.rUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.gUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.bUI_COURSOUR.GetValue(), MenuAlpha));
		Render::Clear(Mouse.x + 8, Mouse.y + 12, 5, 1, Color(Menu::Window.CheatSkinTab.rUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.gUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.bUI_COURSOUR.GetValue(), MenuAlpha));
		Render::Clear(Mouse.x + 8, Mouse.y + 13, 1, 1, Color(Menu::Window.CheatSkinTab.rUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.gUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.bUI_COURSOUR.GetValue(), MenuAlpha));
		Render::Clear(Mouse.x + 9, Mouse.y + 14, 1, 2, Color(Menu::Window.CheatSkinTab.rUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.gUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.bUI_COURSOUR.GetValue(), MenuAlpha));
		Render::Clear(Mouse.x + 10, Mouse.y + 16, 1, 2, Color(Menu::Window.CheatSkinTab.rUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.gUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.bUI_COURSOUR.GetValue(), MenuAlpha));
		Render::Clear(Mouse.x + 8, Mouse.y + 18, 2, 1, Color(Menu::Window.CheatSkinTab.rUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.gUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.bUI_COURSOUR.GetValue(), MenuAlpha));
		Render::Clear(Mouse.x + 7, Mouse.y + 16, 1, 2, Color(Menu::Window.CheatSkinTab.rUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.gUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.bUI_COURSOUR.GetValue(), MenuAlpha));
		Render::Clear(Mouse.x + 6, Mouse.y + 14, 1, 2, Color(Menu::Window.CheatSkinTab.rUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.gUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.bUI_COURSOUR.GetValue(), MenuAlpha));
		Render::Clear(Mouse.x + 5, Mouse.y + 13, 1, 1, Color(Menu::Window.CheatSkinTab.rUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.gUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.bUI_COURSOUR.GetValue(), MenuAlpha));
		Render::Clear(Mouse.x + 4, Mouse.y + 14, 1, 1, Color(Menu::Window.CheatSkinTab.rUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.gUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.bUI_COURSOUR.GetValue(), MenuAlpha));
		Render::Clear(Mouse.x + 3, Mouse.y + 15, 1, 1, Color(Menu::Window.CheatSkinTab.rUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.gUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.bUI_COURSOUR.GetValue(), MenuAlpha));
		Render::Clear(Mouse.x + 2, Mouse.y + 16, 1, 1, Color(Menu::Window.CheatSkinTab.rUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.gUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.bUI_COURSOUR.GetValue(), MenuAlpha));
		for (int i = 0; i < 4; i++)
			Render::Clear(Mouse.x + 2 + i, Mouse.y + 2 + i, 1, 14 - (i * 2), Color(Menu::Window.CheatSkinTab.rUI_COURSOUR.GetValue() - (i * 4), Menu::Window.CheatSkinTab.gUI_COURSOUR.GetValue() - (i * 4), Menu::Window.CheatSkinTab.bUI_COURSOUR.GetValue() - (i * 4), MenuAlpha));
		Render::Clear(Mouse.x + 6, Mouse.y + 6, 1, 8, Color(Menu::Window.CheatSkinTab.rUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.gUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.bUI_COURSOUR.GetValue(), MenuAlpha));
		Render::Clear(Mouse.x + 7, Mouse.y + 7, 1, 9, Color(Menu::Window.CheatSkinTab.rUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.gUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.bUI_COURSOUR.GetValue(), MenuAlpha));
		for (int i = 0; i < 4; i++)
			Render::Clear(Mouse.x + 8 + i, Mouse.y + 8 + i, 1, 4 - i, Color(Menu::Window.CheatSkinTab.rUI_COURSOUR.GetValue() - (i * 4), Menu::Window.CheatSkinTab.gUI_COURSOUR.GetValue() - (i * 4), Menu::Window.CheatSkinTab.bUI_COURSOUR.GetValue() - (i * 4), MenuAlpha));
		Render::Clear(Mouse.x + 8, Mouse.y + 14, 1, 4, Color(Menu::Window.CheatSkinTab.rUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.gUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.bUI_COURSOUR.GetValue(), MenuAlpha));
		Render::Clear(Mouse.x + 9, Mouse.y + 16, 1, 2, Color(Menu::Window.CheatSkinTab.rUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.gUI_COURSOUR.GetValue(), Menu::Window.CheatSkinTab.bUI_COURSOUR.GetValue(), MenuAlpha));
	}
}

void CGUI::Update()
{
	std::copy(keys, keys + 255, oldKeys);
	for (int x = 0; x < 255; x++) {
		keys[x] = static_cast<bool>(GetAsyncKeyState(x));
	}

	POINT mp; GetCursorPos(&mp);
	ScreenToClient(GetForegroundWindow(), &mp);
	Mouse.x = mp.x; Mouse.y = mp.y;

	RECT Screen = Render::GetViewport();

	for (auto bind : WindowBinds)
	{
		if (GetKeyPress(bind.first) && bind.second != nullptr)
		{
			bind.second->Toggle();
		}
	}

	if (IsDragging && !GetKeyState(VK_LBUTTON))
	{
		IsDragging = false;
		DraggingWindow = nullptr;
	}

	if (IsDragging && GetKeyState(VK_LBUTTON) && !GetKeyPress(VK_LBUTTON))
	{
		if (DraggingWindow)
		{
			DraggingWindow->m_x = Mouse.x - DragOffsetX;
			DraggingWindow->m_y = Mouse.y - DragOffsetY;
		}
	}

	for (auto window : Windows)
	{
		if (window->m_bIsOpen)
		{
			bool bCheckWidgetClicks = false;

			if (GetKeyPress(VK_LBUTTON))
			{
				bCheckWidgetClicks = true;

				if (IsMouseInRegion(window->m_y, window->m_x + window->m_iWidth, window->m_y + window->m_iHeight, window->m_x))
				{
					if (IsMouseInRegion(window->m_y, window->m_x + window->m_iWidth, window->m_y + UI_WIN_CLOSE_X, window->m_x + window->m_iWidth - UI_WIN_CLOSE_X))
					{
						window->Toggle();
					}
					else
						if (IsMouseInRegion(window->GetTabArea()))
						{

							bCheckWidgetClicks = true;

							int iTab = 0;
							int TabCount = window->Tabs.size();
							if (TabCount)
							{
								int TabCount = window->Tabs.size();
								int TabSize = (window->m_iWidth - UI_TAB_WIDTH - UI_WIN_TITLEHEIGHT - 214) / TabCount;
								int Dist = Mouse.y - (window->m_y + UI_WIN_TITLEHEIGHT + UI_WIN_TOPHEIGHT);
								if (Dist < (TabSize*TabCount))
								{
									while (Dist > TabSize)
									{
										if (Dist > TabSize)
										{
											iTab++;
											Dist -= TabSize;
										}
										if (iTab == (TabCount - 1))
										{
											break;
										}
									}
									window->SelectedTab = window->Tabs[iTab];

									bCheckWidgetClicks = false;
									window->IsFocusingControl = false;
									window->FocusedControl = nullptr;
								}
							}

						}
						else if (IsMouseInRegion(window->GetClientArea()))
						{
							bCheckWidgetClicks = true;
						}
						else
						{
							IsDragging = true;
							DraggingWindow = window;
							DragOffsetX = Mouse.x - window->m_x;
							DragOffsetY = Mouse.y - window->m_y;

							window->IsFocusingControl = false;
							window->FocusedControl = nullptr;
						}
				}
				else
				{
					window->IsFocusingControl = false;
					window->FocusedControl = nullptr;
				}
			}

			if (window->SelectedTab != nullptr)
			{
				bool SkipWidget = false;
				CControl* SkipMe = nullptr;

				if (window->IsFocusingControl)
				{
					if (window->FocusedControl != nullptr)
					{
						SkipWidget = true;
						SkipMe = window->FocusedControl;

						POINT cAbs = window->FocusedControl->GetAbsolutePos();
						RECT controlRect = { cAbs.x, cAbs.y, window->FocusedControl->m_iWidth, window->FocusedControl->m_iHeight };
						window->FocusedControl->OnUpdate();

						if (window->FocusedControl->Flag(UIFlags::UI_Clickable) && IsMouseInRegion(controlRect) && bCheckWidgetClicks)
						{
							window->FocusedControl->OnClick();

							window->IsFocusingControl = false;
							window->FocusedControl = nullptr;
							bCheckWidgetClicks = false;
						}
					}
				}

				for (auto control : window->SelectedTab->Controls)
				{
					if (control != nullptr)
					{
						if (SkipWidget && SkipMe == control)
							continue;

						control->parent = window;

						POINT cAbs = control->GetAbsolutePos();
						RECT controlRect = { cAbs.x, cAbs.y, control->m_iWidth, control->m_iHeight };
						control->OnUpdate();

						if (control->Flag(UIFlags::UI_Clickable) && IsMouseInRegion(controlRect) && bCheckWidgetClicks)
						{
							control->OnClick();
							bCheckWidgetClicks = false;

							if (control->Flag(UIFlags::UI_Focusable))
							{
								window->IsFocusingControl = true;
								window->FocusedControl = control;
							}
							else
							{
								window->IsFocusingControl = false;
								window->FocusedControl = nullptr;
							}

						}
					}
				}

				if (bCheckWidgetClicks)
				{
					window->IsFocusingControl = false;
					window->FocusedControl = nullptr;
				}
			}
		}
	}
}

bool CGUI::GetKeyPress(unsigned int key)
{
	if (keys[key] == true && oldKeys[key] == false)
		return true;
	else
		return false;
}

bool CGUI::GetKeyState(unsigned int key)
{
	return keys[key];
}

bool CGUI::IsMouseInRegion(int y, int x2, int y2, int x)
{
	if (Mouse.x > x && Mouse.y > y && Mouse.x < x2 && Mouse.y < y2)
		return true;
	else
		return false;
}

bool CGUI::IsMouseInRegion(RECT region)
{
	return IsMouseInRegion(region.top, region.left + region.right, region.top + region.bottom, region.left);
}

POINT CGUI::GetMouse()
{
	return Mouse;
}

bool CGUI::DrawWindow(CWindow* window)
{
	int TextX = window->m_x + (window->m_iWidth / 2);
	Render::Clear(window->m_x, window->m_y, window->m_iWidth, window->m_iHeight, Color(Menu::Window.CheatSkinTab.rBACKGROUND.GetValue(), Menu::Window.CheatSkinTab.gBACKGROUND.GetValue(), Menu::Window.CheatSkinTab.bBACKGROUND.GetValue(), MenuAlpha)); //25 25 25
	Render::Clear(window->m_x, window->m_y + 2 + 20, window->m_iWidth, 4, Color(Menu::Window.CheatSkinTab.rUI_COL_MAIN.GetValue(), Menu::Window.CheatSkinTab.gUI_COL_MAIN.GetValue(), Menu::Window.CheatSkinTab.bUI_COL_MAIN.GetValue(), MenuAlpha11));
	Render::Text(TextX + 26, window->m_y + 1, Color(Menu::Window.CheatSkinTab.rUI_COL_MAIN.GetValue(), Menu::Window.CheatSkinTab.gUI_COL_MAIN.GetValue(), Menu::Window.CheatSkinTab.bUI_COL_MAIN.GetValue(), MenuAlpha19), Render::Fonts::MenuBold, "MICROSOFT.CC | Premium CSGO Cheat");
	// Tabs
	int TabCount = window->Tabs.size();
	int TabSize = (window->m_iWidth - UI_TAB_WIDTH - UI_WIN_TITLEHEIGHT - 214)/ TabCount;
	if (TabCount)
	{
		for (int i = 0; i < TabCount; i++)
		{
			RECT TabArea = { window->m_x, window->m_y + UI_WIN_TOPHEIGHT + UI_WIN_TITLEHEIGHT + (i*TabSize)/*insert shit here*/ , window->m_iWidth - window->m_iHeight - 200, TabSize  }; //RECT TabArea = { window->m_x, window->m_y + UI_WIN_TOPHEIGHT + UI_WIN_TITLEHEIGHT + (i*TabSize) , window->m_iWidth - window->m_iHeight - 200, TabSize  };
			CTab *tab = window->Tabs[i];

			Render::Clear(TabArea.left, TabArea.top, UI_TAB_WIDTH, 1, Color(0, 0, 0, MenuAlpha));
			Render::Clear(TabArea.left, TabArea.top + 1, UI_TAB_WIDTH, 1, Color(48, 48, 48, MenuAlpha));
			Color txtColor = Color(Menu::Window.CheatSkinTab.rUI_COL_TABSEPERATOR.GetValue(), Menu::Window.CheatSkinTab.gUI_COL_TABSEPERATOR.GetValue(), Menu::Window.CheatSkinTab.bUI_COL_TABSEPERATOR.GetValue(), MenuAlpha7);

			if (window->SelectedTab == tab)
			{
				Render::Clear(window->m_x, window->m_y + UI_WIN_TOPHEIGHT + UI_WIN_TITLEHEIGHT + (i*TabSize) + 2 /*insert shit here*/, UI_TAB_WIDTH, (TabSize) - 2, Color(Menu::Window.CheatSkinTab.rBACKGROUND.GetValue(), Menu::Window.CheatSkinTab.gBACKGROUND.GetValue(), Menu::Window.CheatSkinTab.bBACKGROUND.GetValue(), MenuAlpha)); //Render::Clear(window->m_x, window->m_y + UI_WIN_TOPHEIGHT + UI_WIN_TITLEHEIGHT + (i*TabSize) + 2, UI_TAB_WIDTH, TabSize - 2, Color(Menu::Window.CheatSkinTab.rBACKGROUND.GetValue(), Menu::Window.CheatSkinTab.gBACKGROUND.GetValue(), Menu::Window.CheatSkinTab.bBACKGROUND.GetValue(), MenuAlpha));
				txtColor = Color(Menu::Window.CheatSkinTab.rUI_COL_MAIN.GetValue(), Menu::Window.CheatSkinTab.gUI_COL_MAIN.GetValue(), Menu::Window.CheatSkinTab.bUI_COL_MAIN.GetValue(), MenuAlpha11);
			}
			else if (IsMouseInRegion(TabArea))
			{
				// Hover
				txtColor = Color(255, 255, 255, MenuAlpha7);
			}
			Render::Text(TabArea.left + 50 - UI_WIN_TOPHEIGHT - UI_WIN_TITLEHEIGHT + 30, TabArea.top + 50 - UI_WIN_TOPHEIGHT - UI_WIN_TITLEHEIGHT + 5, txtColor, Render::Fonts::Tabs, tab->Title.c_str());
		}
	}
	//Window Outline
	
	Render::Outline(window->m_x - 1, window->m_y - 1, window->m_iWidth + 2, window->m_iHeight + 2, Color(Menu::Window.CheatSkinTab.rUI_COL_SHADOW.GetValue(), Menu::Window.CheatSkinTab.gUI_COL_SHADOW.GetValue(), Menu::Window.CheatSkinTab.bUI_COL_SHADOW.GetValue(), MenuAlpha));
	Render::Outline(window->m_x - 2, window->m_y - 2, window->m_iWidth + 4, window->m_iHeight + 4, Color(Menu::Window.CheatSkinTab.rUI_COL_SHADOW.GetValue(), Menu::Window.CheatSkinTab.gUI_COL_SHADOW.GetValue(), Menu::Window.CheatSkinTab.bUI_COL_SHADOW.GetValue(), MenuAlpha));
	Render::Outline(window->m_x - 3, window->m_y - 3, window->m_iWidth + 6, window->m_iHeight + 6, Color(Menu::Window.CheatSkinTab.rUI_COL_SHADOW.GetValue(), Menu::Window.CheatSkinTab.gUI_COL_SHADOW.GetValue(), Menu::Window.CheatSkinTab.bUI_COL_SHADOW.GetValue(), MenuAlpha));
	Render::Outline(window->m_x - 4, window->m_y - 4, window->m_iWidth + 8, window->m_iHeight + 8, Color(Menu::Window.CheatSkinTab.rUI_COL_SHADOW.GetValue(), Menu::Window.CheatSkinTab.gUI_COL_SHADOW.GetValue(), Menu::Window.CheatSkinTab.bUI_COL_SHADOW.GetValue(), MenuAlpha));
	Render::Outline(window->m_x - 5, window->m_y - 5, window->m_iWidth + 10, window->m_iHeight + 10, Color(Menu::Window.CheatSkinTab.rUI_COL_SHADOW.GetValue(), Menu::Window.CheatSkinTab.gUI_COL_SHADOW.GetValue(), Menu::Window.CheatSkinTab.bUI_COL_SHADOW.GetValue(), MenuAlpha));
	Render::Outline(window->m_x - 6, window->m_y - 6, window->m_iWidth + 12, window->m_iHeight + 12, Color(Menu::Window.CheatSkinTab.rUI_COL_SHADOW.GetValue(), Menu::Window.CheatSkinTab.gUI_COL_SHADOW.GetValue(), Menu::Window.CheatSkinTab.bUI_COL_SHADOW.GetValue(), MenuAlpha));
	Render::Outline(window->m_x - 7, window->m_y - 7, window->m_iWidth + 14, window->m_iHeight + 14, Color(Menu::Window.CheatSkinTab.rUI_COL_SHADOW.GetValue(), Menu::Window.CheatSkinTab.gUI_COL_SHADOW.GetValue(), Menu::Window.CheatSkinTab.bUI_COL_SHADOW.GetValue(), MenuAlpha));
	
	if (window->SelectedTab != nullptr)
	{
		bool SkipWidget = false;
		CControl* SkipMe = nullptr;

		if (window->IsFocusingControl)
		{
			if (window->FocusedControl != nullptr)
			{
				SkipWidget = true;
				SkipMe = window->FocusedControl;
			}
		}

		for (auto control : window->SelectedTab->Controls)
		{
			if (SkipWidget && SkipMe == control)
				continue;

			if (control != nullptr && control->Flag(UIFlags::UI_Drawable))
			{
				POINT cAbs = control->GetAbsolutePos();
				RECT controlRect = { cAbs.x, cAbs.y, control->m_iWidth, control->m_iHeight };
				bool hover = false;
				if (IsMouseInRegion(controlRect))
				{
					hover = true;
				}
				control->Draw(hover);
			}
		}

		if (SkipWidget)
		{
			auto control = window->FocusedControl;

			if (control != nullptr && control->Flag(UIFlags::UI_Drawable))
			{
				POINT cAbs = control->GetAbsolutePos();
				RECT controlRect = { cAbs.x, cAbs.y, control->m_iWidth, control->m_iHeight };
				bool hover = false;
				if (IsMouseInRegion(controlRect))
				{
					hover = true;
				}
				control->Draw(hover);
			}
		}

	}

	return true;
}

void CGUI::RegisterWindow(CWindow* window)
{
	Windows.push_back(window);
}

void CGUI::BindWindow(unsigned char Key, CWindow* window)
{
	if (window)
		WindowBinds[Key] = window;
	else
		WindowBinds.erase(Key);
}

void CGUI::SaveWindowState(CWindow* window, std::string Filename)
{
	tinyxml2::XMLDocument Doc;

	tinyxml2::XMLElement *Root = Doc.NewElement("AVOZ");
	Doc.LinkEndChild(Root);

	if (Root && window->Tabs.size() > 0)
	{
		for (auto Tab : window->Tabs)
		{
			tinyxml2::XMLElement *TabElement = Doc.NewElement(Tab->Title.c_str());
			Root->LinkEndChild(TabElement);

			if (TabElement && Tab->Controls.size() > 1)
			{
				for (auto Control : Tab->Controls)
				{
					if (Control && Control->Flag(UIFlags::UI_SaveFile) && Control->FileIdentifier.length() > 1 && Control->FileControlType)
					{
						tinyxml2::XMLElement *ControlElement = Doc.NewElement(Control->FileIdentifier.c_str());
						TabElement->LinkEndChild(ControlElement);

						if (!ControlElement)
						{
							return;
						}

						CCheckBox* cbx = nullptr;
						CComboBox* cbo = nullptr;
						CKeyBind* key = nullptr;
						CSlider* sld = nullptr;

						switch (Control->FileControlType)
						{
						case UIControlTypes::UIC_CheckBox:
							cbx = (CCheckBox*)Control;
							ControlElement->SetText(cbx->GetState());
							break;
						case UIControlTypes::UIC_ComboBox:
							cbo = (CComboBox*)Control;
							ControlElement->SetText(cbo->GetIndex());
							break;
						case UIControlTypes::UIC_KeyBind:
							key = (CKeyBind*)Control;
							ControlElement->SetText(key->GetKey());
							break;
						case UIControlTypes::UIC_Slider:
							sld = (CSlider*)Control;
							ControlElement->SetText(sld->GetValue());
							break;
						}
					}
				}
			}
		}
	}

	if (Doc.SaveFile(Filename.c_str()) != tinyxml2::XML_NO_ERROR)
	{
		MessageBox(NULL, "Failed To Save Config File!", "AVOZ", MB_OK);
	}

}

void CGUI::LoadWindowState(CWindow* window, std::string Filename)
{
	tinyxml2::XMLDocument Doc;
	if (Doc.LoadFile(Filename.c_str()) == tinyxml2::XML_NO_ERROR)
	{
		tinyxml2::XMLElement *Root = Doc.RootElement();

		if (Root)
		{
			if (Root && window->Tabs.size() > 0)
			{
				for (auto Tab : window->Tabs)
				{
					tinyxml2::XMLElement *TabElement = Root->FirstChildElement(Tab->Title.c_str());
					if (TabElement)
					{
						if (TabElement && Tab->Controls.size() > 0)
						{
							for (auto Control : Tab->Controls)
							{
								if (Control && Control->Flag(UIFlags::UI_SaveFile) && Control->FileIdentifier.length() > 1 && Control->FileControlType)
								{
									tinyxml2::XMLElement *ControlElement = TabElement->FirstChildElement(Control->FileIdentifier.c_str());

									if (ControlElement)
									{
										CCheckBox* cbx = nullptr;
										CComboBox* cbo = nullptr;
										CKeyBind* key = nullptr;
										CSlider* sld = nullptr;

										switch (Control->FileControlType)
										{
										case UIControlTypes::UIC_CheckBox:
											cbx = (CCheckBox*)Control;
											cbx->SetState(ControlElement->GetText()[0] == '1' ? true : false);
											break;
										case UIControlTypes::UIC_ComboBox:
											cbo = (CComboBox*)Control;
											cbo->SelectIndex(atoi(ControlElement->GetText()));
											break;
										case UIControlTypes::UIC_KeyBind:
											key = (CKeyBind*)Control;
											key->SetKey(atoi(ControlElement->GetText()));
											break;
										case UIControlTypes::UIC_Slider:
											sld = (CSlider*)Control;
											sld->SetValue(atof(ControlElement->GetText()));
											break;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}