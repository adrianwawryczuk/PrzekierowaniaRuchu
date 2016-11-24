#include "Window.h"

Window::Window()
{

	OpenCVWindow opencvwindow = OpenCVWindow();

	thread* thr = new thread(bind(&OpenCVWindow::openwindow, &opencvwindow));
	thr->join();

}
