#pragma once

namespace threshold
{
	void init();
	void update();
	void draw();
	void destroy();

	void ProcessMouse(double xpos, double ypos);
	void ProcessScroll(double xoffset, double yoffset);
	void ProcessKeyboardInput(float deltaTime);
}