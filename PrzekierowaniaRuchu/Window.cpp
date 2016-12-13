#include "Window.h"

Window::Window()
{
	auto opencvwindow = OpenCVWindow();

	auto thr = new thread(bind(&OpenCVWindow::openwindow, &opencvwindow));
	thr->join();
}
