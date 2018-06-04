#pragma once

#include "GUI.h"
#include "Interfaces.h"

void CWindow::SetPosition(int x, int y)
{
	m_x = x; m_y = y;
}

void CWindow::SetSize(int w, int h)
{
	m_iWidth = w;
	m_iHeight = h;
}

void CWindow::SetTitle(std::string title)
{
	Title = title;
}

void CWindow::RegisterTab(CTab* Tab)
{
	if (Tabs.size() == 0)
	{
		SelectedTab = Tab;
	}
	Tab->parent = this;
	Tabs.push_back(Tab);
}

RECT CWindow::GetClientArea()
{
	RECT client;
	client.left = m_x + 150;
	client.top = m_y + 40; //26
	client.right = m_iWidth - 150;
	client.bottom = m_iHeight - 40; //26
	return client;
}

RECT CWindow::GetTabArea()
{
	RECT client;
	client.left = m_x;
	client.top = m_y + 26; //26
	client.right = 150;
	client.bottom = m_iHeight - 26; //26
	return client;
}

bool CWindow::Open()
{
	return m_bIsOpen;
}

void CWindow::Close()
{
	m_bIsOpen = false;
}

void CWindow::Toggle()
{
	m_bIsOpen = !m_bIsOpen;
	if (m_bIsOpen)
	{
		Interfaces::Engine->ClientCmd_Unrestricted("cl_mouseenable 0");

	}

	else
	{
		Interfaces::Engine->ClientCmd_Unrestricted("cl_mouseenable 1");

	}
}

CControl* CWindow::GetFocus()
{
	return FocusedControl;
}

void CTab::SetTitle(std::string name)
{
	Title = name;
}

void CTab::RegisterControl(CControl* control)
{
	control->parent = parent;
	Controls.push_back(control);
}
