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
 */

#include <QMainWindow>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include "AudioAdaptor.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
	QLabel* m_audioDeviceLabel;
	QComboBox* m_audioDeviceCombox;
	QWidget* m_centralWidget;
	QVBoxLayout m_audioDeviceLayout;
	QVBoxLayout m_mainLayout;
	
	AudioAdaptor m_audioAdaptor;
	
public:
	MainWindow();
	virtual ~MainWindow();
};
