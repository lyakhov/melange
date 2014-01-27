/* main-window.cpp
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

#include "main-window.h"

#include <QHBoxLayout>
#include <QFormLayout>

MainWindow::MainWindow():
 m_bIsMicTesting(false), m_bIsActiveCall(false)
{
	setFixedSize(500, 250);
	
	m_centralWidget = new QWidget(this);
	setCentralWidget(m_centralWidget);
	
	m_widgetMicTest = new QWidget(this);
	m_widgetMakeCall = new QWidget(this);
	
	m_pushBtnTestSpeaker = new QPushButton("Test", this);
	m_pushBtnTestMicrophone = new QPushButton ("Start", this);
	m_pushBtnMakeCall = new QPushButton ("Make Call", this);
	m_pushBtnTestSpeaker->setFixedSize(60,30);
	
	m_textEditAddress = new QLineEdit (this);
	
	m_barTestMicro = new QProgressBar (this);
	m_barTestMicro->setRange(0, 9);
	
	QHBoxLayout* layoutMicTest = new QHBoxLayout;
	layoutMicTest->addWidget(m_pushBtnTestMicrophone);
	layoutMicTest->addWidget(m_barTestMicro);
	
	QHBoxLayout* layoutMakeCall = new QHBoxLayout;
	layoutMakeCall->addWidget(m_pushBtnMakeCall);
	layoutMakeCall->addWidget(m_textEditAddress);
	
	m_widgetMicTest->setLayout(layoutMicTest);
	m_widgetMakeCall->setLayout(layoutMakeCall);
	
	m_timerVolumeCheck = new QTimer (this);
	
	m_playoutDeviceCombox = new QComboBox(this);
	m_recordingDeviceCombox = new QComboBox(this);
	
	QFormLayout* audioDeviceLayout = new QFormLayout;
	audioDeviceLayout->addRow("Playout device", m_playoutDeviceCombox);
	audioDeviceLayout->addRow("Recording device", m_recordingDeviceCombox);
	audioDeviceLayout->addRow("Play tone", m_pushBtnTestSpeaker);
	audioDeviceLayout->addRow("Test microphone", m_widgetMicTest);
	audioDeviceLayout->addRow("Make Call", m_widgetMakeCall);

	m_centralWidget->setLayout(audioDeviceLayout);
	
	std::vector<std::string> playout_dev, recording_dev;
	m_audioAdaptor.GetPlayBackDevices(playout_dev);
	for (int i = 0; i < playout_dev.size(); i++)
	{
		m_playoutDeviceCombox->addItem(playout_dev[i].c_str());
	}
	
	m_audioAdaptor.GetRecordingDevices(recording_dev);
	for (int i = 0; i < recording_dev.size(); i++)
	{
		m_recordingDeviceCombox->addItem(recording_dev[i].c_str());
	}
	
	connect (m_playoutDeviceCombox, SIGNAL(currentIndexChanged(int)), 
		this, SLOT(on_playout_combobox_index_changed(int)));
	connect (m_recordingDeviceCombox, SIGNAL(currentIndexChanged(int)), 
		this, SLOT(on_recording_combobox_index_changed(int)));
	connect (m_timerVolumeCheck, SIGNAL(timeout()), this, SLOT(on_timeout_fired()));
	connect (m_pushBtnTestSpeaker, SIGNAL(pressed()), this, SLOT(on_pushbtn_test_speaker_pressed()));
	connect (m_pushBtnTestMicrophone, SIGNAL(pressed()), this, SLOT(on_pushbtn_test_mic_pressed()));
	connect (m_pushBtnMakeCall, SIGNAL(pressed()), this, SLOT(on_pushbtn_make_call_pressed()));
}

void MainWindow::on_playout_combobox_index_changed(int index)
{
	std::string dev = m_playoutDeviceCombox->currentText().toStdString();
	m_audioAdaptor.SetPlayoutDevice(dev);
}

void MainWindow::on_recording_combobox_index_changed(int index)
{
	std::string dev = m_recordingDeviceCombox->currentText().toStdString();
	m_audioAdaptor.SetRecordingDevice(dev);
}

void MainWindow::on_timeout_fired()
{
	m_barTestMicro->setValue(m_audioAdaptor.GetMicrophoneLevel());
}

void MainWindow::on_pushbtn_test_speaker_pressed()
{
	m_audioAdaptor.PlayTone();
}

void MainWindow::on_pushbtn_test_mic_pressed()
{
	if (m_bIsMicTesting)
	{
		m_timerVolumeCheck->stop();
		m_pushBtnTestMicrophone->setText("Start");
		m_audioAdaptor.StopMicTest();
		m_barTestMicro->setValue(0);
	}
	else
	{
		m_timerVolumeCheck->start(100);
		m_pushBtnTestMicrophone->setText("Stop");
		m_audioAdaptor.StartMicTest();
	}
	m_bIsMicTesting = !m_bIsMicTesting;
}

void MainWindow::on_pushbtn_make_call_pressed()
{
	if (m_bIsActiveCall)
	{
		m_audioAdaptor.EndCall();
		m_pushBtnMakeCall->setText("Make Call");
		m_bIsActiveCall = false;
	}
	else
	{
		std::string addr = m_textEditAddress->text().toStdString();
		m_audioAdaptor.MakeCall(addr);
		m_pushBtnMakeCall->setText("End Call");
		m_bIsActiveCall = true;
	}
}

MainWindow::~MainWindow()
{
	
}
