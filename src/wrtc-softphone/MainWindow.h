/* MainWindow.h
 *
 * Copyright 2014 Yegor Mazur <yegor.mazur@gmail.com>
 *
 * This file is part of Melange.
 *
 * Melange is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Melange is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Melange. If not, see <http://www.gnu.org/licenses/>.
 *
 * This file was derived from helloworld.c test/example of GStreamer framework.
 */

#include <QMainWindow>
#include <QLabel>
#include <QComboBox>

class MainWindow : public QMainWindow
{
	QLabel* m_AudioDeviceLabel;
	QComboBox* m_AudioDeviceCombox;
	
	
public:
	MainWindow();
	virtual ~MainWindow();
};
