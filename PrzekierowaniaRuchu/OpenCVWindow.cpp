#include "OpenCVWindow.h"

OpenCVWindow::OpenCVWindow(): width(0), heigh(0)
{
}

void OpenCVWindow::openwindow()
{
	double latFrom, latTo, lonFrom, lonTo, roznicaLonX, roznicaLatY, minLat, minLong;

	auto image = imread("background-wroclaw-map.png");

	auto img_size = image.size();
	width = img_size.width;
	heigh = img_size.height;

	auto tab = new string[4];
	MySqlConnection::getMySqlConnection().getMinMaxLatLon(tab);

	sql::ResultSet* result;

	auto index = 0;

	minLat = stod(tab[1]);
	minLong = stod(tab[2]);

	roznicaLonX = stod(tab[3]) - stod(tab[2]);
	roznicaLatY = stod(tab[0]) - stod(tab[1]);

	double point1x, point1y, point2x, point2y;

	do
	{
		result = MySqlConnection::getMySqlConnection().getBothEdgeEnds(index);

		while (result->next())
		{
			latFrom = result->getDouble("latFrom");
			latTo = result->getDouble("latTo");
			lonFrom = result->getDouble("lonFrom");
			lonTo = result->getDouble("lonTo");

			point1x = ((lonFrom - minLong) * width) / roznicaLonX;
			point1y = heigh - ((latFrom - minLat) * heigh) / roznicaLatY;

			point2x = ((lonTo - minLong) * width) / roznicaLonX;
			point2y = heigh - ((latTo - minLat) * heigh) / roznicaLatY;

			if (point1x > 0.0 && point1y > 0.0 && point2x > 0.0 && point2y > 0.0)
				DrawLine(image, Point(point1x, point1y), Point(point2x, point2y));
		}

		index += 1000;
	}
	while (result->rowsCount() != 0);


	imwrite("../map.png", image);
}

void OpenCVWindow::MyFilledCircle(Mat img, Point center)
{
	circle(img,
	       center,
	       1,
	       Scalar(0, 0, 0),
	       -1,
	       LINE_AA);
}

void OpenCVWindow::DrawLine(Mat img, Point start, Point end)
{
	MyFilledCircle(img, start);
	MyFilledCircle(img, end);

	line(img,
	     start,
	     end,
	     Scalar(255, 0, 187),
	     1,
	     LINE_AA);
}
