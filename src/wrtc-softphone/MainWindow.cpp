/* MainWindow.cpp
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

#include "MainWindow.h"

MainWindow::MainWindow()
{
	setFixedSize(300, 200);
	
	m_centralWidget = new QWidget(this);
	setCentralWidget(m_centralWidget);
	
	m_audioDeviceLabel = new QLabel("Audio Device", this);
	m_audioDeviceCombox = new QComboBox(this);
	
	m_audioDeviceLayout.addWidget(m_audioDeviceLabel, Qt::AlignTop);
	m_audioDeviceLayout.addWidget(m_audioDeviceCombox, Qt::AlignTop);
	//m_mainLayout.addLayout(&m_audioDeviceLayout);
	m_centralWidget->setLayout(&m_audioDeviceLayout);
	
	std::vector<std::string> dev;
	m_audioAdaptor.GetAudioDevices(dev);
	//connect(m_audioDeviceCombox, SIGNAL(), this, SLOT(
}

MainWindow::~MainWindow()
{
	
}
